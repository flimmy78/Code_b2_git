/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/configuration/config_plugins/agent/src/AgentFrameworkView.h $
  * @author:  Karen Graham
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * This view contains a splitter. It then loads the left side of the splitter as a list of agents
  * and the right side as a view for the user to configure agent details.
  */

#if !defined(AFX_AgentFrameworkView_H__1332EF35_428C_4AA3_8B05_008BBA40FA97__INCLUDED_)
#define AFX_AgentFrameworkView_H__1332EF35_428C_4AA3_8B05_008BBA40FA97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "app/configuration/config_plugins/config_plugin_helper/src/AbstractFrameworkView.h"

namespace TA_Base_App
{

    class AgentFrameworkView : public AbstractFrameworkView
    {
    protected:
        /**
         * Constructor
         *
         * Protected constructor used by dynamic creation
         */
	    AgentFrameworkView();

	    DECLARE_DYNCREATE(AgentFrameworkView)


    public:

        /**
         * setComponentInterface
         *
         * This is called by the component interface to register itself with this view. This view
         * is the main view so it provides all communication between the various
         * bits and pieces. This method will also perform any final initialisation required on its
         * child views now that it has all the information it requires.
         */
        virtual void setComponentInterface(IComponent* component);


        /**
         * itemSelected
         *
         * This is called when the user has chosen a toolbar or menu item.
         *
         * @param const CString& - The name of the item selected. This should be exactly
         *                         the same as one of the strings passed in the ToolBarItem::name
         *                         structure or MenuItem::menuItem structure.
         */
        virtual void itemSelected(const CString& item);


        /**
         * changeDetailView
         *
         * This method changes the detail view in the right pane to be the view passed in
         *
         * @param CRuntimeClass* - The view to create and display in the right pane
         */
        virtual void changeDetailView(CRuntimeClass* newView);


    // Overrides
	    // ClassWizard generated virtual function overrides
	    //{{AFX_VIRTUAL(AgentFrameworkView)
	//}}AFX_VIRTUAL

    // Implementation
    protected:
	    virtual ~AgentFrameworkView();
    #ifdef _DEBUG
	    virtual void AssertValid() const;
	    virtual void Dump(CDumpContext& dc) const;
    #endif

	    // Generated message map functions
    protected:
	    //{{AFX_MSG(AgentFrameworkView)
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

        CWnd* m_viewToSwitchTo;
    };

    /////////////////////////////////////////////////////////////////////////////

    //{{AFX_INSERT_LOCATION}}
    // Microsoft Visual C++ will insert additional declarations immediately before the previous line.
}

#endif // !defined(AFX_AgentFrameworkView_H__1332EF35_428C_4AA3_8B05_008BBA40FA97__INCLUDED_)
