/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  *
  * Source:    $File: //depot/GZL6_TIP/3002/transactive/app/cctv/video_switch_agent/src/VideoOutput.cpp $
  * @author:   Katherine Thomson
  * @version:  $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/08/13 14:55:34 $
  * Last modified by:  $Author: huang.wenbo $
  *
  * Handles all the common functions of video outputs.
  * Implements the IVideoOutput interface. 
  * Uses the IPDVideoOutput interface to perform the protocol
  * dependent sections of the control functions.
  */

#ifdef _MSC_VER
#pragma warning( disable : 4786 )
#endif // _MSC_VER

#include <sstream>

#include "app/cctv/video_switch_agent/src/VideoOutput.h"
#include "app/cctv/video_switch_agent/src/AgentModeMonitor.h"
#include "app/cctv/video_switch_agent/src/SwitchManager.h"
#include "app/cctv/video_switch_agent/src/VideoInput.h"
#include "app/cctv/video_switch_agent/protocols/src/PDInterfaceFactory.h"
#include "app/cctv/video_switch_agent/src/VisualAuditMessageSender.h"

#include "bus/security/access_control/actions/src/AccessControlledActions.h"
#include "bus/generic_agent/src/GenericAgent.h"

#include "core/configuration_updates/src/ConfigUpdateDetails.h"
#include "core/data_access_interface/entity_access/src/EntityAccessFactory.h"
#include "core/exceptions/src/DatabaseException.h"
#include "core/exceptions/src/DataException.h"
#include "core/exceptions/src/VideoSwitchAgentInternalException.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/TAAssert.h"
#include "core/data_access_interface/entity_access/src/IConsole.h"
#include "core/data_access_interface/entity_access/src/ConsoleAccessFactory.h"
#include "core/data_access_interface/src/SessionAccessFactory.h"

namespace TA_IRS_App
{

    //
    // VideoOutput
    //
    VideoOutput::VideoOutput( TA_Base_Core::IEntityDataPtr entityData )
        :   VideoSwitchResource( entityData ),
            m_videoOutputData( boost::dynamic_pointer_cast<TA_Base_Core::VideoOutput>(entityData) ), 
            m_pdVideoOutput( 0 )
    {
        // Store the database data.

        if ( 0 == m_videoOutputData.get() )
        {
            TA_THROW( TA_Base_Core::VideoSwitchAgentInternalException( 
                TA_Base_Core::VideoSwitchAgentInternalException::INVALID_CONFIG,
                "The provided entity data is not VideoOutput data." ) );
        }

        // Create an object to handle the protocol dependent work for the VideoOutput.

        m_pdVideoOutput = std::auto_ptr< IPDVideoOutput >( getPDInterfaceFactory().createVideoOutput( m_videoOutputData ) );
        if ( 0 == m_pdVideoOutput.get() )
        {
            // m_videoOutputData is cleaned up by GenericAgent, so we don't have to clean it up here.

            TA_THROW( TA_Base_Core::VideoSwitchAgentInternalException( 
                TA_Base_Core::VideoSwitchAgentInternalException::CREATION_FAILED, "Failed to create IPDVideoOutput." ) );
        }
    }

    
    //
    // ~VideoOutput
    //
    VideoOutput::~VideoOutput()
    {
        // If an exception is thrown here, there is nothing we can do, 
        // but we should make sure no exceptions are thrown out of this destructor.

        try
        {
            // Do not delete this object because it is owned by GenericAgent.

            //m_videoOutputData = 0;
        }
        catch( const TA_Base_Core::TransactiveException& e )
        {
            LOG_EXCEPTION_CATCH( SourceInfo, "TransactiveException", e.what() );
        }
        catch( ... )
        {
             LOG_EXCEPTION_CATCH( SourceInfo, "Unknown Exception", "Reason unknown" );           
        }
    }
        
    
    ///////////////////////////////////////////////////////////////////////
    //
    // State Update Methods
    //
    ///////////////////////////////////////////////////////////////////////

    
    //
    // updateState
    //
    void VideoOutput::updateState( const TA_Base_Bus_GZL9::VideoOutputCorbaDef::VideoOutputState& state )
    {
        LOG_FUNCTION_ENTRY( SourceInfo, "updateState" );

        TA_ASSERT( 0 != m_pdVideoOutput.get(), "The object handling the protocol dependent video output tasks is NULL" );
        m_pdVideoOutput->updateState( state );

        LOG_FUNCTION_EXIT( SourceInfo, "updateState" );
    }


    ///////////////////////////////////////////////////////////////////////
    //
    // VideoOutputCorbaDef Methods
    //
    ///////////////////////////////////////////////////////////////////////
        
    
    //
    // getVideoOutputState
    //
    TA_Base_Bus_GZL9::VideoOutputCorbaDef::VideoOutputState* VideoOutput::getVideoOutputState()
    {
        TA_Base_Bus::GenericAgent::ensureControlMode();//limin

        try
        {
            return m_pdVideoOutput->getVideoOutputState();
        }
        catch( TA_Base_Core::VideoSwitchAgentInternalException& vsiex )
        {
            throw TA_Base_Bus_GZL9::VideoSwitchAgentException( vsiex.what() );
        }
    }


    //
    // getVideoOutputGroupName
    //
    char* VideoOutput::getVideoOutputGroupName()
    {
        TA_Base_Bus::GenericAgent::ensureControlMode();//limin

        TA_ASSERT( 0 != m_videoOutputData.get(), "The video output database object has not been set." );

        try
        {
            return CORBA::string_dup( m_videoOutputData->getVideoOutputGroupName().c_str() );
        }
        catch( const TA_Base_Core::DatabaseException& e )
        {
            LOG_EXCEPTION_CATCH( SourceInfo, "DatabaseException", e.what() );
            LOG_EXCEPTION_DETAILS( SourceInfo, "DatabaseException", "Converting to ExceptionsCorbaDef::VideoSwitchAgentException" );
            throw TA_Base_Bus_GZL9::VideoSwitchAgentException( e.what() );
        }
        catch( const TA_Base_Core::DataException& e )
        {
            LOG_EXCEPTION_CATCH( SourceInfo, "DataException", e.what() );
            LOG_EXCEPTION_DETAILS( SourceInfo, "DataException", "Converting to ExceptionsCorbaDef::VideoSwitchAgentException" );
            throw TA_Base_Bus_GZL9::VideoSwitchAgentException( e.what() );
        }    
        return 0;
    }


    //
    // getCurrentVideoInputKey
    //
    unsigned long VideoOutput::getCurrentVideoInputKey()
    {
        TA_Base_Bus::GenericAgent::ensureControlMode();//limin

        TA_ASSERT( 0 != m_pdVideoOutput.get(), "The object handling the protocol dependent video output tasks is NULL" );

        try
        {
            return m_pdVideoOutput->getCurrentVideoInputKey();
        }
        catch( TA_Base_Core::VideoSwitchAgentInternalException& vsiex )
        {
            throw TA_Base_Bus_GZL9::VideoSwitchAgentException( vsiex.what() );
        }
    }


    //
    // requestSwitchOfInput
    //
    void VideoOutput::requestSwitchOfInput( unsigned long videoInputEntityKey, 
                                            const char* sessionId, bool isDemand )
    {
        LOG_FUNCTION_ENTRY( SourceInfo, "requestSwitchOfInput" );

        TA_ASSERT( 0 != m_pdVideoOutput.get(), "The object handling the protocol dependent video output tasks is NULL" );


        VideoInput* videoInput;
        if ( videoInputEntityKey != 0 )
        {
			// if input is not 0, check if the input exist, if not exist, will throw
            videoInput = &(SwitchManager::getInstance().getVideoInputInternal( videoInputEntityKey ));
        }

        AgentModeMonitor::getInstance().verifyInControlMode( TA_Visual::REQUEST_SWITCH_OF_INPUT );
        m_userPrivilegeVerifier.verifyRights( sessionId, m_videoOutputData, TA_Base_Bus::aca_CONTROL_MONITOR_VIDEO_ASSIGNMENT, "Switch Monitor Video Input" );
 
        // Verify that the user holds the lock for the given input.  
        // This will throw an exception as documented in the comment for this method.
 
        // FUTURE TODO - Do we need this?     videoInput->verifyUserHoldsLock( sessionId );
       
        try
        {
            m_pdVideoOutput->requestSwitchOfInput( videoInputEntityKey, isDemand );
        }
        catch( TA_Base_Core::VideoSwitchAgentInternalException& vsiex )
        {
           throw TA_Base_Bus_GZL9::VideoSwitchAgentException( vsiex.what() );
        }

                
        LOG_FUNCTION_EXIT( SourceInfo, "requestSwitchOfInput" );
    }

	void VideoOutput::cycleToNextVideoInput( const char* sessionId )
	{
		LOG_FUNCTION_ENTRY( SourceInfo, "cycleToNextVideoInput" );

        TA_ASSERT( 0 != m_pdVideoOutput.get(), "The object handling the protocol dependent video output tasks is NULL" );

        AgentModeMonitor::getInstance().verifyInControlMode( TA_Visual::SEQUENCE_CYCLE_TO_NEXT );
        m_userPrivilegeVerifier.verifyRights( sessionId, m_videoOutputData,
                                              TA_Base_Bus::aca_CONTROL_VIDEO_INPUT, 
                                              TA_Visual::SEQUENCE_CYCLE_TO_NEXT );

        m_pdVideoOutput->cycleToNextVideoInput();

        LOG_FUNCTION_EXIT( SourceInfo, "cycleToNextVideoInput" );
    }
	
	void VideoOutput::cycleToPreviousVideoInput( const char* sessionId )
	{
		LOG_FUNCTION_ENTRY( SourceInfo, "cycleToPreviousVideoInput" );

        TA_ASSERT( 0 != m_pdVideoOutput.get(), "The object handling the protocol dependent video output tasks is NULL" );

        AgentModeMonitor::getInstance().verifyInControlMode( TA_Visual::SEQUENCE_CYCLE_TO_PREVIOUS );
        m_userPrivilegeVerifier.verifyRights( sessionId, m_videoOutputData,
                                              TA_Base_Bus::aca_CONTROL_VIDEO_INPUT, 
                                              TA_Visual::SEQUENCE_CYCLE_TO_PREVIOUS );

        m_pdVideoOutput->cycleToPreviousVideoInput();

        LOG_FUNCTION_EXIT( SourceInfo, "cycleToPreviousVideoInput" );
	}

	void VideoOutput::pause( const char* sessionId )
	{
		LOG_FUNCTION_ENTRY( SourceInfo, "pause" );

        TA_ASSERT( 0 != m_pdVideoOutput.get(), "The object handling the protocol dependent video output tasks is NULL" );

        AgentModeMonitor::getInstance().verifyInControlMode( TA_Visual::SEQUENCE_PAUSE );
        m_userPrivilegeVerifier.verifyRights( sessionId, m_videoOutputData,
                                              TA_Base_Bus::aca_CONTROL_VIDEO_INPUT, 
                                              TA_Visual::SEQUENCE_PAUSE );

        m_pdVideoOutput->pause();

        LOG_FUNCTION_EXIT( SourceInfo, "pause" );
	}

	void VideoOutput::play( const char* sessionId )
	{
		LOG_FUNCTION_ENTRY( SourceInfo, "play" );

        TA_ASSERT( 0 != m_pdVideoOutput.get(), "The object handling the protocol dependent video output tasks is NULL" );

        AgentModeMonitor::getInstance().verifyInControlMode( TA_Visual::SEQUENCE_PLAY );
        m_userPrivilegeVerifier.verifyRights( sessionId, m_videoOutputData,
                                              TA_Base_Bus::aca_CONTROL_VIDEO_INPUT, 
                                              TA_Visual::SEQUENCE_PLAY );

        m_pdVideoOutput->play();

        LOG_FUNCTION_EXIT( SourceInfo, "play" );
	}
	
	void VideoOutput::stop( const char* sessionId )
	{
		LOG_FUNCTION_ENTRY( SourceInfo, "stop" );

        TA_ASSERT( 0 != m_pdVideoOutput.get(), "The object handling the protocol dependent video output tasks is NULL" );

        AgentModeMonitor::getInstance().verifyInControlMode( TA_Visual::SEQUENCE_STOP );
        m_userPrivilegeVerifier.verifyRights( sessionId, m_videoOutputData,
                                              TA_Base_Bus::aca_CONTROL_VIDEO_INPUT, 
                                              TA_Visual::SEQUENCE_STOP );

        m_pdVideoOutput->stop();

        LOG_FUNCTION_EXIT( SourceInfo, "stop" );
	}

	/*::CORBA::Boolean VideoOutput::OutputCameraPan(::CORBA::ULong cameraKey, ::CORBA::Char movement, ::CORBA::Char speed)
	{
		try
		{
			LOG3(SourceInfo,TA_Base_Core::DebugUtil::DebugInfo,"VideoOutput::CameraPan will be called.--(%d)(%d)(%d)",cameraKey,movement ,speed);
			m_pdVideoOutput->OutputCameraPan( cameraKey, movement,speed );
		}
		catch( TA_Base_Core::VideoSwitchAgentInternalException& vsiex )
		{
			throw TA_Base_Bus_GZL9::VideoSwitchAgentException( vsiex.what() );
		}

		return true;
	}

	::CORBA::Boolean VideoOutput::OutputCameraTilt(::CORBA::ULong cameraKey, ::CORBA::Char movement, ::CORBA::Char speed) 
	{
		try
		{
			LOG3(SourceInfo,TA_Base_Core::DebugUtil::DebugInfo,"VideoOutput::CameraTilt will be called.--(%d)(%d)(%d)",cameraKey,movement ,speed);
			m_pdVideoOutput->OutputCameraTilt( cameraKey, movement,speed );
		}
		catch( TA_Base_Core::VideoSwitchAgentInternalException& vsiex )
		{
			throw TA_Base_Bus_GZL9::VideoSwitchAgentException( vsiex.what() );
		}

		return true;
	}

	::CORBA::Boolean VideoOutput::OutputCameraZoom(::CORBA::ULong cameraKey, ::CORBA::Char movement)
	{
		try
		{
			LOG2(SourceInfo,TA_Base_Core::DebugUtil::DebugInfo,"VideoOutput::CameraZoom will be called.--(%d)(%d)",cameraKey,movement );
			m_pdVideoOutput->OutputCameraZoom( cameraKey, movement);
		}
		catch( TA_Base_Core::VideoSwitchAgentInternalException& vsiex )
		{
			throw TA_Base_Bus_GZL9::VideoSwitchAgentException( vsiex.what() );
		}

		return true;
	}
	
	::CORBA::Boolean VideoOutput::OutputCameraPTZ(::CORBA::ULong cameraKey, const ::TA_Base_Bus_GZL9::VideoOutputCorbaDef::CameraPTZ& cmd) 
	{
		try
		{
			LOG0(SourceInfo,TA_Base_Core::DebugUtil::DebugInfo,"VideoOutput::CameraPan will be called.");
			m_pdVideoOutput->OutputCameraPTZ( cameraKey, cmd );
		}
		catch( TA_Base_Core::VideoSwitchAgentInternalException& vsiex )
		{
			throw TA_Base_Bus_GZL9::VideoSwitchAgentException( vsiex.what() );
		}
		return true;
	}*/

	void VideoOutput::activeVideoInput( unsigned long videoInputEntityKey,bool active,  
		const char*  sessionId, bool isDemand )
	{
		LOG_FUNCTION_ENTRY( SourceInfo, "activeVideoInput" );

		TA_ASSERT( 0 != m_pdVideoOutput.get(), "The object handling the protocol dependent video output tasks is NULL" );


		VideoInput* videoInput;
		if ( videoInputEntityKey != 0 )
		{
			videoInput = &(SwitchManager::getInstance().getVideoInputInternal( videoInputEntityKey ));
			/*VisualAuditMessageSender::getInstance().sendMessage( VisualAuditMessageSender::SwitchInputToOutputAttempt,
			m_videoOutputData->getKey(),
			sessionId,
			videoInput->getName(),
			m_videoOutputData->getName() );*/
		}

		AgentModeMonitor::getInstance().verifyInControlMode( TA_Visual::REQUEST_SWITCH_OF_INPUT );
		m_userPrivilegeVerifier.verifyRights( sessionId, m_videoOutputData, TA_Base_Bus::aca_CONTROL_MONITOR_VIDEO_ASSIGNMENT, "Switch Monitor Video Input" );

		// Verify that the user holds the lock for the given input.  
		// This will throw an exception as documented in the comment for this method.

		// FUTURE TODO - Do we need this?     videoInput->verifyUserHoldsLock( sessionId );

		try
		{
			m_pdVideoOutput->activeVideoInput( videoInputEntityKey,active, isDemand );
		}
		catch( TA_Base_Core::VideoSwitchAgentInternalException& vsiex )
		{
			throw TA_Base_Bus_GZL9::VideoSwitchAgentException( vsiex.what() );
		}


		LOG_FUNCTION_EXIT( SourceInfo, "activeVideoInput" );
	}

	    //
    // setSequenceConfig
    //
    void VideoOutput::connectSequence( const TA_Base_Bus_GZL9::VideoOutputCorbaDef::UserDefinedSequenceConfig& newConfig ,const char* sessionId ) 
    {

        AgentModeMonitor::getInstance().verifyInControlMode( TA_Visual::SEQUENCE_CYCLE_TO_NEXT );
        m_userPrivilegeVerifier.verifyRights( sessionId, m_videoOutputData,
                                              TA_Base_Bus::aca_CONTROL_VIDEO_INPUT, 
                                              TA_Visual::SEQUENCE_CYCLE_TO_NEXT );
        // Pass to protocol dependent component
       

        try
        {
            m_pdVideoOutput->connectSequence( newConfig);
        }
        catch( TA_Base_Core::VideoSwitchAgentInternalException& vsiex )
		{
			throw TA_Base_Bus_GZL9::VideoSwitchAgentException( vsiex.what() );
		}
    }

	void VideoOutput::disconnectSequence(const char* sessionId )
    {

        AgentModeMonitor::getInstance().verifyInControlMode( TA_Visual::SEQUENCE_CYCLE_TO_NEXT );
        m_userPrivilegeVerifier.verifyRights( sessionId, m_videoOutputData,
                                              TA_Base_Bus::aca_CONTROL_VIDEO_INPUT, 
                                              TA_Visual::SEQUENCE_CYCLE_TO_NEXT );
        // Pass to protocol dependent component
       
        try
        {
            m_pdVideoOutput->disconnectSequence();
        }
        catch( TA_Base_Core::VideoSwitchAgentInternalException& vsiex )
		{
			throw TA_Base_Bus_GZL9::VideoSwitchAgentException( vsiex.what() );
		}
    }
    ///////////////////////////////////////////////////////////////////////
    //
    // IEntity Methods
    //
    ///////////////////////////////////////////////////////////////////////


    //
    // isValid
    //
    bool VideoOutput::isValid()
    {
        return true;
    }
   

    //
    // update
    //
    void VideoOutput::update( const TA_Base_Core::ConfigUpdateDetails& updateEvent )
    {
        TA_ASSERT( 0 != m_videoOutputData.get(), "The database object for the VideoOutput has not been initialised." );
        m_videoOutputData->invalidate();
    
        // FUTURE TODO When adding online updates - may need to notify PD object.
        // FUTURE TODO If you update your corba name you have to reregister and update m_myCorbaName.
    }

	void VideoOutput::requestSwitchOfInputs( unsigned long topRightVideoInputEntityKey, unsigned long topLeftVideoInputEntityKey, unsigned long botRightVideoInputEntityKey, unsigned long botLeftVideoInputEntityKey, const char* sessionId, bool isDemand )
	{
        LOG_FUNCTION_ENTRY( SourceInfo, "requestSwitchOfInput" );

        TA_ASSERT( 0 != m_pdVideoOutput.get(), "The object handling the protocol dependent video output tasks is NULL" );


        VideoInput* topRightVideoInput = NULL;
        VideoInput* topLeftVideoInput = NULL;
        VideoInput* botRightVideoInput = NULL;
        VideoInput* botLeftVideoInput = NULL;
        if ( topRightVideoInputEntityKey != 0 )
        {
			// if input is not 0, check if the input exist, if not exist, will throw
            topRightVideoInput = &(SwitchManager::getInstance().getVideoInputInternal( topRightVideoInputEntityKey ));
        }
        if ( topLeftVideoInputEntityKey != 0 )
        {
			// if input is not 0, check if the input exist, if not exist, will throw
            topLeftVideoInput = &(SwitchManager::getInstance().getVideoInputInternal( topLeftVideoInputEntityKey ));
        }
        if ( botRightVideoInputEntityKey != 0 )
        {
			// if input is not 0, check if the input exist, if not exist, will throw
            botRightVideoInput = &(SwitchManager::getInstance().getVideoInputInternal( botRightVideoInputEntityKey ));
        }
        if ( botLeftVideoInputEntityKey != 0 )
        {
			// if input is not 0, check if the input exist, if not exist, will throw
            botLeftVideoInput = &(SwitchManager::getInstance().getVideoInputInternal( botLeftVideoInputEntityKey ));
        }

        AgentModeMonitor::getInstance().verifyInControlMode( TA_Visual::REQUEST_SWITCH_OF_INPUT );
        m_userPrivilegeVerifier.verifyRights( sessionId, m_videoOutputData, TA_Base_Bus::aca_CONTROL_MONITOR_VIDEO_ASSIGNMENT, "Switch Monitor Video Input" );

 
        // Verify that the user holds the lock for the given input.  
        // This will throw an exception as documented in the comment for this method.
 
        // FUTURE TODO - Do we need this?     videoInput->verifyUserHoldsLock( sessionId );
       
        try
        {
			std::auto_ptr<TA_Base_Core::IConsole> console(TA_Base_Core::ConsoleAccessFactory::getInstance().getConsoleFromSession(sessionId));
            m_pdVideoOutput->requestSwitchOfInputs( topRightVideoInputEntityKey, topLeftVideoInputEntityKey, botRightVideoInputEntityKey, botLeftVideoInputEntityKey, console->getKey(), isDemand );
        }
		catch(TA_Base_Core::TransactiveException& e)
		{
           throw TA_Base_Bus_GZL9::VideoSwitchAgentException( e.what());
		}
        catch( TA_Base_Core::VideoSwitchAgentInternalException& vsiex )
        {
           throw TA_Base_Bus_GZL9::VideoSwitchAgentException( vsiex.what() );
        }

                
        LOG_FUNCTION_EXIT( SourceInfo, "requestSwitchOfInput" );

	}

} // TA_IRS_App

