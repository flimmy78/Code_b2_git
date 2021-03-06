/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/cctv/video_display_manager/src/VideoDisplayManagerGUI.cpp $
  * @author:  Robert Young
  * @version: $Revision: #8 $
  *
  * Last modification: $DateTime: 2014/09/04 15:42:32 $
  * Last modified by:  $Author: huang.wenbo $
  *
  * TODO: <description>
  */

// VideoDisplayManagerGUI.cpp: implementation of the VideoDisplayManagerGUI class.
//
//////////////////////////////////////////////////////////////////////

#if defined( WIN32 )
#pragma warning( disable : 4786 )
#pragma warning( disable : 4503 )
#endif // defined( WIN32 )

#include "stdafx.h"

#include "app/cctv/video_display_manager/src/VideoDisplayManagerGUI.h"
#include "app/cctv/video_display_manager/src/VideoDisplayManager.h"
#include "app/cctv/video_display_manager/src/VideoDisplayManagerDlg.h"
#include "app/cctv/video_display_manager/src/SwitchAgentCommunicator.h"

#include "bus/user_settings/src/SettingsMgr.h"
#include "bus/application_types/src/apptypes.h"

#include "core/data_access_interface/entity_access/src/DisplayManagerEntityData.h"
#include "core/exceptions/src/GenericGUIException.h"
#include "core/exceptions/src/UserSettingsException.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/RunParams.h"
#include "core/data_access_interface/entity_access/src/IConsole.h"
#include "core/data_access_interface/entity_access/src/ConsoleAccessFactory.h"
#include "core/data_access_interface/src/GlobalParameterAccessFactory.h"
#include "core/exceptions/src/DatabaseException.h"
#include "core/exceptions/src/DataException.h"

using TA_Base_Core::DebugUtil;
using TA_Base_Core::RunParams;
using TA_Base_Bus::SettingsMgr;
using TA_Base_Core::UserSettingsException;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace
{
	bool isInStageOne()
	{
		TA_Base_Core::IGlobalParameter* stageParameter = NULL;
		try
		{
			stageParameter =
				TA_Base_Core::GlobalParameterAccessFactory::getInstance().getGlobalParameterByNameAndSubsystem("VssStageMode", 25);
		}
		catch(const TA_Base_Core::DatabaseException& e)
		{
			LOG_EXCEPTION_CATCH(SourceInfo, "TA_Base_Core::DatabaseException", e.what());
		}
		catch(const TA_Base_Core::DataException& e)
		{
			LOG_EXCEPTION_CATCH(SourceInfo, "TA_Base_Core::DataException", e.what());
		}
		return (stageParameter != NULL && stageParameter->getValue() == "1");
	}
}

namespace TA_IRS_App
{
    VideoDisplayManagerGUI::VideoDisplayManagerGUI()
    : AbstractDialogGUI( IDD_VIDEODISPLAYMANAGER_DIALOG )
    {
        FUNCTION_ENTRY( "VideoDisplayManagerGUI" );
        FUNCTION_EXIT;
    }


    VideoDisplayManagerGUI::~VideoDisplayManagerGUI()
    {
        FUNCTION_ENTRY( "~VideoDisplayManagerGUI" );

        try
        {
            if (getApplicationWnd() != NULL)
            {
                delete getApplicationWnd();
            }
            TA_IRS_App::SwitchAgentCommunicator::getInstance().removeInstance();
        }
        catch( ... )
        {
        }

        FUNCTION_EXIT;
    }


    void VideoDisplayManagerGUI::createApplicationObject()
    {
        FUNCTION_ENTRY( "createApplicationObject" );

        // TD18095, jianghp, to fix the performance of showing manager application
       // VideoDisplayManagerDlg *pDlg = new VideoDisplayManagerDlg(*this);
        // TD18095, jianghp, to fix the performance of showing manager application
		TA_Base_Core::IConsole* console;
		std::string sessionID = TA_Base_Core::RunParams::getInstance().get( RPARAM_SESSIONID );
		console = TA_Base_Core::ConsoleAccessFactory::getInstance().getConsoleFromSession( sessionID );
		std::string locationname = console->getLocationName();
		unsigned long dialogID;
		if(locationname == LOCATION_NAME_OCC)
			dialogID = isInStageOne() ? IDD_VIDEODISPLAYMANAGER_DIALOG_KOCC : IDD_VIDEODISPLAYMANAGER_DIALOG_OCC;
		else if(locationname == LOCATION_NAME_DPT_1)
			dialogID = IDD_VIDEODISPLAYMANAGER_DIALOG_GBD;
		else if(locationname == LOCATION_NAME_DPT_2)
			dialogID = IDD_VIDEODISPLAYMANAGER_DIALOG_GBD;
		else if(locationname == LOCATION_NAME_GBD)
			dialogID = IDD_VIDEODISPLAYMANAGER_DIALOG_GBD;
		else if(locationname == LOCATION_NAME_TMF)
			dialogID = IDD_VIDEODISPLAYMANAGER_DIALOG_TMF;
		else if(locationname == LOCATION_NAME_TDS)
			dialogID = IDD_VIDEODISPLAYMANAGER_DIALOG_TDS;
		else 
			dialogID = IDD_VIDEODISPLAYMANAGER_DIALOG_PSC;
		this->setDlgResourceID (dialogID);

		VideoDisplayManagerDlg *pDlg = new VideoDisplayManagerDlg(*this,dialogID);
        setApplicationWnd( *pDlg);

        FUNCTION_EXIT;
    }


    unsigned long VideoDisplayManagerGUI::getApplicationType()
    {
        FUNCTION_ENTRY( "getApplicationType" );
        FUNCTION_EXIT;
        return VIDIWALL_GUI_APPTYPE;
    }


    void VideoDisplayManagerGUI::checkEntity(TA_Base_Core::IEntityData* guiEntity)
    {
        FUNCTION_ENTRY( "checkEntity" );

        TA_ASSERT( guiEntity != NULL, "The IEntityData pointer passed in was NULL" );

        setGuiEntity( *guiEntity );

        // cast down to the entity type
        TA_Base_Core::DisplayManagerEntityData* entityData = dynamic_cast< TA_Base_Core::DisplayManagerEntityData* >( guiEntity );
        if ( NULL == entityData )
        {
            CString message;
            message.FormatMessage( IDS_UE010016_CANNOT_LOAD_DATA, TA_Base_Core::DisplayManagerEntityData::getStaticType().c_str(), "Entity" );
            TA_THROW( TA_Base_Core::GenericGUIException( std::string( message ), TA_Base_Core::GenericGUIException::ENTITY_CONFIGURATION_INVALID) );
        }

        // load the default display parameter
        try
        {
            VideoDisplayManagerApp* application = dynamic_cast<VideoDisplayManagerApp*>(AfxGetApp());
            TA_ASSERT(application != NULL, "Application is NULL");

            application->setDefaultDwellTime(entityData->getDefaultDwellTime());

						/*
            std::vector<unsigned long> videoWallMonitorKeys(7, 0); // make sure its got 7 entries
            videoWallMonitorKeys[0] = entityData->getLeftTopWallMonitorKey();
            videoWallMonitorKeys[1] = entityData->getLeftMiddleWallMonitorKey();
            videoWallMonitorKeys[2] = entityData->getLeftBottomWallMonitorKey();
            videoWallMonitorKeys[3] = entityData->getOdsWallMonitorKey();
            videoWallMonitorKeys[4] = entityData->getRightTopWallMonitorKey();
            videoWallMonitorKeys[5] = entityData->getRightMiddleWallMonitorKey();
            videoWallMonitorKeys[6] = entityData->getRightBottomWallMonitorKey();

            application->setVideoWallMonitorKeys(videoWallMonitorKeys);
						*/
        }
        catch (TA_Base_Core::TransactiveException&)
        {
            CString message;
            message.FormatMessage( IDS_UE010016_CANNOT_LOAD_DATA, TA_Base_Core::DisplayManagerEntityData::getStaticType().c_str(), "Configuration Data" );
            TA_THROW( TA_Base_Core::GenericGUIException( std::string( message ), TA_Base_Core::GenericGUIException::ENTITY_CONFIGURATION_INVALID) );
        }

        FUNCTION_EXIT;
    }


    void VideoDisplayManagerGUI::checkCommandLine()
    {
        FUNCTION_ENTRY( "checkCommandLine" );

        // TODO: Check any command line arguments specific to this application
        // are available and correct. Throw the specified exception if they
        // are not.

        FUNCTION_EXIT;
    }


    void VideoDisplayManagerGUI::entityChanged(const std::vector<std::string>& changes)
    {
        FUNCTION_ENTRY( "entityChanged" );

        // TODO: Check the changes passed and pass any relevant information on.

        FUNCTION_EXIT;
    }


    void VideoDisplayManagerGUI::serverIsDown()
    {
        FUNCTION_ENTRY( "serverIsDown" );

        // TODO: Get the GUI to update to indicate this.

        FUNCTION_EXIT;
    }


    void VideoDisplayManagerGUI::serverIsUp()
    {
        FUNCTION_ENTRY( "serverIsUp" );

        // TODO: Get the GUI to update to indicate this.

        FUNCTION_EXIT;
    }


    void VideoDisplayManagerGUI::loadAllUserSettings()
    {
        FUNCTION_ENTRY( "loadAllUserSettings" );

        // First check if we should be loading the user settings.

        if ( RunParams::getInstance().get(RPARAM_USERPREFERENCES).empty() )
        {
           setWindowPosition();

           FUNCTION_EXIT;
           return;
        }

        if ( getUserSetting() == NULL )
        {
            setUserSetting(
                     *(new SettingsMgr(getSessionId(), getApplicationType())) );
        }
        loadPositionSettings();
        // TODO: Restore any other settings here

        FUNCTION_EXIT;
    }


    void VideoDisplayManagerGUI::saveAllUserSettings()
    {
        FUNCTION_ENTRY( "saveAllUserSettings" );

        // First check if we should be saving the user settings.
        if ( RunParams::getInstance().get(RPARAM_USERPREFERENCES).empty() )
        {
            FUNCTION_EXIT;
            return;
        }

        if (getUserSetting() == NULL)
        {
            setUserSetting( *(new SettingsMgr(getSessionId(), getApplicationType())) );
        }

        savePositionSettings();

        // TODO: Perform any shutdown tasks here

        FUNCTION_EXIT;
    }


    void VideoDisplayManagerGUI::prepareForClose()
    {
        FUNCTION_ENTRY( "prepareForClose" );

        try
        {
            saveAllUserSettings();
        }
        catch ( UserSettingsException& )
        {
            // Handle here with appropriate errror message
        }

        // TODO: Perform any shutdown tasks here

        FUNCTION_EXIT;
    }


    void VideoDisplayManagerGUI::onInitGenericGUICompleted()
    {
        FUNCTION_ENTRY( "onInitGenericGUICompleted" );
        FUNCTION_EXIT;
    }


/*    void VideoDisplayManagerGUI::setPosition(  const unsigned long posFlag,
                                               const unsigned long alignFlag,
                                               const RECT& objectDim,
                                               const RECT& boundaryDim)
    {
        MessageBox(NULL,"Inside VideoDisplayManagerGUI::setPosition","",MB_OK);
        // TA_Base_Bus::AbstractDialogGUI::AbstractGUIApplication::setPosition(posFlag,alignFlag,objectDim,boundaryDim);

    }
*/

} // TA_IRS_App
