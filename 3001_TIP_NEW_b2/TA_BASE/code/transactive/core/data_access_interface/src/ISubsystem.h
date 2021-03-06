/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/src/ISubsystem.h $
  * @author:  Karen Graham
  * @version: $Revision: #4 $
  *
  * Last modification: $DateTime: 2012/06/07 16:40:53 $
  * Last modified by:  $Author: hui.wang $
  * 
  * ISubsystem is an interface to a Subsystem object. It allows the Subsystem object implementation
  * to be chagned (e.g. if necessary due to a database schema change) without changing code
  * that uses it.
  *
  */

#if !defined(ISUBSYSTEM_34315582_B0A7_4100_BD60_2E13958D7501__INCLUDED_)
#define ISUBSYSTEM_34315582_B0A7_4100_BD60_2E13958D7501__INCLUDED_

#include <string>

#include "core/data_access_interface/src/IItem.h"

namespace TA_Base_Core
{

    class ISubsystem : public IItem
	{

    public:
        virtual ~ISubsystem() 
			{ 
			};

        /** 
         * isPhysical
         *
         * This returns whether this is a physical subsystem or not.
         *
         * @return bool - True if this is a physical subsystem, false otherwise
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception DataException A DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. ACCESSLEVEL should be an 
         *            unsigned long), or if the wrong ammount of data is retrieved.
         */
        virtual bool isPhysical() =0;


		/** 
         * isExclusive
         *
         * This returns whether this is an exclusive subsystem or not.
         *
         * @return bool - True if this is an exclusive subsystem, false otherwise
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception DataException A DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. ACCESSLEVEL should be an 
         *            unsigned long), or if the wrong ammount of data is retrieved.
         */
        virtual bool isExclusive() =0;


        /**
         * getDateCreated
         *
         * Returns the date created for this subsystem.
         *
         * @return The date created for this subsystem as a time_t.
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception DataException A DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. TYPEKEY should be an 
         *            unsigned long), or if the wrong ammount of data is retrieved, or if the
         *            the subsystem key is invalid (and this is not a new subsystem).
         */
        virtual time_t getDateCreated() =0;


        /**
         * getDateModified
         *
         * Returns the date modified for this subsystem.
         *
         * @return The date modified for this subsystem as a time_t.
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception DataException A DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. TYPEKEY should be an 
         *            unsigned long), or if the wrong ammount of data is retrieved, or if the
         *            the subsystem key is invalid (and this is not a new subsystem).
         */
        virtual time_t getDateModified() =0;

		/**
         * getSystemKey
         *
         * Returns the key for this system.
         *
         * @return The key for this system as an unsigned long.
         */
        virtual unsigned long getSystemKey() =0;

	};
} //close namespace TA_Base_Core

#endif // !defined(ISubsystem_34315582_B0A7_4100_BD60_2E13958D7501__INCLUDED_)
