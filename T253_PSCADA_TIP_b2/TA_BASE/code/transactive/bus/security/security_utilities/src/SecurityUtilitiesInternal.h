#ifndef SECURITYUTILITIESINTERNAL_H_INCLUDED
#define SECURITYUTILITIESINTERNAL_H_INCLUDED

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/bus/security/security_utilities/src/SecurityUtilitiesInternal.h $
  * @author:  Gregg Kirkpatrick
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2017/10/31 16:21:54 $
  * Last modified by:  $Author: CM $
  *
  * The header file that all local cpp files should include.
  *
  */

#include "SecurityUtilities.h"

// defines
#define SOURCE_INFO      SourceInfo

#define GENERIC_LOG_TYPE          TA_Base_Core::DebugUtil::GenericLog
#define EXCEPTION_CATCH_LOG_TYPE  TA_Base_Core::DebugUtil::ExceptionCatch
#define EXCEPTION_DETAIL_LOG_TYPE TA_Base_Core::DebugUtil::ExceptionDetails
#define FUNCTION_ENTRY_LOG_TYPE   TA_Base_Core::DebugUtil::FunctionEntry
#define FUNCTION_EXIT_LOG_TYPE   TA_Base_Core::DebugUtil::FunctionExit

#define FATAL_LOG_LEVEL  TA_Base_Core::DebugUtil::DebugFatal
#define ERROR_LOG_LEVEL  TA_Base_Core::DebugUtil::DebugError
#define WARN_LOG_LEVEL   TA_Base_Core::DebugUtil::DebugWarn
#define INFO_LOG_LEVEL   TA_Base_Core::DebugUtil::DebugInfo
#define DEBUG_LOG_LEVEL  TA_Base_Core::DebugUtil::DebugDebug

#endif // SECURITYUTILITIESINTERNAL_H_INCLUDED
