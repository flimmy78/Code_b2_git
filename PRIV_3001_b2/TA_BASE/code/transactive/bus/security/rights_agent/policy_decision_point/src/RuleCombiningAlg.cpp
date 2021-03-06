/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/bus/security/rights_agent/policy_decision_point/src/RuleCombiningAlg.cpp $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2018/03/14 13:51:20 $
  *  Last modified by:  $Author: lim.cy $
  *
  *  Implementation of .
  */

#include "PolicyDecisionPoint.h"

namespace TA_Base_Bus
{
	RuleCombiningAlg::RuleCombiningAlg() :
		m_deny(false),
		m_atLeastOneError(false),
		m_potentialDeny(false),
		m_atLeastOnePermit(false)
	{
	}

	void RuleCombiningAlg::setResult(  PdpConst::EPolicyResult effect, PdpConst::EPolicyResult result )
	{
		switch( result )
		{
			case PdpConst::DENY_PR:
			{
				LOG( SOURCE_INFO, GENERIC_LOG_TYPE, DEBUG_LOG_LEVEL, "Rule result: DENY_PR" );
				m_deny = true;
			}
			break;

			case PdpConst::PERMIT_PR:
			{
				LOG( SOURCE_INFO, GENERIC_LOG_TYPE, DEBUG_LOG_LEVEL, "Rule result: PERMIT_PR" );
				m_atLeastOnePermit = true;
			}
			break;

			case PdpConst::NOT_APPLICABLE_PR:
				LOG( SOURCE_INFO, GENERIC_LOG_TYPE, DEBUG_LOG_LEVEL, "Rule result: NOT_APPLICABLE_PR" );
				break;

			case PdpConst::INDETERMINATE_PR:
			{
				LOG( SOURCE_INFO, GENERIC_LOG_TYPE, DEBUG_LOG_LEVEL, "Rule result: INDETERMINATE_PR" );

				m_atLeastOneError = true;

				if( PdpConst::DENY_PR == effect )
				{
					m_potentialDeny = true;
				}
			}
			break;

			default:
			{
				std::ostringstream msg;
				msg << "result == " << result;

				TA_ASSERT(false, msg.str().c_str());
			}
			break;
		}
	}

	bool RuleCombiningAlg::resultKnown() const
	{
		return( m_deny );
	}

	PdpConst::EPolicyResult RuleCombiningAlg::combinedResult() const
	{
		if( m_deny )
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, DEBUG_LOG_LEVEL, "Comb. result: DENY_PR" );
			return( PdpConst::DENY_PR );
		}
		if( m_potentialDeny )
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, DEBUG_LOG_LEVEL, "Comb. result: INDETERMINATE_PR" );
			return( PdpConst::INDETERMINATE_PR );
		}
		if( m_atLeastOnePermit )
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, DEBUG_LOG_LEVEL, "Comb. result: PERMIT_PR" );
			return( PdpConst::PERMIT_PR );
		}
		if( m_atLeastOneError )
		{
			LOG( SOURCE_INFO, GENERIC_LOG_TYPE, DEBUG_LOG_LEVEL, "Comb. result: INDETERMINATE_PR" );
			return( PdpConst::INDETERMINATE_PR );
		}

		LOG( SOURCE_INFO, GENERIC_LOG_TYPE, DEBUG_LOG_LEVEL, "Comb. result: NOT_APPLICABLE_PR" );
		return( PdpConst::NOT_APPLICABLE_PR );
	}
} // TA_Base_Bus
