//
// The source code in this file is the property of
// Ripple Systems and is not for redistribution
// in any form.
//
// Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/response_plans/plan_manager/src/PlanEditorThread.h $
// @author:  Bart Golab
// @version: $Revision: #1 $
//
// Last modification: $DateTime: 2008/11/28 16:26:01 $
// Last modified by:  $Author: builder $
//
// <description>

#if !defined(AFX_PLANEDITORTHREAD_H__A69E8803_C051_4CD8_B64C_F8C791E88287__INCLUDED_)
#define AFX_PLANEDITORTHREAD_H__A69E8803_C051_4CD8_B64C_F8C791E88287__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FloatingWindowThread.h"


namespace TA_Base_App
{
    /////////////////////////////////////////////////////////////////////////////
    // CPlanEditorThread thread

    class CPlanEditorThread : public CFloatingWindowThread
    {
        DECLARE_DYNAMIC(CPlanEditorThread)

        CPlanEditorThread(TreeNodeId  nodeId);
        virtual ~CPlanEditorThread();

    // Operations
    protected:
        // CFloatingWindowThread overrides
        virtual CDocTemplate *GetDocumentTemplate() const;

    // Attributes
    private:

    // Overrides
    public:
        // ClassWizard generated virtual function overrides
        // {{AFX_VIRTUAL(CPlanEditorThread)
        // }}AFX_VIRTUAL

    // Implementation
        // Generated message map functions
        // {{AFX_MSG(CPlanEditorThread)
        afx_msg void OnRefreshPlanGeneralDetail(WPARAM wParam, LPARAM lParam);
        afx_msg void OnRefreshPlanStepDetail(WPARAM wParam, LPARAM lParam);
        // }}AFX_MSG

        DECLARE_MESSAGE_MAP()
    };

    /////////////////////////////////////////////////////////////////////////////

    // {{AFX_INSERT_LOCATION}}
    // Microsoft Visual C++ will insert additional declarations immediately before the previous line.

} // namespace TA_Base_App

#endif // !defined(AFX_PLANEDITORTHREAD_H__A69E8803_C051_4CD8_B64C_F8C791E88287__INCLUDED_)
