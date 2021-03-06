/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/ecs/ECSAgent/src/MasterModeExecutionWorker.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */
///////////////////////////////////////////////////////////
//
//  MasterModeExecutionWorker.h
//  Implementation of the Class MasterModeExecutionWorker
//  Generated by Enterprise Architect
//  Created on:      25-Sep-2003 18:53:34
//  Original author: 
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////


#if !defined(MasterModeExecutionWorker_B323CC80_49BA_4d42_98A5_8CE9884F7924__INCLUDED_)
#define MasterModeExecutionWorker_B323CC80_49BA_4d42_98A5_8CE9884F7924__INCLUDED_


#include <string>
#include <map>

#include "app/ecs/ECSAgent/src/ItaEcsCachedMaps.h"
#include "app/ecs/ECSAgent/src/AbstractFailoverable.h"
#include "app/ecs/ECSAgent/src/MasterModeLocksManager.h"

#include "bus/ecs/ecs_agent/IDL/src/IStationEcsAgentCorbaDef.h"

#include "core/naming/src/NamedObject.h"
#include "core/threads/src/Thread.h"
#include "core/message/src/SpecialisedMessageSubscriber.h"
#include "core/message/IDL/src/CommsMessageCorbaDef.h"
#include "core/timers/src/ITimeoutCallback.h"
#include "core/timers/src/SingletonTimerUtil.h"


class ItaEcsCachedConfig;
class ItaEcsAuditing;
class ItaEcsAlarms;
class ItaEcsAgentCompleteState;
class ItaEcsDatapoints;
class ImmmArrowAccess;

typedef TA_Base_Core::NamedObject<TA_IRS_Bus::IStationEcsAgentCorbaDef,
	   					     TA_IRS_Bus::IStationEcsAgentCorbaDef_ptr, 
	           			     TA_IRS_Bus::IStationEcsAgentCorbaDef_var> StationEcsAgentNamedObject;

//TD4303, use timer driven thread rather than to sleep
class MasterModeExecutionWorker : public TA_Base_Core::Thread,
                                  public ItaEcsCachedMapsObserver,
                                  public virtual AbstractFailoverable,
                                  public virtual TA_Base_Core::SpecialisedMessageSubscriber<TA_Base_Core::CommsMessageCorbaDef>,
                                  public TA_Base_Core::ITimeoutCallback
  
{

public:
    MasterModeExecutionWorker(
        ItaEcsCachedMaps& theMaps,
        ItaEcsCachedConfig& theConfig,
        ItaEcsAuditing& theAuditing,
        ItaEcsAlarms& theAlarms,
        ItaEcsAgentCompleteState& theCompleteState,
		ItaEcsDatapoints&	theDatapoints,
        ImmmArrowAccess& theArrows);

    virtual ~MasterModeExecutionWorker();
  

    // AbstractFailoverable overrides
    virtual void setControl(bool isOnStartup=false);
    virtual void setMonitor(bool isOnStartup=false);

    virtual void run();
    virtual void terminate();
    void execute(long fromMasterMode, long toMasterMode, const std::string& sessionId, const TA_IRS_Bus::EcStationModeRecords& stationModeRecords);
    void abortIfRequired();

    virtual void receiveSpecialisedMessage(const TA_Base_Core::CommsMessageCorbaDef&  message);
    
    //Implement for ITimeoutCallback;
    void timerExpired(long timerId, void* userData);
    
private:

	MasterModeExecutionWorker( const MasterModeExecutionWorker& theMasterModeExecutionWorker);

    void processStationEcsPacket(const TA_IRS_Bus::IStationEcsAgentCorbaDef::EcsStationModeExecutionUpdateData& packet);

    virtual void processItaEcsCachedMapsUpdate(ItaEcsCachedMaps::EItaEcsCachedMapsItemKey key);

    void processReadyState(TA_IRS_Bus::IMasterEcsAgentCorbaDef::EcsMasterModeExecutionUpdateData& modeState);
    void processControlState(TA_IRS_Bus::IMasterEcsAgentCorbaDef::EcsMasterModeExecutionUpdateData& modeState);
    void processInProgressState(TA_IRS_Bus::IMasterEcsAgentCorbaDef::EcsMasterModeExecutionUpdateData& modeState);
    void processCompletedState(TA_IRS_Bus::IMasterEcsAgentCorbaDef::EcsMasterModeExecutionUpdateData& modeState);
	
    void subscribeToStationEcsAgentComms();
	void unsubscribeToStationEcsAgentComms();
	
private:

    typedef std::map<unsigned long, StationEcsAgentNamedObject*>   LocationToNamedObjectMap;

    MasterModeLocksManager                  m_locksManager;

    ItaEcsCachedMaps&                       m_theMaps;
    ItaEcsCachedConfig&                     m_theConfig;
    ItaEcsAuditing&                         m_theAuditing;
    ItaEcsAlarms&                           m_theAlarms;
    ItaEcsAgentCompleteState&               m_theCompleteState;
	ItaEcsDatapoints&						m_theDatapoints;
    ImmmArrowAccess&                        m_theArrows;

    LocationToNamedObjectMap                m_stationAgents;
	TA_IRS_Bus::EcStationModeRecords		m_stationModeRecords;  //TD16709
    
    volatile bool                           m_isRunning;

	time_t                                  m_startTime;

	TA_Base_Core::ReEntrantThreadLockable	m_lockForNamedObjects;
    TA_Base_Core::ReEntrantThreadLockable	m_possibleModeStateModificationLock;
    
    TA_Base_Core::SingletonTimerUtil&		m_timerUtility;
    

};

#endif // !defined(MasterModeExecutionWorker_B323CC80_49BA_4d42_98A5_8CE9884F7924__INCLUDED_)
