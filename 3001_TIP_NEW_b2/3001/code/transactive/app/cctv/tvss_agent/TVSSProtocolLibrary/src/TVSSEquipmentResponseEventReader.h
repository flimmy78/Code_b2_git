#pragma once
#include<vector>

#include "app/cctv/tvss_agent/TVSSProtocolLibrary/src/TVSSProtocol.h"
#include "app/cctv/tvss_agent/TVSSProtocolLibrary/src/TVSSEventReader.h"

namespace TA_IRS_App
{
	class TVSSEquipmentResponseEventReader :public TVSSEventReader
	{
	public:
		TVSSEquipmentResponseEventReader(boost::shared_ptr<TVSSEvent> event);
		virtual ~TVSSEquipmentResponseEventReader(void);

	   /**
	    * Use to initialize Data mapping for Equipment Alarm Response
		*/
		void initializeAlarmResponseMap(void);
	
	public:
		unsigned char getAlarmResponseOrigin(void);
       /**
        * Return the Data of the Alarm Response based on the specified dataIndex
		* @param dataIndex
		* dataIndex: 1 , for Data1
		*            2 , for Data2
		*            3 , for Data3
		*            4 , for Data4
		*/
		unsigned char getAlarmResponseData(int dataIndex);

	   /**
        * Return the Data length of the Equipment Alarm Response
		*
		*/
		int getLengthAlarmResponseData();

	private:
		std::vector<int> AlarmResponseData;
	};
};