/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/core/data_access_interface/entity_access/src/IStationEntityData.h $
  * @author HoaVu
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2017/10/31 16:21:54 $
  * Last modified by: $Author: CM $
  * 
  * IStationEntity provides read-only access to Station entity data.
  */

#ifndef ISTAION_ENTITY_DATA_H
#define ISTAION_ENTITY_DATA_H

#include "core/data_access_interface/entity_access/src/IEntityData.h"

namespace TA_Base_Core
{

    class IStationEntityData : public virtual IEntityData
    {
    };

} //close namespace TA_Base_Core

#endif

