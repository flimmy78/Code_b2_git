#ifndef __MFT_TERMINATE_PLAN_STEP_COMPONENT_H_
#define __MFT_TERMINATE_PLAN_STEP_COMPONENT_H_

#include "ace/RW_Mutex.h"
#include "ace/Singleton.h"
#include "app/response_plans/plan_step_plugin/common_editor/src/EditorStepComponent.h"
#include "app/response_plans/plan_editor_plugin/workflow_element/src/IActivityComponent.h"

namespace TA_Base_App
{
    class  MftTerminatePlanStepComponentImpl: public EditorStepComponent, public IActivityComponent
    {
        
    public:
        friend class ACE_Singleton<MftTerminatePlanStepComponentImpl, ACE_Recursive_Thread_Mutex>;

		virtual PlanStep* createStep( IPlanNode* parent, BasicParameter& stepDetail );
		virtual PlanStep* createStep( IPlanNode* parent, const unsigned long stepId, const int stepType );

		virtual InteractiveStep* createExecutableStep( const unsigned int unId, const int eType, const unsigned int ulLocation, const unsigned int ulPlanId, 
			const unsigned int ulInstanceNum, const unsigned int ulStepNum, const std::vector<std::string>& vecParameters );

        virtual IActivityComponent& getActivityComponent();

        virtual bool readonly();
        virtual int getStepType();
        virtual int getAccessType();
		virtual CreateActivitycPtr getActivityCreationFuncPtr();
		virtual std::vector<std::pair<std::string, std::vector<int>>> getShortcuts();
        virtual std::string getName();
        virtual std::string getResource();
        virtual std::string getCatagroyName();

        static WorkflowActivity* createWorkflowActivity();

    private:
        MftTerminatePlanStepComponentImpl();
        ~MftTerminatePlanStepComponentImpl();
        MftTerminatePlanStepComponentImpl( const MftTerminatePlanStepComponentImpl& );
        MftTerminatePlanStepComponentImpl& operator=( const MftTerminatePlanStepComponentImpl& );

    };

    typedef ACE_Singleton<MftTerminatePlanStepComponentImpl, ACE_Recursive_Thread_Mutex> MftTerminatePlanStepComponent;
}

#endif