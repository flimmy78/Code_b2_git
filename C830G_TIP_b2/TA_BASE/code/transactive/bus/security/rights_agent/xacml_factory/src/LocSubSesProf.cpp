/**
 * The source code in this file is the property of
 * Ripple Systems and is not for redistribution in any form.
 * 
 * Source:    $File: //depot/4669_T01271350/TA_BASE/transactive/bus/security/rights_agent/xacml_factory/src/LocSubSesProf.cpp $
 * @author:   Nick Jardine
 * @version:  $Revision: #1 $
 *
 * Last modification: $DateTime: 2008/11/28 16:26:01 $
 * Last modified by:  $Author: builder $
 *
 * Implements the LocSubSesProf interface.
 *
 */

#include "XacmlFactoryInternal.h"

namespace TA_Base_Bus
{
	LocSubSesProf::LocSubSesProf( const unsigned long location, const unsigned long subsystem,
		const std::string& sessionId, const unsigned long profile ) :
		m_location (location ),
		m_subsystem(subsystem),
		m_sessionId(sessionId),
		m_profile  (profile  )
	{
	}


	bool LocSubSesProf::operator==( const LocSubSesProf& rhs ) const
	{
		if( m_location != rhs.m_location )
		{
			return false;
		}

		if( m_subsystem != rhs.m_subsystem )
		{
			return false;
		}

		if( m_sessionId != rhs.m_sessionId )
		{
			return false;
		}

		if( m_profile != rhs.m_profile )
		{
			return false;
		}
		return true;
	}

	bool LocSubSesProf::operator< (const LocSubSesProf& rhs) const
	{
		if( m_location < rhs.m_location )
		{
			return true;
		}

		if( m_location > rhs.m_location )
		{
			return false;
		}

		if( m_subsystem < rhs.m_subsystem )
		{
			return true;
		}

		if( m_subsystem > rhs.m_subsystem )
		{
			return false;
		}

		if( m_sessionId < rhs.m_sessionId )
		{
			return true;
		}

		if( m_sessionId > rhs.m_sessionId )
		{
			return false;
		}

		if( m_profile < rhs.m_profile )
		{
			return true;
		}

		return false;
	}
	
}

