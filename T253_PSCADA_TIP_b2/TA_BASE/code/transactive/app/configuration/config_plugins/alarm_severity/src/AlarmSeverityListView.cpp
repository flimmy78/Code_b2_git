/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/app/configuration/config_plugins/alarm_severity/src/AlarmSeverityListView.cpp $
  * @author:  Dirk McCormick
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/01/23 17:37:20 $
  * Last modified by:  $Author: builder $
  * 
  * This view contains a list of all alarm severities available to be configured. This view must communicate
  * with the AlarmSeverityDetailView as this will show the details of the item selected in this view.
  */


#pragma warning(disable:4786)

#include "app/configuration/config_plugins/alarm_severity/src/StdAfx.h"
#include "app/configuration/config_plugins/alarm_severity/src/AlarmSeverityListView.h"
#include "app/configuration/config_plugins/alarm_severity/src/AlarmSeverityComponent.h"
#include "app/configuration/config_plugins/alarm_severity/src/resource.h"

#include "bus/resources/resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace TA_Base_App
{
    IMPLEMENT_DYNCREATE(AlarmSeverityListView, CListView)


    AlarmSeverityListView::AlarmSeverityListView()
    {
        m_componentIcon = LoadIcon(GetModuleHandle(AlarmSeverityComponent::DLL_NAME), MAKEINTRESOURCE(IDI_CONFIG_ALARM_SEVERITY) );
    }


    AlarmSeverityListView::~AlarmSeverityListView()
    {
    }


BEGIN_MESSAGE_MAP(AlarmSeverityListView, AbstractListView)
	//{{AFX_MSG_MAP(AlarmSeverityListView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


    void AlarmSeverityListView::OnDraw(CDC* pDC)
    {
	    CDocument* pDoc = GetDocument();
    }


    /////////////////////////////////////////////////////////////////////////////
    // AlarmSeverityListView diagnostics

    #ifdef _DEBUG
    void AlarmSeverityListView::AssertValid() const
    {
	    AbstractListView::AssertValid();
    }

    void AlarmSeverityListView::Dump(CDumpContext& dc) const
    {
	    AbstractListView::Dump(dc);
    }
    #endif //_DEBUG

 
}

