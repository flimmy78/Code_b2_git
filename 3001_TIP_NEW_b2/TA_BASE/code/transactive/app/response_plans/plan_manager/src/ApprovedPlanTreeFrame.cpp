//
// The source code in this file is the property of
// Ripple Systems and is not for redistribution
// in any form.
//
// Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/response_plans/plan_manager/src/ApprovedPlanTreeFrame.cpp $
// @author:  Bart Golab
// @version: $Revision: #3 $
//
// Last modification: $DateTime: 2012/10/08 17:44:33 $
// Last modified by:  $Author: qi.huang $
//
// <description>

#include "app/response_plans/plan_manager/src/StdAfx.h"
#include "app/response_plans/plan_manager/src/PlanManager.h"
#include "app/response_plans/plan_manager/src/MainFrame.h"
#include "app/response_plans/plan_manager/src/ApprovedPlanTreeFrame.h"
#include "app/response_plans/plan_manager/src/ApprovedPlanTreeView.h"
#include "app/response_plans/plan_manager/src/LabelMaker.h"
#include "app/response_plans/plan_manager/src/ApplicationFont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace TA_Base_App;


/////////////////////////////////////////////////////////////////////////////
// CApprovedPlanTreeFrame

IMPLEMENT_DYNCREATE(CApprovedPlanTreeFrame, CPlanTreeFrame)

CApprovedPlanTreeFrame::CApprovedPlanTreeFrame()
{
    FUNCTION_ENTRY( "CApprovedPlanTreeFrame" );
    FUNCTION_EXIT;
}


CApprovedPlanTreeFrame::~CApprovedPlanTreeFrame()
{
    FUNCTION_ENTRY( "~CApprovedPlanTreeFrame" );
    FUNCTION_EXIT;
}


BEGIN_MESSAGE_MAP(CApprovedPlanTreeFrame, CPlanTreeFrame)
    // {{AFX_MSG_MAP(CApprovedPlanTreeFrame)
    ON_WM_CREATE()
    // }}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApprovedPlanTreeFrame message handlers

int CApprovedPlanTreeFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    FUNCTION_ENTRY( "OnCreate" );

    if (CPlanTreeFrame::OnCreate(lpCreateStruct) == -1)
    {
        FUNCTION_EXIT;
        return -1;
    }

    SetTitle(LabelMaker::getApprovedPlanTreeRootNodeLabel());

    // TODO: Add your specialized creation code here
    GetMainFrame()->AddPlanBrowserFrame(ID_VIEW_APPROVEDPLANS, this);

    ApplicationFont::getInstance().adjustChildrenFont( GetSafeHwnd() );

    FUNCTION_EXIT;
    return 0;
}


CRuntimeClass *CApprovedPlanTreeFrame::GetLeftPaneRuntimeClass()
{
    FUNCTION_ENTRY( "GetLeftPaneRuntimeClass" );
    FUNCTION_EXIT;
    return RUNTIME_CLASS(CApprovedPlanTreeView);
}


