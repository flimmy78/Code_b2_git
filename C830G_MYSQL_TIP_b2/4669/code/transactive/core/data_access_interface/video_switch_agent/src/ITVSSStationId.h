/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/3001_TIP/3001/transactive/core/data_access_interface/video_switch_agent/src/ITVSSStationId.h $
  * @author Zhang hongzhi
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2015/02/05 13:35:44 $
  * Last modified by: $Author: builder $
  * 
  * ITVSSStationId is an interface to an TVSSStationId object. It allows the TVSSStationId object implementation
  * to be chagned (e.g. if necessary due to a database schema change) without changing code
  * that uses it.
  */

#if !defined(ITVSSStationId_34315582_B0A7_4100_BD60_2E13958D7501__INCLUDED_)
#define ITVSSStationId_34315582_B0A7_4100_BD60_2E13958D7501__INCLUDED_

#include <string>
#include <vector>

#include "core/data_access_interface/src/IItem.h"

namespace TA_IRS_Core
{
    class ITVSSStationId : public virtual TA_Base_Core::IItem
    {

    public:

        virtual unsigned long getStationId() =0;
        virtual unsigned long getTaLocation() =0;
        
        virtual ~ITVSSStationId() {};

        /**
         * invalidate
         *
         * Make the data contained by this item as invalid. The next call to get...() 
         * following a call to invalidate() will cause all the data to be reloaded from
         * the database.
         */
        virtual void invalidate() =0;

    };


    typedef std::vector<ITVSSStationId*> ITVSSStationIds;
    typedef ITVSSStationIds::iterator    ITVSSStationIdsIt;
} //close namespace TA_IRS_Core

#endif // !defined(ITVSSStationId_34315582_B0A7_4100_BD60_2E13958D7501__INCLUDED_)
