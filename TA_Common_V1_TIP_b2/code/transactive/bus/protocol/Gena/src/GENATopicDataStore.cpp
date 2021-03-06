
#include "GENATopicDataStore.h"
#include "core/utilities/src/DebugUtil.h"


namespace TA_Base_Bus
{

	GENATopicDataStore::GENATopicDataStore()
	{
		FUNCTION_ENTRY("Constructor");
		FUNCTION_EXIT;
	}

	GENATopicDataStore::~GENATopicDataStore()
	{
		FUNCTION_ENTRY("Destructor");
		FUNCTION_EXIT;
	}

	T_GENATopicDataList GENATopicDataStore::getAllData(const std::string& topicName )
	{
		FUNCTION_ENTRY("getAllData");
		T_GENATopicDataList objRetVal;
		

		FUNCTION_EXIT;
		return objRetVal;
	}
	
	void GENATopicDataStore::synchronizeBegin(const std::string& topicName)
	{
		FUNCTION_ENTRY("synchronizeBegin");
		FUNCTION_EXIT;
	}

	void GENATopicDataStore::synchronizeEnd(const std::string& topicName)
	{
		FUNCTION_ENTRY("synchronizeEnd");
		FUNCTION_EXIT;
	}

	void GENATopicDataStore::updateDataImpl(const std::string& topicName, GENATopicDataPtr pData)
	{
		//FUNCTION_ENTRY("updateDataImpl");

		//T_DatatStoreIter itr = m_DataStoreMap.find(topicName);

		//if(itr == m_DataStoreMap.end())
		//{
		//	T_GENATopicDataList DataListVect;
		//	std::string test = pData->getTopicName();
		//	DataListVect.push_back(pData);
		//	m_DataStoreMap[topicName]= DataListVect;
		//	//m_DataStoreMap.insert(T_DataStoreMap::value_type(topicName, pData));	
		//}
		//else
		//{
		//	itr->second.push_back(pData);
		//}

		//FUNCTION_EXIT;
	}

}