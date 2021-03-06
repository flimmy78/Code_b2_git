/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/response_plans/plan_agent/src/ActiveVmsBlankoutStep.cpp $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2008/11/28 16:26:01 $
  *  Last modified by:  $Author: builder $
  *
  *  Implementation of .
  */

#include "PlanAgent.h"

// namespace alias for Corba structures/types

#if defined ( STEPTYPE_VMS_BLANKOUT )
 
namespace TA_Base_App
{

	ActiveVmsBlankoutStep::ActiveVmsBlankoutStep( const TA_Base_Core::StepDetail& stepDetail, 
													const TA_Base_Core::VmsBlankoutParameters& params,
													IActivePlanFlow& flowControl ) :
		ActiveStep(stepDetail, flowControl),
		m_params(params),
		m_flowControl(flowControl)
	{
	}

	TA_Base_Core::EActiveStepState ActiveVmsBlankoutStep::executeImpl( void )
	{
		LOG( SOURCE_INFO, GENERIC_LOG_TYPE, DEBUG_LOG_LEVEL, "Data Point Set step %lu", getStepNumber() );

		TA_Base_Core::EActiveStepState stepState = TA_Base_Core::EXECUTED_ACTIVE_STEP_STATE;

		m_remark = "Step executed.";
		
		std::string message;

        std::ostringstream msg;

        TA_Base_Core::NamedObject< TA_Base_App::TA_Signs::ISignFactoryCorbaDef, TA_Base_App::TA_Signs::ISignFactoryCorbaDef_ptr, TA_Base_App::TA_Signs::ISignFactoryCorbaDef_var> signFactory; 
        TA_Base_Core::CorbaName name = TA_Base_Core::EntityAccessFactory::getInstance().getCorbaNameOfEntity( "VmsAgent");
        signFactory.setCorbaName( name.getAgentName(), "VMS/SignFactory" );

        try
        {
			TA_Base_App::TA_Signs::SignObjectSeq* signObjSeq ;
			CORBA_CALL_RETURN( signObjSeq,
			                   signFactory,
			                   getAll,
			                   () );
            int numberOfSigns = signObjSeq->length();
            bool foundSign = false;

            for ( int i=0; i < numberOfSigns; i++ )
            {
                TA_Base_App::TA_Signs::SignObject so = signObjSeq->operator[](i);
                if ( so.entityKey == m_params.vmsSign )
                {
                    std::string session = ActivePlanBulletinBoard::instance()->getSession(m_flowControl.getPlan());
                    so.id->blank(session.c_str());
					foundSign = true;
                    break;
                }
            }

            if ( !foundSign )
            {
                m_remark = "The sign was not found.";
                stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;
                return stepState;
            }

            //On successful completion of the step
            m_flowControl.setNextStep();  
            return( stepState );
        }

        catch ( const TA_Base_App::TA_Signs::SignOperationFailed& e)
        {
            m_remark = "Sign operation failed";
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "TA_Base_Core::SignOperationFailed", e.reason );
			stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;
                                   
        }

        catch ( TA_Base_App::TA_Signs::SignCommunicationError& e)
        {
            m_remark = "Sign communication error";
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "TA_Base_Core::SignCommunicationError", e.reason );
			stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;            
        }

        catch ( TA_Base_App::TA_Signs::PermissionDenied& e)
        {
            m_remark = "Permission denied";
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "TA_Base_Core::PermissionDenied", e.reason );
			stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;                        
        }

		catch( const TA_Base_Core::ObjectResolutionException& e )
		{
			msg << dumpContext() << ": "
			    << e.what();

            m_remark = "The sign is not accessible.";

			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "TA_Base_Core::ObjectResolutionException", msg.str().c_str() );
			stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;
		}
		catch( const ActiveStepParamException& e )
		{
			msg << dumpContext() << ": "
			    << e.what();

            m_remark = "Wrong step parameter";
			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "TA_Base_App::ActiveStepParamException", msg.str().c_str() );
			stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;
		}
		catch( ... )
		{
			msg << dumpContext() << ": ";
            m_remark = "Failed to perform sign operation.";

			LOG( SOURCE_INFO, EXCEPTION_CATCH_LOG_TYPE, "Unknown Exception caught", msg.str().c_str() );
			stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;
		}

		return( stepState );
	}
} // TA_Base_App

#endif //  STEPTYPE_VMS_BLANKOUT
