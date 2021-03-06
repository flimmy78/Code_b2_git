//
// The source code in this file is the property of
// Ripple Systems and is not for redistribution
// in any form.
//
// Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/response_plans/plan_manager/src/PlanStepStationPAPage.cpp $
// @author:  Andy Parker
// @version: $Revision: #5 $
//
// Last modification: $DateTime: 2013/03/20 14:16:56 $
// Last modified by:  $Author: qi.huang $
//
// <description>

#include "StdAfx.h"

#if defined (STEPTYPE_STATION_PUBLIC_ADDRESS)

#include "core/utilities/src/TAAssert.h"
#include "core/data_access_interface/pa_4669/src/PaStationAccessFactory.h"
#include "core/exceptions/src/DataException.h"
#include "core/data_access_interface/pa_4669/src/IPaStation.h"
#include "bus/response_plans/active_plans_display/src/StringUtilities.h"
#include "core/data_access_interface/src/LocationAccessFactory.h"
#include "core/data_access_interface/pa_4669/src/PaZoneAccessFactory.h"
#include "core/data_access_interface/pa_4669/src/IPaZone.h"
#include "core/data_access_interface/pa_4669/src/PaDvaMessageAccessFactory.h"
#include "core/data_access_interface/pa_4669/src/IPaDvaMessage.h"
#include "PlanManager.h"
#include "PlanStepStationPAPage.h"
#include "TextualStepParameter.h"
#include "NumericStepParameter.h"
#include "YesNoStepParameter.h"
#include "PlanNode.h"
#include "PlanManagerCommonDefs.h"
#include "bus/generic_gui/src/TransActiveMessage.h"
#include "PAStationZones.h"
#include "PAMessagesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace TA_Base_App;

static const std::string ALL_STATIONS     ("<All Stations>");


/////////////////////////////////////////////////////////////////////////////
// CPlanStepStationPAPage property page

IMPLEMENT_DYNAMIC(CPlanStepStationPAPage, CPlanStepEditParameterPage)

CPlanStepStationPAPage::CPlanStepStationPAPage(StationPAStep* step)
  : CPlanStepEditParameterPage(CPlanStepStationPAPage::IDD,step)
{
    FUNCTION_ENTRY( "CPlanStepStationPAPage" );

    m_paMessage.messageId  = step->getPaMessageParameter()->getPAMessageId ();
    m_paMessage.libVersion = step->getPaMessageParameter()->getPAMessageLibVersion ();
    m_paMessage.libSection = step->getPaMessageParameter()->getPAMessageLibSection ();

    TA_Base_Core::StationZones zones = step->getPaZonesParameter()->getPAZones();
    for (unsigned int i = 0u; i < zones.length (); ++i)
    {
        m_zoneIds.Add (zones [i]);
    }

    // {{AFX_DATA_INIT(CPlanStepStationPAPage)
    // }}AFX_DATA_INIT

    FUNCTION_EXIT;
}


CPlanStepStationPAPage::~CPlanStepStationPAPage()
{
    FUNCTION_ENTRY( "~CPlanStepStationPAPage" );
    FUNCTION_EXIT;
}


void CPlanStepStationPAPage::DoDataExchange(CDataExchange* pDX)
{
    FUNCTION_ENTRY( "DoDataExchange" );

    CPlanStepEditParameterPage::DoDataExchange(pDX);
    // {{AFX_DATA_MAP(CPlanStepStationPAPage)
    DDX_Control(pDX, IDC_DURATION_DTPICKER, m_durationTime);
    DDX_Control(pDX, IDC_INTERVAL_SPIN, m_intervalSpin);
    DDX_Control (pDX, IDC_INTERVAL_TXT, m_intervalTxt);
    DDX_Control(pDX, IDC_PA_STATION_RADIO, m_stationBtn);
    DDX_Radio  (pDX, IDC_PA_STATION_RADIO, m_station);
    DDX_Check(pDX,IDC_CHIME_CHECK, m_chime);
    DDX_Control (pDX, IDC_CHIME_CHECK, m_chimeBtn);
    DDX_Check(pDX,IDC_CYCLIC_CHECK, m_cyclic);
    DDX_Control (pDX,IDC_CYCLIC_CHECK, m_cyclicBtn);
    DDX_Check(pDX,IDC_TIS_SYNCH_CHECK, m_TISSynch);
    DDX_Control (pDX,IDC_TIS_SYNCH_CHECK, m_TISSynchBtn);
    DDX_Control(pDX, IDC_STATIONS_COMBO, m_stationCombo);
    DDX_Control(pDX, IDC_ZONE_LIST, m_stationZonesLst);
    DDX_CBString (pDX, IDC_STATIONS_COMBO, m_stationName);
    DDX_Control (pDX, IDC_MESSAGE_TXT, m_messageNameTxt);
    // }}AFX_DATA_MAP

    FUNCTION_EXIT;
}


BEGIN_MESSAGE_MAP(CPlanStepStationPAPage, CPlanStepEditParameterPage)
    // {{AFX_MSG_MAP(CPlanStepStationPAPage)
        ON_BN_CLICKED (IDC_PA_STATION_RADIO, OnStationBtn)
        ON_BN_CLICKED (IDC_ALL_PA_STATIONS_RADIO, OnStationBtn)
        ON_CBN_SELCHANGE (IDC_STATIONS_COMBO, OnStationChange)
        ON_BN_CLICKED (IDC_ZONE_DLG__BTN, OnZonesBtn)
        ON_BN_CLICKED (IDC_MSG_DLG_BTN, OnMessagesBtn)
        ON_BN_CLICKED (IDC_CYCLIC_CHECK, OnCyclicBtn)
    // }}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlanStepStationPAPage message handlers

BOOL CPlanStepStationPAPage::OnInitDialog()
{
    FUNCTION_ENTRY( "OnInitDialog" );

    if (!CPlanStepEditParameterPage::OnInitDialog())
    {
        FUNCTION_EXIT;
        return FALSE;
    }

    std::vector<TA_Base_Core::ILocation*> vecLocations = TA_Base_Core::LocationAccessFactory::getInstance().getAllLocations();
    for ( std::vector<TA_Base_Core::ILocation*>::iterator itLoop = vecLocations.begin(); 
        vecLocations.end() != itLoop; ++itLoop )
    {
        m_mapLocationKeyToName[(*itLoop)->getKey()] = (*itLoop)->getDisplayName();
        delete (*itLoop);
        (*itLoop) = NULL;
    }

    m_intervalSpin.SetBuddy(GetDlgItem(IDC_INTERVAL_TXT));
    m_intervalSpin.SetRange(MIN_PA_MESSAGE_INTERVAL, MAX_PA_MESSAGE_INTERVAL);
    m_durationTime.SetFormat("    HH:mm:ss");
    // populate stations
    PopulateStationsCombo ();

    m_stationZonesLst.EnableWindow( TRUE );

    FUNCTION_EXIT;
    return TRUE;
}


void CPlanStepStationPAPage::EnableParameterControls(bool enable)
{
    FUNCTION_ENTRY( "EnableParameterControls" );
    FUNCTION_EXIT;
}


void CPlanStepStationPAPage::DisplayParameters()
{
    FUNCTION_ENTRY( "DisplayParameters" );

    CWaitCursor waitCursor;

    StationPAStep* step = dynamic_cast<StationPAStep*>(GetPlanStep());
    TA_ASSERT(step!=NULL,"Incorrect step type for the PA Station step page");

    try
    {
        std::string st = step->getStationDestinationParameter()->getDestination ().station;
        CString station = st.c_str ();
        m_stationCombo.SetCurSel(m_stationCombo.FindStringExact( 0, station));

        m_stationBtn.SetCheck (station.Compare (ALL_STATIONS.c_str ()) != 0);

        TA_Base_Core::StationZones zones = step->getPaZonesParameter()->getPAZones();
        int zoneCnt = zones.length ();
        m_stationZonesLst.ResetContent ();
        for (int i = 0; i < zoneCnt; i++)
        {
            unsigned long locationKey = zones [i];
            TA_Base_Core::IPaZone* zone = TA_Base_Core::PaZoneAccessFactory::getInstance().getPaZone(locationKey, false);

            std::map<unsigned long, std::string>::const_iterator itFound = m_mapLocationKeyToName.find( zone->getLocationKey() );
            if ( m_mapLocationKeyToName.end() == itFound )
            {
                continue;
            }

            std::string zoneName = itFound->second + " - " + zone->getLabel();

            // Place the zone name in the available-zones listbox
            int index = m_stationZonesLst.AddString (zoneName.c_str());
            if (index == LB_ERR)
            {
                m_stationZonesLst.DeleteString (m_stationZonesLst.FindStringExact (0, zoneName.c_str()));
               TA_Base_Bus::TransActiveMessage userMsg;
                UINT selectedButton = userMsg.showMsgBox (IDS_UE_210102);
            }
        }

        CString messageLabel;
        unsigned long messageId = m_paMessage.messageId;
        if (messageId > 0)
        {
            TA_Base_Core::IPaDvaMessage* paMessage = TA_Base_Core::PaDvaMessageAccessFactory::getInstance().getPaDvaMessage(messageId, false);
            messageLabel = paMessage->getLabel ().c_str ();
        }
        else
        {
            messageLabel = NO_MESSAGE;
        }

        m_messageNameTxt.SetWindowText (messageLabel);
    }
    catch( TA_Base_Core::DatabaseException& dbe )
    {
        LOG_EXCEPTION_CATCH( SourceInfo, "DatabaseException", dbe.what() );
        TA_Base_Bus::TransActiveMessage userMsg;
        UINT selectedButton = userMsg.showMsgBox (IDS_UE_210102);
    }
    catch (TA_Base_Core::DataException&  de)
    {
        LOG_EXCEPTION_CATCH( SourceInfo, "DataException", de.what() );
        TA_Base_Bus::TransActiveMessage userMsg;
        UINT selectedButton = userMsg.showMsgBox (IDS_UE_210102);
    }

    // Initialise duration. Use any valid date with the picker control as it will be suppressed anyway.
    // as per TD 12382
    // for new steps set default duration to 1 sec
    unsigned long initialDuration = step->getMessageDuration()->getNumericValue();
    if (initialDuration == 0)
    {
        initialDuration = 1;
    }

    COleDateTimeSpan duration(0, 0, 0, initialDuration);
    TA_ASSERT(duration.GetDays() == 0, "Invalid message duration");
    COleDateTime durationAsTime(COleDateTime::GetCurrentTime());
    durationAsTime.SetTime(duration.GetHours(), duration.GetMinutes(), duration.GetSeconds());
    m_durationTime.SetTime(durationAsTime);

    m_intervalSpin.SetPos (step->getMessageInterval()->getNumericValue ());

    m_cyclicBtn.SetCheck (step->getCyclicParameter()->getAffirmative ());
    m_TISSynchBtn.SetCheck (step->getTISSynch()->getAffirmative ());
    m_chimeBtn.SetCheck (step->getChimeParameter()->getAffirmative ());


    m_durationTime.EnableWindow (m_cyclicBtn.GetCheck ());
    m_intervalSpin.EnableWindow (m_cyclicBtn.GetCheck ());
    m_intervalTxt.EnableWindow  (m_cyclicBtn.GetCheck ());

    if (!m_cyclicBtn.GetCheck ())
    {
        m_TISSynchBtn.SetCheck (!m_cyclicBtn.GetCheck ());
    }

    m_TISSynchBtn.EnableWindow(!m_cyclicBtn.GetCheck ());

    UpdateData();

    FUNCTION_EXIT;
}


void CPlanStepStationPAPage::UpdateParameters()
{
    FUNCTION_ENTRY( "UpdateParameters" );

    // update stations
    StationPAStep* step = dynamic_cast<StationPAStep*>(GetPlanStep());
    TA_ASSERT(step!=NULL,"Incorrect step type for the PA Station step page");
    if (m_stationBtn.GetCheck ())
    {//single station
        std::string station = m_stationName.GetBuffer (1);
        unsigned long ulLocationKey = m_stationCombo.GetItemData(m_stationCombo.FindStringExact(0, m_stationName ));
        step->getStationDestinationParameter()->setStation (station, ulLocationKey);
    }
    else
    {//all stations
        step->getStationDestinationParameter()->setAllStations();
    }


    // update zones
    step->getPaZonesParameter()->resetZones ();
    for (int i = 0; i < m_zoneIds.GetSize (); i++)
    {
        step->getPaZonesParameter()->addPaZoneID ( m_zoneIds.GetAt (i));
    }

    // update message info
    step->getPaMessageParameter()->setPaMessageId (m_paMessage.messageId);
    step->getPaMessageParameter()->setPAMessageLibVersion (m_paMessage.libVersion);
    step->getPaMessageParameter()->setPAMessageLibSection (m_paMessage.libSection);

    if (m_cyclicBtn.GetCheck ())
    {
     // Update the duration parameter.
     COleDateTime durationAsTime;
    m_durationTime.GetTime(durationAsTime);

    COleDateTimeSpan duration(0, durationAsTime.GetHour(), durationAsTime.GetMinute(), durationAsTime.GetSecond());
    step->getMessageDuration()->setValue(static_cast<unsigned long>(duration.GetTotalSeconds()));
    step->getMessageDuration()->hideValue(step->getMessageDuration()->getNumericValue() == 0);

     step->getMessageInterval()->setValue (m_intervalSpin.GetPos ());
    }

    // update options
    step->getChimeParameter()->setAffirmative (m_chime);
    step->getCyclicParameter()->setAffirmative (m_cyclicBtn.GetCheck ());
    step->getTISSynch()->setAffirmative (m_TISSynch);

    FUNCTION_EXIT;
}


void CPlanStepStationPAPage::OnStationBtn ()
{
    FUNCTION_ENTRY( "OnStationBtn" );

    int oldSel = m_stationCombo.GetCurSel ();
    if (m_stationBtn.GetCheck ())
    {
        m_stationCombo.SetCurSel (m_stationCombo.FindStringExact (0, ALL_STATIONS.c_str()) + 1);
    }
    else
    {
        m_stationCombo.SetCurSel (m_stationCombo.FindStringExact (0, ALL_STATIONS.c_str()));
    }

    m_stationCombo.EnableWindow (m_stationBtn.GetCheck ());

    // reset zones if selection changed
    if (oldSel != m_stationCombo.GetCurSel ())
    {
        m_stationZonesLst.ResetContent ();
        m_zoneIds.SetSize (0);
    }

    UpdateData ();

    FUNCTION_EXIT;
}


void CPlanStepStationPAPage::OnStationChange ()
{
    FUNCTION_ENTRY( "OnStationChange" );

    int selectedStationIdx = m_stationCombo.GetCurSel();

    if (selectedStationIdx != CB_ERR)
    {
        m_stationName.Format( _T("%d"), static_cast<unsigned long>(m_stationCombo.GetItemData(selectedStationIdx)) );
    }
    else
    {
        m_stationName = "";
    }

    // reset zones
    m_stationZonesLst.ResetContent ();
    m_zoneIds.SetSize (0);
    UpdateData ();

    FUNCTION_EXIT;
}


void CPlanStepStationPAPage::OnZonesBtn ()
{
    FUNCTION_ENTRY( "OnZonesBtn" );

    StationPAStep* step = dynamic_cast<StationPAStep*>(GetPlanStep());
    TA_ASSERT(step!=NULL,"Incorrect step type for the PA Station step page");

    StationStepParameter  station = *step->getStationDestinationParameter();
    unsigned long locationKey = m_stationCombo.GetItemData (m_stationCombo.FindStringExact( 0, m_stationName));
    CPAStationZones zonesDlg (m_stationName, locationKey, station, false, m_mapLocationKeyToName);
    if (IDOK == zonesDlg.DoModal())
    {
        CStringArray* stationZones = zonesDlg.GetSelectedZones ();
        m_stationZonesLst.ResetContent ();
        for (int i = 0; i < stationZones->GetSize (); i++)
        {
            m_stationZonesLst.AddString (stationZones->GetAt (i));
        }

        m_zoneIds.SetSize (0);
        for (int i = 0; i < zonesDlg.GetZoneIDs ()->GetSize (); i++)
        {
            m_zoneIds.Add (zonesDlg.GetZoneIDs()->GetAt (i));
        }

    }
    UpdateData ();

    FUNCTION_EXIT;
}


void CPlanStepStationPAPage::OnMessagesBtn ()
{
    FUNCTION_ENTRY( "OnMessagesBtn" );

    StationPAStep* step = dynamic_cast<StationPAStep*>(GetPlanStep());
    TA_ASSERT(step!=NULL,"Incorrect step type for the PA Station step page");

    PaMessageStepParameter messagePar = *step->getPaMessageParameter ();
    unsigned long locationKey = 0;
    if ( 1 == m_station )
    {
        locationKey = TA_Base_Core::LocationAccessFactory::getInstance().getOccLocationKey();
    }
    else
    {
        locationKey= m_stationCombo.GetItemData (m_stationCombo.FindStringExact( 0, m_stationName));
    }
    CPaMessagesDlg messagesDlg (PA_STATION_MESSAGE_TYPE, messagePar, false, locationKey);

    if (IDOK == messagesDlg.DoModal())
    {
        CString message = messagesDlg.GetSelectedMessage ();
        m_messageNameTxt.SetWindowText (message);
        m_paMessage = messagePar.getPAMessage ();
    }

    UpdateData ();

    FUNCTION_EXIT;
}


void CPlanStepStationPAPage::OnCyclicBtn ()
{
    FUNCTION_ENTRY( "OnCyclicBtn" );

    m_durationTime.EnableWindow (m_cyclicBtn.GetCheck ());
    m_intervalSpin.EnableWindow (m_cyclicBtn.GetCheck ());
    m_intervalTxt.EnableWindow (m_cyclicBtn.GetCheck ());
    m_TISSynchBtn.SetCheck (!m_cyclicBtn.GetCheck ());
    m_TISSynchBtn.EnableWindow (!m_cyclicBtn.GetCheck ());
    UpdateData ();

    FUNCTION_EXIT;
}


void CPlanStepStationPAPage::PopulateStationsCombo ()
{
    FUNCTION_ENTRY( "PopulateStationsCombo" );

    int index = 0;
    try
    {
        m_stationCombo.ResetContent ();

        // Now reload all the PA Stations
        TA_Base_Core::IPaStations items = TA_Base_Core::PaStationAccessFactory::getInstance().getAllPaStations();

        for (TA_Base_Core::IPaStationsIt it = items.begin(); it != items.end(); ++it)
        {
            std::map<unsigned long, std::string>::const_iterator itFound = m_mapLocationKeyToName.find( (*it)->getLocationKey() );

            delete (*it);
            (*it) = NULL;

            if ( m_mapLocationKeyToName.end() == itFound )
            {
                continue;
            }

            std::string strStationName = itFound->second;

            // Place the station name in the combo box.
            index = m_stationCombo.AddString(strStationName.c_str());
            if ( CB_ERR == index )
            {
                // If an error occurred on the insert, attempt to remove the new entry,
                // and then move on to the next item.
                m_stationCombo.DeleteString( m_stationCombo.FindStringExact( 0, strStationName.c_str()) );
                continue;
            }
            // also add station key as its required to get zones for particular station
            m_stationCombo.SetItemData ( index, itFound->first );
        }

        items.clear();
    }
    catch( TA_Base_Core::DatabaseException& dbe )
    {
        LOG_EXCEPTION_CATCH( SourceInfo, "DatabaseException", dbe.what() );
        TA_Base_Bus::TransActiveMessage userMsg;
        UINT selectedButton = userMsg.showMsgBox (IDS_UE_210101);
        m_stationCombo.EnableWindow(FALSE);
    }
    catch (TA_Base_Core::DataException&  de)
    {
        LOG_EXCEPTION_CATCH( SourceInfo, "DataException", de.what() );
        TA_Base_Bus::TransActiveMessage userMsg;
        UINT selectedButton = userMsg.showMsgBox (IDS_UE_210101);
        m_stationCombo.EnableWindow(FALSE);
    }

    FUNCTION_EXIT;
}


#endif // defined (STEPTYPE_STATION_PUBLIC_ADDRESS)
