/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/4677_TIP/4677/transactive/app/radio/radio_manager_gui_icdv4/src/RadioSelectedEntity/SelectedEntityDetails/SiteEntityDetailsAreaStrategy.cpp $
 * @author:  Alexis Laredo
 * @version: $Revision: #2 $
 *
 * Last modification: $DateTime: 2009/12/15 19:31:45 $
 * Last modified by:  $Author: grace.koh $
 * 
 */

#include "app/radio/radio_manager_gui_icdv4/src/stdafx.h"
#include "app/radio/radio_manager_gui_icdv4/src/RadioManager.h"
#include "app/radio/radio_manager_gui_icdv4/src/RadioSelectedEntity/SelectedEntityDetails/SiteEntityDetailsAreaStrategy.h"


#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/DebugUtil.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SiteEntityDetailsAreaStrategy::SiteEntityDetailsAreaStrategy()
{
	m_CEntityDetailsAreaDlg = NULL;
}

SiteEntityDetailsAreaStrategy::~SiteEntityDetailsAreaStrategy()
{

}


void SiteEntityDetailsAreaStrategy::initialise(CEntityDetailsAreaDlg* pentityDetailsArea)
{
    FUNCTION_ENTRY("initialise");
    
	TA_ASSERT(pentityDetailsArea != NULL, "pentityDetailsArea is NULL");
	
	m_CEntityDetailsAreaDlg = pentityDetailsArea;

	// hide controls
	m_CEntityDetailsAreaDlg->m_staticText.SetWindowText("");
	m_CEntityDetailsAreaDlg->m_listLB.ShowWindow(SW_HIDE);
	m_CEntityDetailsAreaDlg->m_edit.ShowWindow(SW_HIDE);
	m_CEntityDetailsAreaDlg->m_delete.ShowWindow(SW_HIDE);
	//m_CEntityDetailsAreaDlg->m_deleteMember.ShowWindow(SW_HIDE);
	m_CEntityDetailsAreaDlg->m_save.ShowWindow(SW_HIDE);
	m_CEntityDetailsAreaDlg->m_cancel.ShowWindow(SW_HIDE);

	// clear previously selected resource's members 
	m_CEntityDetailsAreaDlg->m_members.clear();

	// display resource data in edit controls
	m_CEntityDetailsAreaDlg->refresh(IDS_RR_SITE);

	FUNCTION_EXIT;
}

