#include "WFEventHandler.h"
#include "WFCommandPolicy.h"
#include "bus/scada/104_library/src/Command.h"
#include "bus/scada/104_library/src/Iec104Api.h"
#include "bus/soe/soe_process_library/src/SOEProcessor.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/data_access_interface/soe/src/SOEEvent.h"
#include <sstream>

namespace TA_IRS_App
{
const int WfEventHandler::s_UpdateMonitorTimeSlice = 5000; //5s
WfEventHandler::WfEventHandler()
:m_wfMsgTimer(NULL),
 m_isConnectionTimerStarted(false),
 m_lastUpdateTimeSec(0),
 m_monitorConnectionTimeId(-1),
 m_monitorLastUpdateTimeId(-1),
 m_linkStatusBadToGood(false),
 m_isInControl(false)
{
	FUNCTION_ENTRY("WfEventHandler::WfEventHandler");
	m_InputDataPoints.clear();
	m_OutputDataPoints.clear();
	m_wfDpProcessor = new WfDpProcessor(m_InputDataPoints);
	FUNCTION_EXIT("WfEventHandler::WfEventHandler");
}
WfEventHandler::~WfEventHandler()
{
	FUNCTION_ENTRY("WfEventHandler::~WfEventHandler");

	delete m_wfDpProcessor;
	m_wfDpProcessor=NULL;
	TA_Base_Core::SingletonTimerUtil::getInstance().stopPeriodicTimeOutClock(this);
	FUNCTION_EXIT("WfEventHandler::~WfEventHandler");
}
void WfEventHandler::setMsgTimer(TA_IRS_App::WfMsgTimer* wfMsgTimer)
{
	m_wfMsgTimer = wfMsgTimer;
}

void WfEventHandler::handleSinglePoint(int rtuAddr,b_ui8 bCot, vector<SSinglePoint> &vSinglePoint)
{
	FUNCTION_ENTRY("handleSinglePoint");
	int num = vSinglePoint.empty() ? -1 : static_cast<int>(vSinglePoint.size());
	SSinglePoint sp;
	LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Type 1 Message: CommonAddress=%02x, cot_%03d, Num=%d",rtuAddr,bCot,num);
	b_ui8 SIQ;
	timeb currentSystemTime;   //TD16182
	ftime ( &currentSystemTime );
	m_lastUpdateTimeSec = currentSystemTime.time;

	TA_Base_Bus::DataPoint * dp;

	for(int i=0;i < num;i++)
	{
		sp = vSinglePoint[i];
		memcpy(&SIQ,&sp.SIQ,1);
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Point: %03d IOA=0X%06x (%6d), { SIQ:%02x, SPI:%02x}",i,sp.iOffset,sp.iOffset,SIQ,sp.SIQ.SPI);

		WfDataPointMap::iterator itr = m_InputDataPoints.find( sp.iOffset );

		if ( itr != m_InputDataPoints.end() )
		{
			dp = itr->second;

			// set up DataPointState with the specified timestamp, quality and value
			TA_Base_Bus::DpValue dpValue( dp->getDataPointDataType(), dp->getEnumLabelsMap(), dp->getBooleanLabels() );
			bool bResult = false;

			if (sp.SIQ.SPI == 1)
				bResult = true;
			else
				bResult = false;

			TA_Base_Bus::EQualityStatus quality = TA_Base_Bus::QUALITY_GOOD_NO_SPECIFIC_REASON;

			if (sp.SIQ.BL == 1)
				quality = TA_Base_Bus::QUALITY_UNCERTAINTY_NO_SPECIFIC_REASON;

			if (sp.SIQ.SB == 1)
				quality = TA_Base_Bus::QUALITY_UNCERTAINTY_SENSOR_NOT_ACCURATE;

			if (sp.SIQ.NT == 1)
				quality = TA_Base_Bus::QUALITY_BAD_LAST_KNOWN_VALUE;

			if (sp.SIQ.IV == 1)
				quality = TA_Base_Bus::QUALITY_BAD_OUT_OF_SERVICE;

			dpValue.setBoolean( bResult);
			boost::shared_ptr<TA_Base_Bus::DataPointState> newState(new TA_Base_Bus::DataPointState( dpValue, currentSystemTime, quality));
			m_wfDpProcessor->submitUpdateDataPoint(dp,  newState);

		}
	}
	FUNCTION_EXIT("handleSinglePoint");
}
void WfEventHandler::handleSinglePointWithTimeTag(int rtuAddr,b_ui8 bCot, vector<SSinglePointTimeTag> &vSinglePointTm)
{
	FUNCTION_ENTRY("handleSinglePointWithTimeTag");

	int num = vSinglePointTm.empty() ? -1 : static_cast<int>(vSinglePointTm.size());
	SSinglePointTimeTag sp;
	LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Type 30 Message: CommonAddress=%02x, cot_%03d, Num=%d",rtuAddr,bCot,num);
	b_ui8 SIQ;
	SFepTime sysTime;
	struct tm dateTm;
	timeb currentSystemTime;   //TD16182
	ftime ( &currentSystemTime );
	m_lastUpdateTimeSec = currentSystemTime.time;

	timeb sourceSystemTime;  
	ftime ( &sourceSystemTime );

	TA_Base_Bus::DataPoint * dp;

	for(int i=0;i < num;i++)
	{
		sp = vSinglePointTm[i];
		memcpy(&SIQ,&sp.SIQ,1);
		memcpy(&sysTime,&(sp.cp56TimeTag),sizeof(SFepTime));

		dateTm.tm_mday = sysTime.day;
		dateTm.tm_mon = sysTime.month - 1; 
		dateTm.tm_year = sysTime.year - 1900;
		dateTm.tm_hour = sysTime.hour;
		dateTm.tm_isdst = -1;
		dateTm.tm_min = sysTime.minute;
		dateTm.tm_sec = sysTime.second;

		time_t time = mktime( &dateTm );
		if ( time == static_cast< time_t >( -1 ) )
		{
			//TA_THROW( TA_Base_Core::ArchiveException( "Unable to convert date/time." ) );
		}

		
		sourceSystemTime.millitm = sysTime.millisecond;
		sourceSystemTime.time = time;

		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Point: %03d IOA=0X%06x (%6d), { SIQ:%02x, SPI:%02x}",i,sp.iOffset,sp.iOffset,SIQ,sp.SIQ.SPI);

		WfDataPointMap::iterator itr = m_InputDataPoints.find( sp.iOffset );

		if ( itr != m_InputDataPoints.end() )
		{
			dp = itr->second;

			// set up DataPointState with the specified timestamp, quality and value
			TA_Base_Bus::DpValue dpValue( dp->getDataPointDataType(), dp->getEnumLabelsMap(), dp->getBooleanLabels() );
			bool bResult = false;

			if (sp.SIQ.SPI == 1)
				bResult = true;
			else
				bResult = false;

			std::string strValue = bResult?"True":"False";
			dpValue.setBoolean( bResult);

			TA_Base_Core::SOEEvent soeEvent;
			soeEvent.setEntityKey(dp->getEntityKey());
			soeEvent.setLocationKey(dp->getLocationKey());
			soeEvent.setLocationName(dp->getLocationName());
			soeEvent.setAssetName(dp->getAssetName());
			soeEvent.setDescription(dp->getDescription());
			soeEvent.setSourceTime(sourceSystemTime);
			soeEvent.setTransactiveTime(currentSystemTime);
			soeEvent.setValueData(strValue);
			soeEvent.setDisplayValue(dpValue.getValueAsString());

			TA_Base_Bus::SOEProcessor::getInstance().submitSOE(soeEvent);

		}
	}
	FUNCTION_EXIT("handleSinglePointWithTimeTag");

}

void WfEventHandler::handleMeasureValueSVA(int rtuAddr, b_ui8 bCot,vector<SMeasuredValueSVA> &vMeasuredValueSVA)
{
	FUNCTION_ENTRY("handleMeasureValueSVA");
	int num = vMeasuredValueSVA.empty() ? -1 : static_cast<int>(vMeasuredValueSVA.size());
	SMeasuredValueSVA sva;
	LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Type 11 Message: CommonAddress=%02x, cot=%03d, num=%d",rtuAddr,bCot,num);
	b_ui16 SVA;b_ui8 QDS;
	timeb currentSystemTime;   //TD16182
	ftime ( &currentSystemTime );
	m_lastUpdateTimeSec = currentSystemTime.time;

	TA_Base_Bus::DataPoint * dp;
	for(int i=0;i< num;i++)
	{
		sva =vMeasuredValueSVA[i];
		memcpy(&SVA, &sva.SVA,2);
		memcpy(&QDS,&sva.QDS,1);
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Point: %03d IOA=%06d, { SVA:%02d, QDS:%02x}",i,sva.iOffset,SVA,QDS);

		WfDataPointMap::iterator itr = m_InputDataPoints.find( sva.iOffset );

		if (itr != m_InputDataPoints.end() )
		{
			dp = itr->second;

			TA_Base_Bus::EQualityStatus quality = TA_Base_Bus::QUALITY_GOOD_NO_SPECIFIC_REASON;

			if (sva.QDS.OV == 1)
				quality = TA_Base_Bus::QUALITY_BAD_DEVICE_FAILURE;

			if (sva.QDS.BL == 1)
				quality = TA_Base_Bus::QUALITY_UNCERTAINTY_NO_SPECIFIC_REASON;

			if (sva.QDS.SB == 1)
				quality = TA_Base_Bus::QUALITY_UNCERTAINTY_SENSOR_NOT_ACCURATE;

			if (sva.QDS.NT == 1)
				quality = TA_Base_Bus::QUALITY_BAD_LAST_KNOWN_VALUE;

			if (sva.QDS.IV == 1)
				quality = TA_Base_Bus::QUALITY_BAD_OUT_OF_SERVICE;


			// set up DataPointState with the specified timestamp, quality and value
			TA_Base_Bus::DpValue dpValue( dp->getDataPointDataType(), dp->getEnumLabelsMap(), dp->getBooleanLabels() );
			dpValue.setFloat( sva.SVA, dp->getPrecision() );
			boost::shared_ptr<TA_Base_Bus::DataPointState> newState(new TA_Base_Bus::DataPointState( dpValue, currentSystemTime, quality));
			m_wfDpProcessor->submitUpdateDataPoint(dp,  newState);
		}

	}
	FUNCTION_EXIT("handleMeasureValueSVA");
}

void WfEventHandler::handleMeasureValueSVAWithTimeTag(int rtuAddr,b_ui8 bCot,vector<SMeasuredValueSVATimeTag> &vMeasuredValueSVATm)
{
	FUNCTION_ENTRY("handleMeasureValueSVAWithTimeTag");
	int num = vMeasuredValueSVATm.empty() ? -1 : static_cast<int>(vMeasuredValueSVATm.size());
	SMeasuredValueSVATimeTag sva;
	LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Type 11 Message: CommonAddress=%02x, cot=%03d, num=%d",rtuAddr,bCot,num);
	b_ui16 SVA;b_ui8 QDS;
	SFepTime sysTime;
	struct tm dateTm;
	timeb currentSystemTime;   //TD16182
	ftime ( &currentSystemTime );
	m_lastUpdateTimeSec = currentSystemTime.time;

	timeb sourceSystemTime;  
	ftime ( &sourceSystemTime );

	TA_Base_Bus::DataPoint * dp;
	for(int i=0;i< num;i++)
	{
		sva =vMeasuredValueSVATm[i];
		memcpy(&SVA, &sva.SVA,2);
		memcpy(&QDS,&sva.QDS,1);
		memcpy(&sysTime,&(sva.cp56TimeTag),sizeof(SFepTime));

		dateTm.tm_mday = sysTime.day;
		dateTm.tm_mon = sysTime.month - 1; 
		dateTm.tm_year = sysTime.year - 1900;
		dateTm.tm_hour = sysTime.hour;
		dateTm.tm_isdst = -1;
		dateTm.tm_min = sysTime.minute;
		dateTm.tm_sec = sysTime.second;

		time_t time = mktime( &dateTm );
		if ( time == static_cast< time_t >( -1 ) )
		{
			//TA_THROW( TA_Base_Core::ArchiveException( "Unable to convert date/time." ) );
		}


		sourceSystemTime.millitm = sysTime.millisecond;
		sourceSystemTime.time = time;

		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Point: %03d IOA=%06d, { SVA:%02d, QDS:%02x}",i,sva.iOffset,SVA,QDS);

		WfDataPointMap::iterator itr = m_InputDataPoints.find( sva.iOffset );

		if (itr != m_InputDataPoints.end() )
		{
			dp = itr->second;

			// set up DataPointState with the specified timestamp, quality and value
			TA_Base_Bus::DpValue dpValue( dp->getDataPointDataType(), dp->getEnumLabelsMap(), dp->getBooleanLabels() );
			dpValue.setFloat( sva.SVA, dp->getPrecision() );
			
			char szTemp[64];
			sprintf(szTemp,"%d",sva.SVA);
			std::string strValue = szTemp;
			
			TA_Base_Core::SOEEvent soeEvent;
			soeEvent.setEntityKey(dp->getEntityKey());
			soeEvent.setLocationKey(dp->getLocationKey());
			soeEvent.setLocationName(dp->getLocationName());
			soeEvent.setAssetName(dp->getAssetName());
			soeEvent.setDescription(dp->getDescription());
			soeEvent.setSourceTime(sourceSystemTime);
			soeEvent.setTransactiveTime(currentSystemTime);
			soeEvent.setValueData(strValue);
			soeEvent.setDisplayValue(dpValue.getValueAsString());

			TA_Base_Bus::SOEProcessor::getInstance().submitSOE(soeEvent);

		}

	}
	FUNCTION_EXIT("handleMeasureValueSVAWithTimeTag");

}

void WfEventHandler::handleMeasureValueSFA(int rtuAddr,b_ui8 bCot,vector<SMeasuredValueSFA> &vMeasuredValueSFA)
{
	FUNCTION_ENTRY("handleMeasureValueSFA");
	int num = vMeasuredValueSFA.empty() ? -1 : static_cast<int>(vMeasuredValueSFA.size());
	SMeasuredValueSFA sfa;
	LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Type 13 Message: CommonAddress=%02x, cot=%03d, num=%d",rtuAddr,bCot,num);
	float SFA;b_ui8 QDS;
	timeb currentSystemTime;   //TD16182
	ftime ( &currentSystemTime );
	m_lastUpdateTimeSec = currentSystemTime.time;

	TA_Base_Bus::DataPoint * dp;
	for(int i=0;i< num;i++)
	{
		sfa =vMeasuredValueSFA[i];
		memcpy(&SFA, &sfa.SFA,4);
		memcpy(&QDS,&sfa.QDS,1);
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Point: %03d IOA=%06d, { SFA:%f, QDS:%02x}",i,sfa.iOffset,SFA,QDS);

		WfDataPointMap::iterator itr = m_InputDataPoints.find( sfa.iOffset );

		if (itr != m_InputDataPoints.end() )
		{
			dp = itr->second;

			TA_Base_Bus::EQualityStatus quality = TA_Base_Bus::QUALITY_GOOD_NO_SPECIFIC_REASON;

			if (sfa.QDS.OV == 1)
				quality = TA_Base_Bus::QUALITY_BAD_DEVICE_FAILURE;

			if (sfa.QDS.BL == 1)
				quality = TA_Base_Bus::QUALITY_UNCERTAINTY_NO_SPECIFIC_REASON;

			if (sfa.QDS.SB == 1)
				quality = TA_Base_Bus::QUALITY_UNCERTAINTY_SENSOR_NOT_ACCURATE;

			if (sfa.QDS.NT == 1)
				quality = TA_Base_Bus::QUALITY_BAD_LAST_KNOWN_VALUE;

			if (sfa.QDS.IV == 1)
				quality = TA_Base_Bus::QUALITY_BAD_OUT_OF_SERVICE;


			// set up DataPointState with the specified timestamp, quality and value
			TA_Base_Bus::DpValue dpValue( dp->getDataPointDataType(), dp->getEnumLabelsMap(), dp->getBooleanLabels() );
			dpValue.setFloat( sfa.SFA );
			boost::shared_ptr<TA_Base_Bus::DataPointState> newState(new TA_Base_Bus::DataPointState( dpValue, currentSystemTime, quality));
			m_wfDpProcessor->submitUpdateDataPoint(dp,  newState);
		}

	}
	FUNCTION_EXIT("handleMeasureValueSFA");
}


void WfEventHandler::handleMeasureValueSFAWithTimeTag(int rtuAddr,b_ui8 bCot,vector<SMeasuredValueSFATimeTag> &vMeasuredValueSFATm)
{
		FUNCTION_ENTRY("handleMeasureValueSFAWithTimeTag");
		int num = vMeasuredValueSFATm.empty() ? -1 : static_cast<int>(vMeasuredValueSFATm.size());
		SMeasuredValueSFATimeTag sfa;
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Type 36 Message: CommonAddress=%02x, cot=%03d, num=%d",rtuAddr,bCot,num);
		float SFA;b_ui8 QDS;
		SFepTime sysTime;
		struct tm dateTm;
		timeb currentSystemTime;   //TD16182
		ftime ( &currentSystemTime );
		m_lastUpdateTimeSec = currentSystemTime.time;

		timeb sourceSystemTime;  
		ftime ( &sourceSystemTime );
	
		TA_Base_Bus::DataPoint * dp;
		for(int i=0;i< num;i++)
		{
			sfa =vMeasuredValueSFATm[i];
			memcpy(&SFA, &sfa.SFA,4);
			memcpy(&QDS,&sfa.QDS,1);
			memcpy(&sysTime,&(sfa.cp56TimeTag),sizeof(SFepTime));
	
			dateTm.tm_mday = sysTime.day;
			dateTm.tm_mon = sysTime.month - 1; 
			dateTm.tm_year = sysTime.year - 1900;
			dateTm.tm_hour = sysTime.hour;
			dateTm.tm_isdst = -1;
			dateTm.tm_min = sysTime.minute;
			dateTm.tm_sec = sysTime.second;
	
			time_t time = mktime( &dateTm );
			if ( time == static_cast< time_t >( -1 ) )
			{
				//TA_THROW( TA_Base_Core::ArchiveException( "Unable to convert date/time." ) );
			}
	
	
			sourceSystemTime.millitm = sysTime.millisecond;
			sourceSystemTime.time = time;
	
			LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Point: %03d IOA=%06d, { SFA:%f, QDS:%02x}",i,sfa.iOffset,SFA,QDS);
	
			WfDataPointMap::iterator itr = m_InputDataPoints.find( sfa.iOffset );
	
			if (itr != m_InputDataPoints.end() )
			{
				dp = itr->second;
	
				// set up DataPointState with the specified timestamp, quality and value
				TA_Base_Bus::DpValue dpValue( dp->getDataPointDataType(), dp->getEnumLabelsMap(), dp->getBooleanLabels() );
				dpValue.setFloat( sfa.SFA );
				
				char szTemp[64];
				sprintf(szTemp,"%f",sfa.SFA);
				std::string strValue = szTemp;
				
				TA_Base_Core::SOEEvent soeEvent;
				soeEvent.setEntityKey(dp->getEntityKey());
				soeEvent.setLocationKey(dp->getLocationKey());
				soeEvent.setLocationName(dp->getLocationName());
				soeEvent.setAssetName(dp->getAssetName());
				soeEvent.setDescription(dp->getDescription());
				soeEvent.setSourceTime(sourceSystemTime);
				soeEvent.setTransactiveTime(currentSystemTime);
				soeEvent.setValueData(strValue);
				soeEvent.setDisplayValue(dpValue.getValueAsString());
	
				TA_Base_Bus::SOEProcessor::getInstance().submitSOE(soeEvent);
	
			}
	
		}
		FUNCTION_EXIT("handleMeasureValueSVAWithTimeTag");

}


void WfEventHandler::handleIntegratedTotal(int rtuAddr,b_ui8 bCot,vector<SCounterValue>&vCounterValue)
{
	FUNCTION_ENTRY("handleIntegratedTotal");
	int num = vCounterValue.empty() ? -1 : static_cast<int>(vCounterValue.size());
	SCounterValue cv;
	LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Type 15 Message: Common Address=%02x, cot_%02x, num_ %d",rtuAddr,bCot,num);
	b_ui8 sequence;
	timeb currentSystemTime;   //TD16182
	ftime ( &currentSystemTime );
	m_lastUpdateTimeSec = currentSystemTime.time;

	TA_Base_Bus::DataPoint * dp;

	for(int i=0;i< num;i++)
	{
		cv =vCounterValue[i];
		memcpy(&sequence, &cv.BCR.SequenceNotation,1);
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive Point:%02d IOA=%06d,{Counter:%04x,Sequence:%02d,IV:%d,CY:%d,CA:%d}",
			i,cv.iOffset,cv.BCR.Counter,sequence,
			cv.BCR.SequenceNotation.IV,
			cv.BCR.SequenceNotation.CY,
			cv.BCR.SequenceNotation.CA);
		
		WfDataPointMap::iterator itr = m_InputDataPoints.find( cv.iOffset );

		if (itr != m_InputDataPoints.end() )
		{
			dp = itr->second;

			TA_Base_Bus::EQualityStatus quality = TA_Base_Bus::QUALITY_GOOD_NO_SPECIFIC_REASON;

			if (cv.BCR.SequenceNotation.CY == 1)
				quality = TA_Base_Bus::QUALITY_BAD_DEVICE_FAILURE;

			if (cv.BCR.SequenceNotation.IV == 1)
				quality = TA_Base_Bus::QUALITY_BAD_SENSOR_FAILURE;

			//if (cv.BCR.SequenceNotation.CA == 1)
			//	quality = TA_Base_Bus::QUALITY_GOOD_NO_SPECIFIC_REASON;

			// set up DataPointState with the specified timestamp, quality and value
			TA_Base_Bus::DpValue dpValue( dp->getDataPointDataType(), dp->getEnumLabelsMap(), dp->getBooleanLabels() );
			dpValue.setFloat( cv.BCR.Counter, dp->getPrecision() );
			boost::shared_ptr<TA_Base_Bus::DataPointState> newState(new TA_Base_Bus::DataPointState( dpValue, currentSystemTime, quality));
			m_wfDpProcessor->submitUpdateDataPoint(dp,  newState);

		}	
	}
	FUNCTION_EXIT("handleIntegratedTotal");
}

void WfEventHandler::handleIntegratedTotalWithTimeTag(int rtuAddr,b_ui8 bCot,vector<SCounterValueTimeTag>&vCounterValueTm)
{
	FUNCTION_ENTRY("handleIntegratedTotalWithTimeTag");
	FUNCTION_EXIT("handleIntegratedTotalWithTimeTag");
}

void WfEventHandler::handleInterrogateGeneral(b_ui16 iRtuAddr,b_ui8 bCot , b_ui8 bQoi)
{
	//all data transfereded
	if(10 == bCot)
	{
		m_wfUnit->setAllDataTransfered(true);
	}
}

void WfEventHandler::handleInterrogateCounter(b_ui16 iRtuAddr,b_ui8 bCot , b_ui8 bRqt,b_ui8 bFrz)
{
	if(10 == bCot)
	{
		m_wfUnit->setKwhDataTransfered(true);
	}
}
void WfEventHandler::handleSingleCommand(int rtuAddr,int iInfoAddr,b_ui8 btCot,b_ui8 bSco,b_ui8 bOriAddr)
{
	FUNCTION_ENTRY("handleSingleCommand");
	LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Receive type 45 message: rtu_%02x,info_%06x cot_%02x oriAddr_%02x   Sco_%02x ",rtuAddr,iInfoAddr,btCot,bOriAddr,bSco);

	WfDataPointMap::iterator itr = m_OutputDataPoints.find( iInfoAddr );

	if (m_OutputDataPoints.end() == itr)
	{
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugWarn, "no datapoint find for address:%d", iInfoAddr);
		return;
	}

	int test = btCot & 0x80;
	int pn = btCot & 0x40;
	int cot = btCot & 0x3f;
	TA_Base_Bus::DataPoint * dp = itr->second;
	ECommandPolicyResult policyResult;

	switch (cot)
	{
	case 7:
		if (bSco & 0x80)
		{
			if (m_wfMsgTimer)
			{
				m_wfMsgTimer->removeMessage(dp,TA_Base_Bus::selectCmdConfirmTimeout);
			}
			
			if (pn > 0)
			{
				std::stringstream ss;
				ss << bOriAddr;
				LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "WF datapoint %s with address %d verfication fail with errorcode %s ",dp->getDataPointName().c_str(),dp->getDataPointRegisterAddress(),ss.str().c_str());
				WfCommandPolicy::updateControlState (dp, TA_Base_Bus::selectCmdCfmNegative, ss.str(),true );
			}
			else
			{
				LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "WF datapoint %s with address %d verfication pass.",dp->getDataPointName().c_str(),dp->getDataPointRegisterAddress());
				WfCommandPolicy::updateControlState (dp, TA_Base_Bus::selectCmdConfirm,"", true );
                // set control command state for WF using, the controlcommandstate was desinged for PSCADA, the control command state will be begin execute.
                dp->setControlCommandState(TA_Base_Bus::CompletedWithSuccess);
			}
		}
		break;

	default:
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugWarn, "the cot:%d is not been handled.", cot);
	}

	FUNCTION_EXIT("handleSingleCommand");
}	


bool WfEventHandler::addDataPoint(TA_Base_Bus::DataPoint * dp)
{
	FUNCTION_ENTRY("addDataPoint");
	TA_ASSERT(NULL != dp, "dp is NULL in WfEventHandler::addDataPoint");
	LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Add DataPoint:0x%p Address:%04d Name(%s) ",dp,dp->getDataPointRegisterAddress(),dp->getDataPointName().c_str());

	// only hold output datapoints
	bool isAdded = false;
	if (dp->isWriteable())
	{
		m_OutputDataPoints[ dp->getDataPointRegisterAddress() ] = dp;

		isAdded = true;
	}
	else
	{
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Begin Add DataPoint to WfEventHandler");
		m_InputDataPoints[ dp->getDataPointRegisterAddress() ] = dp;
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "End Add DataPoint to WfEventHandler");

		isAdded = true;
	}
	FUNCTION_EXIT("addDataPoint");
	return isAdded;
}


void WfEventHandler::removeDataPoint (TA_Base_Bus::DataPoint * dp)
{
	FUNCTION_ENTRY("removeDataPoint");
	TA_ASSERT(NULL != dp, "dp is NULL in WfEventHandler::removeDataPoint");


	WfDataPointMap::iterator itr = m_InputDataPoints.find( dp->getDataPointRegisterAddress() );

	if ( itr != m_InputDataPoints.end() )
	{
		m_InputDataPoints.erase( itr );
	}

	itr = m_OutputDataPoints.find( dp->getDataPointRegisterAddress() );

	if ( itr != m_OutputDataPoints.end() )
	{
		m_OutputDataPoints.erase( itr );
	}
	FUNCTION_EXIT("removeDataPoint");

}


///This method will be called when one link is close by connectThread actively
//connectStatus=0,disconnect;
//connectStatus=1,connect;
void WfEventHandler::handleLinkConnectStatusChanged(b_ui8 groupID,string &linkIP,int connectStatus)
{
	FUNCTION_ENTRY("handleLinkConnectStatusChanged");

	TA_Base_Core::ThreadGuard guard(m_linkStatusLock);

	LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugWarn, "HB--Link Status Changed: Group %d - IPAddress:%s Connect Status: %d",groupID,linkIP.c_str(),connectStatus);
	
	m_wfUnit->setWfLinkConnectStatus(groupID,linkIP.c_str(),connectStatus==0?false:true);

	if (!m_linkStatusBadToGood && m_wfUnit->isLinkConnected())
	{
		m_linkStatusBadToGood = true;
		// update m_lastUpdateTimeSec when link status from bad to good 
		timeb currentSystemTime;
		ftime ( &currentSystemTime );
		m_lastUpdateTimeSec = currentSystemTime.time;
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "HB--Link Status bad to good update time:%u", m_lastUpdateTimeSec);
	}
	
	if (m_linkStatusBadToGood && !m_wfUnit->isLinkConnected())
	{
		m_linkStatusBadToGood = false;
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "HB--Link Status good to bad");
	}

	//master link disconnect, other link is ok, if data not tranfered in time set quality to bad; 
	if(0 == connectStatus && m_wfUnit->isMasterWfLink(groupID, linkIP))
	{

		int dataLostDurableTime = m_wfUnit->getDataLostDurableTimeInsec();
		if(false == m_wfUnit->isLinkConnected() || 0 >= dataLostDurableTime)
		{
			LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "submit request set all datapoint's quality to bad,due to all link disconnected");
			m_wfDpProcessor->submitUpdateAllQualityToBad();
			return;
		}
		else if(false == m_isConnectionTimerStarted )
		{
			m_monitorConnectionTimeId = TA_Base_Core::SingletonTimerUtil::getInstance().startPeriodicTimeOutClock(this,dataLostDurableTime*1000,true);
			m_isConnectionTimerStarted = true;
			m_wfDpProcessor->submitStartRecordDpUpdate();
			LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "start timer due to wf master link disconnected,wait data");
		}
		else
		{
			LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Timer has started");
		}
	}

	FUNCTION_EXIT("handleLinkConnectStatusChanged");
}

//mode=1 master
//mode=0 stanby
void WfEventHandler::handleLinkModeStatus(b_ui8 groupID,string &linkIP,int mode)
{
	m_wfUnit->setWfLinkModeStatus(groupID,linkIP.c_str(),mode==0?false:true);
	// change master link
	if (mode != 0)
	{
		timeb currentSystemTime;
		ftime ( &currentSystemTime );
		m_lastUpdateTimeSec = currentSystemTime.time;
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, 
			"HB--Link Mode Changed: Group:%d,IPAddress:%s,mode:%d,update time:%u",
			groupID,linkIP.c_str(),mode, m_lastUpdateTimeSec);
	}
	else
	{
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "HB--Link Mode Changed: Group:%d,IPAddress:%s,mode:%d",groupID,linkIP.c_str(),mode);
	}
}

///This method will be called when link which is used to transfer data changes
//changeReason=0, link connect,                
//changeReason=1, link disconnect,		
//changeReason=2, pscada status SLAVE2MASTER	
//changeReason=3, pscada status MASTER2SLAVE	
void WfEventHandler::handleDataTransferLinkChanged(b_ui8 newGroupID,string &newLinkIP,b_ui8 oldGroupID,string&oldLinkIP,int changeReason)
{
	FUNCTION_ENTRY("handleDataTransferLinkChanged");
    
	LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugWarn, "HB--Link Status Changed: old (Group %d - IPAddress:%s) to new(Group %d - IPAddress:%s) Reason: %d",oldGroupID,oldLinkIP.c_str(),newGroupID,newLinkIP.c_str(),changeReason);
	
	FUNCTION_EXIT("handleDataTransferLinkChanged");
}



void WfEventHandler::setWfUnit(TA_IRS_App::WfUnit* wfUnit)
{
	m_wfUnit = wfUnit;
	int updateLostTime = wfUnit->getUpdateLostPeriodInSec();
	if (updateLostTime <= 0)
	{
		m_updateLostPeriodTime = 0;
	}
	else if (updateLostTime < 60)
	{
		m_updateLostPeriodTime = 60;
	}
	else
	{
		m_updateLostPeriodTime = updateLostTime;
	}
	LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "HB--set update lost period time:%us", m_updateLostPeriodTime);
}

void WfEventHandler::timerExpired(long timerId, void* userData)
{
	if (timerId == m_monitorLastUpdateTimeId)
	{
		timeb currentSystemTime;
		ftime ( &currentSystemTime );
		unsigned long currentTimeSec = currentSystemTime.time;
		bool updateExpired = (currentTimeSec - m_lastUpdateTimeSec >= m_updateLostPeriodTime );
		if(m_isInControl && updateExpired && m_wfUnit->isLinkConnected())
		{
			LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "HB--update expired handle time out");
			handleUpdateTimeOut();
		}
	}
	else if (timerId == m_monitorConnectionTimeId)
	{
		m_isConnectionTimerStarted = false;
		m_monitorConnectionTimeId = -1;
		m_wfDpProcessor->submitStopRecordDpUpdate();
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "timerExpired:submit submitStopRecordDpUpdate");
	}
}

void WfEventHandler::handleUpdateTimeOut()
{
	m_wfUnit->resetLink();
}

void WfEventHandler::setOperationMode(bool bControl)
{
	m_isInControl = bControl;
	if (bControl && m_updateLostPeriodTime > 0)
	{
		// update m_lastUpdateTimeSec when control mode 
		timeb currentSystemTime;
		ftime ( &currentSystemTime );
		m_lastUpdateTimeSec = currentSystemTime.time;

		// start timer if not start
		if (m_monitorLastUpdateTimeId == -1)
		{
			m_monitorLastUpdateTimeId = TA_Base_Core::SingletonTimerUtil::getInstance().startPeriodicTimeOutClock(this, s_UpdateMonitorTimeSlice, false);
		}

		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "HB--Set to control, timer:%d, update time:%u",
			m_monitorLastUpdateTimeId, m_lastUpdateTimeSec);
	}
	else if (m_monitorLastUpdateTimeId != -1)
	{
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "HB--stop update monitor timer:%u for monitor mode", m_monitorLastUpdateTimeId);
		TA_Base_Core::SingletonTimerUtil::getInstance().stopPeriodicTimeOutClock(this, m_monitorLastUpdateTimeId);
		m_monitorLastUpdateTimeId = -1;
	}
}

void WfEventHandler::stop()
{
	TA_Base_Core::SingletonTimerUtil::getInstance().stopPeriodicTimeOutClock(this);

	if (NULL != m_wfDpProcessor)
	{
		m_wfDpProcessor->terminateAndWait();
	}
}
}
