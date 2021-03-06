#pragma once

#include "app/response_plans/plan_editor_plugin/workflow_element/src/BitmapActivity.h"

namespace TA_Base_App
{

class TaskRunPlan : public BitmapActivity
{
public:
    TaskRunPlan();
    virtual ~TaskRunPlan();

protected:
	virtual void serializeAddons( Stringification& ioSerilization );

public:
    static const std::string DisplayName;
    static const std::string Name;
    static const std::string Resource;
};

}


