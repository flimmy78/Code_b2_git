#ifndef SUBSYSTEMDUTYSTATE_H_INCLUDED
#define SUBSYSTEMDUTYSTATE_H_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/security/duty_agent/src/SubsystemDutyState.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #2 $
  *
  *  Last modification: $DateTime: 2012/02/06 16:15:14 $
  *  Last modified by:  $Author: haijun.li $
  *
  *  <description>
  */

namespace TA_Base_App
{
	class SubsystemDutyState
	{
	public:

		virtual ~SubsystemDutyState(){}
		
		virtual void allocateDuty( const std::string& operatorId );
		virtual void freeDuty    ( const std::string& operatorId );

		virtual void takeDuty( const std::string& operatorId,
							   const std::list<const std::string>& siteList );

		virtual void takeDuty( const std::string& operatorId,
							   const std::string& site,
							   const std::list<const std::string>& subsystemList );

		virtual void giveDuty( const std::string& operatorId,
							   const std::string& site,
							   const std::list<const std::string>& subsystemList );

		virtual void delegateDuty();

	private:

		std::list<const std::string> subsystemList;
		std::list<const std::string> operatorList;
	};
}

#endif // SUBSYSTEMDUTYSTATE_H_INCLUDED
