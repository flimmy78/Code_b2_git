/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/radio/RadioTetraAgent/RadioProtocolLibrary/src/TextToReferenceEventReader.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */
///////////////////////////////////////////////////////////
//
//  DisconnectEventReader.cpp
//  Implementation of the Class TextToReferenceEventReader
//  Generated by Enterprise Architect
//  Created on:      10-Nov-2003 16:38:14
//  Original author: 
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////

#include "TextToReferenceEventReader.h"
#include "core/utilities/src/TAAssert.h"

namespace TA_IRS_App
{
	const unsigned int TextToReferenceEventReader::EVENT_TEXT_TO_REFERENCE_LENGTH =  36;
    const unsigned int TextToReferenceEventReader::STRING_REFERENCE_START         =  0;
    const unsigned int TextToReferenceEventReader::REFERENCE_START                =  32;


    TextToReferenceEventReader::TextToReferenceEventReader(RadioEvent& event)
		   : RadioEventReader(event,EVENT_TEXT_TO_REFERENCE,EVENT_TEXT_TO_REFERENCE_LENGTH)
    {
    }

    TextToReferenceEventReader::~TextToReferenceEventReader()
    {
    }


    const TextToReferenceEventReader::RadioReference TextToReferenceEventReader::getReference() const
    {
	    return getParameterLong(REFERENCE_START);
    }

    const std::string TextToReferenceEventReader::getReferenceText() const
    {
		return getParameterShortString(STRING_REFERENCE_START);
    }
     

}

