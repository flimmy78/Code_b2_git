/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/configuration/config_plugins/tis_ratis_destination/src/TisRatisDestinationComponent.cpp $
  * @author:  James
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
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
    // TUpdate: Sets constants as required
    // This is the name of the DLL and is used to load resources correctly.
    const CString TisRatisDestinationComponent::DLL_NAME = "TA_TisRatisDestinationConfigPlugin.dll";
    const DWORD TisRatisDestinationComponent::RIGHTS_ACTION_ID = TA_Base_Bus::aca_CE_CONFIGURE_TIS_RATIS_DESTINATIONS;
        
    TisRatisDestinationComponent::TisRatisDestinationComponent(const std::string& componentName)
        : m_icon(NULL),
         AbstractComponent(componentName, new TisRatisDestinationDatabaseAccessor())
    {
        m_icon = LoadIcon(GetModuleHandle(DLL_NAME), MAKEINTRESOURCE(IDI_CONFIG_TIS_RATIS_DESTINATIONS) );
    }


    TisRatisDestinationComponent::~TisRatisDestinationComponent()
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


    HICON TisRatisDestinationComponent::getIcon()
    {
        FUNCTION_ENTRY("getIcon");
        FUNCTION_EXIT;
        return m_icon;
    }


    CRuntimeClass* TisRatisDestinationComponent::getComponentView()
    {
        return RUNTIME_CLASS(TisRatisDestinationFrameworkView);
    }


    std::string TisRatisDestinationComponent::getDLLName() const
    {
        return std::string(DLL_NAME);
    }
}
