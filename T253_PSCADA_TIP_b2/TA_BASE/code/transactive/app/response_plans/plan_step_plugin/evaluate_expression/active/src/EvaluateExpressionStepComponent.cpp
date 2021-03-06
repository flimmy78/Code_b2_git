#include "EvaluateExpressionStepComponent.h"
#include "ActiveEvaluateExpressionStep.h"
//#include "ActivePlanLogStepMessage.h"

namespace TA_Base_App
{


    ActiveStep* EvaluateExpressionStepComponentImpl::createActiveStep(const BasicParameter& detail, TA_Base_App::IActivePlan& flowControl)
    {
        return new TA_Base_App::ActiveEvaluateExpressionStep(detail, flowControl);
    }

    void EvaluateExpressionStepComponentImpl::validateStepParameter(const std::vector<std::string>& parameters)
    {

    }

    /*IActiveStepMessage* EvaluateExpressionStepComponentImpl::createPlanStepMessage( const unsigned long ulStepNum, const std::vector<std::string>& vecData )
    {
        return new TA_Base_App::ActivePlanLogStepMessage(ulStepNum, vecData);
    }*/

    EvaluateExpressionStepComponentImpl::EvaluateExpressionStepComponentImpl()
    {

    }

    EvaluateExpressionStepComponentImpl::~EvaluateExpressionStepComponentImpl()
    {

    }

}