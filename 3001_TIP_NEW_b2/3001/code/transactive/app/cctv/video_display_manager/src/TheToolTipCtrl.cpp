/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/cctv/video_display_manager/src/TheToolTipCtrl.cpp $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  */
// TheToolTipCtrl.cpp : implementation file
//

#ifdef _MSC_VER
#pragma warning( disable : 4786 )
#endif

#include "stdafx.h"
#include "TheToolTipCtrl.h"
#include "core/utilities/src/FunctionEntry.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTheToolTipCtrl


CTheToolTipCtrl::CTheToolTipCtrl()
{
    FUNCTION_ENTRY( "CTheToolTipCtrl" );
    FUNCTION_EXIT;
}


CTheToolTipCtrl::~CTheToolTipCtrl()
{
    FUNCTION_ENTRY( "~CTheToolTipCtrl" );
    FUNCTION_EXIT;
}


BEGIN_MESSAGE_MAP(CTheToolTipCtrl, CToolTipCtrl)
    // {{AFX_MSG_MAP(CTheToolTipCtrl)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    // }}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTheToolTipCtrl message handlers
BOOL CTheToolTipCtrl::AddWindowTool( CWnd* pWnd, LPCTSTR pszText )
{
    FUNCTION_ENTRY( "AddWindowTool" );

    TOOLINFO ti;
    ti.cbSize = sizeof( TOOLINFO );
    ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
    ti.hwnd = pWnd->GetParent()->GetSafeHwnd();
    ti.uId = (UINT) pWnd->GetSafeHwnd();
    ti.hinst = AfxGetInstanceHandle();
    ti.lpszText = (LPTSTR) pszText;

    LRESULT  message = SendMessage( TTM_ADDTOOL, 0, (LPARAM) &ti );

    FUNCTION_EXIT;
    return (BOOL) message;
}


