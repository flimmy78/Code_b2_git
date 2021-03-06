#ifndef IACTIVEPLANMESSAGE_H_INCLUDED
#define IACTIVEPLANMESSAGE_H_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/response_plans/plan_agent/src/IActivePlanMessage.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #3 $
  *
  *  Last modification: $DateTime: 2012/12/27 15:59:31 $
  *  Last modified by:  $Author: qi.huang $
  *
  *  <description>
  */

namespace TA_Base_App
{
    class ActivePlan;

	//Class declaration
	class IActivePlanMessage
	{
	// Public methods
	public:
		IActivePlanMessage(){}
		virtual ~IActivePlanMessage(){}

		virtual void execute( ActivePlan& activePlan ) const = 0;
	
	private:
		IActivePlanMessage& operator=( const IActivePlanMessage& );
		IActivePlanMessage( const IActivePlanMessage& );

	}; // IActivePlanMessage
}; // TA_Base_App

#endif // IACTIVEPLANMESSAGE_H_INCLUDED
