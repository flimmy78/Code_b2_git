/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/bus/security/duty_monitor_framework/src/DutyMonitorFrameworkException.cpp $
  * @author:  Bart Golab
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * Thrown when an internal Duty Monitor Framework error occurs.
  *
  */

#include "bus/security/duty_monitor_framework/src/DutyMonitorFramework.h"

using namespace TA_Base_Bus;


DutyMonitorFrameworkException::DutyMonitorFrameworkException() throw()
{
    FUNCTION_ENTRY("DutyMonitorFrameworkException()");
    FUNCTION_EXIT;
}


DutyMonitorFrameworkException::DutyMonitorFrameworkException(const std::string& msg) throw() :
    TA_Base_Core::TransactiveException(msg)
{
    FUNCTION_ENTRY("DutyMonitorFrameworkException(const std::string& msg)");
    FUNCTION_EXIT;
}


DutyMonitorFrameworkException::DutyMonitorFrameworkException(const std::string& msg, const std::string& details) throw() :
    TA_Base_Core::TransactiveException(msg),
    m_details(details)
{
    FUNCTION_ENTRY("DutyMonitorFrameworkException(const std::string& msg, const std::string& details)");
    FUNCTION_EXIT;
}


DutyMonitorFrameworkException::~DutyMonitorFrameworkException() throw()
{
    FUNCTION_ENTRY("~DutyMonitorFrameworkException()");
    FUNCTION_EXIT;
}


const char* DutyMonitorFrameworkException::getDetails() const throw()
{
    FUNCTION_ENTRY("getDetails()");
    FUNCTION_EXIT;

    return m_details.c_str();
}
