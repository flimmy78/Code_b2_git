/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/radio/RadioTetraAgent/RadioProtocolLibrary/src/RadioMethodSelect.cpp $
  * @author:  Andy Parker
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * This class encapsulates the Radio API Select method.
  *
  */
///////////////////////////////////////////////////////////
//  RadioMethodSelect.cpp
//  Implementation of the Class RadioMethodSelect
//  Created on:      29-Nov-2003 09:57:09 AM
///////////////////////////////////////////////////////////

#include "RadioMethodSelect.h"
#include "RadioProtocol.h"
#include "core/utilities/src/TAAssert.h"

using namespace TA_IRS_App;

#define SELECT_LENGTH                     4


RadioMethodSelect::RadioMethodSelect(RadioSessionReference sessionRef, RadioCallReference callRef) 
                   : RadioMethodCallReference(SELECT_LENGTH,METHOD_SELECT,sessionRef,callRef)
{
}



RadioMethodSelect::~RadioMethodSelect()
{
}


