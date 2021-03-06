#if defined ( STEPTYPE_STATION_TRAVELLER_INFO_SYSTEM )

#ifndef ACTIVESTATIONTISSTEP_H_INCLUDED
#define ACTIVESTATIONTISSTEP_H_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/response_plans/plan_agent/src/ActiveStationTisStep.h $
  *  @author:  Bart Golab
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2018/03/14 13:51:20 $
  *  Last modified by:  $Author: lim.cy $
  *
  *  Represents a Station Traveller Info System step in an executing plan.
  */

#include "app/response_plans/plan_agent/src/ActiveStep.h"

namespace TA_Base_App
{
	//Class declaration
	class ActiveStationTisStep : public ActiveStep
	{
	// Public methods
	public:
        ActiveStationTisStep(const TA_Base_Core::StepDetail& stepDetail,
            const TA_Base_Core::StationTravellerInfoSystemParameters& params, IActivePlanFlow& flowControl);

	protected:
        virtual TA_Base_Core::EActiveStepState executeImpl( void );

	private:
        ActiveStationTisStep& operator=( const ActiveStationTisStep& );
        ActiveStationTisStep( const ActiveStationTisStep& );

        const TA_Base_Core::StationTravellerInfoSystemParameters m_params;
	}; // ActiveStationTisStep
}; // TA_Base_App

#endif // ACTIVESTATIONTISSTEP_H_INCLUDED

#endif //  STEPTYPE_STATION_TRAVELLER_INFO_SYSTEM
