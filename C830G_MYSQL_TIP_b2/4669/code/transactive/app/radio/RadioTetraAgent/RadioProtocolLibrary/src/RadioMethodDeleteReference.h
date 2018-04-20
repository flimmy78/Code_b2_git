/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/radio/RadioTetraAgent/RadioProtocolLibrary/src/RadioMethodDeleteReference.h $
  * @author:  Andy Parker
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * This class manages the Delete Reference radio API call
  *
  */
///////////////////////////////////////////////////////////
//
//  RadioMethodDeleteReference.h
//  Implementation of the Class RadioMethodDeleteReference
//  Generated by Enterprise Architect
//  Created on:      10-Nov-2003 15:15:18
//  Original author: 
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////


#if !defined(RadioMethodDeleteReference_99B7FB58_BEC4_41ff_9DBE_849ECD750A77__INCLUDED_)
#define RadioMethodDeleteReference_99B7FB58_BEC4_41ff_9DBE_849ECD750A77__INCLUDED_

#include "RadioMethod.h"
/**
* Obtains a new reference according to the specified Reference_Type.
* @version 1.0
* @generator Enterprise Architect
* @created 10-Nov-2003 15:15:18
*/


namespace TA_IRS_App
{

	class RadioMethodDeleteReference : public RadioMethod
	{
	public:
		enum ReferenceType 
        {                      
           CALL_REFERENCE, 
		   SDS_REFERENCE, 
		   DATA_REFERENCE, 
		   SUBSCRIBER_REFERENCE,
           AUDIO_REFERENCE,
           CAD_REFERENCE,
           MONITOR_REFERENCE,
           SEARCH_REFERENCE 
        };

		RadioMethodDeleteReference(RadioSessionReference sessionRef);
		virtual ~RadioMethodDeleteReference();

	public:
		/**
		* Constructor
		* @param    sessionRef
		*/
		void setReference(RadioMethodDeleteReference::ReferenceType referenceType,unsigned long reference);

    private:

        static const unsigned int DELETE_REFERENCE_METHOD_LENGTH;
        static const unsigned int REFERENCE_TYPE_START;
        static const unsigned int REFERENCE_PARAMETER_POSITION;
	};
}; // Namespace

#endif // !defined(RadioMethodDeleteReference_99B7FB58_BEC4_41ff_9DBE_849ECD750A77__INCLUDED_)