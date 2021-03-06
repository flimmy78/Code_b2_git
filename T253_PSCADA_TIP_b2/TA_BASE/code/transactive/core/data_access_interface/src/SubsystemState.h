#if !defined(SUBSYSTEM_STATE_H_INLCUDED)
#define SUBSYSTEM_STATE_H_INLCUDED

/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/core/data_access_interface/src/SubsystemState.h $
  * @author:  Anita Lee
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2017/10/31 16:21:54 $
  * Last modified by:  $Author: CM $
  * 
  * Action is an implementation of ISubsystemState. It holds the data specific to an action entry
  * in the database, and allows read-only access to that data.
  *
  */

#include "core/data_access_interface/src/ISubsystemState.h"

namespace TA_Base_Core
{
    class SubsystemState : public ISubsystemState
    {

    public:

        /**
         * Constructor
         *
         * Construct an SubsystemState class based around a key.
         *
         * @param key The key of this SubsystemState in the database
         */
        SubsystemState( const unsigned long key );

        /**
         * Constructor
         *
         * Construct an SubsystemState class based around all data 
         *
         * @param key The key of this SubsystemState in the database
         * @param name The name of this SubsystemState in the database
         * @param description The description of this SubsystemState in the database
         */
        SubsystemState( const unsigned long key, const std::string& name, const std::string& description );

        /**
         * Refer to ISubsystemState.h for a description of this method.
         */
        virtual unsigned long getKey();

        /**
         * Refer to ISubsystemState.h for a description of this method.
         */
        virtual std::string getName();

        /**
         * Refer to ISubsystemState.h for a description of this method.
         */
        virtual std::string getDescription();
        
        /**
         * Refer to ISubsystemState.h for a description of this method.
         */
        virtual void invalidate();

    private:

        // Assignment operator not used so it is made private
        SubsystemState( const SubsystemState&);            
		SubsystemState& operator=(const SubsystemState&);

        bool m_isValidData;

        unsigned long m_key;
        std::string m_name;
        std::string m_description;

		void reload();

    };
} // closes TA_Base_Core

#endif // !defined(SUBSYSTEM_STATE_H_INLCUDED)
