/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/pa/PAAgent/src/ForcedDataPointSynchroniser.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */

#if !defined(ForcedDataPointSynchroniser_B323CC80_49BA_4d42_98A5_8CE9884F7924__INCLUDED_)
#define ForcedDataPointSynchroniser_B323CC80_49BA_4d42_98A5_8CE9884F7924__INCLUDED_


#include <string>
#include "core/threads/src/Thread.h"
#include "core/synchronisation/src/NonReEntrantThreadLockable.h"

namespace TA_Base_Core
{
	class CommsMessageSender;
};

namespace TA_Base_Bus
{
	class AgentStateUpdateQueueSingletonManager;
};

class CachedConfig;

namespace TA_IRS_App
{

class ForcedDataPointSynchroniser : public TA_Base_Core::Thread
{

public:
    ForcedDataPointSynchroniser();
    virtual ~ForcedDataPointSynchroniser();
  
    virtual void run();
    virtual void terminate();

    void setControlMode(bool inControl);

protected:

    void processDataPointStateManuallyUpdate();

    
    volatile bool                           m_isRunning;
    TA_Base_Core::NonReEntrantThreadLockable     m_lock;

	TA_Base_Bus::AgentStateUpdateQueueSingletonManager *	m_agentStateUpdateQ;
	TA_Base_Core::StateUpdateMessageSender*	    m_stateUpdateMessageSender;
    CachedConfig*                           m_cachedConfigInstance;
    bool                                        m_agentSetControl;


private:
    ForcedDataPointSynchroniser( const ForcedDataPointSynchroniser& theForcedDataPointSynchroniser);



};

} // namespace TA_IRS_App

#endif // !defined(ForcedDataPointSynchroniser_B323CC80_49BA_4d42_98A5_8CE9884F7924__INCLUDED_)

