/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/radio/RadioTetraAgent/src/RadioSessionException.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */
///////////////////////////////////////////////////////////
//
//  RadioSessionException.h
//  Implementation of the Class RadioSessionException
//  Generated by Enterprise Architect
//  Created on:      06-Nov-2003 15:03:54
//  Original author: 
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////


#if !defined(RadioSessionException_0D279184_D225_4c31_9777_59AC3A1EFFAB__INCLUDED_)
#define RadioSessionException_0D279184_D225_4c31_9777_59AC3A1EFFAB__INCLUDED_

#include "app/radio/RadioTetraAgent/src/RadioException.h"
/**
* This exception is thrown when a radio session method is called and the session
* has not been or completed initialisation.
* @version 1.0
* @generator Enterprise Architect
* @created 06-Nov-2003 15:03:54
*/

namespace TA_IRS_App
{
	class RadioSessionException : public RadioException
	{
		public:
			RadioSessionException(const std::string& errorText,long errorNumber) throw();
			virtual ~RadioSessionException() throw();

            long getErrorNumber() const;

		private:

			long  m_errorNumber;
	};

    inline long RadioSessionException::getErrorNumber() const
    {
        return m_errorNumber;
    }
};

#endif // !defined(RadioSessionException_0D279184_D225_4c31_9777_59AC3A1EFFAB__INCLUDED_)
