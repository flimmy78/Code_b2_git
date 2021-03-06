//
// The source code in this file is the property of
// Ripple Systems and is not for redistribution
// in any form.
//
// Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/response_plans/plan_manager/src/TreeNodeFactory.h $
// @author:  Bart Golab
// @version: $Revision: #1 $
//
// Last modification: $DateTime: 2008/11/28 16:26:01 $
// Last modified by:  $Author: builder $
//
// <description>

#if !defined(AFX_TREENODEFACTORY_H__AB7D8100_2FE6_44D3_A8ED_07BB43925EB2__INCLUDED_)
#define AFX_TREENODEFACTORY_H__AB7D8100_2FE6_44D3_A8ED_07BB43925EB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "core/data_access_interface/PlanAgent/IDL/src/PlanAgentDataCorbaDef.h"
#include "core/synchronisation/src/NonReEntrantThreadLockable.h"
#include "SynchronisedMap.h"
#include "PlanManagerCommonDefs.h"


namespace TA_Base_App
{
    class TreeNode;
    class RootNode;


    /////////////////////////////////////////////////////////////////////////////
    // TreeNodeFactory singleton

    class TreeNodeFactory
    {
    // Operations
    public:
        static TreeNodeFactory &getInstance();
        static void destroyInstance();
        static TreeNodeId getRootNodeId();

        RootNode *createRootNode();
        TreeNode *createTreeNode(TreeNodeId nodeId);
        TreeNode *createTreeNode(const TA_Base_Core::NodeSummary &nodeSummary);
        void createChildren(TreeNodeId nodeId, TreeNodeList &children);
        void createRootChildren(TreeNodeList &children);
        void retireTreeNode(TreeNodeId nodeId);

        RootNode *getRootNode();
        TreeNode *getTreeNode(TreeNodeId nodeId);
        TreeNode *getClosestAncestor(TreeNodeId nodeId);
        TreeNode *getTreeNodeOrClosestAncestor(TreeNodeId nodeId);
        int getTreeNodeLevelInTree(TreeNodeId nodeId);

        void getNodeIdsInNodePath(TreeNodeId nodeId, TreeNodeIdList &nodeIds);

    private:
        TreeNodeFactory();
        ~TreeNodeFactory();
        TreeNodeFactory(const TreeNodeFactory &other);
        TreeNodeFactory& operator=(const TreeNodeFactory &other);
        void createTreeNodes(const TA_Base_Core::SiblingNodes &nodes, TreeNodeList &treeNodes);


    // Attributes
    private:
        static TreeNodeFactory *s_instance;
        static TA_Base_Core::NonReEntrantThreadLockable s_singletonLock;

        SynchronisedMap<TreeNodeId, TreeNode *> m_treeNodeMap;

    };

} // namespace TA_Base_App


#endif // !defined(AFX_TREENODEFACTORY_H__AB7D8100_2FE6_44D3_A8ED_07BB43925EB2__INCLUDED_)
