/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/response_plans/plan_agent/src/ActivePlanFailureSummaryStepMessage.cpp $
  *  @author:  Lizette Lingo
  *  @version: $Revision: #7 $
  *
  *  Last modification: $DateTime: 2014/04/02 13:17:14 $
  *  Last modified by:  $Author: qi.huang $
  *
  *  Generated when the result of a Failure summary dialog display
  *  is received back from the Plan Manager.
  */
#include "app/response_plans/common/src/ProjectDefinition.h"

#if defined ( STEPTYPE_FAILURE_SUMMARY_STEP )

#include "core/utilities/src/DebugUtil.h"
#include "app/response_plans/plan_agent/src/ActivePlan.h"
#include "app/response_plans/plan_agent/src/ActiveStep.h"
#include "app/response_plans/plan_agent/src/ActivePlanBulletinBoard.h"
#include "app/response_plans/plan_agent/src/ActivePlanFailureSummaryStepMessage.h"
#include "app/response_plans/common/src/StringConstants.h"

namespace TA_Base_App
{
    ActivePlanFailureSummaryStepMessage::ActivePlanFailureSummaryStepMessage(const int status, const std::string& error) : 
    m_status(status), 
    m_error(error.c_str())
    {

    }


    ActivePlanFailureSummaryStepMessage::~ActivePlanFailureSummaryStepMessage()
    {
    }


    void ActivePlanFailureSummaryStepMessage::execute( ActivePlan& activePlan ) const
    {
        activePlan.resume();

        ActiveStep* activeStep = activePlan.getCurrentStep();
		unsigned long stepNumber = activeStep->getStepNumber();

		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "ActivePlanFailureSummaryStepMessage");

		if ( TA_Base_Core::PSCS_SUCCESS != m_status )            
	    {
            activePlan.setInteractiveStepFailed();
            activeStep->processStepExecutionFailure(m_error);
            return;
	    }

		ActivePlanBulletinBoard::instance()->updateStepState( activePlan.getPlan(), stepNumber,
            TA_Base_Core::EXECUTED_ACTIVE_STEP_STATE, RemarkPlanStepExecuted );

		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "ActivePlanBulletinBoard::instance()->update");
 
        activePlan.setNextStep();
        activePlan.setInteractiveStep(false);
    }
}

#endif