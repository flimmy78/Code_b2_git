/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/response_plans/plan_manager/src/LaunchSchematicDlg.h $
  * @author:  Bart Golab
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * Facilitates the launching of a display when executing a Launch Schematic step.
  *
  */

#if !defined(AFX_LAUNCHSCHEMATICDLG_H__632F3386_7562_460E_B72C_2357C0311E1B__INCLUDED_)
#define AFX_LAUNCHSCHEMATICDLG_H__632F3386_7562_460E_B72C_2357C0311E1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "InteractiveStepDlg.h"


namespace TA_Base_App
{
    /////////////////////////////////////////////////////////////////////////////
    // CLaunchSchematicDlg dialog

    class CLaunchSchematicDlg : public CInteractiveStepDlg
    {
    // Construction
    public:
        CLaunchSchematicDlg(const TA_Base_Bus::IPlanManagerCorbaDef::CurrentPlanStepDetail& stepDetail);


    // Operations
    protected:
        virtual CString getTitlePrefix() const;
        virtual void reportCompletionStatus() const;


    // Dialog Data
    private:
        // {{AFX_DATA(CLaunchSchematicDlg)
        enum { IDD = IDD_LAUNCH_SCHEMATIC_DLG };
        CComboBox    m_screenNumberCombo;
        // }}AFX_DATA

    // Overrides
    protected:
        // ClassWizard generated virtual function overrides
        // {{AFX_VIRTUAL(CLaunchSchematicDlg)
    public:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL OnInitDialog();
        // }}AFX_VIRTUAL

    // Implementation
    protected:
        // Generated message map functions
        // {{AFX_MSG(CLaunchSchematicDlg)
        // }}AFX_MSG
        DECLARE_MESSAGE_MAP()
    };

} // namespace TA_App

#endif // !defined(AFX_LAUNCHSCHEMATICDLG_H__632F3386_7562_460E_B72C_2357C0311E1B__INCLUDED_)
