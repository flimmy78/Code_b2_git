/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/radio/RadioTetraAgent/RadioProtocolLibrary/src/RadioMethodCallReference.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */
///////////////////////////////////////////////////////////
//
//  RadioMethodCallReference.h
//  Implementation of the Class RadioMethodCallReference
//  Generated by Enterprise Architect
//  Created on:      06-Nov-2003 08:37:06
//  Original author: 
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////


#if !defined(RadioMethodCallReference_EB712232_513D_42ce_84AE_D80A48766D81__INCLUDED_)
#define RadioMethodCallReference_EB712232_513D_42ce_84AE_D80A48766D81__INCLUDED_

#include "RadioMethod.h"
/**
* Abstract class for all methods which simply pass the call reference as their
* first parameter
* @version 1.0
* @generator Enterprise Architect
* @created 06-Nov-2003 08:37:06
*/

namespace TA_IRS_App
{
	class RadioMethodCallReference : public RadioMethod
	{

		public:

			typedef unsigned long RadioCallReference;

			RadioMethodCallReference(unsigned long messageSize, unsigned long messageType, RadioSessionReference sessionRef, RadioCallReference callRef);
			virtual ~RadioMethodCallReference();

		public:
			/**
			* Constructor
			* @param    messageSize
			* @param    messageType
			* @param    sessionRef
			* @param    callRef
			*/
	};
};

#endif // !defined(RadioMethodCallReference_EB712232_513D_42ce_84AE_D80A48766D81__INCLUDED_)
