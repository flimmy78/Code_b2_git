/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/response_plans/plan_agent/src/ActivePromptStep.cpp $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2018/03/14 13:51:20 $
  *  Last modified by:  $Author: lim.cy $
  *
  *  Implementation of .
  */

#include "app/response_plans/common/src/ProjectDefinition.h"

#if defined ( STEPTYPE_PROMPT )

#include "core/utilities/src/DebugUtil.h"
#include "core/corba/src/CorbaUtil.h"
#include "core/exceptions/src/ObjectResolutionException.h"
#include "bus/response_plans/plan_manager/IDL/src/IPlanManagerCorbaDef.h"
#include "app/response_plans/plan_agent/src/IActivePlanFlow.h"
#include "app/response_plans/plan_agent/src/ActivePlanBulletinBoard.h"
#include "app/response_plans/plan_agent/src/ActivePromptStep.h"
#include "app/response_plans/common/src/StringConstants.h"

// namespace alias for Corba structures/types
 
namespace TA_Base_App
{

	ActivePromptStep::ActivePromptStep( const TA_Base_Core::StepDetail& stepDetail, 
        const TA_Base_Core::PromptParameters& params, IActivePlanFlow& flowControl ) : 
    ActiveStep(stepDetail, flowControl, params.dismissTimeout),
    m_params(params)
	{
	}

	TA_Base_Core::EActiveStepState ActivePromptStep::executeImpl( void )
	{
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "Prompt step %lu", getStepNumber() );

		TA_Base_Core::EActiveStepState stepState = TA_Base_Core::LOADED_ACTIVE_STEP_STATE;

		m_remark = RemarkWaitingForOperatorResponse;

		TA_Base_Core::CurrentPlanStepDetail detail;

        detail.activePlan = m_flowControl.getPlan();
        detail.step = getStepNumber();
        detail.data.prompt(m_params);

		TA_Base_Bus::IPlanManagerCorbaDef_ptr planManager = NULL;
		try
		{
			ActivePlanBulletinBoard::instance()->getPlanManagerObjRef(m_flowControl.getPlan(), planManager);

			if ( planManager != NULL )
			{
				if ( planManager->_non_existent() )
				{
					LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "Reference to non existent Plan Manager");
					m_remark = RemarkPlanManagerIsNotRegistered;
					stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;
					// The object is invalid
				}
				else
                {
                    try
                    {
					    planManager->executeInteractiveStep(detail);
                        m_flowControl.setInteractiveStep(true);
                    }
                    catch (const TA_Base_Bus::IPlanManagerCorbaDef::InteractiveStepExecuteError& isee)
                    {   
                        std::string message = "ActivePromptStep: Exception caught IPlanManagerCorbaDef::InteractiveStepExecuteError. ";
                        message += isee.reason.in();
			            LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, message.c_str() );
			            m_remark = isee.reason.in();
			            stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;                            
                    }
                }
			}
			else
			{
				LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Error: Unregistered Plan Manager is running the interactive plan.");
				m_remark = RemarkNoPlanManagerForOperatorInput;
				stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;
			}
		}
		catch ( const CORBA::Exception& e)
		{
			LOG_EXCEPTION_DETAILS( SourceInfo, "TA_Base_Core::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString( e ).c_str() );
			m_remark = RemarkPlanManagerIsNotRegistered;
			stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;
		}
		catch ( ... )
		{
			LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Error: Unregistered Plan Manager is running the interactive plan.");
			m_remark = RemarkPlanManagerIsNotRegistered;
			stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;
		}

        if ( TA_Base_Core::FAILED_ACTIVE_STEP_STATE != stepState )
        {
            m_flowControl.pauseForOperator();
        }

		return( stepState );
	}
} // TA_Base_App


#endif // STEPTYPE_PROMPT

