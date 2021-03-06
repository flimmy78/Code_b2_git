#ifndef THIRDPARTYLIBEXCEPTION_H_INCLUDED
#define THIRDPARTYLIBEXCEPTION_H_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/response_plans/plan_agent/src/ThirdPartyLibException.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #3 $
  *
  *  Last modification: $DateTime: 2012/12/27 15:59:31 $
  *  Last modified by:  $Author: qi.huang $
  *
  *  <description>
  */

#include "core/exceptions/src/TransactiveException.h"

namespace TA_Base_App
{
	class ThirdPartyLibException : public TA_Base_Core::TransactiveException
	{
	public:
		ThirdPartyLibException() throw();
		ThirdPartyLibException(const std::string& msg) throw();
		virtual ~ThirdPartyLibException() throw();
	};
}; // TA_Base_App

#endif // THIRDPARTYLIBEXCEPTION_H_INCLUDED

