/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/alarm/alarm_list_control/src/CommonStructures.h $
  * @author:  Karen Graham
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  *
  */


#ifndef COMMON_STRUCTURES_WED_04_02_2004_H
#define COMMON_STRUCTURES_WED_04_02_2004_H

#include <string>
#include <vector>

namespace TA_Base_Bus
{
    struct SAlarmDetails
    {
        std::string uuid;       // Unique identifier for the alarm
        bool isSelected;        // Indicates whether the alarm is selected

        bool operator==(const SAlarmDetails& rhs) const
        {
            if (rhs.uuid == this->uuid)
            {
                return true;
            }
            return false;
        }
    };


    typedef std::vector<SAlarmDetails> AlarmList;    

}
#endif COMMON_STRUCTURES_WED_04_02_2004_H
