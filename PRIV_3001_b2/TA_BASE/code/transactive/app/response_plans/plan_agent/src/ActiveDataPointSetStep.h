#if defined ( STEPTYPE_DATA_POINT_SET )

#ifndef ACTIVEDATAPOINTSETSTEP_H_INCLUDED
#define ACTIVEDATAPOINTSETSTEP_H_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/response_plans/plan_agent/src/ActiveDataPointSetStep.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2018/03/14 13:51:20 $
  *  Last modified by:  $Author: lim.cy $
  *
  *  <description>
  */

#include "ace/Future.h"

#include "core/timers/src/TimedWaitSemaphore.h"
#include "bus/scada/proxy_library/src/IEntityUpdateEventProcessor.h"
#include "bus/scada/proxy_library/src/DataPointProxySmartPtr.h"
#include "app/response_plans/plan_agent/src/ActiveStep.h"


namespace TA_Base_App
{
    class IActivePlanFlow;

	//Class declaration
	class ActiveDataPointSetStep : public ActiveStep, public TA_Base_Bus::IEntityUpdateEventProcessor
	{
	// Public methods
	public: 
		ActiveDataPointSetStep( const TA_Base_Core::StepDetail& stepDetail, 
            const TA_Base_Core::DataPointSetParameters& params, IActivePlanFlow& flowControl, bool bSubStep );
        ~ActiveDataPointSetStep();

		virtual void processEntityUpdateEvent(unsigned long entityKey , TA_Base_Bus::ScadaEntityUpdateType updateType);
		void setExecResult(ACE_Future<bool> & execResult);

	protected:
	    virtual TA_Base_Core::EActiveStepState executeImpl( void );
        bool sendControl(const std::string& strSession, const std::string &strValue, const int waitMillSec);
        bool initialize(std::string& strSession, std::string &strValue, int& waitMillSec);

	private:
		ActiveDataPointSetStep& operator=( const ActiveDataPointSetStep& );
		ActiveDataPointSetStep( const ActiveDataPointSetStep& );

        const TA_Base_Core::DataPointSetParameters m_params;

		TA_Base_Core::TimedWaitSemaphore m_semaphore;
		TA_Base_Core::TimedWaitSemaphore m_agentConnectedSem;
		TA_Base_Bus::DataPointProxySmartPtr m_pDataPoint;

        bool m_bRccSucceed;
        int m_nControlType;

		ACE_Future<bool> m_execResult;
	}; // ActiveDataPointSetStep
}; // TA_Base_App

#endif // ACTIVEDATAPOINTSETSTEP_H_INCLUDED

#endif //  STEPTYPE_DATA_POINT_SET
