/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/core/exceptions/src/ValueNotSetException.h $
  * @author:  Jade Lee
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * This class describes a value not set exception, thrown when attempting 
  * to perform an uninitialized variable read
  *
  */


#if !defined(ValueNotSetException_23E1B2D0_A84C_4b2a_9F1C_FF5F4339F536__INCLUDED_)
#define ValueNotSetException_23E1B2D0_A84C_4b2a_9F1C_FF5F4339F536__INCLUDED_

#include "core/exceptions/src/TransactiveException.h"

namespace TA_Base_Core
{
    class ValueNotSetException : public TransactiveException
    {
    public:
	    
        ValueNotSetException() throw()
        : TransactiveException("Uninitialized variable read")
        { }
	    
        ValueNotSetException(const char* msg) throw()
        : TransactiveException(msg)
        { }
	    
        virtual ~ValueNotSetException() throw()
        { }
    };
};
#endif // !defined(ValueNotSetException_23E1B2D0_A84C_4b2a_9F1C_FF5F4339F536__INCLUDED_)
