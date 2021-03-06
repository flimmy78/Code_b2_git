/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/4669_Review_Branch/TA_BASE/transactive/bus/alarm/alarm_list_control/src/columns/ColumnMms.cpp $
 * @author:  Karen Graham
 * @version: $Revision: #4 $
 *
 * Last modification: $DateTime: 2011/05/27 12:16:41 $
 * Last modified by:  $Author: huirong.luo $
 * 
 * This class provides all the information for the MMS column.
 */

#include "bus/alarm/alarm_list_control/src/StdAfx.h"
#include "bus/alarm/alarm_list_control/src/columns/ColumnMms.h"

#include "core/utilities/src/TAAssert.h"
#include "core/alarm/IDL/src/AlarmUpdateCorbaDef.h"
#include "core/utilities/src/DebugUtil.h"
#include "bus/alarm/alarm_store_library/src/LogAlarmItem.h"

using TA_Base_Core::DebugUtil;
namespace TA_Base_Bus
{
    ColumnMms::ColumnMms(int width,
                         bool isEnabled,
                         SORT_COLUMN sortCol,
                         IAlarmAction* doubleClickAction)
     : AbstractAlarmColumn(width, sortCol, isEnabled, doubleClickAction)
    {
    }

	const std::string ColumnMms::getItemText(AlarmVectorWrap* pAlarmWrap, unsigned long ulIndex)
	{
		try
		{
			return pAlarmWrap->getItemString(ulIndex, MMS_STATE);
		}
		catch(...)
		{ 
 			LOG_GENERIC(SourceInfo, DebugUtil::DebugError, "wrong");
			
		}
		return "";
			//Utilities::getInstance().getMMSDisplayString(alarm).c_str();
    }


} //End of TA_Base_Bus

