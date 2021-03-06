/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/response_plans/plan_agent/src/ActivePlanLaunchGuiAppStepMessage.cpp $
  *  @author:  Bart Golab
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2018/03/14 13:51:20 $
  *  Last modified by:  $Author: lim.cy $
  *
  *  Generated when the result of a Launch GUI App interactive step execution request
  *  is received back from the Plan Manager.
  */
#include "app/response_plans/common/src/ProjectDefinition.h"

#if defined ( STEPTYPE_LAUNCH_GUI_APP )

#include "core/data_access_interface/PlanAgent/IDL/src/PlanAgentDataCorbaDef.h"
#include "app/response_plans/plan_agent/src/ActivePlan.h"
#include "app/response_plans/plan_agent/src/ActiveStep.h"
#include "app/response_plans/plan_agent/src/ActivePlanBulletinBoard.h"
#include "app/response_plans/plan_agent/src/ActivePlanLaunchGuiAppStepMessage.h"
#include "app/response_plans/common/src/StringConstants.h"

namespace TA_Base_App
{
    ActivePlanLaunchGuiAppStepMessage::ActivePlanLaunchGuiAppStepMessage(const int status, const std::string& error) : 
    m_status(status), 
    m_error(error.c_str())
    {
    }


    ActivePlanLaunchGuiAppStepMessage::~ActivePlanLaunchGuiAppStepMessage()
    {
    }


    void ActivePlanLaunchGuiAppStepMessage::execute( ActivePlan& activePlan ) const
    {
        activePlan.resume();

        ActiveStep* activeStep = activePlan.getCurrentStep();

		if ( TA_Base_Core::PSCS_SUCCESS != m_status )            
	    {
            activePlan.setInteractiveStepFailed();
            activeStep->processStepExecutionFailure(m_error);
            return;
	    }

		ActivePlanBulletinBoard::instance()->updateStepState( activePlan.getPlan(), activeStep->getStepNumber(),
            TA_Base_Core::EXECUTED_ACTIVE_STEP_STATE, RemarkPlanStepExecuted );

        activePlan.setNextStep();
        activePlan.setInteractiveStep(false);
    }
}

#endif