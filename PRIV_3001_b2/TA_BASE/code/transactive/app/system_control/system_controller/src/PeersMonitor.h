/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/system_control/system_controller/src/PeersMonitor.h $
  * @author:  Justin Ebedes
  * @version: $Revision: #5 $
  *
  * Last modification: $DateTime: 2018/03/23 17:31:26 $
  * Last modified by:  $Author: Ouyang $
  *
  * This class is used to check if all heartbeats have been
  * received from peer System Controllers. When a heartbeat is
  * received from a System Controller, it is passed to this
  * class which checks to see if it's from a peer and if so
  * timestamps it. If a heartbeat is not received from ANY peer
  * after a certain time, the SystemControllerMonitor class
  * handles it.
  *
  */

#if !defined(PeersMonitor_C80D2DE4_5953_4a2a_9F3F_35D7C4A99736__INCLUDED_)
#define PeersMonitor_C80D2DE4_5953_4a2a_9F3F_35D7C4A99736__INCLUDED_

#include "core/synchronisation/src/NonReEntrantThreadLockable.h"
#include "core/timers/src/MonotonicTimer.h"
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include <map>
#include <sys/timeb.h>

namespace TA_Base_App
{
    class PeersMonitor
    {
    public:

        /**
          * Constructor
          *
          * @param peerHostnames  A vector of hostnames that are the peers
          *                       of this System Controller.
          */
        PeersMonitor(const std::vector<std::string>& peerHostnames, unsigned long heartbeatSendPeriod, unsigned long heartbeatSendNumber);

        /**
          * Destructor
          */
        virtual ~PeersMonitor();

        /**
          * getFailedPeers
          *
          * Checks the timestamps to see if any peers have not sent us
          * a heartbeat within the last time frame.
          *
          * @return A vector of strings containing the hostname(s)
          *         that failed. Usually (hopefully) this will be empty.
          *
          * @param  expectedTime  The time that we expect heartbeats to
          *                       be at least equal to.
          *
          */
        std::vector<std::string> getFailedPeers();

        /**
          * notifyHeartbeat
          *
          * Called to inform this class that a heartbeat has been received
          * from another System Controller.
          *
          * @param host The hostname of the System Controller that
          *             send the heartbeat.
          */
        void notifyHeartbeat(const std::string& host);

    private:

        PeersMonitor(const PeersMonitor& thePeersMonitor);
        PeersMonitor& operator=(const PeersMonitor&);

        /**
          * A map of hostnames to timestamps.
          */
        typedef std::map< std::string, std::pair<TA_Base_Core::MonotonicTimer, timeb> > HeartBeatTimeMap;
        HeartBeatTimeMap m_lastHeartbeatTimeMap;
        TA_Base_Core::NonReEntrantThreadLockable m_lock;

        /**
          * The interval, in seconds, between heartbeats.
          */
        unsigned long m_heartbeatSendPeriod;
        unsigned long m_heartbeatSendNumber;
        std::vector<std::string> m_failedPeers;
    };

    typedef boost::shared_ptr<PeersMonitor> PeersMonitorPtr;
} // namespace TA_Base_App

#endif // !defined(PeersMonitor_C80D2DE4_5953_4a2a_9F3F_35D7C4A99736__INCLUDED_)
