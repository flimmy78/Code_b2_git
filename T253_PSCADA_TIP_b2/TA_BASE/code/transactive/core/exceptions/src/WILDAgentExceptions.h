/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/core/exceptions/src/WILDAgentExceptions.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2017/10/31 16:21:54 $
  * Last modified by:  $Author: CM $
  *
  * This file outlines a simple exception class for the WILD Agent
  */


#if !defined(WILDAGENTEXCEPTION)
#define WILDAGENTEXCEPTION


#include <string>																
#include "core/exceptions/src/TransactiveException.h"

namespace TA_Base_Core
{
    class InvalidWILDConfigurationException : public TransactiveException
    {

    public:
	    
        InvalidWILDConfigurationException() throw()
        : TransactiveException("Unspecified inconsistency detected in the WILD configuration")
        { }
	    
        InvalidWILDConfigurationException(const char* msg) throw()
        : TransactiveException(msg)
        { }
	    
        virtual ~InvalidWILDConfigurationException() throw()
        { }
    };

    class InvalidWILDDataPointValueException : public TransactiveException
    {

    public:
	    
        InvalidWILDDataPointValueException() throw() : TransactiveException("Invalid WILD DataPoint value")
        { }
	    
        virtual ~InvalidWILDDataPointValueException() throw()
        { }
    };


	class WILDAgentException : public TA_Base_Core::TransactiveException  
	{

    public:
        WILDAgentException() throw();
        WILDAgentException(const std::string& msg) throw();
        virtual ~WILDAgentException() throw();
    }; 

}

#endif // !defined(WILDAGENTEXCEPTION)

