/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/configuration/config_plugins/action_groups/src/DutyListView.h $
  * @author:  Karen Graham
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * This view contains a list of all dutys available to be configured. This view must communicate
  * with the DutyDetailView as this will show the details of the item selected in this view.
  */

#if !defined(AFX_DutyListView_H__D8199CFB_594F_4ED1_9A1E_632168E5BF11__INCLUDED_)
#define AFX_DutyListView_H__D8199CFB_594F_4ED1_9A1E_632168E5BF11__INCLUDED_

#include <afxcview.h>
#include <string>

#include "app/configuration/config_plugins/config_plugin_helper/src/AbstractListView.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace TA_Base_App
{
    class DutyDetailView;
    class DutyDatabaseAccessor;

    class DutyListView : public AbstractListView
    {
    protected:
        /**
         * Constructor
         *
         * Protected constructor used by dynamic creation
         */
	    DutyListView();


	    DECLARE_DYNCREATE(DutyListView)


	    virtual ~DutyListView();

    // Operations
    public:

    // Overrides
	    // ClassWizard generated virtual function overrides
	    //{{AFX_VIRTUAL(DutyListView)
	    protected:
	    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	    //}}AFX_VIRTUAL

    // Implementation
    protected:
    #ifdef _DEBUG
	    virtual void AssertValid() const;
	    virtual void Dump(CDumpContext& dc) const;
    #endif

	    // Generated message map functions
    protected:
	    //{{AFX_MSG(DutyListView)
	    //}}AFX_MSG
	    DECLARE_MESSAGE_MAP()

    protected:

        /**
         * getComponentIcon
         *
         * This should return the component icon for items to be shown in the list
         *
         * @return HICON - The icon to be shown
         */
        virtual HICON getComponentIcon()
        {
            return m_componentIcon;
        }


        /**
         * getConfigMessageType
         *
         * This should return the type of configuration update. ie ENTITY, OPERATOR etc.
         *
         * @return ConfigUpdateType - The type of component this update is for
         */
        virtual MessageSender::ConfigUpdateType getConfigMessageType() const
        {
            return MessageSender::ACTION_GROUP;
        }

        
    private:
        HICON m_componentIcon;

    };

    /////////////////////////////////////////////////////////////////////////////

    //{{AFX_INSERT_LOCATION}}
    // Microsoft Visual C++ will insert additional declarations immediately before the previous line.
}
#endif // !defined(AFX_DutyListView_H__D8199CFB_594F_4ED1_9A1E_632168E5BF11__INCLUDED_)
