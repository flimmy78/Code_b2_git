/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/user_settings/src/UserSettingsAccessFactory.cpp $
  * @author:  Ripple
  * @version: $Revision: #3 $
  *
  * Last modification: $DateTime: 2012/02/10 14:06:39 $
  * Last modified by:  $Author: huirong.luo $
  *
  * <description>
  *
  */
#pragma warning (disable:4786)
#include <string>
#include "core\data_access_interface\user_settings\src\UserSettingsAccessFactory.h"
#include "core\data_access_interface\user_settings\src\UserSettingsData.h"
#include "core\exceptions\src\DataException.h"

using TA_Base_Core::DataException;

namespace TA_Base_Core
{
    UserSettingsAccessFactory::~UserSettingsAccessFactory()
    {

    }


    IUserSettings* UserSettingsAccessFactory::getUserSettings(std::string sessionId,unsigned long appType)
    {

        // Create the UserSettings object to represent this object.
        IUserSettings* userSettings = new UserSettingsData(sessionId, appType);

        // Return the userSettings pointer. The class that recieves this pointer is responsible
        // for deleting it.
        return userSettings;
    }
} //end namespace TA_Base_Core


