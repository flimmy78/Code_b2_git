/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/exceptions/src/SoundInitException.cpp $
  * @author:  Justin Ebedes
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * This exception is raised when there is an error
  * initialising the sound card.
  *
  */

#include "SoundInitException.h"


namespace TA_Base_Core
{
	SoundInitException::SoundInitException()
	{

	}

	SoundInitException::SoundInitException(const std::string& msg) 
		: TransactiveException(msg)
	{

	}
		

	SoundInitException::~SoundInitException()
	{

	}
}

