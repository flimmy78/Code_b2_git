/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/configuration/config_plugins/ats_psd_entity_map/src/AtsPsdEntityMapComponent.cpp $
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

#pragma warning(disable:4786)

#include <sstream>

#include "app/configuration/config_plugins/ats_psd_entity_map/src/AtsPsdEntityMapComponent.h"
#include "app/configuration/config_plugins/ats_psd_entity_map/src/resource.h"
#include "app/configuration/config_plugins/ats_psd_entity_map/src/AtsPsdEntityMapFrameworkView.h"
#include "app/configuration/config_plugins/ats_psd_entity_map/src/AtsPsdEntityMapDatabaseAccessor.h"

#include "bus/resources/resource.h"

#include "core/utilities/src/DebugUtil.h"

using TA_Base_Core::DebugUtil;

namespace TA_IRS_App
{
    // This is the name of the DLL and is used to load resources correctly.
    const CString AtsPsdEntityMapComponent::DLL_NAME = "TA_AtsPsdEntityMapConfigPlugin.dll";


    AtsPsdEntityMapComponent::AtsPsdEntityMapComponent(const std::string& componentName)
        : m_icon(NULL),
         AbstractComponent(componentName, new AtsPsdEntityMapDatabaseAccessor())
    {
        m_icon = LoadIcon(GetModuleHandle(DLL_NAME), MAKEINTRESOURCE(IDI_CONFIG_ATS) );
    }


    AtsPsdEntityMapComponent::~AtsPsdEntityMapComponent()
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


    HICON AtsPsdEntityMapComponent::getIcon()
    {
        FUNCTION_ENTRY("getIcon");
        FUNCTION_EXIT;
        return m_icon;
    }


    CRuntimeClass* AtsPsdEntityMapComponent::getComponentView()
    {
        return RUNTIME_CLASS(AtsPsdEntityMapFrameworkView);
    }


    std::string AtsPsdEntityMapComponent::getDLLName() const
    {
        return std::string(DLL_NAME);
    }
}
