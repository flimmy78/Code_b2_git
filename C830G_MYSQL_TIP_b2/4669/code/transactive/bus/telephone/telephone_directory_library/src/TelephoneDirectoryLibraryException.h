/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/bus/telephone/telephone_directory_library/src/TelephoneDirectoryLibraryException.h $
  * @author:  Raymond Pau
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * Implements the Exception required by the TelephoneDirectoryLibrary
  */

#if !defined(AFX_TELEPHONEDIRECTORYLIBRARYEXCEPTION_H__C497517C_9CF2_4C70_890F_D4BEB86DAA32__INCLUDED_)
#define AFX_TELEPHONEDIRECTORYLIBRARYEXCEPTION_H__C497517C_9CF2_4C70_890F_D4BEB86DAA32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "core/exceptions/src/TransactiveException.h"

class TelephoneDirectoryLibraryException : public TA_Base_Core::TransactiveException  
{
public:
	TelephoneDirectoryLibraryException();
    TelephoneDirectoryLibraryException(const std::string& msg);
	virtual ~TelephoneDirectoryLibraryException();
};

#endif // !defined(AFX_TELEPHONEDIRECTORYLIBRARYEXCEPTION_H__C497517C_9CF2_4C70_890F_D4BEB86DAA32__INCLUDED_)
