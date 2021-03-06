/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/core/event_processing/src/ProcessCommand.cpp $
  * @author:  Bradley Cleaver
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * The ProcessCommand is used to invoke all processors on the given event.
  *
  */

#ifdef __WIN32__
#pragma warning(disable:4786)
#endif

#include "core/event_processing/src/CommandScheduler.h"
#include "core/event_processing/src/IEventProcessor.h"
#include "core/event_processing/src/ProcessCommand.h"
#include "core/event_processing/src/RetryCommand.h"
#include "core/synchronisation/src/ThreadReadGuard.h"
#include "core/utilities/src/DebugUtil.h"

namespace
{
    const unsigned long NO_DELAY(0);
};

namespace TA_Base_Core
{
    ProcessCommand::ProcessCommand( Event& event, std::vector<IEventProcessor*>& processorList,
        WriteReadThreadLockable& processorListLock ) : AbstractCommand(NO_DELAY),
        m_event(event), m_processorList(processorList), m_processorListLock(processorListLock)
    {
    }


    ProcessCommand::~ProcessCommand()
    {
    }


    void ProcessCommand::execute( CommandScheduler& queue )
    {
        FUNCTION_ENTRY( "execute" );

        // Get a read lock on the list of processors.
        ThreadReadGuard guard( m_processorListLock );

        std::vector<IEventProcessor*>::iterator processorIt;
        for ( processorIt=m_processorList.begin(); processorIt!=m_processorList.end(); processorIt++ )
        {
            // Process the event.
            if ( !(*processorIt)->processEvent( m_event ) )
            {
                // If it failed and the processor wants to retry, create a retry command
                // and add it back into the processing queue.
                unsigned char retryCount = (*processorIt)->getNumRetries();
                if ( 0 < retryCount )
                {
                    AbstractCommand* command = new RetryCommand( m_event, **processorIt, retryCount-1,
                        (*processorIt)->getRetryDelay() );
                    queue.push( command );
                }
            }
        }

        FUNCTION_EXIT;
    }
};
