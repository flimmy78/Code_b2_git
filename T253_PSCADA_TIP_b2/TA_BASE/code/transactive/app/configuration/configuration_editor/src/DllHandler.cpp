/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/app/configuration/configuration_editor/src/DllHandler.cpp $
  * @author:  Karen Graham
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/01/23 17:37:20 $
  * Last modified by:  $Author: builder $	
  *
  * This implements the IDLLHandler so it can be passed to the SingletonHelper to allow it
  * to initialise all singletons.
  */

#include "app/configuration/configuration_editor/src/DllHandler.h"

#include "core/corba/src/CorbaUtil.h"

namespace TA_Base_App
{
    TA_Base_Core::RunParams::ParamVector DllHandler::getRunParams() const
    {
        TA_Base_Core::RunParams::ParamVector allParams;
        TA_Base_Core::RunParams::getInstance().getAll(allParams);
        return allParams;
    }


    TA_Base_Core::CorbaUtil& DllHandler::getCorbaUtil() const
    {
        return TA_Base_Core::CorbaUtil::getInstance();
    }


} // TA_Base_App

