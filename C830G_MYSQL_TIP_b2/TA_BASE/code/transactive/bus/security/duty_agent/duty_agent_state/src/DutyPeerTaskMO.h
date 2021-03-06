/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/bus/security/duty_agent/duty_agent_state/src/DutyPeerTaskMO.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #2 $
  *
  *  Last modification: $DateTime: 2010/03/19 10:26:04 $
  *  Last modified by:  $Author: builder $
  *
  *  A base class for DutyPeerTask method objects that encapsulates the error
  *  handling.
  */

#ifndef DUTYPEERTASKMO_H_INCLUDED
#define DUTYPEERTASKMO_H_INCLUDED

namespace TA_Base_Bus
{
	class DutyPeerTask;
}

namespace TA_Base_Bus
{
	//Class declaration
	class DutyPeerTaskMO : public ACE_Method_Request
	{
	// Public methods
	public:
		DutyPeerTaskMO( const ACE_Future<bool>& future );
		virtual int call();

	protected:

		virtual void execute() = 0;

	private:

		DutyPeerTaskMO& operator=( const DutyPeerTaskMO& );
		DutyPeerTaskMO( const DutyPeerTaskMO& );

		ACE_Future<bool> m_future;

		static unsigned long getTimeOutSeconds();
		static const unsigned long MAX_PEER_TIMEOUT;
		static const unsigned long TIME_OF_FLIGHT;
		static unsigned long m_timeout;  //maximum time value second;
		unsigned long  m_createtime;     //created time of the task;
	}; 
} // TA_Base_Bus

#endif //DUTYPEERTASKMO_H_INCLUDED
