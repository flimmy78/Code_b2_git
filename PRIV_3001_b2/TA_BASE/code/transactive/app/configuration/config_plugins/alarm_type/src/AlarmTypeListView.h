/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/configuration/config_plugins/alarm_type/src/AlarmTypeListView.h $
  * @author:  Dirk McCormick
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  * 
  * This view contains a list of all alarm types available to be configured. This view must communicate
  * with the AlarmTypeDetailView as this will show the details of the item selected in this view.
  */

#if !defined(AFX_AlarmTypeListView_H__D8199CFB_594F_4ED1_9A1E_632168E5BF11__INCLUDED_)
#define AFX_AlarmTypeListView_H__D8199CFB_594F_4ED1_9A1E_632168E5BF11__INCLUDED_

#include <afxcview.h>
#include <string>

#include "app/configuration/config_plugins/config_plugin_helper/src/AbstractListView.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace TA_Base_App
{
    class AlarmTypeListView : public AbstractListView
    {
    protected:
        /**
         * Constructor
         *
         * Protected constructor used by dynamic creation
         */
	    AlarmTypeListView();

	    virtual ~AlarmTypeListView();

	    DECLARE_DYNCREATE(AlarmTypeListView)


    // Operations
    public:

    // Overrides
	    // ClassWizard generated virtual function overrides
	    //{{AFX_VIRTUAL(AlarmTypeListView)
	    public:
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
	    //{{AFX_MSG(AlarmTypeListView)
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
            return MessageSender::ALARMTYPE;
        }


        /**
         * deleteItem
         *
         * This requires an item to be selected. It will then delete the specified item from the database
         * and the list. We are overwriting the abstract version as we can't delete all alarm types.
         */
        virtual void deleteItem();



        
    private:
        HICON m_componentIcon;
    };

    /////////////////////////////////////////////////////////////////////////////

    //{{AFX_INSERT_LOCATION}}
    // Microsoft Visual C++ will insert additional declarations immediately before the previous line.
}
#endif // !defined(AFX_AlarmTypeListView_H__D8199CFB_594F_4ED1_9A1E_632168E5BF11__INCLUDED_)
