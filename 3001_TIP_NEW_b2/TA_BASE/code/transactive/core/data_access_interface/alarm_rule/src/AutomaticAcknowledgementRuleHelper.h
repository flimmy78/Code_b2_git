/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/alarm_rule/src/AutomaticAcknowledgementRuleHelper.h $
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

#ifndef AUTOMATIC_ACKNOWLEDGEMENT_RULE_HELPER_H
#define AUTOMATIC_ACKNOWLEDGEMENT_RULE_HELPER_H


#include <string>
#include <vector>


#include "core/data_access_interface/alarm_rule/src/AlarmRuleHelper.h"

namespace TA_Base_Core
{

    class AutomaticAcknowledgementRuleHelper : public AlarmRuleHelper
    {

    public:

        /** 
          * AutomaticAcknowledgementRuleHelper
          *
          * @param entityTypeKey  The key of the entity's type.
          * @param entityKey      The entity's key.
          * @param ruleType       The rule type associated with the alarm rule.
          * @param ruleTrigger    The trigger for this alarm rule.
          *
          */
        AutomaticAcknowledgementRuleHelper(
            unsigned long entityTypeKey,
            unsigned long entityKey,
            unsigned long alarmTypeKey,
            const std::string& ruleTrigger);


        /** 
          * AutomaticAcknowledgementRuleHelper
          *
          * Constructs a new AutomaticAcknowledgementRuleHelper with blank
          * fields
          *
          */
        AutomaticAcknowledgementRuleHelper();


        
        /** 
          * AutomaticAcknowledgementRuleHelper
          *
          * Creates an Automatic Acknowledgement Alarm Rule from the database.
          *
          * @param pkey  the primary key of the automatic acknowledgement
          *              alarm rule.
          */
        AutomaticAcknowledgementRuleHelper(unsigned long pkey);


        /** 
          * ~AutomaticAcknowledgementRuleHelper
          *
          * Destructor
          *
          */
        virtual ~AutomaticAcknowledgementRuleHelper();


        /** 
          * AutomaticAcknowledgementRuleHelper
          *
          * Creates a copy of the given object.
          *
          * @param original  the object that will be copied.
          */
        AutomaticAcknowledgementRuleHelper(
            AutomaticAcknowledgementRuleHelper& original);


        /** 
          * setRuleTrigger
          *
          * This is overridden to assert if anything other than
          * IAlarmRuleData::RULE_TRIGGER_CLOSE is set.
          *
          * @param trigger  the trigger
          */
        virtual void setRuleTrigger(const std::string& trigger);


    private:

        const AutomaticAcknowledgementRuleHelper& operator=(const AutomaticAcknowledgementRuleHelper&);
    };


}// TA_Base_Core

#endif // AUTOMATIC_ACKNOWLEDGEMENT_RULE_HELPER_H
