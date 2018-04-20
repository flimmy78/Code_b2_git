/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  *
  * Source:    $File$
  * @author:   Dirk McCormick
  * @version:  $Revision$
  *
  * Last modification: $DateTime$
  * Last modified by:  $Author$
  *
  * This class implements the IJob interface by extending the AbstractJob class
  * to create a Job that can be used to run plans.
  *
  */


#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/TAAssert.h"
#include "core/corba/src/CorbaUtil.h"
#include "app/scheduling/scheduling_agent/src/JobInstanceNotFoundException.h"
#include "app/scheduling/scheduling_agent/src/JobInstanceStateRetrievalException.h"
#include "app/scheduling/scheduling_agent/src/PlanRunnerJobInstance.h"
#include "app/scheduling/scheduling_agent/src/PlanRunnerJobFactory.h"
#include "core/exceptions/src/DataException.h"
#include "core/exceptions/src/DatabaseException.h"

#include "app/scheduling/scheduling_agent/src/PlanRunnerJob.h"

using TA_Base_Core::DatabaseException;
using TA_Base_Core::DataException;
using TA_Base_Core::DebugUtil;
using TA_Base_Core::CorbaUtil;
using TA_Base_Bus::PlanAgentLibrary;

namespace TA_Base_App
{


const std::string PlanRunnerJob::JOB_TYPE = "Plan";
const std::string PlanRunnerJob::PLAN_PATH_PARAMETER_NAME = "PlanPath";



IJobInstance* PlanRunnerJob::createJobInstance(
    unsigned long minuteStarted)
{
    FUNCTION_ENTRY("createJobInstance");

    return new PlanRunnerJobInstance(this, minuteStarted);
}

IJobInstance::JobInstanceState PlanRunnerJob::getJobInstanceState(
    unsigned long minuteStarted,
    std::string& errorMessage)
{
    FUNCTION_ENTRY("getJobInstanceState");


    CORBA::ULong instanceID = 0;
    PlanRunnerJobInstance jobInstance(this, minuteStarted);

    //
    // Get the plan details from the Plan Agent
    //
    TA_Base_Core::ActivePlanDetails_var activePlanDetails;

    try
    {
        // throws DatabaseException, JobInstanceNotFoundException
        instanceID = jobInstance.getInstanceIDFromDB();

		// TD #12032
		// Get location specific plan agent
        //PlanAgentLibrary* planAgent = PlanRunnerJobFactory::getPlanAgent();
        PlanAgentLibrary* planAgent = PlanRunnerJobFactory::getPlanAgent(getLocationID());

        planAgent->getActivePlanDetailByName(getPlanPath().c_str(), activePlanDetails);

        std::stringstream message;
        message << "There are " << activePlanDetails->length() << " "
                << "Active plan details for plan " << getPlanPath() << " "
                << "(job ID " << getID() << ")";

        LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, message.str().c_str());
    }
    catch(const DatabaseException& ex)
    {
        TA_THROW(JobInstanceStateRetrievalException(ex.what()));
    }
    catch(const CORBA::Exception& ex)
    {
        std::string message = "Corba Exception: "
                            + CorbaUtil::getInstance().exceptionToString(ex);

        TA_THROW(JobInstanceStateRetrievalException(message));
    }
    catch(...)
    {
        TA_THROW(JobInstanceStateRetrievalException());
    }



    //
    // The Plan Agent returns all plans with a particular ID,
    // so we need to find the plan with the instance ID matching
    // the one we retrieved from the database.
    //
    for(unsigned int i = 0; i < activePlanDetails->length(); i ++)
    {
        const TA_Base_Core::ActivePlanDetail& activePlanDetail = activePlanDetails[i];

        if(activePlanDetail.plan.instance == instanceID)
        {
            //
            // Return the appropriate JobInstanceState
            //
            switch(activePlanDetail.activePlanState)
            {
				// marvin++
				// TD13442
				LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo,
						"Active Plan State %d",activePlanDetail.activePlanState);
				// ++marvin
				// TD13442

                case TA_Base_Core::PENDING_ACTIVE_PLAN_STATE:
                {
                    return IJobInstance::NotStarted;
                }

                case TA_Base_Core::EXECUTING_ACTIVE_PLAN_STATE:
                case TA_Base_Core::PAUSED_ACTIVE_PLAN_STATE:
                case TA_Base_Core::OPERATOR_PAUSED_ACTIVE_PLAN_STATE:
				// marvin++
				// TD13442
				case TA_Base_Core::DELAYED_ACTIVE_PLAN_STATE:
				case TA_Base_Core::NEW_OWNER_ACTIVE_PLAN_STATE:
				// ++marvin
				// TD13442
                {
                    return IJobInstance::Started;
                }


                case TA_Base_Core::STOPPED_ACTIVE_PLAN_STATE:
                {
                    errorMessage = "The plan was forcibly stopped.";
                    return IJobInstance::Completed;
                }
                case TA_Base_Core::ABORTED_ACTIVE_PLAN_STATE:
                {
                    errorMessage = "The plan was aborted.";
                    return IJobInstance::Completed;
                }
                case TA_Base_Core::COMPLETED_ACTIVE_PLAN_STATE:
                case TA_Base_Core::EXPIRED_ACTIVE_PLAN_STATE:
                {
                    return IJobInstance::Completed;
                }


                case TA_Base_Core::UNDEFINED_ACTIVE_PLAN_STATE:
                case TA_Base_Core::FAILED_ACTIVE_PLAN_STATE:
                {
                    //
                    // These states should never be returned by the plan
                    // agent.
                    //
                    TA_ASSERT(false, "Plan in illegal state");
                }
                default:
                {
                    TA_ASSERT(false, "Plan in unknown state");
                }
            }

        }// if(activePlanDetails[i].instance == instanceID)

    }// for(unsigned int i = 0; i < activePlanDetails.length(); i ++)


    //
    // The state should have been returned before this point.
    // It hasn't, so throw an exception.
    //
    std::stringstream errorMessageStream;
    errorMessageStream <<
        "Plan " << getPlanPath() <<
        " does not have an instance with ID " << instanceID;

    TA_THROW( JobInstanceNotFoundException(errorMessageStream.str()) );
}



TA_Base_Bus::SchedulingAgentCorbaDef::JobCorbaDef PlanRunnerJob::toCorbaObject()
{
    TA_Base_Bus::SchedulingAgentCorbaDef::JobCorbaDef job = AbstractJob::toCorbaObject();

    return job;
}


std::string PlanRunnerJob::getPlanPath()
{
    return getParameter(PLAN_PATH_PARAMETER_NAME);
}


void PlanRunnerJob::updateJob(const TA_Base_Bus::SchedulingAgentCorbaDef::JobCorbaDef& job)
{
    AbstractJob::updateJob(job);
}



PlanRunnerJob::~PlanRunnerJob()
{
    FUNCTION_ENTRY("~PlanRunnerJob");
}



PlanRunnerJob::PlanRunnerJob(
    const TA_Base_Bus::SchedulingAgentCorbaDef::JobCorbaDef& job)
    :
    AbstractJob(job)
{
    FUNCTION_ENTRY("PlanRunnerJob");
}


PlanRunnerJob::PlanRunnerJob(const TA_Base_Bus::SchedulingAgentCorbaDef::JobID& jobID)
    :
    AbstractJob(jobID)
{
}




}; // TA_Base_App
