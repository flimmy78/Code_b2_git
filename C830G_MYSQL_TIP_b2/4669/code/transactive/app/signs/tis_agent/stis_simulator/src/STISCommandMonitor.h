#ifndef STIS_COMMAND_MONITOR_H
#define STIS_COMMAND_MONITOR_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/signs/tis_agent/stis_simulator/src/STISCommandMonitor.h $
  * @author:  Robin Ashcroft
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * CommandMonitor provides a new thread for the simulator, to listen for and 
  * respond to user commands in runtime.
  */
#pragma warning(disable : 4786)

#include "bus/generic_server_simulator/src/CommandMonitor.h"

namespace TA_IRS_App
{
	class STISCommandMonitor : public TA_Base_Bus::CommandMonitor
	{
	public:
		STISCommandMonitor(const std::string& desc, TA_Base_Bus::GenericSimulator *simulator);
		
		virtual ~STISCommandMonitor();

		// Override this method to create the supported simulation classes
		virtual TA_Base_Bus::ISimulationModule* createSimulationModule(const std::string& type,
																  const std::string& name,
																  const std::string& parameters);
	};
}

#endif // !defined(AFX_COMMANDMONITOR_H__BE504C32_681F_438D_96C1_F48F87F3FEF7__INCLUDED_)

