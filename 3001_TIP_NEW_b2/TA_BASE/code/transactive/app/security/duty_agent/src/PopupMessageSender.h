/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/security/duty_agent/src/PopupMessageSender.h $
  * @author:  Gregg Kirkpatrick
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Listens to FrontEndStateChangeSubject and sends messages for displaying to affected operators.
  *
  */

#ifndef POPUPMESSAGESENDER_H_INCLUDED
#define POPUPMESSAGESENDER_H_INCLUDED

namespace TA_Base_App
{
	class PopupMessageSender : public TA_Base_Bus::SeDutyStateObserver<TA_Base_Bus::FrontEndStateChangeSubjectImpl>,
		                       public TA_Base_Bus::SeObserver<TA_Base_Bus::AgentTerminateSubjectImpl>
	{
	public:
		PopupMessageSender();

		virtual void update( TA_Base_Bus::FrontEndStateChangeSubjectImpl& frontEndStateChange, const TA_Base_Bus::DutyState & state);
		virtual void update( TA_Base_Bus::AgentTerminateSubjectImpl&  terminateUpdate );

	private:

		typedef TA_Base_Bus::SeDutyStateObserver<TA_Base_Bus::FrontEndStateChangeSubjectImpl> FrontEndStateParent;
		typedef TA_Base_Bus::SeObserver<TA_Base_Bus::AgentTerminateSubjectImpl>  AgentTerminateParent;

		std::auto_ptr<TA_Base_Core::CommsMessageSender> m_commsSender;
	};
}
#endif // POPUPMESSAGESENDER_H_INCLUDED
