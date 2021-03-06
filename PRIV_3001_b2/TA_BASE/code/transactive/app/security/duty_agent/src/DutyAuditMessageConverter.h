/**
 * The source code in this file is the property of
 * Ripple Systems and is not for redistribution in any form.
 * 
 * Source:    $File: //depot/PRIV_3001/TA_BASE/transactive/app/security/duty_agent/src/DutyAuditMessageConverter.h $
 * @author:   Gregg Kirkpatrick
 * @version:  $Revision: #1 $
 *
 * Last modification: $DateTime: 2018/03/14 13:51:20 $
 * Last modified by:  $Author: lim.cy $
 *
 */

#if !defined(DUTYAUDITMESSAGECONVERTER_H_INCLUDED)
#define DUTYAUDITMESSAGECONVERTER_H_INCLUDED

namespace TA_Base_App
{
	class DutyAuditMessageConverter : public TA_Base_Bus::IDutyStateConverter
	{
	public:
		DutyAuditMessageConverter();
		~DutyAuditMessageConverter();

		TA_Base_Core::DescriptionParameters& buildSummaryDesc();
		std::vector<TA_Base_Core::DescriptionParameters*>& buildDetailDesc();
		std::vector<TA_Base_Core::DescriptionParameters*>& buildSubsystemDetailDesc();

        // Implementation of IDutyStateConverter
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
		DutyAuditMessageConverter( const DutyAuditMessageConverter& );
		DutyAuditMessageConverter& operator =( const DutyAuditMessageConverter& );

		TA_Base_Bus::DASType::SubsystemMap m_regions;
		TA_Base_Bus::DASType::SubsystemSet m_emptySubSet;

		TA_Base_Bus::DutyPrimitive m_session;
		TA_Base_Bus::DASType::DbKey m_region;
		TA_Base_Bus::DASType::DbKey m_subsystem;

		TA_Base_Core::DescriptionParameters m_summaryDesc;
		std::vector<TA_Base_Core::DescriptionParameters*> m_detailDesc;
	};
}

#endif // !defined(DUTYAUDITMESSAGECONVERTER_H_INCLUDED)
