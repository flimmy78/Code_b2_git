/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/pa/PAAgent/src/TrainAgentSubscriber.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  */
#if !defined(TrainAgentSubscriber_3F7C474E_D4B5_4966_A962_1414544E17A6__INCLUDED_)
#define TrainAgentSubscriber_3F7C474E_D4B5_4966_A962_1414544E17A6__INCLUDED_

/**
* Obtains the ATSTrainMessage ptr from the CORBA::Any.
* Converts the Fixed block IDs to ECS Zone IDs.  Only ECS Zones inside the
* station's ECS Zone Decision Scope are mapped.
* Adds the equivalent ATSTrainMessage_var references to the StationDecisionEngine
* and StationDataPointUpdater class maps.  The reference count mechanism is
* apparently thread-safe.
*/

#include "core/synchronisation/src/NonReEntrantThreadLockable.h"
#include "bus/pa/cachedmaps/src/PaTrainDvaMessageCachedMap.h"
#include "bus/trains/TrainCorbaProxy/src/ITrainPaUpdateObserver.h"


namespace TA_IRS_App
{

class AbstractBroadcastCircularList;

class TrainAgentSubscriber : public TA_IRS_Bus::ITrainPaUpdateObserver, 
    public TA_IRS_Bus::PaTrainDvaMessageCachedMap::IGlobalTrainVersionObserver
{

public:
    TrainAgentSubscriber( AbstractBroadcastCircularList& refObject );
    virtual ~TrainAgentSubscriber();

    void subscribe();

    // Client should call this just before destruction so that there is no
    // possibility of a processing of a message after the class is destroyed

    void unsubscribe();

    /**
     * onGlobalTrainVersionChanged
     *
     * Called whenever there is a change in the global train version setting
     */
    virtual void onGlobalTrainVersionChanged();


    /**
     * This will receive a PaAnnouncementUpdate message from the local train agent.
     *
     * @param event    The event to process
     */
    virtual void processPaAnnouncementUpdate( const TA_IRS_Bus::PaTypes::PaAnnouncementUpdate& event );


    /**
     * This will receive a PaUpdateEvent message from the local train agent.
     *
     * @param event    The event to process
     */
    virtual void processPaUpdateEvent( const TA_IRS_Bus::PaTypes::PaUpdateEvent& event );


    /**
     * This will receive a TrainLibraryInfo message from the local train agent.
     *
     * @param event    The event to process
     */
    virtual void processTrainLibraryInfo( const TA_IRS_Bus::PaTypes::TrainLibraryInfo& event );

private:
    TrainAgentSubscriber( const TrainAgentSubscriber& theTrainAgentSubscriber);

    TA_Base_Core::NonReEntrantThreadLockable m_lock;  // Mainly used to syncronise destruction
    AbstractBroadcastCircularList& m_allBroadcasts;
    unsigned long m_iscsLibraryVersion;
};

} // namespace TA_IRS_App

#endif // !defined(TrainAgentSubscriber_3F7C474E_D4B5_4966_A962_1414544E17A6__INCLUDED_)

