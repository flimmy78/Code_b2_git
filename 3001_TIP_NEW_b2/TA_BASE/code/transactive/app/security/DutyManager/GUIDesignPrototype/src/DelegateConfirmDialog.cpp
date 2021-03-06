/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/security/DutyManager/GUIDesignPrototype/src/DelegateConfirmDialog.cpp $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  */
// DelegateConfirmDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DutyManager.h"
#include "DelegateConfirmDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelegateConfirmDialog dialog


CDelegateConfirmDialog::CDelegateConfirmDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDelegateConfirmDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDelegateConfirmDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDelegateConfirmDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDelegateConfirmDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDelegateConfirmDialog, CDialog)
	//{{AFX_MSG_MAP(CDelegateConfirmDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelegateConfirmDialog message handlers
