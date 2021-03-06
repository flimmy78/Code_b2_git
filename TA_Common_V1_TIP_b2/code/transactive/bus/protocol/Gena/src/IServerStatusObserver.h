/**
  * The source code in this file is the property of 
  * Combuilder and is not for redistribution
  * in any form.
  *
  * Source:   $File: IConnStateListener.h $
  * @author:  Noel R. Tajanlangit
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/06/10 14:17:48 $
  * Last modified by:  $Noel R. Tajanlangit $
  * 
  * This class contains the interface for connection state listener.
  */

#ifndef __ISERVER_STATUS_OBSERVER_H_INCLUDED__
#define __ISERVER_STATUS_OBSERVER_H_INCLUDED__

#include "CommonDef.h"

namespace TA_Base_Bus
{
	class IServerStatusObserver
	{
	public:
		/*
		* Virtual Destructor
		*/
		virtual ~IServerStatusObserver(){};

		/*
		* onStateChanged
		*/
		virtual void onStateChanged(const std::string& strServer, const GENAConnectionStatus& status ) = 0;
	};

} //TA_Base_Bus


#endif // __ICONNECTION_STATE_LISTENER_H_INCLUDED__