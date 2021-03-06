/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/signs/ttis_manager/src/TrainScheduleUpgrades.h $
  * @author:  Adam Radics
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * This is used to make download and upgrade requests. Also to retry those
  * requests if necessary.
  *
  * Messages are sent to the given window, they are:
  * WM_UPDATE_DOWNLOADLIST (wParam is a TrainDownloadStatus*, it must be deleted when used)
  */


#if !defined(TrainScheduleUpgrades_H)
#define TrainScheduleUpgrades_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "app/signs/ttis_manager/src/AbstractTrainDownloads.h"

#include "bus/trains/TrainSelectionComponent/src/TrainList.h"


namespace TA_IRS_App
{


    class TrainScheduleUpgrades : public AbstractTrainDownloads
    {

    public:

        /**
          * TrainScheduleUpgrades
          *
          * Constructor
          *
          * @param window   the window to receive the update messages.
          */
        TrainScheduleUpgrades(CWnd* window);

        virtual ~TrainScheduleUpgrades();


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
            return ScheduleUpgrade;
        };

    };


} // TA_IRS_App

#endif // !defined
