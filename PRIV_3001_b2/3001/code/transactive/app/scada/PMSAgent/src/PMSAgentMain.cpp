/**
  * The source code in this file is the property of Ripple Systems and is not for redistribution in
  * any form.
  *
  * Source:		$File: //depot/PRIV_3001/3001/transactive/app/scada/PMSAgent/src/PMSAgentMain.cpp $
  * @author:	Raymond Pau
  * @version:	$Revision: #1 $
  *
  * Last modification:	$DateTime: 2018/03/14 13:51:20 $
  * Last modified by:	$Author: lim.cy $
  *
  * Description:
  *
  *	Main program for PMSAgent process
  *
  */

#include "app/scada/PMSAgent/src/PMSAgent.h"

#include "core/utilities/src/DebugUtil.h"
#include "core/exceptions/src/GenericAgentException.h"

int main( int argc, char * argv[] )
{
	try
	{
		TA_IRS_App::PMSAgent pmsAgent( argc, argv );
		pmsAgent.startPMSAgent();
	}
    catch( const TA_Base_Core::GenericAgentException& gae )
    {
        LOG_EXCEPTION_CATCH( SourceInfo, "GenericAgentException", gae.what());
    }
	catch( const TA_Base_Core::TransactiveException & te)
	{
		LOG_EXCEPTION_CATCH( SourceInfo, "TransactiveException", te.what() );
	}
	catch( std::exception & e )
	{
		LOG_EXCEPTION_CATCH( SourceInfo, "std::exception", e.what() );
	}
	catch( ... )
	{
		LOG_EXCEPTION_CATCH( SourceInfo, "Unknown Exception", "Caught unknown exception" );
	}
		
	return 1;
}
