/**
  * The source code in this file is the property of Ripple Systems and is not for redistribution in
  * any form.
  *
  * Source:		$File$
  * @author:	Weimin
  * @version $Revision$
  *
  * Last modification : $DateTime$
  * Last modified by : $Author$
  *
  *
  * AlarmAckStateProcessor provides a single interface to subscribe and unsubscribe for alarm
  * acknowledgemnt from an alarm entity.
  *
  */

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#pragma warning(disable:4250)
#endif // defined (_MSC_VER)

#include <sstream>

#include "bus/scada/datapoint_library/src/IAlarmAckStateUser.h"
#include "bus/scada/datapoint_library/src/AlarmAckStateProcessor.h"

#include "core/alarm/IDL/src/AlarmAgentCorbaDef.h"
#include "core/alarm/src/AlarmHelper.h"
#include "core/alarm/src/AlarmHelperManager.h"
#include "core/alarm/src/AlarmSubscriptionManager.h"
#include "core/alarm/IDL/src/AlarmMessageCorbaDef.h"
#include "core/data_access_interface/src/LocationAccessFactory.h"
#include "core/exceptions/src/TransactiveException.h"
#include "core/message/types/MessageTypes.h"
#include "core/message/types/DataPointAlarms_MessageTypes.h"
#include "core/synchronisation/src/ThreadGuard.h"
#include "core/synchronisation/src/ThreadReadGuard.h"
#include "core/timers/src/SingletonTimerUtil.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/corba/src/CorbaUtil.h"

using TA_Base_Core::DebugUtil;

namespace TA_Base_Bus
{
	//
	// static declaration
	//

	AlarmAckStateProcessor *							AlarmAckStateProcessor::m_singletonManager = 0;
	TA_Base_Core::ReEntrantThreadLockable				AlarmAckStateProcessor::m_singletonLock;



	AlarmAckStateProcessor::AlarmAckStateProcessor()
	{
        m_alarmLocations.clear();
        m_toRetryQueue.clear();
        m_alarmEntityMap.clear();
        m_alarmIdMap.clear();
        
		m_currentAlarmIdMap.clear();

		m_bLoadAlarmsError = false;
		m_bLoadAlarms = false;
		m_bGotAlarmDetail = false;
        //start processor thread
        start();

        //schedule a 10 seconds retry timer
        TA_Base_Core::SingletonTimerUtil::getInstance().startPeriodicTimeOutClock ( this, 10000, false );
    }


	AlarmAckStateProcessor::~AlarmAckStateProcessor()
	{
        //stop processor thread first
        TA_Base_Core::SingletonTimerUtil::getInstance().stopPeriodicTimeOutClock( this );
        terminateAndWait();

        m_alarmLocations.clear();
        m_toRetryQueue.clear();
        m_alarmEntityMap.clear();
        m_alarmIdMap.clear();
		m_currentAlarmIdMap.clear();

		m_entityToAlarmMap.clear();
        
        // let the AlarmSubscriptionManager to know that we are not interesting in 
        // receiving any alarm messages
        try
        {
            TA_Base_Core::AlarmSubscriptionManager::unsubscribeToMessages ( this );
        }
        catch ( ... )
        {
        }
	}


	TA_Base_Bus::AlarmAckStateProcessor& AlarmAckStateProcessor::getInstance()
	{
		// prevent multiple threads attempting to delete/create
		// simultaneously
		TA_THREADGUARD( m_singletonLock );

		// if the singleton has not been created yet
		if ( 0 == m_singletonManager )
		{
			// create one and only one instance
			m_singletonManager = new AlarmAckStateProcessor();
		}

		return *m_singletonManager;
	}


	void AlarmAckStateProcessor::removeInstance ()
	{
		// prevent multiple threads attempting to delete/create
		// simultaneously
		TA_THREADGUARD( m_singletonLock );

		// destroy the only instance
		delete m_singletonManager;
		m_singletonManager = 0;
	}

	void AlarmAckStateProcessor::receiveAlarmMessage( const TA_Base_Core::AlarmMessageCorbaDef & alarmMessage )
	{
        AlarmAckUpdate* alarmAckUpdate = NULL; 

        switch ( alarmMessage._d() )
        {
        case TA_Base_Core::NewAlarm:
            {
                // new alarm message has alarm value and alarm id, use these can build the alarm id map.
                alarmAckUpdate = new AlarmAckUpdate();
                alarmAckUpdate->m_updateType = AlarmAckUpdate::Update;

                alarmAckUpdate->m_alarmTypeKey = alarmMessage.alarm().messageTypeKey;
                alarmAckUpdate->m_ackState = ScadaAlarmNack;
                alarmAckUpdate->m_entityKey = alarmMessage.alarm().assocEntityKey;
                alarmAckUpdate->m_locationKey = alarmMessage.alarm().assocEntityKey;
                alarmAckUpdate->m_alarmId = alarmMessage.alarm().alarmID;
                alarmAckUpdate->m_user = NULL;

                // for DpGeneral alarm type, need to check the enum value of the alarm
                if (alarmAckUpdate->m_alarmTypeKey == atol(TA_Base_Core::DataPointAlarms::DpGeneral.getTypeKey().c_str()))
                {
                    alarmAckUpdate->m_valueString = alarmMessage.alarm().alarmValue;
                }
                else
                {
                    alarmAckUpdate->m_valueString = "NotUsed";
                }
                
                LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "receive a new alarm message: entity [%u], alarm type [%u], alarm value [%s], alarm id [%s]",
                    alarmAckUpdate->m_entityKey, alarmAckUpdate->m_alarmTypeKey, alarmAckUpdate->m_valueString.c_str(), alarmAckUpdate->m_alarmId.c_str());
                
                break;
            }
        case TA_Base_Core::UpdateAlarm:
            {
                // update alarm message has no alarm value property, so have to use alarm id to find the subscriber.
                alarmAckUpdate = new AlarmAckUpdate();
                alarmAckUpdate->m_updateType = AlarmAckUpdate::Update;
                
                alarmAckUpdate->m_alarmTypeKey = alarmMessage.update().messageTypeKey;

                std::string ackedBy(alarmMessage.update().alarmAcknowledgedBy);
                bool isAcked = !ackedBy.empty();
                bool isClosed = alarmMessage.update().alarmHasBeenClosed;
                
                if (isClosed && isAcked)
                {
                    alarmAckUpdate->m_ackState = ScadaAlarmNotPresent;
                }
                else
                {
                    alarmAckUpdate->m_ackState = isAcked ? ScadaAlarmAck : ScadaAlarmNack;
                }
                
                alarmAckUpdate->m_entityKey = alarmMessage.update().assocEntityKey;
                alarmAckUpdate->m_locationKey = alarmMessage.update().assocEntityKey;
                alarmAckUpdate->m_alarmId = alarmMessage.update().alarmID;
                alarmAckUpdate->m_user = NULL;

                LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "receive an update alarm message: entity [%u], alarm type [%u], alarm ID [%s]",
                    alarmAckUpdate->m_entityKey, alarmAckUpdate->m_alarmTypeKey, alarmAckUpdate->m_alarmId.c_str());
                
                break;
            }
        default:
            {
                break;
            }
        }
        
		if (NULL != alarmAckUpdate)
		{
			boost::shared_ptr<AlarmAckUpdate> ackUpdate(alarmAckUpdate);
            this->insertUnique(ackUpdate);
		}
	}

	void AlarmAckStateProcessor::requestLoadAlarms( unsigned long alarmEntityLocationKey )
	{
		AlarmAckUpdate* alarmAckUpdate = new AlarmAckUpdate();
		alarmAckUpdate->m_updateType = AlarmAckUpdate::LoadAlarms;
        alarmAckUpdate->m_locationKey = alarmEntityLocationKey;
	
	
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "receive a LoadAlarms request: EntityLocation [%d]",
			alarmEntityLocationKey);
		
		boost::shared_ptr<AlarmAckUpdate> ackUpdate(alarmAckUpdate);
		this->insertUnique(ackUpdate);
	}

	void AlarmAckStateProcessor::subscribeToAlarmType ( const TA_Base_Core::MessageType & alarmMessageType,
								const std::string & valueString,
                                IAlarmAckStateUser * user,
								unsigned long alarmEntityKey,
								unsigned long alarmEntityLocationKey )
	{
        AlarmAckUpdate* alarmAckUpdate = new AlarmAckUpdate();
        alarmAckUpdate->m_updateType = AlarmAckUpdate::Subscribe;
        
        alarmAckUpdate->m_alarmType = &alarmMessageType;
        alarmAckUpdate->m_alarmTypeKey = atol(alarmMessageType.getTypeKey().c_str());
        alarmAckUpdate->m_valueString = valueString;
        alarmAckUpdate->m_entityKey = alarmEntityKey;
        alarmAckUpdate->m_locationKey = alarmEntityLocationKey;
        alarmAckUpdate->m_user = user;

        LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "receive a subcribe request: entity [%u], alarm type [%u], alarm value [%s]",
            alarmAckUpdate->m_entityKey, alarmAckUpdate->m_alarmTypeKey, alarmAckUpdate->m_valueString.c_str());

        boost::shared_ptr<AlarmAckUpdate> ackUpdate(alarmAckUpdate);
        this->insertUnique(ackUpdate);
	}

	void AlarmAckStateProcessor::unsubscribeToAlarmType ( const TA_Base_Core::MessageType & alarmMessageType,
								  const std::string & valueString,
                                  unsigned long alarmEntityKey,
								  unsigned long alarmEntityLocationKey )
	{
        AlarmAckUpdate* alarmAckUpdate = new AlarmAckUpdate();
        alarmAckUpdate->m_updateType = AlarmAckUpdate::Unsubscribe;
        
        alarmAckUpdate->m_alarmType = &alarmMessageType;
        alarmAckUpdate->m_alarmTypeKey = atol(alarmMessageType.getTypeKey().c_str());
        alarmAckUpdate->m_valueString = valueString;
        alarmAckUpdate->m_entityKey = alarmEntityKey;
        alarmAckUpdate->m_locationKey = alarmEntityLocationKey;
        alarmAckUpdate->m_user = NULL;
        
        LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "receive a unsubcribe request: entity [%u], alarm type [%u], alarm value [%s]",
            alarmAckUpdate->m_entityKey, alarmAckUpdate->m_alarmTypeKey, alarmAckUpdate->m_valueString.c_str());
        
        boost::shared_ptr<AlarmAckUpdate> ackUpdate(alarmAckUpdate);
        this->insertUnique(ackUpdate);
	}


    void AlarmAckStateProcessor::threadedTimerExpired(long timerId, void* userData)
    {
        // when timer expired, move all items from retry queue to working queue.
        TA_THREADGUARD( m_toRetryQueueLock );

		{
			if ((m_bLoadAlarms == false) && (m_bLoadAlarmsError == true))
			{
				LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "AlarmAckStateProcessor::threadedTimerExpired. loadAllAlarms again");
				
				loadAllAlarms(m_nLocationKey);
			}

		}

        if (m_toRetryQueue.empty())
        {
            return;
        }

        std::vector<boost::shared_ptr<AlarmAckUpdate> >::iterator updateIt = m_toRetryQueue.begin();
        for (; updateIt != m_toRetryQueue.end(); ++ updateIt)
        {
            this->insertUnique(*updateIt);
        }
        m_toRetryQueue.clear();
    }


    void AlarmAckStateProcessor::processEvent(boost::shared_ptr<AlarmAckUpdate> update)
	{
		if (NULL == update.get())
		{
			return;
		}

        LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Begin to process update [%u] for entity [%u]",
            update->m_updateType, update->m_entityKey);
        
		try
		{
			switch (update->m_updateType)
			{
			case AlarmAckUpdate::LoadAlarms:
				{
					LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Before ProcessEvent LoadAlarms.");
					loadAllAlarms(update->m_locationKey);
					LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "After ProcessEvent LoadAlarms.");
				}
				break;

            case AlarmAckUpdate::Subscribe:
				{
                    //to get alarm state from alarm agent
                    TA_Base_Core::AlarmDetailCorbaDef * alarmDetail = NULL;
                    EScadaAlarmAckState ackState = ScadaAlarmUnknown;
                    
                    try
                    {
						if ((m_bLoadAlarms == false) || (m_bLoadAlarmsError == true))
						{
							LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Cannot contact alarm agent, add the subscribe request to queue for later retry.",
								update->m_alarmTypeKey, update->m_valueString.c_str(), ackState, update->m_entityKey);
							
							TA_THREADGUARD( m_toRetryQueueLock );
							m_toRetryQueue.push_back(update);
							break;
						}

						// Obtain handle to the Alarm Helper
                        alarmDetail = getActiveAlarmForEntityOfType (update->m_alarmTypeKey,
							update->m_entityKey);

						if (!m_bGotAlarmDetail)
						{
							ackState = ScadaAlarmNotPresent;
						}
                    }
                    catch(...)
                    {
                        LOG_EXCEPTION_CATCH( SourceInfo, "Unknown Exception", 
                            "calling getActiveAlarmForEntityOfType." );
                    }

                    // if can't get alarm detail from alarm agent, schedule to retry and return
                    //if (!gotAlarmDetail)

                    //save alarm ack user to internal map
                    DataPointAlarmType dpAlarmType;
                    dpAlarmType.entityKey = update->m_entityKey;
                    dpAlarmType.alarmTypeKey = update->m_alarmTypeKey;
                    dpAlarmType.valueString = update->m_valueString;
                    
                    m_alarmEntityMap[dpAlarmType] = update->m_user;
                    
                    //save location to internal vector
                    if (m_alarmLocations.find(update->m_locationKey) == m_alarmLocations.end())
                    {
                        m_alarmLocations.insert(update->m_locationKey);
                        
                        // subscribe for all DataPoint alarm types from the specified location key
                        TA_Base_Core::AlarmSubscriptionManager::subscribeToAlarmsFromLocation ( 
                            TA_Base_Core::DataPointAlarms::Context,
                            this,
                            update->m_locationKey );
                    }
                    
                    std::string alarmId;

                    if( NULL != alarmDetail )
                    {
                        std::string ackedBy( alarmDetail->alarmAcknowledgedBy );
                        alarmId = alarmDetail->alarmID;

                        // if the alarm type is DpGeneral alarm, 
                        // need to get the alarm value to check if it is the exact enum value alarm
                        if (update->m_alarmTypeKey == atol(TA_Base_Core::DataPointAlarms::DpGeneral.getTypeKey().c_str()))
                        {
                            std::string valueString(alarmDetail->alarmValue);
                            if (valueString == update->m_valueString)
                            {
                                ackState = ackedBy.empty() ? ScadaAlarmNack : ScadaAlarmAck;
                            }
                        }
                        else
                        {
                            ackState = ackedBy.empty() ? ScadaAlarmNack : ScadaAlarmAck;
                        }

                        delete alarmDetail;
                        alarmDetail = NULL;
                    }

                    if (ackState != ScadaAlarmUnknown)
                    {
                        // if the alarm is not acknowledged or not closed, save it to alarm id map.
                        if (ackState == ScadaAlarmNack || ackState == ScadaAlarmAck)
                        {
                            m_alarmIdMap[alarmId] = update->m_user;
							m_currentAlarmIdMap[update->m_entityKey] = AlarmIDAndUser(alarmId, update->m_user);
                        }

                        LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Update alarm type [%u] with alarm value [%s] to AckState [%u] for entity [%u]",
                            update->m_alarmTypeKey, update->m_valueString.c_str(), ackState, update->m_entityKey);
                        
                        update->m_user->updateAlarmAckState(ackState);
                    }
				}
				break;

            case AlarmAckUpdate::Unsubscribe:
				{
                    //remove alarm ack user from internal map
                    DataPointAlarmType dpAlarmType;
                    dpAlarmType.entityKey = update->m_entityKey;
                    dpAlarmType.alarmTypeKey = update->m_alarmTypeKey;
                    dpAlarmType.valueString = update->m_valueString;
                    
                    DataPointAlarmTypeMap::iterator alarmEntityIt = m_alarmEntityMap.find(dpAlarmType);
                    if (alarmEntityIt != m_alarmEntityMap.end())
                    {
                        m_alarmEntityMap.erase(alarmEntityIt);
                        // remove the related item of alarm id map
                        for (AlarmIdMap::iterator alarmIdIt = m_alarmIdMap.begin();
                            alarmIdIt != m_alarmIdMap.end(); ++ alarmIdIt)
                        {
                            if (alarmIdIt->second == update->m_user)
                            {
                                m_alarmIdMap.erase(alarmIdIt);
                                break;
                            }
                        }
						
						EntityCurrentAlarmIdMap::iterator it = m_currentAlarmIdMap.find(update->m_entityKey);
						if (m_currentAlarmIdMap.end() != it)
						{
							m_currentAlarmIdMap.erase(it);
						}
                    }
                    else
                    {
                        LOG_GENERIC(SourceInfo, DebugUtil::DebugWarn, "Try to remove non-existed subscription for entity [%u] alarm type [%u] with alarm value [%s]",
                            update->m_entityKey, update->m_alarmTypeKey, update->m_valueString.c_str());
                    }
                }
				break;

            case AlarmAckUpdate::Update:
                {
                    // first search the alarm id map
                    AlarmIdMap::iterator alarmIdIt = m_alarmIdMap.find(update->m_alarmId);
                    if (alarmIdIt != m_alarmIdMap.end())
                    {
                        LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Update alarm type [%u] with alarm id [%s] to AckState [%u] for entity [%u]",
                            update->m_alarmTypeKey, update->m_alarmId.c_str(), update->m_ackState, update->m_entityKey);
                        
						bool isCurrentAlarmId = false;
						EntityCurrentAlarmIdMap::iterator it = m_currentAlarmIdMap.find(update->m_entityKey);
						if (m_currentAlarmIdMap.end() != it)
						{
							isCurrentAlarmId = (it->second.first == update->m_alarmId);
							// current alarm id or another alarmDetail user;
							if (isCurrentAlarmId || it->second.second != alarmIdIt->second)
							{
								alarmIdIt->second->updateAlarmAckState(update->m_ackState);
							}
						}
						else
						{
							LOG_GENERIC(SourceInfo, DebugUtil::DebugError, "Current AlarmId do't exist, this update is too old.");
						}

                        // if the alarm is already acknowledged & closed, remove it from alarm id map.
                        if (update->m_ackState != ScadaAlarmNack && update->m_ackState != ScadaAlarmAck)
                        {
                            m_alarmIdMap.erase(alarmIdIt);
							if (isCurrentAlarmId)
							{
								m_currentAlarmIdMap.erase(it);
							}
                        }
                    }
                    else
                    {
                        // search the related alarm entity and alarm type, call its callback function
                        DataPointAlarmType dpAlarmType;
                        dpAlarmType.entityKey = update->m_entityKey;
                        dpAlarmType.alarmTypeKey = update->m_alarmTypeKey;
                        dpAlarmType.valueString = update->m_valueString;

                        DataPointAlarmTypeMap::iterator alarmEntityIt = m_alarmEntityMap.find(dpAlarmType);
                        if (alarmEntityIt != m_alarmEntityMap.end())
                        {
                            LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Update alarm type [%u] with alarm value [%s] to AckState [%u] for entity [%u]",
                                update->m_alarmTypeKey, update->m_valueString.c_str(), update->m_ackState, update->m_entityKey);
                        
                            alarmEntityIt->second->updateAlarmAckState(update->m_ackState);

                            // if the alarm is not acknowledged or not closed, add it to alarm id map.
                            if (update->m_ackState == ScadaAlarmNack || update->m_ackState == ScadaAlarmAck)
                            {
                                m_alarmIdMap[update->m_alarmId] = alarmEntityIt->second;
								
								// set current alarm id and ack user.
								m_currentAlarmIdMap[update->m_entityKey] = AlarmIDAndUser(update->m_alarmId, alarmEntityIt->second);
                            }
                        }
                    }
                }
				break;
			}
		}
		catch( const TA_Base_Core::TransactiveException & te )
		{
			LOG_EXCEPTION_CATCH( SourceInfo, "TransactiveException", te.what() );
		}
        catch( const CORBA::Exception& )
        {
            LOG_EXCEPTION_CATCH ( SourceInfo, "CORBA::Exception", "Corba exception caught during processing AlarmUpdate." );
        }
		catch(...) 
		{
			LOG_EXCEPTION_CATCH(SourceInfo,"UnknownException", "Unknown exception caught during processing AlarmUpdate.");
		}
				
        LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Finished to process update [%u] for entity [%u]",
            update->m_updateType, update->m_entityKey);
	}

	void AlarmAckStateProcessor::loadAllAlarms( unsigned long alarmEntityLocationKey )
	{
        TA_THREADGUARD( m_AlarmsMapLock );
		m_nLocationKey = alarmEntityLocationKey;
		if (m_bLoadAlarms == false)
		{
			m_bLoadAlarmsError = false;
			//first clear the map
			for( EntityToAlarmMap::iterator p = m_entityToAlarmMap.begin(); p != m_entityToAlarmMap.end(); p++ )
			{
				if( p->second != NULL )
				{
					delete p->second;
					p->second = NULL;
				}
			}
			m_entityToAlarmMap.clear();

			//get all of the alarms from the related alarmagent.
			TA_Base_Core::AlarmSequence* alarmList = NULL;
			try
			{
				alarmList = TA_Base_Core::AlarmHelperManager::getInstance().getAlarmHelper().getActiveAlarms(alarmEntityLocationKey);
				LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "alarmList length is: %d", alarmList->length());
			}


			catch( const TA_Base_Core::TransactiveException & te )
			{
				LOG_EXCEPTION_CATCH( SourceInfo, "TransactiveException", te.what() );
				m_bLoadAlarmsError = true;
			}
			catch ( const TA_Base_Core::OperationModeException & ope)
			{
				LOG_EXCEPTION_CATCH(SourceInfo, "TA_Base_Core::OperationModeException", "Caught Operation Mode exception" );
				m_bLoadAlarmsError = true;
			}
			catch ( const CORBA::Exception & ex )
			{
				LOG_EXCEPTION_CATCH ( SourceInfo, "CORBA::Exception", ( TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ex) ).c_str() );
				m_bLoadAlarmsError = true;
			}
			catch(...)
			{
				LOG_EXCEPTION_CATCH( SourceInfo, "Unknown Exception", 
					"calling getAlarms." );
				m_bLoadAlarmsError = true;
			}

			if (alarmList != NULL && !m_bLoadAlarmsError)
			{
				for (unsigned int iLoop = 0; iLoop < alarmList->length(); iLoop++)
				{
					TA_Base_Core::AlarmDetailCorbaDef * alarmDetail = new TA_Base_Core::AlarmDetailCorbaDef();
					*alarmDetail = 	(*alarmList)[iLoop];

					m_entityToAlarmMap.insert(std::pair<unsigned long, TA_Base_Core::AlarmDetailCorbaDef*>(alarmDetail->assocEntityKey, alarmDetail));
				}

				delete alarmList;
				m_bLoadAlarms = true;
			}

		}
		else
		{
			LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Have done the batch alarms loading, no need to do again");
		}

	}

	TA_Base_Core::AlarmDetailCorbaDef* AlarmAckStateProcessor::getActiveAlarmForEntityOfType(unsigned long p_alarmTypeKey, unsigned long p_entity )
	{
        FUNCTION_ENTRY( "getActiveAlarmForEntityOfType" );
		
        TA_THREADGUARD(m_AlarmsMapLock);
		m_bGotAlarmDetail = true;
		EntityToAlarmMap::const_iterator p = m_entityToAlarmMap.begin();
		
		TA_Base_Core::AlarmDetailCorbaDef* alarm = new TA_Base_Core::AlarmDetailCorbaDef();
		bool found = false;
		
		p = m_entityToAlarmMap.find(p_entity);
		if (p == m_entityToAlarmMap.end())
		{
			delete alarm;
            alarm = NULL;

			m_bGotAlarmDetail = false;
			LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug,
				"No alarm found for Type %u, Entity key %d", 
				p_alarmTypeKey,
				p_entity);

			FUNCTION_EXIT;
			return NULL;
		}

		unsigned long nCount = m_entityToAlarmMap.count(p_entity);
		for (unsigned long i = 0; i < nCount; i++)
		{
			TA_ASSERT((p->second != NULL), "Alarm cannot be NULL");
			TA_ASSERT((p->second->messageTypeKey != 0), "Message type key cannot be 0");
			
			std::string alarmAckedBy(p->second->alarmAcknowledgedBy.in());
            if ( (p->second->state == TA_Base_Core::AlarmOpen || true == alarmAckedBy.empty()) && p->second->messageTypeKey ==p_alarmTypeKey )
			{
				const TA_Base_Core::AlarmDetailCorbaDef* openAlarm = p->second;
				*alarm = *openAlarm;
				found = true;
				break;
			}
			p++;			
		}
		
		if (found == true)
		{
			LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug,
				"Returning alarm with ID %s, Type %u, Entity key %d", alarm->alarmID.in(),
				alarm->messageTypeKey,
				alarm->assocEntityKey);
			FUNCTION_EXIT;
			return alarm;
		}
		else
		{
			// delete the alarm
			delete alarm;
			alarm = NULL;
			
			m_bGotAlarmDetail = false;
			FUNCTION_EXIT;
			return NULL;
		}
	}

}
