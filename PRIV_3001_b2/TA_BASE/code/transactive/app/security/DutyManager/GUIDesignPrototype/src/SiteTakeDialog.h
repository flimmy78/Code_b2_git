/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/security/DutyManager/GUIDesignPrototype/src/SiteTakeDialog.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  */
#if !defined(AFX_SITETAKEDIALOG_H__D3BD6DD4_DD89_48A2_8743_8A808F52BE1A__INCLUDED_)
#define AFX_SITETAKEDIALOG_H__D3BD6DD4_DD89_48A2_8743_8A808F52BE1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SiteTakeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSiteTakeDialog dialog

class CSiteTakeDialog : public CDialog
{
// Construction
public:
	CSiteTakeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSiteTakeDialog)
	enum { IDD = IDD_SITETAKE };
	CListCtrl	m_takeList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSiteTakeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSiteTakeDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SITETAKEDIALOG_H__D3BD6DD4_DD89_48A2_8743_8A808F52BE1A__INCLUDED_)
