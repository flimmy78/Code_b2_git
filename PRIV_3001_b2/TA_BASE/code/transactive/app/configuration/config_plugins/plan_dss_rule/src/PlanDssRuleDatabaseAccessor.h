/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/configuration/config_plugins/plan_dss_rule/src/PlanDssRuleDatabaseAccessor.h $
  * @author:  Karen Graham
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  * 
  * This class uses the Data Access Interface to retrieve alarm plan association information and returns it to
  * the caller in a variety of formats. It abstracts some of the database access from the views.
  * 
  */


#if !defined(PlanDssRuleDatabaseAccessor_40D09158_85E4_464f_81D1_E7B9225238D9__INCLUDED_)
#define PlanDssRuleDatabaseAccessor_40D09158_85E4_464f_81D1_E7B9225238D9__INCLUDED_

#include <map>
#include <vector>
#include <string>

#include "app/configuration/config_plugins/config_plugin_helper/src/IDatabaseAccessor.h"

// Forward declarations
namespace TA_Base_Core
{
    class IConfigPlanDssDpRule;
    class IConfigItem;
}


namespace TA_Base_App
{
	const int SECONDS_IN_MINUTE = 60;
	const int SECONDS_IN_HOUR = 3600;
	const int HOURS_IN_DAY = 24;
	const int SECONDS_IN_DAY = 86400;
	const int SECONDS_INTERVAL = 28800;    //8 hours * 3600 seconds

    // This is a map of IConfigPlanDssDpRule* objects stored by their key (unsigned long)
    typedef std::map<unsigned long, TA_Base_Core::IConfigPlanDssDpRule*> LoadedDssRules;

    class PlanDssRuleDatabaseAccessor : public IDatabaseAccessor
    {

    public:

        struct PlanDssDpRuleText
        {
            std::string status;     // This will be the current applied status of the item (ie new, modified etc)
            std::string strLocation;  // Location name
            std::string strActivePlan;     // The active plan name
            std::string strTriggerEntity; // The entity 
            std::string strMinimumInterval;       // The minimum interval
			std::string strActivedTolerantTime;   //The Actived tolerant time
			std::string strDenyStrategy;          //The Deny Strategy
			std::string strActivateValue;         //The Activate Value
			std::string strNeedDeactivate;        //Need deactivate 
			std::string strAllowMultiple;        //Allow Multiple
			std::string strValidTimeInDay;       //The Valid time in day
			std::string strValidDaysInWeek;        //The Valid days in week
			std::string strEnable;                 //Enable
        };


        /**
         * Constructor
         */
        PlanDssRuleDatabaseAccessor();


        /**
         * Destructor
         */
        virtual ~PlanDssRuleDatabaseAccessor();


        /**
         * loadItems
         *
         * This will retrieve all the alarm plan associations from the database and store them in m_PlanDssRules.
         *
         * @exception DataException - This will be thrown if there is an error with the alarm plan association
         *                            data and it cannot be retrieved for some reason.
         * @exception DatabaseException - This will be thrown if there is an error communicating with the
         *                                database.
         */
        void loadItems();

        virtual std::map<CString,unsigned long> getItemNames(CProgressCtrl& progress);

        /**
         * getAllItemDetails
         *
         * This retrieves the items' details in a display format.
         * Precondition: loadItems() must be called before this method
         * 
         * @param CProgressCtrl - This is used to show how long the loading is taking
         *
         * @return map<unsigned long, PlanDssRuleiation> - This is all the alarm plan assocations keyed
         *                                                    on their unique identifier
         */
        std::map<unsigned long,PlanDssDpRuleText> getAllItemDetails(CProgressCtrl& progress);

        std::map<unsigned long, std::string> getAllLocations();
        std::map<unsigned long, std::string> getAllStrategies( const bool bOnlyValid = true );

        void reloadLocations();
        
        
        /**
         * getItemDetails
         *
         * This retrieves the item's details in a display format. The items is specified by passing
         * in its unique identifier.
         * Precondition: loadItems() must be called before this method
         * 
         * @param unsigned long - The identifier of the item to retrieve details for
         *
         * @return PlanDssRuleiation - This is all the alarm plan assocation details
         */
        PlanDssDpRuleText getItemDetails(unsigned long identifier);
 
        
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
         void invalidateData();

         void convertItemToDisplay( TA_Base_Core::IConfigPlanDssDpRule& refFrom, PlanDssDpRuleText& refTo );

		 void convertValidDaysToDisplay( std::string& strValidDaysInWeek, TA_Base_Core::IConfigPlanDssDpRule& refFrom );
    
    private:
        /**
         * Copy Constructor
         *
         * Hidden as a private method so it is not used.
         */
        PlanDssRuleDatabaseAccessor( const PlanDssRuleDatabaseAccessor& thePlanDssRuleDatabaseAccessor){ };

        /**
         * Operator =
         *
         * Hidden as a private method so it is not used.
         */
        PlanDssRuleDatabaseAccessor& operator=(const PlanDssRuleDatabaseAccessor& pm);

        LoadedDssRules m_PlanDssRules;   // This is all the alarm plan associations loaded from the database

        bool m_isLoaded;

        std::map<unsigned long, std::string> m_mapLocations;
    };
}

#endif // !defined(PlanDssRuleDatabaseAccessor_40D09158_85E4_464f_81D1_E7B9225238D9__INCLUDED_)
