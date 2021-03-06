/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/scada/Prototypes/ATSDemo/DummyControlStation.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */
#ifndef DUMMYCONTROLSTATION_h
#define DUMMYCONTROLSTATION_h

class DummyControlStation
{
public:

	DummyControlStation();
	virtual ~DummyControlStation();

	void launchApps();

private:

	PROCESS_INFORMATION m_processInfo;
	HWND m_hSCADAProcess1;
	HWND m_hSCADAProcess2;
	HWND m_hSCADAProcess3;
	HWND m_hAlarmProcess1;
	HWND m_hAlarmProcess2;
	HWND m_hAlarmProcess3;

//	void showSCADA();
//	void showAlarm();
	void showAppsOn1Screen();
	void showAppsOnScreen1();
	void showAppsOnScreen2();
	void showAppsOnScreen3();
	void killWindow ( HWND & hWindow );

	int m_numScreens;
	int m_screenWidth;
	int m_screenHeight;
	int m_alarmHeight;
	CString m_alarmEXE;
	CString m_gwxEXE;
	CString m_alarmNr;
	CString m_alarmBanner;
	CString m_leftSCADA;
	CString m_middleSCADA;
	CString m_rightSCADA;
};

#endif