/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/GZL6_TIP/3002/transactive/core/data_access_interface/stis_manager/src/ConfigTiRatisDestination.h $
  * @author chunzhong
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2012/06/12 13:35:44 $
  * Last modified by: $Author: builder $
  * 
  * ConfigTiRatisDestination is a concrete implementation of IConfigTiRatisDestination, which is in turn an implementation
  * of ITiRatisDestination. It is to be used by the Configuration Editor, and other applications
  * that wish to change the database content for TiRatisDestinations.
  */


#ifndef TI_RATIS_DESTIONATION_CONFIG_H_INCLUDED
#define TI_RATIS_DESTIONATION_CONFIG_H_INCLUDED


#include <string>
#include <set>

#include "core/data_access_interface/stis_manager/src/IConfigTiRatisDestination.h"


namespace TA_Base_Core
{
    class IData;
}



namespace TA_IRS_Core
{
    class TiRatisDestinationHelper;

    class ConfigTiRatisDestination : public IConfigTiRatisDestination
    {

    public:
        /**
         * ConfigTiRatisDestination (constructor)
         *
         * Constructs a new instance of the ConfigTiRatisDestination with no id. This is used when
         * creating a *new* TiRatisDestination - that is, one that does not yet exist in the database.
         */
        ConfigTiRatisDestination();

        /**
         * ConfigTiRatisDestination (constructor)
         *
         * Constructs a new instance using the information provided in IData interface
         *
         * @see TiRatisDestinationHelper::TiRatisDestinationHelper(IData*)
         *
         */
        ConfigTiRatisDestination(unsigned long row, TA_Base_Core::IData& data);

        /**
         * ConfigTiRatisDestination (constructor)
         *
         * Constructs a new instance of ConfigTiRatisDestination with the specified id. This is used 
         * when creating a ConfigTiRatisDestination based around an existing TiRatisDestination in the database.
         *
         * @param key The key to this TiRatisDestination in the database.
         */
        ConfigTiRatisDestination(const unsigned long idKey);


        /**
         * ConfigTiRatisDestination (copy constructor)
         *
         * @param ConfigTiRatisDestination& - The TiRatisDestination to make a copy of.
         */
        ConfigTiRatisDestination( const ConfigTiRatisDestination& theConfigTiRatisDestination);

        
        virtual ~ConfigTiRatisDestination();


    public:

        /**
         * deleteThisObject
         *
         * Removes this TiRatisDestination from the database. 
         * The calling application MUST then delete this TiRatisDestination object, as it makes no sense
         * to keep it any longer.
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a 
         *            problem writing the data to the database.
         *
         * pre: Either - this TiRatisDestination was initially loaded from the database
         *      OR     - writeTiRatisDestinationData() has already been called
         *      This TiRatisDestination has not been deleted
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
         * @exception DataConfigurationException If the data contained in the TiRatisDestination object
         *            is not sufficent to create an entry in the database, a 
         *            DataConfigurationException will be thrown. This is thrown as an exception
         *            and not tested as an assert as it can be directly linked to GUI components
         *            and may be the result of a user action that occurs prior to filling in 
         *            all sections.
         *
         * pre: This TiRatisDestination has not been deleted
         */
        void applyChanges();
        

        /**
         * getKey
         *
         * Returns the key for this TiRatisDestination.
         *
         * @return The key for this TiRatisDestination as an unsigned long.
         *
         * pre: Either - this TiRatisDestination was initially loaded from the database
         *      OR     - writeTiRatisDestinationData() has already been called
         *      AND    - deleteThisObject() has NOT been called
         */
        
        virtual unsigned long getKey();

		virtual std::string	getDestination();

		virtual void setDestination(const std::string & destination);

		
         /**
         * getName
         *
         * Returns the name of this item for the IItem interface.  For the PA Station this is 
         * just the key in a string format e.g. "PA Station 1".
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
            return m_tiRatisDestinationChanges;
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
         * hasChanged
         *
         * This should be called to determine if any part of the TiRatisDestination has been changed by the user.
         *
         * @return bool - This will return true if the TiRatisDestination does not match the one in the database. It 
         *                will return false if the data has not changed from that in the database.
         */
        virtual bool hasChanged()
        {
            // If the TiRatisDestination changes is empty then nothing has changed
            return !m_tiRatisDestinationChanges.empty();
        }


        /**
         * isNew
         *
         * This should be called to determine if this TiRatisDestination is new. A new TiRatisDestination is one that has not
         * yet been applied to the database and been given a pkey and create date.
         *
         * @return bool - This will return true if the TiRatisDestination has not been applied to the database.
         */
        virtual bool isNew();

        /**
         * getModifiedKey (interface implementation)
         *
         * @see IConfigPaTrainDvaMessage::getModifiedKey for more details
         */
        virtual unsigned long getModifiedKey();

        /**
         * invalidate
         *
         * Make the data contained by this TiRatisDestination as invalid. The next call to get...() 
         * following a call to invalidate() will cause all the data to be reloaded from
         * the database.
         *
         * pre: deleteThisObject() has NOT been called
         */
        void invalidate();


        private:
            
	    /**
         * updateTiRatisDestinationChanges
         *
         * This updates the map recording the changes to the TiRatisDestination. Whenever a call to set is made in this
         * class then this method must be called to store the changes.
         *
         * @param const string& - The name of the attribute that has been given a new value
         * @param const string& - The old value that was stored for this attribute
         * @param const string& - The new value to be stored for this attribute
         */
        virtual void updateTiRatisDestinationChanges(const std::string& name, const std::string& oldValue, const std::string& newValue);
 
	    /**
         * updateTiRatisDestinationChanges
         *
         * This updates the map recording the changes to the TiRatisDestination. Whenever a call to set is made in this
         * class then this method must be called to store the changes.  The input values are converted to
         * string representations before being added to the map
         *
         * @param const string& - The name of the attribute that has been given a new value
         * @param const unsigned long - The old value that was stored for this attribute
         * @param const unsigned long - The new value to be stored for this attribute
         */
        virtual void updateTiRatisDestinationChanges(const std::string& name, const unsigned long oldValue, const unsigned long newValue);
		
        // Assignment TiRatisDestination not used so it is made private
		ConfigTiRatisDestination& operator=(const ConfigTiRatisDestination&);


        unsigned long m_uniqueIdentifier; // We cannot use keys for identification of TiRatisDestinations in the
                                          // Configuration Editor because new TiRatisDestinations do not have keys.
                                          // Therefore we use this method for identification.

        static long s_nextAvailableIdentifier; // The next unique identifier available


        TiRatisDestinationHelper* m_tiRatisDestinationHelper;


        TA_Base_Core::ItemChanges m_tiRatisDestinationChanges; // This is a map of all changes made to the TiRatisDestination so that they are
                                       // recorded and can be sent in audit or online update messages.

    };
} // closes TA_IRS_Core

#endif // !defined(ConfigTiRatisDestination_BB23A710_0466_469f_952A_E7A090EFB3CD__INCLUDED_)
