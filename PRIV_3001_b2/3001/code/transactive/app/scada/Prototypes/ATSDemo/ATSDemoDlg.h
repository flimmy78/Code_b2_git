/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/scada/Prototypes/ATSDemo/ATSDemoDlg.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  */
// ATSDemoDlg.h : header file
//

#if !defined(AFX_ATSDEMODLG_H__AA70C847_0E8C_45E8_8C46_09EE8127ED9B__INCLUDED_)
#define AFX_ATSDEMODLG_H__AA70C847_0E8C_45E8_8C46_09EE8127ED9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DummyControlStation;

/////////////////////////////////////////////////////////////////////////////
// CATSDemoDlg dialog

class CATSDemoDlg : public CDialog
{
// Construction
public:
	CATSDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CATSDemoDlg)
	enum { IDD = IDD_ATSDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CATSDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
		
	void cleanUp();

protected:
	HICON m_hIcon;

	DummyControlStation * m_dummyControlStation;

	// Generated message map functions
	//{{AFX_MSG(CATSDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATSDEMODLG_H__AA70C847_0E8C_45E8_8C46_09EE8127ED9B__INCLUDED_)
