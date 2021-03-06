/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/bus/signs/tis_agent_access/src/TTISLibraryVersionMonitor.h $
  * @author:  Kent Yip
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * This is used to keep track of the TTIS predefined message library
  * version at each location
  *
  */

#ifndef TTISLIBRARYVERSIONMONITOR_H
#define TTISLIBRARYVERSIONMONITOR_H

#include "core/synchronisation/src/NonReEntrantThreadLockable.h"
#include "core/synchronisation/src/ThreadGuard.h"

#include "bus/signs/tis_agent_access/src/LibraryVersionMonitor.h"

#include <string>
#include <map>

namespace TA_IRS_Bus
{

    /**
     * Class that will listen for datapoint updates on datapoints that store
     * TTIS version data.
     *
     * This class essentially stores the applicable datapoint postfix and
     * informs the super class of the nature of each postfix (current or
     * next).
     */
    class TTISLibraryVersionMonitor : public LibraryVersionMonitor
    {
    public:
        const static std::string CURRENT_TTIS_STATION_LIBRARY_VERSION_DP_NAME;
        const static std::string NEXT_TTIS_STATION_LIBRARY_VERSION_DP_NAME;
		static void setDPPostfixNameToType(const std::map<std::string, ELibraryVersionPointType>& dpPostFixNameToType);

    public:
        
	    typedef struct
	    {
		    std::string name;
		    unsigned long locationKey;

		    // entitykeys of the particular library version datapoints at this location
		    unsigned long currentTTISLibraryVersionKey;
		    unsigned long nextTTISLibraryVersionKey;
	    } LocationInfo;

        /** Singleton access method. */
        static TTISLibraryVersionMonitor& instance();

        static void removeInstance();

    private:
        /** Constructor. */
        TTISLibraryVersionMonitor( std::map<std::string,ELibraryVersionPointType> dpPostfix );
        /** Destructor. */
        virtual ~TTISLibraryVersionMonitor();

		static std::map<std::string, ELibraryVersionPointType> s_dpPostFixNameToType;

        /** The Singleton instance. */
        static TTISLibraryVersionMonitor* s_instance;
        /** Threadlock for singleton access. */
        static TA_Base_Core::NonReEntrantThreadLockable singletonLock;
    };

} // namespace TA_IRS_Bus

#endif // TTISLIBRARYVERSIONMONITOR_H