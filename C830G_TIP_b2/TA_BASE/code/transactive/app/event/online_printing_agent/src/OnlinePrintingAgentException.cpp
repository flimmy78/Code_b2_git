/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/event/online_printing_agent/src/OnlinePrintingAgentException.cpp $
  * @author:  Bart Golab
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * Thrown when an internal Online Printing Agent error occurs.
  *
  */

#include "app/event/online_printing_agent/src/OnlinePrintingAgent.h"

using namespace TA_Base_App;


OnlinePrintingAgentException::OnlinePrintingAgentException() throw()
{
}


OnlinePrintingAgentException::OnlinePrintingAgentException(const std::string& msg) throw() :
    TA_Base_Core::TransactiveException(msg)
{
}


OnlinePrintingAgentException::OnlinePrintingAgentException(const std::string& msg, const std::string& details) throw() :
    TA_Base_Core::TransactiveException(msg),
    m_details(details)
{
}


OnlinePrintingAgentException::~OnlinePrintingAgentException() throw()
{
}


const char* OnlinePrintingAgentException::getDetails() const throw()
{
    return m_details.c_str();
}
