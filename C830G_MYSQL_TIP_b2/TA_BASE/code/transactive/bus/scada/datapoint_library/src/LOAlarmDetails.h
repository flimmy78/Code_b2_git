/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source : $File: //depot/4669_T01271350/TA_BASE/transactive/bus/scada/datapoint_library/src/LOAlarmDetails.h $
  * @author  J. Welton
  * @version $Revision: #1 $
  * Last modification : $DateTime: 2008/11/28 16:26:01 $
  * Last modified by : $Author: builder $
  *
  *
  *	Represents an alarm condition for a LO alarm value
  *
  *
  */

#ifndef LOALARMDETAILS_H
#define LOALARMDETAILS_H

#include "bus/scada/datapoint_library/src/AnalogueAlarmDetails.h"

namespace TA_Base_Bus
{

	class LOAlarmDetails : public AnalogueAlarmDetails
	{
	public:

		/**
		 * LOAlarmDetails::LOAlarmDetails()
		 *
		 * @param   dpEntityKey     the pkey for the DataPoint entity that this
		 *                          alarm pertains to
		 *
		 * @param   almEnabled      whether or not to process this alarm
		 *
		 * @param   almDelay        the alarm state must persist for this period
		 *                          of time (in seconds) before an alarm is
		 *                          generated
		 *
		 * @param   almSeverity     the severity of alarms generated as a result
		 *                          of this alarm condition
		 *
		 * @param   almMessage      the message of alarms generated as a result
		 *                          of this alarm condition
		 *
		 * @param   almValue        the value that defines this alarm condition
		 *
		 */
		LOAlarmDetails( TA_Base_Core::DataPointEntityDataPtr dataPointEntityAccess,
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
                        MmsScadaUtility &   mmsScadaUtility );
        
        virtual ~LOAlarmDetails();

		virtual std::string getAlarmTypeStr();
	
	protected:

	   /*
		* LOAlarmDetails::inAlarm()
		*
		* Determines whether a DataPointState constitutes an alarm
		* state or not.
		*
		* @param state     the state to be tested
		*
		*/
		virtual bool inAlarm( const DataPointState & state );
	private:

	};

}

#endif
