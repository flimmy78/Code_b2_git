/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/maintenance_management/MmsController/src/StdAfx.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  */
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F121D617_7F38_41D4_A2FD_1CF005F8EEF0__INCLUDED_)
#define AFX_STDAFX_H__F121D617_7F38_41D4_A2FD_1CF005F8EEF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/TAAssert.h"
//#include "core/naming/src/NamedObject.h"
//#include "bus\maintenance_management\mmsCorbaDef\idl\src\IMmsGlobalInhibitCorbaDef.h"

#define WM_RM_RIGHTS_CHANGE ( WM_APP + 0 )
#define WM_UPDATE_SUBSYSTEM_CHECKBOX ( WM_APP + 1 )
#define WM_UPDATE_DIALOG_CONTROLS ( WM_APP + 2 )
#define WM_UPDATE_SYSTEM_BUTTONS (WM_APP + 3)
#define WM_UPDATE_SYSTEM_MMS_INHIBITION (WM_APP + 4)
#define WM_UPDATE_MMS_INHIBITION_LIST (WM_APP + 5)

#ifndef _DEFINE_MMS_INHIBIT_AGENT_NAMED_OBJECT_
#define _DEFINE_MMS_INHIBIT_AGENT_NAMED_OBJECT_

/*
namespace TA_IRS_App
{
    typedef TA_Base_Core::NamedObject<TA_Base_Bus::IMmsGlobalInhibitCorbaDef,
	   					     TA_Base_Bus::IMmsGlobalInhibitCorbaDef_ptr, 
	           			     TA_Base_Bus::IMmsGlobalInhibitCorbaDef_var> MmsInhibitAgentNamedObject;
}
*/

#endif


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.



// #ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
// #endif



#endif // !defined(AFX_STDAFX_H__F121D617_7F38_41D4_A2FD_1CF005F8EEF0__INCLUDED_)
