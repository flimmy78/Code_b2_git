/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/signs/ttis_manager/src/TrainScheduleDownloads.h $
  * @author:  Adam Radics
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * This is used to make download and upgrade requests. Also to retry those
  * requests if necessary.
  *
  * Messages are sent to the given window, they are:
  * WM_UPDATE_DOWNLOADLIST (wParam is a TrainDownloadStatus*, it must be deleted when used)
  */


#if !defined(TrainScheduleDownloads_H)
#define TrainScheduleDownloads_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "app/signs/ttis_manager/src/AbstractTrainDownloads.h"

#include "bus/trains/TrainSelectionComponent/src/TrainList.h"


namespace TA_IRS_App
{


    class TrainScheduleDownloads : public AbstractTrainDownloads
    {

    public:

        /**
          * TrainScheduleDownloads
          *
          * Constructor
          *
          * @param window   the window to receive the update messages.
          */
        TrainScheduleDownloads(CWnd* window);

        virtual ~TrainScheduleDownloads();


    protected:


        /**
         * This will perform the actual download/upgrade request to the TIS agent.
         * It will return success or failure to submit the operation, and optionally an error code. Further status is updated by incoming messages.
         * 
         * @return true if the request was submitted, false if there was an error encountered
         * 
         * @param trainList    The list of trains to perform the actual request on
         * @param errorString    Optionally this will contain an error string if the download fails
         */
        virtual bool processRequests(const TA_Base_Core::TrainList& trainList, std::string& errorString);


        /**
          * getDownloadType
          *
          * Subclasses will return what type of train download they do.
          *
          * @return A download/upgrade type
          */
        inline virtual TrainDownloadType getDownloadType()
        {
            return ScheduleDownload;
        };

    };


} // TA_IRS_App

#endif // !defined
