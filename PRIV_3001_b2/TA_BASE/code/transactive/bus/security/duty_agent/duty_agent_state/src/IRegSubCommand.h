/**
 * The source code in this file is the property of
 * Ripple Systems and is not for redistribution in any form.
 * 
 * Source:    $File: //depot/PRIV_3001/TA_BASE/transactive/bus/security/duty_agent/duty_agent_state/src/IRegSubCommand.h $
 * @author:   Gregg Kirkpatrick
 * @version:  $Revision: #1 $
 *
 * Last modification: $DateTime: 2018/03/14 13:51:20 $
 * Last modified by:  $Author: lim.cy $
 *
 * Base class for the command pattern for a Region or Subsystem. The command pattern is used
 * to allow the calling class to parameterise the passing on of commands to a list
 * of objects (thus limiting code duplication).
 */

#ifndef IREGSUBCOMMAND_H_INCLUDED
#define IREGSUBCOMMAND_H_INCLUDED

namespace TA_Base_Bus
{
	template< class RegSub >
    class IRegSubCommand
    {
    public:
		
		virtual ~IRegSubCommand(){}

		virtual void execute(RegSub& regSub, bool doApply) = 0;
    };
}

#endif // IREGSUBCOMMAND_H_INCLUDED
