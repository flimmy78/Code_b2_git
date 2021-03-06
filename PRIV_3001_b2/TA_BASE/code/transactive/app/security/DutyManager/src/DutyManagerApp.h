#if !defined(AFX_DUTYMANAGERAPP_H__3885936E_D54D_4FA8_B514_AF2286F39023__INCLUDED_)
#define AFX_DUTYMANAGERAPP_H__3885936E_D54D_4FA8_B514_AF2286F39023__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/security/DutyManager/src/DutyManagerApp.h $
  * @author:  Bart Golab
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * This class provides the entry point into the application.
  * It instantiates DutyManagerGUI, but leaves it to the
  * GenericGUI to display.
  *
  */

namespace TA_Base_App
{
    class DutyManagerApp : public TA_Base_Bus::TransActiveWinApp
    {
    // Operations
    public:
        DutyManagerApp();
        ~DutyManagerApp();


    // Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(DutyManagerApp)
        //}}AFX_VIRTUAL


    // Implementation
    protected:
        //{{AFX_MSG(DutyManagerApp)
	        // NOTE - the ClassWizard will add and remove member functions here.
	        //    DO NOT EDIT what you see in these blocks of generated code !
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
    };

} // namespace TA_Base_App

#endif // !defined(AFX_DUTYMANAGERAPP_H__3885936E_D54D_4FA8_B514_AF2286F39023__INCLUDED_)
