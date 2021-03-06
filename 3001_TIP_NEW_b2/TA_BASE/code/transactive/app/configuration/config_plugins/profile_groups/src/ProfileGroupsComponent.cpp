/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/configuration/config_plugins/profile_groups/src/ProfileGroupsComponent.cpp $
  * @author:  Derrick Liew
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * This is the component the main Configuration Editor framework communicates with.
  * It implements the IConfigurableComponent interface. It will handle all toolbar and menu
  * requests and handle them appropriately.
  */

#pragma warning(disable:4786)

#include <sstream>

#include "app/configuration/config_plugins/profile_groups/src/ProfileGroupsComponent.h"
#include "app/configuration/config_plugins/profile_groups/src/resource.h"
#include "app/configuration/config_plugins/profile_groups/src/ProfileGroupsFrameworkView.h"
#include "app/configuration/config_plugins/profile_groups/src/ProfileGroupsDatabaseAccessor.h"

#include "bus/resources/resource.h"

#include "core/utilities/src/DebugUtil.h"

using TA_Base_Core::DebugUtil;

namespace TA_Base_App
{
    // This is the name of the DLL and is used to load resources correctly.
    const CString ProfileGroupsComponent::DLL_NAME = "TA_ProfileGroupsConfigPlugin.dll";


    ProfileGroupsComponent::ProfileGroupsComponent(const std::string& componentName)
        : m_icon(NULL),
         AbstractComponent(componentName, new ProfileGroupsDatabaseAccessor())
    {
        m_icon = LoadIcon(GetModuleHandle(DLL_NAME), MAKEINTRESOURCE(IDI_CONFIG_PROFILE) );
    }


    ProfileGroupsComponent::~ProfileGroupsComponent()
    {
        FUNCTION_ENTRY("Destructor");

        try
        {
        }
        catch ( ... )
        {
            LOG( SourceInfo, DebugUtil::ExceptionCatch, "Unknown", "Caught in destructor");
        }

        FUNCTION_EXIT;
    }


    HICON ProfileGroupsComponent::getIcon()
    {
        FUNCTION_ENTRY("getIcon");
        FUNCTION_EXIT;
        return m_icon;
    }


    CRuntimeClass* ProfileGroupsComponent::getComponentView()
    {
        return RUNTIME_CLASS(ProfileGroupsFrameworkView);
    }


    std::string ProfileGroupsComponent::getDLLName() const
    {
        return std::string(DLL_NAME);
    }


}
