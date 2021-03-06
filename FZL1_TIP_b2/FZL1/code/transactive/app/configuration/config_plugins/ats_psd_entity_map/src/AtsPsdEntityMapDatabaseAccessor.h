/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/GZL6_TIP/3002/transactive/app/configuration/config_plugins/ats_psd_entity_map/src/AtsPsdEntityMapDatabaseAccessor.h $
  * @author:  Karen Graham
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2012/06/12 13:35:44 $
  * Last modified by:  $Author: builder $
  * 
  * This class uses the Data Access Interface to retrieve ATS PSD Entity Map information and returns it to
  * the caller in a variety of formats. It abstracts some of the database access from the views.
  * 
  */


#if !defined(AtsPsdEntityMapDatabaseAccessor_40D09158_85E4_464f_81D1_E7B9225238D9__INCLUDED_)
#define AtsPsdEntityMapDatabaseAccessor_40D09158_85E4_464f_81D1_E7B9225238D9__INCLUDED_

#include <map>
#include <vector>
#include <string>

#include "app/configuration/config_plugins/config_plugin_helper/src/IDatabaseAccessor.h"

// Forward declarations
namespace TA_Base_Core
{
    class IConfigItem;
}
namespace TA_IRS_Core
{
    class IConfigAtsPSDData;
}


namespace TA_IRS_App
{
    class AtsPsdEntityMapDatabaseAccessor : public TA_Base_App::IDatabaseAccessor
    {

    public:

        typedef std::map<unsigned long, std::string>                DataPointKeyToNamesMap;
        typedef DataPointKeyToNamesMap::iterator                    DataPointKeyToNamesMapIt;


        struct AtsPsdEntityMapRecord
        {
            CString status;             // This will be the current applied status of the item (ie new, modified etc)
                                        // It will be set elsewhere so we don't worry about it

			unsigned long key;			// The primary key
            CString station;			// The Station
            CString mssZone;			// The MSS Zone of the station
			CString platformName;		// The Platform Name
			CString psdNumber;			// The number of the PSD
            CString dpType;             // The DataPoint Type
			CString dpInputOutput;		// Input or Output DataPoint
            CString dpName;				// The name of the DataPoint
            CString dpLabel;			// The label of the DataPoint
        };


        /**
         * Constructor
         */
        AtsPsdEntityMapDatabaseAccessor();


        /**
         * Destructor
         */
        virtual ~AtsPsdEntityMapDatabaseAccessor();


        /**
         * loadItems
         *
         * This will retrieve all the ATS PSD Entity Map records from the database and store them in m_AtsPsdEntityMaps.
         *
         * @exception DataException - This will be thrown if there is an error with the ATS PSD Entity Map
         *                            data and it cannot be retrieved for some reason.
         * @exception DatabaseException - This will be thrown if there is an error communicating with the
         *                                database.
         */
        void loadItems();

        
        /**
         * getItemNames
         *
         * This method cannot be used by ATS PSD Entity Maps and will just assert
         */
        std::multimap<CString,unsigned long> getItemNames(CProgressCtrl& progress);
        

        /**
         * getAllItemDetails
         *
         * This retrieves the items' details in a display format.
         * Precondition: loadItems() must be called before this method
         * 
         * @param CProgressCtrl - This is used to show how long the loading is taking
         *
         * @return map<unsigned long, AtsPsdEntityMapRecord> - This is all the ATS PSD Entity Maps keyed
         *                                                    on their unique identifier
         */
        std::map<unsigned long,AtsPsdEntityMapRecord> getAllItemDetails(CProgressCtrl& progress);
        
        
        /**
         * getItemDetails
         *
         * This retrieves the item's details in a display format. The items is specified by passing
         * in its unique identifier.
         * Precondition: loadItems() must be called before this method
         * 
         * @param unsigned long - The identifier of the item to retrieve details for
         *
         * @return AtsPsdEntityMapRecord - This is all the ATS PSD Entity Map details
         */
        AtsPsdEntityMapRecord getItemDetails(unsigned long identifier);
 
        
        /**
         * getItem
         *
         * This returns a database object for the item specified. The item is specified by
         * passing in its unique identifier..
         * Precondition: loadItems() must be called before this method
         *
         * @param unsigned long - The identifier of the item to retrieve
         *
         * @return IConfigItem* - The database object for this item. This will be NULL if one
         *                            is not found.
         */
        virtual TA_Base_Core::IConfigItem* getItem(unsigned long identifier);


        /**
         * deleteItem
         *
         * This will delete the specified item from the database and it will then delete the
         * IConfigItem object held.
         *
         * @param unsigned long - This is the unique identifier for the item to delete
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is an error
         *                              deleting the item
         */
        virtual void deleteItem(unsigned long id);


        /**
         * newItem
         *
         * This creates a new item. This item will be added to the internal list
         * of current items but will not yet be applied to the database.
         *
         * @return IConfigItem* - The newly created item ready for its data to be populated
         */
        virtual TA_Base_Core::IConfigItem* newItem();


        /**
         * copyItem
         *
         * This creates a new item with the same data in it as the item passed in.
         * This item will be added to the internal list of current items but will not yet be
         * applied to the database.
         *
         * @param unsigned long - The unique identifier of the item to copy
         * 
         * @return IConfigItem* - The newly created item ready for its data to be populated
         *
         * @exception DatabaseException - This is thrown if data could not be retrieved for the item
         *                                that is being copied.
         */
        virtual TA_Base_Core::IConfigItem* copyItem(const unsigned long idOfItemToCopy);

        
        /**
         * areCurrentChangesPending
         *
         * This is called to determine if there are any current changes that have not been applied.
         * If this returns true then it will populate the vector of strings passed in with all items
         * not applied.
         * 
         * @param vector<string>& - This is an OUT parameter and should be passed in empty. It will
         *                          be populated with names for all data not yet applied
         * 
         * @return bool - This will return true if there are items that have had changes which have  not
         *                been applied.
         */
         bool areCurrentChangesPending(std::vector<std::string>& itemsNotApplied);

        
         /**
          * invalidate
          *
          * This will set m_isLoaded to false indicating that next time load is called all data should
          * be refreshed from the database.
          */
         void invalidateData()
         {
             m_isLoaded = false;
         }


        /**
         * getAllPsdDataPoints
         *
         * This returns all PSD datapoints and keys to the caller.  Ensure that loadItems() is called first
         * otherwise no data will be returned.
         *
         * @return map<unsigned long, string> - This returns all the datapoint entity keys and names. This is all
         *                                      information needed to update data and to display to the user
         */
        DataPointKeyToNamesMap getAllPsdDataPoints()
        {
            return m_dataPointMap;
        }

        std::string getDataPointName(unsigned long dataPointKey);
        unsigned long getDataPointKey(const std::string& dataPointName);

    protected:
		AtsPsdEntityMapRecord formatItemDetails(TA_IRS_Core::IConfigAtsPSDData* config);
        void refreshDataPointMap();
   
    private:
        /**
         * Copy Constructor
         *
         * Hidden as a private method so it is not used.
         */
        AtsPsdEntityMapDatabaseAccessor( const AtsPsdEntityMapDatabaseAccessor& theAtsPsdEntityMapDatabaseAccessor){ };


        /**
         * Operator =
         *
         * Hidden as a private method so it is not used.
         */
        AtsPsdEntityMapDatabaseAccessor& operator=(const AtsPsdEntityMapDatabaseAccessor& pm);

        typedef std::map<unsigned long, TA_IRS_Core::IConfigAtsPSDData*>   ConfigItems;
        typedef ConfigItems::iterator                               ConfigItemsIt;


        ConfigItems             m_configItems;      // This is all the ATS PSD Entity Maps loaded from the database
        DataPointKeyToNamesMap  m_dataPointMap;
        

        bool m_isLoaded;                // This indicates if we have loaded the ATS PSD Entity Maps before or not.
                                        // If we have never loaded the ATS PSD Entity Maps then when we are told
                                        // to refresh we shouldn't load them.

    };
}

#endif // !defined(AtsPsdEntityMapDatabaseAccessor_40D09158_85E4_464f_81D1_E7B9225238D9__INCLUDED_)
