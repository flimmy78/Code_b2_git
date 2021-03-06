/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/radio/RadioTetraAgent/RadioProtocolLibrary/src/RadioMethodDisconnect.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */
///////////////////////////////////////////////////////////
//
//  RadioMethodDisconnect.cpp
//  Implementation of the Class RadioMethodDisconnect
//  Generated by Enterprise Architect
//  Created on:      15-Nov-2003 11:59:15
//  Original author: 
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////

#include "RadioMethodDisconnect.h"
#include "RadioProtocol.h"

using namespace TA_IRS_App;


#define DISCONNECT_METHOD_PARAMETER_LENGTH  4


/**
* Constructor
* @param    sessionRef
* @param    callRef
*/
RadioMethodDisconnect::RadioMethodDisconnect(RadioSessionReference sessionRef,RadioCallReference callRef)
: RadioMethodCallReference(DISCONNECT_METHOD_PARAMETER_LENGTH,METHOD_DISCONNECT,sessionRef,callRef)
{
}


RadioMethodDisconnect::~RadioMethodDisconnect()
{
}




