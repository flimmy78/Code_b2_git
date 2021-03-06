/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File$
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision$
  *
  *  Last modification: $DateTime$
  *  Last modified by:  $Author$
  *
  *  Gets a list of transferable subsystems.
  */

#if !defined(TRANSFERABLESUBSYSTEMQUERY_H_INCLUDED)
#define TRANSFERABLESUBSYSTEMQUERY_H_INCLUDED

namespace TA_Base_Bus
{
	class TransferableSubsystemQuery : public IDutyQuery
	{

	public:
		TransferableSubsystemQuery( const TA_Base_Bus::SessionInfo& session, const DASType::RegionSet& regions );

		virtual std::auto_ptr<IDutyQuery> clone() const;

		virtual void execute(DutyState& state, DASType::DutyAgentPeer* peer );

		virtual void execute(DutyState& state, const DASType::DbKey& region, const DASType::DutySet& dutySet);
		virtual void execute(DutyState& state, const DASType::DbKey& subsystem,
			const DASType::DutySet& dutySet, const SubsystemState& subState );
		virtual bool isValidToCheckSubsystems();
		virtual const DASType::SubsystemSet& getSubsystems() const;
		virtual const DASType::RegionSet&    getRegions()    const;

	private:
		const TA_Base_Bus::SessionInfo&    m_session;
		DASType::SubsystemSet m_subsystems;
		DASType::RegionSet    m_regions;
		DASType::DutySet      m_regionDuty;

	};
}







#endif // !defined(TRANSFERABLESUBSYSTEMQUERY_H_INCLUDED)
