/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  * 
  * Source:    $File: //depot/4669_T01271350/TA_BASE/transactive/app/system_control/system_manager/dummy_agent/src/ProcessIdResolver.h $
  * @author:   Ross Tucker
  * @version:  $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * The ProcessIdResolver simply provides a static method for returning
  * a process Id. The reason it has been separated from the rest of 
  * ManagedProcess is to keep all the operating system specific stuff
  * in the same place.
  */
#if !defined(PROCESSIDRESOLVER)
#define PROCESSIDRESOLVER

namespace TA_Base_Core
{
    class ProcessIdResolver
    {
    public:
        
        /**
          * Destructor
          */
        virtual ~ProcessIdResolver(){}

        /**
          * Static method for returning the process id
          *
          * @return The process id
          *
          * @exception ManagedProcessException thrown if we fail to 
          *            return the process id
          */
        static unsigned long getProcessId();
    };
}
#endif // !defined(PROCESSIDRESOLVER)
