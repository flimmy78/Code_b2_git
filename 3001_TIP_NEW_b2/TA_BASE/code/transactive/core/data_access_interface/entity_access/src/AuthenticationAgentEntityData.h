#ifndef AUTHENTICATIONAGENTENTITYDATA_H_INCLUDED
#define AUTHENTICATIONAGENTENTITYDATA_H_INCLUDED

/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/entity_access/src/AuthenticationAgentEntityData.h $
  * @author Anita Lee
  * @version $Revision: #2 $
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by: $Author: haijun.li $
  * 
  *
  */

#include "core/data_access_interface/entity_access/src/EntityData.h"

namespace TA_Base_Core
{
    class AuthenticationAgentEntityData : public EntityData
    {

    public:
        AuthenticationAgentEntityData() {}
        AuthenticationAgentEntityData(unsigned long key);

        virtual ~AuthenticationAgentEntityData();

    public:

        /**
         * getType
         *
         * Returns the type of this entity. This method must be callable when the object
         * is constructed using the default constructor. The entity type string should be
         * stored as a static const variable in the concrete class. The entity type should
         * not be loaded from the database (note that this method defines no exceptions).
         *
         * @return The entity type of this entity as a std::string
         */
        virtual std::string getType();
		static std::string getStaticType();

        /**
         * getCheckSessionFrequency
         *
		 * Returns the frequency in seconds of how often the sessionRegister is checked
         * for dead sessions.
         */
		unsigned long getCheckSessionFrequency();

        /**
         * getTimeOutPeriod
         *
		 * Returns the timeout period in seconds which is the time the authentication agent
         * will wait without receiving notification from the Control Station that a session 
         * is still alive before removing the session from the register.
         */
		unsigned long getTimeOutPeriod();

        /**
         * getKeepSessionAliveHeartbeat
         *
		 * Returns the frequency at which a session will notify the Authentication Agent that
         * it is still alive.
         */
		unsigned long getKeepSessionAliveHeartbeat();

		std::string getAssetName();

		/**
         * clone
         *
         * Returns a pointer to a new DutyAgentEntityData object that has been initialised with the 
         * specified key.
         *
         * @param key The key with which to construct the DutyAgentEntityData object.
         */
        static IEntityData* clone(unsigned long key);
        
        /**
         * invalidate
         *
         * Mark the data contained by this entity as invalid. The next call to get...() 
         * following a call to invalidate() will cause all the data to be reloaded from
         * the database.
         */
        void invalidate();

    protected:



	private:

        AuthenticationAgentEntityData( const AuthenticationAgentEntityData&);            
		AuthenticationAgentEntityData& operator=(const AuthenticationAgentEntityData&);

        // 
        // The entity type is fixed for all instances of this class.
        // 
        static const std::string ENTITY_TYPE;
		static const std::string CHECK_SESSION_FREQUENCY_NAME;
		static const std::string TIMEOUT_PERIOD_NAME;
        static const std::string KEEP_SESSION_ALIVE_HEARTBEAT_NAME;
		static const std::string ASSET_NAME;
		
		unsigned long m_checkSessionfrequency;
        unsigned long m_timeoutPeriod;
        unsigned long m_keepSessionAliveHeartbeat;
		std::string m_assetName;

        bool m_isValidData;
    };

    typedef boost::shared_ptr<AuthenticationAgentEntityData> AuthenticationAgentEntityDataPtr;
} //close namespace TA_Base_Core

#endif // !defined(AUTHENTICATIONAGENTENTITYDATA_H_INCLUDED)
