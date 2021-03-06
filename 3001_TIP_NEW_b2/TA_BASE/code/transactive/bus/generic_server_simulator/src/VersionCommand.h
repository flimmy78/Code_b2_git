#ifndef VersionCommand_H
#define VersionCommand_H
/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/generic_server_simulator/src/VersionCommand.h $
  * @author:  Robert van Hugten
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
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
    class VersionCommand : public LeafCommand
    {
	public:
        VersionCommand(CommandOwner * owner);

        bool execute(TokenList & args, const std::string & argstr);

        void usage(const std::string & name) const;

	}; // class VersionCommand

} // namespace TA_Base_Bus

#endif // #ifndef VersionCommand_H
