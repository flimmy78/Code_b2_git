#if !defined(ItaRuntime_6C7E1C63_2C40_4ea7_B38A_F3BAC74347E8__INCLUDED_)
#define ItaRuntime_6C7E1C63_2C40_4ea7_B38A_F3BAC74347E8__INCLUDED_

/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/core/process_management/public_interfaces/ItaRuntime.h $
  * @author:  Sean Liew
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * Interface to allow the outsourcer to access certain process parameters of the
  * application.
  */

#include <string>

namespace TA_Base_Core
{
    class ItaRuntime
    {
    public:

	    /**
         * getConfigParameterValue
         *
         * This returns the value for a stored parameter
         *
	     * @param name The name of the parameter to retrieve
         *
         * @return string The value for the parameter
	     * 
         * @exception CtaRuntimeEntityParameterNotFoundException if the parameter is not found
	     */
	    virtual std::string getConfigParameterValue(const std::string& name) =0;


        /**
         * getMyEntityKey
         *
         * @return unsigned long The key of the agent/application entity from the database
         */
	    virtual unsigned long getMyEntityKey() const =0;


        /**
         * getMyEntityName
         *
         * @return string The name of the agent/application entity from the database
         */
        virtual std::string getMyEntityName() const =0;


        /**
         * getMyEntityType
         *
         * @return string The name of the agent/application entity type from the database
         */
	    virtual std::string getMyEntityType() const =0;


        /**
         * getMyEntityTypeKey
         *
         * @return unsigned long The key of the agent/application entity type from the database
         */
	    virtual unsigned long getMyEntityTypeKey() const =0;

        
        /**
         * getMySessionId
         *
         * @return string The current session id
         */
	    virtual std::string getMySessionId() const =0;


        /**
         * getMyEntityLocationKey
         *
         * @return unsigned long The key of the agent/application location from the database
         */
	    virtual unsigned long getMyEntityLocationKey() const =0;


        /**
         * getMyProcessLocationKey
         *
         * @return unsigned long The key of the location where the application/agent is running
         */
	    virtual unsigned long getMyProcessLocationKey() const =0;


        /**
         * getMyEntitySubsystemKey
         *
         * @return unsigned long The key of the agent/application subsystem from the database
         */
	    virtual unsigned long getMyEntitySubsystemKey() const =0;

    };
}
#endif // !defined(ItaRuntime_6C7E1C63_2C40_4ea7_B38A_F3BAC74347E8__INCLUDED_)
