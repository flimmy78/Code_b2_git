/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/pa_4669/src/ConfigPaTisZoneMap.h $
  * @author Jade Lee
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2012/11/20 09:51:49 $
  * Last modified by: $Author: qi.huang $
  * 
  * ConfigPaTisZoneMap is a concrete implementation of IConfigPaTisZoneMap, which is in turn an implementation
  * of IPaTisZoneMap. It is to be used by the Configuration Editor, and other applications
  * that wish to change the database content for PaTisZoneMaps.
  */


#ifndef CONFIGPATISZONEMAP_INCLUDED_
#define CONFIGPATISZONEMAP_INCLUDED_

#include <string>
#include <set>

#include "core/data_access_interface/pa_4669/src/IConfigPaTisZoneMap.h"

namespace TA_Base_Core
{
    class IData;
}

namespace TA_Base_Core
{
    class PaTisZoneMapHelper;

    class ConfigPaTisZoneMap : public IConfigPaTisZoneMap
    {

    public:
        /**
         * ConfigPaTisZoneMap (constructor)
         *
         * Constructs a new instance of the ConfigPaTisZoneMap with no id. This is used when
         * creating a *new* PaTisZoneMap - that is, one that does not yet exist in the database.
         */
        ConfigPaTisZoneMap();

        /**
         * ConfigPaTisZoneMap (constructor)
         *
         * Constructs a new instance using the information provided in IData interface
         *
         * @see PaTisZoneMapHelper::PaTisZoneMapHelper(IData*)
         *
         */
        ConfigPaTisZoneMap(unsigned long row, TA_Base_Core::IData& data);

        /**
         * ConfigPaTisZoneMap (constructor)
         *
         * Constructs a new instance of ConfigPaTisZoneMap with the specified id. This is used 
         * when creating a ConfigPaTisZoneMap based around an existing PaTisZoneMap in the database.
         *
         * @param key The key to this PaTisZoneMap in the database.
         */
        ConfigPaTisZoneMap(const unsigned long idKey);


        /**
         * ConfigPaTisZoneMap (copy constructor)
         *
         * @param ConfigPaTisZoneMap& - The PaTisZoneMap to make a copy of.
         */
        ConfigPaTisZoneMap( const ConfigPaTisZoneMap& theConfigPaTisZoneMap);

        
        virtual ~ConfigPaTisZoneMap();


    public:

        /**
         * deleteThisObject
         *
         * Removes this PaTisZoneMap from the database. 
         * The calling application MUST then delete this PaTisZoneMap object, as it makes no sense
         * to keep it any longer.
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a 
         *            problem writing the data to the database.
         *
         * pre: Either - this PaTisZoneMap was initially loaded from the database
         *      OR     - writePaTisZoneMapData() has already been called
         *      This PaTisZoneMap has not been deleted
         */
        void deleteThisObject(bool cascade=false);


        /**
         * applyChanges
         *
         * This will apply all changes made to the database.
         *
         * @exception DatabaseException Thrown if there is a database error.
         * @exception DataException Thrown if the a parameter name cannot be found, or if
         *            there is more than one value for a parmeter.
         * @exception DataConfigurationException If the data contained in the PaTisZoneMap object
         *            is not sufficent to create an entry in the database, a 
         *            DataConfigurationException will be thrown. This is thrown as an exception
         *            and not tested as an assert as it can be directly linked to GUI components
         *            and may be the result of a user action that occurs prior to filling in 
         *            all sections.
         *
         * pre: This PaTisZoneMap has not been deleted
         */
        void applyChanges();
        

        /**
         * getKey
         *
         * Returns the key for this PaTisZoneMap.
         *
         * @return The key for this PaTisZoneMap as an unsigned long.
         *
         * pre: Either - this PaTisZoneMap was initially loaded from the database
         *      OR     - writePaTisZoneMapData() has already been called
         *      AND    - deleteThisObject() has NOT been called
         */
        virtual unsigned long getKey();
        virtual unsigned long getPaZoneKey();
        virtual std::string getTisZoneEntity();

        virtual void setPaZoneKey(const unsigned long id);
        virtual void setTisZoneEntity(const std::string& strTisZoneEntity);


         /**
         * getName
         *
         * Returns the name of this item for the IItem interface.  For the PA DVA Message this is 
         * just the key in a string format e.g. "PA Dva Message 1".
         *
         * @return The key description for this item as a std::string
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception DataException A DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. ACCESSLEVEL should be an 
         *            unsigned long), or if the wrong ammount of data is retrieved.
         */
        virtual std::string getName();

        /**
         * setName
         *
         * Not applicable for PA DVA Messages.  Will just assert.
         *
         * @param name The name to give this item.
         *
         */
        virtual void setName(const std::string& name);


        /**
         * getAllItemChanges
         *
         * This is called to retrieve all changes made to this zone. If the map returned is empty then
         * no changes have been made. This must be called before the changes are applied or it will be
         * cleared.
         *
         * @return ItemChanges - The map containing all display changes
         */
        virtual TA_Base_Core::ItemChanges getAllItemChanges()
        {
            return m_PaTisZoneMapChanges;
        }

       /**
         * getUniqueIdentifier
         *
         * This retrieves the unique identifier for this operator. We cannot use keys for identification
         * in the configuration editor because new operators do not have keys. Therefore we use this
         * method for identification
         *
         * @return unsigned long - The unique identifier for this operator
         */
        virtual unsigned long getUniqueIdentifier()
        {
            return m_uniqueIdentifier;
        };

        /**
         * getDateCreated
         *
         * Returns the date created for this PaTisZoneMap
         *
         * @return The date created for this PaTisZoneMap as a time_t.
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception DataException A DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. TYPEKEY should be an 
         *            unsigned long), or if the wrong amount of data is retrieved, or if the
         *            the entity key is invalid (and this is not a new entity).
         */
        virtual time_t getDateCreated();


        /**
         * getDateModified
         *
         * Returns the date modified for this PaTisZoneMap.
         *
         * @return The date modified for this PaTisZoneMap as a time_t.
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception DataException A DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. TYPEKEY should be an 
         *            unsigned long), or if the wrong amount of data is retrieved, or if the
         *            the entity key is invalid (and this is not a new entity).
         */
        virtual time_t getDateModified();

        
        /**
         * hasChanged
         *
         * This should be called to determine if any part of the PaTisZoneMap has been changed by the user.
         *
         * @return bool - This will return true if the PaTisZoneMap does not match the one in the database. It 
         *                will return false if the data has not changed from that in the database.
         */
        virtual bool hasChanged()
        {
            // If the PaTisZoneMap changes is empty then nothing has changed
            return !m_PaTisZoneMapChanges.empty();
        }


        /**
         * isNew
         *
         * This should be called to determine if this PaTisZoneMap is new. A new PaTisZoneMap is one that has not
         * yet been applied to the database and been given a pkey and create date.
         *
         * @return bool - This will return true if the PaTisZoneMap has not been applied to the database.
         */
        virtual bool isNew();


        /**
         * invalidate
         *
         * Make the data contained by this PaTisZoneMap as invalid. The next call to get...() 
         * following a call to invalidate() will cause all the data to be reloaded from
         * the database.
         *
         * pre: deleteThisObject() has NOT been called
         */
        void invalidate();


        private:
            
	    /**
         * updatePaTisZoneMapChanges
         *
         * This updates the map recording the changes to the PaTisZoneMap. Whenever a call to set is made in this
         * class then this method must be called to store the changes.
         *
         * @param const string& - The name of the attribute that has been given a new value
         * @param const string& - The old value that was stored for this attribute
         * @param const string& - The new value to be stored for this attribute
         */
        virtual void updatePaTisZoneMapChanges(const std::string& name, const std::string& oldValue, const std::string& newValue);
 
	    /**
         * updatePaTisZoneMapChanges
         *
         * This updates the map recording the changes to the PaTisZoneMap. Whenever a call to set is made in this
         * class then this method must be called to store the changes.  The input values are converted to
         * string representations before being added to the map
         *
         * @param const string& - The name of the attribute that has been given a new value
         * @param const unsigned long - The old value that was stored for this attribute
         * @param const unsigned long - The new value to be stored for this attribute
         */
        virtual void updatePaTisZoneMapChanges(const std::string& name, const unsigned long oldValue, const unsigned long newValue);
		
        // Assignment PaTisZoneMap not used so it is made private
		ConfigPaTisZoneMap& operator=(const ConfigPaTisZoneMap&);


        unsigned long m_uniqueIdentifier; // We cannot use keys for identification of PaTisZoneMaps in the
                                          // Configuration Editor because new PaTisZoneMaps do not have keys.
                                          // Therefore we use this method for identification.

        static long s_nextAvailableIdentifier; // The next unique identifier available


        PaTisZoneMapHelper* m_PaTisZoneMapHelper;


        TA_Base_Core::ItemChanges m_PaTisZoneMapChanges; // This is a map of all changes made to the PaTisZoneMap so that they are
                                       // recorded and can be sent in audit or online update messages.

    };
} // closes TA_Base_Core

#endif // !defined(ConfigPaTisZoneMap_BB23A710_0466_469f_952A_E7A090EFB3CD__INCLUDED_)
