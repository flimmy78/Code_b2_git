/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/telephone/telephone_manager/src/DirectLineDialog.h $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  */
#if !defined(AFX_DIRECTLINEDIALOG_H__33CA3ED4_8829_11D7_B17D_0050BAB1D931__INCLUDED_)
#define AFX_DIRECTLINEDIALOG_H__33CA3ED4_8829_11D7_B17D_0050BAB1D931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirectLineDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DirectLineDialog dialog

class DirectLineDialog : public CDialog
{
// Construction
public:
	DirectLineDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DirectLineDialog)
	enum { IDD = IDD_DIRECT_LINE };
	CButton	m_auto_call_cb;
	CTabCtrl	m_tabControl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DirectLineDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DirectLineDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTLINEDIALOG_H__33CA3ED4_8829_11D7_B17D_0050BAB1D931__INCLUDED_)
