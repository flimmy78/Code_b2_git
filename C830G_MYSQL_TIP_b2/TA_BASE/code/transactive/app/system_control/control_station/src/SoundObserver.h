/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/system_control/control_station/src/SoundObserver.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */
// SoundObserver.h: interface for the SoundObserver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUNDOBSERVER_H__F955A7AA_2F37_4118_9C0D_44AFE571D0E0__INCLUDED_)
#define AFX_SOUNDOBSERVER_H__F955A7AA_2F37_4118_9C0D_44AFE571D0E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "app/alarms_events/alarm_viewer/src/SoundInterface.h"
#include "app/system_control/control_station/src/BtnST.h"

class SoundObserver  :  public TA_Base_App::ISoundInterfaceObserver
{
public:
	SoundObserver(CButtonST& silenceButton);
	virtual ~SoundObserver();

    
    // ISoundInterfaceObserver methods
    /**
     * setState
     *
     * Implemented
     */
    void setState(bool state);

private:

    CButtonST& m_silenceButton;
};

#endif // !defined(AFX_SOUNDOBSERVER_H__F955A7AA_2F37_4118_9C0D_44AFE571D0E0__INCLUDED_)
