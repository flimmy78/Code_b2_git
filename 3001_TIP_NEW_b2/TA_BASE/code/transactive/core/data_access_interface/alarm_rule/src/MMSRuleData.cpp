/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/alarm_rule/src/MMSRuleData.cpp $
  * @author:  Ross Tucker
  * @version: $Revision: #3 $
  *
  * Last modification: $DateTime: 2012/02/10 14:06:39 $
  * Last modified by:  $Author: huirong.luo $
  *
  */

#ifdef __WIN32__
#pragma warning(disable:4786)
#pragma warning(disable:4503)  // warning C4503: '  ' : decorated name length exceeded, name was truncated
#endif


#include "core/data_access_interface/alarm_rule/src/MMSRuleData.h"

namespace TA_Base_Core
{
    std::string MMSRuleData::RULE_TYPE = "MMS"; //TD16491++

    
    MMSRuleData::~MMSRuleData()
    {
    }


    MMSRuleData::MMSRuleData(
        const unsigned long key)
        :
        AlarmRuleData( new MMSRuleHelper(key) )
    {
    }


    MMSRuleData::MMSRuleData()
        :
        AlarmRuleData(new MMSRuleHelper())
    {
    }


    MMSRuleData::MMSRuleData(
        unsigned long entityTypeKey,
        unsigned long entityKey,
        unsigned long alarmTypeKey,
        const std::string& ruleTrigger)
        :
        AlarmRuleData(
            new MMSRuleHelper(
                entityTypeKey, entityKey, alarmTypeKey, ruleTrigger) )
    {
    }


    MMSRuleData::MMSRuleData(
        const MMSRuleData& theRule)
        :
        AlarmRuleData(
            new MMSRuleHelper(
                dynamic_cast<MMSRuleHelper&>( theRule.getHelper() )))
    {
    }


    std::string MMSRuleData::getName()
    {
        return RULE_TYPE + " " + AlarmRuleData::getName();
    }

} // closes TA_Base_Core
