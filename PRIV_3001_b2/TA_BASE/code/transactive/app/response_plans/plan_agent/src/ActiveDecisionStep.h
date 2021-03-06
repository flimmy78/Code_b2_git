#if defined ( STEPTYPE_DECISION )

#ifndef ACTIVEDECISIONSTEP_H_INCLUDED
#define ACTIVEDECISIONSTEP_H_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/response_plans/plan_agent/src/ActiveDecisionStep.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2018/03/14 13:51:20 $
  *  Last modified by:  $Author: lim.cy $
  *
  *  <description>
  */

#include "app/response_plans/plan_agent/src/ActiveStep.h"
#include "app/response_plans/plan_agent/src/IDecisionStep.h"

namespace TA_Base_App
{
	//Class declaration
	class ActiveDecisionStep : public ActiveStep, public IDecisionStep
	{
	// Public methods
	public:
		ActiveDecisionStep( const TA_Base_Core::StepDetail& stepDetail, const TA_Base_Core::DecisionParameters& params, IActivePlanFlow& flowControl );

        virtual TA_Base_Core::StepNumber getNextDecisionStep(const int status);

	protected:
		virtual TA_Base_Core::EActiveStepState executeImpl( void );

	private:
		ActiveDecisionStep& operator=( const ActiveDecisionStep& );
		ActiveDecisionStep( const ActiveDecisionStep& );

		const TA_Base_Core::DecisionParameters m_params;
	}; // ActiveDecisionStep
}; // TA_Base_App

#endif // ACTIVEDECISIONSTEP_H_INCLUDED


#endif //  STEPTYPE_DECISION

