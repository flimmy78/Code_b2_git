/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/configuration/config_plugins/location/src/LocationFrameworkView.h $
  * @author:  Karen Graham
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * This view contains a splitter. It then loads the left side of the splitter as a list of locations
  * and the right side as a view for the user to configure location details.
  */

#if !defined(AFX_LocationFrameworkView_H__1332EF35_428C_4AA3_8B05_008BBA40FA97__INCLUDED_)
#define AFX_LocationFrameworkView_H__1332EF35_428C_4AA3_8B05_008BBA40FA97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "app/configuration/config_plugins/config_plugin_helper/src/AbstractFrameworkView.h"

namespace TA_Base_App
{

    class LocationFrameworkView : public AbstractFrameworkView
    {
    protected:
        /**
         * Constructor
         *
         * Protected constructor used by dynamic creation
         */
	    LocationFrameworkView();

	    DECLARE_DYNCREATE(LocationFrameworkView)


    public:

    // Overrides
	    // ClassWizard generated virtual function overrides
	    //{{AFX_VIRTUAL(LocationFrameworkView)
	    //}}AFX_VIRTUAL

    // Implementation
    protected:
	    virtual ~LocationFrameworkView();
    #ifdef _DEBUG
	    virtual void AssertValid() const;
	    virtual void Dump(CDumpContext& dc) const;
    #endif

	    // Generated message map functions
    protected:
	    //{{AFX_MSG(LocationFrameworkView)
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


    };

    /////////////////////////////////////////////////////////////////////////////

    //{{AFX_INSERT_LOCATION}}
    // Microsoft Visual C++ will insert additional declarations immediately before the previous line.
}

#endif // !defined(AFX_LocationFrameworkView_H__1332EF35_428C_4AA3_8B05_008BBA40FA97__INCLUDED_)
