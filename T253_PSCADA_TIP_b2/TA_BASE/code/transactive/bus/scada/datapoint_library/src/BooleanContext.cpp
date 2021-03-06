/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:		$File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/bus/scada/datapoint_library/src/BooleanContext.cpp $
  * @author:	HoaVu
  * @version:	$Revision: #1 $
  *
  * Last modification:	$DateTime: 2017/10/31 16:21:54 $
  * Last modified by:	$Author: CM $
  *
  * Description:
  *
  *	Boolean Context...Required by the Mathematical_Evaluation library
  *
  */

#include "core/utilities/src/DebugUtil.h"
#include "bus/scada/datapoint_library/src/BooleanContext.h"


namespace TA_Base_Bus
{

	BooleanContext::BooleanContext()
	:
	CommonContext()
	{

	}


	BooleanContext::BooleanContext ( IExpressionNodeNotification * userOfExpression )
	:
	CommonContext ( userOfExpression )
	{

	}


	BooleanContext::~BooleanContext()
	{

	}


	bool BooleanContext::getValue ( const std::string & variableName ) const
	{
        bool result = const_cast< BooleanContext * >(this)->getBooleanValue ( variableName );

        LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "getValue(%s) = %s", variableName.c_str(), result ? "true" : "false" );

		return result;
	}

}

