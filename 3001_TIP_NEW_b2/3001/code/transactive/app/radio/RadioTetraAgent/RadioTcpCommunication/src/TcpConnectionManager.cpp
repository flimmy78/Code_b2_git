
#include "app/radio/RadioTetraAgent/RadioTcpCommunication/src/TcpConnectionManager.h"
#include "app/radio/RadioTetraAgent/RadioTcpCommunication/src/TcpConnectionException.h"

#include "core/threads/src/Thread.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/message/src/NameValuePair.h"

using namespace TA_IRS_App;
using TA_Base_Core::DebugUtil;


TcpConnectionManager::TcpConnectionManager(ITcpEventProcessor& TCPServer)
: m_primaryConnection(0),
m_secondaryConnection(0),
m_active(0),
m_currentConnection(0),
m_waitForConnection(true),
m_tcpServer(TCPServer),
m_objectName(""),
m_entityKey(0),
m_entityLocation(0),
m_entitySubsystem(0),
m_entityTypeKey(0),
m_controlConnectionStatus(NoAppliable),
m_isConnected(false)
{
	FUNCTION_ENTRY("Constructor");
	m_observers.clear();
	FUNCTION_EXIT;
}


void TcpConnectionManager::setEntity(TA_Base_Core::IEntityData& entityData)
{
	m_objectName      = entityData.getName();
	m_entityKey       = entityData.getKey();
	m_entityLocation  = entityData.getLocation();
	m_entitySubsystem = entityData.getSubsystem();
	m_entityTypeKey   = entityData.getTypeKey();
}

void TcpConnectionManager::setTcpHost(bool isPrimary,std::string hostAddress)
{
	// basic sanity check : the "host:port" should be at least two characters
	// long. This accounts for entityparametervalues that don't have SIL2
	// integrity
	LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Entering TcpConnectionManager::setRadioHost, isPrimary = %d, hostAddress = %s",isPrimary,hostAddress.c_str());

	if (hostAddress.size()<2)
	{
		LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Host address \"%s\" too small, ignoring", hostAddress.c_str());
		if (isPrimary)
		{
			delete m_primaryConnection;
			m_primaryConnection = 0;
		}
		else
		{
			delete m_secondaryConnection;
			m_secondaryConnection = 0;
		}
		return;
	}
	//Separate host and port
	std::string  host;
	std::string  port;
	bool separatorFound=false;   // In this case a :
	for (unsigned int index = 0;index<hostAddress.size();index++)
	{
		if (hostAddress[index]==':')
		{
			separatorFound = true;
		}
		else
		{
			if (separatorFound)
			{
				port += hostAddress[index];
			}
			else
			{
				host += hostAddress[index];
			}
		}
	}

	if (isPrimary)
	{
		//Haipeng added the check to verify whether pointer is NULL
		if (m_primaryConnection != NULL)
		{
			delete m_primaryConnection;
			m_primaryConnection = 0;
		}

		m_primaryConnection = new TCPConnection(m_tcpServer, *this, host, port, true);
		m_primaryConnection->setIgnoreIncomingData(m_active);
	}
	else
	{
		//Haipeng added the check to verify whether pointer is NULL
		if (m_secondaryConnection != NULL)
		{
			delete m_secondaryConnection;
			m_secondaryConnection = 0;
		}

		m_secondaryConnection = new TCPConnection(m_tcpServer, *this, host, port, false);
		m_secondaryConnection->setIgnoreIncomingData(m_active);
	}
}
void TcpConnectionManager::start()
{
	if (m_primaryConnection != NULL)
	{
		m_primaryConnection->start();
	}

	if (m_secondaryConnection != NULL)
	{
		m_secondaryConnection->start();
	}
}

void TcpConnectionManager::setControlConnection(ETcpControlConnectionStatus controlConnectionStatus)
{
	switch(controlConnectionStatus)
	{
	case NoAppliable:
		m_controlConnectionStatus = NoAppliable;
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, 
			"[update] set current connection NoAppliable.");
		break;
	case ConnectToPrimary:
		m_controlConnectionStatus = ConnectToPrimary;
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, 
			"[update] set current connection ConnectToPrimary.");
		break;
	case ConnectToSecondary:
		m_controlConnectionStatus = ConnectToSecondary;
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, 
			"[update] set current connection ConnectToSecondary.");
		break;
	default:
		;
	}

	LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "[Connection Control] Current value: %d", m_controlConnectionStatus );
}

void TcpConnectionManager::onConnectionFail(bool isPrimary)
{
	FUNCTION_ENTRY("onConnectionFail");

	TA_Base_Core::ThreadGuard connectionSwitchGuard(m_serverGuard); //onConnectionFail

	LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, 
		"[Link Lost] connection %s fail. current connection number is %d", 
		(isPrimary ? "Primary" : "secondary"), numConnected() );

	bool isAbleToSwitch = false;

	if ( isPrimary)  
	{
		//there is no m_secondaryConnection on station 
		if (m_secondaryConnection != NULL) isAbleToSwitch = m_secondaryConnection->isConnected();
	} 
	else
	{
		isAbleToSwitch = m_primaryConnection->isConnected();
	}

	// if no more connections, let general dependents know
	if ( !isAbleToSwitch )
	{
		
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "[Link Lost],is not able to switch");
		m_isConnected = false;

		m_currentConnection = 0;

		if (m_active)
		{
			m_controlConnectionStatus = NoAppliable;

			//RadioConnectionSwitch message;
			//message.controlConnectionStatus = m_controlConnectionStatus;
			//message.TCPServerIndex = m_tcpServer.getServerIndex();
			//RadioStateUpdateBroadcaster::getInstance()->sendRadioConnectionSwitch(message);	
		}

		releaseSendMethod();

		TA_Base_Core::ThreadGuard guard(m_observerGuard);
		std::vector< ITcpConnectionStatusObserver* >::iterator it = m_observers.begin();
		for(; it != m_observers.end() ; ++it)
		{
			(*it)->onConnectionLost();
		}		


		// Raise a "unique" alarm
		//	TA_Base_Core::DescriptionParameters descriptionParameters;

		//	TA_Base_Core::AlarmHelperManager::getInstance().getAlarmHelper().submitAlarmWithAsset(TA_Base_Core::RadioAlarms::RadioCommunicationsFailureAlarm,
		//		m_entityKey,
		//		m_entityTypeKey,
		//		descriptionParameters,
		//		m_objectName, 
		//		m_entityLocation, 
		//	m_entitySubsystem,
		//		m_assetName,
		//		TA_Base_Core::AlarmConstants::defaultTime );
	}
	else
	{
		if ( (m_currentConnection == m_primaryConnection && isPrimary) || 
			(m_currentConnection == m_secondaryConnection && m_secondaryConnection!=NULL && !isPrimary) )
		{
			switchConnection(!isPrimary);
			notifyConnectionSwitch();
		}
		else
		{
			LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "The standby connection lost.");
		}
	}

	LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "[Connection Control] Current value: %d", m_controlConnectionStatus );	
	FUNCTION_EXIT;
}

void TcpConnectionManager::onConnectionResumed(bool isPrimary)
{
	FUNCTION_ENTRY("onConnectionResumed");
	TA_Base_Core::ThreadGuard connectionSwitchGuard(m_serverGuard); //onConnectionResumed

	LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, 
		"[Link Resumed] connection %s Resumed.", (isPrimary ? "Primary" : "secondary") );

	if ( numConnected() > 0 && !m_isConnected )
	{
		m_isConnected = true;
		switchConnection(isPrimary);

		TA_Base_Core::ThreadGuard guard(m_observerGuard);
		std::vector< ITcpConnectionStatusObserver* >::iterator it = m_observers.begin();
		for(; it != m_observers.end() ; ++it)
		{
			(*it)->onConnectionEstablish(isPrimary);
		}

		// Close any alarm
		//		TA_Base_Core::AlarmHelperManager::getInstance().getAlarmHelper().closeAlarmAtLocation(TA_Base_Core::RadioAlarms::RadioCommunicationsFailureAlarm,m_entityKey,m_entityLocation);
	}

	LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "[Connection Control] Current value: %d", m_controlConnectionStatus );
	FUNCTION_EXIT;
}

void TcpConnectionManager::notifyConnectionSwitch()
{
	TA_Base_Core::ThreadGuard guard(m_observerGuard);
	std::vector< ITcpConnectionStatusObserver* >::iterator it = m_observers.begin();
	bool isPrimary = (m_currentConnection == m_primaryConnection) ? true : false;
	for(; it != m_observers.end() ; ++it)
	{
		(*it)->onSwitchConnection(isPrimary);
	}
}

void TcpConnectionManager::setToControlMode(void)
{
	FUNCTION_ENTRY("setToControlMode");
	TA_Base_Core::ThreadGuard lock(m_serverGuard); //setToControlMode
	LOG_GENERIC(SourceInfo,TA_Base_Core::DebugUtil::DebugInfo,"Setting RadioConnectionManager to control mode.");
	m_active = true;

	if (m_controlConnectionStatus == ConnectToPrimary)
	{
		m_currentConnection = m_primaryConnection;
	}
	else if (m_controlConnectionStatus == ConnectToSecondary)
	{
		m_currentConnection = m_secondaryConnection;
	}
	else if (m_controlConnectionStatus == NoAppliable && numConnected() > 0)
	{
		if( m_primaryConnection->isConnected() ) 
		{
			switchConnection(true);
		}
		else if (m_secondaryConnection!=NULL && m_secondaryConnection->isConnected() )
		{
			switchConnection(false);
		}
		else
		{
			m_currentConnection = NULL;
		}
	}
    
	// Start the sockets processing events
	// The ONLY connection we want to NOT ignore incoming data is the current
	// one, and only if it is non-null
	if (m_primaryConnection != NULL)
	{
		// ie. if primary != current, then ignore data
		LOG_GENERIC(SourceInfo,TA_Base_Core::DebugUtil::DebugInfo,"Start the sockets of primaryConnection processing events: setIgnoreIncomingData %d", m_primaryConnection != m_currentConnection);
		m_primaryConnection->setIgnoreIncomingData( m_primaryConnection != m_currentConnection );
	}

	if (m_secondaryConnection != NULL)
	{
		// ie. if secondary != current, then ignore data
		LOG_GENERIC(SourceInfo,TA_Base_Core::DebugUtil::DebugInfo,"Start the sockets of secondaryConnection processing events: setIgnoreIncomingData %d", m_secondaryConnection != m_currentConnection);
		m_secondaryConnection->setIgnoreIncomingData( m_secondaryConnection != m_currentConnection );
	}

	LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "[Connection Control] Current value: %d", m_controlConnectionStatus );

	FUNCTION_EXIT;
}

void TcpConnectionManager::setToMonitorMode(void)
{
	FUNCTION_ENTRY("setToMonitorMode");
	LOG_GENERIC(SourceInfo,TA_Base_Core::DebugUtil::DebugInfo,"Setting RadioConnectionManager to monitor mode.");
	TA_Base_Core::ThreadGuard lock(m_serverGuard); //setToMonitorMode
	m_active = false;
	//need set it to false, the disconnection callback cannot be triggered after calling closeConnection.	
    m_isConnected = false;   //DTL-2098
	m_controlConnectionStatus = NoAppliable;
	m_currentConnection=NULL;

	// Stop the sockets from processing events
	if (m_primaryConnection != NULL)
	{
		m_primaryConnection->setIgnoreIncomingData(true);
		m_primaryConnection->closeConnection();
	}

	if (m_secondaryConnection != NULL)
	{
		m_secondaryConnection->setIgnoreIncomingData(true);
		m_secondaryConnection->closeConnection();
	}

	FUNCTION_EXIT;
}

void TcpConnectionManager::registForConnectionStatus( ITcpConnectionStatusObserver* observer)
{
	FUNCTION_ENTRY("registForConnectionStatus");

	TA_Base_Core::ThreadGuard guard(m_observerGuard);

	m_observers.push_back(observer);

	FUNCTION_EXIT;
}

void TcpConnectionManager::unregistForConnectionStatus( ITcpConnectionStatusObserver* observer)
{
	FUNCTION_ENTRY("unregistForConnectionStatus");

	TA_Base_Core::ThreadGuard guard(m_observerGuard);
	std::vector< ITcpConnectionStatusObserver* >::iterator it = m_observers.begin();
	for(; it != m_observers.end() ; ++it)
	{
		if (*it == observer)
		{
			m_observers.erase(it);
			break;
		}
	}

	FUNCTION_EXIT;
}

TcpConnectionManager::~TcpConnectionManager()
{
	FUNCTION_ENTRY("Destructor");

	
	TA_Base_Core::ThreadGuard lock(m_serverGuard); //~TcpConnectionManager
	m_currentConnection = 0;
	
	delete m_primaryConnection;
	delete m_secondaryConnection;
	m_primaryConnection=NULL;
	m_secondaryConnection=NULL;
	FUNCTION_EXIT;
}

/**
* Sends the content of the radio method to the Radio server via TCP/IP
* @param    Method
*/
void TcpConnectionManager::SendMethod(const ITcpMethod& method)
{
	FUNCTION_ENTRY("SendMethod");

	if (getCurrentConnection() == 0)
	{
		TA_THROW(TcpConnectionException());
	}

	// ThreadGuard scope restriction
	{
		TA_Base_Core::ThreadGuard lock(m_serverGuard); //SendMethod
		// and just in case its changed back to zero in the meantime...
		if (m_currentConnection != 0)
		{
			// Send it to the current server
			m_currentConnection->Send(method);
		}		 
	}

	FUNCTION_EXIT;
}


/**
* Change connection from primary to secondary and vice-versa
*/
void TcpConnectionManager::switchConnection(bool toPrimary)
{
	FUNCTION_ENTRY("switchConnection");

	LOG_GENERIC(SourceInfo,TA_Base_Core::DebugUtil::DebugInfo,"[Link Switch] about to switch connection to %s connection",toPrimary? "Primary":"Secondary");

	TA_Base_Core::ThreadGuard lock(m_serverGuard); //switchConnection

	m_currentConnection = (toPrimary) ? m_primaryConnection : m_secondaryConnection;

	m_controlConnectionStatus = (toPrimary) ? ConnectToPrimary : ConnectToSecondary;

	if ((m_primaryConnection != NULL) && (m_active))
	{
		// set to ignore incoming data if not the current connection
		m_primaryConnection->setIgnoreIncomingData(m_primaryConnection != m_currentConnection);
	}

	if ((m_secondaryConnection != NULL) && (m_active))
	{
		// set to ignore incoming data if not the current connection
		m_secondaryConnection->setIgnoreIncomingData(m_secondaryConnection != m_currentConnection);
	}

	if(m_active)
	{
		//	RadioConnectionSwitch message;
		//	message.controlConnectionStatus = m_controlConnectionStatus;
		//		message.TCPServerIndex = m_tcpServer.getServerIndex();
		//		RadioStateUpdateBroadcaster::getInstance()->sendRadioConnectionSwitch(message);

		m_currentConnection->setCheckConnection();
	}

	LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "[Connection Control] Current value: %d", m_controlConnectionStatus );

	FUNCTION_EXIT;
}

int TcpConnectionManager::numConnected()
{
	FUNCTION_ENTRY("numConnected");
	int numConnected = 0;
	if ((m_primaryConnection != 0) && (m_primaryConnection->isConnected()))
	{
		numConnected++;
	}

	if ((m_secondaryConnection != 0) && (m_secondaryConnection->isConnected()))
	{
		numConnected++;
	}

	LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Number of active connections=%d", numConnected);

	FUNCTION_EXIT;
	return numConnected;
}

TCPConnection * TcpConnectionManager::getCurrentConnection()
{
	TA_Base_Core::ThreadGuard lock(m_serverGuard); //getCurrentConnection
	return m_currentConnection;
}


void TcpConnectionManager::releaseSendMethod()
{
	FUNCTION_ENTRY("releaseSendMethod");
	m_waitForConnection = false;
	FUNCTION_EXIT;
}

void TcpConnectionManager::getControlConnectionStatus(ETcpControlConnectionStatus& controlConnectionStatus)
{
	controlConnectionStatus = m_controlConnectionStatus;
	LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "[Connection Control] Current value: %d", m_controlConnectionStatus );
}

void TcpConnectionManager::onCloseSocket()
{
	if (m_primaryConnection != NULL) m_primaryConnection->connectionLost();
	LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "Primary socket closed" );

	if (m_secondaryConnection != NULL) m_secondaryConnection->connectionLost();
	LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "Secondary sockets closed" );
}
