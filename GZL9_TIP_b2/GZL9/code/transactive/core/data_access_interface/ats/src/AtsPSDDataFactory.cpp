/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/GZL6_TIP/3002/transactive/core/data_access_interface/ats/src/AtsPSDDataFactory.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2012/06/12 13:35:44 $
  * Last modified by:  $Author: builder $
  *
  */
#if defined(_MSC_VER)
	#pragma warning(disable:4786)	// disable the "trucated to 255 character" warning
	#pragma warning(disable:4290)	// C++ Exception Specification ignored
#endif // defined _MSC_VER

#include <sstream>

#include "core/data_access_interface/ats/src/AtsPSDDataFactory.h"
#include "core/data_access_interface/ats/src/AtsPSDData.h"
#include "core/data_access_interface/ats/src/ConfigAtsPSDData.h"
#include "core/data_access_interface/src/DatabaseFactory.h"
#include "core/data_access_interface/src/SQLCode.h"
#include "core/exceptions/src/DataException.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/TAAssert.h"


namespace TA_IRS_Core
{	
	static const std::string KEY_COL					= "ATPEMA_ID";
    static const std::string STATIONID_COL				= "STATION_ID";
	static const std::string PLATFORMKEY_COL			= "PLATFORM_KEY";
	static const std::string PLATFORMID_COL				= "PLATFORM_ID";
    static const std::string PLATFORMNAME_COL			= "PLATFORM_NAME";
    static const std::string TIS_PLATFORMID_COL         = "TIS_PLATFORM_ID";
	static const std::string MSSZONE_COL				= "MSS_ZONE";
	static const std::string PSDNUMBER_COL				= "PSD_NUMBER";
	static const std::string DATAPOINTENTITYKEY_COL		= "DATA_POINT_ENTITY_KEY";
	static const std::string DATAPOINTTYPE_COL			= "DATA_POINT_TYPE";
	static const std::string DATAPOINTNAMEOFTYPE_COL	= "DATA_POINT_NAMEOF_TYPE";

	AtsPSDDataFactory& AtsPSDDataFactory::getInstance()
	{
		static AtsPSDDataFactory factory;

        return factory;
	}

	std::vector<IAtsPSDData*> AtsPSDDataFactory::getAllPSDDataInMSSZone(const std::string &aMSSZone, const bool readWrite)
	{
		// initialise our return variable
		std::vector<IAtsPSDData *> PSDDataVector;

		// get a connection to the database
        TA_Base_Core::IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Ats_Cd, TA_Base_Core::Read);

		// create an SQL statement to retrieve all records from the view
		/*std::ostringstream sql;
		sql << "select " << KEY_COL << ", " << STATIONID_COL << ", " << PLATFORMKEY_COL << ", " << PLATFORMID_COL << ", ";
		sql << PLATFORMNAME_COL << ", " << TIS_PLATFORMID_COL << ", ";
		sql << MSSZONE_COL << ", " << PSDNUMBER_COL << ", " << DATAPOINTENTITYKEY_COL << ", ";
		sql << DATAPOINTTYPE_COL << ", " << DATAPOINTNAMEOFTYPE_COL;
		sql << " from AT_PSD_ENTITY_MAP_V where " << MSSZONE_COL << " = upper('" << aMSSZone << "')";*/
//		std::string strSql = defPrepareSQLStatement(databaseConnection->GetDbServerType(), AT_PSD_ENTITY_MAP_STD_SELECT_49003, aMSSZone);
//		std::string strSql  = databaseConnection->prepareSQLStatement(AT_PSD_ENTITY_MAP_SELECT_49003, aMSSZone);
		TA_Base_Core::SQLStatement strSql;
		databaseConnection->prepareSQLStatement(strSql, AT_PSD_ENTITY_MAP_SELECT_49003, aMSSZone);

        // Set up the columnNames vector to be passed to executeQuery()
        std::vector<std::string> columnNames;
        columnNames.push_back(KEY_COL);
        columnNames.push_back(STATIONID_COL);
        columnNames.push_back(PLATFORMKEY_COL);
        columnNames.push_back(PLATFORMID_COL);
        columnNames.push_back(PLATFORMNAME_COL);
        columnNames.push_back(TIS_PLATFORMID_COL);
		columnNames.push_back(MSSZONE_COL);
        columnNames.push_back(PSDNUMBER_COL);
        columnNames.push_back(DATAPOINTENTITYKEY_COL);
        columnNames.push_back(DATAPOINTTYPE_COL);
		columnNames.push_back(DATAPOINTNAMEOFTYPE_COL);

        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it
        TA_Base_Core::IData* data = databaseConnection->executeQuery(strSql,columnNames);
                
        using TA_Base_Core::DataException;

        if (0 == data->getNumRows()) // No records are found
        {
            // clean up the pointer
            delete data;
            data = NULL;
            
			// will be empty
			return PSDDataVector;
        }

        // retrieve information in the database
		do
        {
            for (unsigned long i = 0; i < data->getNumRows(); i++)
            {
                // The getUnsignedLongData() call can throw an exception. 
                try
                {
                    // Create a shiny new AtsPSDData interface which will have all the information pre-loaded!
                    IAtsPSDData* atsPSDData = NULL;

                    if (readWrite)
					{
						atsPSDData = new ConfigAtsPSDData(i, *data);
					}
					else
					{
						atsPSDData = new AtsPSDData(i, *data);
					}               				 												

					// add this object to the vector
                    PSDDataVector.push_back(atsPSDData);
                }
                catch (TA_Base_Core::DataException&)
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
        while (databaseConnection->moreData(data));    
        
        // Now that we're finished with the IData object, we need to delete it.
        delete data;
        data = NULL;

        return PSDDataVector;
	}


	std::vector<IAtsPSDData*> AtsPSDDataFactory::getAllPSDDataInMSSZoneOfGivenDataPointNameOfType(const std::string &aMSSZone, const std::string &aDataPointNameOfType, const bool readWrite)
	{
		// initialise our return variable
		std::vector<IAtsPSDData *> PSDDataVector;

		// get a connection to the database
        TA_Base_Core::IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Ats_Cd, TA_Base_Core::Read);

		// create an SQL statement to retrieve all records from the view
		/*std::ostringstream sql;
		sql << "select " << KEY_COL << ", " << STATIONID_COL << ", " << PLATFORMKEY_COL << ", " << PLATFORMID_COL << ", ";
		sql << PLATFORMNAME_COL << ", " << TIS_PLATFORMID_COL << ", ";
		sql << MSSZONE_COL << ", " << PSDNUMBER_COL << ", " << DATAPOINTENTITYKEY_COL << ", ";
		sql << DATAPOINTTYPE_COL << ", " << DATAPOINTNAMEOFTYPE_COL;
		sql << " from AT_PSD_ENTITY_MAP_V where " << MSSZONE_COL << " = upper('" << aMSSZone << "') ";
		sql << "and " << DATAPOINTNAMEOFTYPE_COL << " = '" << aDataPointNameOfType << "'";*/
//		std::string strSql = defPrepareSQLStatement(databaseConnection->GetDbServerType(), AT_PSD_ENTITY_MAP_STD_SELECT_49004, aMSSZone,
//		std::string strSql  = databaseConnection->prepareSQLStatement(AT_PSD_ENTITY_MAP_SELECT_49004, aMSSZone,
		TA_Base_Core::SQLStatement strSql;
		databaseConnection->prepareSQLStatement(strSql, AT_PSD_ENTITY_MAP_SELECT_49004, aMSSZone,
			aDataPointNameOfType);

        // Set up the columnNames vector to be passed to executeQuery()
        std::vector<std::string> columnNames;
        columnNames.push_back(KEY_COL);
        columnNames.push_back(STATIONID_COL);
        columnNames.push_back(PLATFORMKEY_COL);
        columnNames.push_back(PLATFORMID_COL);
        columnNames.push_back(PLATFORMNAME_COL);
        columnNames.push_back(TIS_PLATFORMID_COL);
		columnNames.push_back(MSSZONE_COL);
        columnNames.push_back(PSDNUMBER_COL);
        columnNames.push_back(DATAPOINTENTITYKEY_COL);
        columnNames.push_back(DATAPOINTTYPE_COL);
		columnNames.push_back(DATAPOINTNAMEOFTYPE_COL);

        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it
        TA_Base_Core::IData* data = databaseConnection->executeQuery(strSql,columnNames);
                
        using TA_Base_Core::DataException;

        if (0 == data->getNumRows()) // No records are found
        {
            // clean up the pointer
            delete data;
            data = NULL;
            
			// will be empty
			return PSDDataVector;
        }

        // retrieve information in the database
		do
        {
            for (unsigned long i = 0; i < data->getNumRows(); i++)
            {
                // The getUnsignedLongData() call can throw an exception. 
                try
                {
                    // Create a shiny new AtsPSDData interface which will have all the information pre-loaded!
                    IAtsPSDData* atsPSDData = NULL;

                    if (readWrite)
					{
						atsPSDData = new ConfigAtsPSDData(i, *data);
					}
					else
					{
						atsPSDData = new AtsPSDData(i, *data);
					}                 				 												

					// add this object to the vector
                    PSDDataVector.push_back(atsPSDData);
                }
                catch (TA_Base_Core::DataException&)
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
        while (databaseConnection->moreData(data));    
        
        // Now that we're finished with the IData object, we need to delete it.
        delete data;
        data = NULL;

        return PSDDataVector;
	}


	std::vector<IAtsPSDData*> AtsPSDDataFactory::getAllPSDDataInMSSZoneOfGivenDataPointType(const std::string &aMSSZone, const std::string &aDataPointType, const bool readWrite)
	{
		// initialise our return variable
		std::vector<IAtsPSDData *> PSDDataVector;

		// get a connection to the database
        TA_Base_Core::IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Ats_Cd, TA_Base_Core::Read);

		// create an SQL statement to retrieve all records from the view
		/*std::ostringstream sql;
		sql << "select " << KEY_COL << ", " << STATIONID_COL << ", " << PLATFORMKEY_COL << ", " << PLATFORMID_COL << ", ";
		sql << PLATFORMNAME_COL << ", " << TIS_PLATFORMID_COL << ", ";
		sql << MSSZONE_COL << ", " << PSDNUMBER_COL << ", " << DATAPOINTENTITYKEY_COL << ", ";
		sql << DATAPOINTTYPE_COL << ", " << DATAPOINTNAMEOFTYPE_COL;
		sql << " from AT_PSD_ENTITY_MAP_V where " << MSSZONE_COL << " = upper('" << aMSSZone << "') ";
		sql << "and " << DATAPOINTTYPE_COL << " = '" << aDataPointType << "'";*/
//		std::string strSql = defPrepareSQLStatement(databaseConnection->GetDbServerType(), AT_PSD_ENTITY_MAP_STD_SELECT_49005, aMSSZone, aDataPointType);
//		std::string strSql  = databaseConnection->prepareSQLStatement(AT_PSD_ENTITY_MAP_SELECT_49005, aMSSZone, aDataPointType);
		TA_Base_Core::SQLStatement strSql;
		databaseConnection->prepareSQLStatement(strSql, AT_PSD_ENTITY_MAP_SELECT_49005, aMSSZone, aDataPointType);

        // Set up the columnNames vector to be passed to executeQuery()
        std::vector<std::string> columnNames;
        columnNames.push_back(KEY_COL);
        columnNames.push_back(STATIONID_COL);
        columnNames.push_back(PLATFORMKEY_COL);
        columnNames.push_back(PLATFORMID_COL);
        columnNames.push_back(PLATFORMNAME_COL);
        columnNames.push_back(TIS_PLATFORMID_COL);
		columnNames.push_back(MSSZONE_COL);
        columnNames.push_back(PSDNUMBER_COL);
        columnNames.push_back(DATAPOINTENTITYKEY_COL);
        columnNames.push_back(DATAPOINTTYPE_COL);
		columnNames.push_back(DATAPOINTNAMEOFTYPE_COL);

        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it
        TA_Base_Core::IData* data = databaseConnection->executeQuery(strSql,columnNames);
                
        using TA_Base_Core::DataException;

        if (0 == data->getNumRows()) // No records are found
        {
            // clean up the pointer
            delete data;
            data = NULL;
            
			// will be empty
			return PSDDataVector;
        }

        // retrieve information in the database
		do
        {
            for (unsigned long i = 0; i < data->getNumRows(); i++)
            {
                // The getUnsignedLongData() call can throw an exception. 
                try
                {
                    // Create a shiny new AtsPSDData interface which will have all the information pre-loaded!
                    IAtsPSDData* atsPSDData = NULL;

                    if (readWrite)
					{
						atsPSDData = new ConfigAtsPSDData(i, *data);
					}
					else
					{
						atsPSDData = new AtsPSDData(i, *data);
					}                 				 												

					// add this object to the vector
                    PSDDataVector.push_back(atsPSDData);
                }
                catch (TA_Base_Core::DataException&)
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
        while (databaseConnection->moreData(data));    
        
        // Now that we're finished with the IData object, we need to delete it.
        delete data;
        data = NULL;

        return PSDDataVector;
	}


	std::vector<IAtsPSDData*> AtsPSDDataFactory::getAllPSDDataOfGivenDataPointType(const std::string &aDataPointType, const bool readWrite)
	{
		// initialise our return variable
		std::vector<IAtsPSDData *> PSDDataVector;

		// get a connection to the database
        TA_Base_Core::IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Ats_Cd, TA_Base_Core::Read);

		// create an SQL statement to retrieve all records from the view
		/*std::ostringstream sql;
		sql << "select " << KEY_COL << ", " << STATIONID_COL << ", " << PLATFORMKEY_COL << ", " << PLATFORMID_COL << ", ";
		sql << PLATFORMNAME_COL << ", " << TIS_PLATFORMID_COL << ", ";
		sql << MSSZONE_COL << ", " << PSDNUMBER_COL << ", " << DATAPOINTENTITYKEY_COL << ", ";
		sql << DATAPOINTTYPE_COL << ", " << DATAPOINTNAMEOFTYPE_COL;
		sql << " from AT_PSD_ENTITY_MAP_V where " << DATAPOINTTYPE_COL << " = '" << aDataPointType << "'";*/
//		std::string strSql = defPrepareSQLStatement(databaseConnection->GetDbServerType(), AT_PSD_ENTITY_MAP_STD_SELECT_49006, aDataPointType);
//		std::string strSql  = databaseConnection->prepareSQLStatement(AT_PSD_ENTITY_MAP_SELECT_49006, aDataPointType);
		TA_Base_Core::SQLStatement strSql;
		databaseConnection->prepareSQLStatement(strSql, AT_PSD_ENTITY_MAP_SELECT_49006, aDataPointType);

        // Set up the columnNames vector to be passed to executeQuery()
        std::vector<std::string> columnNames;
        columnNames.push_back(KEY_COL);
        columnNames.push_back(STATIONID_COL);
        columnNames.push_back(PLATFORMKEY_COL);
        columnNames.push_back(PLATFORMID_COL);
        columnNames.push_back(PLATFORMNAME_COL);
        columnNames.push_back(TIS_PLATFORMID_COL);
		columnNames.push_back(MSSZONE_COL);
        columnNames.push_back(PSDNUMBER_COL);
        columnNames.push_back(DATAPOINTENTITYKEY_COL);
        columnNames.push_back(DATAPOINTTYPE_COL);
		columnNames.push_back(DATAPOINTNAMEOFTYPE_COL);

        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it
        TA_Base_Core::IData* data = databaseConnection->executeQuery(strSql,columnNames);
                
        using TA_Base_Core::DataException;

        if (0 == data->getNumRows()) // No records are found
        {
            // clean up the pointer
            delete data;
            data = NULL;
            
			// will be empty
			return PSDDataVector;
        }

        // retrieve information in the database
		do
        {
            for (unsigned long i = 0; i < data->getNumRows(); i++)
            {
                // The getUnsignedLongData() call can throw an exception. 
                try
                {
                    // Create a shiny new AtsPSDData interface which will have all the information pre-loaded!
                    IAtsPSDData* atsPSDData = NULL;

                    if (readWrite)
					{
						atsPSDData = new ConfigAtsPSDData(i, *data);
					}
					else
					{
						atsPSDData = new AtsPSDData(i, *data);
					}               				 												

					// add this object to the vector
                    PSDDataVector.push_back(atsPSDData);
                }
                catch (TA_Base_Core::DataException&)
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
        while (databaseConnection->moreData(data));    
        
        // Now that we're finished with the IData object, we need to delete it.
        delete data;
        data = NULL;

        return PSDDataVector;
	}

	std::vector<IAtsPSDData*> AtsPSDDataFactory::getAllPSDDataOfGivenDataPointNameOfType(const std::string &aDataPointNameOfType, const bool readWrite)
	{
		// initialise our return variable
		std::vector<IAtsPSDData *> PSDDataVector;

		// get a connection to the database
        TA_Base_Core::IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Ats_Cd, TA_Base_Core::Read);

		// create an SQL statement to retrieve all records from the view
	/*	std::ostringstream sql;
		sql << "select " << KEY_COL << ", " << STATIONID_COL << ", " << PLATFORMKEY_COL << ", " << PLATFORMID_COL << ", ";
		sql << PLATFORMNAME_COL << ", " << TIS_PLATFORMID_COL << ", ";
		sql << MSSZONE_COL << ", " << PSDNUMBER_COL << ", " << DATAPOINTENTITYKEY_COL << ", ";
		sql << DATAPOINTTYPE_COL << ", " << DATAPOINTNAMEOFTYPE_COL;
		sql << " from AT_PSD_ENTITY_MAP_V where " << DATAPOINTNAMEOFTYPE_COL << " = '" << aDataPointNameOfType << "'";*/
//		std::string strSql = defPrepareSQLStatement(databaseConnection->GetDbServerType(),AT_PSD_ENTITY_MAP_STD_SELECT_49007, aDataPointNameOfType);
//		std::string strSql  = databaseConnection->prepareSQLStatement(AT_PSD_ENTITY_MAP_SELECT_49007, aDataPointNameOfType);
		TA_Base_Core::SQLStatement strSql;
		databaseConnection->prepareSQLStatement(strSql, AT_PSD_ENTITY_MAP_SELECT_49007, aDataPointNameOfType);

        // Set up the columnNames vector to be passed to executeQuery()
        std::vector<std::string> columnNames;
        columnNames.push_back(KEY_COL);
        columnNames.push_back(STATIONID_COL);
        columnNames.push_back(PLATFORMKEY_COL);
        columnNames.push_back(PLATFORMID_COL);
        columnNames.push_back(PLATFORMNAME_COL);
        columnNames.push_back(TIS_PLATFORMID_COL);
		columnNames.push_back(MSSZONE_COL);
        columnNames.push_back(PSDNUMBER_COL);
        columnNames.push_back(DATAPOINTENTITYKEY_COL);
        columnNames.push_back(DATAPOINTTYPE_COL);
		columnNames.push_back(DATAPOINTNAMEOFTYPE_COL);

        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it
        TA_Base_Core::IData* data = databaseConnection->executeQuery(strSql,columnNames);
                
        using TA_Base_Core::DataException;

        if (0 == data->getNumRows()) // No records are found
        {
            // clean up the pointer
            delete data;
            data = NULL;
            
			// will be empty
			return PSDDataVector;
        }

        // retrieve information in the database
		do
        {
            for (unsigned long i = 0; i < data->getNumRows(); i++)
            {
                // The getUnsignedLongData() call can throw an exception. 
                try
                {
                    // Create a shiny new AtsPSDData interface which will have all the information pre-loaded!
                    IAtsPSDData* atsPSDData = NULL;

					if (readWrite)
					{
						atsPSDData = new ConfigAtsPSDData(i, *data);
					}
					else
					{
						atsPSDData = new AtsPSDData(i, *data);
					}
                	
					// add this object to the vector
                    PSDDataVector.push_back(atsPSDData);
                }
                catch (TA_Base_Core::DataException&)
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
        while (databaseConnection->moreData(data));    
        
        // Now that we're finished with the IData object, we need to delete it.
        delete data;
        data = NULL;

        return PSDDataVector;
	}

	std::vector<IAtsPSDData*> AtsPSDDataFactory::getAllPSDDataAtGivenStationOfGivenDataPointType(unsigned long aStationId, const std::string &aDataPointType, const bool readWrite)
	{
		// initialise our return variable
		std::vector<IAtsPSDData *> PSDDataVector;

		// get a connection to the database
        TA_Base_Core::IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Ats_Cd, TA_Base_Core::Read);

		// create an SQL statement to retrieve all records from the view
		/*std::ostringstream sql;
		sql << "select " << KEY_COL << ", " << STATIONID_COL << ", " << PLATFORMKEY_COL << ", " << PLATFORMID_COL << ", ";
		sql << PLATFORMNAME_COL << ", " << TIS_PLATFORMID_COL << ", ";
		sql << MSSZONE_COL << ", " << PSDNUMBER_COL << ", " << DATAPOINTENTITYKEY_COL << ", ";
		sql << DATAPOINTTYPE_COL << ", " << DATAPOINTNAMEOFTYPE_COL;
		sql << " from AT_PSD_ENTITY_MAP_V where " << DATAPOINTTYPE_COL << " = '" << aDataPointType << "' ";
		sql << "and " << STATIONID_COL << " = " << aStationId;*/
//		std::string strSql = defPrepareSQLStatement(databaseConnection->GetDbServerType(), AT_PSD_ENTITY_MAP_STD_SELECT_49008, aDataPointType, aStationId);
//		std::string strSql  = databaseConnection->prepareSQLStatement(AT_PSD_ENTITY_MAP_SELECT_49008, aDataPointType, aStationId);
		TA_Base_Core::SQLStatement strSql;
		databaseConnection->prepareSQLStatement(strSql, AT_PSD_ENTITY_MAP_SELECT_49008, aDataPointType, aStationId);

        // Set up the columnNames vector to be passed to executeQuery()
        std::vector<std::string> columnNames;
        columnNames.push_back(KEY_COL);
        columnNames.push_back(STATIONID_COL);
        columnNames.push_back(PLATFORMKEY_COL);
        columnNames.push_back(PLATFORMID_COL);
        columnNames.push_back(PLATFORMNAME_COL);
        columnNames.push_back(TIS_PLATFORMID_COL);
		columnNames.push_back(MSSZONE_COL);
        columnNames.push_back(PSDNUMBER_COL);
        columnNames.push_back(DATAPOINTENTITYKEY_COL);
        columnNames.push_back(DATAPOINTTYPE_COL);
		columnNames.push_back(DATAPOINTNAMEOFTYPE_COL);

        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it
        TA_Base_Core::IData* data = databaseConnection->executeQuery(strSql,columnNames);
                
        using TA_Base_Core::DataException;

        if (0 == data->getNumRows()) // No records are found
        {
            // clean up the pointer
            delete data;
            data = NULL;
            
			// will be empty
			return PSDDataVector;
        }

        // retrieve information in the database
		do
        {
            for (unsigned long i = 0; i < data->getNumRows(); i++)
            {
                // The getUnsignedLongData() call can throw an exception. 
                try
                {
                    // Create a shiny new AtsPSDData interface which will have all the information pre-loaded!
                    IAtsPSDData* atsPSDData = NULL;

                    if (readWrite)
					{
						atsPSDData = new ConfigAtsPSDData(i, *data);
					}
					else
					{
						atsPSDData = new AtsPSDData(i, *data);
					}                				 												

					// add this object to the vector
                    PSDDataVector.push_back(atsPSDData);
                }
                catch (TA_Base_Core::DataException&)
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
        while (databaseConnection->moreData(data));    
        
        // Now that we're finished with the IData object, we need to delete it.
        delete data;
        data = NULL;

        return PSDDataVector;
	}

	std::vector<IAtsPSDData*> AtsPSDDataFactory::getAllPSDDataAtGivenStationOfGivenDataPointNameOfType(unsigned long aStationId, const std::string &aDataPointNameOfType, const bool readWrite)
	{
			// initialise our return variable
		std::vector<IAtsPSDData *> PSDDataVector;

		// get a connection to the database
        TA_Base_Core::IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Ats_Cd, TA_Base_Core::Read);

		// create an SQL statement to retrieve all records from the view
		/*std::ostringstream sql;
		sql << "select " << KEY_COL << ", " << STATIONID_COL << ", " << PLATFORMKEY_COL << ", " << PLATFORMID_COL << ", ";
		sql << PLATFORMNAME_COL << ", " << TIS_PLATFORMID_COL << ", ";
		sql << MSSZONE_COL << ", " << PSDNUMBER_COL << ", " << DATAPOINTENTITYKEY_COL << ", ";
		sql << DATAPOINTTYPE_COL << ", " << DATAPOINTNAMEOFTYPE_COL;
		sql << " from AT_PSD_ENTITY_MAP_V where " << DATAPOINTNAMEOFTYPE_COL << " = '" << aDataPointNameOfType << "' ";
		sql << "and " << STATIONID_COL << " = " << aStationId;*/
//		std::string strSql = defPrepareSQLStatement(databaseConnection->GetDbServerType(), AT_PSD_ENTITY_MAP_STD_SELECT_49009, aDataPointNameOfType, aStationId);
//		std::string strSql  = databaseConnection->prepareSQLStatement(AT_PSD_ENTITY_MAP_SELECT_49009, aDataPointNameOfType, aStationId);
		TA_Base_Core::SQLStatement strSql;
		databaseConnection->prepareSQLStatement(strSql, AT_PSD_ENTITY_MAP_SELECT_49009, aDataPointNameOfType, aStationId);

        // Set up the columnNames vector to be passed to executeQuery()
        std::vector<std::string> columnNames;
        columnNames.push_back(KEY_COL);
        columnNames.push_back(STATIONID_COL);
        columnNames.push_back(PLATFORMKEY_COL);
        columnNames.push_back(PLATFORMID_COL);
        columnNames.push_back(PLATFORMNAME_COL);
        columnNames.push_back(TIS_PLATFORMID_COL);
		columnNames.push_back(MSSZONE_COL);
        columnNames.push_back(PSDNUMBER_COL);
        columnNames.push_back(DATAPOINTENTITYKEY_COL);
        columnNames.push_back(DATAPOINTTYPE_COL);
		columnNames.push_back(DATAPOINTNAMEOFTYPE_COL);

        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it
        TA_Base_Core::IData* data = databaseConnection->executeQuery(strSql,columnNames);
                
        using TA_Base_Core::DataException;

        if (0 == data->getNumRows()) // No records are found
        {
            // clean up the pointer
            delete data;
            data = NULL;
            
			// will be empty
			return PSDDataVector;
        }

        // retrieve information in the database
		do
        {
            for (unsigned long i = 0; i < data->getNumRows(); i++)
            {
                // The getUnsignedLongData() call can throw an exception. 
                try
                {
                    // Create a shiny new AtsPSDData interface which will have all the information pre-loaded!
                    IAtsPSDData* atsPSDData = NULL;

                    if (readWrite)
					{
						atsPSDData = new ConfigAtsPSDData(i, *data);
					}
					else
					{
						atsPSDData = new AtsPSDData(i, *data);
					}                 				 												

					// add this object to the vector
                    PSDDataVector.push_back(atsPSDData);
                }
                catch (TA_Base_Core::DataException&)
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
        while (databaseConnection->moreData(data));    
        
        // Now that we're finished with the IData object, we need to delete it.
        delete data;
        data = NULL;

        return PSDDataVector;
	}
	
	std::vector<IAtsPSDData*> AtsPSDDataFactory::getAllPSDDataAtGivenStation(unsigned long aStationId, const bool readWrite)
	{
		// initialise our return variable
		std::vector<IAtsPSDData *> PSDDataVector;

		// get a connection to the database
        TA_Base_Core::IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Ats_Cd, TA_Base_Core::Read);

		// create an SQL statement to retrieve all records from the view
		/*std::ostringstream sql;
		sql << "select " << KEY_COL << ", " << STATIONID_COL << ", " << PLATFORMKEY_COL << ", " << PLATFORMID_COL << ", ";
		sql << PLATFORMNAME_COL << ", " << TIS_PLATFORMID_COL << ", ";
		sql << MSSZONE_COL << ", " << PSDNUMBER_COL << ", " << DATAPOINTENTITYKEY_COL << ", ";
		sql << DATAPOINTTYPE_COL << ", " << DATAPOINTNAMEOFTYPE_COL;
		sql << " from AT_PSD_ENTITY_MAP_V where " << STATIONID_COL << " = " << aStationId;*/
//		std::string strSql = defPrepareSQLStatement(databaseConnection->GetDbServerType(), AT_PSD_ENTITY_MAP_STD_SELECT_49010, aStationId);
//		std::string strSql  = databaseConnection->prepareSQLStatement(AT_PSD_ENTITY_MAP_SELECT_49010, aStationId);
		TA_Base_Core::SQLStatement strSql;
		databaseConnection->prepareSQLStatement(strSql, AT_PSD_ENTITY_MAP_SELECT_49010, aStationId);

        // Set up the columnNames vector to be passed to executeQuery()
        std::vector<std::string> columnNames;
        columnNames.push_back(KEY_COL);
        columnNames.push_back(STATIONID_COL);
        columnNames.push_back(PLATFORMKEY_COL);
        columnNames.push_back(PLATFORMID_COL);
        columnNames.push_back(PLATFORMNAME_COL);
        columnNames.push_back(TIS_PLATFORMID_COL);
		columnNames.push_back(MSSZONE_COL);
        columnNames.push_back(PSDNUMBER_COL);
        columnNames.push_back(DATAPOINTENTITYKEY_COL);
        columnNames.push_back(DATAPOINTTYPE_COL);
		columnNames.push_back(DATAPOINTNAMEOFTYPE_COL);

        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it
        TA_Base_Core::IData* data = databaseConnection->executeQuery(strSql,columnNames);
                
        using TA_Base_Core::DataException;

        if (0 == data->getNumRows()) // No records are found
        {
            // clean up the pointer
            delete data;
            data = NULL;
            
			// will be empty
			return PSDDataVector;
        }

        // retrieve information in the database
		do
        {
            for (unsigned long i = 0; i < data->getNumRows(); i++)
            {
                // The getUnsignedLongData() call can throw an exception. 
                try
                {
                    // Create a shiny new AtsPSDData interface which will have all the information pre-loaded!
                    IAtsPSDData* atsPSDData = NULL;

                    if (readWrite)
					{
						atsPSDData = new ConfigAtsPSDData(i, *data);
					}
					else
					{
						atsPSDData = new AtsPSDData(i, *data);
					}                   				 												

					// add this object to the vector
                    PSDDataVector.push_back(atsPSDData);
                }
                catch (TA_Base_Core::DataException&)
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
        while (databaseConnection->moreData(data));    
        
        // Now that we're finished with the IData object, we need to delete it.
        delete data;
        data = NULL;

        return PSDDataVector;
	}


	std::vector<IAtsPSDData*> AtsPSDDataFactory::getAllPSDData(const bool readWrite)
    {
		// initialise our return variable
		std::vector<IAtsPSDData *> PSDDataVector;

		// get a connection to the database
        TA_Base_Core::IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(TA_Base_Core::Ats_Cd, TA_Base_Core::Read);

		// create an SQL statement to retrieve all records from the view
		/*std::ostringstream sql;
		sql << "select " << KEY_COL << ", " << STATIONID_COL << ", " << PLATFORMKEY_COL << ", " << PLATFORMID_COL << ", ";
		sql << PLATFORMNAME_COL << ", " << TIS_PLATFORMID_COL << ", ";
		sql << MSSZONE_COL << ", " << PSDNUMBER_COL << ", " << DATAPOINTENTITYKEY_COL << ", ";
		sql << DATAPOINTTYPE_COL << ", " << DATAPOINTNAMEOFTYPE_COL;
		sql << " from AT_PSD_ENTITY_MAP_V";*/
//		std::string strSql = defPrepareSQLStatement(databaseConnection->GetDbServerType(), AT_PSD_ENTITY_MAP_STD_SELECT_49011);
//		std::string strSql  = databaseConnection->prepareSQLStatement(AT_PSD_ENTITY_MAP_SELECT_49011);
		TA_Base_Core::SQLStatement strSql;
		databaseConnection->prepareSQLStatement(strSql, AT_PSD_ENTITY_MAP_SELECT_49011);

        // Set up the columnNames vector to be passed to executeQuery()
        std::vector<std::string> columnNames;
		columnNames.push_back(KEY_COL);
        columnNames.push_back(STATIONID_COL);
        columnNames.push_back(PLATFORMKEY_COL);
        columnNames.push_back(PLATFORMID_COL);
        columnNames.push_back(PLATFORMNAME_COL);
        columnNames.push_back(TIS_PLATFORMID_COL);
		columnNames.push_back(MSSZONE_COL);
        columnNames.push_back(PSDNUMBER_COL);
        columnNames.push_back(DATAPOINTENTITYKEY_COL);
        columnNames.push_back(DATAPOINTTYPE_COL);
		columnNames.push_back(DATAPOINTNAMEOFTYPE_COL);

        // Execute the query. The method can throw a DatabaseException.
        // This is documented in the comment of this method.
        // We are responsible for deleting the returned IData object when we're done with it
        TA_Base_Core::IData* data = databaseConnection->executeQuery(strSql,columnNames);
                
        using TA_Base_Core::DataException;

        if (0 == data->getNumRows()) // No records are found
        {
            // clean up the pointer
            delete data;
            data = NULL;
            
			// will be empty
			return PSDDataVector;
        }

        // retrieve information in the database
		do
        {
            for (unsigned long i = 0; i < data->getNumRows(); i++)
            {
                // The getUnsignedLongData() call can throw an exception. 
                try
                {
                    // Create a shiny new AtsPSDData interface which will have all the information pre-loaded!
                    IAtsPSDData* atsPSDData = NULL;

					if (readWrite)
					{
						atsPSDData = new ConfigAtsPSDData(i, *data);
					}
					else
					{
						atsPSDData = new AtsPSDData(i, *data);
					}

					// add this object to the vector
                    PSDDataVector.push_back(atsPSDData);
                }
                catch (TA_Base_Core::DataException&)
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
        while (databaseConnection->moreData(data));    
        
        // Now that we're finished with the IData object, we need to delete it.
        delete data;
        data = NULL;

        return PSDDataVector;
    }

	IConfigAtsPSDData* AtsPSDDataFactory::createAtsPSDData()
    {            
        return new ConfigAtsPSDData();    
    }


    IConfigAtsPSDData* AtsPSDDataFactory::copyAtsPSDData(const IConfigAtsPSDData* atsPSDDataToCopy)
    {
        FUNCTION_ENTRY("copyAtsPSDData");

        TA_ASSERT(atsPSDDataToCopy !=  NULL, "The AtsPSDData to copy was NULL");
        
        const ConfigAtsPSDData* cast = dynamic_cast<const ConfigAtsPSDData*>(atsPSDDataToCopy);

        TA_ASSERT(cast != NULL, "AtsPSDData passed could not be converted into a ConfigAtsPSDData");

        FUNCTION_EXIT;
        return new ConfigAtsPSDData(*cast);

    }

} // TA_Core
