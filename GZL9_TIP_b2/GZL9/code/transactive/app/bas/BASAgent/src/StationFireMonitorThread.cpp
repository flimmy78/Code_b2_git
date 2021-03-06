/**
  * The source code in this file is the property of ST Electronics and is not for redistribution in
  * any form.
  *
  * Source:		$File: //depot/GZL9_TIP/GZL9/transactive/app/bas/BASAgent/src/StationFireMonitorThread.cpp $
  * @author:	Liu Yong
  * @version:	$Revision: #1 $
  *
  * Last modification:	$DateTime: 2015/02/27 17:12:34 $
  * Last modified by:	$Author: CM $
  *
  * Description:
  *
  *
  */
  
#include "app/bas/BASAgent/src/StationFireMonitorThread.h"
#include "core/utilities/src/DebugUtil.h"
#include "app/bas/BASAgent/src/FireTriggerBasEquipmentManager.h"

namespace TA_IRS_App
{
	using namespace TA_Base_Core;
	StationFireMonitorThread::StationFireMonitorThread(FireTriggerBasEquipmentManager* fireManager)
		: m_stopMonitor(false),
		m_fireTriggerManager(fireManager),
		m_semaphore(0)
	{
		FUNCTION_ENTRY("StationFireMonitorThread");

		FUNCTION_EXIT;
	}


	StationFireMonitorThread::~StationFireMonitorThread()
	{
		FUNCTION_ENTRY("~StationFireMonitorThread");
		FUNCTION_EXIT;
	}

	void StationFireMonitorThread::terminate()
	{
		FUNCTION_ENTRY("terminate");

		m_stopMonitor = true;

		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugDebug,"StationFireMonitorThread::terminate() called");

		FUNCTION_EXIT;
	}

	void StationFireMonitorThread::run()
	{
		FUNCTION_ENTRY("run");
		LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "StationFireMonitorThread::run() called");

		while(!m_stopMonitor )
		{
			TA_Base_Core::Thread::sleep(5*1000);
 
			if (!m_fireTriggerManager->needProcessUnprocessedFireMode())
			{
#if !defined(BAS_TEST_MODE)
				m_semaphore.wait();
#endif
			}

			if (!m_stopMonitor)
			{
				m_fireTriggerManager->processStationFireMode();	
			}			
		}

		FUNCTION_EXIT;
	}

	void StationFireMonitorThread::notifyStationFire()
	{
		m_semaphore.post();
	}

	void StationFireMonitorThread::notifyToQuit()
	{
		m_stopMonitor = true;
	}
}
