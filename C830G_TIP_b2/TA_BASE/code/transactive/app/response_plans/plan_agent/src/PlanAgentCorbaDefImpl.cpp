/**
*  The source code in this file is the property of
*  Ripple Systems and is not for redistribution
*  in any form.
*
*  Source:   $File: //depot/4669_Review_Branch/TA_BASE/transactive/app/response_plans/plan_agent/src/PlanAgentCorbaDefImpl.cpp $
*  @author:  Gregg Kirkpatrick
*  @version: $Revision: #6 $
*
*  Last modification: $DateTime: 2011/06/20 20:46:25 $
*  Last modified by:  $Author: qi.huang $
*
*  Implementation of DAI::PlanAgentDataCorbaDef and GenericAgent
*  interfaces.
*/

#include "core/process_management/IDL/src/ProcessManagementDataDefinitionsCorbaDef.h"
#include "core/exceptions/IDL/src/CommonExceptionsCorbaDef.h"
#include "core/utilities/src/RunParams.h"
#include "bus/generic_agent/src/GenericAgent.h"
#include "PlanAgent.h"


namespace TA_Base_App
{
	
	PlanAgentCorbaDefImpl::PlanAgentCorbaDefImpl(PlanAgentUser * parentClass)
		:m_parentClass(parentClass)
	{
	}
	
	PlanAgentCorbaDefImpl::~PlanAgentCorbaDefImpl()
	{
		ActivePlanBulletinBoard::instance()->deleteRightsLib ();
    }
	
	
	CORBA::Boolean PlanAgentCorbaDefImpl::isRegisteredManager (const char* session, const char* pmId)
	{
		FUNCTION_ENTRY("isRegisteredManager");
		
		
		checkOperationMode();
		
		CORBA::Boolean retVal = ActivePlanBulletinBoard::instance()->isRegisteredManager (session, pmId);
		FUNCTION_EXIT;
		return retVal;
	}
	
	void PlanAgentCorbaDefImpl::registerPlanManager(const char* session, const char* pmId, TA_Base_Bus::IPlanManagerCorbaDef_ptr planManagerRef)
	{
		FUNCTION_ENTRY("registerPlanManager");
		
		
		checkOperationMode();
		
		ActivePlanBulletinBoard::instance()->registerPlanManager( session, pmId, planManagerRef);
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::deregisterPlanManager(const char* session, const char* pmId)
	{
		FUNCTION_ENTRY("deregisterPlanManager");
		
		
		checkOperationMode();
		
		ActivePlanBulletinBoard::instance()->deregisterPlanManager( session, pmId);
        FUNCTION_EXIT;
	}
	
	CORBA::Boolean PlanAgentCorbaDefImpl::isOwner(const char* session, const TA_Base_Core::ActivePlanId& plan)
	{
		FUNCTION_ENTRY("isOwner");
		
		
		checkOperationMode();
		
		try
		{
			CORBA::Boolean retVal = ActivePlanBulletinBoard::instance()->isOwner(session, plan);
            FUNCTION_EXIT;
            return retVal;
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch( ...)
		{
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown exception"));
		}
	}
	
    void PlanAgentCorbaDefImpl::processDecisionStepResponse(const char* session, const TA_Base_Core::ActivePlanId& plan, TA_Base_Core::EPlanStepCompletionStatus status)
    {
		FUNCTION_ENTRY("processDecisionStepResponse");
		
		checkOperationMode();
		
		try
		{
			if ( ActivePlanBulletinBoard::instance()->isOwner(session, plan))
				PlanExecutor::instance()->processDecisionStepResponse( plan, status );
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown exception"));
		}
        
        FUNCTION_EXIT;
    }
	
    void PlanAgentCorbaDefImpl::processPromptStepResponse(const char* session, const TA_Base_Core::ActivePlanId& plan, TA_Base_Core::EPlanStepCompletionStatus status)
    {
		FUNCTION_ENTRY("processPromptStepResponse");
		
		
		checkOperationMode();
		
		try
		{
			if ( ActivePlanBulletinBoard::instance()->isOwner(session, plan))
				PlanExecutor::instance()->processPromptStepResponse( plan, status );
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown exception"));
		}
		
        FUNCTION_EXIT;
    }
    void PlanAgentCorbaDefImpl::processLogStepResponse(const char* session, const TA_Base_Core::ActivePlanId& plan, TA_Base_Core::EPlanStepCompletionStatus status, const char* logMessage)
    {
		FUNCTION_ENTRY("processLogStepResponse");

		checkOperationMode();
		
		try
		{
			if ( ActivePlanBulletinBoard::instance()->isOwner(session, plan))
				PlanExecutor::instance()->processLogStepResponse( plan, status, logMessage );
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown exception"));
		}
		
        FUNCTION_EXIT;
    }
	
    void PlanAgentCorbaDefImpl::processRunPlanStepResult(const char* session, const TA_Base_Core::ActivePlanId& plan, TA_Base_Core::EPlanStepCompletionStatus status, const char* error)
    {
		FUNCTION_ENTRY("processRunPlanStepResult");
		
		
		checkOperationMode();
		
		try
		{
			if ( ActivePlanBulletinBoard::instance()->isOwner(session, plan))
            {
				PlanExecutor::instance()->processRunPlanStepResult( plan, status, error ); 
            }
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown exception"));
		}
		
        FUNCTION_EXIT;
    }
	
    void PlanAgentCorbaDefImpl::processLaunchGuiAppStepResult(const char* session, const TA_Base_Core::ActivePlanId& plan, TA_Base_Core::EPlanStepCompletionStatus status, const char* error)
    {
		FUNCTION_ENTRY("processLaunchGuiAppStepResult");
		
		
		checkOperationMode();
		
		try
		{
			if ( ActivePlanBulletinBoard::instance()->isOwner(session, plan))
            {
				PlanExecutor::instance()->processLaunchGuiAppStepResult( plan, status, error );
            }
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown exception"));
		}
		
        FUNCTION_EXIT;
    }
	
    void PlanAgentCorbaDefImpl::processLaunchSchematicStepResult(const char* session, const TA_Base_Core::ActivePlanId& plan, TA_Base_Core::EPlanStepCompletionStatus status, const char* error)
    {
		FUNCTION_ENTRY("processLaunchSchematicStepResult");
		
		
		checkOperationMode();
		try
		{
			if ( ActivePlanBulletinBoard::instance()->isOwner(session, plan))
            {
				PlanExecutor::instance()->processLaunchSchematicStepResult( plan, status, error );
            }
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown exception"));
		}
		
        FUNCTION_EXIT;
    }
	
	//lizettejl++ DP-Changes
	void PlanAgentCorbaDefImpl::processFailureSummaryStepResult(const char* session, const TA_Base_Core::ActivePlanId& plan, TA_Base_Core::EPlanStepCompletionStatus status, const char* error)
    {
		FUNCTION_ENTRY("processFailureSummaryStepResult");
		
		
		checkOperationMode();
		
		try
		{
			if ( ActivePlanBulletinBoard::instance()->isOwner(session, plan))
            {
				PlanExecutor::instance()->processFailureSummaryStepResult( plan, status, error );
            }
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown exception"));
		}
		
        FUNCTION_EXIT;
    }
	//++lizettejl


	// TD20368 Yanrong++
	void PlanAgentCorbaDefImpl::runPlan(const char* session, TA_Base_Core::ActivePlanId& plan)
	{
		FUNCTION_ENTRY("runPlan");
		runPlan( session, plan, true );
        FUNCTION_EXIT;
	}


	void PlanAgentCorbaDefImpl::runPlan(const char* session, 
										TA_Base_Core::ActivePlanId& plan, 
										bool checkActionPermitted )
	{
		FUNCTION_ENTRY("runPlan");
		checkOperationMode();
		
		unsigned long action = TA_Base_Bus::aca_PLAN_CONTROL_PLAN;
		std::string reason;
		
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "TD20368 runPlan: session=%s, planId=%li, checkActionPermited=%s",
			session, plan.plan, checkActionPermitted ? "true" : "false" );
		if( checkActionPermitted )
		{
			std::ostringstream message;
			
			message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
				<< " does not have rights to run Plan[" << plan.plan << ":" << plan.instance
				<< "]";

			if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
			{
				LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
				FUNCTION_EXIT;
				TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
			}
		}
		
		
		try
		{
			PlanExecutor::instance()->run( session, "", plan );
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown exception"));
		}
        FUNCTION_EXIT;
	}

	
	unsigned long PlanAgentCorbaDefImpl::runPlanByNameWithoutActionPermittedCheck(const char* session, const char* path, const char* param)
	{
		FUNCTION_ENTRY( "runPlanByNameForTSP" );
		checkOperationMode();

        TA_Base_Core::ActivePlanId plan;
        plan.plan = getNodeId(path);

		plan.entitykey = -1;
		plan.param = param;
        
        runPlan(session, plan, false);

		FUNCTION_EXIT;
        return plan.instance;
	}
	// ++Yanrong
	
	unsigned long PlanAgentCorbaDefImpl::runPlanByName(const char* session, const char* path, const char* param)
	{
		FUNCTION_ENTRY("runPlanByName");
		
		
		
		checkOperationMode();
		
        TA_Base_Core::ActivePlanId plan;
        plan.plan = getNodeId(path);
		//marvin++
		//TD13527
		plan.entitykey = -1;
		plan.param = param;
		//++marvin
		//TD13527
        
        runPlan(session, plan);
		
        FUNCTION_EXIT;
        return plan.instance;
	}
	
	//marvin++
	//TD13527
	//Prevents another instance of a plan to execute while a plan of the same type is executing for the same entity
	unsigned long PlanAgentCorbaDefImpl::runPlanByNameWithEntityRestriction( const char* session, const char* path, unsigned long entitykey)
	{
		FUNCTION_ENTRY("runPlanByNameWithEntityRestriction");
		
		
		
		checkOperationMode();
		
        TA_Base_Core::ActivePlanId plan;
        plan.plan = getNodeId(path);
		plan.entitykey = entitykey;
        plan.param = CORBA::string_dup("");
        
        runPlan(session, plan);
		
        FUNCTION_EXIT;
        return plan.instance;
	}
	//++marvin
	//TD13527
	
    void PlanAgentCorbaDefImpl::runOperatorTriggeredPlan(const char* session, const char* pmId, TA_Base_Core::ActivePlanId& plan)
    {
        FUNCTION_ENTRY("runOperatorTriggeredPlan");

		checkOperationMode();

		unsigned long action = TA_Base_Bus::aca_PLAN_CONTROL_PLAN;
		std::string reason;

		std::ostringstream message;

		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to run Plan[" << plan.plan << ":" << plan.instance
			<< "]";
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}

		try
		{
			PlanExecutor::instance()->run( session, pmId, plan , true);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Cannot run operator triggered plan"));
		}
		
        FUNCTION_EXIT;
    }
	
	
	void PlanAgentCorbaDefImpl::customisePlan(const char* session, const char* pmId, TA_Base_Core::ActivePlanId& plan)
	{
		FUNCTION_ENTRY("customisePlan");
		
		
		checkOperationMode();
		
		unsigned long action = TA_Base_Bus::aca_PLAN_CUSTOMISE_PLAN;
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to customise Plan[" << plan.plan << ":" << plan.instance
			<< "]";
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanExecutor::instance()->customise( session, pmId, plan );
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Cannot customise plan"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::pausePlan(const char* session, const TA_Base_Core::ActivePlanId& plan)
	{
		FUNCTION_ENTRY("pausePlan");

		checkOperationMode();
		
		unsigned long action = TA_Base_Bus::aca_PLAN_CONTROL_PLAN;
		std::string reason;
		
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to pause Plan[" << plan.plan << ":" << plan.instance
			<< "]";
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
        std::string planName = TA_Base_Bus::PlanDataReader::instance()->getNodePath(plan.plan);
        std::ostringstream inststrm;
        inststrm << plan.instance;
        std::string instanceNumber = inststrm.str();
        TA_Base_Core::DescriptionParameters descriptionParameters;
		//xufeng++ TD14927
		TA_Base_Core::NameValuePair pair0( "DSSOperatorActionValue", "UNSUCCESSFUL");
		descriptionParameters.push_back ( &pair0 );
		//++xufeng TD14927
        TA_Base_Core::NameValuePair pair1( "PlanName", planName);
		descriptionParameters.push_back ( &pair1);        
        TA_Base_Core::NameValuePair pair2( "InstanceNumber", instanceNumber);
		descriptionParameters.push_back ( &pair2);
		
		try
		{
			PlanExecutor::instance()->pause( plan );
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unknown.");
			if (ActivePlanBulletinBoard::instance()->isManualPlan (plan))
			{
				AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanPauseFailure, descriptionParameters);
				FUNCTION_EXIT;
				TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_PLAN_PAUSE_ERROR, 0, e.what()));
			}
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unknown.");
			if (ActivePlanBulletinBoard::instance()->isManualPlan (plan))
			{
				AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanPauseFailure, descriptionParameters);
				FUNCTION_EXIT;
				TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_PLAN_PAUSE_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
			}
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
			if (ActivePlanBulletinBoard::instance()->isManualPlan (plan))
			{
				AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanPauseFailure, descriptionParameters);
				FUNCTION_EXIT;
				TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_PLAN_PAUSE_ERROR, 0, "Cannot pause plan"));
			}
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::resumePlan(const char* session, const TA_Base_Core::ActivePlanId& plan)
	{
		FUNCTION_ENTRY("resumePlan");
		
		
		checkOperationMode();
		
		unsigned long action = TA_Base_Bus::aca_PLAN_CONTROL_PLAN;
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to resume Plan[" << plan.plan << ":" << plan.instance
			<< "]";
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
        std::string planName = TA_Base_Bus::PlanDataReader::instance()->getNodePath(plan.plan);
        std::ostringstream inststrm;
        inststrm << plan.instance;
        std::string instanceNumber = inststrm.str();
        TA_Base_Core::DescriptionParameters descriptionParameters;
        TA_Base_Core::NameValuePair pair1( "PlanName", planName);
		descriptionParameters.push_back ( &pair1);        
        TA_Base_Core::NameValuePair pair2( "InstanceNumber", instanceNumber);
		descriptionParameters.push_back ( &pair2);
		
		
		try
		{
			
			//lizettejl++ DP-changes: Add in step position for the resumed plan 
			TA_Base_Core::ActivePlanDetail_var activePlanDetail = ActivePlanBulletinBoard::instance()->getActivePlanDetail(plan);
			PlanExecutor::instance()->resume( plan, activePlanDetail->currentStepDetail.position );
			//++lizettejl
			
			TA_Base_Core::DescriptionParameters descriptionParameters;
			//xufeng++ TD14927
			TA_Base_Core::NameValuePair pair0( "DSSOperatorActionValue", "UNSUCCESSFUL");
			descriptionParameters.push_back ( &pair0 );
			//++xufeng TD14927
			
            TA_Base_Core::NameValuePair pair1( "PlanName", TA_Base_Bus::PlanDataReader::instance()->getNodePath(plan.plan));
			descriptionParameters.push_back ( &pair1);
			
            std::ostringstream tempStrm;
            tempStrm << plan.instance;
            TA_Base_Core::NameValuePair pair2( "InstanceNumber", tempStrm.str());
			descriptionParameters.push_back ( &pair2);
			
			//xufeng++ TD14927
			TA_Base_Core::DescriptionParameters descriptionParameters2;
			TA_Base_Core::NameValuePair pair3( "DSSOperatorActionValue", "SUCCESSFUL");
			descriptionParameters2.push_back ( &pair3 );
			descriptionParameters2.push_back ( &pair1);
			descriptionParameters2.push_back ( &pair2);
			//++xufeng TD14927
			
			std::string session = ActivePlanBulletinBoard::instance()->getSession(plan);
			
			AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanResume, descriptionParameters2);
			
		}
		catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
			if (ActivePlanBulletinBoard::instance()->isManualPlan (plan))
			{
				AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanResumeFailure, descriptionParameters);
				FUNCTION_EXIT;
				TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_PLAN_RESUME_ERROR, 0, e.what()));
			}
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
			if (ActivePlanBulletinBoard::instance()->isManualPlan (plan))
			{
				AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanResumeFailure, descriptionParameters);
				FUNCTION_EXIT;
				TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_PLAN_RESUME_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
			}
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
			if (ActivePlanBulletinBoard::instance()->isManualPlan (plan))
			{
				AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanResumeFailure, descriptionParameters);
				FUNCTION_EXIT;
				TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_PLAN_RESUME_ERROR, 0, "Cannot resume plan"));
			}
		}
		
        FUNCTION_EXIT;
	}
	
	//lizettejl++ (DP-changes)
	void PlanAgentCorbaDefImpl::resumePlanAtStep(const char* session, const TA_Base_Core::ActivePlanId& plan, TA_Base_Core::StepNumber step)
	{
		FUNCTION_ENTRY("resumePlanAtStep");
		
		
		checkOperationMode();
		
		unsigned long action = TA_Base_Bus::aca_PLAN_CONTROL_PLAN;
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to resume Plan[" << plan.plan << ":" << plan.instance
			<< "]";
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
        std::string planName = TA_Base_Bus::PlanDataReader::instance()->getNodePath(plan.plan);
        std::ostringstream inststrm;
        inststrm << plan.instance;
        std::string instanceNumber = inststrm.str();
        TA_Base_Core::DescriptionParameters descriptionParameters;
		//xufeng++ TD14927
		TA_Base_Core::NameValuePair pair0( "DSSOperatorActionValue", "SUCCESSFUL");
		descriptionParameters.push_back ( &pair0 );
		//++xufeng TD14927
        TA_Base_Core::NameValuePair pair1( "PlanName", planName);
		descriptionParameters.push_back ( &pair1);        
        TA_Base_Core::NameValuePair pair2( "InstanceNumber", instanceNumber);
		descriptionParameters.push_back ( &pair2);	
		
		//xufeng++ TD14927
		TA_Base_Core::DescriptionParameters descriptionParameters2;
		TA_Base_Core::NameValuePair pair3( "DSSOperatorActionValue", "UNSUCCESSFUL");
		descriptionParameters2.push_back ( &pair3 );
		descriptionParameters2.push_back ( &pair1);
		descriptionParameters2.push_back ( &pair2);
		//++xufeng TD14927		
		
		bool bValidStepToResume = false;
		
		TA_Base_Core::ExecutionHistory* executionHistory = ActivePlanBulletinBoard::instance()->getPlanExecutionHistory( plan);
		if ( NULL != executionHistory )
		{
			for (CORBA::ULong i = 0; i < executionHistory->details.length(); i++)
			{
				TA_Base_Core::ActiveStepDetail stepDetail =  executionHistory->details[i];
				if ((stepDetail.position == step) && ((stepDetail.state == TA_Base_Core::PAUSED_ACTIVE_STEP_STATE) || 
					(stepDetail.state == TA_Base_Core::SKIPPED_ACTIVE_STEP_STATE) || 
					(stepDetail.state == TA_Base_Core::EXECUTED_ACTIVE_STEP_STATE)))
				{
					bValidStepToResume = true;
					break;
				}
			}
			delete executionHistory;
			executionHistory = NULL;
		}	 	
		
		try
		{	
			if (true == bValidStepToResume)
			{				
				PlanExecutor::instance()->resume( plan, step );				
				AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanResume, descriptionParameters);
			}
			
		}
		catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
			if (ActivePlanBulletinBoard::instance()->isManualPlan (plan))
			{
				AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanResumeFailure, descriptionParameters2);
				FUNCTION_EXIT;
				TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_PLAN_RESUME_ERROR, 0, e.what()));
			}
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
			if (ActivePlanBulletinBoard::instance()->isManualPlan (plan))
			{
				AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanResumeFailure, descriptionParameters2);
				FUNCTION_EXIT;
				TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_PLAN_RESUME_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
			}
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
			if (ActivePlanBulletinBoard::instance()->isManualPlan (plan))
			{
				AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanResumeFailure, descriptionParameters2);
				FUNCTION_EXIT;
				TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_PLAN_RESUME_ERROR, 0, "Cannot resume plan"));
			}
		}
		
        FUNCTION_EXIT;
	}
	//++lizettejl
	
	void PlanAgentCorbaDefImpl::stopPlan(const char* session, const TA_Base_Core::ActivePlanId& plan)
	{
		FUNCTION_ENTRY("stopPlan");
		
		
		checkOperationMode();
		
		unsigned long action = TA_Base_Bus::aca_PLAN_CONTROL_PLAN;
		std::ostringstream message;
        std::string reason;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to stop Plan[" << plan.plan << ":" << plan.instance
			<< "]";
		
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
        reason = ActivePlanBulletinBoard::instance()->getOwner(session);
        reason += " stopped the Plan.";
		
        std::string planName = TA_Base_Bus::PlanDataReader::instance()->getNodePath(plan.plan);
        std::ostringstream inststrm;
        inststrm << plan.instance;
        std::string instanceNumber = inststrm.str();
        TA_Base_Core::DescriptionParameters descriptionParameters;
		//xufeng++ TD14927
		TA_Base_Core::NameValuePair pair0( "DSSOperatorActionValue", "UNSUCCESSFUL");
		descriptionParameters.push_back ( &pair0 );
		//++xufeng TD14927
        TA_Base_Core::NameValuePair pair1( "PlanName", planName);
		descriptionParameters.push_back ( &pair1);        
        TA_Base_Core::NameValuePair pair2( "InstanceNumber", instanceNumber);
		descriptionParameters.push_back ( &pair2);
		
		try
		{
			PlanExecutor::instance()->stop( plan, reason );
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
			if (ActivePlanBulletinBoard::instance()->isManualPlan (plan))
			{
				AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanStopFailure, descriptionParameters);
				FUNCTION_EXIT;
				TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_PLAN_STOP_ERROR, 0, e.what()));
			}
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
			if (ActivePlanBulletinBoard::instance()->isManualPlan (plan))
			{
				AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanStopFailure, descriptionParameters);
				FUNCTION_EXIT;
				TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_PLAN_STOP_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
			}
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
			if (ActivePlanBulletinBoard::instance()->isManualPlan (plan))
			{
				AAMessageSender::instance()->sendAuditMessage(session, TA_Base_Core::PlanAgentAudit::PlanStopFailure, descriptionParameters);
				FUNCTION_EXIT;
				TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_PLAN_STOP_ERROR, 0, "Cannot stop plan"));
			}
		}
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::takeControl(const char* session, const char* pmId, const TA_Base_Core::ActivePlanId& plan)
	{
		FUNCTION_ENTRY("takeControl");
		
		
		checkOperationMode();
		
		
		unsigned long action = TA_Base_Bus::aca_PLAN_CHANGE_PLAN_OWNER;
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to take control of Plan[" << plan.plan << ":" << plan.instance
			<< "]";
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		// TODO: talk to the current controllee first, then do this:
		try
		{
			PlanExecutor::instance()->reassign( session, pmId, plan );
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Cannot take control"));
		}
        FUNCTION_EXIT;
	}
	
	
	void PlanAgentCorbaDefImpl::customiseStep(const char* session, const TA_Base_Core::ActivePlanId& plan, const TA_Base_Core::StepCustomisableDetail& detail)
	{
		FUNCTION_ENTRY("customiseStep");
		
		checkOperationMode();
		
		
		unsigned long action = TA_Base_Bus::aca_PLAN_CUSTOMISE_PLAN;
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to customise step[" << plan.plan << ":" << plan.instance
			<< "]";
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
        {
			TA_Base_Core::EActivePlanState planState =  ActivePlanBulletinBoard::instance()->getState( plan );
			if ( planState != TA_Base_Core::PAUSED_ACTIVE_PLAN_STATE && planState != TA_Base_Core::PENDING_ACTIVE_PLAN_STATE )
			{
				TA_THROW( TA_Base_Core::PlanAgentException ("An active plan can only be customised in PAUSED or PENDING state.", TA_Base_Core::PAE_WRONG_STATE_TO_CUSTOMISE_ACTIVE_PLAN) );
			}
			PlanExecutor::instance()->customiseStep( plan, detail );
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Cannot customise step"));
		}
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getPlanExecutionHistory(const TA_Base_Core::ActivePlanId& plan, TA_Base_Core::ExecutionHistory_out history)
	{
		FUNCTION_ENTRY("getPlanExecutionHistory");

		checkOperationMode();

		try
		{
			history = ActivePlanBulletinBoard::instance()->getPlanExecutionHistory( plan);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unhandled exception in getPlanExecutionHistory()."));
		}
        FUNCTION_EXIT;
	}
    
	
	void PlanAgentCorbaDefImpl::getPlanCustomisationHistory(const TA_Base_Core::ActivePlanId& plan, TA_Base_Core::CustomisationHistory_out history)
	{
		FUNCTION_ENTRY("getPlanCustomisationHistory");
		
		checkOperationMode();
		
		
		try
		{
			history = ActivePlanBulletinBoard::instance()->getPlanCustomisationHistory( plan);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unhandled exception in getPlanCustomisationHistory()."));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::setPlanApprovalState(const char* session, TA_Base_Core::NodeId plan, TA_Base_Core::EApprovalState state)
	{
		FUNCTION_ENTRY("setPlanApprovalState");
		
		checkOperationMode();
		
		
		unsigned long action = TA_Base_Bus::aca_PLAN_APPROVE_PLAN;
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to set approval state of Plan[" << plan << "]";
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
        try
        {
            PlanDataWriter::instance()->setPlanApprovalState(session, plan, state);
        }
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Cannot set plan approval state"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getRootNodeChildren(TA_Base_Core::SiblingNodes_out children)
	{	
		FUNCTION_ENTRY("getRootNodeChildren");
		
		checkOperationMode();
		
		
		try
		{
			children = TA_Base_Bus::PlanDataReader::instance()->getChildren( TA_Base_Core::ROOT_NODE_ID);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getChildren(TA_Base_Core::NodeId parent, TA_Base_Core::SiblingNodes_out children)
	{
		FUNCTION_ENTRY("getChildren");
		
		
		checkOperationMode();
		
		try
		{
			children = TA_Base_Bus::PlanDataReader::instance()->getChildren( parent);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getNodeDetail(TA_Base_Core::NodeId node, TA_Base_Core::NodeDetail_out detail)
	{
		FUNCTION_ENTRY("getNodeDetail");
		
		
		checkOperationMode();
		
		try
		{
			detail = TA_Base_Bus::PlanDataReader::instance()->getNodeDetail( node);
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getNodePath(TA_Base_Core::NodeId node, TA_Base_Core::NodePath_out path)
	{
		FUNCTION_ENTRY("getNodePath");
		
		
		checkOperationMode();
		
		try
		{
			path = CORBA::string_dup( TA_Base_Bus::PlanDataReader::instance()->getNodePath( node).c_str());
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
        FUNCTION_EXIT;
	}
	
    void PlanAgentCorbaDefImpl::getNodeIdsInNodePath(TA_Base_Core::NodeId plan, TA_Base_Core::NodeIds_out plans)
	{
		FUNCTION_ENTRY("getNodeIdsInNodePath");
		
		
		checkOperationMode();
		
		try
		{
			plans = TA_Base_Bus::PlanDataReader::instance()->getNodeIdsInNodePath( plan);
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
        FUNCTION_EXIT;
	}
	
    TA_Base_Core::NodeId PlanAgentCorbaDefImpl::getNodeId(const char* path)
    {
		FUNCTION_ENTRY("getNodeId");
		
		
		checkOperationMode();
		
		
        TA_Base_Core::NodeId nodeId = TA_Base_Bus::PlanDataReader::instance()->getNodeId(path);
        FUNCTION_EXIT;
        return nodeId;
    }
	
	void PlanAgentCorbaDefImpl::getNodeSummary(TA_Base_Core::NodeId node, TA_Base_Core::NodeSummary_out summary)
	{
		FUNCTION_ENTRY("getNodeSummary");
		
		
		checkOperationMode();
		
		try
		{
			summary = TA_Base_Bus::PlanDataReader::instance()->getNodeSummary(node);
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
		
        FUNCTION_EXIT;
	}
	
    void PlanAgentCorbaDefImpl::getStepNumber(TA_Base_Core::StepId step, TA_Base_Core::StepNumber& position)
	{
		FUNCTION_ENTRY("getStepNumber");
		
		checkOperationMode();
		
		try
		{
			position = TA_Base_Bus::PlanDataReader::instance()->getStepNumber(step);
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
		
        FUNCTION_EXIT;
	}
	
	
	void PlanAgentCorbaDefImpl::getActivePlanDetail(TA_Base_Core::NodeId plan, TA_Base_Core::ActivePlanDetails_out details)
	{
		FUNCTION_ENTRY("getActivePlanDetail");
		checkOperationMode();
		
		try
		{
			details = ActivePlanBulletinBoard::instance()->getActivePlanDetail(plan) ;
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Cannot get active plan detail"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getAssocAlarmPlanDetail(const char* alarmId, TA_Base_Core::ActivePlanDetail_out detail)
	{
		FUNCTION_ENTRY("getAssocAlarmPlanDetail");
		checkOperationMode();
		
		try
		{
			detail = ActivePlanBulletinBoard::instance()->getAssocAlarmActivePlanDetail (alarmId);
		}
		catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Cannot get active plan detail"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getActivePlanDetailByName(const char* path, TA_Base_Core::ActivePlanDetails_out details)
	{
		FUNCTION_ENTRY("getActivePlanDetailByName");
		
		checkOperationMode();
		
        getActivePlanDetail(getNodeId(path), details);
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getAllActivePlanDetails(TA_Base_Core::ActivePlanDetails_out details)
	{
		FUNCTION_ENTRY("getAllActivePlanDetails");
		checkOperationMode();
		
		try
		{
			details = ActivePlanBulletinBoard::instance()->getActivePlanDetail(false);
		}
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Cannot get all active plan details"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getEditPlanLock(const char* session, const char* pmId, TA_Base_Core::NodeId plan)
	{
		FUNCTION_ENTRY("getEditPlanLock");
		
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to edit Plan[" << plan << "]";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_PLAN;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->getEditPlanLock(session, pmId, plan);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Cannot get plan lock"));
		}
		
        FUNCTION_EXIT;
	}
	
	
	void PlanAgentCorbaDefImpl::releaseEditPlanLock(const char* session, TA_Base_Core::NodeId plan)
	{
		FUNCTION_ENTRY("releaseEditPlanLock");
		
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to release lock on Plan[" << plan << "]";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_PLAN;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->releaseEditPlanLock(session, plan);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch( const std::exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, typeid(e).name(), e.what(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Cannot release lock"));
		}
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getStepNames(TA_Base_Core::StepNames_out names)
	{
		FUNCTION_ENTRY("getStepNames");
		checkOperationMode();
		try
		{
			names = TA_Base_Bus::PlanDataReader::instance()->getStepNames();
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getAllStepDetails(TA_Base_Core::NodeId plan, TA_Base_Core::StepDetails_out details)
	{
		FUNCTION_ENTRY("getAllStepDetails");
		
		checkOperationMode();
		
		try
		{
			details = TA_Base_Bus::PlanDataReader::instance()->getAllStepDetails( plan);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getSpecifiedStepDetails(TA_Base_Core::NodeId plan, const TA_Base_Core::StepIds& steps, TA_Base_Core::StepDetails_out details)
	{
		FUNCTION_ENTRY("getSpecifiedStepDetails");
		
		checkOperationMode();
		
		try
		{
			details = TA_Base_Bus::PlanDataReader::instance()->getSpecifiedStepDetails( plan, steps);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getParameterNames(TA_Base_Core::EStep stepType, TA_Base_Core::ParameterNames_out names)
	{
		FUNCTION_ENTRY("getParameterNames");
		
		checkOperationMode();
		
		try
		{
			names = TA_Base_Bus::PlanDataReader::instance()->getParameterNames( stepType);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getStepIdParameters(TA_Base_Core::StepId step, TA_Base_Core::StepParameters_out parameters)
	{
		FUNCTION_ENTRY("getStepIdParameters");
		checkOperationMode();
		
		try
		{
			parameters = TA_Base_Bus::PlanDataReader::instance()->getStepParameters( 0, step);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::getStepNumberParameters(TA_Base_Core::NodeId plan, TA_Base_Core::StepNumber step, TA_Base_Core::StepParameters_out parameters)
	{
		FUNCTION_ENTRY("getStepNumberParameters");
		
		checkOperationMode();
		
		try
		{
			parameters = TA_Base_Bus::PlanDataReader::instance()->getStepParameters( plan, step, true);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
        FUNCTION_EXIT;
	}
	
	
	void PlanAgentCorbaDefImpl::updateCategoryDetail(const char* session, const TA_Base_Core::CategoryDetail& detail)
	{
		FUNCTION_ENTRY("updateCategoryDetail");
		
		checkOperationMode();
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_CATEGORY;
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to edit category[" << detail.name.in() << "]";
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->updateCategory(session, detail);
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch (const TA_Base_Core::DataException& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "DataException", e.what());
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown Exception in updateCategory()"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::insertCategoryIntoRoot(const char* session)
	{
		FUNCTION_ENTRY("insertCategoryIntoRoot");
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to create category.";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_CATEGORY;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->insertCategory(session, TA_Base_Core::ROOT_NODE_ID);
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch (const TA_Base_Core::DataException& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "DataException", e.what());
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown Exception in insertCategoryIntoRoot()"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::insertCategory(const char* session, TA_Base_Core::NodeId parent)
	{
		FUNCTION_ENTRY("insertCategory");
		
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to create category.";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_CATEGORY;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->insertCategory(session, parent);
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch (const TA_Base_Core::DataException& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "DataException", e.what());
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown Exception in insertCategory()"));
		}
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::deleteCategory(const char* session, TA_Base_Core::NodeId category)
	{
		FUNCTION_ENTRY("deleteCategory");
		
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to delete a category[" << category << "]";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_CATEGORY;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->deleteCategory( session, category);
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch (const TA_Base_Core::DataException& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "DataException", e.what());
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown Exception in deleteCategory()"));
		}
        FUNCTION_EXIT;
		
	}
	
	void PlanAgentCorbaDefImpl::updatePlanDetail(const char* session, const TA_Base_Core::PlanDetail& detail)
	{
		FUNCTION_ENTRY("updatePlanDetail");
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to edit Plan[" << detail.name.in() << "]";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_PLAN;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->updatePlanDetail( session, detail);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch (const TA_Base_Core::DataException& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "DataException", e.what());
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown Exception in updatePlanDetail()"));
		}
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::updatePlan(const char* session, const TA_Base_Core::Plan& plan)
	{
		FUNCTION_ENTRY("updatePlan");
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to edit Plan[" << plan.detail.name.in() << "]";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_PLAN;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->updatePlan( session, plan);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch (const TA_Base_Core::DataException& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "DataException", e.what());
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown Exception in updatePlan()"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::insertPlanIntoRoot(const char* session)
	{
		FUNCTION_ENTRY("insertPlanIntoRoot");
		
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to create Plan.";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_PLAN;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->insertPlan( session, TA_Base_Core::ROOT_NODE_ID);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch (const TA_Base_Core::DataException& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "DataException", e.what());
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown Exception in insertPlanIntoRoot()"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::insertPlan(const char* session, TA_Base_Core::NodeId parent)
	{
		FUNCTION_ENTRY("insertPlan");
		
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to create Plan.";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_PLAN;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		
		try
		{
			PlanDataWriter::instance()->insertPlan(session, parent);
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch (const TA_Base_Core::DataException& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "DataException", e.what());
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown Exception in insertPlan()"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::deletePlans(const char* session, const TA_Base_Core::NodeIds& plans)
	{
		FUNCTION_ENTRY("deletePlans");
		
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to delete Plan.";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_PLAN;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->deletePlans( session, plans);
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch (const TA_Base_Core::DataException& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "DataException", e.what());
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown Exception in deletePlans()"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::movePlanToRoot(const char* session, TA_Base_Core::NodeId plan, bool useForce)
	{
		FUNCTION_ENTRY("movePlanToRoot");
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to edit Plan[" << plan << "]";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_PLAN;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->movePlan( session, plan, TA_Base_Core::ROOT_NODE_ID, useForce);
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch (const TA_Base_Core::DataException& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "DataException", e.what());
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown Exception in movePlanToRoot()"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::movePlan(const char* session, TA_Base_Core::NodeId fromPlan, TA_Base_Core::NodeId toParent, bool useForce)
	{
		FUNCTION_ENTRY("movePlan");
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to move Plan[" << fromPlan << "]";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_PLAN;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->movePlan( session, fromPlan, toParent, useForce);
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch (const TA_Base_Core::DataException& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "DataException", e.what());
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown Exception in movePlan()"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::copyPlanToRoot(const char* session, TA_Base_Core::NodeId plan, bool useForce)
	{
		FUNCTION_ENTRY("copyPlanToRoot");
		
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to copy Plan[" << plan << "]";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_PLAN;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->copyPlan( session, plan, TA_Base_Core::ROOT_NODE_ID, useForce);
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch (const TA_Base_Core::DataException& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "DataException", e.what());
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown Exception in copyPlanToRoot()"));
		}
		
        FUNCTION_EXIT;
		
	}
	
	void PlanAgentCorbaDefImpl::copyPlan(const char* session, TA_Base_Core::NodeId fromPlan, TA_Base_Core::NodeId toParent, bool useForce)
	{
		FUNCTION_ENTRY("copyPlan");
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to copy Plan[" << fromPlan << "]";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_PLAN;
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->copyPlan( session, fromPlan, toParent, useForce);
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
		catch (const TA_Base_Core::DataException& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "DataException", e.what());
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown Exception in copyPlan()"));
		}
		
        FUNCTION_EXIT;
	}
	
	
	void PlanAgentCorbaDefImpl::getNextStepId(const char* session, TA_Base_Core::StepId& step)
	{
		FUNCTION_ENTRY("getNextStepId");
		checkOperationMode();
		
		try
		{
			step = TA_Base_Bus::PlanDataReader::instance()->getNextPlanSeqNumber();
		}
        catch (const TA_Base_Core::PlanStepDetailException& e)
        {
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanStepDetailError(e.getStepNumber(), e.getDetailType(), e.getErrorType(), e.what()));
		}
        catch (const TA_Base_Core::PlanAgentException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(e.getErrorType(), e.getItemId(), e.what()));
        }
        catch ( const TA_Base_Core::DataException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
        }
        catch ( const TA_Base_Core::DatabaseException& e)
        {
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
        }
		catch( const std::exception& e)
		{
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
            FUNCTION_EXIT;
            TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
		
        FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::exportPlan (const char* session, TA_Base_Core::AuxPlanDetail_out plan, TA_Base_Core::NodeId planId)
	{
		FUNCTION_ENTRY("exportPlan");
		
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to export this plan";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_PLAN;//same permission as for edit plan
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
			FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			plan = PlanDataWriter::instance()->exportPlan (session, planId);
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
			FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch ( const TA_Base_Core::DataException& e)
		{
			FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch ( const TA_Base_Core::DatabaseException& e)
		{
			FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
		}
		catch( const std::exception& e)
		{
			FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
			FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
			FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
		
		FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::importPlan (const char* session, const TA_Base_Core::AuxPlanDetail& plan, TA_Base_Core::NodeId parentId)
	{
		FUNCTION_ENTRY("importPlan");
		
		checkOperationMode();
		
		std::string reason;
		std::ostringstream message;
		
		message << "Owner:" << ActivePlanBulletinBoard::instance()->getOwner(session).c_str()
			<< " does not have rights to import plans";
		
		unsigned long action = TA_Base_Bus::aca_PLAN_EDIT_PLAN;//same permission as for edit plan
		
		if ( !ActivePlanBulletinBoard::instance()->isActionPermitted(session, action, reason))
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, INFO_LOG_LEVEL, message.str().c_str());
            FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION (TA_Base_Bus::IPlanAgentCorbaDef::NoPermission(reason.c_str()));
		}
		
		try
		{
			PlanDataWriter::instance()->importPlan (session, plan, parentId);
		}
		catch( const TA_Base_App::PlanNotFoundException& e)
		{
			FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION(TA_Base_Bus::IPlanAgentCorbaDef::PlanNotFoundError(e.getErrorType(), e.getPlanId(), e.getInstanceId(), e.what()));
		}
		catch ( const TA_Base_Core::DataException& e)
		{
			FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATA_ERROR, 0, e.what()));
		}
		catch ( const TA_Base_Core::DatabaseException& e)
		{
			FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_DATABASE_ERROR, 0, e.what()));
		}
		catch( const std::exception& e)
		{
			FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, e.what()));
		}
		catch( const CORBA::Exception& e)
		{
			LOG( SOURCE_INFO, EXCEPTION_DETAIL_LOG_TYPE, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str(), "Unhandled.");
			FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError( TA_Base_Core::PAE_UNKNOWN_ERROR, 0, TA_Base_Core::CorbaUtil::getInstance().exceptionToString(e).c_str()));
		}
		catch( ...)
		{
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown", "Unhandled.");
			FUNCTION_EXIT;
			TA_THROW_CORBA_EXCEPTION( TA_Base_Bus::IPlanAgentCorbaDef::PlanAgentError(TA_Base_Core::PAE_UNKNOWN_ERROR, 0, "Unknown error"));
		}
		
		FUNCTION_EXIT;
	}
	
	void PlanAgentCorbaDefImpl::checkOperationMode()
	{
		TA_ASSERT(m_parentClass != NULL, "The parent class is NULL");
		m_parentClass->checkOperationMode();
	}
} // TA_Base_App



