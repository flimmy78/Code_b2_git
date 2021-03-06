/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/TA_Common_V1_TIP/transactive/bus/banner_framework/src/SingletonHelper.cpp $
  * @author:  Katherine Thomson
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/01/19 17:43:23 $
  * Last modified by:  $Author: CM $	
  *
  * Provides methods to handle the problems of accessing
  * singletons across a DLL interface.
  */

#pragma warning (disable : 4786)
#pragma warning (disable : 4284)

#include "stdafx.h"

#include "bus/banner_framework/src/SingletonHelper.h"

#include "core/exceptions/src/UtilitiesException.h"
#include "core/utilities/src/RunParams.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/IDllHandler.h"
#include "core/corba/src/CorbaUtil.h"

namespace TA_Base_Bus
{
    void SingletonHelper::initialiseUtilities( const TA_Base_Core::IDllHandler& handler, 
                                               const std::string& entityName,
                                               const std::string& dllName )
    {
        // Pick a random runparam that always gets set and see if it is already set
        if (TA_Base_Core::RunParams::getInstance().isSet( RPARAM_APPNAME ))
        {
            // We have already initialised the singletons so don't do it again
            return;
        }

        initialiseCorba( handler.getCorbaUtil() );
        setRunParams( handler.getRunParams(), entityName );
        initialiseDebugUtil( dllName );

        // TD10773: Now make sure we get updates - unfortunately the handler is const but forwarding
        // updates requires modifying internal structures, so we must cast away the constness.
        const_cast<TA_Base_Core::IDllHandler*>(&handler)->forwardRunParamUpdates( &TA_Base_Core::RunParams::getInstance() );
    }


    void SingletonHelper::initialiseCorba( TA_Base_Core::CorbaUtil& corbaUtil  )
    {
        TA_Base_Core::CorbaUtil::setInstance( corbaUtil );
    }


    void SingletonHelper::setRunParams( TA_Base_Core::RunParams::ParamVector& mainAppRunParams,
                                        const std::string& entityName )
    {
        TA_Base_Core::RunParams& dllRunParams = TA_Base_Core::RunParams::getInstance();
        TA_Base_Core::RunParams::ParamVector::iterator it = mainAppRunParams.end();
        for( it = mainAppRunParams.begin(); it != mainAppRunParams.end(); it++ )
        {
            if( !dllRunParams.isSet( it->name.c_str() ) )
            {
                dllRunParams.set( it->name.c_str(), it->value.c_str() );
            }
        }

        // Set the DLL's entity name
        dllRunParams.set( RPARAM_ENTITYNAME, entityName.c_str() );
    }


    void SingletonHelper::initialiseDebugUtil( const std::string& dllName )
    {
        // Set the debug file name
        // It will be the debug file name for the MapViewer + the DLL name.
        std::string param = TA_Base_Core::RunParams::getInstance().get(RPARAM_DEBUGFILE);
        if (!param.empty())
        {
			std::string::size_type pos = param.find_last_of(".");

            std::string strToInsert = "." + dllName;
            if (pos == std::string::npos)
            {
                pos = param.length();
            }
            param.insert(pos,strToInsert.c_str());

            TA_Base_Core::DebugUtil::getInstance().setFile( ( param ).c_str());
        }

        // Set the debug level
        param = TA_Base_Core::RunParams::getInstance().get(RPARAM_DEBUGLEVEL);
        if (!param.empty())
        {
            TA_Base_Core::DebugUtil::getInstance().setLevel( TA_Base_Core::DebugUtil::getDebugLevelFromString(param.c_str()));
        }

        // Set the maximum size of a debug file in bytes
        param = TA_Base_Core::RunParams::getInstance().get(RPARAM_DEBUGFILEMAXSIZE);
        if (!param.empty())
        {
            TA_Base_Core::DebugUtil::getInstance().setMaxSize(atoi(param.c_str()));
        }

        // Set the maximum number of log files
        param = TA_Base_Core::RunParams::getInstance().get(RPARAM_DEBUGMAXFILES);
        if (!param.empty())
        {
            TA_Base_Core::DebugUtil::getInstance().setMaxFiles(atoi(param.c_str()));
        }

		// Use Pid encoding in filenames
        param = TA_Base_Core::RunParams::getInstance().get(RPARAM_DEBUGPIDFILENAMES);
        if (!param.empty())
        {
            TA_Base_Core::DebugUtil::getInstance().encryptPidInFilenames(param);
        }

		// Use debug level specific log files
        param = TA_Base_Core::RunParams::getInstance().get(RPARAM_DEBUGLEVELFILE);
        if (!param.empty())
        {
            TA_Base_Core::DebugUtil::getInstance().decodeLevelFilenames(param);
        }

		// Turn off logging for debug levels
        param = TA_Base_Core::RunParams::getInstance().get(RPARAM_DEBUGLEVELOFF);
        if (!param.empty())
        {
            TA_Base_Core::DebugUtil::getInstance().decodeDisabledLevels(param);
        }
    }
} // TA_Base_Bus
