/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/core/data_access_interface/alarm_rule/src/PlanExecutionRuleData.cpp $
  * @author:  Dirk McCormick
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2017/10/31 16:21:54 $
  * Last modified by:  $Author: CM $
  *
  * PlanExecutionRuleData is an implementation of IPlanExecutionRuleData.
  */

#ifdef __WIN32__
#pragma warning(disable:4786)
#pragma warning(disable:4503)  // warning C4503: '  ' : decorated name length exceeded, name was truncated
#endif


#include "core/data_access_interface/alarm_rule/src/PlanExecutionRuleData.h"
#include "core/data_access_interface/src/IData.h"
#include "core/data_access_interface/src/IDatabase.h"
#include "core/data_access_interface/src/DatabaseFactory.h"

#include "core/data_access_interface/plans/src/PlanAccessFactory.h"
#include "core/data_access_interface/plans/src/IPlan.h"

#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/DebugUtil.h"

#include "core/exceptions/src/DataException.h"

#include <sstream>

namespace TA_Base_Core
{
    const std::string PlanExecutionRuleData::RULE_TYPE = "PlanExecution";
    
    const std::string PlanExecutionRuleData::PLAN_NAME = "Plan";


    PlanExecutionRuleData::~PlanExecutionRuleData()
    {
    }


    PlanExecutionRuleData::PlanExecutionRuleData(
        const unsigned long key)
        :
        AlarmRuleData( new PlanExecutionRuleHelper(key) )
    {
    }


    PlanExecutionRuleData::PlanExecutionRuleData()
        :
        AlarmRuleData(new PlanExecutionRuleHelper())
    {
    }

    PlanExecutionRuleData::PlanExecutionRuleData(
        unsigned long entityTypeKey,
        unsigned long entityKey,
        unsigned long alarmTypeKey,
        const std::string& ruleTrigger,
        const std::string& planPath)
        :
        AlarmRuleData(
            new PlanExecutionRuleHelper(
                entityTypeKey, entityKey, alarmTypeKey, ruleTrigger, planPath) )
    {
    }


    PlanExecutionRuleData::PlanExecutionRuleData(
        const PlanExecutionRuleData& theRule)
        :
        AlarmRuleData(
            new PlanExecutionRuleHelper(
                dynamic_cast<PlanExecutionRuleHelper&>( theRule.getHelper() )))
    {
    }


    std::string PlanExecutionRuleData::getName()
    {
        return RULE_TYPE + " " + AlarmRuleData::getName();
    }


    std::string PlanExecutionRuleData::getPlanPath()
    {
        PlanExecutionRuleHelper& helper =
            dynamic_cast<PlanExecutionRuleHelper&>( getHelper() );

        return helper.getPlanPath();
    }


    void PlanExecutionRuleData::setPlanPath(const std::string& planPath)
    {
        PlanExecutionRuleHelper& helper =
            dynamic_cast<PlanExecutionRuleHelper&>( getHelper() );

        std::string oldPlanPath = helper.getPlanPath();
        
        helper.setPlanPath(planPath);

        updateAlarmRuleChanges(PLAN_NAME, oldPlanPath, planPath);
    }

} // closes TA_Base_Core
