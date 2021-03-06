/**
  * The source code in this file is the property of Ripple Systems and is not for redistribution in
  * any form.
  *
  * Source:		$File: //depot/3001_TIP_NEW/3001/transactive/app/scada/PMSAgent/src/PMSAgent.h $
  * @author:	HoaVu
  * @version:	$Revision: #4 $
  *
  * Last modification:	$DateTime: 2014/07/11 18:24:37 $
  * Last modified by:	$Author: haijun.li $
  *
  * Description:
  *
  *	PMSAgent implementes the GenericAgent interface.  PMSAgent monitors and controls the 
  * the entities associated with its process, such as PMS RTU and the DataPoint entities.
  *
  */

#ifndef PMSAGENT_H
#define PMSAGENT_H

#include <map>

#include "app/scada/PMSAgent/src/RTUManager.h"
#include "core/threads/src/LFThreadPoolManager.h"
#include "bus/generic_agent/src/IGenericAgentUser.h"
#include "bus/scada/datapoint_library/src/DataPoint.h"
#include "bus/scada/DataPointAgentCorbaDef_Impl/src/DataPointAgentCorbaDef_Impl.h"
#include "bus/scada/DataPointAgentCorbaDef_Impl/src/DataPointAccessCorbaDef_Impl.h"
#include "bus/scada/DataNodeAgentCorbaDef_Impl/src/IDataNodeAgent.h"
#include "bus/scada/common_library/src/ScadaPersistence.h"

#include "core/message/src/NameValuePair.h"
#include "core/synchronisation/src/ReEntrantThreadLockable.h"
#include "core/timers/src/SingletonTimerUtil.h"
#include "core/timers/src/ITimeoutCallback.h"
#include "core/threads/src/Thread.h"

namespace TA_Base_Bus
{
	class DataPointFactory;
	class LocalUpdateEventProcessor;
	class GenericAgent;
	class AgentStateUpdateQueueSingletonManager;
	class ScadaProxyFactory;
	class SummaryProcessor;
	class DataNode;
	class DataNodeAgentCorbaDef_Impl;
	class DataNodeAccessCorbaDef_Impl;
};

namespace TA_Base_Core
{
	class IThreadPoolExecuteItem;
	class AuditMessageSender;
    class MessageType;
	class ThreadPoolSingletonManager;
};

namespace TA_IRS_App
{
	class RTU;
    class ForcedDataPointSynchroniser;
	
	class PMSAgent;
	typedef void (PMSAgent::*FuncInit)(TA_Base_Core::IEntityDataPtr agentEntityData);

	class AgentInitThread : public TA_Base_Core::Thread
	{
	public:
		AgentInitThread(PMSAgent& agent, FuncInit func, TA_Base_Core::IEntityDataPtr agentEntityData);
		~AgentInitThread();
		bool waitForCompelete();
		void run();
		void terminate();
	private:
		TA_Base_Core::Semaphore			m_semphore;
		FuncInit						m_func;
		TA_Base_Core::IEntityDataPtr	m_agentEntityData;
		PMSAgent&						m_agent;
		bool							m_executeSuccess;
	};

	class CreateEntityWorkItem : public TA_Base_Core::IThreadPoolExecuteItem
	{
	public:
		CreateEntityWorkItem(PMSAgent& agent, 
			TA_Base_Core::IEntityDataPtr entityData, 
			TA_Base_Core::WorkItemExeSync* workSync);
		void executeWorkItem();
	private:
		PMSAgent&						m_parent;
		TA_Base_Core::IEntityDataPtr	m_entityData;
		TA_Base_Core::WorkItemExeSync*  m_sync;
	};

	class InitDataPointWorkItem : public TA_Base_Core::IThreadPoolExecuteItem
	{
	public:
		InitDataPointWorkItem(TA_Base_Bus::DataPoint* dp, TA_Base_Core::WorkItemExeSync* workSync);
		void executeWorkItem();
	private:
		TA_Base_Bus::DataPoint*			m_dp;
		TA_Base_Core::WorkItemExeSync*  m_sync;
	};

	class PMSAgent : public virtual TA_Base_Bus::IGenericAgentUser,
					 public virtual TA_Base_Bus::IDataPointAgent,
					 public virtual TA_Base_Bus::IDataNodeAgent
	{
	typedef std::vector< TA_Base_Bus::DataNode* > DataNodeList;

	public:

		PMSAgent ( int argc, char* argv[] );
		virtual ~PMSAgent();

		//
		// operations required by IGenericAgentUser
		//

		/** 
		  * notifyGroupOffline
		  *
		  * This request is passed on by GenericAgent when it receives a call to 
		  * notifyGroupOffline from the Process Monitor.
		  *
		  * @param The group name
		  */
		virtual void notifyGroupOffline( const std::string& group );

		/** 
		  * notifyGroupOnline
		  *
		  * This request is passed on by GenericAgent when it receives a call to 
		  * notifyGroupOnline from the Process Monitor.
		  *
		  * @param The group name
		  */
		virtual void notifyGroupOnline( const std::string& group );

		/**
		  * agentTerminate
		  *
		  * This pure virtual method is called from the onTerminate
		  * method in GenericAgent. This allows the agent to do any
		  * of its own cleaning up before exiting.
		  *
		  * If the agent's entities implement CORBA interfaces,
		  * this method should take care of deactivating them. It is not
		  * possible for GenericAgent to do this because the IEntity 
		  * interface is not a ServantBase.
		  *
		  * If the class implementing this interface holds the GenericAgent
		  * as a member variable, DO NOT delete it inside this method.
		  * GenericAgent waits for this call to return before shutting down
		  * the ORB. Deleting the GenericAgent from within this method will
		  * cause obvious problems.
		  */
		virtual void agentTerminate();

        /** 
          * createAllEntities
          *
          * [optional]
          *
          * This allows for bulk entity creation.
          * It is called first (before any calls to createEntity) to allow agents to
          * optimise entity creation. If true is returned, the entities are already created
          * if false is returned, then createEntity is called one by one for each entity.
          * Also entityCreationComplete will be called at the end of the creation
          *
          * Note that even if using this method, createEntity should still be implemented
          * as it is used for entity updates
          *
          * @param agentEntityData the agent's entity data
          * @param entityDataList a list of shared pointers to all entities
          * @param createdEntities the entities created to return to generic agent
          *
          * @return true if entity creation was done, false if createEntity should be used
          *
          */
        virtual bool createAllEntities( TA_Base_Core::IEntityDataPtr agentEntityData,
                                        const TA_Base_Core::SharedIEntityDataList& entityDataList,
                                        TA_Base_Bus::IEntityList& createdEntities );

        /** 
          * entityCreationComplete
          *
          * [optional]
          *
          * this is called back after 
          * createEntity has been called for all entities.
          * The client can do any clean up of temporary data.
          */
        virtual void entityCreationComplete();

		/**
		  * createEntity
		  *
		  * This method takes Entity Configuration data stored in the database and
		  * generates an object that implements the IEntity interface. The returned
		  * objects are stored and managed within Generic Agent. The Agent can get a 
		  * pointer to the objects via the getEntityMap method in GenericAgent.
		  *
		  * @param Entity data retrieved from the database.
		  *
		  * @return The constructed entity
		  */
		virtual TA_Base_Bus::IEntity* createEntity(TA_Base_Core::IEntityDataPtr EntityData);

		/**
		  * agentSetMonitor
		  *
		  * This pure virtual method is called by GenericAgent whenever it receives
		  * a request from the Process Monitor to change its operating state to monitor.
		  * The derived agent should respond by subscribing/unsubscribing to/from the 
		  * appropriate message channels and performing any other internal house keeping.
		  */
		virtual void agentSetMonitor();

		/**
		  * agentSetControl
		  *
		  * This pure virtual method is called by GenericAgent whenever it receives
		  * a request from the Process Monitor to change its operating state to control.
		  * The derived agent should respond by subscribing/unsubscribing to/from the 
		  * appropriate message channels and performing any other internal house keeping.
		  */
		virtual void agentSetControl();

		/**
          * agentSetStandby
          *
          * This pure virtual method is called by GenericAgent whenever it receives
          * a request from the Process Monitor to change its operating state to standby.
          * The derived agent should respond by subscribing/unsubscribing to/from the 
          * appropriate message channels and performing any other internal house keeping.
          */
		virtual void agentSetStandby();

		/**
		  * registerForStateUpdates
		  *
		  * This pure virtual method forces agents to subscribe for either
		  * state updates or state update requests, depending on whether or not they
		  * are operating in monitor or control mode.
		  */
		virtual void registerForStateUpdates();

		/**
		  * receiveSpecialisedMessage
		  *
		  * This method is called whenever the Agent receives a state update or
		  * state update request (depending on their mode of operation)
		  */
		virtual void receiveSpecialisedMessage(const TA_Base_Core::StateUpdateMessageCorbaDef& message);

		/**
		  * processOnlineUpdate
		  *
		  * Generic Agent will handle the receiving of online updates. However, in some
		  * cases, it will be necessary to pass the updates on to the registered agent.
		  * For example, if a child entity needs to be updated.
		  *
		  * @param The update event
		  */
		virtual void processOnlineUpdate(const TA_Base_Core::ConfigUpdateDetails& updateEvent);


		//
		// operations required by IDataPointAgent interface
		//


		virtual TA_Base_Bus::DataPoint * getDataPoint ( unsigned long entityKey );


        virtual void getAllDataPoints (std::map < unsigned long, TA_Base_Bus::DataPoint *>& dataPointList );

		//
		// operations required by IDataNodeAgent interface
		//
		virtual TA_Base_Bus::DataNode * getDataNode( unsigned long entityKey );

		/**
		* getAllDataNodes 
		* 
		* 
		* @return virtual void 
		* @param : std::map < unsigned long
		* @param : TA_Base_Bus::DataNode *>& dataNodeList
		* 
		* @exception <exceptions> Optional
		*/
        virtual void getAllDataNodes (std::map < unsigned long, TA_Base_Bus::DataNode *>& dataNodeList );

		virtual TA_Base_Bus::DataPointFactory* getDataPointFactory();
		//
		// opearations specific to PMSAgent
		//

		/**
		  * startPMSAgent
		  *
		  * Start this PMSAgent process
		  *
		  */
		void startPMSAgent();

		virtual void beforeGetDescendantsOfAgent(TA_Base_Core::IEntityDataPtr agentEntity);

		void initilizeCache(TA_Base_Core::IEntityDataPtr agentEntity);
		
		void initializeDPAfterProxyReady();
	// operations
	private:
		//TD18706,jianghp, handle the operation mode
		virtual void checkOperationMode()
		{
		};
		/**
		  * loadAgentParamValues
		  *
		  * Load the PMSAgent entity's parameter from the database
		  *
		  */
		void loadAgentParamValues();

		/**
		  * startProcessors
		  *
		  * Start up all processors associated with the PMSAgent entity
		  *
		  */
		void startProcessors();

		/**
		  * stopProcessors
		  *
		  * Stop all processors associated with the PMSAgent entity
		  *
		  */
		void stopProcessors();

		/**
		 * submitAuditMessage
		 *
		 * Generates an audit message of the specified message type
		 *
		 * @param	description		The description of the audit message
		 * @param	messageType		The audit message type
		 *
		 */
		void submitAuditMessage ( const TA_Base_Core::DescriptionParameters & description,
								  const TA_Base_Core::MessageType & messageType );

		/**
		  * registerForControlMessages
		  *
		  * Registers for the messages expected to receive while in 
		  * control mode.
		  */
		void registerForControlMessages();

		/**
		  * registerForMonitorMessages
		  *
		  * Registers for the messages expected to receive while in 
		  * monitor mode.
		  */
		void registerForMonitorMessages();

		void updatePMSAgentConfiguration ( const TA_Base_Core::ConfigUpdateDetails & updateEvent);

		void updateDataPointConfiguration ( const TA_Base_Core::ConfigUpdateDetails & updateEvent);

		TA_Base_Bus::IEntity* createDataPointEntity ( TA_Base_Core::IEntityDataPtr EntityData );

		/**
		 * createRTUWorkers
		 *
		 * create rtu internal worker utilities
		 *
		 */
        void createRTUWorkers();

		void setScadaInterfaceOperationMode(TA_Base_Core::EOperationMode mode);

            // attributes
	private:

		unsigned long m_pmsAgentPrimaryKey;
		int m_proxyDpMonitoringPeriodSecs;
        TA_Base_Core::EOperationMode	m_operationMode;
		bool m_bulkInterfaceStarted;
        bool m_isRTUSwitchingDisabled;
        int m_analogueDpUpdateInterval;
		std::string m_stationName;
		std::string m_agentName;
		std::string m_agentAssetName;

		std::map< unsigned long, TA_Base_Bus::DataPoint * > m_datapoints;

		TA_Base_Core::ReEntrantThreadLockable		m_dataPointListtLock;
		TA_Base_Bus::GenericAgent *					m_genericAgent;
		TA_Base_Core::AuditMessageSender *			m_auditMessageSender;
        TA_Base_Bus::DataPointAgentCorbaDef_Impl *	m_dpBulkPolledInterface;
        TA_Base_Bus::DataPointAccessCorbaDef_Impl * m_dpAccessInterface;
        TA_Base_Bus::DataPointFactory *				m_dataPointFactory;
		TA_Base_Bus::ScadaProxyFactory *			m_scadaProxyFactory;
		
		TA_Base_Bus::DataNodeAgentCorbaDef_Impl *	m_dnBulkPolledInterface;
		TA_Base_Bus::DataNodeAccessCorbaDef_Impl *	m_dnAccessInterface;
		TA_Base_Bus::SummaryProcessor*				m_summaryProcessor;
		TA_Base_Bus::ScadaPersistencePtr			m_persistence;
		TA_Base_Core::ReEntrantThreadLockable		m_dataNodeListLock;
		DataNodeList								m_dataNodes;

		RTUManager									m_rtuManager;
		AgentInitThread*							m_agentInitThread;
	};
}

#endif

