/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/configuration/config_plugins/subsystem/src/SubsystemFrameworkView.cpp $
  * @author:  Dirk McCormick
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * This view contains a splitter. It then loads the left side of the splitter as a list of subsystems
  * and the right side as a view for the user to configure subsystem details.
  */

#pragma warning(disable:4786)

#include "app/configuration/config_plugins/subsystem/src/StdAfx.h"
#include "app/configuration/config_plugins/subsystem/src/SubsystemFrameworkView.h"

#include "app/configuration/config_plugins/subsystem/src/SubsystemListView.h"
#include "app/configuration/config_plugins/subsystem/src/SubsystemDetailView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using TA_Base_Core::DebugUtil;

namespace TA_Base_App
{
    IMPLEMENT_DYNCREATE(SubsystemFrameworkView, CView)


    SubsystemFrameworkView::SubsystemFrameworkView()
    {
    }


    SubsystemFrameworkView::~SubsystemFrameworkView()
    {
    }


BEGIN_MESSAGE_MAP(SubsystemFrameworkView, AbstractFrameworkView)
	//{{AFX_MSG_MAP(SubsystemFrameworkView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

    
    CRuntimeClass* SubsystemFrameworkView::getRuntimeClassForDetailView()
    {
        return RUNTIME_CLASS(SubsystemDetailView);
    }


    CRuntimeClass* SubsystemFrameworkView::getRuntimeClassForListView()
    {
        return RUNTIME_CLASS(SubsystemListView);
    }

    
    /////////////////////////////////////////////////////////////////////////////
    // SubsystemFrameworkView diagnostics

    #ifdef _DEBUG
    void SubsystemFrameworkView::AssertValid() const
    {
	    AbstractFrameworkView::AssertValid();
    }

    void SubsystemFrameworkView::Dump(CDumpContext& dc) const
    {
	    AbstractFrameworkView::Dump(dc);
    }
    #endif //_DEBUG

}



