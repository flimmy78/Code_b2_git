/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/core/exceptions/src/SoundInitException.h $
  * @author:  Justin Ebedes
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * This exception is raised when there is an error
  * initialising the sound card.
  *
  */


#if !defined(SOUNDINITEXCEPTION_H)
#define SOUNDINITEXCEPTION_H

#include "TransactiveException.h"
#include <string>																

namespace TA_Base_Core
{
	class SoundInitException : public TransactiveException  
	{
	public:
		SoundInitException();
		SoundInitException(const std::string& msg);
		virtual ~SoundInitException();
	};
}

#endif // SOUNDINITEXCEPTION_H

