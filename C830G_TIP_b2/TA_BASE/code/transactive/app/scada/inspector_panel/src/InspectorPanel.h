/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_Review_Branch/TA_BASE/transactive/app/scada/inspector_panel/src/InspectorPanel.h $
  * @author:  Andy Parker
  * @version: $Revision: #4 $
  *
  * Last modification: $DateTime: 2011/06/14 21:09:24 $
  * Last modified by:  $Author: yong.liu $
  * 
  * This class provides the base application class for the inspector panel.  It is implemented
  * as a managed process.
  */

#ifndef INSPECTORPANEL_H
#define INSPECTORPANEL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "app/scada/Inspector_Panel/src/resource.h"		// main symbols
#include "app/scada/Inspector_Panel/src/inspectorpanelGUI.h"

#include "bus/generic_gui/src/TransActiveWinApp.h"


// Command line variables
#define EQUIPMENT_RPARAM		"ControlEntity"
#define SCREEN_RPARAM			"ScreenName"
#define VALUE_RPARAM			"ControlValue"


#define UPDATED_PROXY_MESSAGE                   (WM_USER + 1)
#define LOAD_DATAPOINTS_MESSAGE	                (WM_USER + 2)
#define UPDATE_LABEL_IN_MAIN_THREAD_MESSAGE	    (WM_USER + 3)
#define PROCESS_RUNPARAM_IN_MAIN_THREAD_MESSAGE	(WM_USER + 4)
#define UPDATE_STATUS_WINDOW_MESSAGE			(WM_USER + 5)
#define UPDATE_PERMISSION						(WM_USER + 7)


namespace TA_Base_App
{
	/////////////////////////////////////////////////////////////////////////////
	// CInspectorPanelApp:
	// See InspectorPanel.cpp for the implementation of this class
	//

	class CInspectorPanelApp : public TA_Base_Bus::TransActiveWinApp
	{
	public:
		CInspectorPanelApp();
		virtual ~CInspectorPanelApp() {};

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CInspectorPanelApp)
		public:
		//}}AFX_VIRTUAL

	// Implementation

		//{{AFX_MSG(CInspectorPanelApp)
			// NOTE - the ClassWizard will add and remove member functions here.
			//    DO NOT EDIT what you see in these blocks of generated code !
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};


	/////////////////////////////////////////////////////////////////////////////

	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
}

#endif // ifndef INSPECTORPANEL_H
