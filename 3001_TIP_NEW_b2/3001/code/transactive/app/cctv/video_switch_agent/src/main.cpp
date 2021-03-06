/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  *
  * Source:    $File: //depot/3001_TIP_NEW/3001/transactive/app/cctv/video_switch_agent/src/main.cpp $
  * @author:   Katherine Thomson
  * @version:  $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Creates the VideoSwitchAgent object and sets it running.
  */

#ifdef _MSC_VER
#pragma warning( disable : 4786 )
#endif // _MSC_VER

#include <memory>

#include "app/cctv/video_switch_agent/src/VideoSwitchAgent.h"

#include "core/exceptions/src/GenericAgentException.h"
#include "core/exceptions/src/VideoSwitchAgentInternalException.h"
#include "core/utilities/src/DebugUtil.h"

int main( int argc, char* argv[] )
{
    try
    {
        TA_IRS_App::VideoSwitchAgent agent( argc, argv );
        agent.agentRun();
    }
    catch( const TA_Base_Core::VideoSwitchAgentInternalException& e )
    {
        LOG_EXCEPTION_CATCH( SourceInfo, "VideoSwitchAgentInternalException", e.what());
    }
    catch( const TA_Base_Core::GenericAgentException& e )
    {
        LOG_EXCEPTION_CATCH( SourceInfo, "GenericAgentException", e.what());
    }
    catch( const TA_Base_Core::TransactiveException& e )
    {
        LOG_EXCEPTION_CATCH( SourceInfo, "TransactiveException", e.what());
    }
    catch( ... )
    {
        LOG_EXCEPTION_CATCH( SourceInfo, "UnknownException", 
            "An unknown non-Transactive exception has been caught." );
    }

    return 0;
}
