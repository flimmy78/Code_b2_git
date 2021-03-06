/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/core/ftp/src/FTPException.cpp $
  * @author:  J. Welton
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
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
