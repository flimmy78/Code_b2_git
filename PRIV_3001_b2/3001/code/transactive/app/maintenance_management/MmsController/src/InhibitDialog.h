/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/maintenance_management/MmsController/src/InhibitDialog.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  */
#if !defined(AFX_INHIBITDIALOG_H__A132A5CB_DD32_406D_99F6_7DC2898FC018__INCLUDED_)
#define AFX_INHIBITDIALOG_H__A132A5CB_DD32_406D_99F6_7DC2898FC018__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

namespace TA_IRS_App
{
	class CInhibitDialog : public CDialog
	{
	public:
		CInhibitDialog(CWnd* pParent = NULL);   // standard constructor

		//{{AFX_DATA(CInhibitDialog)
		enum { IDD = IDD_INHIBIT_DLG };
			// NOTE: the ClassWizard will add data members here
		//}}AFX_DATA


		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CInhibitDialog)
		protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		//}}AFX_VIRTUAL

	protected:

		// Generated message map functions
		//{{AFX_MSG(CInhibitDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

		DECLARE_MESSAGE_MAP()
	};

} // TA_IRS_App

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INHIBITDIALOG_H__A132A5CB_DD32_406D_99F6_7DC2898FC018__INCLUDED_)
