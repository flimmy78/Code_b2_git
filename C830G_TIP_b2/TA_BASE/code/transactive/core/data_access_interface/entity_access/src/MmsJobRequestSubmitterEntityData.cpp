/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/4669_T01271350/TA_BASE/transactive/core/data_access_interface/entity_access/src/MmsJobRequestSubmitterEntityData.cpp $
  * @author Gregg Kirkpatrick
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by: $Author: builder $
  * 
  * Implementataion of   MmsJobRequestSubmitterEntityData.
  */

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif // defined _MSC_VER

#include "core/data_access_interface/entity_access/src/MmsJobRequestSubmitterEntityData.h"
#include "core/data_access_interface/src/IData.h"

#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/DebugUtil.h"

using TA_Base_Core::DebugUtil;

namespace TA_Base_Core
{

    const std::string MmsJobRequestSubmitterEntityData::ENTITY_TYPE = "MmsJobRequestSubmitter";

    MmsJobRequestSubmitterEntityData::MmsJobRequestSubmitterEntityData(unsigned long key) 
        : EntityData(key,getStaticType())
    {
    }

    MmsJobRequestSubmitterEntityData::~  MmsJobRequestSubmitterEntityData()
    { // Nothing to clean up
    }

    IEntityData* MmsJobRequestSubmitterEntityData::clone(unsigned long key)
    {
        return new   MmsJobRequestSubmitterEntityData(key);        
    }

    void MmsJobRequestSubmitterEntityData::invalidate()
    {
		getHelper()->invalidate();
    }


    std::string MmsJobRequestSubmitterEntityData::getType()
    {
        return getStaticType();
    }
	
    std::string MmsJobRequestSubmitterEntityData::getStaticType()
    {
        return ENTITY_TYPE;
    }
}
