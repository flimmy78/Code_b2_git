/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/security/duty_agent/duty_agent_state/src/RemoteDutyPeer.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #2 $
  *
  *  Last modification: $DateTime: 2012/02/06 16:15:14 $
  *  Last modified by:  $Author: haijun.li $
  *
  *  An implementation of the duty peer that uses the IDutyAgentPeerCobaDef object to implement
  *  the IDutyPeer interface.
  */
#ifndef REMOTEDUTYPEER_H_INCLUDED
#define REMOTEDUTYPEER_H_INCLUDED

namespace TA_Base_Bus
{
	class RemoteDutyPeer : public IDutyPeer
	{
	public:
		RemoteDutyPeer( const DASType::DbKey& location );
		virtual ~RemoteDutyPeer();

		virtual void sessionBegin        ( DutyState& state, const SessionInfo& session );
		virtual void sessionEnd          ( DutyState& state, const SessionInfo& session,
			const DASType::RegionSet& regions );
		virtual void sessionOverrideBegin( DutyState& state, const SessionInfo& session );
		virtual void sessionOverrideEnd  ( DutyState& state, const SessionInfo& session );
		
		virtual void transfer( DutyState& state, const TA_Base_Bus::SessionInfo& session, const DASType::RegionSet& regions );
		virtual void transfer( DutyState& state, const TA_Base_Bus::SessionInfo& session, const DASType::SubsystemMap& subsystems );

		virtual void degrade( DutyState& state, const DASType::SubsystemSet& subsystems);

		virtual void executeQuery( DutyState& state, IDutyQuery& query );
			
	private:

		RemoteDutyPeer( const RemoteDutyPeer& );
		RemoteDutyPeer& operator=( const RemoteDutyPeer& );
		DASType::DutyAgentPeer* m_peer;

        // TD9899: Store the location key so that the peer can generate meaningful
        //         error messages.
        DASType::DbKey m_peerLocation;
	
		static const unsigned long TIME_OF_FLIGHT;
		static const unsigned long MAX_PEER_TIMEOUT;
	};
}

#endif //  REMOTEDUTYPEER_H_INCLUDED
