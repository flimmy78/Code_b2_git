//
// The source code in this file is the property of
// Ripple Systems and is not for redistribution
// in any form.
//
// Source:   $File: //depot/TA_Product_ECSPlan/TA_BASE/transactive/app/response_plans/plan_manager/src/PlanStepEditPromptPage.h $
// @author:  Andy Parker
// @version: $Revision: #1 $
//
// Last modification: $DateTime: 2013/07/17 15:33:29 $
// Last modified by:  $Author: CM $
//
// <description>

#if !defined(AFX_PLANSTEPEDITPROMPTPAGE_H__D1282C18_2991_4F94_B465_26CEA47B582A__INCLUDED_)
#define AFX_PLANSTEPEDITPROMPTPAGE_H__D1282C18_2991_4F94_B465_26CEA47B582A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "app/response_plans/plan_step_plugin/common_editor/src/PlanStepEditParameterPage.h"


namespace TA_Base_App
{
    class PromptStep;

    /////////////////////////////////////////////////////////////////////////////
    // CPlanStepEditLogPage dialog

    class CPlanStepEditPromptPage : public CPlanStepEditParameterPage
    {
        DECLARE_DYNAMIC(CPlanStepEditPromptPage)

    // Construction
    public:
        CPlanStepEditPromptPage(PromptStep* step);
        ~CPlanStepEditPromptPage();


    // Operations
    protected:
        virtual void EnableParameterControls(bool enable);
        virtual void DisplayParameters();
        virtual void UpdateParameters();


    // Overrides
    protected:
        // ClassWizard generate virtual function overrides
        // {{AFX_VIRTUAL(CPlanStepEditPromptPage)
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        // }}AFX_VIRTUAL

    // Implementation
    protected:
        // Generated message map functions
        // {{AFX_MSG(CPlanStepEditPromptPage)
        virtual BOOL OnInitDialog();
        // }}AFX_MSG
        DECLARE_MESSAGE_MAP()

    // Dialog Data
    private:
        // {{AFX_DATA(CPlanStepEditPromptPage)
        CEdit m_promptMsg;
        CDateTimeCtrl     m_responseTimeout;
        // }}AFX_DATA
    };

} // end namespace

#endif // !defined(AFX_PLANSTEPEDITPROMPTPAGE_H__D1282C18_2991_4F94_B465_26CEA47B582A__INCLUDED_)
