/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/core/exceptions/src/FailoverException.h $
  * @author:  <Rob Ashcroft>
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
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
