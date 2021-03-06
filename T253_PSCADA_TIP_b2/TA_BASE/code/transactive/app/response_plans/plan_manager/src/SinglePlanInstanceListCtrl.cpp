//
// The source code in this file is the property of
// Ripple Systems and is not for redistribution
// in any form.
//
// Source:   $File: //depot/TA_Product_ECSPlan/TA_BASE/transactive/app/response_plans/plan_manager/src/SinglePlanInstanceListCtrl.cpp $
// @author:  Bart Golab
// @version: $Revision: #6 $
//
// Last modification: $DateTime: 2015/01/08 17:33:12 $
// Last modified by:  $Author: qi.huang $
//
// Displays the current state of a single active plan instance. Used by plan step detail page.
//

#include "app/response_plans/plan_manager/src/StdAfx.h"
#include "core/utilities/src/DebugUtil.h"
#include "bus/response_plans/active_plans_display/src/StringUtilities.h"
#include "app/response_plans/plan_manager/src/resource.h"
#include "app/response_plans/plan_manager/src/SinglePlanInstanceListCtrl.h"
#include "app/response_plans/plan_manager/src/LabelMaker.h"
#include "app/response_plans/plan_step_plugin/common_editor/src/ApplicationFont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static enum
{
    OWNER_COLUMN_INDEX = 0,
    ACTIVATION_COLUMN_INDEX,
    STATE_COLUMN_INDEX,
    REMARKS_COLUMN_INDEX,
};

using namespace TA_Base_App;


/////////////////////////////////////////////////////////////////////////////
// CSinglePlanInstanceListCtrl

CSinglePlanInstanceListCtrl::CSinglePlanInstanceListCtrl()
{
    FUNCTION_ENTRY( "CSinglePlanInstanceListCtrl" );
    FUNCTION_EXIT;
}


CSinglePlanInstanceListCtrl::~CSinglePlanInstanceListCtrl()
{
    FUNCTION_ENTRY( "~CSinglePlanInstanceListCtrl" );
    FUNCTION_EXIT;
}


BEGIN_MESSAGE_MAP(CSinglePlanInstanceListCtrl, CListCtrl)
    // {{AFX_MSG_MAP(CSinglePlanInstanceListCtrl)
    ON_WM_NCCALCSIZE()
    ON_NOTIFY_REFLECT(LVN_ITEMCHANGING, OnItemChanging)
    // }}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSinglePlanInstanceListCtrl message handlers

void CSinglePlanInstanceListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
    FUNCTION_ENTRY( "OnNcCalcSize" );

    // TODO: Add your message handler code here and/or call default
    ModifyStyle(WS_HSCROLL | WS_VSCROLL, 0);  // remove scrolls

    CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);

    FUNCTION_EXIT;
}


void CSinglePlanInstanceListCtrl::OnItemChanging(NMHDR* pNMHDR, LRESULT* pResult)
{
    FUNCTION_ENTRY( "OnItemChanging" );

    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    // TODO: Add your control notification handler code here
    if ((pNMListView->uNewState & LVIS_SELECTED) == LVIS_SELECTED) // remove ability to select items
    {
        *pResult = 1;
    }
    else
    {
        *pResult = 0;
    }

    FUNCTION_EXIT;
}


BOOL CSinglePlanInstanceListCtrl::PreCreateWindow( CREATESTRUCT& cs )
{
    BOOL bRes = CListCtrl::PreCreateWindow( cs );

    ApplicationFont::getInstance().adjustChildrenFont( GetSafeHwnd() );

    return bRes;
}


void CSinglePlanInstanceListCtrl::PreSubclassWindow()
{
    FUNCTION_ENTRY( "PreSubclassWindow" );

    // TODO: Add your specialized code here and/or call the base class
    ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL);
    SetExtendedStyle(GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_INFOTIP);

    InsertColumn(OWNER_COLUMN_INDEX, _T(LabelMaker::getActivePlanListOwnerColumnLabel()), LVCFMT_LEFT, 150);
    InsertColumn(ACTIVATION_COLUMN_INDEX, _T(LabelMaker::getActivePlanListActivationColumnLabel()), LVCFMT_LEFT, 150);
    InsertColumn(STATE_COLUMN_INDEX, _T(LabelMaker::getActivePlanListStateColumnLabel()), LVCFMT_LEFT, 90);
    InsertColumn(REMARKS_COLUMN_INDEX, _T(LabelMaker::getActivePlanListRemarksColumnLabel()), LVCFMT_LEFT, 600);

    CListCtrl::PreSubclassWindow();

    FUNCTION_EXIT;
}


BOOL CSinglePlanInstanceListCtrl::SetReadOnly(BOOL readOnly)
{
    FUNCTION_ENTRY( "SetReadOnly" );

    DWORD colorRef = ::GetSysColor(readOnly? COLOR_3DFACE : COLOR_WINDOW);

    if (SetBkColor(colorRef) && SetTextBkColor(colorRef))
    {
        FUNCTION_EXIT;
        return TRUE;
    }

    FUNCTION_EXIT;
    return FALSE;
}


void CSinglePlanInstanceListCtrl::PopulateInstance(const TA_Base_Core::ActivePlanDetail &activePlanDetail)
{
    FUNCTION_ENTRY( "PopulateInstance" );

    if (GetItemCount() == 0)
    {
        InsertItem(0, "");
    }

    SetItemText(0, OWNER_COLUMN_INDEX, _T(activePlanDetail.owner.in()));
    SetItemText(0, ACTIVATION_COLUMN_INDEX, _T(TA_Base_Bus::StringUtilities::timeToString(activePlanDetail.instantiationTime).c_str()));
    SetItemText(0, STATE_COLUMN_INDEX, _T(TA_Base_Bus::StringUtilities::convertToString(activePlanDetail.activePlanState)));
    SetItemText(0, REMARKS_COLUMN_INDEX, _T(activePlanDetail.remark.in()));

    FUNCTION_EXIT;
}


void CSinglePlanInstanceListCtrl::UpdateInstance(const TA_Base_Core::ActivePlanDetail &activePlanDetail)
{
    FUNCTION_ENTRY( "UpdateInstance" );

    if ( GetItemCount() == 0 )
    {
        LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugError, 
            "No instance when update plan [%lu, %lu] at location %lu", 
            activePlanDetail.plan.plan, activePlanDetail.plan.instance, activePlanDetail.plan.location );
        return;
    }
    
    SetItemText(0, OWNER_COLUMN_INDEX, _T(activePlanDetail.owner.in()));
    SetItemText(0, STATE_COLUMN_INDEX, _T(TA_Base_Bus::StringUtilities::convertToString(activePlanDetail.activePlanState)));
    SetItemText(0, REMARKS_COLUMN_INDEX, _T(activePlanDetail.remark.in()));

    FUNCTION_EXIT;
}
