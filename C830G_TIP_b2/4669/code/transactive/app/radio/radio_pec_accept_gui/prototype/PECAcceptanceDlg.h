/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/radio/radio_pec_accept_gui/prototype/PECAcceptanceDlg.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */
// PECAcceptanceDlg.h : header file
//

#if !defined(AFX_PECACCEPTANCEDLG_H__8F6DD429_64C7_4A27_AF75_0352AB47E5D6__INCLUDED_)
#define AFX_PECACCEPTANCEDLG_H__8F6DD429_64C7_4A27_AF75_0352AB47E5D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPECAcceptanceDlg dialog

class CPECAcceptanceDlg : public CDialog
{
// Construction
public:
	CPECAcceptanceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPECAcceptanceDlg)
	enum { IDD = IDD_PECACCEPTANCE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPECAcceptanceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPECAcceptanceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PECACCEPTANCEDLG_H__8F6DD429_64C7_4A27_AF75_0352AB47E5D6__INCLUDED_)
