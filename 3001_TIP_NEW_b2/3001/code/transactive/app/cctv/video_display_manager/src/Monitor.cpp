/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/cctv/video_display_manager/src/Monitor.cpp $
  * @author:  Adam Radics
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  *
  * This is used to locally store state and association information
  * so it can easily be retrieved for displaying in the GUI.
  */


#include "Monitor.h"
#include "core/utilities/src/FunctionEntry.h"

namespace TA_IRS_App
{

	Monitor::Monitor( unsigned long entityKey,
		const std::string& name,
		const std::string& description,
		const std::string& addr,
		unsigned int displayOrder,
		unsigned long consoleKey,
		bool isOverallMonitor)
		: VideoOutput(entityKey, name, description),
		m_address(addr),
		m_displayOrder(displayOrder),
		m_consoleKey(consoleKey),
		m_isConsoleMonitor((consoleKey>0&&!isOverallMonitor)?true:false),
		m_isOverallMonitor(isOverallMonitor)
	{
		FUNCTION_ENTRY( "Monitor" );
		FUNCTION_EXIT;
	}


	bool Monitor::isConsoleMonitor()
	{
		FUNCTION_ENTRY( "isConsoleMonitor" );

		// no setter - no need to lock
		FUNCTION_EXIT;
		return m_isConsoleMonitor;
	}

	bool Monitor::isOverAllMonitor()
	{
		FUNCTION_ENTRY( "isOverAllMonitor" );

		// no setter - no need to lock
		FUNCTION_EXIT;
		return m_isOverallMonitor;
	}

	std::string Monitor::getAddress()
	{
		FUNCTION_ENTRY( "getDisplayOrder" );

		// no setter - no need to lock
		FUNCTION_EXIT;
		return m_address;
	}

	unsigned int Monitor::getDisplayOrder()
	{
		FUNCTION_ENTRY( "getDisplayOrder" );

		// no setter - no need to lock
		FUNCTION_EXIT;
		return m_displayOrder;
	}

	unsigned long Monitor::getConsoleKey()
	{
		FUNCTION_ENTRY( "getConsoleKey" );

		// no setter - no need to lock
		FUNCTION_EXIT;
		return m_consoleKey;
	}

}

