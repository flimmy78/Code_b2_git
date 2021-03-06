//
// The source code in this file is the property of
// Ripple Systems and is not for redistribution
// in any form.
//
// Source:   $File: //depot/TA_Product_ECSPlan/TA_BASE/transactive/app/response_plans/plan_manager/src/UnapprovedPlanDoc.cpp $
// @author:  Bart Golab
// @version: $Revision: #2 $
//
// Last modification: $DateTime: 2015/09/15 15:58:53 $
// Last modified by:  $Author: huang.wenbo $
//
// <description>

#include "StdAfx.h"
#include "PlanManager.h"
#include "UnapprovedPlanDoc.h"
#include "TreeNodeFactory.h"
#include "TreeNode.h"
#include "RootNode.h"
#include "CategoryNode.h"
#include "PlanNode.h"
#include "LabelMaker.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace TA_Base_App;


/////////////////////////////////////////////////////////////////////////////
// CUnapprovedPlanDoc

IMPLEMENT_DYNCREATE(CUnapprovedPlanDoc, CPlanTreeDoc)

CUnapprovedPlanDoc::CUnapprovedPlanDoc()
{
    FUNCTION_ENTRY( "CUnapprovedPlanDoc" );
    FUNCTION_EXIT;
}


CUnapprovedPlanDoc::~CUnapprovedPlanDoc()
{
    FUNCTION_ENTRY( "~CUnapprovedPlanDoc" );
    FUNCTION_EXIT;
}


BEGIN_MESSAGE_MAP(CUnapprovedPlanDoc, CPlanTreeDoc)
    // {{AFX_MSG_MAP(CUnapprovedPlanDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    // }}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CUnapprovedPlanDoc commands

const std::string &CUnapprovedPlanDoc::GetRootNodeLabel()
{
    FUNCTION_ENTRY( "GetRootNodeLabel" );

    static const std::string ROOT_NODE_LABEL = (LPCTSTR) LabelMaker::getUnapprovedPlanTreeRootNodeLabel();

    FUNCTION_EXIT;
    return ROOT_NODE_LABEL;
}


// ITreeNodeFilter interface
bool CUnapprovedPlanDoc::isRelevant(TreeNode &treeNode)
{
    FUNCTION_ENTRY( "isRelevant" );

    // PW#2920: If the operator is locked into a particular category, then all that is relevant are
    // nodes at or above the locked category or below it.
    if (IsPlanTreeLocked() && !IsNodeOnLockedCategoryPath(treeNode.getNodeId()) && !IsNodeAccessible(treeNode.getNodeId()))
    {
        FUNCTION_EXIT;
        return false;
    }

    PlanNode *planNode = dynamic_cast<PlanNode *>(&treeNode);

    if (planNode)
    {
        FUNCTION_EXIT;
        return !planNode->isApproved();
    }

    CategoryNode *categoryNode = dynamic_cast<CategoryNode *>(&treeNode);

    if (categoryNode)
    {
        // A category is relevant to the unapproved plan tree if either of the following applies:
        // 1. the category has unapproved descendants, or
        // 2. a plan tree lock is active and the category lies on the path leading to the locked category - this
        // allows the locked category to appear in the unapproved plan tree, even if it has no unapproved descendants.
        FUNCTION_EXIT;
        return (categoryNode->getNodeSummary().hasUnapprovedDescendant ||
                (IsPlanTreeLocked() && IsNodeOnLockedCategoryPath(categoryNode->getNodeId())));
    }

    FUNCTION_EXIT;
    return false;
}


