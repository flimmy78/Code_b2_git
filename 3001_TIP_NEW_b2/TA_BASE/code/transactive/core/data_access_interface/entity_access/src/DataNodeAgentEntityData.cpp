/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/entity_access/src/DataNodeAgentEntityData.cpp $
  * @author:  Karen Graham
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * DataNodeAgentEntityData provide read-only access to DataNodeAgent entity data.
  */

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif // defined _MSC_VER

#include "core/data_access_interface/entity_access/src/DataNodeAgentEntityData.h"
#include "core/data_access_interface/src/IData.h"

namespace TA_Base_Core
{

    const std::string DataNodeAgentEntityData::ENTITY_TYPE = "DataNodeAgent";
	const std::string DataNodeAgentEntityData::ASSET_NAME = "AssetName";
    


	DataNodeAgentEntityData::DataNodeAgentEntityData()
    {
    }


    DataNodeAgentEntityData::DataNodeAgentEntityData ( unsigned long key )
	    : EntityData( key, getStaticType() )
    {
    }


    DataNodeAgentEntityData::~DataNodeAgentEntityData()
    {
    }

    std::string DataNodeAgentEntityData::getAssetName()
	{
		return getHelper()->getParameter(ASSET_NAME);
	}

	std::string DataNodeAgentEntityData::getType()
	{
		return getStaticType();
	}


	std::string DataNodeAgentEntityData::getStaticType()
    {
        return ENTITY_TYPE;
    }


    IEntityData* DataNodeAgentEntityData::clone ( unsigned long key )
    {
        return new DataNodeAgentEntityData ( key );
    }


    void DataNodeAgentEntityData::invalidate()
    {
        getHelper()->invalidate();
    }

} //close namespace TA_Base_Core
