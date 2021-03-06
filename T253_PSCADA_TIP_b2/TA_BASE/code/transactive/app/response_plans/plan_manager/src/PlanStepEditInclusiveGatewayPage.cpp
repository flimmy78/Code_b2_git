//
// The source code in this file is the property of
// Ripple Systems and is not for redistribution
// in any form.
//
// Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/response_plans/plan_manager/src/PlanStepEditActivePlanCheckPage.cpp $
// @author:  Andy Parker
// @version: $Revision: #2 $
//
// Last modification: $DateTime: 2012/02/06 16:15:14 $
// Last modified by:  $Author: haijun.li $
//
// <description>

#include "StdAfx.h"

#include "core/utilities/src/DebugUtil.h"
#include "app/response_plans/plan_editor_plugin/workflow_editor/src/GridEditorPage.h"
#include "Resource.h"
#include "PlanStepEditInclusiveGatewayPage.h"
#include "InclusiveGatewayStep.h"

namespace TA_Base_App
{

/////////////////////////////////////////////////////////////////////////////
// CPlanStepEditActivePlanCheckPage dialog
    
CPlanStepEditInclusiveGatewayPage::CPlanStepEditInclusiveGatewayPage(InclusiveGatewayStep* step) : 
CPlanStepEditParameterPage( IDD_PLAN_STEP_EDIT_INCLUSIVE_GATEWAY_DLG, step ),
m_pNextStepGrid( new GridEditorPage( *(step->getActivityParameter().getGridEditor( ParamStepExpressionPairs )), ParamStepExpressionPairs, this ))
{
    FUNCTION_ENTRY( "CPlanStepEditInclusiveGatewayPage" );

    // {{AFX_DATA_INIT(CPlanStepEditActivePlanCheckPage)
    // }}AFX_DATA_INIT

    FUNCTION_EXIT;
}

CPlanStepEditInclusiveGatewayPage::~CPlanStepEditInclusiveGatewayPage()
{
    FUNCTION_ENTRY( "~CPlanStepEditInclusiveGatewayPage" );

    delete m_pNextStepGrid;
    m_pNextStepGrid = NULL;

    FUNCTION_EXIT;
}

void CPlanStepEditInclusiveGatewayPage::DoDataExchange(CDataExchange* pDX)
{
    FUNCTION_ENTRY( "DoDataExchange" );

    CPlanStepEditParameterPage::DoDataExchange(pDX);
    // {{AFX_DATA_MAP(CPlanStepEditActivePlanCheckPage)
    // }}AFX_DATA_MAP

    FUNCTION_EXIT;
}

BEGIN_MESSAGE_MAP(CPlanStepEditInclusiveGatewayPage, CPlanStepEditParameterPage)
    // {{AFX_MSG_MAP(CPlanStepEditActivePlanCheckPage)
    ON_WM_DESTROY()
    // }}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlanStepEditActivePlanCheckPage message handlers

BOOL CPlanStepEditInclusiveGatewayPage::OnInitDialog()
{
    CPlanStepEditParameterPage::OnInitDialog();

    m_pNextStepGrid->createWnd( *this, true );

    RECT rtWndArea;
    GetWindowRect( &rtWndArea );
    ScreenToClient( &rtWndArea );
    m_pNextStepGrid->MoveWindow( &rtWndArea );

    return FALSE;
}

void CPlanStepEditInclusiveGatewayPage::OnDestroy()
{
    if ( NULL != m_pNextStepGrid)
    {
        if ( ::IsWindow( m_pNextStepGrid->GetSafeHwnd() ))
        {
            m_pNextStepGrid->DestroyWindow();
        }
    }

    CPlanStepEditParameterPage::OnDestroy();
}

void CPlanStepEditInclusiveGatewayPage::EnableParameterControls(bool enable)  // TD#614/1170/1409
{
    FUNCTION_ENTRY( "EnableParameterControls" );

    FUNCTION_EXIT;
}

void CPlanStepEditInclusiveGatewayPage::DisplayParameters()
{
    FUNCTION_ENTRY( "DisplayParameters" );

    InclusiveGatewayStep* step = dynamic_cast<InclusiveGatewayStep*>(GetPlanStep());
    TA_ASSERT( step != NULL, "Incorrect step type for the active plan check step page" );

    FUNCTION_EXIT;
}

void CPlanStepEditInclusiveGatewayPage::UpdateParameters()
{
    FUNCTION_ENTRY( "UpdateParameters" );

    // Load the initial values
    InclusiveGatewayStep* step = dynamic_cast<InclusiveGatewayStep*>(GetPlanStep());
    TA_ASSERT(step!=NULL,"Incorrect step type for the active plan check step page");

    FUNCTION_EXIT;
}

void CPlanStepEditInclusiveGatewayPage::OnSize( UINT nType, int cx, int cy )
{
    RECT rtWndArea;
    GetWindowRect( &rtWndArea );
    ScreenToClient( &rtWndArea );
    m_pNextStepGrid->MoveWindow( &rtWndArea );
}

}