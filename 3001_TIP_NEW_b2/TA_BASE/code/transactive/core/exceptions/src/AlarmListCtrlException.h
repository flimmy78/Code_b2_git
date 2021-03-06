/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/exceptions/src/AlarmListCtrlException.h $
  * @author:  Karen Graham
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * This is used by bus/alarm/alarm_list_control to determine errors. When specified the msg field
  * may hold appropriate error messages to be displayed to the user.
  */

#if !defined(ALARM_LIST_CONTROL_EXCEPTION)
#define ALARM_LIST_CONTROL_EXCEPTION

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

#include "core/exceptions/src/TransactiveException.h"

namespace TA_Base_Core
{
    class AlarmListCtrlException : public TA_Base_Core::TransactiveException  
	{
    public:
        AlarmListCtrlException() throw();
        AlarmListCtrlException(const std::string& msg) throw();
        
        virtual ~AlarmListCtrlException() throw();
    };    
}

#endif // !defined(ALARM_LIST_CONTROL_EXCEPTION)
