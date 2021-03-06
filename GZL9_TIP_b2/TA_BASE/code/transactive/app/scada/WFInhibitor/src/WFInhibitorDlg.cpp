/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/GZL9_TIP/TA_BASE/transactive/app/scada/wf_inhibitor/src/WFInhibitorDlg.cpp $
  * @author:  Andy Parker
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/07/05 10:04:52 $
  * Last modified by:  $Author: jinmin.huang $
  * 
  * This class provides the main dialog used to set WF Global Inhibit information.  
  */

#include "stdafx.h"
#include "app/scada/WFInhibitor/src/WFInhibitor.h"
#include "app/scada/WFInhibitor/src/WFInhibitorDlg.h"
#include "bus/scada/wf_global_inhibit/src/WFGlobalInhibitionManager.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/RunParams.h"
#include "bus/security/authentication_library/src/AuthenticationLibrary.h"
#include <time.h>
#include <sstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


namespace TA_Base_App
{
	const char* RPARAM_WF_INHIBIT 	= "WFInActive";
	const char* RPARAM_WF_UNINHIBIT	= "WFActive";

	CWFInhibitorDlg::CWFInhibitorDlg(TA_Base_Bus::IGUIAccess& genericGUICallback,CWnd* pParent /*= NULL*/)
	:
	TA_Base_Bus::TransActiveDialog(genericGUICallback,CWFInhibitorDlg::IDD, pParent),
	m_wfInhibit(false),
	m_globalInhibitStatus(false),
	m_timerUtility( TA_Base_Core::SingletonTimerUtil::getInstance() )	
	{
		m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	}

	CWFInhibitorDlg::~CWFInhibitorDlg()
	{
		m_timerUtility.stopPeriodicTimeOutClock(this);
		TA_Base_Core::SingletonTimerUtil::removeInstance();		
	}

	void CWFInhibitorDlg::DoDataExchange(CDataExchange* pDX)
	{
		TA_Base_Bus::TransActiveDialog::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_EDIT_LOG_STATUS, m_statusBox);
	}

	BEGIN_MESSAGE_MAP(CWFInhibitorDlg, TA_Base_Bus::TransActiveDialog)
		ON_WM_SYSCOMMAND()
		ON_WM_PAINT()
		ON_WM_QUERYDRAGICON()
		//}}AFX_MSG_MAP
		//ON_EN_SETFOCUS(IDC_EDIT_PASSWORD, &CWFInhibitorDlg::OnEnSetfocusEditPassword)
		ON_BN_CLICKED(IDCANCEL, &CWFInhibitorDlg::OnBnClickedCancel)
		ON_BN_CLICKED(IDC_BUTTON_WF_INHIBIT, &CWFInhibitorDlg::OnBnClickedButtonWfInhibit)
	END_MESSAGE_MAP()


	BOOL CWFInhibitorDlg::OnInitDialog()
	{
		CRect windowSize;
		GetWindowRect(&windowSize);

		TA_Base_Bus::ResizingProperties properties;
		properties.canMaximise = false;
		properties.maxHeight = -1;
		properties.maxWidth = -1;
		properties.minHeight = windowSize.bottom - windowSize.top;
		properties.minWidth = windowSize.right - windowSize.left;
		setResizingProperties(properties);


		LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugInfo, 
				"CWFInhibitorDlg::OnInitDialog");

		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
		
		TA_Base_Bus::TransActiveDialog::OnInitDialog();

		// Set the icon for this dialog.  The framework does this automatically
		//  when the application's main window is not a dialog
		SetIcon(m_hIcon, TRUE);			// Set big icon
		SetIcon(m_hIcon, FALSE);		// Set small icon

		if (true == TA_Base_Core::RunParams::getInstance().isSet(RPARAM_WF_INHIBIT))
		{
			m_wfInhibit = true;
			GetDlgItem(IDC_BUTTON_WF_INHIBIT)->SetWindowText(_T("退出五防系统"));
		}

		if (true == TA_Base_Core::RunParams::getInstance().isSet(RPARAM_WF_UNINHIBIT))
		{
			m_wfInhibit = false;
			GetDlgItem(IDC_BUTTON_WF_INHIBIT)->SetWindowText(_T("投入五防系统"));
		}			
		m_timerUtility.startPeriodicTimeOutClock( this, 1000, false );

		return TRUE;  // return TRUE  unless you set the focus to a control
	}

	// If you add a minimize button to your dialog, you will need the code below
	//  to draw the icon.  For MFC applications using the document/view model,
	//  this is automatically done for you by the framework.
	void CWFInhibitorDlg::OnPaint()
	{
		if (IsIconic())
		{
			CPaintDC dc(this); // device context for painting

			SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

			// Center icon in client rectangle
			int cxIcon = GetSystemMetrics(SM_CXICON);
			int cyIcon = GetSystemMetrics(SM_CYICON);
			CRect rect;
			GetClientRect(&rect);
			int x = (rect.Width() - cxIcon + 1) / 2;
			int y = (rect.Height() - cyIcon + 1) / 2;

			// Draw the icon
			dc.DrawIcon(x, y, m_hIcon);
		}
		else
		{
			CDialog::OnPaint();
		}
	}

	// The system calls this function to obtain the cursor to display while the user drags
	//  the minimized window.
	HCURSOR CWFInhibitorDlg::OnQueryDragIcon()
	{
		return static_cast<HCURSOR>(m_hIcon);
	}
	
	void CWFInhibitorDlg::OnBnClickedCancel()
	{
		// TODO: Add your control notification handler code here
		OnCancel();
		PostMessage(WM_CLOSE);
	}

	void CWFInhibitorDlg::timerExpired(long timerId, void* userData)
	{
		bool bRet = false;
		bool inhibitStatus = m_globalInhibitStatus;
		bRet = TA_Base_Bus::WFGlobalInhibitionManager::getInstance().getWFGlobalInhibitState(inhibitStatus);
		
		if (true == bRet)
		{
			if (true == inhibitStatus)
			{
				GetDlgItem(IDC_WF_INHIBIT_STATUS)->SetWindowText(_T("五防校验当前退出"));
			}
			else
			{
				GetDlgItem(IDC_WF_INHIBIT_STATUS)->SetWindowText(_T("五防校验当前投入"));
			}
		}
		else
		{
			GetDlgItem(IDC_WF_INHIBIT_STATUS)->SetWindowText(_T("五防校验状态未知"));
		}
	}
	
	void CWFInhibitorDlg::OnBnClickedButtonWfInhibit()
	{
		// TODO: Add your control notification handler code here
		CString strLog;
		GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(strLog);
		std::string strPassword((LPCTSTR)strLog);
		std::string strSession = TA_Base_Core::RunParams::getInstance().get(RPARAM_SESSIONID);
		
		if (0 == strPassword.length())
		{
			displayResultInfo(_T("密码为空，请输入密码。"));
			return;
		}

		//if (m_wfInhibit == m_globalInhibitStatus)
			
		bool globalInhibitStatus = m_globalInhibitStatus;
		bool bRet = TA_Base_Bus::WFGlobalInhibitionManager::getInstance().getWFGlobalInhibitState(globalInhibitStatus);
		
		if (true == bRet)
		{
			if (m_wfInhibit == globalInhibitStatus)
			{
				displayResultInfo(_T("五防校验投退状态与操作一致，无需执行。"));
				return;
			}
		}
		else
		{
			displayResultInfo(_T("五防校验状态未知,不能执行投退操作。"));
			return;
		}		

		if (true == TA_Base_Bus::WFGlobalInhibitionManager::getInstance().verifyPassoword(strSession,strPassword))
		{
			displayResultInfo(_T("密码校验通过。"));
			CString strResult = _T("五防系统");
			
			if (m_wfInhibit)
				strResult += _T("退出设置"); 
			else
				strResult += _T("投入设置"); 
				
			
			if (true == TA_Base_Bus::WFGlobalInhibitionManager::getInstance().setWFGlobalInhibitState(m_wfInhibit,strSession))
			{
				displayResultInfo(strResult + _T("成功。"));
			}
			else
			{
				displayResultInfo(strResult + _T("失败。"));
			}
		}
		else
		{
			displayResultInfo(_T("密码错误，请重新输入。"));
			
		}
		//m_statusBox.GetWindowText(strLog);
		//strLog = strLog + '\n';
		//strLog += getCurrentTimeStr().c_str();
		//strLog += _T("校验密码错误，请重新输入。");
		//strLog += "This is a Test";
		//m_statusBox.SetWindowText(strLog);

		//m_statusBox.SetSel(-1, -1);
		//m_statusBox.ReplaceSel(strLog+"\r\n");
		//UpdateData(true);
		//m_statusBox.LineScroll(m_statusBox.GetLineCount());
	}

	std::string CWFInhibitorDlg::getCurrentTimeStr()
	{
		time_t rawtime;
		struct tm * localTm;

		time (&rawtime);
		localTm = localtime (&rawtime);

		std::string month="";
		switch(localTm->tm_mon)
		{
		case 0 : month = "1";
			break;
		case 1 : month = "2";
			break;
		case 2 : month = "3";
			break;
		case 3 : month = "4";
			break;
		case 4 : month = "5";
			break;
		case 5 : month = "6";
			break;
		case 6 : month = "7";
			break;
		case 7 : month = "8";
			break;
		case 8 : month = "9";
			break;
		case 9 : month = "10";
			break;
		case 10 : month = "11";
			break;
		case 11 : month = "12";
				 break;
		}
		std::stringstream timestampedStatusText;

		timestampedStatusText << localTm->tm_year+1900 << "-"
							  << month.c_str() << "-"
							  << ( localTm->tm_mday < 10 ? "0" : "" )
							  << localTm->tm_mday << " "									  
							  << ( localTm->tm_hour < 10 ? "0" : "" ) 
							  << localTm->tm_hour << ":" 
							  << ( localTm->tm_min < 10 ? "0" : "" ) 
							  << localTm->tm_min << ":" 
							  << ( localTm->tm_sec < 10 ? "0" : "" ) 
							  << localTm->tm_sec << " - ";
							  //<< *statusText;
		std::string strTemp;
		return timestampedStatusText.str();
	}
	
	void CWFInhibitorDlg::displayResultInfo(CString strResult)
	{
		CString strLog;
		strLog += getCurrentTimeStr().c_str();
		strLog += strResult;
		m_statusBox.SetSel(-1, -1);
		m_statusBox.ReplaceSel(strLog+"\r\n");
		UpdateData(true);		
	}

}