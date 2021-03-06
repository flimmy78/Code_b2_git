
#ifndef ATS_EVENT_H
#define ATS_EVENT_H

#include "app/ats/AtsAgent/AtsMethod/src/AtsITcpEvent.h"

namespace TA_IRS_App
{
	class AtsEventReader;

	class AtsEvent: public AtsITcpEvent
	{
	public:
		AtsEvent(void);
		AtsEvent(const AtsEvent& atsEvent);

		typedef unsigned char   TransactionIDType;
		typedef unsigned char   TrainIDType; 
		typedef unsigned char   StatusType;
		typedef unsigned char   EventType;
		
		virtual ~AtsEvent(void);

	public:
		/**
		* Resets the command to be empty.
		*/
		virtual void clear();
		/**
		* This method is used to determine if the message is complete.  It is used after appending incoming characters to the message.
		*/
		virtual bool isComplete() const;
		/**
		* Get the session this event is intended for
		*/
		TrainIDType getTrainId() const;
		/**
		* Returns the transaction Id for the event which will correspond to the Transaction ID of the associated Method called.
		*/
		   //Note: To be removed.
		//TransactionIDType getTransactionId() const;
		/**
		* Returns the status code for the event
		*/
		   //Note: To be removed.
		//StatusType getStatus() const;
		/**
		* Returns boolean to show if status indicates more data to follow.
		*/
		bool isStatusMoreData() const;
		/**
		* Returns the status text for the event
		*/
		  //Note: To be removed.
		// std::string getTextStatus() const;
		/**
		* Returns the radio event type for the event.
		*/
		EventType getCommandType() const;
		/**
		* Return the specified length of the message as defined in the first bytes.
		*/
		virtual unsigned long getEventLength() const;
		/**
		* Return the specified length of the message header
		*/
		   //To be removed.
		virtual unsigned long getEventHeaderLength() const;
		/**
		* Provides access to the appropriate RadioEventReader for the incoming message.  The reader will be automatically destroyed when the RadioEvent is destroyed.
		*/
		
		AtsEventReader* getEventReader();
	
	private:

		/**
		* Create an event reader that is correct for the type of message.
		*/
		  
		AtsEventReader* createEventReader();
		  
		AtsEventReader*  m_eventReader;
	};
};

#endif //end of ATS_EVENT_H