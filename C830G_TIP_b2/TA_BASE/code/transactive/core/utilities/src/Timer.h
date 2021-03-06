/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  * 
  * Source:    $File: //depot/4669_T01271350/TA_BASE/transactive/core/utilities/src/Timer.h $
  * @author:   Ross Tucker
  * @version:  $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * This class provides a mechanism of timing operations on both
  * Windows and Solaris.
  */
#if !defined(TIMER)
#define TIMER

#include <time.h>
#include <sys/timeb.h>

namespace TA_Base_Core
{

    class Timer
    {
    public:
        
        /**
          * Constructor
          *
          * Starts the timer.
          */
        Timer();

        /**
          * Destructor
          */
        virtual ~Timer();

        /**
          * restart
          *
          * Restarts the timer. This can be called multiple times to restart the timer
          * as required.
          */
        void restart();

        /**
          * elapsedTime
          *
          * Returns the time elapsed since the timer was (re)started
          *
          * @return The time elapsed since start was called (seconds.milliseconds)
          */
        double elapsedTime();   

    private:

        Timer( const Timer& theTimer);
        Timer& operator=(const Timer&);

        struct timeb m_startTime;
        struct timeb m_endTime;
    };
}

#endif // !defined(TIMER)
