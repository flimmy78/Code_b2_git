/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source: $File: //depot/PRIV_3001/TA_BASE/transactive/core/data_access_interface/src/IConfigECSStationColourData.h $
 * @author Andy Siow
 * @version $Revision: #1 $
 * Last modification: $DateTime: 2018/03/14 13:51:20 $
 * Last modified by: $Author: lim.cy $
 * 
 * IECSStationColourData is a writeable interface to an Alarm Station object.
 * It allows the Alarm Station object implementation
 * to be changed without changing the code that uses this interface.
 */


#ifndef ICONFIG_ECS_STATION_COLOUR_DATA_H
#define ICONFIG_ECS_STATION_COLOUR_DATA_H

#include <string>

#include "core/data_access_interface/src/IECSStationColourData.h"
#include "core/data_access_interface/src/IConfigItem.h"


namespace TA_Base_Core
{

    class IConfigECSStationColourData:
        public IECSStationColourData, public IConfigItem
	{
	public:


        /**
         * getUniqueIdentifier
         *
         * This retrieves the unqiue identifier for this item. We cannot use keys for identification
         * in the configuration editor because new items do not have keys. Therefore we use this
         * method for identification
         *
         * @return unsigned long - The unique identifier for this item
         */
        virtual unsigned long getUniqueIdentifier() = 0;


        /**
         * getAllItemChanges
         *
         * This is called to retrieve all changes made to the item. If the map returned is empty then
         * no changes have been made. This must be called before the changes are applied or it will be
         * cleared.
         *
         * @return ItemChanges - The map containing all item changes
         */
        virtual ItemChanges getAllItemChanges() = 0;

        
        /**
         * hasChanged
         *
         * This should be called to determine if any part of the item has been changed by the user.
         *
         * @return bool - This will return true if the item does not match the one in the database. It 
         *                will return false if the data has not changed from that in the database.
         */
        virtual bool hasChanged() =0;


        /**
         * isNew
         *
         * This should be called to determine if this item is new. A new item is one that has not
         * yet been applied to the database and been given a pkey and create date.
         *
         * @return bool - This will return true if the item has not been applied to the database.
         */
        virtual bool isNew() =0;


        /**
         * applyChanges
         *
         * This will apply all changes made to the database.
         *
         * @exception DatabaseException Thrown if there is a database error.
         * @exception DataException Thrown if the a parameter name cannot be found, or if
         *            there is more than one value for a parmeter.
         * @exception DataConfigurationException If the data contained in the Item object
         *            is not sufficent to create an entry in the database, a 
         *            DataConfigurationException will be thrown. This is thrown as an exception
         *            and not tested as an assert as it can be directly linked to GUI components
         *            and may be the result of a user action that occurs prior to filling in 
         *            all sections.
         *
         * pre: This item has not been deleted
         */
        virtual void applyChanges() =0;
    
    
    
        /**
         * setName
         *
         * Sets the name of the AlarmStation.
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception DataException A DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. colour should be an 
         *            unsigned long), or if the wrong amount of data is retrieved.
         */
        virtual void setName(const std::string& name) =0;


		/**
		 * setStationColourKey
		 *
		 * Sets the Station RGB level of this Alarm type.
         *
         * @param unsigned long - The RGB colour
         * @param EColourType - Which colour type is being updated.
		 *
		 * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception DataException A DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. colour should be an 
         *            unsigned long), or if the wrong amount of data is retrieved.
		 */
		virtual void setStationColourKey(unsigned long colour, EColourType type=CURRENT_PROPOSED_CF) =0;


        virtual ~IConfigECSStationColourData() {};
	};

} //close namespace TA_Base_Core

#endif // ICONFIG_ECS_STATION_COLOUR_DATA_H
