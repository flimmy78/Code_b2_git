/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $Source$
  * @author:  Adam Radics
  * @version: $Revision$
  *
  * Last modification: $Date$
  * Last modified by:  $Author$
  *
  */
#include "bus/trains/TrainProtocolLibrary/src/ChangeAreaCommandReceivedEvent.h"
#include "bus/trains/TrainCommonLibrary/src/ProtocolException.h"

#include "core/utilities/src/DebugUtil.h"

#include <sstream>
#include <iomanip>


namespace TA_IRS_Bus
{
    const TrainMessageType ChangeAreaCommandReceivedEvent::MESSAGE_TYPE = 77;
    const unsigned short ChangeAreaCommandReceivedEvent::EXPECTED_MESSAGE_LENGTH = 8;
    const unsigned short ChangeAreaCommandReceivedEvent::AREA_POSITION = 5;


    ChangeAreaCommandReceivedEvent::ChangeAreaCommandReceivedEvent( const TrainMessageData& data,
                                                                    const std::string& sendingTsi,
                                                                    const std::string& destinationTsi )
        : TimsEvent( data, sendingTsi, destinationTsi )
    {
        FUNCTION_ENTRY( "ChangeAreaCommandReceivedEvent" );

        m_area = static_cast<ETrainArea>( getByte( AREA_POSITION ) );

        switch ( m_area )
        {
            // Valid types

            case MainlineArea:

            case DepotArea:
                break;

            // invalid types
            default:
                std::ostringstream areaCode;
                areaCode << static_cast<int> ( m_area );
                TA_THROW( ProtocolException( "Invalid Area Code (Status12)", "Area (Status12)", areaCode.str() ) );
        }

        FUNCTION_EXIT;
    }


    ChangeAreaCommandReceivedEvent::~ChangeAreaCommandReceivedEvent()
    {
        FUNCTION_ENTRY( "~ChangeAreaCommandReceivedEvent" );
        FUNCTION_EXIT;
    }


    TrainMessageType ChangeAreaCommandReceivedEvent::getStaticType()
    {
        FUNCTION_ENTRY( "getStaticType" );
        FUNCTION_EXIT;
        return MESSAGE_TYPE;

    }


    ETrainArea ChangeAreaCommandReceivedEvent::getArea() const
    {
        FUNCTION_ENTRY( "getArea" );
        FUNCTION_EXIT;
        return m_area;

    }


    std::string ChangeAreaCommandReceivedEvent::getLogString() const
    {
        FUNCTION_ENTRY( "getLogString" );

        // appends more information in the format:
        // "[Area=X]"
        std::ostringstream logStream;
        logStream << TimsEvent::getLogString();
        logStream << "[Area=" << static_cast<int> ( m_area ) << "]";

        FUNCTION_EXIT;
        return logStream.str();
    }


    unsigned short ChangeAreaCommandReceivedEvent::getExpectedMessageLength() const
    {
        FUNCTION_ENTRY( "getExpectedMessageLength" );
        FUNCTION_EXIT;
        return EXPECTED_MESSAGE_LENGTH;
    }

}  //end of namespace
