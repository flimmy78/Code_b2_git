/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/bus/generic_gui/templates/Dialog/src/TemplateDialog.cpp $
  * @author:  
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  * 
  *
  */

#include "stdafx.h"
#include "TemplateDialog.h"
#include "TemplateDialogDlg.h"
#include "TemplateDialogGUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using TA_Base_Bus::TransActiveWinApp;

/////////////////////////////////////////////////////////////////////////////
// CTemplateDialogApp

BEGIN_MESSAGE_MAP(CTemplateDialogApp, TransActiveWinApp)
	//{{AFX_MSG_MAP(CTemplateDialogApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTemplateDialogApp construction

CTemplateDialogApp::CTemplateDialogApp() : TransActiveWinApp(new TemplateDialogGUI(), "Template Dialog")
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTemplateDialogApp object

CTemplateDialogApp theApp;

