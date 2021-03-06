/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/core/utilities/src/DllHandler.cpp $
  * @author:  Karen Graham
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2017/12/11 17:56:56 $
  * Last modified by:  $Author: Ouyang $	
  *
  * This implements the IDLLHandler so it can be passed to the SingletonHelper to allow it
  * to initialise all singletons.
  */

#include "core/utilities/src/DllHandler.h"

#include "core/corba/src/CorbaUtil.h"
#include "core/utilities/src/DebugUtil.h"

namespace TA_Base_Core
{
    TA_Base_Core::RunParams::ParamVector DllHandler::getRunParams() const
    {
        TA_Base_Core::RunParams::ParamVector allParams;
        TA_Base_Core::RunParams::getInstance().getAll(allParams);
        return allParams;
    }


    void DllHandler::forwardRunParamUpdates( TA_Base_Core::RunParams* runParams )
    {
        // TD10773: Tell the main RunParams instance to forward updates to the specified
        //          child instance.
        TA_Base_Core::RunParams::getInstance().forwardUpdatesTo( runParams );
    }


    TA_Base_Core::CorbaUtil& DllHandler::getCorbaUtil() const
    {
        return TA_Base_Core::CorbaUtil::getInstance();
    }

	TA_Base_Core::DebugUtil& DllHandler::getDebugUtil() const
	{
		return TA_Base_Core::DebugUtil::getInstance();
	}
}