/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/response_plans/plan_manager/src/extstatuscontrolbar.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  */
#if (!defined __EXT_STATUSCONTROLBAR_H)
#define __EXT_STATUSCONTROLBAR_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtStatusControlBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtStatusControlBar window

class CExtStatusControlBar : public CStatusBar
{
// Construction
public:

    CExtStatusControlBar();

// Attributes
public:

    // Operations
public:

    int GetPanesCount() const{
        return m_nCount;
    }

    void SetPaneWidth(int nIndex, int nWidth)
    {
        _STATUSBAR_PANE_ pane;
        PaneInfoGet(nIndex, &pane);
        pane.cxText = nWidth;
        PaneInfoSet(nIndex, &pane);
    }

    BOOL AddPane(
        UINT nID,    // ID of the  pane
        int nIndex    // index of the pane
        );

    BOOL RemovePane(
        UINT nID    // ID of the pane
        );

    BOOL AddPaneControl(CWnd* pWnd, UINT nID, BOOL bAutoDestroy)
    {
        return AddPaneControl( pWnd->GetSafeHwnd(), nID, bAutoDestroy);
    }

    BOOL AddPaneControl(HWND hWnd, UINT nID, BOOL bAutoDestroy);

    void DisableControl( int nIndex, BOOL bDisable=TRUE)
    {
        UINT uItemID = GetItemID(nIndex);
        for ( int i = 0; i < m_arrPaneControls.GetSize(); i++ ){
            if( uItemID == m_arrPaneControls[i]->nID ){
                if( m_arrPaneControls[i]->hWnd && ::IsWindow(m_arrPaneControls[i]->hWnd) ) {
                    ::EnableWindow(m_arrPaneControls[i]->hWnd, bDisable);
                }
            }
        }
    }

    void SetPaneInfo(int nIndex, UINT nID, UINT nStyle, int cxWidth)
    {
        CStatusBar::SetPaneInfo(nIndex, nID, nStyle, cxWidth);
        BOOL bDisabled = ((nStyle&SBPS_DISABLED) == 0);
        DisableControl(nIndex, bDisabled);
    }

    void SetPaneStyle(int nIndex, UINT nStyle)
    {
        CStatusBar::SetPaneStyle(nIndex, nStyle);
        BOOL bDisabled = ((nStyle&SBPS_DISABLED) == 0);
        DisableControl(nIndex, bDisabled);
    }

// Overrides
    // ClassWizard generated virtual function overrides
    // {{AFX_VIRTUAL(CExtStatusControlBar)
    // }}AFX_VIRTUAL

// Implementation
public:
    virtual ~CExtStatusControlBar();

protected:

    struct _STATUSBAR_PANE_
    {
        _STATUSBAR_PANE_(){
            nID = cxText = nStyle = nFlags = 0;
        }

        UINT    nID;        // IDC of indicator: 0 => normal text area
        int     cxText;     // width of string area in pixels
        // on both sides there is a 3 pixel gap and
        // a one pixel border, making a pane 6 pixels wider
        UINT    nStyle;     // style flags (SBPS_*)
        UINT    nFlags;     // state flags (SBPF_*)
        CString strText;    // text in the pane
    };

    struct _STATUSBAR_PANE_CTRL_
    {
        HWND hWnd;
        UINT nID;
        BOOL bAutoDestroy;
    };

    CArray < _STATUSBAR_PANE_CTRL_*, _STATUSBAR_PANE_CTRL_* > m_arrPaneControls;

    _STATUSBAR_PANE_* GetPanePtr(int nIndex) const
    {
        ASSERT((nIndex >= 0 && nIndex < m_nCount) || m_nCount == 0);
        return ((_STATUSBAR_PANE_*)m_pData) + nIndex;
    }

    BOOL PaneInfoGet(int nIndex, _STATUSBAR_PANE_* pPane);
    BOOL PaneInfoSet(int nIndex, _STATUSBAR_PANE_* pPane);

    void RepositionControls();

    // Generated message map functions
protected:
    // {{AFX_MSG(CExtStatusControlBar)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    // }}AFX_MSG
    DECLARE_MESSAGE_MAP()
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __EXT_STATUSCONTROLBAR_H
