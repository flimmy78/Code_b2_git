/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  *
  * Source:    $File: //depot/PRIV_3001/3001/transactive/app/system_control/banner/pages/call_page/src/CallBannerInitialiser.h $
  * @author:   Dirk McCormick
  * @version:  $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * This thread is used to separate the initialisation of the call banner
  * from MFC windowing functions so that the banner is viewable without
  * having to be initialised completely.
  *
  */


#ifndef CALL_BANNER_INITIALISER_H
#define CALL_BANNER_INITIALISER_H


#include "core/threads/src/Thread.h"


namespace TA_IRS_App
{
    // Forward declaration
    class CallPage;


    class CallBannerInitialiser:  public TA_Base_Core::Thread
    {

    public:


        /**
         *  Constructor
         */
        CallBannerInitialiser(CallPage& callPage);

        /**
         *  Destructor.
         */
	    virtual ~CallBannerInitialiser();


    private:

        /**
         *  Called by the start method.
         */
        void run();

        /**
         *  Terminates the thread
         */
        void terminate();



        CallBannerInitialiser();
        CallBannerInitialiser(const CallBannerInitialiser&);
        const CallBannerInitialiser& operator=(const CallBannerInitialiser&);


        volatile bool m_running;
        CallPage& m_callPage;

    };


} // TA_IRS_App

#endif // CALL_BANNER_INITIALISER_H
