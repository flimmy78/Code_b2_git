#if !defined(AFX_DUTYMANAGER_H__5F04215F_509A_4311_82C5_842F9C2A0157__INCLUDED_)
#define AFX_DUTYMANAGER_H__5F04215F_509A_4311_82C5_842F9C2A0157__INCLUDED_

/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File$
  * @author:  Bart Golab
  * @version: $Revision$
  *
  * Last modification: $DateTime$
  * Last modified by:  $Author$
  * 
  * Consolidates all the required includes in a single header.
  *
  */

#ifdef __WIN32__
	#pragma warning(disable: 4250 4786)
#endif

// System includes
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

// Core includes
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/RunParams.h"
#include "core/exceptions/src/TransactiveException.h"
#include "core/exceptions/src/GenericGUIException.h"
#include "core/exceptions/src/UserSettingsException.h"
#include "core/data_access_interface/entity_access/src/DutyManagerEntityData.h"

// Bus includes
#include "bus/application_types/src/apptypes.h"
#include "bus/generic_gui/src/AbstractDialogGUI.h"
#include "bus/generic_gui/src/TransActiveDialog.h"
#include "bus/generic_gui/src/TransActiveWinApp.h"
#include "bus/generic_gui/src/HelpLauncher.h"
#include "bus/user_settings/src/SettingsMgr.h"
#include "bus/mfc_extensions/src/mfc_extensions.h"
#include "bus/security/duty_monitor_framework/src/DutyMonitorFramework.h"
#include "bus/security/duty_agent/idl/src/DutyAgentTypeCorbaDef.h"

// Duty Manager includes
#include "app/security/DutyManager/src/Resource.h"
#include "app/security/DutyManager/src/DutyManagerConstants.h"
#include "app/security/DutyManager/src/MessageBox.h"
#include "app/security/DutyManager/src/GridAssistant.h"
#include "app/security/DutyManager/src/DutyManagerPropertySheet.h"
#include "app/security/DutyManager/src/RegionDutyPropertyPage.h"
#include "app/security/DutyManager/src/SubsystemDutyPropertyPage.h"
#include "app/security/DutyManager/src/RegionDutyTransferDlg.h"
#include "app/security/DutyManager/src/SubsystemDutyTransferDlg.h"
#include "app/security/DutyManager/src/RegionSelectionDlg.h"
#include "app/security/DutyManager/src/DutyManagerDlg.h"
#include "app/security/DutyManager/src/DutyManagerGUI.h"
#include "app/security/DutyManager/src/DutyManagerApp.h"
#include "app/security/DutyManager/src/DutyManagerBridge.h"
#include "app/security/DutyManager/src/OtherSesSubDutyPropertyPage.h"
#include "app/security/DutyManager/src/SelectSesSubDutyDlg.h"

//
//	The custom Windows messages passed within the Duty Manager
//
#define RPARAM_SHOWOTHERSES			"ShowOtherses"
#define RPARAM_SHOWCONSOLE			"ShowConsole"

namespace TA_Base_App
{
    enum
    {
        WM_USER_RECEIVE_SESSION_UPDATE= (WM_USER + 1001),  // wParam = TA_Base_Bus::SessionUpdate*, lParam = unused
        WM_USER_RECEIVE_RGN_DUTY_UPDATE,                   // wParam = TA_Base_Bus::RegionDutyUpdate*, lParam = unused
        WM_USER_RECEIVE_SUB_DUTY_UPDATE,                   // wParam = TA_Base_Bus::SubsystemDutyUpdate*, lParam = unused
		WM_USER_RECEIVE_DUTY_AGENT_RECOVER_UPDATE,      // wParam = unused, lParam = locatiionKey
		WM_POPULATE_DATA,
		WM_OTHER_SES_SUB_DUTY_UPDATE
    };
}

#endif // !defined(AFX_DUTYMANAGER_H__5F04215F_509A_4311_82C5_842F9C2A0157__INCLUDED_)