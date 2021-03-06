
#if !defined(RadioProtocol_H)
#define RadioProtocol_H

namespace TA_IRS_App
{

#define  STX_VALUE 0x02
#define  ETX_VALUE 0x03

#define METHOD_HEADER_STX_START_POSITION              0
#define METHOD_HEADER_TRANSACTION_ID_START_POSITION   1       

#define  EVENT_LENGTH_PROFILE_REQUEST              165
#define  EVENT_LENGTH_SUBSCRIBER_MONITORING         58
#define  EVENT_LENGTH_DGNA_QUERY                    46
#define  EVENT_LENGTH_CALL_CANCEL_REQUEST           22
#define  EVENT_LENGTH_BASE_PROFILE_UPDATE           23
#define  EVENT_LENGTH_VARIABLE_PROFILE_UPDATE       13
#define  EVENT_LENGTH_RADIO_SYSTEM_STATUS           8

#define  MESSAGE_ID_PROFILE_REQUEST                "A39"
#define  MESSAGE_ID_SUBSCRIBER_MONITORING          "A40"
#define  MESSAGE_ID_DGNA_REQUEST                   "A41"
#define  MESSAGE_ID_CALL_FORWARDING_REQUEST        "A32"
#define  MESSAGE_ID_CANCEL_CALL_FORWARDING        "A33"
#define  MESSAGE_ID_QUERY_CALL_FORWARDING          "A34"
#define  MESSAGE_ID_PROFILE_UPDATE                 "A42"
//#define  MESSAGE_ID_RADIO_SYSTEM_STATUS            "A37"
#define  MESSAGE_ID_OCC_RADIO_SYSTEM_STATUS          "A37"
#define  MESSAGE_ID_STATION_RADIO_SYSTEM_STATUS      "A38"

#define EVENT_PROFILE_UPDATE_NUM_POSITION 20

	enum {
		TYPE_PROFILE_REQUEST = 1,
		TYPE_SUBSCRIBER_MONITOR,
		TYPE_DGNA_REQUEST,
		TYPE_CALL_FORWARDING_REQUEST,
		TYPE_CANCEL_CALL_FORWARDING,
		TYPE_QUERY_CALL_FORWARDING,
		TYPE_PROFILE_UPDATE,
		TYPE_RADIO_SYSTEM_STATUS
	};

#define STATUS_OK 1

}
 

#endif // !defined(RadioProtocol_H)
