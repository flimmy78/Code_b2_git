#ifndef ACTIVE_PLAN_LAUNCH_GUI_APP_STEP_HEADER_INCLUDED
#define ACTIVE_PLAN_LAUNCH_GUI_APP_STEP_HEADER_INCLUDED
/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/response_plans/plan_agent/src/ActivePlanLaunchGuiAppStepMessage.h $
  *  @author:  Bart Golab
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2008/11/28 16:26:01 $
  *  Last modified by:  $Author: builder $
  *
  *  Generated when the result of a Launch GUI App interactive step execution request
  *  is received back from the Plan Manager.
  */
namespace TA_Base_App
{
    class ActivePlanLaunchGuiAppStepMessage : public IActivePlanMessage
    {
    //public methods
    public:
        ActivePlanLaunchGuiAppStepMessage(TA_Base_Core::EPlanStepCompletionStatus status, const std::string& error);
        virtual ~ActivePlanLaunchGuiAppStepMessage();
        
        virtual void execute( ActivePlan& activePlan ) const;
    
    private:
        ActivePlanLaunchGuiAppStepMessage& operator=( const ActivePlanLaunchGuiAppStepMessage& );
        ActivePlanLaunchGuiAppStepMessage( const ActivePlanLaunchGuiAppStepMessage& );

        TA_Base_Core::EPlanStepCompletionStatus m_status;
        std::string m_error;
    };

}

#endif //ACTIVE_PLAN_LAUNCH_GUI_APP_STEP_HEADER_INCLUDED
