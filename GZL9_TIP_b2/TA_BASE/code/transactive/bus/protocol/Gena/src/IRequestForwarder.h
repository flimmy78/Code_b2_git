/**
  * The source code in this file is the property of 
  * Combuilder and is not for redistribution
  * in any form.
  *
  * Source:   $File: IRequestForwarder.h $
  * @author:  Noel R. Tajanlangit
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/08/14 14:17:48 $
  * Last modified by:  $Noel R. Tajanlangit $
  * 
  * This file contains the interface declaration for IRequestForwarder
  */


#ifndef __IREQUEST_FORWARDER_H_INCLUDED__
#define __IREQUEST_FORWARDER_H_INCLUDED__

#include "CommonDef.h"

#include <string>

namespace TA_Base_Bus
{
	class IRequestForwarder
	{
	public:
		/*
		* Virtual Destructor
		*/
		virtual ~IRequestForwarder(){};

		/*
		* Virtual subscribe
		*/
		virtual int subscribe(const std::string& topicURL, const std::string& notification) = 0;

		/*
		* Virtual unsubscribe
		*/
		virtual void unsubscribe(const std::string& topicURL) = 0;

	};

} //TA_Base_Bus

#endif //__IREQUEST_FORWARDER_H_INCLUDED__