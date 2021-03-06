/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/4669_TIP/TA_BASE/transactive/bus/security/duty_agent/duty_agent_state/src/SesSnapshotQuery.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2008/10/31 12:12:40 $
  *  Last modified by:  $Author: grace.koh $
  *
  *  Gets a snapshot of the current state.
  */

#if !defined(SesSnapshotQuery_H_INCLUDED)
#define SesSnapshotQuery_H_INCLUDED

namespace TA_Base_Bus
{
	class SesSnapshotQuery : public IDutyQuery
	{

	public:
		SesSnapshotQuery(const std::string & sessionId);

		virtual std::auto_ptr<IDutyQuery> clone() const;

		virtual void execute(DutyState& state, DASType::DutyAgentPeer* peer );

		virtual void execute(DutyState& state, const DASType::DbKey& region, const DASType::DutySet& dutySet);
		virtual void execute(DutyState& state, const DASType::DbKey& subsystem,
			const DASType::DutySet& dutySet, const SubsystemState& subState );
		virtual bool isValidToCheckSubsystems();
		virtual const DASType::SubsystemSet& getSubsystems() const;
		virtual const DASType::RegionSet&    getRegions()    const;

	private:
		DASType::SubsystemSet m_subsystems;
		DASType::RegionSet    m_regions;
		const std::string&    m_sessionId;
		bool m_validToCheckSubsystems;
	};
}

#endif // !defined(SesSnapshotQuery_H_INCLUDED)
