/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/bus/generic_gui/src/AbstractDialogGUI.cpp $
  * @author:  Karen Graham
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  * 
  * This inherits from AbstractGUIApplication and implements all methods specific to dialogs.
  */

#include "bus/generic_gui/src/StdAfx.h"
#include "bus/generic_gui/src/IGUIApplication.h"
#include "bus/generic_gui/src/IGUIAccess.h"
#include "bus/generic_gui/src/AbstractDialogGUI.h"

#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/TAAssert.h"

namespace TA_Base_Bus
{
    AbstractDialogGUI::AbstractDialogGUI(UINT nIDTemplate)
    :
    m_dlgResourceID( nIDTemplate )
    {
    }


    AbstractDialogGUI::~AbstractDialogGUI()
    {
    }


    bool AbstractDialogGUI::displayApplication()
    {
        FUNCTION_ENTRY( "displayApplication" );

        createApplicationObject();
        
        CWnd* app = getApplicationWnd();
        TA_ASSERT(app != NULL, "CWnd pointer was never set up correctly. Nothing assigned to m_application");

        // Assign the dialog as the main window.
        AfxGetApp()->m_pMainWnd = app;

        // Start the dialog
        CDialog* dialog = dynamic_cast<CDialog*>(app);

        // Check if m_application is a CDialog
        TA_ASSERT(dialog != NULL, "m_application is not a CDialog");

		
		dialog->Create(m_dlgResourceID);
        //dialog->DoModal();
		dialog->SetActiveWindow();
		dialog->UpdateWindow();

        FUNCTION_EXIT;
        return true;
    }
} // end namespace TA_Base_Bus
