/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/TA_Common_V1_TIP/transactive/bus/security/duty_agent/duty_agent_state/src/AgentTerminateSubject.cpp $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2015/01/19 17:43:23 $
  *  Last modified by:  $Author: CM $
  *
  *  Implements AgentTerminateSubject.
  */

#include "DutyAgentState.h"

namespace TA_Base_Bus
{
	void AgentTerminateSubjectImpl::update()
	{
		notify(*this);
	}
}
