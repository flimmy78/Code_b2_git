/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/configuration/config_plugins/pa_train_dva_message/src/PATrainDvaMessageFrameworkView.h $
  * @author:  Karen Graham
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * This view contains a splitter. It then loads the top of the splitter as a list of PA Train DVA Messages
  * and the bottom as a view for the user to configure a single PA Train DVA Messages details.
  */


#if !defined(AFX_PaTrainDvaMessageFrameworkView_H__1332EF35_428C_4AA3_8B05_008BBA40FA97__INCLUDED_)
#define AFX_PaTrainDvaMessageFrameworkView_H__1332EF35_428C_4AA3_8B05_008BBA40FA97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "app/configuration/config_plugins/config_plugin_helper/src/AbstractFrameworkView.h"

namespace TA_IRS_App
{

    class PaTrainDvaMessageFrameworkView : public TA_Base_App::AbstractFrameworkView
    {
    protected:
        /**
         * Constructor
         *
         * Protected constructor used by dynamic creation
         */
	    PaTrainDvaMessageFrameworkView();

	    DECLARE_DYNCREATE(PaTrainDvaMessageFrameworkView)


    public:

    // Overrides
	    // ClassWizard generated virtual function overrides
	    //{{AFX_VIRTUAL(PaTrainDvaMessageFrameworkView)
	    //}}AFX_VIRTUAL

        // Override Create so we can create a horizontal splitter instead of a vertical one
	    virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

    // Implementation
    protected:
	    virtual ~PaTrainDvaMessageFrameworkView();
    #ifdef _DEBUG
	    virtual void AssertValid() const;
	    virtual void Dump(CDumpContext& dc) const;
    #endif

	    // Generated message map functions
    protected:
	    //{{AFX_MSG(PaTrainDvaMessageFrameworkView)
	    afx_msg void OnSize(UINT nType, int cx, int cy);
    	//}}AFX_MSG
	    DECLARE_MESSAGE_MAP()


        /**
         * getRuntimeClassForListView
         *
         * This returns the runtime class for the list view.
         *
         * @return CRuntimeClass* - The result of a RUNTIME_CLASS call on the
         *                          class name required.
         */
        virtual CRuntimeClass* getRuntimeClassForListView();


        /**
         * getRuntimeClassForDetailView
         *
         * This returns the runtime class for the detail view.
         *
         * @return CRuntimeClass* - The result of a RUNTIME_CLASS call on the
         *                          class name required.
         */
         virtual CRuntimeClass* getRuntimeClassForDetailView();

    private:

        // These constants are used to pass to the splitter methods so the code is more readable
        static const int TOP_PANE;
        static const int BOTTOM_PANE;
        static const int ZERO_COLUMN;
        static const int ONE_COLUMN;

        static const int TOP_PANE_SIZE;
        static const int TOP_RIGHT_PANEL_WIDTH;

        CSplitterWnd m_splitter;    // This splitter separates the list of items and the detail view.
        CSplitterWnd m_topSplitter; // This splitter separates the list of items and global detail view
    };

    /////////////////////////////////////////////////////////////////////////////

    //{{AFX_INSERT_LOCATION}}
    // Microsoft Visual C++ will insert additional declarations immediately before the previous line.
}

#endif // !defined(AFX_PaTrainDvaMessageFrameworkView_H__1332EF35_428C_4AA3_8B05_008BBA40FA97__INCLUDED_)