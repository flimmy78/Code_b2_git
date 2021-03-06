/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/configuration/config_plugins/system_controller/src/SystemControllerDatabaseAccessor.h $
  * @author:  Karen Graham
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * This class uses the Data Access Interface to retrieve system controller information and returns it to
  * the caller in a variety of formats. It abstracts some of the database access from the views.
  * 
  */


#if !defined(SystemControllerDatabaseAccessor_40D09158_85E4_464f_81D1_E7B9225238D9__INCLUDED_)
#define SystemControllerDatabaseAccessor_40D09158_85E4_464f_81D1_E7B9225238D9__INCLUDED_

#include <map>
#include <vector>
#include <string>

#include "app/configuration/config_plugins/config_plugin_helper/src/IDatabaseAccessor.h"


// Forward declarations
namespace TA_Base_Core
{
    class IConfigSystemController;
    class IConfigItem;
}


namespace TA_Base_App
{
    class SystemControllerDatabaseAccessor : public IDatabaseAccessor
    {

    public:

        /**
         * Constructor
         */
        SystemControllerDatabaseAccessor();


        /**
         * Destructor
         */
        virtual ~SystemControllerDatabaseAccessor();


        /**
         * loadItems
         *
         * This will retrieve all the system controllers from the database and store them in m_systemControllers.
         *
         * @exception DataException - This will be thrown if there is an error with the System Controller data and it
         *                             cannot be retrieved for some reason.
         * @exception DatabaseException - This will be thrown if there is an error communicating with the
         *                                database.
         */
        void loadItems();

        
        /**
         * getItemNames
         *
         * This returns all system controller names and keys to the caller. 
         * Precondition: loadItems() must be called before this method
         *
         * @param CProgressCtrl& - The progress control to advance as the names are retrieved.
         *
         * @return map<CString, unsigned long> - This returns a map of all the system controller names. The map also
         *                                       contains the identifier of the system controller as the caller will probably
         *                                       need this later to specify a specific system controller.
         *
         * @exception DataException - This will be thrown if there is an error with the system controller's data and it
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
         * getAllGroups
         *
         * This returns all system controller groups and keys to the caller. This goes to the database each time
         * this method is called.
         *
         * @return map<unsigned long, string> - This returns all the group keys and names.
         */
        std::map<unsigned long, std::string> getAllGroups();


         /**
         * getAllServers
         *
         * This returns all server entities and keys to the caller. This goes to the database each time
         * this method is called.
         *
         * @return map<unsigned long, string> - This returns all the server entity keys and names.
         */
        std::map<unsigned long, std::string> getAllServers();


         /**
         * getAllManagedProcesses
         *
         * This returns all managed process entity names and keys to the caller. This goes to the database each time
         * this method is called.
         *
         * @return map<unsigned long, string> - This returns all the managed process entity keys and names.
         */
        std::map<unsigned long, std::string> getAllManagedProcesses();

    
    private:
        /**
         * Copy Constructor
         *
         * Hidden as a private method so it is not used.
         */
        SystemControllerDatabaseAccessor( const SystemControllerDatabaseAccessor& theSystemControllerDatabaseAccessor){ };


        /**
         * Operator =
         *
         * Hidden as a private method so it is not used.
         */
        SystemControllerDatabaseAccessor& operator=(const SystemControllerDatabaseAccessor& pm);


        static const std::string SERVER_ENTITY_TYPE;
        static const std::string MANAGED_PROCESS_ENTITY_TYPE;

        // This is a map of IConfigSystemController* objects stored by their SystemController key (unsigned long)
        typedef std::map<unsigned long, TA_Base_Core::IConfigSystemController*> LoadedSystemControllers;

        LoadedSystemControllers m_systemControllers;   // This is all the system controllers loaded from the database

        bool m_isLoaded;          // This indicates if we have loaded the system controllers before or not. If we
                                  // have never loaded the system controllers then when we are told to refresh we
                                  // shouldn't load them.

    };
}

#endif // !defined(SystemControllerDatabaseAccessor_40D09158_85E4_464f_81D1_E7B9225238D9__INCLUDED_)
