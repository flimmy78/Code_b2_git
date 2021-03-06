/**
 * The source code in this file is the property of
 * Ripple Systems and is not for redistribution in any form.
 * 
 * Source:    $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/security/duty_agent/src/TransferableSubsystemStateConverter.h $
 * @author:   Gregg Kirkpatrick
 * @version:  $Revision: #2 $
 *
 * Last modification: $DateTime: 2012/02/06 16:15:14 $
 * Last modified by:  $Author: haijun.li $
 *
 * Converts DutyState to a list of transferable subsystems suitable for sending to
 * the duty manager.
 */

#if !defined(TRANSFERABLESUBSYSTEMSTATECONVERTER_H_INCLUDED)
#define TRANSFERABLESUBSYSTEMSTATECONVERTER_H_INCLUDED

namespace TA_Base_App
{
	class TransferableSubsystemStateConverter : public TA_Base_Bus::IDutyStateConverter
	{

	public:

		TransferableSubsystemStateConverter();

		TA_Base_Bus::DutyAgentTypeCorbaDef::TransferableSubsystemSequence* getResult();
		
		virtual void setSession(const std::string& session);
		virtual void setAction(const std::string& action);
	
		virtual void setRegionCount( unsigned long count );

		virtual void setRegion(const TA_Base_Bus::DASType::DbKey& region);
		
		virtual void setSubsystemCount( unsigned long count );

		virtual void setSubsystem(const TA_Base_Bus::DASType::DbKey& subsystem,
			const TA_Base_Bus::SubsystemState::State& addState, const TA_Base_Bus::SubsystemState::State& remState );
		
		virtual void setRegionAddCount   ( unsigned long count );
		virtual void setRegionRemoveCount( unsigned long count );

		virtual void regionAdd(const TA_Base_Bus::DutyPrimitive& session);
		
		virtual void regionRemove(const TA_Base_Bus::DutyPrimitive& session);
		
		virtual void setSubsystemAddCount    ( unsigned long count );
		virtual void setSubsystemRemoveCount ( unsigned long count );

		virtual void subsystemAdd(const TA_Base_Bus::DutyPrimitive& session);
	
		virtual void subsystemRemove(const TA_Base_Bus::DutyPrimitive& session);
	
		virtual void subsystemDeny(const TA_Base_Bus::DutyPrimitive& session);
	
		virtual void subsystemTimeout(const TA_Base_Bus::DutyPrimitive& session);

		virtual void subsystemComplete();
		virtual void regionComplete();

	private:
		TA_Base_Bus::DutyAgentTypeCorbaDef::TransferableSubsystemSequence_var m_subsystemSequence;

		CORBA::ULong   m_index;
		TA_Base_Bus::DASType::DbKey m_region;
		TA_Base_Bus::DASType::DbKey m_subsystem;

		unsigned long m_addCount;
		unsigned long m_remCount;

		unsigned long m_added;
	};
}

#endif // !defined(TRANSFERABLESUBSYSTEMSTATECONVERTER_H_INCLUDED)
