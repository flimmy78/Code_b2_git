/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/core/ftp/src/FTPException.cpp $
  * @author:  J. Welton
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * Exception class thrown by the FTP Interface
  *
  */

#include "core/ftp/src/FTPException.h"

namespace TA_Base_Core
{
	FTPException::FTPException() throw() {}

    FTPException::FTPException(const std::string& msg) 
            throw(): TransactiveException(msg) {}

    FTPException::~FTPException() throw() {}
}
