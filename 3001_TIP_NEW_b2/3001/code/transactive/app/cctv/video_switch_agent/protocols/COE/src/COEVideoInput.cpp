/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  *
  * Source:    $File: //depot/3001_TIP_NEW/3001/transactive/app/cctv/video_switch_agent/protocols/COE/src/COEVideoInput.cpp $
  * @author:   Rob Young
  * @version:  $Revision: #3 $
  *
  * Last modification: $DateTime: 2013/02/20 13:45:32 $
  * Last modified by:  $Author: huang.wenbo $
  *
  * Handles the protocol dependent sections of the operations for a VideoInput
  * using the COE protocol. 
  * Inherits from IPDVideoInput. Before the methods
  * in this interface are called, the user privileges have been checked and
  * that the protocol supports the required features.
  */

#include "app/cctv/video_switch_agent/protocols/COE/src/COEVideoInput.h"
#include "app/cctv/video_switch_agent/src/StateUpdateBroadcaster.h"

#include "core/exceptions/src/DatabaseException.h"
#include "core/exceptions/src/DataException.h"

namespace TA_IRS_App
{
    //
    // COEVideoInput
    //
    COEVideoInput::COEVideoInput( TA_Base_Core::VideoInputPtr videoInputData )
        : m_videoInputData( videoInputData ),
          m_lockOwner( "" )
    {
        // Do nothing.
    }


    ///////////////////////////////////////////////////////////////////////
    //
    // State Update Methods
    //
    ///////////////////////////////////////////////////////////////////////
       
    
    //
    // notifyVideoInputStateUpdated
    //
    void COEVideoInput::notifyVideoInputStateUpdated()
    {            
        try
        {
            StateUpdateBroadcaster::getInstance().notifyVideoInputStateUpdate( m_videoInputData->getKey() );
        }
        catch( const TA_Base_Core::DatabaseException& e )
        {
            LOG_EXCEPTION_CATCH( SourceInfo, "DatabaseException", e.what() );
            LOG_EXCEPTION_DETAILS( SourceInfo, "DatabaseException", 
                "Failed to notify the agent's clients that a VideoInput has changed state." );
        }
        catch( const TA_Base_Core::DataException& e )
        {
            LOG_EXCEPTION_CATCH( SourceInfo, "DataException", e.what() );
            LOG_EXCEPTION_DETAILS( SourceInfo, "DataException", 
                "Failed to notify the agent's clients that a VideoInput has changed state." );
        }	
    }


    //
    // updateState
    //
    void COEVideoInput::updateState( const TA_Base_Bus::VideoInputCorbaDef::VideoInputState& state )
    {
        m_lockOwner = state.sessionIdOfLockOwner;
        //m_videoInputData.setPublicViewingAllowed( state.isPublicViewingAllowed );
        m_videoInputData->setInService( state.isInService );
    }


	///////////////////////////////////////////////////////////////////////
	//
	// IPDVideoInput Methods
	//
	///////////////////////////////////////////////////////////////////////

    
    //
    // lock
    //
    void COEVideoInput::lock( const std::string& sessionId )
    {
        m_lockOwner = sessionId;
        notifyVideoInputStateUpdated();
    }


    //
    // unlock
    //
    void COEVideoInput::unlock( const std::string& sessionId )
    {
        m_lockOwner = "";
        notifyVideoInputStateUpdated();
    }


    //
    // overrideLock
    //
    void COEVideoInput::overrideLock( const std::string& sessionId )
    {
        m_lockOwner = sessionId;
        notifyVideoInputStateUpdated();
    }


    //
    // getLockOwner
    //
    std::string COEVideoInput::getLockOwner()
    {
        return m_lockOwner;
    }


    //
    // verifyUserHoldsLock
    //
	void COEVideoInput::verifyUserHoldsLock( const std::string& sessionId )
    {
        return; // TODO REMOVE THIS
	}


    //
    // isPublicViewingAllowed
    //
    bool COEVideoInput::isPublicViewingAllowed()
    {
        return m_videoInputData->isPublicViewingAllowed();
    }


    //
    // setPublicViewingAllowed
    //
    void COEVideoInput::setPublicViewingAllowed( bool isPublicViewingAllowed )
    {
        m_videoInputData->setPublicViewingAllowed( isPublicViewingAllowed );
        notifyVideoInputStateUpdated();
    }


    //
    // isInService
    //
    bool COEVideoInput::isInService()
    {
        return m_videoInputData->isInService();
    }


    //
    // setInService
    //
    void COEVideoInput::setInService( bool isInService )
    {
        m_videoInputData->setInService( isInService );
        notifyVideoInputStateUpdated();
    }


} // namespace TA_IRS_App

