/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/core/exceptions/src/AssertException.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * This file outlines a simple exception class for use with
  * the TA_ASSERT and TD_VERIFY macros. It is derived from 
  * TransActiveException.
  */


#if !defined(AFX_ASSERTEXCEPTION_H__599117C1_47C9_11D7_B150_0080C8E32E69__INCLUDED_)
#define AFX_ASSERTEXCEPTION_H__599117C1_47C9_11D7_B150_0080C8E32E69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TransactiveException.h"
#include <string>

namespace TA_Base_Core
{
	class AssertException : public TransactiveException  
	{
	public:
		AssertException() throw();
		AssertException(const std::string& msg) throw();
		virtual ~AssertException() throw();

	};
}

#endif // !defined(AFX_ASSERTEXCEPTION_H__599117C1_47C9_11D7_B150_0080C8E32E69__INCLUDED_)

