/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/signs/ttis_manager/src/TTISManager.cpp $
  * @author:  Adam Radics
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * Main application
  *
  */


#include "stdafx.h"
#include "TTISManager.h"
#include "TTISManagerGUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace TA_IRS_App
{

/////////////////////////////////////////////////////////////////////////////
// TTISManagerApp

BEGIN_MESSAGE_MAP(TTISManagerApp, TA_Base_Bus::TransActiveWinApp)
    // {{AFX_MSG_MAP(TTISManagerApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        // DO NOT EDIT what you see in these blocks of generated code!
    // }}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TTISManagerApp construction

TTISManagerApp::TTISManagerApp()
: TA_Base_Bus::TransActiveWinApp( new TTISManagerGUI(), "TTIS Manager" )
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only TTISManagerApp object

TTISManagerApp theApp;

} // TA_IRS_App
