/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/radio/RadioTetraAgent/RadioProtocolLibrary/src/SelectEventReader.h $
  * @author:  Andy Parker
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * Implementation of Select Event Reader
  *
  */
///////////////////////////////////////////////////////////
//
//  SelectEventReader.h
//  Implementation of the Class SelectEventReader
//  Generated by Enterprise Architect
//  Created on:      10-Nov-2003 16:38:14
//  Original author: 
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////


#if !defined(SelectEventReader_INCLUDED_)
#define SelectEventReader_INCLUDED_

#include "RadioEventReader.h"


namespace TA_IRS_App
{
	class SelectEventReader : public RadioEventReader
	{
		public:

			typedef unsigned long RadioReference;

			SelectEventReader(RadioEvent& event);
			virtual ~SelectEventReader();

		public:

			const RadioReference getReference() const;

		private:

			static const unsigned int SELECT_EVENT_LENGTH;
			static const unsigned int SELECT_REFERENCE_START;
	};
};

#endif // !defined(SelectEventReader_INCLUDED_)
