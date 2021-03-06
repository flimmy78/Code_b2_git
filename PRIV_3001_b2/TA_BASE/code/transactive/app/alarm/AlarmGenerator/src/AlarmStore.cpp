/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4677_ALL_TIP/TA_BASE/transactive/bus/alarm/alarm_list_control/src/AlarmStore.cpp $
  * @author:  Karen Graham
  * @version: $Revision: #6 $
  *
  * Last modification: $DateTime: 2011/01/20 15:53:31 $
  * Last modified by:  $Author: huirong.luo $
  * 
  * This class provides the interface to the alarm store. It connects to it and sends information
  * to it.
  */

#pragma warning(disable:4786)

#include "bus/alarm/alarm_list_control/src/AlarmStore.h"
 
#include "bus/security/authentication_library/src/AuthenticationLibrary.h"
#include "bus/security/authentication_library/src/SessionInfo.h"

#include "core/corba/src/CorbaUtil.h"
#include "core/data_access_interface/entity_access/src/IConsole.h"
#include "core/data_access_interface/entity_access/src/AlarmStoreEntityData.h"
#include "core/data_access_interface/entity_access/src/ConsoleAccessFactory.h"
#include "core/data_access_interface/entity_access/src/EntityAccessFactory.h"
#include "core/exceptions/src/AlarmListCtrlException.h"
#include "core/exceptions/src/DataException.h"
#include "core/exceptions/src/ObjectResolutionException.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/RunParams.h"

using TA_Base_Core::DebugUtil;

namespace TA_Base_Bus
{
    const std::string AlarmStore::PORT_NUMBER = "PortNumber";

    AlarmStore::AlarmStore(const Filter& preFilter,
                           const std::vector<unsigned long>& locations,
                           const Sort& sort,
                           const Filter& filter,
                           const std::string& sessionId,
						   bool isHighestSeverityNeeded)
    :
    m_bTerminate(false),
    m_bAlarmStoreValid(false),
//     m_alarmStoreCallback(NULL),
//     m_alarmStoreIndexId(-1),
    m_preFilter(preFilter),
    m_sort(sort),
    m_filter(filter),
    m_locations(locations),
    m_sessionId(sessionId),
	m_isHighestSeverityNeeded(isHighestSeverityNeeded),
	m_bFilterCreated(true)
    {
        FUNCTION_ENTRY("Constructor");

        // Create the alarm store callback to pass to our alarm store.
        //m_alarmStoreCallback = new AlarmStoreCallback();

        // Now start trying to resolve that object. Until we can find it there is not a lot we can do
        start();

        FUNCTION_EXIT;
    }


    AlarmStore::~AlarmStore()
    {
        FUNCTION_ENTRY("Destructor");

        terminateAndWait();

        TA_THREADGUARD( m_alarmStoreLock );
        if ( false == CORBA::is_nil(m_alarmStore) )
        {
             
            m_alarmStore = NULL;
        }

        try
        {
             
			// Release the cache memory and pointers
            TA_THREADGUARD( m_alarmCacheLock );
			for ( std::map<std::string, TA_Base_Core::AlarmDetailCorbaDef*>::iterator itr = m_alarmCache.begin();
                  itr != m_alarmCache.end(); ++itr )
			{
				delete itr->second;
				itr->second = NULL;
			}
			m_alarmCache.clear();
        }
        catch( ... )
        {
        }
        FUNCTION_EXIT;
    }


    void AlarmStore::run()
    {
        //FUNCTION_ENTRY("run");
		LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "AlarmStore::run come in" );


		LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "AlarmStore register Session Info" );
        // The first step in the resolution is to work out the IOR for the alarm store.
        // To do this, first determine if there's a run param set for the port number
        std::string portNumber = TA_Base_Core::RunParams::getInstance().get(PORT_NUMBER.c_str());

        std::ostringstream ior;
        ior << "corbaloc::localhost:";
        if ( false == portNumber.empty() )
        {
            ior << portNumber;
        }
        else
        {
            ior << TA_Base_Core::IAlarmStoreCorbaDef::DEFAULT_ALARM_STORE_PORT;
        }
        ior << "/" << TA_Base_Core::IAlarmStoreCorbaDef::DEFAULT_ALARM_STORE_NAME;

        std::string alarmStoreIOR = ior.str();

        int retry = 0;
        while ( false == m_bTerminate )
        {            
            try
            {
                TA_THREADGUARD( m_alarmStoreLock );   

                LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Resolving Alarm Store - Attempt %d", ++retry );

                CORBA::Object_var obj = TA_Base_Core::CorbaUtil::getInstance().stringToObject( alarmStoreIOR );
                if ( true == CORBA::is_nil(obj) )
                {
                    LOG_GENERIC( SourceInfo, DebugUtil::DebugWarn, "Failed to retrieve Corba object with IOR %s",
                        alarmStoreIOR );
					// wait a moment to avoid reconnecting to a invalid CORBA servant in hight frequency;
					if (false == m_bTerminate) sleep(2000); 
                    continue;
                }
                
                m_alarmStore = TA_Base_Core::IAlarmStoreCorbaDef::_narrow( obj );
                if ( true == CORBA::is_nil(m_alarmStore) )
                {
                    LOG_GENERIC( SourceInfo, DebugUtil::DebugWarn, "Failed to narrow obj into IAlarmStoreCorbaDef" );
					// wait a moment to avoid reconnecting to a invalid CORBA servant in hight frequency;
					if (false == m_bTerminate) sleep(2000);
                    continue;
                }                
            }
            catch( const TA_Base_Core::ObjectResolutionException& ore )
            {
                m_alarmStore = NULL;
                std::ostringstream desc;
                desc << "Caught ObjectResolutionException while resolving AlarmStore with IOR "
                    << alarmStoreIOR << "; Reason: " << ore.what();
                LOG_EXCEPTION_CATCH( SourceInfo, "ObjectResolutionException", desc.str().c_str() );
            }
            catch( const TA_Base_Core::IAlarmStoreCorbaDef::InvalidFilterException& ife )
            {
                //TODO: How to get this back out to the calling class
                m_alarmStore = NULL;
                std::ostringstream desc;
                desc << "Filter specified is invalid; Reason: " << TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ife);
                LOG_EXCEPTION_CATCH( SourceInfo, "InvalidFilterException", desc.str().c_str() );
            }
            catch ( const CORBA::SystemException& se )
            {
                //m_alarmStore = NULL;
				std::string errinfo=TA_Base_Core::CorbaUtil::getInstance().exceptionToString(se).c_str();
                std::ostringstream desc;
                desc << "Caught CORBA::SystemException resolving AlarmStore with IOR "
                    << alarmStoreIOR << "; Reason: " << errinfo;
                LOG_EXCEPTION_CATCH( SourceInfo, "CORBA::SystemException", desc.str().c_str() );			 
				if (errinfo!="TRANSIENT_CallTimedout")
				{		 
					m_resolveAlarmStore.signal();
				}
            }
            catch ( const std::exception& e )
            {
                m_alarmStore = NULL;
                std::ostringstream desc;
                desc << "Caught std::exception resolving AlarmStore with IOR "
                    << alarmStoreIOR << "; Reason: " << e.what();
                LOG_EXCEPTION_CATCH( SourceInfo, "std::exception", desc.str().c_str() );
            }
            catch( ... )
            {
                m_alarmStore = NULL;
                // Catch all exception to prevent thread from pre-maturely terminating
                LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "Caught unknown exception in AlarmStore::run()!" );
            }

            if ( false == CORBA::is_nil(m_alarmStore) )
            {
                retry = 0;
                m_bAlarmStoreValid = true;

                // Wait till we need to terminate or search for new Alarm Store Service
                m_resolveAlarmStore.wait();
                
                m_bAlarmStoreValid = false;
            }
			else
			{
				// wait a moment to avoid reconnecting to a invalid CORBA servant in hight frequency;
				if (false == m_bTerminate) sleep(4000); 
			}
        }
        LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "AlarmStore::run come out" );
        //FUNCTION_EXIT;
    }


    void AlarmStore::terminate()
    {
        FUNCTION_ENTRY("terminate");
        m_bTerminate = true;
        m_resolveAlarmStore.signal();
        FUNCTION_EXIT;
    }


 

	bool AlarmStore::deleteSharedAlarm(std::vector<std::string>& alarmIDs)
	{
		TA_THREADGUARD( m_alarmStoreLock );
		if ( false == isAlarmStoreValid() )
        {
            return false;
        }
		if (alarmIDs.size()==0)
		{
			return true;
		}
		TA_Base_Core::StringSequence alarms;
		alarms.length(alarmIDs.size());
		bool isSuccessfully=true;
		try
		{
			std::vector<std::string>::iterator  iter=alarmIDs.begin();
			int i=0;
			for (;iter!=alarmIDs.end();iter++)
			{
				std::string str=*iter;
				alarms[i] = CORBA::string_dup(str.c_str());;
				i++;
			}
			m_alarmStore->_setTimeout(10,0);
//			m_alarmStore->RemoveAlarms(alarms);
		}
		catch(const TA_Base_Core::ObjectResolutionException& )
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "ObjectResolutionException", "deleteSharedAlarm Could not resolve alarm store. Will indicate that this has to be found");
			isSuccessfully=false;
            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "deleteSharedAlarm Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (CORBA::SystemException& ex)
        {
            isSuccessfully=false;
			LOG_EXCEPTION_CATCH(SourceInfo, "deleteSharedAlarm CORBA::SystemException", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ex).c_str());		             
        }
        catch (CORBA::Exception& ce)
        {
            isSuccessfully=false;
			LOG_EXCEPTION_CATCH(SourceInfo, "deleteSharedAlarm CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ce).c_str());             
        }
        catch (const std::exception& e)
        {
            isSuccessfully=false;
			std::ostringstream desc;
            desc << "Caught std::exception in deleteSharedAlarm; Reason: " << e.what();
            LOG_EXCEPTION_CATCH(SourceInfo, "std::exception", desc.str().c_str());             
        }
        catch(...)
        {
            isSuccessfully=false;
			LOG_EXCEPTION_CATCH(SourceInfo, "Unknown", "Caught unknown exception in deleteSharedAlarm");             
        }	
		return isSuccessfully;
	}
   
   


    TA_Base_Core::AlarmDetailCorbaDef* AlarmStore::getAlarm(std::string alarmUUID)
    {
        // See if the alarm is in the cache. Hopefully it is
        {
            TA_Base_Core::ThreadGuard guard(m_alarmCacheLock);

            AlarmCache::iterator itAlarmDetail = m_alarmCache.find(alarmUUID);
            if (itAlarmDetail != m_alarmCache.end())
            {
                // Copy the object to be safe. It means no problems later if the item is cleared
                // from the cache while still in use.
				return new TA_Base_Core::AlarmDetailCorbaDef(*(itAlarmDetail->second));
            }
        }

        // Nope it's not so we'll have to try and retrieve it from the alarm store library ie. AlarmStoreServant
        if ( false == isAlarmStoreValid() )
        {
            TA_THROW( TA_Base_Core::AlarmListCtrlException("Could not retrieve the specified alarm") );
        }

        try
        {
            TA_THREADGUARD( m_alarmStoreLock );
            TA_Base_Core::AlarmDetailCorbaDef* alarmDetail = m_alarmStore->getAlarm(alarmUUID.c_str());
            
            TA_Base_Core::ThreadGuard guard(m_alarmCacheLock);
            m_alarmCache[ alarmUUID ] = alarmDetail; //cache the retreived Alarm Detail
           
            // Copy the object to be safe. It means no problems later if the item is cleared
            // from the cache while stillin use.
			return new TA_Base_Core::AlarmDetailCorbaDef(*alarmDetail);
        }
        catch(const TA_Base_Core::IAlarmStoreCorbaDef::AlarmNotFoundException& )
        {
            std::ostringstream errorMsg;
            errorMsg << "Alarm " << alarmUUID << " not found in alarm store";
            LOG_EXCEPTION_CATCH( SourceInfo, "AlarmNotFoundException", errorMsg.str().c_str() );
        }
        catch(const TA_Base_Core::ObjectResolutionException& )
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "ObjectResolutionException", "Could not resolve alarm store. Will indicate that this has to be found");

            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (CORBA::SystemException& ex)
        {
            std::string errinfo=TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ex).c_str();
			LOG_EXCEPTION_CATCH(SourceInfo, "CORBA::SystemException", errinfo.c_str());
			if (errinfo!="TRANSIENT_CallTimedout")
			{		 
				m_resolveAlarmStore.signal();
			}
        }
        catch (CORBA::Exception& ce)
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ce).c_str());

            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (const std::exception& e)
        {
            std::ostringstream desc;
            desc << "Caught std::exception in generateAlarmCache; Reason: " << e.what();
            LOG_EXCEPTION_CATCH(SourceInfo, "std::exception", desc.str().c_str());

            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch(...)
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "Unknown", "Caught unknown exception in generateAlarmCache");

            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }

        TA_THROW( TA_Base_Core::AlarmListCtrlException("Could not retrieve the specified alarm") );
    }


    void AlarmStore::setFilter(const Filter& filter,const int cs_pos,bool isDefault)
    {
        FUNCTION_ENTRY("setFilter");

        m_filter = filter;
		m_bFilterCreated = false;

		if (!isAlarmStoreValid())
		{
			LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo,
				"[+++LY+++] AlarmStore::setFilter detected alarmStore is invalid!");
			m_alarmStoreReady.timedWait(3000);
		}
		if (!isAlarmStoreValid())
		{
			TA_THROW(TA_Base_Core::AlarmListCtrlException("Create filter failed!"));
		}
        setFilterAndSort(cs_pos,isDefault);
		if(!m_bFilterCreated)
		{
			TA_THROW(TA_Base_Core::AlarmListCtrlException("Create filter failed!"));
		}
        FUNCTION_EXIT;
    }

    /*
    void AlarmStore::setSort(const Sort& sort)
    {
        FUNCTION_ENTRY("setSort");

        m_sort = sort;

        setFilterAndSort();

        FUNCTION_EXIT;
    }
*/

    


    void AlarmStore::updatePreFilterLocationsAndSession( const Filter& preFilter,
                                                         const std::vector<unsigned long>& locations,
                                                         const std::string& sessionID )
    {
        FUNCTION_ENTRY("updatePreFilterLocationsAndSession");
        LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "updatePreFilterLocationsAndSession come in" );
        // The prefilter should be the new session id
		//Move function to thread, so it will not hold the GUI again. luohuirong 08-04-2010
		TA_THREADGUARD( m_alarmStoreLock );
        m_preFilter = preFilter;
        m_locations = locations;
		m_bAlarmStoreValid = false;
		m_resolveAlarmStore.signal();
		LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "updatePreFilterLocationsAndSession come out" );
		return;

        // Now we want to reset the prefilter and locations in the alarm store
        try
        {
            TA_THREADGUARD( m_alarmStoreLock );
			
            //*
            // Set the locations we are interested in
            if ( true == m_locations.empty() )
            {
                m_alarmStore->setStoreMonitorAllLocations();
            }
            else if ( m_locations.size() == 1 )
            {
                m_alarmStore->setStoreMonitorLocation( m_locations[0] );
            }
            else
            {
                // Send through sequence of locations
                TA_Base_Core::IAlarmStoreCorbaDef::LocationList locations;
                locations.length( m_locations.size() );
                for(unsigned int i = 0; i < m_locations.size(); ++i)
                {
                    locations[i] = m_locations[i];
                }

                m_alarmStore->setStoreMonitorLocations( locations );
            }
		    //*/
            // Inform the alarm store of the new session
             m_alarmStore->setSessionId(sessionID.c_str());
// 			 TA_Base_Core::IAlarmStoreCorbaDef::LocationList locations;
// 			 locations.length( m_locations.size() );
// 			 for(unsigned int i = 0; i < m_locations.size(); ++i)
// 			 {
// 				 locations[i] = m_locations[i];
// 			 }			 
//              m_alarmStore->setStoreMonitorLocations( locations );

            // Set the prefilter we are interested in
            TA_Base_Core::IAlarmStoreCorbaDef::FilterInfo preFilter = convertFilterToCorbaDefVersion(m_preFilter);
			
            m_alarmStore->setStorePreFilter(preFilter);
        }
        catch(const TA_Base_Core::ObjectResolutionException& )
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "ObjectResolutionException", "Could not resolve alarm store. Will try again");

            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch( const TA_Base_Core::IAlarmStoreCorbaDef::InvalidFilterException& )
        {
            //TODO: How to get this back out to the calling class
            LOG_EXCEPTION_CATCH(SourceInfo, "InvalidFilterException", "Filter specified is invalid");

            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (CORBA::SystemException& ex)
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "CORBA::SystemException", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ex).c_str());

            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (CORBA::Exception& ce)
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ce).c_str());

            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (const std::exception& e)
        {
            std::ostringstream desc;
            desc << "Caught std::exception in generateAlarmCache; Reason: " << e.what();
            LOG_EXCEPTION_CATCH(SourceInfo, "std::exception", desc.str().c_str());

            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch(...)
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "Unknown", "Caught unknown exception in generateAlarmCache");

            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "updatePreFilterLocationsAndSession come out" );
        FUNCTION_EXIT;
    }


    void AlarmStore::setFilterAndSort(const int cs_pos,bool isDefault)
    {
        FUNCTION_ENTRY("setFilterAndSort");

		  if ( false == isAlarmStoreValid() )
		  {
			  return;
		  }

        TA_THREADGUARD( m_alarmStoreLock );
		/*
        try
        {
            // Remove the old index
            LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "Removing old index");
            m_alarmStore->deleteIndex( m_alarmStoreIndexId );
            m_alarmStoreIndexId = -1;
        }
        catch( const TA_Base_Core::IAlarmStoreCorbaDef::AlarmIndexNotFoundException& )
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "AlarmIndexNotFoundException", "Our registration with the alarm store could not be found. This means we will just register the new index.");
        }
		*/
        try
        {
            // Now add the new one
            TA_Base_Core::IAlarmStoreCorbaDef::FilterInfo filter = convertFilterToCorbaDefVersion( m_filter );
            TA_Base_Core::IAlarmStoreCorbaDef::SortInfo sort = convertSortToCorbaDefVersion( m_sort );
            
            //LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "Adding new index");
            //m_alarmStoreIndexId = m_alarmStore->createIndex(filter, sort,/* m_alarmStoreCallback->_this()*/ cs_pos,m_isHighestSeverityNeeded,isDefault);
			m_bFilterCreated = true;
        }
        catch(const TA_Base_Core::ObjectResolutionException& )
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "ObjectResolutionException", "Could not resolve alarm store. Will indicate that this has to be found");
            
            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (CORBA::SystemException& ex)
        {
			std::string errinfo=TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ex).c_str();		 
			LOG_EXCEPTION_CATCH( SourceInfo, "CORBA::SystemException", errinfo.c_str() );			 
			if (errinfo!="TRANSIENT_CallTimedout")
			{		 
				m_resolveAlarmStore.signal();
			}
			else
			{
				m_bFilterCreated = true;
			}
        }
        catch( const TA_Base_Core::IAlarmStoreCorbaDef::InvalidFilterException& )
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "InvalidFilterException", "Filter is invalid. Converting this into an AlarmListCtrl exception");
            TA_THROW( TA_Base_Core::AlarmListCtrlException("Filter specified was invalid") );
        }
        catch (CORBA::Exception& ce)
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ce).c_str());

            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (const std::exception& e)
        {
            std::ostringstream desc;
            desc << "Caught std::exception in generateAlarmCache; Reason: " << e.what();
            LOG_EXCEPTION_CATCH(SourceInfo, "std::exception", desc.str().c_str());

            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch(...)
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "Unknown", "Caught unknown exception in generateAlarmCache");

            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }

        FUNCTION_EXIT;
    }


    unsigned long AlarmStore::getAlarmCount() const
    {
        TA_Base_Core::ThreadGuard guard(m_alarmCacheLock);
        return m_alarmCache.size();
    }


    TA_Base_Core::IAlarmStoreCorbaDef::FilterInfo AlarmStore::convertFilterToCorbaDefVersion(const Filter& filterToConvert) const
    {
        FUNCTION_ENTRY("convertFilterToCorbaDefVersion");

        // Retrieve the individual filter items from the Filter object
        std::vector<Filter::FilterDetails> filterVector = filterToConvert.getFilters();

        // Now create our sequence and set it to the correct size
        TA_Base_Core::IAlarmStoreCorbaDef::FilterInfo filter;
        filter.length( filterVector.size() );

        // Now we loop through and add each item.
        for(unsigned int i = 0; i < filterVector.size(); ++i)
        {
            TA_Base_Core::IAlarmStoreCorbaDef::FilterEntry filterEntry;
            TA_Base_Core::IAlarmStoreCorbaDef::FilterParameters filterParameters;
            
            switch(filterVector[i].type)
            {
                case(Filter::FILTER_PROFILE):
                    filterParameters.paramText(CORBA::string_dup( filterVector[i].value.stringValue->c_str() ));
                    filterParameters._d(TA_Base_Core::IAlarmStoreCorbaDef::FILTER_PROFILE);
                    break;

                case(Filter::FILTER_ASSOCIATED_ENTITY_NAME):
                    filterParameters.paramText(CORBA::string_dup( filterVector[i].value.stringValue->c_str() ));
                    filterParameters._d(TA_Base_Core::IAlarmStoreCorbaDef::FILTER_ASSOCIATED_ENTITY_NAME);
                    break;

                case(Filter::FILTER_ASSET_NAME):
                    filterParameters.paramText(CORBA::string_dup( filterVector[i].value.stringValue->c_str() ));
                    filterParameters._d(TA_Base_Core::IAlarmStoreCorbaDef::FILTER_ASSET_NAME);
                    break;
                    
                case(Filter::FILTER_DESCRIPTION):
                    filterParameters.paramText(CORBA::string_dup( filterVector[i].value.stringValue->c_str() ));
                    filterParameters._d(TA_Base_Core::IAlarmStoreCorbaDef::FILTER_DESCRIPTION);
                    break;
                    
                case(Filter::FILTER_ALARM_TYPE):
                    filterParameters.paramULong( filterVector[i].value.ulValue );
                    filterParameters._d(TA_Base_Core::IAlarmStoreCorbaDef::FILTER_ALARM_TYPE);
                    break;

                case(Filter::FILTER_SUBSYSTEM):
                    filterParameters.paramULong( filterVector[i].value.ulValue );
                    filterParameters._d(TA_Base_Core::IAlarmStoreCorbaDef::FILTER_SUBSYSTEM);
                    break;

                case(Filter::FILTER_ALARM_TIME):
                    filterParameters.paramULong( filterVector[i].value.ulValue );
                    filterParameters._d(TA_Base_Core::IAlarmStoreCorbaDef::FILTER_ALARM_TIME);
                    break;

                case(Filter::FILTER_LOCATION):
                    filterParameters.paramULong( filterVector[i].value.ulValue );
                    filterParameters._d(TA_Base_Core::IAlarmStoreCorbaDef::FILTER_LOCATION);
                    break;

                case(Filter::FILTER_OPERATOR):
                    filterParameters.paramText( filterVector[i].value.stringValue->c_str() );
                    filterParameters._d(TA_Base_Core::IAlarmStoreCorbaDef::FILTER_OPERATOR);
                    break;

                case(Filter::FILTER_ASSOCIATED_ENTITY_KEY):
                    filterParameters.paramULong( filterVector[i].value.ulValue );
                    filterParameters._d(TA_Base_Core::IAlarmStoreCorbaDef::FILTER_ASSOCIATED_ENTITY_KEY);
                    break;
                    
                case(Filter::FILTER_SEVERITY):
                    filterParameters.paramULong( filterVector[i].value.ulValue );
                    filterParameters._d(TA_Base_Core::IAlarmStoreCorbaDef::FILTER_SEVERITY);
                    break;

                case(Filter::FILTER_ALARM_TIME_RANGE):

                    TA_Base_Core::IAlarmStoreCorbaDef::ParameterDateRange dateRange;
                    dateRange.paramDate1 = filterVector[i].value.dateRange.startTime;
                    dateRange.paramDate2 = filterVector[i].value.dateRange.endTime;
                    filterParameters.paramDateRange( dateRange );
                    filterParameters._d(TA_Base_Core::IAlarmStoreCorbaDef::FILTER_ALARM_TIME_RANGE);
                    break;

                case(Filter::FILTER_STATE):

                    switch( filterVector[i].value.alarmStateValue)
                    {
                        case(Filter::STATE_ALL_OPEN):
                            filterParameters.paramState( TA_Base_Core::IAlarmStoreCorbaDef::STATE_ALL_OPEN );
                            break;

                        case(Filter::STATE_OPEN_UNACKED):
                            filterParameters.paramState( TA_Base_Core::IAlarmStoreCorbaDef::STATE_OPEN_UNACKED );
                            break;

                        case(Filter::STATE_OPEN_ACKED):
                            filterParameters.paramState( TA_Base_Core::IAlarmStoreCorbaDef::STATE_OPEN_ACKED );
                            break;

                        case(Filter::STATE_CLOSED):
                            filterParameters.paramState( TA_Base_Core::IAlarmStoreCorbaDef::STATE_CLOSED );
                            break;

                        case(Filter::STATE_ALL_UNACKED):
                            filterParameters.paramState( TA_Base_Core::IAlarmStoreCorbaDef::STATE_ALL_UNACKED );
                            break;

                        case(Filter::STATE_ANY):
                            filterParameters.paramState( TA_Base_Core::IAlarmStoreCorbaDef::STATE_ANY );
                            break;

                        default:
                            TA_ASSERT(false, "Invalid alarm state. Perhaps enumerated type has been updated but not this switch statement");
                            break;
                    }
                    filterParameters._d(TA_Base_Core::IAlarmStoreCorbaDef::FILTER_STATE);
            
                    break;
            } // End Switch
            
            filterEntry.parameters = filterParameters;

            switch(filterVector[i].comparison)
            {
                case(Filter::COMPARE_LESS_THAN):
                    filterEntry.compareOp = TA_Base_Core::IAlarmStoreCorbaDef::COMPARE_LESS_THAN;
                    break;

                case(Filter::COMPARE_LESS_THAN_EQUAL):
                    filterEntry.compareOp = TA_Base_Core::IAlarmStoreCorbaDef::COMPARE_LESS_THAN_EQUAL;
                    break;

                case(Filter::COMPARE_EQUAL):
                    filterEntry.compareOp = TA_Base_Core::IAlarmStoreCorbaDef::COMPARE_EQUAL;
                    break;

                case(Filter::COMPARE_GREATER_THAN):
                    filterEntry.compareOp = TA_Base_Core::IAlarmStoreCorbaDef::COMPARE_GREATER_THAN;
                    break;

                case(Filter::COMPARE_GREATER_THAN_EQUAL):
                    filterEntry.compareOp = TA_Base_Core::IAlarmStoreCorbaDef::COMPARE_GREATER_THAN_EQUAL;
                    break;

                case(Filter::COMPARE_NOT_EQUAL):
                    filterEntry.compareOp = TA_Base_Core::IAlarmStoreCorbaDef::COMPARE_NOT_EQUAL;
                    break;

                case(Filter::COMPARE_CONTAINS):
                    filterEntry.compareOp = TA_Base_Core::IAlarmStoreCorbaDef::COMPARE_CONTAINS;
                    break;

                case(Filter::COMPARE_RANGE_INCLUSIVE):
                    filterEntry.compareOp = TA_Base_Core::IAlarmStoreCorbaDef::COMPARE_RANGE_INCLUSIVE;
                    break;

                case(Filter::COMPARE_RANGE_EXCLUSIVE):
                    filterEntry.compareOp = TA_Base_Core::IAlarmStoreCorbaDef::COMPARE_RANGE_EXCLUSIVE;
                    break;

                default:
                    TA_ASSERT(false, "Invalid filter type. Perhaps enumerated type has been updated but not this switch statement");
                    break;
            } // End switch

            filter[i] = filterEntry;
        } // End For

        FUNCTION_EXIT;
        return filter;
    }


    TA_Base_Core::IAlarmStoreCorbaDef::SortInfo AlarmStore::convertSortToCorbaDefVersion(const Sort& sortToConvert) const
    {
        FUNCTION_ENTRY("convertSortToCorbaDefVersion");

        // Retrieve the individual filter items from the Filter object
        std::vector<Sort::SortDetails> sortVector = sortToConvert.getSort();

        // Now create our sequence and set it to the correct size
        TA_Base_Core::IAlarmStoreCorbaDef::SortInfo sort;
        sort.length( sortVector.size() );

        // Now we loop through and add each item.
        for(unsigned int i = 0; i < sortVector.size(); ++i)
        {
            TA_Base_Core::IAlarmStoreCorbaDef::SortEntry sortEntry;
            
            switch(sortVector[i].type)
            {
                case(Sort::SORT_OPEN_CLOSE):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_OPEN_CLOSE;
                    break;

			    case(Sort::SORT_ACK_NOT_ACK):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_ACK_NOT_ACK;
                    break;

			    case(Sort::SORT_ALARM_TYPE):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_ALARM_TYPE;
                    break;

			    case(Sort::SORT_LOCATION):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_LOCATION;
                    break;

			    case(Sort::SORT_TIME):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_TIME;
                    break;

			    case(Sort::SORT_DESCRIPTION):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_DESCRIPTION;
                    break;

			    case(Sort::SORT_ENTITY_NAME):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_ENTITY_NAME;
                    break;

			    case(Sort::SORT_SUB_SYSTEM_KEY):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_SUB_SYSTEM_KEY;
                    break;

			    case(Sort::SORT_ACK_TIME):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_ACK_TIME;
                    break;

			    case(Sort::SORT_ACK_BY):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_ACK_BY;
                    break;

                case(Sort::SORT_SEVERITY):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_SEVERITY;
                    break;

                case(Sort::SORT_ASSET_NAME):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_ASSET_NAME;
                    break;

                case(Sort::SORT_VALUE):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_VALUE;
                    break;

                case(Sort::SORT_MMS):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_MMS;
                    break;

                    case(Sort::SORT_DSS):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_DSS;
                    break;

                case(Sort::SORT_AVALANCHE):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_AVALANCHE;
                    break;

                case(Sort::SORT_COMMENT):
                    sortEntry.type = TA_Base_Core::IAlarmStoreCorbaDef::SORT_COMMENT;
                    break;
                    
                default:
                    TA_ASSERT(false, "Invalid sort type. Perhaps enumerated type has been updated but not this switch statement");
                    break;

            } // end switch

            switch(sortVector[i].direction)
            {
                case(Sort::SORT_ASCENDING):
                    sortEntry.direction = TA_Base_Core::IAlarmStoreCorbaDef::SORT_ASCENDING;
                    break;

                case(Sort::SORT_DESCENDING):
                    sortEntry.direction = TA_Base_Core::IAlarmStoreCorbaDef::SORT_DESCENDING;
                    break;

                default:
                    TA_ASSERT(false, "Invalid sort direction. Perhaps enumerated type has been updated but not this switch statement");
                    break;
            } // end switch

            sort[i] = sortEntry;

        } // end for

        FUNCTION_EXIT;
        return sort;
    }

	//////////////////////////////////////////////////////////
	// The following three functions is used for stress test
	/*
	* newAlarm
	*
	* @param alarmDetail - indicate the new alarm detailed data
	*/
	void AlarmStore::newAlarm(TA_Base_Core::AlarmDetailCorbaDef& alarmDetail)
	{
		TA_THREADGUARD( m_alarmStoreLock );
		try
		{
			if(m_bAlarmStoreValid)
			{
				m_alarmStore->newAlarm(alarmDetail);
			}
		}
		catch(const TA_Base_Core::ObjectResolutionException& )
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "ObjectResolutionException", "Could not resolve alarm store. Will indicate that this has to be found");
			
            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (CORBA::SystemException& ex)
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "CORBA::SystemException", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ex).c_str());
			
            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (CORBA::Exception& ce)
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ce).c_str());
			
            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (const std::exception& e)
        {
            std::ostringstream desc;
            desc << "Caught std::exception in generateAlarmCache; Reason: " << e.what();
            LOG_EXCEPTION_CATCH(SourceInfo, "std::exception", desc.str().c_str());
			
            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch(...)
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "Unknown", "Caught unknown exception in generateAlarmCache");
			
            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
	}
	
	/*
	* updateAlarm
	*
	* @param alarmUpdate - indicate the updated alarm detailed data
	*/
	void AlarmStore::updateAlarm(TA_Base_Core::AlarmUpdateCorbaDef alarmUpdate)
	{
		TA_THREADGUARD( m_alarmStoreLock );
		try
		{
			if(m_bAlarmStoreValid)
			{
				m_alarmStore->updateAlarm(alarmUpdate);
			}
		}
		catch(const TA_Base_Core::ObjectResolutionException& )
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "ObjectResolutionException", "Could not resolve alarm store. Will indicate that this has to be found");
			
            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (CORBA::SystemException& ex)
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "CORBA::SystemException", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ex).c_str());
			
            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (CORBA::Exception& ce)
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "CORBA::Exception", TA_Base_Core::CorbaUtil::getInstance().exceptionToString(ce).c_str());
			
            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch (const std::exception& e)
        {
            std::ostringstream desc;
            desc << "Caught std::exception in generateAlarmCache; Reason: " << e.what();
            LOG_EXCEPTION_CATCH(SourceInfo, "std::exception", desc.str().c_str());
			
            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }
        catch(...)
        {
            LOG_EXCEPTION_CATCH(SourceInfo, "Unknown", "Caught unknown exception in generateAlarmCache");
			
            // Start trying to reconnect
            LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Signalling m_resolveAlarmStore..." );
            m_resolveAlarmStore.signal();
        }	}
	


	/*
	* getASTimeStamp
	*
	* this is used to check if alarmStore work normally
	*/
	long AlarmStore::getASTimeStamp()
	{
		long timeStamp = 0;
		TA_THREADGUARD( m_alarmStoreLock );
		try
		{
			if(m_bAlarmStoreValid)
			{
				timeStamp = m_alarmStore->getAliveTimeStamp();
			}
		}
		catch(...)
		{

		}

		return timeStamp;
	}

	//////////////////////////////////////////////////////////

}
