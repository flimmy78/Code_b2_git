/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/4669_T01271350/TA_BASE/transactive/core/data_access_interface/entity_access/src/EquipmentEntityData.cpp $
  * @author HoaVu
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by: $Author: builder $
  * 
  * EquipmentEntityData provides read-only access to Equipment entity 
  */

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif // defined _MSC_VER

#include "core/data_access_interface/entity_access/src/EquipmentEntityData.h"

namespace TA_Base_Core
{
    const std::string EquipmentEntityData::ENTITY_TYPE = "Equipment";

	EquipmentEntityData::EquipmentEntityData()
    {
    }

	
    EquipmentEntityData::EquipmentEntityData ( unsigned long key )
	:
	EntityData( key, getStaticType() )
    {
    }

    EquipmentEntityData::~EquipmentEntityData()
    {
    }

	std::string EquipmentEntityData::getType()
	{
        return getStaticType();
	}

    std::string EquipmentEntityData::getStaticType()
    {
        return ENTITY_TYPE;
    }

    IEntityData* EquipmentEntityData::clone ( unsigned long key )
    {
        return new EquipmentEntityData ( key );
    }

    void EquipmentEntityData::invalidate()
    {
        getHelper()->invalidate();
    }


} //close namespace TA_Base_Core
