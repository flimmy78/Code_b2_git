/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/4669_T01271350/TA_BASE/transactive/core/data_access_interface/archive_manager_dai/src/ArchiveTableAccessFactory.cpp $
  * @author Katherine Thomson
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * ArchiveTableAccessFactory is a singleton that is used to retrieve objects either from the
  * database or newly created. All objects returned will adhere to the IArchiveTable interface.
  */

#ifdef _MSC_VER
#pragma warning( disable : 4786 )
#endif // _MSC_VER

#include <sstream>

#include "core/data_access_interface/archive_manager_dai/src/ArchiveTableAccessFactory.h"
#include "core/data_access_interface/archive_manager_dai/src/ArchiveTable.h"
#include "core/data_access_interface/archive_manager_dai/src/ConfigArchiveTable.h"
#include "core/data_access_interface/archive_manager_dai/src/ArchiveTableTable.h"
#include "core/data_access_interface/src/DatabaseFactory.h"
#include "core/data_access_interface/src/IDatabase.h"
#include "core/exceptions/src/ArchiveException.h"
#include "core/exceptions/src/DataException.h"
#include "core/exceptions/src/DbConnectionFailed.h"
#include "core/utilities/src/DebugUtil.h"

namespace TA_Base_Core
{
	// Initialise statics
		
    ReEntrantThreadLockable ArchiveTableAccessFactory::m_singletonLock;
	ArchiveTableAccessFactory* ArchiveTableAccessFactory::m_theClassInstance = 0;


    //
    // getInstance
    //
	ArchiveTableAccessFactory& ArchiveTableAccessFactory::getInstance()
	{
	    TA_Base_Core::ThreadGuard guard( m_singletonLock );

		// If guard acquired then make sure the singleton is still 0.

		if ( m_theClassInstance == 0 )
		{
			// Create the one & only object
			
            m_theClassInstance = new ArchiveTableAccessFactory();
		}
		
		return *m_theClassInstance;
	}

    
    //
    // getArchiveTable
    //
    IArchiveTable* ArchiveTableAccessFactory::getArchiveTable( 
        unsigned long archiveTableKey, bool isReadWrite )
    {
        // Get a connection to the database
        
        IDatabase* databaseConnection = DatabaseFactory::getInstance().getDatabase(Archive_d, Write);
        if( 0 == databaseConnection )
        {
            std::stringstream error;
            error << "Failed to get a connection to the database.";
            TA_THROW( DbConnectionFailed(error.str().c_str()) );
        }

        // Check that this ArchiveTable exists in the table.

        std::stringstream selectSql;
        selectSql << "select " << TA_ArchiveManagerDAI::ARCHIVE_TABLE_KEY_COLUMN;
        selectSql << " from " << TA_ArchiveManagerDAI::ARCHIVE_TABLE_TABLE_NAME;
        selectSql << " where " << TA_ArchiveManagerDAI::ARCHIVE_TABLE_KEY_COLUMN;
        selectSql << "=" << archiveTableKey;

        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it,
        // so make it a std::auto_ptr so it is automatically cleaned up.

        std::vector< std::string > columnNames;
        columnNames.push_back( TA_ArchiveManagerDAI::ARCHIVE_TABLE_KEY_COLUMN );
        
        std::auto_ptr< IData > data( databaseConnection->executeQuery( selectSql.str(), columnNames ) );
        if ( 0 == data.get() )
        {
            std::stringstream error;
            error << "Failed to load the data for the ArchiveTable with the key " << archiveTableKey;
            error << " from the database table ";
            error << TA_ArchiveManagerDAI::ARCHIVE_TABLE_TABLE_NAME << ".";
            TA_THROW( DataException( error.str().c_str(), DataException::NO_VALUE, "" ));
        }

        if ( 0 == data->getNumRows() ) // No entry found with the specified pkey
        {
            std::stringstream error;
            error << "No data found for ArchiveTable with the key " << archiveTableKey;			
            TA_THROW( DataException( error.str().c_str(), DataException::NO_VALUE, 
                TA_ArchiveManagerDAI::ARCHIVE_TABLE_KEY_COLUMN ));
        }

        // Create the ArchiveTable object to represent this object. Initially only populate it
        // with ArchiveTable key. We will populate the rest of the data on demand.

        IArchiveTable* theArchiveTable;
        
        // Decide which type of ArchiveTable object to return.
        // The new's may throw an exception, but it is okay because everything will
        // be cleaned up.

        if ( isReadWrite ) // Need a config object.
        {
            theArchiveTable = new ConfigArchiveTable( archiveTableKey );
        }
        else // Need a standard object.
        {
            theArchiveTable = new ArchiveTable( archiveTableKey );
        }

        // Return the appropriate object. 
        // The class that recieves this pointer is responsible for deleting it.

        return theArchiveTable;
    }


    //
    // getAllArchiveTables
    //
    ArchiveTableAccessFactory::IArchiveTableVector ArchiveTableAccessFactory::getAllArchiveTables( bool isReadWrite )
    {
        // Get a connection to the database.

        IDatabase* databaseConnection = DatabaseFactory::getInstance().getDatabase(Archive_d, Write);

        // Get all the ArchiveTable keys that exist in the table.

        std::stringstream selectSql;
        selectSql << "select " << TA_ArchiveManagerDAI::ARCHIVE_TABLE_KEY_COLUMN;
        selectSql << " from " << TA_ArchiveManagerDAI::ARCHIVE_TABLE_TABLE_NAME;

        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it,
        // so make it a std::auto_ptr so it is automatically cleaned up.

        std::vector< std::string > columnNames;
        columnNames.push_back( TA_ArchiveManagerDAI::ARCHIVE_TABLE_KEY_COLUMN );
        
        std::auto_ptr< IData > data( databaseConnection->executeQuery( selectSql.str(), columnNames ) );
        
        if ( 0 == data->getNumRows() ) // No entry found with the specified pkey
        {
            std::stringstream error;
            error << "There are no ArchiveTables configured in the database table ";
            error << TA_ArchiveManagerDAI::ARCHIVE_TABLE_TABLE_NAME;
            TA_THROW( DataException( error.str().c_str(), DataException::NO_VALUE, "" ));
        }

        // Create the vector of pointers to IArchiveTables.
            
        IArchiveTableVector archiveTables;
        try
        {
            if ( isReadWrite )  // Need a config objects.
            {
                for ( unsigned long i = 0; i < data->getNumRows(); ++i )
                {                
                    archiveTables.push_back( new ConfigArchiveTable( 
                        data->getUnsignedLongData( i, TA_ArchiveManagerDAI::ARCHIVE_TABLE_KEY_COLUMN ) ) );
                }
            }
            else // Need standard objects.
            {
                for ( unsigned long i = 0; i < data->getNumRows(); ++i )
                {                
                    archiveTables.push_back( new ArchiveTable( 
                        data->getUnsignedLongData( i, TA_Base_Core::TA_ArchiveManagerDAI::ARCHIVE_TABLE_KEY_COLUMN ) ) );
                }
            }
        }
        catch( ArchiveException& )
        {
            // Don't log here, because we're just cleaning up...

            for ( std::vector< IArchiveTable* >::iterator it = archiveTables.begin(); it != archiveTables.end(); ++it )
            {
                delete *it;
                *it = 0;
            }
            throw;
        }

        return archiveTables;
    }

    
    //
    // createArchiveTable
    //
    IConfigArchiveTable* ArchiveTableAccessFactory::createArchiveTable()
    {            
        return new ConfigArchiveTable();    
    }

} // closes TA_Base_Core


