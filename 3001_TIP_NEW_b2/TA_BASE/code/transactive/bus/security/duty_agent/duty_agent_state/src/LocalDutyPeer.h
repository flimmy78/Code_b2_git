/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/security/duty_agent/duty_agent_state/src/LocalDutyPeer.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #2 $
  *
  *  Last modification: $DateTime: 2012/02/06 16:15:14 $
  *  Last modified by:  $Author: haijun.li $
  *
  *  An implementation of the duty peer that uses the local library as apposed to making a
  *  call on a remote agent (RemoteDutyPeer).
  */
#ifndef LOCALDUTYPEER_H_INCLUDED
#define LOCALDUTYPEER_H_INCLUDED

namespace TA_Base_Bus
{
	class LocalDutyPeer : public IDutyPeer,
						  public TA_Base_Bus::SeDutyStateObserver<TA_Base_Bus::StateUpdateSubjectImpl>,
		                  public TA_Base_Bus::SeObserver<TA_Base_Bus::AgentTerminateSubjectImpl>
	{
	public:
		LocalDutyPeer( const DASType::DbKey& location );
		virtual ~LocalDutyPeer();

		virtual void sessionBegin        ( DutyState& state, const SessionInfo& session );
		virtual void sessionEnd          ( DutyState& state, const SessionInfo& session,
			const DASType::RegionSet& regions );
		virtual void sessionOverrideBegin( DutyState& state, const SessionInfo& session );
		virtual void sessionOverrideEnd  ( DutyState& state, const SessionInfo& session );
		
		virtual void transfer( DutyState& state, const TA_Base_Bus::SessionInfo& session, const DASType::RegionSet& regions );
		virtual void transfer( DutyState& state, const TA_Base_Bus::SessionInfo& session, const DASType::SubsystemMap& subsystems );

		virtual void degrade( DutyState& state, const DASType::SubsystemSet& subsystems);

		virtual void executeQuery( DutyState& state, IDutyQuery& query );
		
		virtual void update( StateUpdateSubjectImpl&    stateUpdate  ,const DutyState & state   );
		virtual void update( AgentTerminateSubjectImpl& terminateUpdate );

	private:

		LocalDutyPeer( const LocalDutyPeer& );
		LocalDutyPeer& operator=( const LocalDutyPeer& );
		typedef SeDutyStateObserver<StateUpdateSubjectImpl   > StateUpdateParent;
		typedef SeObserver<AgentTerminateSubjectImpl> AgentTerminateParent;

		class RegXferSubCommand : public IRegSubCommand<Region>
		{
		public:
			RegXferSubCommand( DutyState& state, const TA_Base_Bus::SessionInfo& session,
				const DASType::SubsystemSet& subsystems, bool apply);
			virtual void execute( Region& region, bool doApply );

		private:
			DutyState& m_state;
			const TA_Base_Bus::SessionInfo& m_session;
			const DASType::SubsystemSet& m_subsystems;
			bool m_apply;
		};

		class RegSubSetCommand : public IRegSubCommand<Region>
		{
		public:
			RegSubSetCommand( void (Region::*subSetCmd)(DutyState&, const DASType::SubsystemSet&), DutyState& state,
				const DASType::SubsystemSet& subsystems );
			virtual void execute( Region& region, bool doApply );

		private:
			void (Region::*m_subSetCmd)(DutyState&,const DASType::SubsystemSet&);
			DutyState& m_state;
			const DASType::SubsystemSet& m_subsystems;
		};

		void regionExecute( IRegSubCommand<Region>& command, bool doApply );
		void regionExecute( IRegSubCommand<Region>& command, const DASType::RegionSet& regions, bool doApply );
		void regionExecute( IRegSubCommand<Region>& command, const DASType::DbKey& region, bool doApply );

		typedef std::map<DASType::DbKey, Region*> RegionMap;

		RegionMap m_regions;

		//DutyRequestSender m_dutyRequestSender;
	};
}
#endif //  LOCALDUTYPEER_H_INCLUDED
