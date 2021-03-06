/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/bus/alarm/alarm_list_control/src/CSuppressAlarmConfirmDlg.cpp $
 * @author:  Derrick Liew
 * @version: $Revision: #1 $
 *
 * Last modification: $DateTime: 2018/03/14 13:51:20 $
 * Last modified by:  $Author: lim.cy $
 * 
 * This class is for the user to confirm the create of inhibition rule for system alarm.
 */

// CSuppressAlarmConfirmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSuppressAlarmConfirmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuppressAlarmConfirmDlg dialog
namespace TA_Base_Bus
{


	CSuppressAlarmConfirmDlg::CSuppressAlarmConfirmDlg(CWnd* pParent /*=NULL*/)
		: CDialog(CSuppressAlarmConfirmDlg::IDD, pParent)
	{
		//{{AFX_DATA_INIT(CSuppressAlarmConfirmDlg)
		m_confirmationText = _T("");
		//}}AFX_DATA_INIT
	}


	void CSuppressAlarmConfirmDlg::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CSuppressAlarmConfirmDlg)
		DDX_Text(pDX, IDC_STATIC_CONFIRM_TEXT, m_confirmationText);
		//}}AFX_DATA_MAP
	}


	BEGIN_MESSAGE_MAP(CSuppressAlarmConfirmDlg, CDialog)
		//{{AFX_MSG_MAP(CSuppressAlarmConfirmDlg)
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CSuppressAlarmConfirmDlg message handlers

	void CSuppressAlarmConfirmDlg::OnCancel() 
	{
		// TODO: Add extra cleanup here
		
		CDialog::OnCancel();
	}

	void CSuppressAlarmConfirmDlg::OnOK() 
	{
		// TODO: Add extra validation here
		
		CDialog::OnOK();
	}

	void CSuppressAlarmConfirmDlg::setConfirmationText(std::string confirmText)
	{
		m_confirmationText = confirmText.c_str();
	}
}// end of namespace
BOOL TA_Base_Bus::CSuppressAlarmConfirmDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
