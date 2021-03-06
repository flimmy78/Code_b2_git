#if !defined(StateUpdateBroadcaster_F136C5A2_7FC6_401f_98AE_919F73EE9F20__INCLUDED_)
#define StateUpdateBroadcaster_F136C5A2_7FC6_401f_98AE_919F73EE9F20__INCLUDED_

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  *
  * Source:    $File: //depot/WXL1_TIP/3002/transactive/app/cctv/video_switch_agent/src/StateUpdateBroadcaster.h $
  * @author:   Katherine Thomson
  * @version:  $Revision: #4 $
  *
  * Last modification: $DateTime: 2013/07/30 17:42:30 $
  * Last modified by:  $Author: huang.wenbo $
  *
  * Broadcasts messages to the GUIs and any other Video Switch Agents
  * notifying them of state updates.
  * This class is a singleton.
  */

#ifdef _MSC_VER
#pragma warning( disable : 4786 )
#endif // _MSC_VER

#include <memory>
#include <string>
#include "core/message/src/MessagePublicationManager.h"
#include "app/cctv/video_switch_agent/src/SwitchManager.h"
#include <boost/noncopyable.hpp>
#include <ace/Singleton.h>
#include <ace/Recursive_Thread_Mutex.h>


// Forward declarations.

namespace TA_Base_Core
{
    class CommsMessageSender;
    class StateUpdateMessageSender;
}

namespace TA_IRS_App
{
    class StateUpdateBroadcaster : boost::noncopyable
    {
		friend class ACE_Singleton<StateUpdateBroadcaster, ACE_Recursive_Thread_Mutex>;
        public:
            /**
              * getInstance
              *
              * Gets the one and only StateUpdateBroadcaster.
              *
              * @return     StateUpdateBroadcaster&
              *             The only StateUpdateBroadcaster.
              */

            static StateUpdateBroadcaster& getInstance();

            /**
              * StateUpdateBroadcaster
              *
              * Standard destructor.
              */


            ///////////////////////////////////////////////////////////////////////
            //
            // Request Methods
            //
            ///////////////////////////////////////////////////////////////////////

            /**
              * requestAgentState
              *
              * Sends a state update request message to get the Control mode agent
              * to send all it's state information.
              * There is no notification if the sending fails, except for a log.
              */

            void requestAgentState();

            ///////////////////////////////////////////////////////////////////////
            //
            // Notification Methods
            //
            ///////////////////////////////////////////////////////////////////////

            /**
              * notifyAgentState
              *
              * Sends a state update message of the agent's current state information.
              * This is called on startup of the agent and when the agent receives a request
              * for it's state (i.e. when a Monitor mode Video Switch Agent starts up).
              * There is no notification if the sending fails, except for a log.
              */

            void notifyAgentState();

            /**
              * notifyCameraStateUpdate
              *
              * Sends a comms and a state update message stating that the state of a Camera
              * has changed.  The whole state of the Camera is sent in the messages, not just
              * the updated parameter.  This is a safeguard for the receiving agents/GUIs in
              * case they miss an update.  There is no notification if the sending fails,
              * except for a log because there is nothing we can do about it.
              *
              * @param      unsigned long cameraKey
              *             The database (entity) key of the Camera.
              * @param      bool sendStateUpdateMessageOnly
              *             True if only a StateUpdate message should be sent.
              */

            void notifyCameraStateUpdate(unsigned long cameraKey,
                                         bool sendStateUpdateMessageOnly = false);

            /**
              * notifyVideoInputStateUpdate
              *
              * Sends a comms and a state update message stating that the state of a VideoInput
              * has changed.  The whole state of the VideoInput is sent in the messages, not just
              * the updated parameter.  This is a safeguard for the receiving agents/GUIs in
              * case they miss an update.  There is no notification if the sending fails,
              * except for a log because there is nothing we can do about it.
              *
              * @param      unsigned long videoInputKey
              *             The database (entity) key of the VideoInput.
              * @param      bool sendStateUpdateMessageOnly
              *             True if only a StateUpdate message should be sent.
              */

            void notifyVideoInputStateUpdate(unsigned long videoInputKey,
                                             bool sendStateUpdateMessageOnly = false);

            /**
             * notifyBVSStateUpdate
             *
             * Sends a comms and a state update message stating that the state of a BVSStage
             * has changed.  The whole state of the BVSStage is sent in the messages, not just
             * the updated parameter.  This is a safeguard for the receiving agents/GUIs in
             * case they miss an update.  There is no notification if the sending fails,
             * except for a log because there is nothing we can do about it.
             *
             * @param      unsigned long bvsKey
             *             The database (entity) key of the bvsStage.
             * @param      bool sendStateUpdateMessageOnly
             *             True if only a StateUpdate message should be sent.
             */

            //  void notifyBVSStateUpdate( unsigned long bvsKey,
            //      bool sendStateUpdateMessageOnly = false );

            /**
             * notifyVideoOutputStateUpdate
             *
             * Sends a comms and a state update message stating that the state of a VideoOutput
             * has changed.  The whole state of the VideoOutput is sent in the messages, not just
             * the updated parameter.  This is a safeguard for the receiving agents/GUIs in
             * case they miss an update.  There is no notification if the sending fails,
             * except for a log because there is nothing we can do about it.
             *
             * @param      unsigned long videoOutputKey
             *             The database (entity) key of the VideoOutput.
             * @param      bool sendStateUpdateMessageOnly
             *             True if only a StateUpdate message should be sent.
             */

            void notifyVideoOutputStateUpdate(unsigned long videoOutputKey,
                                              bool sendStateUpdateMessageOnly = false);


            /**
              * notifyQuadStateUpdate
              *
              * Sends a comms and a state update message stating that the state of a Quad
              * has changed.  The whole state of the Quad is sent in the messages, not just
              * the updated parameter.  This is a safeguard for the receiving agents/GUIs in
              * case they miss an update.  There is no notification if the sending fails,
              * except for a log because there is nothing we can do about it.
              *
              * @param      unsigned long quadKey
              *             The database (entity) key of the Quad.
              * @param      bool sendStateUpdateMessageOnly
              *             True if only a StateUpdate message should be sent.
              */

            // void notifyQuadStateUpdate( unsigned long quadKey,
            //     bool sendStateUpdateMessageOnly = false );


            /**
              * notifySequenceStateUpdate
              *
              * Sends a comms and a state update message stating that the state of a sequence
              * has changed.  The whole state of the Sequence is sent in the messages, not just
              * the updated parameter.  This is a safeguard for the receiving agents/GUIs in
              * case they miss an update.  There is no notification if the sending fails,
              * except for a log because there is nothing we can do about it.
              *
              * @param      unsigned long sequenceKey
              *             The database (entity) key of the Sequence.
              * @param      unsigned long videoOutputKey
              *             The database (entity) key of the VideoOutput that the sequence
              *             instance is running on.
              * @param      bool sendStateUpdateMessageOnly
              *             True if only a StateUpdate message should be sent.
              */

            void notifySequenceStateUpdate(unsigned long sequenceKey,
                                           unsigned long videoOutputKey,
                                           bool sendStateUpdateMessageOnly = false);


            /**
              * notifySequenceConfigUpdate
              *
              * Sends a comms and a state update message stating that the Sequence Config of a sequence
              * has changed.  The whole SequenceConfig of the Sequence is sent in the messages, not just
              * the updated parameter.  This is a safeguard for the receiving agents/GUIs in
              * case they miss an update.  There is no notification if the sending fails,
              * except for a log because there is nothing we can do about it.
              *
              * @param      unsigned long sequenceKey
              *             The database (entity) key of the Sequence.
              * @param      bool sendStateUpdateMessageOnly
              *             True if only a StateUpdate message should be sent.
              */

            void notifySequenceConfigUpdate(unsigned long sequenceKey,
                                            bool sendStateUpdateMessageOnly = false);
            /**
              * notifySequenceConfigUpdate
              *
              * Same as above, but with different input parameters
              * sends a comms and a state update message stating that the Sequence Config of a sequence
              * has changed.  The whole SequenceConfig of the Sequence is sent in the messages, not just
              * the updated parameter.  This is a safeguard for the receiving agents/GUIs in
              * case they miss an update.  There is no notification if the sending fails,
              * except for a log because there is nothing we can do about it.
              *
              * @param      The Sequence itself
              * @param      bool sendStateUpdateMessageOnly
              *             True if only a StateUpdate message should be sent.
              */
            void notifySequenceConfigUpdate(Sequence& sequence,
                                            bool sendStateUpdateMessageOnly = false);

        private:

            /**
              * StateUpdateBroadcaster
              *
              * Standard constructor that gets the message senders.  This class
              * is a singleton, so use getInstance() to get the one and only
              * instance of this class.
              */

            StateUpdateBroadcaster();
            virtual ~StateUpdateBroadcaster();
            //
            // The message senders.  These are std::auto_ptrs so they will automatically be cleaned up.
            //

            std::auto_ptr< TA_Base_Core::CommsMessageSender > m_commsSender;
            std::auto_ptr< TA_Base_Core::StateUpdateMessageSender > m_stateSender;

    }; // StateUpdateBroadcaster

} // TA_IRS_App

#endif // !defined(StateUpdateBroadcaster_F136C5A2_7FC6_401f_98AE_919F73EE9F20__INCLUDED_)