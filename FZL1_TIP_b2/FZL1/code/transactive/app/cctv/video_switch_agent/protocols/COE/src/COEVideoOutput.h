#if !defined(COEVideoOutput_6D856C3B_635C_4e91_8C91_072E38E337FD__INCLUDED_)
#define COEVideoOutput_6D856C3B_635C_4e91_8C91_072E38E337FD__INCLUDED_

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  *
  * Source:    $File: //depot/WXL1_TIP/3002/transactive/app/cctv/video_switch_agent/protocols/COE/src/COEVideoOutput.h $
  * @author:   Rob Young
  * @version:  $Revision: #5 $
  *
  * Last modification: $DateTime: 2013/08/30 15:01:40 $
  * Last modified by:  $Author: huang.wenbo $
  *
  * Handles the protocol dependent sections of the operations for a VideoOutput
  * using the COE protocol.
  * Inherits from IPDVideoOutput. Before the methods
  * in this interface are called, the user privileges have been checked and
  * that the protocol supports the required features.
  */

#ifdef _MSC_VER
#pragma warning( disable : 4786 )
#endif // _MSC_VER

#include <boost/noncopyable.hpp>
#include "app/cctv/video_switch_agent/protocols/src/IPDVideoOutput.h"
#include "app/cctv/video_switch_agent/protocols/COE/src/COEHelper.h"
#include "core/data_access_interface/entity_access/src/VideoOutput.h"

// Forward declarations

namespace TA_Base_Core
{
    class VideoOutput;
}

namespace TA_IRS_App
{
    class COEVideoOutput : public IPDVideoOutput, boost::noncopyable
    {
        public:
            /**
              * COEVideoOutput
              *
              * Standard constructor.
              *
              * @param      TA_Base_Core::VideoOutput& videoOutputData
              *             The database object relating to this VideoOutput.
              *             This object is owned by GenericAgent, so it should not be deleted.
              */

            COEVideoOutput(TA_Base_Core::VideoOutputPtr videoOutputData);

            /**
              * ~COEVideoOutput
              *
              * Standard destructor.
              */

            virtual ~COEVideoOutput() {};

            virtual unsigned long getKey();

            /**
              * getAddress
              *
              * Gets the address of the VideoOutput.
              *
              * @return     std::string
              *             The address of the VideoOutput.
              *
              * @exception  VideoSwitchAgentException
              *             Thrown if:
              *             1. The database cannot be accessed.
              *             2. The data cannot be retrieved.
              *             3. The retrieved data is invalid.
              *             4. The agent is in Monitor mode.
              */

            std::string getAddress();

            ///////////////////////////////////////////////////////////////////////
            //
            // State Update Methods
            //
            ///////////////////////////////////////////////////////////////////////

            /**
              * notifyInputSwitchedToOutput
              *
              * This is called when data is received from the hardware saying that a
              * switch has occured, so the agent should be in Control mode.
              * Sends a message to notify agent clients that an input has
              * been switched to this output.
              *
              * @param      unsigned long videoInputKey
              *             The database (entity) key of the input that has
              *             been switched to this output.
              */

            void notifyInputSwitchedToOutput(unsigned long videoInputKey);
            /**
              * updateState
              *
              * Updates the state of the VideoOutput.
              *
              * This is called when a VideoSwitchAgentStateUpdate message is received,
              * so the agent should be in Monitor mode. Because this method is called
              * when a message is received, there is not much we can do if the method
              * fails, except log.
              *
              * @param      const TA_Base_Bus::VideoOutputCorbaDef::VideoOutputState& state
              *             The new state of the VideoOutput.
              */

            virtual void updateState(const TA_Base_Bus::VideoOutputCorbaDef::VideoOutputState& state);

            ///////////////////////////////////////////////////////////////////////
            //
            // IPDVideoOutput Methods
            //
            ///////////////////////////////////////////////////////////////////////

            /**
              * getCurrentVideoInputKey
              *
              * Get the database (entity) key of the VideoInput currently switched to this VideoOutput.
              * 0 indicates no VideoInput is siwtched to this VideoOutput.
              *
              * @return     unsigned long
              *             The database (entity) key of the VideoInput for this VideoOutput device or
              *             0 if there is no associated input.
              *
              * @exception  VideoSwitchAgentException
              *             Thrown if there is a communications failure with the hardware.
              */

            virtual unsigned long getCurrentVideoInputKey();

            /**
              * getVideoOutputState
              *
              * returns the entire state of this video output
              *
              * @return     VideoOutputState objhect asscociated with this videoOutput
              *
              * @exception  VideoSwitchAgentException
              *             Thrown if there is a communications failure with the hardware.
              */

            virtual TA_Base_Bus::VideoOutputCorbaDef::VideoOutputState* getVideoOutputState();

            /**
              * requestSwitchOfInput
              *
              * Requests that the hardware switches the named VideoInput to this VideoOutput.
              *
              * @param      unsigned long videoInputEntityKey
              *             The entity key of the VideoInput to switch.
              * @param      bool isDemand = false
              *             If false => If the VideoInput is locked (hardware locking), the
              *                         switch will not occur. Also known as a polite request.
              *             If true  => The switch will occur even if the hardware is locked.
              *
              * @exception  VideoSwitchAgentException
              *             Thrown if:
              *             1. A polite request was made and the VideoInput is switch (hardware) locked.
              *             2. The VideoInput key is not recognised.
              *             3. There is a communications failure with the hardware.
              */

            virtual void requestSwitchOfInput(unsigned long videoInputEntityKey,
                                              bool isDemand);
            virtual void assignQuad(unsigned long cameraW, unsigned long cameraX, unsigned long cameraY, unsigned long cameraZ,
                                    bool isDemand);

            virtual void requestRecordingPlayBack(::CORBA::ULong cameraKey, const ::TA_Base_Bus::VideoOutputCorbaDef::Time& startTime, const ::TA_Base_Bus::VideoOutputCorbaDef::Time& endTime);
            virtual void playBackCtrl(TA_Base_Bus::VideoOutputCorbaDef::PlayBackCtrlCmd cmd);
        private:

            //
            // The configuration data object for this VideoOutput.
            //

            TA_Base_Core::VideoOutputPtr m_videoOutputData;
            //
            // The database (entity) key of the current VideoInput.
            //
            unsigned long m_currentVideoInputKey;
    }; // COEVideoOutput

} // TA_IRS_App

#endif // !defined(COEVideoOutput_6D856C3B_635C_4e91_8C91_072E38E337FD__INCLUDED_)
