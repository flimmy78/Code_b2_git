/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/ats/ATSSimulatorLibrary/cmd/SetCommand.cpp $
  * @author:  Robert van Hugten
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  * 
  */

#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4284)
#endif // #ifdef WIN32

#include "app/ats/ATSSimulatorLibrary/cmd/SetCommand.h"
#include "app/ats/ATSSimulatorLibrary/cmd/SetTableCommand.h"
#include "app/ats/ATSSimulatorLibrary/cmd/SetTrainCommand.h"
#include "app/ats/ATSSimulatorLibrary/cmd/SetWildCommand.h"
#include "app/ats/ATSSimulatorLibrary/cmd/ShowModeCommand.h"
#include "app/ats/ATSSimulatorLibrary/cmd/SetDssCommand.h"
#include "app/ats/ATSSimulatorLibrary/cmd/SetPlatformCommand.h"
#include "app/ats/ATSSimulatorLibrary/cmd/SetTwpCommand.h"
#include "app/ats/ATSSimulatorLibrary/cmd/SetWatchdogCommand.h"

using namespace TA_IRS_App::ATS_Sim;

SetCommand::SetCommand(CommandOwner * owner) 
: IntermediateCommand(owner, "set")
{
    new SetTableCommand(this);
    new SetTrainCommand(this);
    new SetWildCommand(this);
    new ShowModeCommand(this);
    new SetDssCommand(this);
    new SetPlatformCommand(this);
    new SetTwpCommand(this);
    new SetWatchdogCommand(this);
}

