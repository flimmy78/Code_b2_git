/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/bus/security/duty_agent/duty_agent_state/src/DutyPrimitive.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2018/03/14 13:51:20 $
  *  Last modified by:  $Author: lim.cy $
  *
  *  The smallest unit of duty: session + profile.
  *
  */

#ifndef DUTYPRIMITIVE_H_INCLUDED
#define DUTYPRIMITIVE_H_INCLUDED

namespace TA_Base_Bus
{
	class DutyPrimitive
	{

	public:

		// An operators session and the profile they are using (as there can be more than one) is
		// needed to uniquely identify an operator's duty. The session alone is insufficient due
		// to the ability of operators to override their initial profile with a new one. This means
		// that an operator can have duty removed/added for one profile indipendently of the other.
		std::string    m_session;
		DASType::DbKey m_profile;

		// Some useful constructors
		DutyPrimitive();
		DutyPrimitive( const std::string& session, const DASType::DbKey& profile );
		DutyPrimitive( const DutyPrimitive& copyThis );

		// Some operators to allow this structure to be put into a sorted container e.g. std::set.
		bool operator <  ( const DutyPrimitive& rhs ) const;
		bool operator == ( const DutyPrimitive& rhs ) const;

		void update();

	}; // DutyPrimitive
} // TA_Base_Bus








#endif // DUTYPRIMITIVE_H_INCLUDED
