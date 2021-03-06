/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/bus/generic_server_simulator/src/CommandException.h $
  * @author:  Robert van Hugten
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  */

#ifndef CommandException_H
#define CommandException_H

#include "core/exceptions/src/TransactiveException.h"

namespace TA_Base_Bus
{
        class CommandException : public TA_Base_Core::TransactiveException  
    {
    public:
        /**
          * Default constructor.
          */
        CommandException() throw();

        /**
          * Constructor which takes a message string as an argument.
          *
          * @param message  An exception message describing a problem.
          */
        CommandException( const std::string & message ) throw();

        /**
          * Destructor.
          */
        virtual ~CommandException() throw();
    };    
}

#endif // CommandException_H
