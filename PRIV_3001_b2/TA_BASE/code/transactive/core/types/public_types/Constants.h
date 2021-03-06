#ifndef Public_Constants_01_03_2005
#define Public_Constants_01_03_2005

/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/core/types/public_types/Constants.h $
  * @author:  
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * Contains public constants
  */

#include <sys/timeb.h>

namespace TA_Base_Core
{
    /**
     * The default time to use on alarms and events.
     */
    const timeb defaultTime = {0,0,-1,-1};

    enum EDataPointQuality
    {
	    /**
	     * Mapped to DataPointStatus - QUALITY_GOOD_NO_SPECIFIC_REASON
	     */
	    ITA_QUALITY_GOOD = 192,
	    /**
	     * Mapped to DataPointStatus - QUALITY_BAD_NO_SPECIFIC_REASON.
	     */
	    ITA_QUALITY_BAD = 0
    };

}

#endif //Public_Type_Defs_01_03_2005
