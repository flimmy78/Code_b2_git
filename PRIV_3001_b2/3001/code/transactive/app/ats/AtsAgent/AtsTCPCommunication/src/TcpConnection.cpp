/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP/3001/transactive/app/radio/RadioTetraAgent/src/RadioTCPConnection.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2009/12/29 14:12:57 $
  * Last modified by:  $Author: grace.koh $
  *
  */
///////////////////////////////////////////////////////////
//
//  RadioTCPConnection.cpp
//  Implementation of the Class RadioTCPConnection
//  Generated by Enterprise Architect
//  Created on:      29-Oct-2003 17:46:16
//  Original author: Andy Parker
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////

#ifdef __WIN32__
#pragma warning(disable:4786)
#endif


#include "core/synchronisation/src/ThreadGuard.h"
#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/DebugUtil.h"

#include "app/ats/AtsAgent/AtsTCPCommunication/src/ObservedSocket.h"
#include "app/ats/AtsAgent/AtsTCPCommunication/src/ITcpConnectionStatusObserver.h"
#include "app/ats/AtsAgent/AtsTCPCommunication/src/TcpConnection.h"
#include "app/ats/AtsAgent/AtsMethod/src/AtsITcpMethod.h"
#include "app/ats/AtsAgent/AtsMethod/src/AtsITcpEvent.h"

//#include "app/radio/RadioTetraAgent/src/RadioKeepAliveHandlerThread.h"
//#include "app/cctv/tvss_agent/TVSSProtocolLibrary/src/ITcpEvent.h"
//#include "app/radio/RadioTetraAgent/RadioProtocolLibrary/src/RadioProtocol.h"


using namespace TA_IRS_App;

using TA_Base_Core::DebugUtil;

TCPConnection::TCPConnection
(   ITcpEventProcessor & eventProcessor,
    IConnectionStatusObserver & observer,
    std::string host,
    std::string service,
    bool isPrimary)
: m_clientSocket(0)
, m_tcpEventPocessor(eventProcessor)
, m_observer(observer)
, m_ignoreIncomingData(false)
, m_event(0)
, m_primary(isPrimary)
, m_identifier(host + ":" + service)
, isConnectionLost(false)
{
    FUNCTION_ENTRY("Constructor");

	m_event = m_tcpEventPocessor.createCompatibleTcpEvent();
    TA_ASSERT(m_event!=0,"Unable to create empty radio event.");
    
	
    LOG_GENERIC(SourceInfo,TA_Base_Core::DebugUtil::DebugDebug,"Creating socket to host: %s, port: %s",host.c_str(),service.c_str());
    m_clientSocket = new ObservedSocket(host,service, *this);
    TA_ASSERT(m_clientSocket!=0,"Unable to create client socket.");

    m_clientSocket->setReconnectInterval(4000);

	m_clientSocket->setPingOption(false);

	FUNCTION_EXIT;
}


TCPConnection::~TCPConnection()
{
	FUNCTION_ENTRY("Destructor");
	m_clientSocket->terminateAndWait();
	
	delete m_clientSocket;
	delete m_event;

	FUNCTION_EXIT;
}

/**
* Sets the connection to primary or secondary.  If primary messages are passed to observer.  
* If secondary messages are discarded.
* @param    method
*/
void TCPConnection::setIgnoreIncomingData(bool bIgnore)
{
    FUNCTION_ENTRY("setIgnoreIncomingData");

	if ( m_ignoreIncomingData != bIgnore )
	{
		m_ignoreIncomingData = bIgnore;
		
	//	m_RadioTimedEvent->setCacheEvent(m_ignoreIncomingData);
		
		// clear any partial events
		m_event->clear();

		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, 
			"current state for m_ignoreIncomingData is %s", 
		(m_ignoreIncomingData ? "true" : "false") );
	}

    FUNCTION_EXIT;
}



void TCPConnection::start()
{
    FUNCTION_ENTRY("start");
    m_clientSocket->start();
    FUNCTION_EXIT;
}



/**
* A thread guard must be used to ensure that a complete message is always sent without interruption.
* @param    method
*/
void TCPConnection::Send(const AtsITcpMethod& method)
{
    FUNCTION_ENTRY("Send");

    // locking is done by the actual socket

    // Log data to be sent
    std::string   hexText = "";
    std::string   consoleText = "";

	const DataGramVector messageDatagramTable = method.getMessageDatagramTable();
	const unsigned char* messageCRC = method.getMessageDataCRC();
	//unsigned short crc = atoi((const char*)messageCRC);
	std::string criticalAlarm = "";
	method.getCriticalAlarm(criticalAlarm);
    // this is a lot of work to do when we're not in debug log level
    //if (DebugUtil::DebugDebug <= DebugUtil::getInstance().getLevel())
    //{
    //    method.getLogText(hexText, consoleText);

    //    LOG_GENERIC( SourceInfo, DebugUtil::DebugDebug, 
    //         "\n\n\t\t\tConnection %s Sending Ats method: %s"
			 //"\n\t\t\t\tStatus: Successfully Sent"
			 //"\n\t\t\tData Sent : %s"
			 //"\n\t\t\tConnection %s Ats method consoleText: %s\n"
			 //"\n\t\t\tFlag           : %.2X"
			 //"\n\t\t\tCommand        : %.2X"
			 //"\n\t\t\tTrain Id       : %.2X"
			 //"\n\t\t\tLength         : %.2X"
			 //"\n\t\t\tOrigin         : %.2X"
			 //"\n\t\t\tCritical Alarm : %s"
			 ////"\n\t\t\tCRC            : %.2X"
			 //, m_identifier.c_str(), typeid(method).name(), hexText.c_str(),m_identifier.c_str(), consoleText.c_str()
			 //, method.getFlag(), method.getCommand(), method.getTrainId(), method.getLength(), method.getOrigin()
			 //, criticalAlarm.c_str());


    //   
    //}

	method.getLogText(hexText, consoleText);
	LOG_GENERIC(SourceInfo,TA_Base_Core::DebugUtil::DebugInfo, 
		"\n\n\t\t\t****** CRITICAL ALARM *******\n"
	    "\n\n\t\t\tConnection %s Sending Ats method: %s"
		"\n\t\t\tStatus: Successfully Sent"
		"\n\t\t\tData Sent : %s"
		"\n\t\t\tConnection %s Ats method consoleText: %s\n"
		"\n\t\t\t*****************************************\n"
		"\n\t\t\tFlag           : %.2X"
		"\n\t\t\tCommand        : %.2X"
		"\n\t\t\tTrain Id       : %.2X"
		"\n\t\t\tLength         : %.2X"
		"\n\t\t\tOrigin         : %.2X\n\n"
		, m_identifier.c_str(), typeid(method).name(), hexText.c_str(),m_identifier.c_str(), consoleText.c_str()
		, method.getFlag(), method.getCommand(), method.getTrainId(), method.getLength(), method.getOrigin());
	//Send the data of the DataGram
    m_clientSocket->sendData(messageDatagramTable);

    FUNCTION_EXIT;
}


void TCPConnection::processReceivedData( SocketData& data, ObservedSocket* socket )
{
	FUNCTION_ENTRY("processReceivedData");

	while (!data.empty())
	{
		// Add to incoming message
		m_event->appendData(data[0]);

		if (m_event->isComplete())
		{
			//RadioEvent * event = dynamic_cast<RadioEvent *>(m_event);

		   if (!m_ignoreIncomingData)
			{
				// Pass the incoming communication to the 
				m_tcpEventPocessor.onReceiveEvent(*m_event);
			}
			
			m_event->clear();
		}

		// Remove from passed buffer to indicate it was processed.
		data.erase(data.begin());
	}

	FUNCTION_EXIT;
}


void TCPConnection::writeFailed( const SocketData& writeBuffer, ObservedSocket* socket )
{
	FUNCTION_ENTRY("writeFailed");
	FUNCTION_EXIT;
}


void TCPConnection::connectionLost( ObservedSocket* socket )
{
    FUNCTION_ENTRY("connectionLost");

	if( !isConnectionLost )
	{
		isConnectionLost = true;

		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, 
			"[Link Lost] %s link connection lost detected.", (m_primary ? "primary" : "secondary") );

		// Notify observer
		m_observer.onConnectionFail(m_primary);

		// clear the write buffer - dont want old data being sent on the new connection
		socket->clearWriteBuffer();
	}

    FUNCTION_EXIT;
}

void TCPConnection::connectionLost()
{
	if( !isConnectionLost )
	{
		isConnectionLost = true;

		LOG_GENERIC(SourceInfo,TA_Base_Core::DebugUtil::DebugInfo,
			"[Link Lost] connection lost detected. is primary link = %d", m_primary);

		m_clientSocket->clearWriteBuffer();
		m_clientSocket->close();

		m_observer.onConnectionFail( m_primary );
	}
}

void TCPConnection::connectionEstablished( ObservedSocket* socket )
{
    FUNCTION_ENTRY("connectionEstablished");

	isConnectionLost = false;
	
	LOG_GENERIC(SourceInfo,TA_Base_Core::DebugUtil::DebugInfo,
		"[Link Establish] connection establish. is primary link = %d", m_primary);
	
	// Notify observer
	m_observer.onConnectionResumed(m_primary);

    FUNCTION_EXIT;
}


bool TCPConnection::isConnected() const
{
    return m_clientSocket->isConnected();
}


inline const std::string & TCPConnection::getIdentifier() const
{
    return m_identifier;
}

