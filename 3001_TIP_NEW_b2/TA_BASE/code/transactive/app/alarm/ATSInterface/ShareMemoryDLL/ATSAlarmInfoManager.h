// ATSAlarmInfoManager.h: interface for the ATSAlarmInfoManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATSAlarmInfoManager_H__ED76F0F8_DB2F_4F01_880C_0C395F2B32FE__INCLUDED_)
#define AFX_ATSAlarmInfoManager_H__ED76F0F8_DB2F_4F01_880C_0C395F2B32FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CacheDataManager.h"

#include "DataStructInfo.h"
//#include "bus/CacheData/CacheDataEntity/src/CacheDataTypes.h"


namespace TA_Base_Bus
{


// 	enum  SharedMemoryDataSize
// 	{
// 		LongSharedMemoryData=sizeof(long),
// 		ULongSharedMemoryData=sizeof(unsigned long),
// 		DoubleSharedMemoryData=sizeof(double),
// 		BoolSharedMemoryData=sizeof(long),
// 		UShortSharedMemoryData=sizeof(unsigned short),
// 		FILETIMESharedMemoryData=sizeof(FILETIME)
// 	};


	class ATSAlarmInfoManager : public CacheDataManager<std::string, ATSAlarmQueueItem>
	{
	public:
		ATSAlarmInfoManager(long maxBlockCount,long blockByteSize);
		virtual ~ATSAlarmInfoManager();
// 		virtual std::string readCachDataKeyFromMem(ShareMemoryHelper* mem, char* pos);
// 		virtual std::string getCacheDataKey(ATSAlarmQueueItem* cacheData);
		virtual bool writeCacheDataToMem(ATSAlarmQueueItem* cacheData,ShareMemoryHelper* mem, char* pos);
		virtual bool readCacheDataFromMem(ATSAlarmQueueItem* cacheData,ShareMemoryHelper* mem, char* pos);


	 
		 
		 
         //the following attribute should be updated based on the "train information" related tables in database.
		enum TrainInformationAttributeSize
		{			    
			AlarmIDSize=ALARM_ID_SIZE+LongSharedMemoryData,			 
			ACKTimeSize=ULongSharedMemoryData,
			MillisecondTimeSize=sizeof(MillisecondTime),
			CloseTimeSize=ULongSharedMemoryData, // the close time if any
			AssetNameSize=ASSERT_NAME_SIZE+LongSharedMemoryData, // the asset name, max 20 characters.
			AlarmSeveritySize=ULongSharedMemoryData, // the severity of the alarm
			AlarmDescriptionSize=ALARM_DESCRIPTION_SIZE+LongSharedMemoryData, // the description of the alarm, max 200 characters.
			AlarmAcknowledgeBySize=OPERATOR_ID_SIZE+LongSharedMemoryData, // the operator who acknowledge this alarm, if any
			StateSize=LongSharedMemoryData, // the alarm state
			LocationIdSize=LOCATION_ID_SIZE+LongSharedMemoryData, // the location (Sect D.5 Station Code Name) that alarm is generated, max 4 characters.
			parentAlarmIDSize=ALARM_ID_SIZE+LongSharedMemoryData, // the parent alarm ID
			AvalancheHeadIDSize=ALARM_ID_SIZE+LongSharedMemoryData, // related to the avalanche head if applicable
			IsHeadOfAvalancheSize=LongSharedMemoryData, // whether the alarm is the head of avalanche
			IsChildOfAvalancheSize=LongSharedMemoryData, // whether the alarm is the child of avalanche
			MmsStateSize=LongSharedMemoryData, // the MMS state
			AlarmValueSize=ALARM_VALUE_SIZE+LongSharedMemoryData, // the value of the data point related to the alarm, max 16 characters.
			omAlarmSize=UCharMemoryData, // O?ˉ for Operation Alarm, ??M?ˉ for maintenance 
            AlarmTypeSize=ALARM_TYPE_SIZE+LongSharedMemoryData,
			SystemKeySize=SYSTEM_KEY_SIZE+LongSharedMemoryData,
			SubSystemKeySize=SUBSYSTEM_KEY_SIZE+LongSharedMemoryData,

			TotalSizeLength=AlarmIDSize+ACKTimeSize+MillisecondTimeSize+CloseTimeSize+AssetNameSize+AlarmSeveritySize
			+AlarmDescriptionSize+AlarmAcknowledgeBySize+StateSize+LocationIdSize+parentAlarmIDSize+AvalancheHeadIDSize+IsHeadOfAvalancheSize
			+IsChildOfAvalancheSize+MmsStateSize+AlarmValueSize+omAlarmSize+AlarmTypeSize+SystemKeySize+SubSystemKeySize,
			MaxItemCount=11000					
		};

	};
}

#endif // !defined(AFX_ATSAlarmInfoManager_H__ED76F0F8_DB2F_4F01_880C_0C395F2B32FE__INCLUDED_)
