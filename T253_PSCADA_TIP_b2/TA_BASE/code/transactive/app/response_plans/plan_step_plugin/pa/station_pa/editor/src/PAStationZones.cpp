/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/TA_Product_ECSPlan/TA_BASE/transactive/app/response_plans/plan_manager/src/PAStationZones.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2013/07/17 15:33:29 $
  * Last modified by:  $Author: CM $
  *
  */
// PAStationZones.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PAStationZones.h"
#include "core/data_access_interface/pa/Src/PaZoneGroupAccessFactory.h"
#include "core/data_access_interface/pa/Src/PaZoneGroup.h"
#include "core/data_access_interface/pa/src/PaZoneAccessFactory.h"
#include "core/data_access_interface/pa/src/IPaZone.h"
#include "core/data_access_interface/src/LocationAccessFactory.h"
#include "core/exceptions/src/DataException.h"
#include "bus/response_plans/active_plans_display/src/StringUtilities.h"
#include "bus/generic_gui/src/TransActiveMessage.h"
#include "core/utilities/src/TAAssert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace TA_Base_App;
static const CString ALL_STATIONS     ("<All Stations>");
static const CString ALL_ZONE_GROUPS ("<All Zone Groups>");

/////////////////////////////////////////////////////////////////////////////
// CPAStationZones dialog
CPAStationZones::CPAStationZones(CString stationName, unsigned long stationLocationKey, StationStepParameter& parameter, bool canEdit, const std::map<unsigned long, std::string>& mapLocations) :
    CPlanStepParameterEditDlg(parameter, CPAStationZones::IDD, canEdit),
    m_stations (parameter),
    m_mapLocationKeyToName(mapLocations)
{
    FUNCTION_ENTRY( "CPAStationZones" );

    m_selectedZones = new CStringArray;
    m_zoneIDs         = new CUIntArray;
    m_locationKey = stationLocationKey;
    m_stationName = stationName;
    // {{AFX_DATA_INIT(CPAStationZones)
    m_stationNameStr = _T("");
    // }}AFX_DATA_INIT

    FUNCTION_EXIT;
}

CPAStationZones::~CPAStationZones ()
{
    FUNCTION_ENTRY( "~CPAStationZones" );

    delete m_selectedZones;
    delete m_zoneIDs;

    FUNCTION_EXIT;
}

void CPAStationZones::DoDataExchange(CDataExchange* pDX)
{
    FUNCTION_ENTRY( "DoDataExchange" );

    CDialog::DoDataExchange(pDX);
    // {{AFX_DATA_MAP(CPAStationZones)
    DDX_Control(pDX, IDC_STATIONPA_STATION_NAME_TXT, m_stationNameTxt);
    DDX_Control(pDX, IDC_STATIONPA_UNSELECT_BTN, m_unselectBtn);
    DDX_Control(pDX, IDC_STATIONPA_UNSELECT_ALL_BTN, m_unselectAllBtn);
    DDX_Control(pDX, IDC_STATIONPA_SELECT_BTN, m_selectBtn);
    DDX_Control(pDX, IDC_STATIONPA_SELECT_ALL_BTN, m_selAllBtn);
    DDX_Control(pDX, IDC_STATIONPA_SELECTED_ZONES_LIST, m_selectedZonesLst);
    DDX_Control(pDX, IDC_STATIONPA_AVAILABLE_ZONES_LIST, m_availableZonesLst);
    DDX_Control(pDX, IDC_STATIONPA_ZONE_GROUPS_COMBO, m_zoneGroupsCombo);
    DDX_Text(pDX, IDC_STATIONPA_STATION_NAME_TXT, m_stationNameStr);
    // }}AFX_DATA_MAP

    FUNCTION_EXIT;
}

BEGIN_MESSAGE_MAP(CPAStationZones, CPlanStepParameterEditDlg)
    // {{AFX_MSG_MAP(CPAStationZones)
    ON_BN_CLICKED(IDC_STATIONPA_SELECT_ALL_BTN, OnSelectAllBtn)
    ON_BN_CLICKED(IDC_STATIONPA_SELECT_BTN, OnSelectBtn)
    ON_BN_CLICKED(IDC_STATIONPA_UNSELECT_ALL_BTN, OnUnselectAllBtn)
    ON_BN_CLICKED(IDC_STATIONPA_UNSELECT_BTN, OnUnselectBtn)
    ON_CBN_SELCHANGE (IDC_STATIONPA_ZONE_GROUPS_COMBO, OnZoneGroupSelChange)
    // }}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPAStationZones::OnInitDialog()
{
    FUNCTION_ENTRY( "OnInitDialog" );

    CPlanStepParameterEditDlg::OnInitDialog();

    if (m_stationName.IsEmpty ())
    {
        m_stationNameTxt.SetWindowText (ALL_STATIONS);
    }
    else
    {
        m_stationNameTxt.SetWindowText (m_stationName);
    }

    PopulateZoneGroups();

    FUNCTION_EXIT;
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPAStationZones message handlers

void CPAStationZones::OnCancel()
{
    FUNCTION_ENTRY( "OnCancel" );

    // TODO: Add extra cleanup here

    CDialog::OnCancel();

    FUNCTION_EXIT;
}

void CPAStationZones::OnOK()
{
    FUNCTION_ENTRY( "OnOK" );

    // TODO: Add extra validation here
    // populate zones
    for (int i = 0; i < m_selectedZonesLst.GetCount (); i++)
    {
        CString  zoneName;
        DWORD        zoneID;
        m_selectedZonesLst.GetText (i, zoneName);
        m_selectedZones->Add (zoneName);
        zoneID = m_selectedZonesLst.GetItemData (i);
        m_zoneIDs->Add (zoneID);
    }
    CDialog::OnOK();

    FUNCTION_EXIT;
}

void CPAStationZones::OnSelectAllBtn()
{
    FUNCTION_ENTRY( "OnSelectAllBtn" );

    // TODO: Add your control notification handler code here
    // transfer selected items from available to selected list
    int nCount = m_availableZonesLst.GetCount ();
    int nSelZonesItemCnt = 0;
    CString zoneName;
    if (nCount > 0)
    {
        for (int i = nCount - 1; i >= 0; i--)
        {
            int n = m_availableZonesLst.GetTextLen (i);
            m_availableZonesLst.GetText (i, zoneName.GetBuffer(n));
            nSelZonesItemCnt = m_selectedZonesLst.AddString (zoneName.GetBuffer (n));
            DWORD zoneId = m_availableZonesLst.GetItemData (i);
            m_selectedZonesLst.SetItemData (nSelZonesItemCnt, zoneId);
            m_availableZonesLst.DeleteString (i);
            zoneName.ReleaseBuffer (n);
        }
    }

    FUNCTION_EXIT;
}

void CPAStationZones::OnSelectBtn()
{
    FUNCTION_ENTRY( "OnSelectBtn" );

    // transfer selected items from available to selected list
    int nCount = m_availableZonesLst.GetCount ();
    int nSelZonesItemCnt = 0;
    CString zoneName;
    if (nCount > 0)
    {
        for (int i = nCount - 1; i >= 0; i--)
        {
            if (m_availableZonesLst.GetSel (i))
            {
                int n = m_availableZonesLst.GetTextLen (i);
                m_availableZonesLst.GetText (i, zoneName.GetBuffer(n));

                nSelZonesItemCnt = m_selectedZonesLst.AddString (zoneName.GetBuffer (n));
                DWORD zoneId = m_availableZonesLst.GetItemData (i);
                m_selectedZonesLst.SetItemData (nSelZonesItemCnt, zoneId);
                m_availableZonesLst.DeleteString (i);
                zoneName.ReleaseBuffer (n);
            }
        }
    }

    FUNCTION_EXIT;
}

void CPAStationZones::OnUnselectAllBtn()
{
    FUNCTION_ENTRY( "OnUnselectAllBtn" );

    int nCount = m_selectedZonesLst.GetCount ();
    CString zoneName;
    for (int i = nCount - 1; i >= 0; i--)
    {
        int n = m_selectedZonesLst.GetTextLen (i);
        m_selectedZonesLst.GetText( i, zoneName.GetBuffer(n) );
        // avoid duplication
        if (m_availableZonesLst.FindStringExact (0, zoneName) == CB_ERR)
        {
            m_selectedZonesLst.DeleteString (i);
            m_availableZonesLst.AddString (zoneName.GetBuffer (n));
        }
        zoneName.ReleaseBuffer (n);
    }

    FUNCTION_EXIT;
}

void CPAStationZones::OnUnselectBtn()
{
    FUNCTION_ENTRY( "OnUnselectBtn" );

    // transfer selected items from available to selected list
    int nCount = m_selectedZonesLst.GetCount ();
    CString zoneName;
    for (int i = nCount - 1; i >= 0; i--)
    {
        if (m_selectedZonesLst.GetSel (i))
        {
            int n = m_selectedZonesLst.GetTextLen (i);
            m_selectedZonesLst.GetText( i, zoneName.GetBuffer(n) );
            // avoid duplication
            if (m_availableZonesLst.FindStringExact (0, zoneName) == CB_ERR)
            {
                m_selectedZonesLst.DeleteString (i);
                m_availableZonesLst.AddString (zoneName.GetBuffer (n));
            }
            zoneName.ReleaseBuffer (n);
        }
    }

    FUNCTION_EXIT;
}

void CPAStationZones::PopulateZonesList ()
{
    FUNCTION_ENTRY( "PopulateZonesList" );

    int index;
    std::string zoneName = "";
    try
    {
        // Now load zones based on user selection
        CString zoneGroupName;
        m_zoneGroupsCombo.GetWindowText (zoneGroupName);

        TA_Base_Core::IPaZones zones;
        if (zoneGroupName.Compare (ALL_ZONE_GROUPS) == 0)
        {
            CString stationName;
            m_stationNameTxt.GetWindowText (stationName);
            if (stationName.Compare (ALL_STATIONS) == 0)//get all zones
            {
                zones = TA_Base_Core::PaZoneAccessFactory::getInstance().getAllPaZones();
            }
            else//get all zones for the selected station
            {
                zones = TA_Base_Core::PaZoneAccessFactory::getInstance().getPaZonesByLocationKey(m_locationKey, false);
            }
        }
        else//get zones for the selected station's zone group
        {
            int curSel = m_zoneGroupsCombo.GetCurSel ();
            unsigned long key = m_zoneGroupsCombo.GetItemData (curSel);
            TA_Base_Core::IPaZoneGroup* zoneGroup = TA_Base_Core::PaZoneGroupAccessFactory::getInstance().getPaZoneGroup(key, false);
            zones = zoneGroup->getAssociatedPaZones();
        }

        m_availableZonesLst.ResetContent ();
        for (TA_Base_Core::IPaZonesIt it = zones.begin(); it != zones.end(); ++it)
        {
            TA_Base_Core::IPaZone* zone = *it;
            if ( NULL == zone )
            {
                continue;
            }

            std::map<unsigned long, std::string>::const_iterator itFound = m_mapLocationKeyToName.find( zone->getLocationKey() );
            if ( m_mapLocationKeyToName.end() == itFound )
            {
                continue;
            }

            zoneName = itFound->second + " - " + zone->getLabel();

            // only add if not already in the selected-zones list
            // to prevent duplication
            if (m_selectedZonesLst.FindStringExact (0, zoneName.c_str()) == CB_ERR)
            {
                // Place the zone name in the available-zones listbox
                index = m_availableZonesLst.AddString (zoneName.c_str());
                if (index == LB_ERR)
                {
                    m_availableZonesLst.DeleteString (m_availableZonesLst.FindStringExact (0, zoneName.c_str()));
                    TA_Base_Bus::TransActiveMessage userMsg;
                    UINT selectedButton = userMsg.showMsgBox (IDS_UE_210102);
                }
                // remember unique zone key
                DWORD zoneId = zone->getKey ();
                m_availableZonesLst.SetItemData (index, zoneId);
            }

            delete (*it);
            (*it) = NULL;
        }

        zones.clear();
    }
    catch (TA_Base_Core::DataException&  de)
    {
        LOG_EXCEPTION_CATCH( SourceInfo, "DataException", de.what() );
        TA_Base_Bus::TransActiveMessage userMsg;
        UINT selectedButton = userMsg.showMsgBox (IDS_UE_210102);
        m_availableZonesLst.EnableWindow (FALSE);
    }

    FUNCTION_EXIT;
}

void CPAStationZones::PopulateZoneGroups ()
{
    FUNCTION_ENTRY( "PopulateZoneGroups" );

    TA_Base_Core::IPaZoneGroups zoneGroups;
    int index;
    CString stationName;
    std::string zoneGroupName = "";
    m_stationNameTxt.GetWindowText (stationName);
    try
    {
        if (stationName.Compare (ALL_STATIONS) == 0)
        {
            zoneGroups = TA_Base_Core::PaZoneGroupAccessFactory::getInstance().getAllPaZoneGroups(false);
        }
        else
        {
            zoneGroups = TA_Base_Core::PaZoneGroupAccessFactory::getInstance().getPaZoneGroupsByLocationKey(m_locationKey, false);
        }

        m_zoneGroupsCombo.ResetContent ();
        for (TA_Base_Core::IPaZoneGroupsIt it = zoneGroups.begin(); it != zoneGroups.end(); ++it)
        {
            TA_Base_Core::IPaZoneGroup* zoneGroup = *it;
            if ( NULL == zoneGroup )
            {
                continue;
            }

            if (stationName.Compare (ALL_STATIONS) == 0)
            {
                std::map<unsigned long, std::string>::const_iterator itFound = m_mapLocationKeyToName.find( zoneGroup->getLocationKey() );
                if ( m_mapLocationKeyToName.end() == itFound )
                {
                    continue;
                }
                zoneGroupName = itFound->second + " - " + zoneGroup->getLabel();
            }
            else
            {
                zoneGroupName = zoneGroup->getLabel();
            }
            // Place the zone name in the available-zones listbox
            index = m_zoneGroupsCombo.AddString (zoneGroupName.c_str());
            if (index == LB_ERR)
            {
                m_zoneGroupsCombo.DeleteString (m_availableZonesLst.FindStringExact (0, zoneGroupName.c_str()));
            }
            // remember unique zone group key
            DWORD zoneGroupId = zoneGroup->getKey ();
            m_zoneGroupsCombo.SetItemData (index, zoneGroupId);

            delete (*it);
            (*it) = NULL;
        }

        zoneGroups.clear();

        // Add the default entry.
        index = m_zoneGroupsCombo.AddString (ALL_ZONE_GROUPS);
        m_zoneGroupsCombo.SetItemData (index, 0);
        m_zoneGroupsCombo.SetCurSel( index );
    }
    catch (TA_Base_Core::DataException&  de)
    {
        LOG_EXCEPTION_CATCH( SourceInfo, "DataException", de.what() );
        TA_Base_Bus::TransActiveMessage userMsg;
        // UINT selectedButton = userMsg.showMsgBox (IDS_UE_210116);
        // m_availableZonesLst.EnableWindow (FALSE);
    }

    PopulateZonesList ();

    FUNCTION_EXIT;
}

void CPAStationZones::OnZoneGroupSelChange ()
{
    FUNCTION_ENTRY( "OnZoneGroupSelChange" );

    PopulateZonesList ();

    FUNCTION_EXIT;
}

CUIntArray* CPAStationZones::GetZoneIDs ()
{
    FUNCTION_ENTRY( "GetZoneIDs" );
    FUNCTION_EXIT;
    return m_zoneIDs;
}