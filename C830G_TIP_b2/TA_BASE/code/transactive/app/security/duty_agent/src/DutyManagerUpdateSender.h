/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_Review_Branch/TA_BASE/transactive/app/security/duty_agent/src/DutyManagerUpdateSender.h $
  * @author:  Gregg Kirkpatrick
  * @version: $Revision: #4 $
  *
  * Last modification: $DateTime: 2011/06/20 18:29:56 $
  * Last modified by:  $Author: shurui.liu $
  *
  * Listens to PeerStateChangeSubject and sends updates to Duty Managers.
  *
  */

#ifndef DUTYMANAGERUPDATESENDER_H_INCLUDED
#define DUTYMANAGERUPDATESENDER_H_INCLUDED

namespace TA_Base_App
{
	class DutyManagerUpdateSender : public TA_Base_Bus::SeDutyStateObserver<TA_Base_Bus::PeerStateChangeSubjectImpl>,
		                            public TA_Base_Bus::SeObserver<TA_Base_Bus::AgentTerminateSubjectImpl>
	{
	public:
		DutyManagerUpdateSender();

		virtual void update( TA_Base_Bus::PeerStateChangeSubjectImpl& peerStateChange , const TA_Base_Bus::DutyState & state);
		virtual void update( TA_Base_Bus::AgentTerminateSubjectImpl&  terminateUpdate );

	private:

		typedef TA_Base_Bus::SeDutyStateObserver<TA_Base_Bus::PeerStateChangeSubjectImpl> PeerStateParent;
		typedef TA_Base_Bus::SeObserver<TA_Base_Bus::AgentTerminateSubjectImpl>  AgentTerminateParent;

		std::auto_ptr<TA_Base_Core::CommsMessageSender> m_commsSender;
	};
}
#endif // DUTYMANAGERUPDATESENDER_H_INCLUDED
