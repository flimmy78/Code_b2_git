#ifndef DetachCommand_H
#define DetachCommand_H
/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/bus/generic_server_simulator/src/DetachCommand.h $
  * @author:  Robert van Hugten
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2017/10/31 16:21:54 $
  * Last modified by:  $Author: CM $
  * 
  * Declaration file for classes used by GssCommandProcessor to handle sub commands,
  * being 
  */

#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4284)
#endif // #ifdef WIN32

#include "bus/generic_server_simulator/src/LeafCommand.h"

namespace TA_Base_Bus
{
    /** 
      * 
      * 
      */
    class DetachCommand : public LeafCommand
    {
	public:
        DetachCommand(CommandOwner * owner, const char * name);

        bool execute(TokenList & args, const std::string & argstr);

        void usage(const std::string & name) const;

	}; // class DetachCommand

} // namespace TA_Base_Bus

#endif // #ifndef DetachCommand_H
