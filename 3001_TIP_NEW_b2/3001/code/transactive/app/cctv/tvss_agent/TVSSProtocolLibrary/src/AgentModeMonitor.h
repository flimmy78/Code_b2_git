
#if !defined(AgentModeMonitor_6D856C3B_635C_4e91_8C91_072E38E337FD__INCLUDED_)
#define AgentModeMonitor_6D856C3B_635C_4e91_8C91_072E38E337FD__INCLUDED_

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  *
  * Source:    $File: //depot/3001_TIP/3001/transactive/app/cctv/video_switch_agent/src/AgentModeMonitor.h $
  * @author:   Katherine Thomson
  * @version:  $Revision: #1 $
  *
  * Last modification: $DateTime: 2009/12/29 14:12:57 $
  * Last modified by:  $Author: grace.koh $
  *
  * This class is a singleton which maintains the mode of the agent.
  * All methods that are mode dependent can use the instance of this
  * class to verify that the agent is in Control mode.  
  */

#include <string>

#include "core/synchronisation/src/ReEntrantThreadLockable.h"

namespace TA_IRS_App
{
    class AgentModeMonitor
    {
    public:
		/**
          * getInstance
          *
          * Gets the one and only AgentModeMonitor.
          *
          * @return     AgentModeMonitor&
          *             The only AgentModeMonitor.
          */

		static AgentModeMonitor& getInstance();

        /**
          * ~AgentModeMonitor
          *
          * Standard destructor.
          */

        virtual ~AgentModeMonitor() {};
        
        /**
          * isInControlMode
          *
          * Returns true if the agent is in Control mode.
          *
          * @return     bool
          *             True if the agent is in Control mode.
          *             False otherwise - i.e. if the agent is in Monitor mode.
          */

        bool isInControlMode();
    
        /**
          * setToControlMode
          *
          * Stores that the agent is in Control mode.
          */

        void setToControlMode();

        /**
          * setToMonitorMode
          *
          * Stores that the agent is in Monitor mode.
          */

        void setToMonitorMode();

        /**
          * verifyInControlMode
          *
          * Throws an exception if the agent is not in Control mode.
          * This should be called first within any methods that are
          * mode dependent.
          *
          * @param      const std::string& action
          *             The name of the method that is being performed.
          *             Used in the exception if required.
          *
          * @exception  VideoSwitchAgentException
          *             Thrown if the agent is not in Control mode.
          */

        void verifyInControlMode( const std::string& action );

    private:

        /**
          * AgentModeMonitor
          *
          * Standard constructor.  Declared private because this class is 
          * as singleton.  Use getInstance() to get access to the 
          * single instance of this class.
          */

        AgentModeMonitor();

        //
        // Disable copy constructor and assignment operator.
        //

        AgentModeMonitor( const AgentModeMonitor& theAgentModeMonitor );
        AgentModeMonitor& operator=( const AgentModeMonitor& theAgentModeMonitor );

		//
		// The one and only instance of this class.
		//

		static AgentModeMonitor* m_theClassInstance;
		
		//
        // Protect singleton creation
        //

		static TA_Base_Core::ReEntrantThreadLockable m_singletonLock;

        //
        // Flag indicating if the agent is in Control mode and
        // the lock to guard the flag from simultaneous thread access.
        //
        
        bool m_isInControlMode;        
        TA_Base_Core::ReEntrantThreadLockable m_modeLock;


    }; // AgentModeMonitor

} // TA_IRS_App
    
#endif // !defined(AgentModeMonitor_6D856C3B_635C_4e91_8C91_072E38E337FD__INCLUDED_)
