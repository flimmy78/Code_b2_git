/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/core/exceptions/src/UserCancelException.h $
  * @author:  Karen Graham
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * This exception is used in the Configuration Editor to determine a user cancel. A user cancel on
  * many of the dialogs means we have to undo everything we've been doing and close the application
  */

#if !defined(AFX_USERCANCELEXCEPTION_H__DCB83ED0_5DA6_11D7_B157_0080C8E32E69__INCLUDED_)
#define AFX_USERCANCELEXCEPTION_H__DCB83ED0_5DA6_11D7_B157_0080C8E32E69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

#include "core/exceptions/src/TransactiveException.h"

namespace TA_Base_Core
{
	class UserCancelException : public TransactiveException  
	{
	public:
		UserCancelException() throw();

		UserCancelException(const std::string& msg) throw();

		virtual ~UserCancelException() throw();

	};
}

#endif // !defined(AFX_USERCANCELEXCEPTION_H__DCB83ED0_5DA6_11D7_B157_0080C8E32E69__INCLUDED_)

