/**
  * The source code in this file is the property of
  * MI Services Group and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/GZL6_TIP/3002/transactive/app/trains/train_agent/src/TrainBarrier.cpp $
  * @author:  zhou yuan
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2012/06/12 13:35:44 $
  * Last modified by:  $Author: builder $
  *
  *
  */

#ifdef __WIN32__
#pragma warning(disable:4250 4503)
#endif

#include "core/utilities/src/DebugUtil.h"

#include "app/trains/train_agent/src/TrainBarrier.h"

namespace TA_IRS_App
{
	TrainBarrier::TrainBarrier(int boundary/* =1 */)
	:m_semaphore(0),
	 m_counter(0),
	 m_boundary(boundary)
	{
		FUNCTION_ENTRY("TrainBarrier::TrainBarrier");
		FUNCTION_EXIT;
	}


	TrainBarrier::~TrainBarrier()
	{
		FUNCTION_ENTRY("TrainBarrier::~TrainBarrier");
		TA_Base_Core::ThreadGuard guard(m_counterLock);
		FUNCTION_EXIT;
	}

	void TrainBarrier::post()
	{
		FUNCTION_ENTRY("TrainBarrier::post");

		TA_Base_Core::ThreadGuard guard(m_counterLock);
		++m_counter;
		
		if(m_counter >= m_boundary)
		{
			m_semaphore.post();
		}

		FUNCTION_EXIT;
	}

	void TrainBarrier::wait()
	{
		FUNCTION_ENTRY("TrainBarrier::wait");
		
		m_semaphore.wait();

		FUNCTION_EXIT;
	}
}