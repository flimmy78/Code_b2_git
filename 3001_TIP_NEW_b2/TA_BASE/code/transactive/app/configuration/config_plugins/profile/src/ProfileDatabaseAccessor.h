/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/configuration/config_plugins/profile/src/ProfileDatabaseAccessor.h $
  * @author:  Karen Graham
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * This class uses the Data Access Interface to retrieve profile information and returns it to
  * the caller in a variety of formats. It abstracts some of the database access from the views.
  * 
  */


#if !defined(ProfileDatabaseAccessor_40D09158_85E4_464f_81D1_E7B9225238D9__INCLUDED_)
#define ProfileDatabaseAccessor_40D09158_85E4_464f_81D1_E7B9225238D9__INCLUDED_

#include <map>
#include <vector>
#include <string>

#include "app/configuration/config_plugins/config_plugin_helper/src/IDatabaseAccessor.h"


// Forward declarations
namespace TA_Base_Core
{
    class IConfigProfile;
    class IConfigItem;
}


namespace TA_Base_App
{
    class ProfileDatabaseAccessor : public IDatabaseAccessor
    {

    public:

        /**
         * Constructor
         */
        ProfileDatabaseAccessor();


        /**
         * Destructor
         */
        virtual ~ProfileDatabaseAccessor();


        /**
         * loadItems
         *
         * This will retrieve all the profiles from the database and store them in m_profiles.
         *
         * @exception DataException - This will be thrown if there is an error with the profile data and it
         *                             cannot be retrieved for some reason.
         * @exception DatabaseException - This will be thrown if there is an error communicating with the
         *                                database.
         */
        void loadItems();

        
        /**
         * getItemNames
         *
         * This returns all profile names and keys to the caller. 
         * Precondition: loadItems() must be called before this method
         *
         * @param CProgressCtrl& - The progress control to advance as the names are retrieved.
         *
         * @return map<CString, unsigned long> - This returns a map of all the profile names. The map also
         *                                       contains the identifier of the profile as the caller will probably
         *                                       need this later to specify a specific profile.
         *
         * @exception DataException - This will be thrown if there is an error with the profile's data and it
         *                            cannot be retrieved for some reason.
         * @exception DatabaseException - This will be thrown if there is an error communicating with the
         *                                database.
         */
        std::map<CString,unsigned long> getItemNames(CProgressCtrl& progress);
        

        /**
         * getItem
         *
         * This returns a database object for the item specified. The item is specified by
         * passing in its key.
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
         bool areCurrentChangesPending(std::vector<std::string>& profilesNotApplied);

        
        /**
         * getAllRadioLoginGroups
         *
         * This returns all radio login groups and keys to the caller. This goes to the database each time
         * this method is called.
         *
         * @return map<unsigned long, string> - This returns all the radio login group keys and names.
         */
         std::map<unsigned long, std::string> getAllRadioLoginGroups();


        /**
         * getAllAccessControlGroups
         *
         * This returns all access control groups and keys to the caller. This goes to the database each time
         * this method is called.
         *
         * @return map<unsigned long, string> - This returns all the access control group keys and names.
         */
         std::map<unsigned long, std::string> getAllAccessControlGroups();

         /**
         * getAllDistinctParameterNames
         *
         * This returns all the different parameter names that represent displays. These will be used as the
         * column headers in the list control. This goes to the database each time
         * this method is called.
         *
         * @return std::vector<std::string> - This returns all the different parameter names.
         */
         std::vector<std::string> getAllDistinctParameterNames();

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


    private:
        /**
         * Copy Constructor
         *
         * Hidden as a private method so it is not used.
         */
        ProfileDatabaseAccessor( const ProfileDatabaseAccessor& theProfileDatabaseAccessor){ };


        /**
         * Operator =
         *
         * Hidden as a private method so it is not used.
         */
        ProfileDatabaseAccessor& operator=(const ProfileDatabaseAccessor& pm);


        // This is a map of IConfigProfile* objects stored by their profile key (unsigned long)
        typedef std::map<unsigned long, TA_Base_Core::IConfigProfile*> LoadedProfiles;

        LoadedProfiles m_profiles;   // This is all the profiles loaded from the database

        bool m_isLoaded;          // This indicates if we have loaded the profiles before or not. If we
                                  // have never loaded the profiles then when we are told to refresh we
                                  // shouldn't load them.

    };
}

#endif // !defined(ProfileDatabaseAccessor_40D09158_85E4_464f_81D1_E7B9225238D9__INCLUDED_)
