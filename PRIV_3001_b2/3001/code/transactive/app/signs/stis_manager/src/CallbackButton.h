/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/signs/stis_manager/src/CallbackButton.h $
  * @author:  Adam Radics
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * This is a button that listens for its own button press events
  * and passes them on to the specified interface.
  * Done so that the owning dialog doesnt have to listen for and handle the events.
  */

#if !defined(AFX_CALLBACKBUTTON_H__DBFC6652_457D_4F5E_910E_FD94B027CEE3__INCLUDED_)
#define AFX_CALLBACKBUTTON_H__DBFC6652_457D_4F5E_910E_FD94B027CEE3__INCLUDED_

#include "IButtonListener.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace TA_IRS_App
{

    class CallbackButton : public CButton
    {

    public:
	    CallbackButton();
        virtual ~CallbackButton();

        void setCallback(IButtonListener* buttonPressListener);

    public:

    // Overrides
	    // ClassWizard generated virtual function overrides
	    //{{AFX_VIRTUAL(CallbackButton)
	    //}}AFX_VIRTUAL

	    // Generated message map functions
    protected:
	    //{{AFX_MSG(CallbackButton)
		afx_msg BOOL onButtonClicked();
	    //}}AFX_MSG

	    DECLARE_MESSAGE_MAP()

    private:
        IButtonListener* m_buttonPressListener;

    };

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

} // TA_IRS_App

#endif // !defined(AFX_CALLBACKBUTTON_H__DBFC6652_457D_4F5E_910E_FD94B027CEE3__INCLUDED_)
