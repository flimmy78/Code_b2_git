/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/trending/trend_viewer/src/HistoryViewer.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */
#include "stdafx.h"
#include "HistoryViewer.h"
#include "HistoryViewerGUI.h"
#include "core/utilities/src/RunParams.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace TA_Base_App
{

    /////////////////////////////////////////////////////////////////////////////
    // CHistoryViewerApp

        BEGIN_MESSAGE_MAP(CHistoryViewerApp, TA_Base_Bus::TransActiveWinApp)
        //{{AFX_MSG_MAP(CHistoryViewerApp)
            // NOTE - the ClassWizard will add and remove mapping macros here.
            //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG
    END_MESSAGE_MAP()

    /////////////////////////////////////////////////////////////////////////////
    // CHistoryViewerApp construction

    CHistoryViewerApp::CHistoryViewerApp()
    : TA_Base_Bus::TransActiveWinApp(new TA_Base_App::HistoryViewerGUI, "Trend Viewer")
    {
        // Place all significant initialization in InitInstance
    }

    /////////////////////////////////////////////////////////////////////////////
    // The one and only CHistoryViewerApp object

    CHistoryViewerApp theApp;

} // TA_History
