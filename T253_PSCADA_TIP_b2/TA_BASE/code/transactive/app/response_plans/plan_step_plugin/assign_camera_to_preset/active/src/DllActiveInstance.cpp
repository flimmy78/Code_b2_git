#include "app/response_plans/plan_step_plugin/assign_camera_to_preset/active/src/AssignCameraToPresetStepComponent.h"
#include "app/response_plans/plan_step_plugin/common/src/ExportDef.h"

extern "C" Plan_Export TA_Base_App::IStepComponent* createStepComponent()
{
    return TA_Base_App::AssignCameraToPresetStepStepComponent::instance();
}