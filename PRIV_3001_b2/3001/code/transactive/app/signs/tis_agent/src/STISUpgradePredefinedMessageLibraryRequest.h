#ifndef STISUPGRADEPREDEFINEDMESSAGELIBRARYREQUEST_H_INCLUDED
#define STISUPGRADEPREDEFINEDMESSAGELIBRARYREQUEST_H_INCLUDED

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  *
  * Source:    $File: //depot/PRIV_3001/3001/transactive/app/signs/tis_agent/src/STISUpgradePredefinedMessageLibraryRequest.h $
  * @author:   Robin Ashcroft
  * @version:  $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  */

#include "app/signs/tis_agent/src/STISMessage.h"

namespace TA_IRS_App
{

	class STISUpgradePredefinedMessageLibraryRequest : public STISMessage
	{
	public:

		STISUpgradePredefinedMessageLibraryRequest();

		~STISUpgradePredefinedMessageLibraryRequest();

		void setData( unsigned long libraryVersion );

		virtual std::vector<unsigned char> createProtocolMessage();

		virtual void log(bool sendSuccess);

	private:

		unsigned long m_libraryVersion;

	};

}

#endif
