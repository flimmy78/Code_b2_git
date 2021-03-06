/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP/3001/transactive/app/signs/ttis_manager/src/TrainLibraryDownloads.h $
  * @author:  Adam Radics
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2009/12/29 14:12:57 $
  * Last modified by:  $Author: grace.koh $
  *
  * This is used to make library download requests. Also to retry those
  * requests if necessary.
  *
  * Messages are sent to the given window, they are:
  * WM_UPDATE_DOWNLOADLIST (wParam is a TrainDownloadStatus*, it must be deleted when used)
  */


#if !defined(TrainLibraryDownloads_H)
#define TrainLibraryDownloads_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "AbstractTrainDownloads.h"

#include "bus/trains/TrainSelectionComponent/src/TrainList.h"


namespace TA_IRS_App
{


    class TrainLibraryDownloads : public AbstractTrainDownloads
    {
    
    public:

        /** 
          * TrainLibraryDownloads
          *
          * Constructor
          *
          * @param window   the window to receive the update messages.
          */
        TrainLibraryDownloads(CWnd* window);

        virtual ~TrainLibraryDownloads();

		void requestCancelDownload(const TA_IRS_Bus::CommonTypes::TrainIdList& cancelList);

		virtual void run();


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
            return LibraryDownload;
        };
	private:
		void processCancelDownloadRequest();

        TA_Base_Core::ReEntrantThreadLockable m_cancelDownLoadTrainsLock;
		TA_IRS_Bus::CommonTypes::TrainIdList m_cancelDownloadTrains;

    };


} // TA_IRS_App

#endif // !defined
