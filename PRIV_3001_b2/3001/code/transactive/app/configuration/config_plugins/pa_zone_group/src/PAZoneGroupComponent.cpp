/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/configuration/config_plugins/pa_zone_group/src/PAZoneGroupComponent.cpp $
  * @author:  Karen Graham
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  * 
  * This is the component the main Configuration Editor framework communicates with.
  * It implements the IConfigurableComponent interface. It will handle all toolbar and menu
  * requests and handle them appropriately.
  */

#pragma warning(disable:4786 4284)

#include <sstream>

#include "StdAfx.h"
#include "bus/resources/resource.h"

#include "core/utilities/src/DebugUtil.h"

using TA_Base_Core::DebugUtil;

namespace TA_IRS_App
{
    // This is the name of the DLL and is used to load resources correctly.
    const CString PaZoneGroupComponent::DLL_NAME = "TA_PAZoneGroupConfigPlugin.dll";
    const DWORD PaZoneGroupComponent::RIGHTS_ACTION_ID = TA_Base_Bus::aca_CE_CONFIGURE_PA_ZONE_GROUPS;
        
    PaZoneGroupComponent::PaZoneGroupComponent(const std::string& componentName)
        : m_icon(NULL),
         AbstractComponent(componentName, new PaZoneGroupDatabaseAccessor())
    {
        m_icon = LoadIcon(GetModuleHandle(DLL_NAME), MAKEINTRESOURCE(IDI_CONFIG_PA_ZONE_GROUPS) );
    }


    PaZoneGroupComponent::~PaZoneGroupComponent()
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


    HICON PaZoneGroupComponent::getIcon()
    {
        FUNCTION_ENTRY("getIcon");
        FUNCTION_EXIT;
        return m_icon;
    }


    CRuntimeClass* PaZoneGroupComponent::getComponentView()
    {
        return RUNTIME_CLASS(PaZoneGroupFrameworkView);
    }


    std::string PaZoneGroupComponent::getDLLName() const
    {
        return std::string(DLL_NAME);
    }
}
