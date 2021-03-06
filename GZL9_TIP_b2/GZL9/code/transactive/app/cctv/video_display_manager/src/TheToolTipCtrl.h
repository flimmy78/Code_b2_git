/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/GZL6_TIP/3002/transactive/app/cctv/video_display_manager/src/TheToolTipCtrl.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2012/06/12 13:35:44 $
  * Last modified by:  $Author: builder $
  *
  */
// TheToolTipCtrl.h : header file
//

#if !defined(AFX_THETOOLTIPCTRL_H__45902BB6_F8C5_11D4_97DD_00485450166A__INCLUDED_)
#define AFX_THETOOLTIPCTRL_H__45902BB6_F8C5_11D4_97DD_00485450166A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////////
// CTheToolTipCtrl window

class CTheToolTipCtrl : public CToolTipCtrl
{
// Operations
public:
    CTheToolTipCtrl();
    virtual ~CTheToolTipCtrl();

    // Add a tool window.
    BOOL AddWindowTool(CWnd* pWnd, LPCTSTR pszText);

// Overrides
    // ClassWizard generated virtual function overrides
    // {{AFX_VIRTUAL(CTheToolTipCtrl)
    // }}AFX_VIRTUAL


    // Generated message map functions
protected:
    // {{AFX_MSG(CTheToolTipCtrl)
        // NOTE - the ClassWizard will add and remove member functions here.
    // }}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THETOOLTIPCTRL_H__45902BB6_F8C5_11D4_97DD_00485450166A__INCLUDED_)
