/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/entity_access/src/RightsAgentEntityData.cpp $
  * @author Nick Jardine
  * @version $Revision: #2 $
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by: $Author: haijun.li $
  * 
  */

#ifdef __WIN32__
#pragma warning(disable:4786) // disable the "identifier truncated" warning
#endif

#include "core/data_access_interface/entity_access/src/RightsAgentEntityData.h"
#include "core/data_access_interface/src/IData.h"

#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/DebugUtil.h"

using TA_Base_Core::DebugUtil;

namespace TA_Base_Core
{

    const std::string RightsAgentEntityData::ENTITY_TYPE    = "RightsAgent";
	const std::string RightsAgentEntityData::ASSET_NAME = "AssetName";

    RightsAgentEntityData::RightsAgentEntityData(unsigned long key) 
        : EntityData(key,getStaticType())
    {
    }


    RightsAgentEntityData::~RightsAgentEntityData()
    { // Nothing to clean up
    }


    IEntityData* RightsAgentEntityData::clone(unsigned long key)
    {
        return new RightsAgentEntityData(key);        
    }


    void RightsAgentEntityData::invalidate()
    {
		TA_ASSERT(getHelper() != NULL, "The EntityHelper pointer is null");
		getHelper()->invalidate();
    }


    std::string RightsAgentEntityData::getType()
    {
        return getStaticType();
    }


    std::string RightsAgentEntityData::getStaticType()
    {
        return ENTITY_TYPE;
    }


    std::string RightsAgentEntityData::getAssetName()
	{
		TA_ASSERT(getHelper() != NULL, "The EntityHelper pointer is null");
		return getHelper()->getParameter(ASSET_NAME);
	}

} //close namespace TA_Base_Core

