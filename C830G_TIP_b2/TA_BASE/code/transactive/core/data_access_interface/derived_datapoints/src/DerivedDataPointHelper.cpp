/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File$
  * @author HoaVu
  * @version $Revision$
  *
  * Last modification: $DateTime$
  * Last modified by: $Author$
  *
  * DerivedDataPointHelper accesses the parameters associated with a
  * Derived DataPoint entity in the database.
  *
  */

#ifdef __WIN32__
    #pragma warning(disable:4786) // disable the "trucated to 255 character" warning
    #pragma warning(disable:4723)    // potential divide by 0
#endif

#include <sstream>

#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/RunParams.h"
#include "core/exceptions/src/DataException.h"
#include "core/exceptions/src/DatabaseException.h"
#include "core/data_access_interface/src/IDatabase.h"
#include "core/data_access_interface/src/IData.h"
#include "core/data_access_interface/src/DatabaseFactory.h"
#include "core/data_access_interface/derived_datapoints/src/DerivedDataPointHelper.h"
#include "core/data_access_interface/derived_datapoints/src/ConfigConfiguredDerivedState.h"
#include "core/data_access_interface/derived_datapoints/src/ConfigConfiguredInputAssociation.h"
#include "core/data_access_interface/derived_datapoints/src/ConfigDerivedOutputAssociation.h"
#include "core/threads/src/Thread.h"

namespace TA_Base_Core
{
    DerivedDataPointHelper::DerivedDataPointHelper()
    {
        // do nothing
    }


    DerivedDataPointHelper::~DerivedDataPointHelper()
    {
        // do nothing
    }


    InputAssociationList DerivedDataPointHelper::getInputAssociations ( unsigned long ddpKey )
    {
        FUNCTION_ENTRY("getInputAssociations");
        FUNCTION_EXIT;

        return DerivedDataPointConfigCache::getInstance().getInputAssociations(ddpKey);
    }


    DerivedStateList DerivedDataPointHelper::getDerivedStates ( unsigned long ddpKey )
    {
        FUNCTION_ENTRY("getDerivedStates");       
        FUNCTION_EXIT;

        return DerivedDataPointConfigCache::getInstance().getDerivedStates(ddpKey);
    }


    OutputAssociationList DerivedDataPointHelper::getDerivedOutputAssociations ( unsigned long derivedStatePkey )
    {
        FUNCTION_ENTRY("getDerivedOutputAssociations");       
        FUNCTION_EXIT;

        return DerivedDataPointConfigCache::getInstance().getOutputAssociations(derivedStatePkey);
    }


    void DerivedDataPointHelper::deleteDerivedDataPoint( unsigned long ddpKey)
    {
        FUNCTION_ENTRY("deleteDerivedDataPoint");

        // get handle to the database
        IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(Scada_Cd, Write);

        std::ostringstream sql;
        sql << "select SCDSTA_ID from SC_DERIVED_STATE where DERIVED_DP_PKEY = " << ddpKey;

        const std::string DERIVED_STATE_PKEY("SCDSTA_ID");
        std::vector<std::string> columnNames;
        columnNames.push_back( DERIVED_STATE_PKEY );

        IData* data = NULL;
        std::string listOfKeys("");
        try
        {
            data = databaseConnection->executeQuery( sql.str(), columnNames );
            
            for (unsigned int i = 0; i < data->getNumRows(); ++i)
            {
                listOfKeys += data->getStringData(i, DERIVED_STATE_PKEY);
                listOfKeys += ",";
            }
            if (!listOfKeys.empty())
            {
                // Remove the trailing comma
                listOfKeys = listOfKeys.substr(0, listOfKeys.length() - 1 );
            }

            delete data;
            data = NULL;
        }
        catch ( ... )
        {
            // Tidy up and then rethrow
            if (data != NULL)
            {
                delete data;
                data = NULL;
            }
            throw;
        }

        sql.str("");
        sql << "delete SC_INPUT_ASSOCIATION where MAIN_ENTITY_PKEY = " << ddpKey;

        databaseConnection->executeModification(sql.str());

        if (!listOfKeys.empty())
        {
            sql.str("");
            sql << "delete SC_DERIVED_OUTPUT_ASSOCIATION where SCDSTA_ID in (" << listOfKeys << ")";

            databaseConnection->executeModification(sql.str());
        }

        sql.str("");
        sql << "delete SC_DERIVED_STATE where DERIVED_DP_PKEY = " << ddpKey;

        databaseConnection->executeModification(sql.str());


        FUNCTION_EXIT;
    }


    void DerivedDataPointHelper::addNew(unsigned long ddpKey,
                                        IConfigDerivedDataPoint::InputAssociationMap& inputs,
                                        IConfigDerivedDataPoint::StateMap& states,
                                        IConfigDerivedDataPoint::OutputAssociationMap& outputs )
    {
        FUNCTION_ENTRY("addNew");

        // get handle to the database
        IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(Scada_Cd, Write);

        //
        // Insert all input associations into the database
        //
        std::ostringstream baseSql;
        baseSql << "insert into SC_INPUT_ASSOCIATION(SCIASS_ID, MAIN_ENTITY_PKEY, INPUT_ENTITY_PKEY, "
                << "INPUT_CALC_ORDER, PREDEFINED_INPUT_VALUE) values (";

        for(IConfigDerivedDataPoint::InputAssociationMap::iterator input = inputs.begin(); input != inputs.end(); ++input)
        {
            unsigned long key = getNextPkey();

            std::ostringstream sql;
            sql << baseSql.str() << key << ","
                                 << ddpKey << ","
                                 << input->second->getInputEntityKey() << "," 
                                 << input->second->getInputCalculationOrder() << ","
                                 << input->second->getPredefinedInputValue() << ")";

            databaseConnection->executeModification(sql.str());

            input->second->setKey(key);
        }

        //
        // Insert all derived states into the database
        //
        baseSql.str("");
        baseSql << "insert into SC_DERIVED_STATE(SCDSTA_ID, DERIVED_DP_PKEY, STATE_VALUE, STATE_DESCRIPTION, "
                << "ALARM_ENABLED, ALARM_DELAY, ALARM_MESSAGE, ALARM_SEVERITY) values (";

        // We will store the keys for the inserted states in a map so when we go to add the outputs
        // we know what keys to use
        std::map<int, unsigned long> stateKeys;

        for(IConfigDerivedDataPoint::StateMap::iterator state = states.begin(); state != states.end(); ++state)
        {
            unsigned long key = getNextPkey();

            stateKeys.insert( std::map<int, unsigned long>::value_type( state->first, key ) );

            std::ostringstream sql;
            sql << baseSql.str() << key << ","
                                 << ddpKey << ","
                                 << state->second->getStateValue() << ",'"
                                 << state->second->getStateDescription() << "',"
                                 << state->second->getAlarmEnabled() << ","
                                 << state->second->getAlarmDelay() << ",'"
                                 << state->second->getAlarmMessage() << "',"
                                 << state->second->getAlarmSeverity() << ")";

            databaseConnection->executeModification(sql.str());

            state->second->setKey( key );
        }

        //
        // Insert all output associations into the database
        //
        baseSql.str("");
        baseSql << "insert into SC_DERIVED_OUTPUT_ASSOCIATION(SCDOAS_ID, SCDSTA_ID, OUTPUT_DP_PKEY, OUTPUT_VALUE)"
                << "values (";

        for(IConfigDerivedDataPoint::OutputAssociationMap::iterator output = outputs.begin(); output != outputs.end(); ++output)
        {
            std::map<int, unsigned long>::iterator matching = stateKeys.find( output->first );
            if (matching == stateKeys.end() )
            {
                continue;
            }

            unsigned long key = getNextPkey();

            std::ostringstream sql;
            sql << baseSql.str() << key << ","
                                 << matching->second << ","
                                 << output->second->getOutputEntityKey() << "," 
                                 << output->second->getOutputValue() << ")";

            databaseConnection->executeModification(sql.str());

            output->second->setKey( key );
        }
        

        FUNCTION_EXIT;
    }


    void DerivedDataPointHelper::modifyExisting(unsigned long ddpKey,
                                                IConfigDerivedDataPoint::InputAssociationMap& inputs,
                                                IConfigDerivedDataPoint::StateMap& states,
                                                IConfigDerivedDataPoint::OutputAssociationMap& outputs )
    {
        FUNCTION_ENTRY("modifyExisting");

        // This procedure performs the following on the database:
        //
        // Inputs  - Select all inputs where the key is not one we have stored and then delete them
        // Inputs  - Update all inputs that have keys
        // Inputs  - Add all inputs that are new and set their keys
        
        modifyInputs(ddpKey, inputs);

        
        // Outputs - Select all outputs where the key is not one we have stored and then delete them

        removeOutputs(ddpKey, outputs);


        // States  - Select all states where the key is not one we have stored and then delete them
        // States  - Update all states that have keys
        // States  - Add all states that are new and set their keys

        modifyStates(ddpKey, states);


        // Outputs - Add all the outputs that are new and set their keys
        // Outputs - Update all outputs that have keys

        modifyOutputs(ddpKey, outputs, states);

        FUNCTION_EXIT;
    }


    void DerivedDataPointHelper::modifyInputs(unsigned long ddpKey,
                                              IConfigDerivedDataPoint::InputAssociationMap& inputs )
    {
        FUNCTION_ENTRY("modifyInputs");

        // get handle to the database
        IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(Scada_Cd, Write);

        //
        // First delete old entries that will no longer be used
        //
        std::ostringstream keys;
        IConfigDerivedDataPoint::InputAssociationMap::iterator input;
        for(input = inputs.begin(); input != inputs.end(); ++input)
        {
            if (input->second->getKey() != 0)
            {
                keys << input->second->getKey() << ",";
            }
        }

        // Remove the trailing comma off the list of keys;
        std::string stillActiveKeys = keys.str().substr(0, keys.str().length() - 1);

        if (!stillActiveKeys.empty())
        {
            // Now we can delete all items for this derived datapoint that do not have one of these keys
            std::ostringstream sql;
            sql << "delete SC_INPUT_ASSOCIATION where MAIN_ENTITY_PKEY = " << ddpKey
                << " and SCIASS_ID not in (" << stillActiveKeys << ")";

            databaseConnection->executeModification(sql.str());
        }
        else
        {
            // Now we can delete all items for this derived datapoint
            std::ostringstream sql;
            sql << "delete SC_INPUT_ASSOCIATION where MAIN_ENTITY_PKEY = " << ddpKey;

            databaseConnection->executeModification(sql.str());
        }


        //
        // Now update or add entries as necessary
        //
        std::ostringstream insertSql;
        insertSql << "insert into SC_INPUT_ASSOCIATION(SCIASS_ID, MAIN_ENTITY_PKEY, INPUT_ENTITY_PKEY, "
                  << "INPUT_CALC_ORDER, PREDEFINED_INPUT_VALUE) values (";

        for(input = inputs.begin(); input != inputs.end(); ++input)
        {
            std::ostringstream sql;
            if (input->second->getKey() != 0)
            {
                // Update existing item
                sql << "update SC_INPUT_ASSOCIATION set INPUT_CALC_ORDER = " << input->second->getInputCalculationOrder()
                    << ", PREDEFINED_INPUT_VALUE = " << input->second->getPredefinedInputValue() 
                    << " where SCIASS_ID = " << input->second->getKey();

                databaseConnection->executeModification(sql.str());
            }
            else
            {
                // Add a new item
                unsigned long key = getNextPkey();

                sql << insertSql.str() << key << "," << ddpKey << "," << input->second->getInputEntityKey()
                                       << "," << input->second->getInputCalculationOrder() << "," 
                                       << input->second->getPredefinedInputValue() << ")";

                databaseConnection->executeModification(sql.str());

                input->second->setKey( key );
            }
        }

        FUNCTION_EXIT;
    }


    void DerivedDataPointHelper::removeOutputs(unsigned long ddpKey,
                                               IConfigDerivedDataPoint::OutputAssociationMap& outputs)
    {
        FUNCTION_ENTRY("modifyOutputs");
        
        // get handle to the database
        IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(Scada_Cd, Write);

        //
        // First delete old entries that will no longer be used
        //
        std::ostringstream keys;
        for(IConfigDerivedDataPoint::OutputAssociationMap::iterator output = outputs.begin(); output != outputs.end(); ++output)
        {
            if (output->second->getKey() != 0)
            {
                keys << output->second->getKey() << ",";
            }
        }

        // Remove the trailing comma off the list of keys;
        std::string stillActiveKeys = keys.str().substr(0, keys.str().length() - 1);

        if (!stillActiveKeys.empty())
        {
            // Now we can delete all items for this derived datapoint that do not have one of these keys
            std::ostringstream sql;
            sql << "delete SC_DERIVED_OUTPUT_ASSOCIATION where SCDOAS_ID not in (" << stillActiveKeys
                << ") and SCDSTA_ID in (select SCDSTA_ID from SC_DERIVED_STATE where DERIVED_DP_PKEY = "
                << ddpKey << ")";

            databaseConnection->executeModification(sql.str());
        }
        else
        {
            // Now we can delete all items for this derived datapoint
            std::ostringstream sql;
            sql << "delete SC_DERIVED_OUTPUT_ASSOCIATION where SCDSTA_ID in "
                << "(select SCDSTA_ID from SC_DERIVED_STATE where DERIVED_DP_PKEY = "
                << ddpKey << ")";

            databaseConnection->executeModification(sql.str());
        }

        FUNCTION_EXIT;
    }


    void DerivedDataPointHelper::modifyOutputs(unsigned long ddpKey,
                                               IConfigDerivedDataPoint::OutputAssociationMap& outputs,
                                               IConfigDerivedDataPoint::StateMap& states)
    {
        FUNCTION_ENTRY("addNewOutputs");

        // get handle to the database
        IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(Scada_Cd, Write);

        //
        // Now update or add entries as necessary
        //
        std::ostringstream insertSql;
        insertSql << "insert into SC_DERIVED_OUTPUT_ASSOCIATION(SCDOAS_ID, SCDSTA_ID, OUTPUT_DP_PKEY, "
                  << "OUTPUT_VALUE) values (";

        // Keep a list of any outputs we need to delete. Once we have finished iterating through the list
        // we will delete these.
        std::vector<IConfigDerivedDataPoint::OutputAssociationMap::iterator> itemsToDelete;

        for(IConfigDerivedDataPoint::OutputAssociationMap::iterator output = outputs.begin(); output != outputs.end(); ++output)
        {
            std::ostringstream sql;
            if (output->second->getKey() != 0)
            {
                // Update existing item
                sql << "update SC_DERIVED_OUTPUT_ASSOCIATION set OUTPUT_VALUE = " << output->second->getOutputValue()
                    << " where SCDOAS_ID = " << output->second->getKey();

                databaseConnection->executeModification(sql.str());
            }
            else
            {
                // Add a new item
                unsigned long key = getNextPkey();
                
                IConfigDerivedDataPoint::StateMap::iterator matching = states.find( output->first );
                if (matching == states.end())
                {
                    // If there is no matching state then we shouldn't have this output
                    delete output->second;
                    output->second = NULL;

                    // Add this item to be deleted later
                    itemsToDelete.push_back(output);
                    continue;
                }
                
                sql << insertSql.str() << key << "," 
                                       << matching->second->getKey() << ","
                                       << output->second->getOutputEntityKey() << ","
                                       << output->second->getOutputValue() << ")";

                databaseConnection->executeModification(sql.str());

                output->second->setKey( key );
            }
        }

        // If there are any outputs to delete do that now.
        for (std::vector<IConfigDerivedDataPoint::OutputAssociationMap::iterator>::iterator i = itemsToDelete.begin();
             i != itemsToDelete.end(); ++i)
        {
             outputs.erase(*i);
        }

        FUNCTION_EXIT;
    }


    void DerivedDataPointHelper::modifyStates(unsigned long ddpKey,
                                              IConfigDerivedDataPoint::StateMap& states)
    {
        FUNCTION_ENTRY("modifyStates");

        // get handle to the database
        IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(Scada_Cd, Write);

        //
        // First delete old entries that will no longer be used
        //
        std::ostringstream keys;
        IConfigDerivedDataPoint::StateMap::iterator state;
        for(state = states.begin(); state != states.end(); ++state)
        {
            if (state->second->getKey() != 0)
            {
                keys << state->second->getKey() << ",";
            }
        }

        // Remove the trailing comma off the list of keys;
        std::string stillActiveKeys = keys.str().substr(0, keys.str().length() - 1);

        if (!stillActiveKeys.empty())
        {
            // Now we can delete all items for this derived datapoint that do not have one of these keys
            std::ostringstream sql;
            sql << "delete SC_DERIVED_STATE where SCDSTA_ID not in (" << stillActiveKeys << ")"
                << " and DERIVED_DP_PKEY = " << ddpKey;

            databaseConnection->executeModification(sql.str());
        }
        else
        {
            // Now we can delete all items for this derived datapoint
            std::ostringstream sql;
            sql << "delete SC_DERIVED_STATE where DERIVED_DP_PKEY = " << ddpKey;

            databaseConnection->executeModification(sql.str());
        }


        //
        // Now update or add entries as necessary
        //
        std::ostringstream insertSql;
        insertSql << "insert into SC_DERIVED_STATE(SCDSTA_ID, DERIVED_DP_PKEY, STATE_VALUE, STATE_DESCRIPTION, "
                  << "ALARM_ENABLED, ALARM_DELAY, ALARM_MESSAGE, ALARM_SEVERITY) values (";

        for(state = states.begin(); state != states.end(); ++state)
        {
            std::ostringstream sql;
            if (state->second->getKey() != 0)
            {
                // Update existing item
                sql << "update SC_DERIVED_STATE set "
                    << " STATE_VALUE = " << state->second->getStateValue()
                    << ", STATE_DESCRIPTION = '" << state->second->getStateDescription()
                    << "', ALARM_ENABLED = " << state->second->getAlarmEnabled()
                    << ", ALARM_DELAY = " << state->second->getAlarmDelay()
                    << ", ALARM_MESSAGE = '" << state->second->getAlarmMessage()
                    << "', ALARM_SEVERITY = " << state->second->getAlarmSeverity()
                    << " where SCDSTA_ID = " << state->second->getKey();

                databaseConnection->executeModification(sql.str());
            }
            else
            {
                // Add a new item
                unsigned long key = getNextPkey();

                sql << insertSql.str() << key << ","
                                       << ddpKey << ","
                                       << state->second->getStateValue() << ",'"
                                       << state->second->getStateDescription() << "',"
                                       << state->second->getAlarmEnabled() << ","
                                       << state->second->getAlarmDelay() << ",'"
                                       << state->second->getAlarmMessage() << "',"
                                       << state->second->getAlarmSeverity() << ")";

                databaseConnection->executeModification(sql.str());

                state->second->setKey( key );
            }
        }
        FUNCTION_EXIT;
    }


    
    unsigned long DerivedDataPointHelper::getNextPkey()
    {
        FUNCTION_ENTRY("getNextPkey");

        // get handle to the database
        IDatabase* databaseConnection = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(Scada_Cd, Write);

#ifdef TDS_DEVELOP
        std::string keySql = "select pkg_seq.get_next_number('SCADA_SEQ') from dual";
#else
		std::string keySql = "select SCADA_SEQ.nextval from dual";
#endif
        std::vector<std::string> keyColumns;
        keyColumns.push_back("Key");

        IData* data = databaseConnection->executeQuery(keySql, keyColumns);
        if (data->getNumRows() == 0)
        {
            delete data;
            data = NULL;
            TA_THROW( DataException("Could not determine the next key", DataException::NO_VALUE ,"") );
        }

        unsigned long key = data->getUnsignedLongData(0, "Key");

        delete data;
        data = NULL;

        FUNCTION_EXIT;
        return key;
    }
} // closes TA_Base_Core


