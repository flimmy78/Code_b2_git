/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/4669_T01271350/TA_BASE/transactive/core/data_access_interface/entity_access/src/ServerEntityData.cpp $
  * @author Derrick Liew
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by: $Author: builder $
  * 
  *
  */


// ServerEntityData.cpp: implementation of the ServerEntityData class.
//
//////////////////////////////////////////////////////////////////////

#include "core/data_access_interface/entity_access/src/ServerEntityData.h"
#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/DebugUtil.h"

namespace TA_Base_Core
{

    const std::string ServerEntityData::ENTITY_TYPE     = "Server";
	const std::string ServerEntityData::ASSET_NAME = "AssetName";
	
	//////////////////////////////////////////////////////////////////////
	// Construction/Destruction
	//////////////////////////////////////////////////////////////////////

    ServerEntityData::ServerEntityData(unsigned long key) : EntityData(key,getStaticType())
    {
    }

    IEntityData* ServerEntityData::clone(unsigned long key)
    {
        return new ServerEntityData(key);        
    }

    void ServerEntityData::invalidate()
    {
		TA_ASSERT(getHelper() != NULL, "The EntityHelper pointer is null");
		getHelper()->invalidate();
    }

	ServerEntityData::~ServerEntityData()
	{
		// nothing to delete
	}

    std::string ServerEntityData::getType()
    {
        return getStaticType();
    }
	
    std::string ServerEntityData::getStaticType()
    {
        return ENTITY_TYPE;
    }

	std::string ServerEntityData::getAssetName()
	{
		return getHelper()->getParameter(ASSET_NAME);
	}

} // end namespace
