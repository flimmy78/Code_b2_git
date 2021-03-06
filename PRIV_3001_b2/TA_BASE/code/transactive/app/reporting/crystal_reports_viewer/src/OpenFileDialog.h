/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/reporting/crystal_reports_viewer/src/OpenFileDialog.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  */
#if !defined(AFX_OPENFILEDIALOG_H__F9A17FE3_129B_4CEB_AA28_9F0E55974CC7__INCLUDED_)
#define AFX_OPENFILEDIALOG_H__F9A17FE3_129B_4CEB_AA28_9F0E55974CC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenFileDialog.h : header file
//

#ifdef TRANSACTIVE_BUILD
namespace TA_Base_App
{
    namespace TA_Reporting
    {
#endif // TRANSACTIVE_BUILD

        /////////////////////////////////////////////////////////////////////////////
        // OpenFileDialog dialog

        class OpenFileDialog : public CFileDialog
        {
	        DECLARE_DYNAMIC(OpenFileDialog)

        public:
	        OpenFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		        LPCTSTR lpszDefExt = NULL,
		        LPCTSTR lpszFileName = NULL,
		        DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		        LPCTSTR lpszFilter = NULL,
		        CWnd* pParentWnd = NULL);

        protected:
	        //{{AFX_MSG(OpenFileDialog)
	        afx_msg void OnDestroy();
	        virtual BOOL OnInitDialog();
	        //}}AFX_MSG
	        DECLARE_MESSAGE_MAP()
        };

#ifdef TRANSACTIVE_BUILD
	} // TA_Reporting
} // TA_Base_App
#endif // TRANSACTIVE_BUILD

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENFILEDIALOG_H__F9A17FE3_129B_4CEB_AA28_9F0E55974CC7__INCLUDED_)
