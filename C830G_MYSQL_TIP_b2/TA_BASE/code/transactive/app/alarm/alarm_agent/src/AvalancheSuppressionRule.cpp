/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/alarm/alarm_agent/src/AvalancheSuppressionRule.cpp $
  * @author:  Ross Tucker
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */
#ifdef _MSC_VER
#pragma warning(disable : 4786)
#pragma warning(disable : 4503)
#endif

#include "app/alarm/alarm_agent/src/AvalancheSuppressionRule.h"
#include "app/alarm/alarm_agent/src/AlarmCache.h"
#include "app/alarm/alarm_agent/src/LocalRunParamDefinitions.h"
#include <sstream>
#include "core/alarm/IDL/src/AlarmMessageCorbaDef.h"
// TD 13530
// #include "core/message/src/AuditMessageSender.h"
// #include "core/message/types/AlarmAudit_MessageTypes.h"
#include "core/message/src/NameValuePair.h"
#include "core/message/src/MessagePublicationManager.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/RunParams.h"
#include "core/utilities/src/AlarmClock.h"
#include "core/synchronisation/src/ThreadGuard.h"
#include "core/synchronisation/src/ThreadReadGuard.h"

using TA_Base_Core::DebugUtil;
using TA_Base_Core::ThreadGuard;

namespace TA_Base_App
{

    //
    // Constructor
    //
    AvalancheSuppressionRule::AvalancheSuppressionRule(unsigned long entityKey, unsigned long entityType, unsigned long alarmTypeKey,
                                                       TA_Base_App::AbstractRule::ETriggerType trigger,
                                                       unsigned long key, unsigned long timeout, unsigned long timein, unsigned int minAlarms,
                                                       const std::vector<AvalancheSuppressionChild*>& children )
            : AbstractRule(entityKey, entityType, alarmTypeKey, trigger, key),
              m_timeout(timeout), m_timein(timein), m_minAlarmsToValidate(minAlarms), m_children(children), m_expiryTime(0), m_alarmsSuppressed(0), m_headAlarmId("")
    {
        LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
             "Head alarm: entity key - %lu entity type - %lu alarm type - %u timeout - %lu", entityKey, entityType, alarmTypeKey, timeout );

		// TD 13530 Audit messages to be sent by AlarmQueue after updating alarm table
        //m_auditSender = TA_Base_Core::MessagePublicationManager::getInstance().getAuditMessageSender(
        //                    TA_Base_Core::AlarmAudit::Context);

        m_timeoutTimer = new TA_Base_Core::AlarmClock( this );
        m_timeinTimer = new TA_Base_Core::AlarmClock( this );

    }


    //
    // Destructor
    //
    AvalancheSuppressionRule::~AvalancheSuppressionRule()
    {
		// TD 13530
        /*if( m_auditSender != NULL )
        {
            delete m_auditSender;
            m_auditSender = 0;
        } */

        for( unsigned int i = 0; i < m_children.size(); i++ )
        {
            if( m_children[i] != NULL )
            {
                delete m_children[i];
                m_children[i] = NULL;
            }
        }

		if (m_timeoutTimer!=NULL)
		{
			m_timeoutTimer->terminate();
			delete m_timeoutTimer;
			m_timeoutTimer = NULL;
		}
		if (m_timeinTimer!=NULL)
		{
			m_timeinTimer->terminate();
			delete m_timeinTimer;
			m_timeinTimer = NULL;
		}
    }


    //
    // process
    //
    void AvalancheSuppressionRule::process( const TA_Base_Core::AlarmDetailCorbaDef& message,
                                            TA_Base_App::AbstractRule::ETriggerType trigger )
    {
        if( doesRuleApply(message, TA_Base_App::AbstractRule::SUBMIT) ) // Avalanche rules are always triggered by a submit
        {
            if( trigger == TA_Base_App::AbstractRule::SUBMIT )
            {
                m_expiryTime = message.sourceTime.time + m_timeout;
                m_activateTime = message.sourceTime.time + m_timein;
                m_alarmsSuppressed = 0;
                // TD12742
				//m_headAlarmId = message.alarmID;

                // start required timers
                if ( m_timein != 0 )
                {
                    // start timer and give an extra second to give slow alarms a chance to be processed
                    m_timeinTimer->start( m_timein + 1000 );
                }
                // start timer and give an extra second to give slow alarms a chance to be processed
                m_timeoutTimer->start( m_timeout + 1000 );

                LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
                     "Head detected, expiry time set to %lu", m_expiryTime );

                TA_Base_Core::DescriptionParameters dp;
                TA_Base_Core::NameValuePair alarmDesc("alarmDescription", message.alarmDescription.in());
                dp.push_back(&alarmDesc);

				// Extract the time
				timeb sourceTime = {0,0,-1,-1};
				sourceTime.time = message.sourceTime.time;
				sourceTime.millitm = message.sourceTime.millitm;

                std::string session = TA_Base_Core::RunParams::getInstance().get(TA_Base_App::TA_AlarmAgent::SESSION.c_str());

				// TD 13530
                //m_auditSender->sendAuditMessageWithAsset(
                //        TA_Base_Core::AlarmAudit::AlarmIsAvalancheHead,
                //        message.assocEntityKey, dp, "", session, std::string(message.alarmID), 
				//		"", "", std::string(message.assetName.in()), 0, sourceTime );

                // FUTURE:: call the cache to reprocess all alarms in case one arrived before
                //          the rule became active.
                //          should this call be here or in timeinTimerExpired()?
            }
            else if( trigger == TA_Base_App::AbstractRule::CLOSE )
            {
                m_expiryTime = 0;
                m_timeinTimer->cancel();
                m_timeoutTimer->cancel();
                openAlarms();
            }
        }
    }


    //
    // alarmIsAnAvalancheHead
    //
    bool AvalancheSuppressionRule::alarmIsAnAvalancheHead( const TA_Base_Core::AlarmDetailCorbaDef& message )
    {
        FUNCTION_ENTRY("alarmIsAnAvalancheHead");

        if ( doesRuleApply(message, TA_Base_App::AbstractRule::SUBMIT) )
        {
            // TD12742++
		    m_headAlarmId = message.alarmID;
            LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
                        "Avalanche Head alarm id set to %s", m_headAlarmId.c_str());
            // ++TD12742


            FUNCTION_EXIT;
            return true;
        }

        FUNCTION_EXIT;
        return false;
    }


    //
    // alarmShouldBeSuppressed
    //
    bool AvalancheSuppressionRule::alarmShouldBeSuppressed( const TA_Base_Core::AlarmDetailCorbaDef& message )
    {
        FUNCTION_ENTRY("alarmShouldBeSuppressed");

        // is this alarm before the currect expiry time
        if( (m_expiryTime <= 0) || (m_expiryTime < message.sourceTime.time) )
        {
            LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug,
                 "Rule expiry time is %li message source time is %lu", m_expiryTime, message.sourceTime.time );

            return false;
        }

        LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
             "Number of avalanche children is %lu", m_children.size() );


        // loop through the child alarms to see if this rule applies to one of them.
        for( unsigned int i = 0; i < m_children.size(); i++ )
        {
            if( m_children[i] != NULL )
            {
                if( true == (m_children[i])->compareToAlarm(message) )
                {
                    LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
                         "Suppressing child" );

                    ThreadGuard guard(m_listLock);

                    const_cast<TA_Base_Core::AlarmDetailCorbaDef&>(message).state = TA_Base_Core::AlarmSuppressed;
                    const_cast<TA_Base_Core::AlarmDetailCorbaDef&>(message).isChildOfAvalanche = true; //Set the flag of this alarm as avalanche child

					// Send audit or event message that a child has been suppressed
					TA_Base_Core::DescriptionParameters dp;
					TA_Base_Core::NameValuePair alarmDesc("alarmDescription", message.alarmDescription.in());
					dp.push_back(&alarmDesc);

					std::string session = TA_Base_Core::RunParams::getInstance().get(TA_Base_App::TA_AlarmAgent::SESSION.c_str());

					// Extract the time
					timeb sourceTime = {0,0,-1,-1};
					sourceTime.time = message.sourceTime.time;
					sourceTime.millitm = message.sourceTime.millitm;

					// since this is a avalanche child alarm, set the head alarm id
					const_cast<TA_Base_Core::AlarmDetailCorbaDef&>(message).avalancheHeadID = m_headAlarmId.c_str();

					 // suppress the alarm in the cache ie hide it in the cache for later release
                    AlarmCache::getInstance()->insertSuppressed( message );

                    m_suppressedAlarmIds.push_back( message.alarmID.in() );
                    if( m_activateTime > message.sourceTime.time)
                    {
                        m_alarmsSuppressed++;
                    }

                    // TD12742++
					/*m_auditSender->sendAuditMessageWithAsset(
							TA_Base_Core::AlarmAudit::AlarmIsAvalancheChild,
							message.assocEntityKey, dp, "", session, std::string(message.alarmID), 
							"", "", std::string(message.assetName.in()), 0, sourceTime );*/

					// TD 13530
                    /*m_auditSender->sendAuditMessageWithAsset(
							TA_Base_Core::AlarmAudit::AlarmIsAvalancheChild,
							message.assocEntityKey, dp, "", session, m_headAlarmId, 
							"", "", std::string(message.assetName.in()), 0, sourceTime );*/

                    //LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
                    //    "Sent Avalanche Child Audit message. Child id: %s, Head id: %s", message.alarmID, m_headAlarmId.c_str());
                    // ++TD12742

                    return true;
                }
            }
        }

        LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
             "Active avalanche does not apply to alarm." );

        FUNCTION_EXIT;
        return false;
    }

	//
	// getHeadAlarmId
	//
	std::string AvalancheSuppressionRule::getHeadAlarmId()
	{
		return m_headAlarmId;
	}

    //
    // timerExpired
    //
    void AvalancheSuppressionRule::executeAlarm( TA_Base_Core::AlarmClock* clock )
    {
        if ( m_timeoutTimer == clock )
        {
            timeoutExpired();
            return;
        }
        if ( m_timeinTimer == clock )
        {
            timeinExpired();
            return;
        }
        TA_ASSERT( false, "Unknown alarmClock went off");
    }

    //
    // TimeoutExpired
    //
    void AvalancheSuppressionRule::timeoutExpired()
    {
        // deactivate the rule
        m_expiryTime = 0;
        m_alarmsSuppressed = 0;

        // repost the child alarms
        openAlarms();
    }

    //
    // TimeinExpired
    //
    void AvalancheSuppressionRule::timeinExpired()
    {
        // check for enough alarms
        if( m_alarmsSuppressed < m_minAlarmsToValidate )
        {
            // deactivate the rule
            m_expiryTime = 0;
            m_alarmsSuppressed = 0;

            // kill the timeout timer
            m_timeoutTimer->cancel();

            // repost the child alarms
            openAlarms();
        }
        // FUTURE:: call the cache to reprocess all alarms in case one arrived before
        //          the rule became active.
        //          should this call be here or in process()?
    }

    // 
    // openAlarms
    //
    void AvalancheSuppressionRule::openAlarms()
    {
        // must be very carefull as the call to the cache will call us back
        // and could create a deadlock
        // to avoid this we copy the critical data and then release the lock
        
        
        // TD 11027 - use scope to ensure the guard is destroyed before calling the cache
        std::vector<std::string> alarmList;
        {
            ThreadGuard guard( m_listLock );  
            alarmList = m_suppressedAlarmIds;
            m_suppressedAlarmIds.clear();
        }

        AlarmCache::getInstance()->openAlarms( alarmList );
    }

};
