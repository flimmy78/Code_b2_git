#ifndef STISMESSAGE_H_INCLUDED
#define STISMESSAGE_H_INCLUDED

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  *
  * Source:    $File$
  * @author:   Robin Ashcroft
  * @version:  $Revision$
  *
  * Last modification: $DateTime$
  * Last modified by:  $Author$
  *
  */

#include <vector>
#include <string>

// IDL compiler-produced header file
#include "core/data_access_interface/tis_agent_4669/IDL/src/TISMessageDataDefinitions.h"

#include "core/synchronisation/src/ReEntrantThreadLockable.h"

namespace TA_IRS_App
{

	class STISMessage
	{


	public:


		/**
		  * constructor
		  *
		  * @return     nothing.
		  *
		  */
		STISMessage();

		/**
		  * StatusMonitor
		  *
		  * Destructor
		  *
		  * @return     none.
		  *
		  */
		virtual ~STISMessage();


		// Other methods

		virtual std::vector<unsigned char> createProtocolMessage() = 0;

		virtual void log(bool sendSuccess) = 0;

		// set 'nack' true if the response was an A99 NACK message
		void setResponse( const std::vector<unsigned char>& responseData, bool nack );

		void setData();

		bool hasReceivedResponse();

		bool receivedNackResponse();

		void setSequenceNumber( unsigned long seqNumber );

		int getSequenceNumber();

		std::string getMessageID();

        std::string getTimestamp();

		static std::string createLogMessage(const std::vector<unsigned char>& protocolMessage);
	protected:

		// Protocol helper methods

		std::string getSequenceNumberAsString();

        /** 
          * getMessageDestinationString
          *
          * Builds the MSGDEST part of the protocol packet given a destination structure.
          *
          * @param destination  The destination structure
          *
          * @return A MSGDEST string according to the protocol
          */
        std::string getMessageDestinationString(const TA_Base_Core::STISDestination& destination);

	    /**
	      * getNewTimestampString
	      *
	      * Returns the current time as a string in the format defined in the TIS SICD
	      * i.e YYYYMMDDHHMMSS
	      * 
	      * @return      nothing
	      * @param       Current time as a string formatted as above
	      */
		std::string getNewTimestampString();

		// Unique sequence number to match a response message to
		int m_sequenceNumber;

		// Sequence number above in string form, to be used in protocol messages
		std::string m_sequenceNumberString;

		// Time the message was sent by the agent to the STIS server
		std::string m_timestamp;

		// Indicates whether the response message has been received from the STIS server
		bool m_receivedResponse;

		// Indicates whether the response was a NACK message
		bool m_nacked;

		// Indicates whether the data members have been set
		bool m_dataIsSet;

		// The response message byte stream
		std::vector<unsigned char> m_responseMessage;

		// Stores the messages ID - defined in the TIS SICD protocol document e.g. M10
		std::string m_messageIDString;

		// e.g 'OCC', 'DBG' 
		std::string m_location;

		// Only create one new timestamp at any point in time
		TA_Base_Core::ReEntrantThreadLockable m_timestampLock;


	private:

	};

}

#endif // STATUSMONITOR_H_INCLUDED