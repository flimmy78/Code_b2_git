/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/PRIV_3001/3001/transactive/bus/pa/cachedmaps/src/PaDvaVersionCachedMap.h $
  * @author Jade Lee
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by: $Author: lim.cy $
  * 
  * Maintains a cache of DVA Version mappings, also listens
  * out for changes to database regarding the PA_DVA_VERSION table
  *
  */


#if !defined(PaDvaVersionCachedMap_4EBD5CE7_C4D0_43BC_A835_518CA9141975__INCLUDED_)
#define PaDvaVersionCachedMap_4EBD5CE7_C4D0_43BC_A835_518CA9141975__INCLUDED_


#include "core/data_access_interface/pa_4669/src/PaDvaMessageVersionAccessFactory.h"
#include "core/message/IDL/src/CommsMessageCorbaDef.h"
#include "core/message/src/SpecialisedMessageSubscriber.h"
#include "bus/pa_4669/pa_agent/IDL/src/IPAAgentCorbaDef.h"
#include "bus/pa/cachedmaps/src/GenericCachedMap.h"
#include "bus/pa/cachedmaps/src/CachedMapDefinitions.h"

#include <list>

namespace TA_Base_Core
{
    class ConfigUpdateMessageSender;
    class CommsMessageSender;
    class IPaDvaMessageVersion;
}

namespace TA_IRS_Bus
{

    class PaDvaVersionCachedMap : public GenericCachedMap<DvaVersionRecord, TA_Base_Core::IPaDvaMessageVersion>, 
        public TA_Base_Core::SpecialisedMessageSubscriber<TA_Base_Core::CommsMessageCorbaDef>
    {
    public:
    

        PaDvaVersionCachedMap();
        ~PaDvaVersionCachedMap();

        /** 
         * refreshKeyToRecordMap
         *
         * Reads the PA_DVA_VERSION table and populates the KeyToDvaVersionRecordMap collection
         * for all records matching the optional locationKey.  To update the map with all records, 
         * do not specify the the parameter.
         *
         * @param  locationKey (optional) filters the table on the LOCATIONKEY field.
         *
         * @exception DatabaseException 
         *         If there is a problem establishing a connection with the database.
         *         If an error is encountered while retrieving data.
         * @exception DataException      
         *         If the data cannot be converted to the required format.
         *         If the wrong ammount of data is retrieved.
         * @exception InvalidPasConfigurationException 
         *         If a single key is mapped to more than one record (i.e. pkeys are not unique).  
         *         This indicates invalid configuration in the databases.
         *
         */
        void refreshKeyToRecordMap(unsigned long locationKey = 0) ;
            //throw(TA_Base_Core::DataException, TA_Base_Core::DatabaseException, TA_Base_Core::InvalidPasConfigurationException);

        /** 
         * getRecordFromLocation
         *
         * Returns the DvaVersionRecord matching the locationKey parameter.
         *
         * pre: refreshKeyToDvaVersionRecordMap() has been called successfully.
         *
         * @param  locationKey the locationkey field of DvaVersionRecord.
         *
         * @return a single matching DvaVersionRecord
         *
         * @exception CachedMappingNotFoundException if the mapping could not be found.  
         *         This indicates invalid configuration in the databases or the map not 
         *         being initlialised for this location
         */
        DvaVersionRecord getRecordFromLocation(unsigned long locationKey);
            //throw(TA_Base_Core::CachedMappingNotFoundException);

        /** 
         * getKeyFromLocation
         *
         * Returns the key associated with the DvaVersionRecord matched by locationKey.
         * This should be unique.
         *
         * pre: refreshKeyToDvaVersionRecordMap() has been called successfully.
         *
         * @param  zoneId      the zone Id field of DvaVersionRecord.
         * @param  locationKey the locationKey field of DvaVersionRecord.
         *
         * @return the primary key of the DvaVersionRecord
         *
         * @exception CachedMappingNotFoundException if the mapping could not be found.  
         *         This indicates invalid configuration in the databases or the map not 
         *         being initlialised for this location
         *
         */
         unsigned long getKeyFromLocation(unsigned long locationKey);
            //throw(TA_Base_Core::CachedMappingNotFoundException);

        /**
         * setRecord
         *
         * Updates internal DvaVersionRecord record map as appropriate to reflect the changes
         * defined in the input parameter and update the database (optional).  
         * 
         * If the record is new, the record.m_pKey must be set to -1 and 
         * writeChangesToDatabase must be true.  Once the data is written to the database
         * this will update the record.m_pKey with the new pKey.  
         *
         * Note: Code will assert if record m_pKey == -1 and writeChangesToDatabase == false
         * 
         * @param record the DvaVersionRecord details.  Specify -1 for the m_pKey field in the 
         *        case of a new record.  The m_pKey will then be returned modified.
         * @param writeChangesToDataBase set to true if the changes are to be written to 
         *        the database as well.  This should only be called by the PA Agent.
         *
         * @exception DatabaseException 
         *         - if there is a problem establishing a connection with the database.
         *         - if an error is encountered while retrieving data.
         * @exception DataException
         *         - if the data cannot be converted to the required format 
         *           (e.g. ECSZoneId should be an unsigned long)
         *         - NO_VALUE if the ECS Zone Id record cannot be found for the helper 
         *           constructed with an ECS Zone Id.
         *         - NOT_UNIQUE if the ECS Zone Id returns multiple records 
         *
         *
         */
        void setRecord(DvaVersionRecord& record, bool writeChangesToDatabase = false);
            //throw(TA_Base_Core::DataException, TA_Base_Core::DatabaseException, TA_Base_Core::DataConfigurationException);

        virtual void receiveSpecialisedMessage(const TA_Base_Core::CommsMessageCorbaDef& message);
        void subscribeStationUpdate();
        void unsubscribeStationUpdate();

         /**
         * processDvaVersionUpdates
         *
         * Updates internal dva version record map as appropriate to reflect the changes
         * defined in the input parameter
         * 
         * @param updateData the updates information to refresh cached map with
         *
         * @return true if the data contained in 'updateData' is different from the data already contained
         *          within the cached map (that is, the we detected data was different)
         *
         * @exception CachedMappingNotFoundException
         *
         */
        bool processDvaVersionUpdates(const TA_Base_Bus::IPAAgentCorbaDef::DvaVersionRecords& updateData);
            //throw(TA_Base_Core::CachedMappingNotFoundException);

    protected:

        /**
         * validateRecordData (interface implementation)
         *
         * @see GenericCachedMap::validateRecordData for more details
         *
         */
        void validateRecordData(const DvaVersionRecord& paZone);

        /**
         * getRecordFromDatabaseUsingKey (interface implementation)
         *
         * @see GenericCachedMap::getRecordFromDatabaseUsingKey for more details
         *
         */
        TA_Base_Core::IPaDvaMessageVersion* getRecordFromDatabaseUsingKey(unsigned long pKey, bool readWrite);
                                //throw(TA_Base_Core::DataException, TA_Base_Core::DatabaseException);

        /**
         * createRecordFromInterface (interface implementation)
         *
         * @see GenericCachedMap::createRecordFromInterface for more details
         *
         */
        virtual DvaVersionRecord createRecordFromInterface(TA_Base_Core::IPaDvaMessageVersion& item);
                  //throw (TA_Base_Core::InvalidPasConfigurationException);

        /**
         * Called whenever there is a change being made by this class to the database
         *  - Note: Call AFTER the changes has been made
         *
         * This will post out ConfigUpdate messages to everyone listening out for
         *  configEditor updates (with relevant change information)
         *
         * @param recordKey the primary key of the record that has been changed
         *
         * @param modificationType the type of modification (Update, Create, Delete etc)
         *
         * @param changes list of the columns that have changed (if applicable)
         *
         */
        void submitConfigUpdate(unsigned long recordKey, TA_Base_Core::EModificationType modificationType, const std::vector<std::string>& changes);

        /**
        * Called whenever there is a change being made by this class to the database
        *  - Note: Call AFTER the changes has been made
        *
        * This will post out ConfigUpdate messages to everyone listening out for
        *  configEditor updates (with relevant change information)
        *
        * @param recordKey the primary key of the record that has been changed
        *
        * @param modificationType the type of modification (Update, Create, Delete etc)
        *
        * @param changes list of the columns that have changed (if applicable)
        *
        */
        void submitCommsUpdate(DvaVersionRecord& refRecord);

        unsigned long getOccLocationKey();

    protected:

        // Sends out config update notifications whenever a change
        // made to database via this class (so other PAManagers know about it)
        TA_Base_Core::ConfigUpdateMessageSender* m_configUpdateSender;
        TA_Base_Core::CommsMessageSender* m_commsUpdateSender;

        /// Custom filter for getDvaVersionRecordFromLocationKey
        class FilterByLocationKey : public ICachedMapFilter<DvaVersionRecord>
        {
        public:
            FilterByLocationKey(unsigned long locationKey) : m_locationKey(locationKey) 
            {
            }

            virtual bool isMatch(const DvaVersionRecord& record) const
            {
                return record.ulLocationKey == m_locationKey;
            }

        private:
            unsigned long m_locationKey;
        };

    private:
        bool m_bIsOcc;
    };

} // end namespace TA_IRS_Bus

#endif //!defined(PaDvaVersionCachedMap_4EBD5CE7_C4D0_43BC_A835_518CA9141975__INCLUDED_)
