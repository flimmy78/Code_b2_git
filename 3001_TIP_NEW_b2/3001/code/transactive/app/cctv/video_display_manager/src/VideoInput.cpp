/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/cctv/video_display_manager/src/VideoInput.cpp $
  * @author:  Adam Radics
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  *
  * This is used to locally store state and association information
  * so it can easily be retrieved for displaying in the GUI.
  */


#include "VideoInput.h"
#include "core/utilities/src/FunctionEntry.h"

namespace TA_IRS_App
{

    VideoInput::VideoInput( unsigned long entityKey,
                            const std::string& name,
                            const std::string& description,
                            const std::string& group )
      : DisplayItem(entityKey, name, description),
        m_group(group)
    {
        FUNCTION_ENTRY( "VideoInput" );
        FUNCTION_EXIT;
    }


    std::string VideoInput::getGroup()
    {
        FUNCTION_ENTRY( "getGroup" );

        // no setter - no need to lock
        FUNCTION_EXIT;
        return m_group;
    }


} // TA_IRS_App

