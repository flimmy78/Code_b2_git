#ifndef ATSTRAINDATATIMER_H
#define ATSTRAINDATATIMER_H

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  * 
  * Source:    $File: //depot/PRIV_3001/3001/transactive/app/ats/AtsAgent/src/AtsTrainDataTimer.h $
  * @author:   zhou yuan
  * @version:  $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last mofified by:  $Author: lim.cy $
  *
  * this time is used for AtsTrainData to update the state of m_oa1Valid and m_atcTrainStatusValid 
  * of AtsTrainData
  *
  */

#ifdef __WIN32__
#pragma warning(disable:4786)
#endif

#include <string>

#include "ace/ACE.h"
#include "ace/Thread_Manager.h"
#include "ace/Timer_Heap.h"
#include "ace/Timer_Queue.h"
#include "ace/Timer_Queue_Adapters.h"

#include "core/synchronisation/src/ReEntrantThreadLockable.h"
#include "core/synchronisation/src/Semaphore.h"
#include "core/threads/src/Thread.h"

namespace TA_IRS_App
{

	enum ETimerType
	{
		AtcTimer,
		Oa1Timer
	};	

    // implemented by classes that use UnsolicitedTrainTimer
    class IAtsTrainDataTimerCallback
    {		
    public:
        virtual void handleTimeout(ETimerType timerType) = 0;
    };


	class AtsTrainDataTimer : public ACE_Event_Handler
	{
		typedef ACE_Thread_Timer_Queue_Adapter<ACE_Timer_Heap> ActiveQueue;
	
		struct TimerItem
        {
            IAtsTrainDataTimerCallback& callback;
			ETimerType timerType;
			
			TimerItem(IAtsTrainDataTimerCallback& theCallback, ETimerType& theTimerType)
			:	callback(theCallback),
				timerType(theTimerType)
			{
			}
		};			

	public:

		AtsTrainDataTimer(long oa1Timeout, long atcTimeout);
		~AtsTrainDataTimer();
	
		/**
		  * startTimer
		  * 
		  * startTimer and return the timer id. 
		  * so late can use the id to delete the timer.
		  * 
		  * @return long 
		  * @param : IAtsTrainDataTimerCallback& callback
		  * @param : ETimerType timerType
		  * @param : long timerId
		  * 
		  * @exception <exceptions> Optional
		  */
		long startTimer(IAtsTrainDataTimerCallback& callback, ETimerType timerType, long timerId);


		/**
		  * endTimer
		  * 
		  * end a time by the timer id 
		  * 
		  * @return void 
		  * @param : long timeId
		  * 
		  * @exception <exceptions> Optional
		  */
        void endTimer(long timerId);


	protected:

		int handle_timeout ( const ACE_Time_Value &tv, const void *constArg );

	protected:

		ActiveQueue m_activeQueue;

		long m_oa1Timeout;
		long m_atcTimeout;
	};
};

#endif // #ifndef ATSTRAINDATATIMER_H

