/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source : $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/bus/scada/datapoint_library/src/LOAlarmDetails.cpp $
  * @author  Liang Weimin TD13619
  * @version $Revision: #1 $
  *
  * Last modification: $DateTime: 2017/10/31 16:21:54 $
  * Last modified by:  $Author: CM $
  *
  */

#if defined(_MSC_VER)
#pragma warning(disable : 4786 4503)
#endif // defined _MSC_VER

#include "bus/scada/datapoint_library/src/LOAlarmDetails.h"
#include "bus/scada/datapoint_library/src/DataPoint.h"

#include "core/message/types/DataPointAlarms_MessageTypes.h"

namespace TA_Base_Bus
{
    LOAlarmDetails::LOAlarmDetails( TA_Base_Core::DataPointEntityDataPtr dataPointEntityAccess,
        unsigned long		dpParentEntityKey,
        unsigned long		dpEntityKey,
        unsigned long		dpEntityTypeKey,
        unsigned long		regionKey,
        unsigned long		subsystemKey,
        const std::string & entityName,
        bool				almEnabled,
        int					almDelay,
        int					almSeverity,
        const std::string &	almMessage,
        const std::string &	MMSConfiguration,
        const DpValue &		almValue,
        MmsScadaUtility &   mmsScadaUtility )
                          :
    AnalogueAlarmDetails( dataPointEntityAccess, TA_Base_Core::DataPointAlarms::LO, dpParentEntityKey, dpEntityKey, dpEntityTypeKey, regionKey,
        subsystemKey, entityName, almEnabled, almDelay, almSeverity,
        almMessage, MMSConfiguration,
        TA_Base_Bus::DptLo, almValue, mmsScadaUtility )
    {
    }
    

    LOAlarmDetails::~LOAlarmDetails() 
    {
    }
    
    
	bool LOAlarmDetails::inAlarm( const DataPointState & state )
	{
		//
		// TD 8307: Raise alarm when the dp value crosses the alarm limit and close
		//			the alarm when the dp value is above the alarm threshold
		//
        FUNCTION_ENTRY("inAlarm");
		// save the current alarm state
		bool hasBeenInAlarm = isInAlarm();
		bool inAlarm = true;

		// if current value is less than the HI alarm limit
		if ( state.getValue().getFloat() > getValue().getFloat() )
		{
			// check if the value is below the alarm threshold limit
			// before we can consider the alarm condition is normalised
			inAlarm = false;

			double alarmNormalisedThreshold = getValue().getFloat() + m_alarmThresholdConstant;

			// if the current value is greater/equal the alarm normalised threshold, alarmstatus should be kept.
			//19620++ keep alarm state when the difference is greater than alarmthreshold (not greater or equal)
			//if ( state.getValue().getFloat() >= alarmNormalisedThreshold )
			if ( state.getValue().getFloat() < alarmNormalisedThreshold )
			//++19620	
			{
				inAlarm = hasBeenInAlarm;
			}
		}
		// if there is an upper value limit, then check it.
		else if (true == m_hasOtherLimit)
		{
			// if the current value is larger than VH alarm limit, close alarm, because the VH alarm is triggered
			if ( state.getValue().getFloat() <= getOtherLimitValue().getFloat() )
			{
				inAlarm = false;
			}
			// if the current value is between (VH - threshold) and VH, alarm status will be kept.
			else
			{
				inAlarm = true;
				double alarmOtherLimitNormalisedThreshold = getOtherLimitValue().getFloat() + m_alarmThresholdConstant;

				if ( state.getValue().getFloat() <= alarmOtherLimitNormalisedThreshold )
				{
					//TD15874, keep alarm state only when there is VL/OL already in alarm
					if (m_dataPoint != NULL)
					{
                        if (TA_Base_Bus::DptOverScaleLo == m_dataPoint->getAlarmState() ||
                            TA_Base_Bus::DptLoLo == m_dataPoint->getAlarmState())
						{
							inAlarm = false;
						}
					}
				}
			}
		}

		FUNCTION_EXIT;
		return inAlarm;
	}

		
	std::string LOAlarmDetails::getAlarmTypeStr()
	{
		std::string alarmTypeStr = DPTALM_LO_SHORT;
		
		return alarmTypeStr;
	}

}
