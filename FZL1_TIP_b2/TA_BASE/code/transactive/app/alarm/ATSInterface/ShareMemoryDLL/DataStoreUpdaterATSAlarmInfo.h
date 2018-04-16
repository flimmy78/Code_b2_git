// DataStoreUpdaterATSAlarmQueueItem.h: interface for the DataStoreUpdaterATSAlarmQueueItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATASTOREUPDATERATSAlarmQueueItem_H__6199400B_C677_42D0_B3EF_1CD13328F051__INCLUDED_)
#define AFX_DATASTOREUPDATERATSAlarmQueueItem_H__6199400B_C677_42D0_B3EF_1CD13328F051__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string> 
#include "CacheDataWraper.h"
#include "ATSAlarmInfoManager.h"
#include "DataStoreUpdater.h"
namespace TA_Base_Bus
{
	class DataStoreUpdaterATSAlarmInfo  :public DataStoreUpdater<std::string , ExAlarmQueueItem,ATSAlarmInfoManager>
	{
	public:
		
		virtual ~DataStoreUpdaterATSAlarmInfo();
		void Initialize(std::vector< boost::shared_ptr<ExAlarmQueueItem> >& batch);
		static DataStoreUpdaterATSAlarmInfo* getInstance();
		static void release();		
		 
	private:
		DataStoreUpdaterATSAlarmInfo();
		 
		bool m_isInitialized;
		//TA_Base_Core::NonReEntrantThreadLockable m_initilizedLock;
		
		static DataStoreUpdaterATSAlarmInfo*  m_Instance;
		//static TA_Base_Core::NonReEntrantThreadLockable m_singletonLock;
		
		};
}
#endif // !defined(AFX_DATASTOREUPDATERATSAlarmQueueItem_H__6199400B_C677_42D0_B3EF_1CD13328F051__INCLUDED_)
