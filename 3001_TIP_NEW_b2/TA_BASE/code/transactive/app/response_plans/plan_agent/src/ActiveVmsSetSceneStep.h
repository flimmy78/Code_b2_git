#if defined ( STEPTYPE_VMS_SET_SCENE )

#ifndef ACTIVE_VMS_SET_SCENE_STEP_HEADER_INCLUDED
#define ACTIVE_VMS_SET_SCENE_STEP_HEADER_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/response_plans/plan_agent/src/ActiveVmsSetSceneStep.h $
  *  @author:  Mahaveer Pareek
  *  @version: $Revision: #3 $
  *
  *  Last modification: $DateTime: 2012/12/27 15:59:31 $
  *  Last modified by:  $Author: qi.huang $
  *
  *  <description>
  */

#include "app/response_plans/plan_agent/src/ActiveStep.h"

namespace TA_Base_App
{
	//Class declaration
	class ActiveVmsSetSceneStep : public ActiveStep
	{
	// Public methods
	public:
		ActiveVmsSetSceneStep( const TA_Base_Core::StepDetail& stepDetail,
            const TA_Base_Core::VmsSetSceneParameters& params, IActivePlanFlow& flowControl );

	protected:
		virtual TA_Base_Core::EActiveStepState executeImpl( void );

	private:
		ActiveVmsSetSceneStep& operator=( const ActiveVmsSetSceneStep& );
		ActiveVmsSetSceneStep( const ActiveVmsSetSceneStep& );

		const TA_Base_Core::VmsSetSceneParameters m_params;
	}; // ActiveVmsSetSceneStep
}; // TA_Base_App

#endif // ACTIVE_VMS_SET_SCENE_STEP_HEADER_INCLUDED

#endif //  STEPTYPE_VMS_SET_SCENE
