//Author: Noel R. Tajanlangit

#ifndef __COMMON_DEFINES_H_INCLUDED__
#define __COMMON_DEFINES_H_INCLUDED__


#define WMU_UPDATE_COUNTERS WM_USER + 1
#define WMU_UPDATE_ERROR_COUNT WM_USER + 2
#define BM_CLICK 0x00F5

#define UPDATE_AUTO_TIMER 1
#define UPDATE_TIME 1000

#define DEFAULT_EVENT_SIZE		100
#define DEFAULT_THREAD_COUNT	1
#define DEFAULT_INTERVAL		1000
#define DEFAULT_LOCATION		1
#define DEFAULT_SUBMIT_BATCH_SIZE		5

#define DEFAULT_PREFIX "EventGenerator"

#define RPARAM_EVENTCOUNT			"EventCount"
#define RPARAM_THREADCOUNT			"ThreadCount"
#define RPARAM_SUBMITINTERVAL		"SubmitInterval"
#define RPARAM_BATCHCOUNT			"BatchSize"
#define RPARAM_AUTOSTART			"AutoStartTest"



#endif //__COMMON_DEFINES_H_INCLUDED__