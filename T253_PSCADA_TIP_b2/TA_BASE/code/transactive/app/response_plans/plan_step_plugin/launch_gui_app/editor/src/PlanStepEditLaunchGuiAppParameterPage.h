//
// The source code in this file is the property of
// Ripple Systems and is not for redistribution
// in any form.
//
// Source:   $File: //depot/TA_Product_ECSPlan/TA_BASE/transactive/app/response_plans/plan_manager/src/PlanStepEditLaunchGuiAppParameterPage.h $
// @author:  Bart Golab
// @version: $Revision: #1 $
//
// Last modification: $DateTime: 2013/07/17 15:33:29 $
// Last modified by:  $Author: CM $
//
// <description>

#if !defined(AFX_PLANSTEPEDITLAUNCHAPPGUIPARAMETERPAGE_H__1F769611_744C_4F51_BAE3_D31208953B3C__INCLUDED_)
#define AFX_PLANSTEPEDITLAUNCHAPPGUIPARAMETERPAGE_H__1F769611_744C_4F51_BAE3_D31208953B3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bus/mfc_extensions/src/numeric_edit_control/NumericEdit.h"
#include "app/response_plans/plan_step_plugin/common_editor/src/PlanStepEditParameterPage.h"


namespace TA_Base_App
{
    class LaunchGuiAppStep;


    /////////////////////////////////////////////////////////////////////////////
    // CPlanStepEditLaunchGuiAppParameterPage dialog

    class CPlanStepEditLaunchGuiAppParameterPage : public CPlanStepEditParameterPage
    {
        DECLARE_DYNAMIC(CPlanStepEditLaunchGuiAppParameterPage)

    // Construction/destruction
    public:
        CPlanStepEditLaunchGuiAppParameterPage(LaunchGuiAppStep* step);
        ~CPlanStepEditLaunchGuiAppParameterPage();


    // Operations
    protected:
        virtual void EnableParameterControls(bool enable);
        virtual void DisplayParameters();
        virtual void UpdateParameters();


    // Dialog Data
    private:
        // {{AFX_DATA(CPlanStepEditLaunchGuiAppParameterPage)
        CNumericEdit    m_yPositionEdit;
        CNumericEdit    m_xPositionEdit;
        CNumericEdit    m_widthEdit;
        CNumericEdit    m_heightEdit;
        CComboBox    m_appTypeCombo;
        CEdit    m_commandLineEdit;
        // }}AFX_DATA

    // Overrides
    protected:
        // ClassWizard generate virtual function overrides
        // {{AFX_VIRTUAL(CPlanStepEditLaunchGuiAppParameterPage)
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        // }}AFX_VIRTUAL

    // Implementation
    protected:
        // Generated message map functions
        // {{AFX_MSG(CPlanStepEditLaunchGuiAppParameterPage)
        virtual BOOL OnInitDialog();
        // }}AFX_MSG
        DECLARE_MESSAGE_MAP()
    };

} // namespace TA_Base_App

#endif // !defined(AFX_PLANSTEPEDITLAUNCHAPPGUIPARAMETERPAGE_H__1F769611_744C_4F51_BAE3_D31208953B3C__INCLUDED_)
