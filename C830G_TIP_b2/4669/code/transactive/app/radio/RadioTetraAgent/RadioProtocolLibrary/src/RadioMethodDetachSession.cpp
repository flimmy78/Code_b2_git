/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/radio/RadioTetraAgent/RadioProtocolLibrary/src/RadioMethodDetachSession.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */
///////////////////////////////////////////////////////////
//
//  RadioMethodDetachSession.cpp
//  Implementation of the Class RadioMethodDetachSession
//  Generated by Enterprise Architect
//  Created on:      06-Nov-2003 09:58:38
//  Original author: 
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////

#include "RadioMethodDetachSession.h"
#include "RadioProtocol.h"

using namespace TA_IRS_App;

/**
* Constructor
* @param    sessionRef
*/
RadioMethodDetachSession::RadioMethodDetachSession(RadioSessionReference sessionRef)
						 :RadioMethod(0,METHOD_DETACH_SESSION,sessionRef)
{

}

RadioMethodDetachSession::~RadioMethodDetachSession()
{

}




