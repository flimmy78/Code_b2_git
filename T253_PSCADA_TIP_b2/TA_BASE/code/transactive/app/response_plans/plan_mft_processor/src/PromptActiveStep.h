/**
  * The source code in this file is the property of Ripple Systems and is not for redistribution in any form.
  *
  * Source:   $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/app/response_plans/plan_mft_processor/src/PromptActiveStep.h $
  * @author:  Huang Jian
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2017/10/31 16:21:54 $
  * Last modified by:  $Author: CM $
  *
  **/

#pragma once

#include "app/response_plans/plan_mft_processor/src/ActivePlanStep.h"

namespace TA_Base_App
{
    class CPromptDlg;

    class PromptActiveStep: public TA_Base_App::ActivePlanStep
    {
        // Operations
    public:
        PromptActiveStep(const TA_Base_Core::CurrentPlanStepDetail& stepDetail);

        // ActivePlanStep interface
        virtual void execute();
        virtual void stop();

        virtual ~PromptActiveStep();

    protected:
        virtual void launch();

    private:
        TA_Base_App::CPromptDlg* m_pPromptDlg;
    };

}
