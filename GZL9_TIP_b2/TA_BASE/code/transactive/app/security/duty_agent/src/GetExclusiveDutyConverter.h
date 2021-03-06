/**
 * The source code in this file is the property of
 * Ripple Systems and is not for redistribution in any form.
 * 
 * Source:    $File: //depot/GZL6_TIP/TA_BASE/transactive/app/security/duty_agent/src/GetExclusiveDutyConverter.h $
 * @author:   Gregg Kirkpatrick
 * @version:  $Revision: #1 $
 *
 * Last modification: $DateTime: 2012/06/12 13:35:44 $
 * Last modified by:  $Author: builder $
 *
 * Converts DutyState to a sequence of Duty Manager updates..
 */

#if !defined(GETEXCLUSIVEDUTYCONVERTER_H_INCLUDED)
#define GETEXCLUSIVEDUTYCONVERTER_H_INCLUDED

namespace TA_Base_App
{
	class GetExclusiveDutyConverter : public TA_Base_Bus::IDutyStateConverter
	{

	public:

		GetExclusiveDutyConverter();

		TA_Base_Bus::DutyAgentTypeCorbaDef::SubsystemTreeSequence* getSubsystems();
		bool getResult() const;
		
		virtual void setSession(const std::string& session);
		virtual void setAction(const std::string& action);
	
		virtual void setRegionCount( unsigned long count );

		virtual void setRegion(const TA_Base_Bus::DASType::DbKey& region);
		
		virtual void setSubsystemCount( unsigned long count );

		virtual void setSubsystem(const TA_Base_Bus::DASType::DbKey& subsystem,
			const TA_Base_Bus::SubsystemState::State& addState, const TA_Base_Bus::SubsystemState::State& remState );
		
		virtual void setRegionAddCount   ( unsigned long count );
		virtual void setRegionRemoveCount( unsigned long count );

		virtual void regionAdd   ( const TA_Base_Bus::DutyPrimitive& session );
		virtual void regionRemove( const TA_Base_Bus::DutyPrimitive& session );
		
		virtual void setSubsystemAddCount    ( unsigned long count );
		virtual void setSubsystemRemoveCount ( unsigned long count );

		virtual void subsystemAdd    ( const TA_Base_Bus::DutyPrimitive& session );
		virtual void subsystemRemove ( const TA_Base_Bus::DutyPrimitive& session );
		virtual void subsystemDeny   ( const TA_Base_Bus::DutyPrimitive& session );
		virtual void subsystemTimeout( const TA_Base_Bus::DutyPrimitive& session );

		virtual void subsystemComplete();
		virtual void regionComplete();

	private:

		TA_Base_Bus::DutyAgentTypeCorbaDef::SubsystemTreeSequence_var m_subsystems;

		CORBA::ULong m_regIdx;
		CORBA::ULong m_subIdx;

		bool m_firstRegion;
		bool m_hasDuty;
	};
}

#endif // !defined(GETEXCLUSIVEDUTYCONVERTER_H_INCLUDED)
