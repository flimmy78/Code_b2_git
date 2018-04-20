#if !defined(IPDCamera_BDE6E42B_B294_4e78_BE77_3ECED963A0C1__INCLUDED_)
#define IPDCamera_BDE6E42B_B294_4e78_BE77_3ECED963A0C1__INCLUDED_

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  *
  * Source:    $File: //depot/4669_T01271350/4669/transactive/app/cctv/video_switch_agent/protocols/src/IPDCamera.h $
  * @author:   Katherine Thomson
  * @version:  $Revision: #2 $
  *
  * Last modification: $DateTime: 2008/12/17 14:59:54 $
  * Last modified by:  $Author: builder $
  *
  * Handles all the protocol dependent common functions of Cameras.
  * This interface is used by the Camera class.
  */

#include <string>

#include "bus/cctv/video_switch_agent/IDL/src/CameraCorbaDef.h"

namespace TA_IRS_App
{
    class IPDCamera
	{
	public:

		/**
		  * ~IPDCamera
		  *
		  * Standard destructor.
		  */

        virtual ~IPDCamera() {};
                  
        ///////////////////////////////////////////////////////////////////////
        //
        // State Update Methods
        //
        ///////////////////////////////////////////////////////////////////////

        /**
          * updateState
          *
          * Updates the state of the Camera.  
          *
          * This is called when a VideoSwitchAgentStateUpdate message is received, 
          * so the agent should be in Monitor mode. Because this method is called 
          * when a message is received, there is not much we can do if the method 
          * fails, except log. 
          *
          * @param      const TA_Base_Bus::CameraCorbaDef::CameraState& state
          *             The new state of the Camera.
          */

        virtual void updateState( const TA_Base_Bus::CameraCorbaDef::CameraState& state ) = 0;
		
        ///////////////////////////////////////////////////////////////////////
		//
		// IPDCamera Methods
		//
		///////////////////////////////////////////////////////////////////////

        /**
          * isInAlarmState
          *
          * Identifies if the Camera is in an alarm state.
          * i.e. if the video signal from the Camera has been lost.
          *
          * @return     bool
          *             True if the Camera is in an alarm state.
          *             False otherwise.
          */

        virtual bool isInAlarmState() = 0;
	};

} // namespace TA_IRS_App

#endif // !defined(IPDCamera_BDE6E42B_B294_4e78_BE77_3ECED963A0C1__INCLUDED_)