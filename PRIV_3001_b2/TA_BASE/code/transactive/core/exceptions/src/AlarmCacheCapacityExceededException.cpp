/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/core/exceptions/src/AlarmCacheCapacityExceededException.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * <description>
  *
  */

#include "AlarmCacheCapacityExceededException.h"

namespace TA_Base_Core
{

    AlarmCacheCapacityExceededException::AlarmCacheCapacityExceededException() throw()
    {}

    AlarmCacheCapacityExceededException::AlarmCacheCapacityExceededException(const std::string& msg) 
        throw(): TransactiveException(msg)
    {}

    AlarmCacheCapacityExceededException::~AlarmCacheCapacityExceededException() throw()
    {}
}
