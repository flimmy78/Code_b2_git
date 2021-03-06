/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  *
  * Source:    $File: //depot/4669_T01271350/4669/transactive/app/signs/tis_agent/src/STISAdHocDisplayRequest.cpp $
  * @author:   Robin Ashcroft
  * @version:  $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */

#include "app/signs/tis_agent/src/STISAdHocDisplayRequest.h"
#include "app/signs/tis_agent/src/STISManager.h"
#include "core/data_access_interface/tis_agent/src/DisplayRequestAccessFactory.h"
#include "core/data_access_interface/tis_agent/src/DisplayRequestData.h"

#include <iomanip>

namespace TA_IRS_App
{

	STISAdHocDisplayRequest::STISAdHocDisplayRequest()
        : STISMessage()
	{
		m_messageIDString = "M11";
	}


	STISAdHocDisplayRequest::~STISAdHocDisplayRequest()
	{
	}


	std::vector<unsigned char> STISAdHocDisplayRequest::createProtocolMessage()
	{
		std::vector<unsigned char> messageVector;
		std::stringstream messageStream;

		// Add the sequence number
		messageStream << getSequenceNumberAsString();

		// Add the timestamp to the message
		messageStream << m_timestamp;

		// Now the message ID
		messageStream << m_messageIDString; // M11

		// Now the actual data - this needs to be created separately
		// because the length of the data needs to be indicated 
		// before the data itself (i.e we need to calculate the size of it)

		std::stringstream dataStream;

		// Message destination (MSGDEST)
        dataStream << getMessageDestinationString(m_destination);

		// MESSAGE (MSGFREE) 'FIELDS'
		
		// Message Tag - this is actually the timestamp for M11 messages
		// format is YYMMDDHHMMSS as opposed to YYYYMMDDHHMMSS used everywhere else in the protocol
		for( int i=2 ; i < m_timestamp.size() ; i++ )
		{
			dataStream << m_timestamp[i];
		}

		// Start Time
		dataStream << m_startTime;

		// End Time
		dataStream << m_endTime;

		// Priority
		dataStream << m_priority;

		// DISPLAYEFFECT fields
		
		// Display Mode
		dataStream << getDisplayAttributesAsString();

		// PLASMAFONT fields
		dataStream << getPlasmaFontAttributesAsString();
		
		// LEDFONT fields
		dataStream << getLedFontAttributesAsString();

		// message length
		dataStream << std::setw(3) << std::setfill('0') << m_message.size();

		// The actual message
		dataStream << m_message;
		
		// Calculate the data length - this is variable
		std::string dataString = dataStream.str();
		int dataSize = dataString.size();

        // add the data size to the stream
		messageStream << std::setw(4) << std::setfill('0') << dataSize;
		
		// Add the data stream to the actual message stream after calculating it
		messageStream << dataString;	

		// No train data

		std::string messageString = messageStream.str();
		unsigned int j;

		messageVector.push_back( 0x02 );
		for(j=0;j < messageString.size() ; j++)
		{
			messageVector.push_back( messageString[j] );
		}
		messageVector.push_back( 0x03 );
				
		return messageVector;
	}


	void STISAdHocDisplayRequest::log(bool sendSuccess)
	{
		TA_ASSERT(m_dataIsSet, "Log() called for Adhoc display request that has no data");

        TA_IRS_Core::IDisplayRequest* displayRequest = TA_IRS_Core::DisplayRequestAccessFactory::getInstance().createNewDisplayRequest();

		if( displayRequest )
		{
			displayRequest->setAdhocMessageContent( m_message );
			displayRequest->setDestinationSystem( "STIS" );
			displayRequest->setStartTime( m_startTime );
			displayRequest->setEndTime( m_endTime );
			displayRequest->setPriority( m_priority );
			displayRequest->setTimestamp( m_timestamp );
            displayRequest->setMessageType( TA_IRS_Core::IDisplayRequest::ADHOC );
			displayRequest->setSubmittedBy( m_submittedBy );
			//hongran++ TD17502
			displayRequest->setIfSendSuccess(sendSuccess ? TA_Base_Core::Pass : TA_Base_Core::Fail);
			//++hongran TD17502

			displayRequest->setStisDestinationStation( m_destination.station.in() );
			
			std::stringstream levelStream;

			unsigned int i;
			for( i = 0 ; i < m_destination.levels.length() ; i++ )
			{
				// Add a space before the next level name
				// this ensures that we don't add one at the end
				if( i > 0 )
				{
					levelStream << " ";
				}

				levelStream << m_destination.levels[i].in();
			}

			displayRequest->setStisDestinationLevels( levelStream.str() );

			std::stringstream pidStream;
			for( i = 0 ; i < m_destination.pids.length() ; i++ )
			{
				// Add a space before the next level name
				// this ensures that we don't add one at the end
				if( i > 0 )
				{
					pidStream << " ";
				}

				pidStream << m_destination.pids[i].in();
			}

			std::string wtf = pidStream.str();

			displayRequest->setStisDestinationPids( pidStream.str() );

			displayRequest->setDisplayAttributes( m_displayAttributes );

			displayRequest->setPlasmaAttributes( m_plasmaAttributes );

			displayRequest->setLEDAttributes( m_LEDAttributes );

			// write this display request to the database
			displayRequest->applyChanges();

			delete displayRequest;
			displayRequest = NULL;
		}
		else
		{
			LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugInfo, "Could not create new display request Database object");
		}

	}


	void STISAdHocDisplayRequest::setData( const TA_Base_Core::STISDestination& destination, const std::string& messageContent, 
			const std::string& startTime, const std::string& endTime, unsigned short priority, 
			const TA_Base_Core::DisplayAttributes& displayAttributes,	const TA_Base_Core::PlasmaAttributes& plasmaAttributes, 
			const TA_Base_Core::LEDAttributes& ledAttributes, const std::string& operatorName )
	{
		m_message = messageContent;
		m_destination = destination;
		m_startTime = startTime;
		m_endTime = endTime;
		m_priority = priority;
		m_displayAttributes = displayAttributes;
		m_plasmaAttributes = plasmaAttributes;
		m_LEDAttributes = ledAttributes;
		m_submittedBy = operatorName;

        // repeat interval should be 0 for a continuous message
        if (m_priority < 4)
        {
            m_displayAttributes.repeatInterval = 0;
        }

		m_dataIsSet = true;
	}


	std::string STISAdHocDisplayRequest::getDisplayAttributesAsString()
	{
		std::stringstream attributeStream;

		attributeStream << (int)m_displayAttributes.displayMode;
	
		// Scroll Speed
		switch( m_displayAttributes.scrollSpeed )
		{
            case TA_Base_Core::SCROLL_SLOW:
				attributeStream << "1";
				break;

			case TA_Base_Core::SCROLL_MEDIUM:
				attributeStream << "8";
				break;

			case TA_Base_Core::SCROLL_FAST:
				attributeStream << "F";
				break;
		}

		// repeat interval
	    attributeStream << std::setw(3) << std::setfill('0') << m_displayAttributes.repeatInterval;

		// displayTime
		attributeStream << std::setw(3) << std::setfill('0') << m_displayAttributes.displayTime;

		// Justification
		attributeStream << m_displayAttributes.justification;

		return attributeStream.str();
	}


	std::string STISAdHocDisplayRequest::getPlasmaFontAttributesAsString()
	{
		std::stringstream plasmaFontStream;

        plasmaFontStream << std::hex << std::uppercase // display each attrib as a hex and uppercase if it is A-F
                        << m_plasmaAttributes.fontType
		                << m_plasmaAttributes.fontSize
                        << m_plasmaAttributes.fontColour
		                << m_plasmaAttributes.backgroundColour;

		return plasmaFontStream.str();
	}


	std::string STISAdHocDisplayRequest::getLedFontAttributesAsString()
	{
		std::stringstream ledFontStream;
		
		// This is the Font Type field and is always 0
		ledFontStream << "0";

		ledFontStream << m_LEDAttributes.fontSize;

		switch ( m_LEDAttributes.intensity )
		{
		case TA_Base_Core::INTENSITY_LOW:
			ledFontStream << "1";
			break;

		case TA_Base_Core::INTENSITY_MEDIUM:
			ledFontStream << "4";
			break;

		case TA_Base_Core::INTENSITY_HIGH:
			ledFontStream << "8";
			break;

		}

		ledFontStream << m_LEDAttributes.fontColour;


        // background font colour is not selectable.
        // It was removed from the protocol.

		return ledFontStream.str();
	}


	
}