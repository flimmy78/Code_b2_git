#ifndef LogModeCommand_H
#define LogModeCommand_H
/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/ats/ATSSimulatorLibrary/cmd/LogModeCommand.h $
  * @author:  Robert van Hugten
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * Declaration file for classes used by ATSSimulator to handle sub commands,
  * being 
  */

#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4284)
#endif // #ifdef WIN32

#include "app/ats/ATSSimulatorLibrary/cmd/LeafCommand.h"

namespace TA_IRS_App
{
namespace ATS_Sim
{
    class ATSSimulatorCommandProcessor;

    /** 
      * 
      * 
      */
    class LogModeCommand : public LeafCommand
    {
	public:
        LogModeCommand(CommandOwner * owner);

        bool makeQuery(TokenList & args, const std::string & argstr, UserQuery * query, LocationType location, std::ostream & err);

        void usage(const std::string & name, std::ostream & os) const;
	
	}; // class ShowTableSubCommand

} // namespace ATS_Sim
} // namespace TA_IRS_App

#endif // #ifndef LogModeCommand_H
