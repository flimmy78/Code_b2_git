/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/bus/response_plans/plan_tree/src/RootItem.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  */
// RootItem.cpp : implementation file
//

#include "StdAfx.h"
#include "bus\response_plans\plan_tree\src\PlanTree_resource.h"
#include "bus\response_plans\plan_tree\src\RootItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace TA_Base_Bus;


/////////////////////////////////////////////////////////////////////////////
// CRootItem

CRootItem::CRootItem(const TA_Base_Core::NodeSummary& nodeSummary, IPlanAccess& planAccess) : 
    CCategoryItem(nodeSummary, planAccess)
{
}


CRootItem::~CRootItem()
{
}


HICON CRootItem::getItemImage(bool itemExpanded)
{
    static HICON rootIcon = LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_PLAN_TREE_ROOT_ICON));

    return rootIcon;
}


IPlanAccess::PlanNodeList CRootItem::getChildren()
{
    return getPlanAccess().getRootChildren();
}
