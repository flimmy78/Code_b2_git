/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/4669_T01271350/4669/transactive/app/radio/radio_monitor_gui/src/SelectedListCtrl.cpp $
  * @author Jade Lee
  * @version $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by: $Author: builder $
  * 
  * List control for Radio Manager, for the selected list 
  *
  */
  
#include "app/radio/radio_monitor_gui/src/StdAfx.h"
#include "app/radio/radio_monitor_gui/src/SelectedListCtrl.h"


namespace TA_IRS_App
{    
    
    typedef ManagedListCtrl<RadioMonitor::SelectedEntity, TA_Base_Bus::ListCtrlSelNoFocus> BaseClass;

    BEGIN_MESSAGE_MAP(SelectedListCtrl, BaseClass)
	    //{{AFX_MSG_MAP(SelectedListCtrl)
	    //}}AFX_MSG_MAP
    END_MESSAGE_MAP()

}   // end namespace TA_IRS_App
