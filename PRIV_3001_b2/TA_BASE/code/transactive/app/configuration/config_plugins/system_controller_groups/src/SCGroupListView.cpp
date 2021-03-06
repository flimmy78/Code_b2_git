/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/configuration/config_plugins/system_controller_groups/src/SCGroupListView.cpp $
  * @author:  Karen Graham
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  * 
  * This view contains a list of all SC groups available to be configured. This view must communicate
  * with the SCGroupDetailView as this will show the details of the item selected in this view.
  */


#pragma warning(disable:4786)

#include "app/configuration/config_plugins/system_controller_groups/src/StdAfx.h"
#include "app/configuration/config_plugins/system_controller_groups/src/SCGroupListView.h"
#include "app/configuration/config_plugins/system_controller_groups/src/SCGroupComponent.h"
#include "app/configuration/config_plugins/system_controller_groups/src/resource.h"

#include "bus/resources/resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace TA_Base_App
{
    IMPLEMENT_DYNCREATE(SCGroupListView, CListView)


    SCGroupListView::SCGroupListView()
    {
        m_componentIcon = LoadIcon(GetModuleHandle(SCGroupComponent::DLL_NAME), MAKEINTRESOURCE(IDI_CONFIG_SYS_CONTROLLER_GROUP) );
    }


    SCGroupListView::~SCGroupListView()
    {
    }


BEGIN_MESSAGE_MAP(SCGroupListView, AbstractListView)
	//{{AFX_MSG_MAP(SCGroupListView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


    void SCGroupListView::OnDraw(CDC* pDC)
    {
	    CDocument* pDoc = GetDocument();
    }


    /////////////////////////////////////////////////////////////////////////////
    // SCGroupListView diagnostics

    #ifdef _DEBUG
    void SCGroupListView::AssertValid() const
    {
	    AbstractListView::AssertValid();
    }

    void SCGroupListView::Dump(CDumpContext& dc) const
    {
	    AbstractListView::Dump(dc);
    }
    #endif //_DEBUG

 
}

