/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/configuration/config_plugins/pa_station/src/StdAfx.h $
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

#if !defined(AFX_STDAFX_H__9CCDFE80_9875_43FD_8180_C9DB736F9683__INCLUDED_)
#define AFX_STDAFX_H__9CCDFE80_9875_43FD_8180_C9DB736F9683__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "bus/resources/resource.h"
#include "app/configuration/config_plugins/pa_station/src/PAStationComponent.h"
#include "app/configuration/config_plugins/pa_station/src/resource.h"
#include "app/configuration/config_plugins/pa_station/src/PAStationFrameworkView.h"
#include "app/configuration/config_plugins/pa_station/src/PAStationDatabaseAccessor.h"
#include "app/configuration/config_plugins/pa_station/src/PAStationDetailView.h"
#include "app/configuration/config_plugins/pa_station/src/PAStationListView.h"


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9CCDFE80_9875_43FD_8180_C9DB736F9683__INCLUDED_)
