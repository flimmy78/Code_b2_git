/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/core/data_access_interface/telephone/telephone_directory_dai/src/TelephoneSubDirectoryAccessFactory.cpp $
  * @author:  Wong Soh Sum
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * TelephoneSubDirectoryAccessFactory is a singleton that is used to retrieve TelephoneSubDirectory objects either from the
  * database or newly created. All TelephoneSubDirectory objects returned will adhear to the ITelephoneSubDirectory interface.
  */

#ifdef __WIN32__
#pragma warning(disable:4786)
#endif

#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/TAAssert.h"

#include "core/data_access_interface/src/DatabaseFactory.h"
#include "core/exceptions/src/DataException.h"

#include "core/data_access_interface/telephone/telephone_directory_dai/src/TelephoneSubDirectoryAccessFactory.h"
#include "core/data_access_interface/telephone/telephone_directory_dai/src/TelephoneSubDirectory.h"
#include "core/data_access_interface/telephone/telephone_directory_dai/src/ConfigTelephoneSubDirectory.h"

using TA_Base_Core::DataException;
using TA_Base_Core::DatabaseException;

namespace TA_IRS_Core
{
    TelephoneSubDirectoryAccessFactory* TelephoneSubDirectoryAccessFactory::m_instance = 0;

    TelephoneSubDirectoryAccessFactory& TelephoneSubDirectoryAccessFactory::getInstance()
    {
        FUNCTION_ENTRY("getInstance");
        
        if( m_instance == 0 )
        {
            m_instance = new TelephoneSubDirectoryAccessFactory();
        }
        
        FUNCTION_EXIT;
        return *m_instance;
    }


    void TelephoneSubDirectoryAccessFactory::removeInstance()
    {
        FUNCTION_ENTRY("removeInstance");
        if ( m_instance != NULL )
	    {
		    delete m_instance;
		    m_instance = NULL;
	    }
        FUNCTION_EXIT;
    }
    
    
    ITelephoneSubDirectory* TelephoneSubDirectoryAccessFactory::getTelephoneSubDirectory(
                                                const unsigned long idKey,
                                                const bool readWrite, 
                                                const TelephoneDirectoryItemStatus stateOfRecords)
    {
        FUNCTION_ENTRY("getTelephoneSubDirectory");

        // create the SQL string to retrieve the name of the TelephoneSubDirectory
        // this is a check to ensure an TelephoneSubDirectory with the specified
        // PKEY actually exists.
        std::ostringstream sql;
        sql << "select " 
            << TelephoneSubDirectoryHelper::SUB_DIR_PRI_KEY << ","
            << TelephoneSubDirectoryHelper::SUB_DIR_NAME    << ","
            << TelephoneSubDirectoryHelper::SUB_DIR_STATUS
            << " from "
            << TelephoneSubDirectoryHelper::SUB_DIR_TABLE
            << " where "
            << TelephoneSubDirectoryHelper::SUB_DIR_PRI_KEY << "=" << idKey
            << " and "
            << TelephoneSubDirectoryHelper::SUB_DIR_STATUS << "=" << stateOfRecords;

        FUNCTION_EXIT;
        return getSubDirectoryWhere(sql.str(),readWrite);
    }

    ITelephoneSubDirectories TelephoneSubDirectoryAccessFactory::getAllTelephoneSubDirectories(
                                                                        const bool readWrite, 
                                                                        const TelephoneDirectoryItemStatus stateOfRecords)
    {
        FUNCTION_ENTRY("getAllTelephoneSubDirectories");

        // create the SQL string to retrieve the data of the TelephoneSubDirectory
        // based upon the key
        std::ostringstream sql;
        sql << "select "
            << TelephoneSubDirectoryHelper::SUB_DIR_PRI_KEY << ","
            << TelephoneSubDirectoryHelper::SUB_DIR_NAME    << ","
            << TelephoneSubDirectoryHelper::SUB_DIR_STATUS
            << " from "
            << TelephoneSubDirectoryHelper::SUB_DIR_TABLE
            << " where "
            << TelephoneSubDirectoryHelper::SUB_DIR_STATUS << "=" << stateOfRecords;

        FUNCTION_EXIT;
        return getSubDirectoriesWhere(sql.str(), readWrite);
    }
    
  
    ITelephoneSubDirectory* TelephoneSubDirectoryAccessFactory::getTelephoneSubDirectoryWhere( const bool readWrite,
                                                        const std::string& dirName,
                                                        const TelephoneDirectoryItemStatus stateOfRecords)
    {
        FUNCTION_ENTRY("getTelephoneSubDirectoryWhere");

        // create the SQL string to retrieve the guis
        std::ostringstream sql;

        sql << "select "
            << TelephoneSubDirectoryHelper::SUB_DIR_PRI_KEY << ","
            << TelephoneSubDirectoryHelper::SUB_DIR_NAME    << ","
            << TelephoneSubDirectoryHelper::SUB_DIR_STATUS
            << " from "
            << TelephoneSubDirectoryHelper::SUB_DIR_TABLE
            << " where "
            << TelephoneSubDirectoryHelper::SUB_DIR_STATUS << "=" << stateOfRecords;

        if (!dirName.empty())
        {
            sql << " and "
                << TelephoneSubDirectoryHelper::SUB_DIR_NAME 
                << "='" 
                << (TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Telephone_Cd, TA_Base_Core::Read)->escapeInsertString(dirName)).c_str()
                << "'";
        }

        FUNCTION_EXIT;
        return getSubDirectoryWhere(sql.str(), readWrite);
    }

    ITelephoneSubDirectories TelephoneSubDirectoryAccessFactory::getAnyStateTelephoneSubDirectoryWhere(  const bool readWrite, const std::string& dirName)
    {
        FUNCTION_ENTRY("getAnyStateTelephoneSubDirectoryWhere");

        // create the SQL string to retrieve the guis
        std::ostringstream sql;

        sql << "select "
            << TelephoneSubDirectoryHelper::SUB_DIR_PRI_KEY << ","
            << TelephoneSubDirectoryHelper::SUB_DIR_NAME    << ","
            << TelephoneSubDirectoryHelper::SUB_DIR_STATUS
            << " from "
            << TelephoneSubDirectoryHelper::SUB_DIR_TABLE
            << " where "
            << "1=1";

        if (!dirName.empty())
        {
            sql << " and "
                << TelephoneSubDirectoryHelper::SUB_DIR_NAME 
                << "='" 
                << (TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Telephone_Cd, TA_Base_Core::Read)->escapeInsertString(dirName)).c_str()
                << "'";
        }

        FUNCTION_EXIT;
        return getSubDirectoriesWhere(sql.str(), readWrite);
    }

    ITelephoneSubDirectories TelephoneSubDirectoryAccessFactory::getNotInactiveTelephoneSubDirectoryWhere( const bool readWrite,
                                                        const std::string& dirName)
    {
        FUNCTION_ENTRY("getNotInactiveTelephoneSubDirectoryWhere");

        // create the SQL string to retrieve the guis
        std::ostringstream sql;

        sql << "select "
            << TelephoneSubDirectoryHelper::SUB_DIR_PRI_KEY << ","
            << TelephoneSubDirectoryHelper::SUB_DIR_NAME    << ","
            << TelephoneSubDirectoryHelper::SUB_DIR_STATUS
            << " from "
            << TelephoneSubDirectoryHelper::SUB_DIR_TABLE
            << " where "
            << TelephoneSubDirectoryHelper::SUB_DIR_STATUS << "!=" << TELDIR_STATUS_INACTIVE;

        if (!dirName.empty())
        {
            sql << " and "
                << TelephoneSubDirectoryHelper::SUB_DIR_NAME 
                << "='" 
                << (TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Telephone_Cd, TA_Base_Core::Read)->escapeInsertString(dirName)).c_str()
                << "'";
        }

        FUNCTION_EXIT;
        return getSubDirectoriesWhere(sql.str(), readWrite);
    }



    IConfigTelephoneSubDirectory* TelephoneSubDirectoryAccessFactory::createTelephoneSubDirectory()
    {            
        FUNCTION_ENTRY("createTelephoneSubDirectory");
        FUNCTION_EXIT;    
        return new ConfigTelephoneSubDirectory();    
    }


    IConfigTelephoneSubDirectory* TelephoneSubDirectoryAccessFactory::copyTelephoneSubDirectory(const IConfigTelephoneSubDirectory* subDirToCopy)
    {
        FUNCTION_ENTRY("copyTelephoneSubDirectory");
        TA_ASSERT(subDirToCopy !=  NULL, "The TelephoneSubDirectory to copy was NULL");
        
        const ConfigTelephoneSubDirectory* cast = dynamic_cast<const ConfigTelephoneSubDirectory*>(subDirToCopy);
        TA_ASSERT(cast != NULL, "TelephoneSubDirectory passed could not be converted into a ConfigTelephoneSubDirectory");

        FUNCTION_EXIT;
        return new ConfigTelephoneSubDirectory(*cast);

    }

    ITelephoneSubDirectory* TelephoneSubDirectoryAccessFactory::getSubDirectoryWhere(const std::string& sql, const bool readWrite)
    {
        FUNCTION_ENTRY("getSubDirectoryWhere");

        // get a connection to the database
        TA_Base_Core::IDatabase* databaseConnection = 
                TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Telephone_Cd, TA_Base_Core::Read);
        if (databaseConnection == NULL)
        {
            TA_THROW(DatabaseException("Cannot connect to database"));
        }

        // Set up the columnNames vector to be passed to executeQuery()
        std::vector<std::string> columnNames;
        columnNames.push_back(TelephoneSubDirectoryHelper::SUB_DIR_PRI_KEY);
        columnNames.push_back(TelephoneSubDirectoryHelper::SUB_DIR_NAME);
		columnNames.push_back(TelephoneSubDirectoryHelper::SUB_DIR_STATUS);


        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it
        TA_Base_Core::IData* data = databaseConnection->executeQuery(sql.c_str(), columnNames);
        TA_ASSERT(data != NULL, "NULL item returned after executeQuery");

        if (0 == data->getNumRows()) // No entry found with the specified pkey
        {
            // clean up the pointer
            delete data;
            data = NULL;

            FUNCTION_EXIT;    
            TA_THROW(DataException("No directory can be found fulfilling the SQL statement." , DataException::NO_VALUE,""));
        }
        else if (1 < data->getNumRows()) // More than one entry found for the pkey
        {
            // clean up the pointer
            delete data;
            data = NULL;

            FUNCTION_EXIT;    
            TA_THROW(DataException("More than one directory are found fulfilling the SQL statement.", DataException::NOT_UNIQUE,""));
        }

        // Create the TelephoneSubDirectory object to represent this object. 
        ITelephoneSubDirectory* theTelephoneSubDirectory;
        
        // decide which TelephoneSubDirectory object to return
        if (readWrite) // need a config TelephoneSubDirectory
        {
            theTelephoneSubDirectory = new ConfigTelephoneSubDirectory(0, *data);
        }
        else // need a standard TelephoneSubDirectory
        {
            theTelephoneSubDirectory = new TelephoneSubDirectory(0, *data);
        }

        // clean up the pointer
        delete data;
        data = NULL;
        
        // Return the TelephoneSubDirectory pointer. The class that recieves this pointer is responsible
        // for deleting it.
        FUNCTION_EXIT;
        return theTelephoneSubDirectory;
    }

    ITelephoneSubDirectories TelephoneSubDirectoryAccessFactory::getSubDirectoriesWhere(const std::string& sql, const bool readWrite)
    {
        FUNCTION_ENTRY("getSubDirectoriesWhere");

        // get a connection to the database
        TA_Base_Core::IDatabase* databaseConnection = 
                TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Telephone_Cd, TA_Base_Core::Read);
        if (databaseConnection == NULL)
        {
            TA_THROW(DatabaseException("Cannot connect to database"));
        }

        // Set up the columnNames vector to be passed to executeQuery()
        std::vector<std::string> columnNames;
        columnNames.push_back(TelephoneSubDirectoryHelper::SUB_DIR_PRI_KEY);
        columnNames.push_back(TelephoneSubDirectoryHelper::SUB_DIR_NAME);
		columnNames.push_back(TelephoneSubDirectoryHelper::SUB_DIR_STATUS);


        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it
        TA_Base_Core::IData* data = databaseConnection->executeQuery(sql.c_str(), columnNames);
        TA_ASSERT(data != NULL, "NULL item returned after executeQuery");

        // create the vector of pointers to IEntityData
        ITelephoneSubDirectories subDirList;
        do
        {
            for (unsigned long i = 0; i < data->getNumRows() ; ++i )
            {   
                if (readWrite)
                {
                    subDirList.push_back(new ConfigTelephoneSubDirectory(i, *data));
                }
                else
                {
                    subDirList.push_back(new TelephoneSubDirectory(i, *data));
                }
            }

            delete data;
            data = NULL;
        }
        while( databaseConnection->moreData(data) );

        FUNCTION_EXIT;
        return subDirList;
    }

	//libo++
	//std::map<long, std::string> TelephoneSubDirectoryAccessFactory::getAllAssociatedSubdirectoryMap(const TelephoneDirectoryItemStatus stateOfRecords)
	//std::map<long, std::string> TelephoneSubDirectoryAccessFactory::getAllAssociatedSubdirectoryMap()
	void TelephoneSubDirectoryAccessFactory::getAllAssociatedSubdirectoryMap()
	{
		const TelephoneDirectoryItemStatus stateOfRecords =TELDIR_STATUS_NEW;
		FUNCTION_ENTRY("getAssociatedSubdirectoryMap");
		std::map<long, std::string> mapSubData;
		mapSubData.clear();
		std::ostringstream sql;
        sql << "select "
            << TelephoneSubDirectoryHelper::SUB_DIR_PRI_KEY << ","
            << TelephoneSubDirectoryHelper::SUB_DIR_NAME   
            << " from "
            << TelephoneSubDirectoryHelper::SUB_DIR_TABLE
            << " where "
            << TelephoneSubDirectoryHelper::SUB_DIR_STATUS << "=" << stateOfRecords;

        // get a connection to the database
        TA_Base_Core::IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Telephone_Cd, TA_Base_Core::Read);
        if (databaseConnection == NULL)
        {
            TA_THROW(DatabaseException("Cannot connect to database"));
        }
        // Set up the columnNames vector to be passed to executeQuery()
        std::vector<std::string> columnNames;
        columnNames.push_back(TelephoneSubDirectoryHelper::SUB_DIR_PRI_KEY);
        columnNames.push_back(TelephoneSubDirectoryHelper::SUB_DIR_NAME);
        TA_Base_Core::IData* data = databaseConnection->executeQuery(sql.str(), columnNames);
        TA_ASSERT(data != NULL, "NULL item returned after executeQuery");
		std::string sName;
		long nKey;
		 do
        {
            for (unsigned long i = 0; i < data->getNumRows() ; ++i )
            {   
				nKey = (long) data->getUnsignedLongData(i,TelephoneSubDirectoryHelper::SUB_DIR_PRI_KEY);
				sName = data->getStringData(i,TelephoneSubDirectoryHelper::SUB_DIR_NAME);
				mapSubData[nKey] = sName;
            }
            delete data;
            data = NULL;
        }
        while( databaseConnection->moreData(data) );

        // Return the TelephoneSubDirectory pointer. The class that recieves this pointer is responsible
        // for deleting it.
        FUNCTION_EXIT;
        //return mapSubData; //mapSubData.size() >0 ? true : false;
	}
	//++libo
    
} // closes TA_Core
