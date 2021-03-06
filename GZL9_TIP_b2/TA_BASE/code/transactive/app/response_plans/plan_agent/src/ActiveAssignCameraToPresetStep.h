#if defined ( STEPTYPE_ACTIVATE_CAMERA_PRESET )

#ifndef ACTIVE_ASSIGN_CAMERA_TO_PRESET_STEP_HEADER_INCLUDED
#define ACTIVE_ASSIGN_CAMERA_TO_PRESET_STEP_HEADER_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File$
  *  @author:  Mahaveer Pareek
  *  @version: $Revision$
  *
  *  Last modification: $DateTime$
  *  Last modified by:  $Author$
  *
  *  <description>
  */

#include "app/response_plans/plan_agent/src/ActiveStep.h"

namespace TA_Base_App
{
	//Class declaration
	class ActiveAssignCameraToPresetStep : public ActiveStep
	{
	// Public methods
	public:
		ActiveAssignCameraToPresetStep( const TA_Base_Core::StepDetail& stepDetail,
            const TA_Base_Core::ActivateCameraPresetParameters& params, IActivePlanFlow& flowControl );
		
	protected:
		virtual TA_Base_Core::EActiveStepState executeImpl( void );

	private:
		ActiveAssignCameraToPresetStep& operator=( const ActiveAssignCameraToPresetStep& );
		ActiveAssignCameraToPresetStep( const ActiveAssignCameraToPresetStep& );

		const TA_Base_Core::ActivateCameraPresetParameters m_params;		
	}; // ActiveCctvStep
}; // TA_Base_App

#endif // ACTIVE_ASSIGN_CAMERA_TO_PRESET_STEP_HEADER_INCLUDED

#endif //  STEPTYPE_CCTV
