// RASelectedCallAccessFactory.cpp: implementation of the RASelectedCallAccessFactory class.
//
//////////////////////////////////////////////////////////////////////

#if 0
#ifdef __WIN32__
#pragma warning(disable:4786)
#pragma warning(disable:4284)
#endif
#endif

#include <sstream>
#include "core/data_access_interface/radio/src/RASelectedCallAccessFactory.h"
#include "core/data_access_interface/radio/src/RASelectedCall.h"
#include "core/data_access_interface/src/DatabaseFactory.h"
#include "core/data_access_interface/src/SQLCode.h"
#include "core/synchronisation/src/ThreadGuard.h"
#include "core/exceptions/src/DataException.h"
#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/DebugUtil.h"

using TA_Base_Core::DebugUtil;
using TA_Base_Core::DataException;



namespace TA_Base_Core
{
    TA_Base_Core::NonReEntrantThreadLockable RASelectedCallAccessFactory::m_singletonLock;
	RASelectedCallAccessFactory* RASelectedCallAccessFactory::s_instance = NULL;
	

    RASelectedCallAccessFactory& RASelectedCallAccessFactory::getInstance()
    {
        ThreadGuard guard( m_singletonLock );

        if (s_instance == NULL)
        {
            s_instance = new RASelectedCallAccessFactory;
        }
        return *s_instance;
    }


    RASelectedCallAccessFactory::~RASelectedCallAccessFactory()
    {

    }


	RASelectedCallAccessFactory::SelectedCallHistoryList RASelectedCallAccessFactory::getList(const std::string& mft) const
    {
		// Perform SQL here
		std::vector< IRASelectedCall* > records;

        // get a connection to the database
        IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(Radio_Cd, Read);

       /* std::stringstream s;
        s   << "select "
			<< "RASC_ID, "
            << " TETRA_ID, "
			<< " CALL_ID, "
			<< " LOCATION"
            << " from "
            << " RA_SELECTED_CALLS "
            << " where "
			<< "   MFT_NAME = '" << databaseConnection->escapeQueryString(mft) << "' "
			<< " and rownum <= " << RASelectedCall::rowLimit
			<< " order by RASC_ID"
            << std::ends;
        std::string sql(s.str()); */
//		std::string strSql = defPrepareSQLStatement(databaseConnection->GetDbServerType(), RA_SELECTED_CALLS_Oracle_SELECT_35551,
//		std::string strSql  = databaseConnection->prepareSQLStatement(RA_SELECTED_CALLS_SELECT_35551,
		SQLStatement strSql;
		databaseConnection->prepareSQLStatement(strSql, RA_SELECTED_CALLS_SELECT_35551,
			databaseConnection->escapeQueryString(mft), RASelectedCall::rowLimit);
        
        // Set up the columnNames vector to be passed to executeQuery()
        std::string colRASC_ID("RASC_ID");
        std::string colMFT_NAME("MFT_NAME");
		std::string colCALL_ID("CALL_ID");
        std::string colLOCATION("LOCATION");
     	    
        std::vector<std::string> columnNames;
		columnNames.push_back(colRASC_ID);
		columnNames.push_back(colMFT_NAME);
		columnNames.push_back(colCALL_ID);
		columnNames.push_back(colLOCATION);
		
        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it
        IData* data = databaseConnection->executeQuery(strSql,columnNames);
		
        // Loop for each row returned
        do
        {
            for (unsigned long i = 0; i < data->getNumRows(); i++)
            {
                try
                {
					// Create the subsystem
                    IRASelectedCall* record = new RASelectedCall( 
						data->getUnsignedLongData(i,colRASC_ID),
						data->getStringData(i,colMFT_NAME),
						data->getStringData(i,colCALL_ID),
						data->getStringData(i,colLOCATION)
						); 
                    
                    records.push_back( record );
                }
                catch (const TA_Base_Core::DataException&)
                {
                    // Clean up the data pointer
                    delete data;
                    data = NULL;
                    throw;
                }
            }
			delete data;
			data = NULL;
        }
        while ( databaseConnection->moreData(data) );

		return records;
    }


	void RASelectedCallAccessFactory::addTetraid( const std::string& mft, const std::string& tsiNumber,const std::string& id,const std::string& location) const
	{
		
        // get a connection to the database
        IDatabase* databaseConnection = 
			TA_Base_Core::DatabaseFactory::getInstance().getDatabase(Radio_Cd, Write);
		
		{
			/*std::stringstream deletes;
			deletes << "delete from RA_SELECTED_CALLS  where MFT_NAME = "
				    << " '" <<databaseConnection->escapeInsertString(mft) <<"' "
					<< " and TETRA_ID = " << "'"<< databaseConnection->escapeInsertString(tsiNumber)<<"' "
					<<std::ends;
			std::string sqldelete(deletes.str());*/
//			std::string strSql = defPrepareSQLStatement(databaseConnection->GetDbServerType(), RA_SELECTED_CALLS_STD_DELETE_35901,
//			std::string strSql  = databaseConnection->prepareSQLStatement(RA_SELECTED_CALLS_DELETE_35901,
		SQLStatement strSql;
		databaseConnection->prepareSQLStatement(strSql, RA_SELECTED_CALLS_DELETE_35901,
				databaseConnection->escapeInsertString(mft), databaseConnection->escapeInsertString(tsiNumber));
            databaseConnection->executeModification(strSql);
			
			/*std::stringstream s;
			s   << "INSERT INTO RA_SELECTED_CALLS ( "
				<< " MFT_NAME , TETRA_ID , CALL_ID , LOCATION ) VALUES ("			
				<< " '" << databaseConnection->escapeInsertString(mft) << "' "
				<< " , '" << databaseConnection->escapeInsertString(tsiNumber) << "' "
				<< " , '" << databaseConnection->escapeInsertString(id) << "' "
				<< " , '" << databaseConnection->escapeInsertString(location) << "' "
				<< " )" 
				<< std::ends;
			std::string sql(s.str());*/
//			strSql = defPrepareSQLStatement(databaseConnection->GetDbServerType(), RA_SELECTED_CALLS_STD_INSERT_35801,
//			strSql  = databaseConnection->prepareSQLStatement(RA_SELECTED_CALLS_INSERT_35801,

		databaseConnection->prepareSQLStatement(strSql, RA_SELECTED_CALLS_INSERT_35801,
				databaseConnection->escapeInsertString(mft), databaseConnection->escapeInsertString(tsiNumber),
				databaseConnection->escapeInsertString(id), databaseConnection->escapeInsertString(location));
			
			databaseConnection->executeModification(strSql);
		}

			// now delete if there are more than rowLimit records for this profile/location
		{
			/*std::stringstream s;
			s   << "delete from RA_SELECTED_CALLS where RASC_ID in ( "
				<< "   select * from ( "
				<< "      select RASC_ID from RA_SELECTED_CALLS "
				<< "      where MFT_NAME = '" << databaseConnection->escapeInsertString(mft) << "' "
				<< "      order by RASC_ID asc ) "
				<< "   where rownum <= ( select count(*) from RA_SELECTED_CALLS "
				<< "                     where MFT_NAME = '" << databaseConnection->escapeInsertString(mft) << "' "	
				<< "                   ) - " << RASelectedCall::rowLimit
				<< "   ) "
				<< std::ends;
			std::string sql(s.str());*/
//			std::string strSql = defPrepareSQLStatement(databaseConnection->GetDbServerType(), RA_SELECTED_CALLS_Oracle_DELETE_35951,
//			std::string strSql  = databaseConnection->prepareSQLStatement(RA_SELECTED_CALLS_DELETE_35951,
		SQLStatement strSql;
		databaseConnection->prepareSQLStatement(strSql, RA_SELECTED_CALLS_DELETE_35951,
				databaseConnection->escapeInsertString(mft), databaseConnection->escapeInsertString(mft), RASelectedCall::rowLimit);
			
			databaseConnection->executeModification(strSql);
		}
	}
}


 
