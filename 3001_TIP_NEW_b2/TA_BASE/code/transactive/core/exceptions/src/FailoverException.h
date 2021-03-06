/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/exceptions/src/FailoverException.h $
  * @author:  <Rob Ashcroft>
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * <description>
  */


// FailoverException.h: interface for the FailoverException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FAILOVEREXCEPTION_H__3AF38847_EFC7_4815_B2B4_2BF966525E49__INCLUDED_)
#define AFX_FAILOVEREXCEPTION_H__3AF38847_EFC7_4815_B2B4_2BF966525E49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TransactiveException.h"

namespace TA_Base_Core
{

    class FailoverException : public TransactiveException  
    {
    public:
        FailoverException() throw();
        FailoverException(const std::string& msg) throw();
        virtual const char* what() const throw();
        virtual ~FailoverException() throw();

    protected:

        // This is where any exception messages are stored
        std::string m_message;
    };
};

#endif // !defined(AFX_FAILOVEREXCEPTION_H__3AF38847_EFC7_4815_B2B4_2BF966525E49__INCLUDED_)
