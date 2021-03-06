#ifndef DEGRADEDAC_H_INCLUDED
#define DEGRADEDAC_H_INCLUDED

/**
 * The source code in this file is the property of
 * Ripple Systems and is not for redistribution in any form.
 * 
 * Source:    $File: //depot/4669_T01271350/TA_BASE/transactive/app/security/duty_agent/src/DegradeDAC.h $
 * @author:   Gregg Kirkpatrick
 * @version:  $Revision: #1 $
 *
 * Last modification: $DateTime: 2008/11/28 16:26:01 $
 * Last modified by:  $Author: builder $
 *
 * The "delegate" command.
 */

#include "IDutyAgentCommand.h"

namespace TA_Base_App
{
    class DegradeDAC : public IDutyAgentCommand
    {
    public:
	
		DegradeDAC( TA_Base_Bus::DutyState& state, TA_Base_Bus::DutyPeerTaskManager& taskManager, 
			const TA_Base_Bus::DASType::SubsystemSet& subsystems, const TA_Base_Bus::DASType::LocationSet& locSet );		

		virtual void execute();

	protected:
		virtual unsigned long getActionKey() const{ return(TA_Base_Bus::aca_DUTY_DEGRADE_SUBSYSTEMS); }
		
	private:

		TA_Base_Bus::DutyState&                   m_state;
		TA_Base_Bus::DutyPeerTaskManager&         m_taskManager;
		const TA_Base_Bus::DASType::SubsystemSet& m_subsystems;
		const TA_Base_Bus::DASType::LocationSet&  m_locSet;
    };
}

#endif // DEGRADEDAC_H_INCLUDED
