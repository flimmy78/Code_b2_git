/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/core/utilities/src/DllHandler.cpp $
  * @author:  Karen Graham
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $	
  *
  * This implements the IDLLHandler so it can be passed to the SingletonHelper to allow it
  * to initialise all singletons.
  */

#include "core/utilities/src/DllHandler.h"

#include "core/corba/src/CorbaUtil.h"

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

} // TA_Base_Core

