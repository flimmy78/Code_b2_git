/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/telephone/telephone_manager/src/telephone_manager.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  */
// telephone_manager.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "telephone_manager.h"
#include "TelephoneManagerAppGUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTelephone_managerApp

BEGIN_MESSAGE_MAP(CTelephone_managerApp, TransActiveWinApp)
	//{{AFX_MSG_MAP(CTelephone_managerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTelephone_managerApp construction

CTelephone_managerApp::CTelephone_managerApp()
: TA_Bus::TransActiveWinApp( *(new TelephoneManagerAppGUI()), "Telephone Manager" )
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTelephone_managerApp object

CTelephone_managerApp theApp;

