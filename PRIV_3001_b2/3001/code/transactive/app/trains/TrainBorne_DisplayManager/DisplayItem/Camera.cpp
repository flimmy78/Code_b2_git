/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP/3001/transactive/app/cctv/video_display_manager/src/Camera.cpp $
  * @author:  Adam Radics
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2009/12/29 14:12:57 $
  * Last modified by:  $Author: grace.koh $
  *
  *
  * This is used to locally store state and association information
  * so it can easily be retrieved for displaying in the GUI.
  */


#include "Camera.h"
#include "core/synchronisation/src/ThreadGuard.h"
#include "core/utilities/src/FunctionEntry.h"

namespace TA_IRS_App
{

    Camera::Camera( unsigned long entityKey,
                    const std::string& name,
                    const std::string& description,
                    const std::string& address,
                    const std::string& group )
      : VideoInput(entityKey, name, description, group)
    {
        FUNCTION_ENTRY( "Camera" );

        m_address = address;

        FUNCTION_EXIT;
    }


    std::string Camera::getAddress()
    {
        FUNCTION_ENTRY( "getAddress" );

        TA_Base_Core::ThreadGuard guard( m_lock );

        FUNCTION_EXIT;
        return m_address;
    }


}

