/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/alarm_rule/src/AutomaticAcknowledgementRuleHelper.cpp $
  * @author:  Dirk McCormick
  * @version: $Revision: #3 $
  *
  * Last modification: $DateTime: 2012/02/10 14:06:39 $
  * Last modified by:  $Author: huirong.luo $
  *
  * Provides an interface to Alarm Rules of type automatic acknowledgement
  * in the database.
  *
  */

#ifdef __WIN32__
#pragma warning(disable:4786)
#endif


#include "core/data_access_interface/alarm_rule/src/AutomaticAcknowledgementRuleHelper.h"
#include "core/data_access_interface/alarm_rule/src/AutomaticAcknowledgementRuleData.h"

#include "core/utilities/src/TAAssert.h"

namespace TA_Base_Core
{

    AutomaticAcknowledgementRuleHelper::AutomaticAcknowledgementRuleHelper()
        :
        AlarmRuleHelper(
            AutomaticAcknowledgementRuleData::RULE_TYPE,
            IAlarmRuleData::RULE_TRIGGER_CLOSE)
    {
    }
    
    
    AutomaticAcknowledgementRuleHelper::AutomaticAcknowledgementRuleHelper(
        unsigned long entityTypeKey,
        unsigned long entityKey,
        unsigned long alarmTypeKey,
        const std::string& ruleTrigger)
        :
        AlarmRuleHelper(
            entityTypeKey,
            entityKey,
            alarmTypeKey,
            AutomaticAcknowledgementRuleData::RULE_TYPE,
            ruleTrigger)
    {
    }


    AutomaticAcknowledgementRuleHelper::AutomaticAcknowledgementRuleHelper(
        unsigned long pkey)
        :
        AlarmRuleHelper(pkey)
    {
    }


    AutomaticAcknowledgementRuleHelper::AutomaticAcknowledgementRuleHelper(
        AutomaticAcknowledgementRuleHelper& original)
        :
        AlarmRuleHelper(
            original.getEntityTypeKey(),
            original.getEntityKey(),
            original.getAlarmType(),
            original.getRuleType(),
            original.getRuleTrigger())
    {
    }


    AutomaticAcknowledgementRuleHelper::~AutomaticAcknowledgementRuleHelper()
    {
    }


    void AutomaticAcknowledgementRuleHelper::setRuleTrigger(
        const std::string& trigger)
    {
        TA_ASSERT(trigger == IAlarmRuleData::RULE_TRIGGER_CLOSE,
                  "Automatic Acknowledgement can only occur when an "
                  "alarm is closed");
    }

}// TA_Base_Core
