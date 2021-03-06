//
// The source code in this file is the property of
// Ripple Systems and is not for redistribution
// in any form.
//
// Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/response_plans/plan_manager/src/ExecutableLogEntryStep.cpp $
// @author:  Bart Golab
// @version: $Revision: #1 $
//
// Last modification: $DateTime: 2018/03/14 13:51:20 $
// Last modified by:  $Author: lim.cy $
//
// <description>

#include "StdAfx.h"
#include "core/utilities/src/TAAssert.h"
#include "PlanManager.h"
#include "ExecutableLogEntryStep.h"
#include "LogEntryDlg.h"
#include "InteractiveStepException.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace TA_Base_App;


/////////////////////////////////////////////////////////////////////////////
// ExecutableLogEntryStep

ExecutableLogEntryStep::ExecutableLogEntryStep(const TA_Base_Core::CurrentPlanStepDetail& stepDetail) :
    InteractiveStep(stepDetail)
{
    FUNCTION_ENTRY( "ExecutableLogEntryStep" );

    TA_ASSERT(stepDetail.data._d() == TA_Base_Core::LOG_STEP, "Invalid step parameter type");

    FUNCTION_EXIT;
}


ExecutableLogEntryStep::~ExecutableLogEntryStep()
{
    FUNCTION_ENTRY( "~ExecutableLogEntryStep" );
    FUNCTION_EXIT;
}


void ExecutableLogEntryStep::launch()
{
    FUNCTION_ENTRY( "launch" );

    CLogEntryDlg* logEntryDlg = new CLogEntryDlg(getStepDetail());

    if (logEntryDlg->Create(IDD_LOG_ENTRY_DLG) == 0)
    {
        TA_THROW(InteractiveStepException("Failed to create Log step interaction dialog"));
    }

    FUNCTION_EXIT;
}


