/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/cctv/video_display_manager/src/VideoInput.cpp $
  * @author:  Adam Radics
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
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

