/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/core/exceptions/src/CannotUseSysControllerException.h $
  * @author:  Karen Graham
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * This is used by the Configuration Editor. It is thrown when it cannot connect to the system using
  * the System Controller. This basically means it will have to connect using a direct database connection
  */


#if !defined(AFX_CANNOTUSESYSTEMCONTROLLEREXCEPTION_H__BCECD7DE_CBB1_47E8_BA92_5D48199EC772__INCLUDED_)
#define AFX_CANNOTUSESYSTEMCONTROLLEREXCEPTION_H__BCECD7DE_CBB1_47E8_BA92_5D48199EC772__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/exceptions/src/TransactiveException.h"

namespace TA_Base_Core
{

    class CannotUseSysControllerException: public TA_Base_Core::TransactiveException  
    {
    public:
        
        CannotUseSysControllerException(const std::string& msg) throw();

	    virtual ~CannotUseSysControllerException() throw();
    };
 
};

#endif // !defined(AFX_CANNOTUSESYSTEMCONTROLLEREXCEPTION_H__BCECD7DE_CBB1_47E8_BA92_5D48199EC772__INCLUDED_)
