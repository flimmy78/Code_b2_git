/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/core/data_access_interface/src/SubsystemState.cpp $
  * @author:  Anita Lee
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * SubsystemState is an implementation of ISubsystemState. It holds the data specific to an SubsystemState entry
  * in the database, and allows read-only access to that data.
  *
  */
#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif // defined (_MSC_VER)

#include "core/data_access_interface/src/SubsystemState.h"
#include "core/data_access_interface/src/IDatabase.h"
#include "core/data_access_interface/src/DatabaseFactory.h"

#include "core/utilities/src/TAAssert.h"

#include "core/exceptions/src/DataException.h"

namespace TA_Base_Core
{

    SubsystemState::SubsystemState( const unsigned long key )
		: m_isValidData( false ),
		m_key( key),
        m_name(""),
        m_description("")
    {
    }


    SubsystemState::SubsystemState( const unsigned long key, const std::string& name, const std::string& description )
        : m_isValidData( false ),
		m_key( key ),
        m_name( name ),
        m_description( description )
    {
    }


	unsigned long SubsystemState::getKey()
    {
		return m_key;
    }


    std::string SubsystemState::getName()
    {
		if( !m_isValidData && m_name.empty() )
        {
            reload();
        }

        return( m_name );
    }


    std::string SubsystemState::getDescription()
    {
		if( !m_isValidData && m_description.empty() )
        {
            reload();
        }

        return( m_description );
    }


    void SubsystemState::invalidate()
    {
	    m_isValidData = false;

		m_name = "";
        m_description = "";
	}


    void SubsystemState::reload()
    {
		// get the name and the ActionGroup
		TA_Base_Core::IDatabase* pDb = TA_Base_Core::DatabaseFactory::getInstance().getDatabase(OnlineUpdatable_Cd, Read);

		std::ostringstream sql;

		sql << "select NAME, DESCRIPTION from SE_SUBSYSTEM_STATE where SESSTA_ID = " << m_key;

		std::vector<std::string> cols;
		cols.push_back( "name" );
        cols.push_back( "description" );

		std::auto_ptr<TA_Base_Core::IData> data( pDb->executeQuery( sql.str(), cols ) );

		if( (NULL == data.get() ) || (0 == data->getNumRows()) ) 
        {
            // If there is no entry then this is an error as the key as accurate before
            std::ostringstream reasonMessage;
            reasonMessage << "No data found for subsystem state with key = " << m_key;
            TA_THROW( DataException(reasonMessage.str().c_str(), DataException::NO_VALUE, "") );
        }

		m_name = data->getStringData( 0, cols[0] );
        m_description = data->getStringData( 0, cols[1] );

        // Need to record that we now have valid data
        m_isValidData = true;
    }

} // closes TA_Base_Core
