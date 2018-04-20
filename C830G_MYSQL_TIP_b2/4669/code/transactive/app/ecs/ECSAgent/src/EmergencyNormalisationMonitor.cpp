/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/ecs/ECSAgent/src/EmergencyNormalisationMonitor.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */
///////////////////////////////////////////////////////////
//
//  EmergencyNormalisationMonitor.cpp
//  Implementation of the Class EmergencyNormalisationMonitor
//  Generated by Enterprise Architect
//  Created on:      25-Sep-2003 18:53:34
//  Original author:
//
///////////////////////////////////////////////////////////
//  Modification history:
//
//
///////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma warning(disable : 4786 4146 4018 4250 4290 4503)
#endif // defined _MSC_VER

#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/TAAssert.h"

#include "app/ecs/ECSAgent/src/ItaEcsAlarms.h"
#include "app/ecs/ECSAgent/src/EmergencyNormalisationMonitor.h"


EmergencyNormalisationMonitor::EmergencyNormalisationMonitor(
	ItaEcsDatapoints& theDatapoints,
	ItaEcsAlarms& theAlarms)
: m_theDatapoints(theDatapoints),
  m_theAlarms(theAlarms)
{
    FUNCTION_ENTRY("Constructor");

	m_theDatapoints.attachEmergencyObserver(this);

    FUNCTION_EXIT;
}


// ExceptionChecked
EmergencyNormalisationMonitor::~EmergencyNormalisationMonitor()
{
    FUNCTION_ENTRY("Destructor");

	m_theDatapoints.detachEmergencyObserver(this);

    FUNCTION_EXIT;
}

void EmergencyNormalisationMonitor::processEmergencyUpdate(unsigned long zoneId, bool value)
{
	FUNCTION_ENTRY("processEmergencyUpdate");

    if (false == m_isEnabled)
    {
        LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, "Skipping operation in operation mode");        
		FUNCTION_EXIT;
        return;
    }

	if (true == value)
	{
		// only interested when the value is false (no longer in emergency)
        LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, 
            "Ignoring processing when entering an emergency state, not for emergency normalisation alarm.");        
		FUNCTION_EXIT;
		return;
	}

	if (m_theDatapoints.getEmergencyApplied(zoneId) == false)
	{
		// the master mode was not applied for this emergency
        LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugInfo, 
            "No emergency normalisation alarm raise for ECS Zone %ld since no Master Mode applied",
			zoneId);   
		FUNCTION_EXIT;
		return;
	}

	m_theAlarms.raiseEcsZoneEmergencyNormalisation(zoneId);
	m_theDatapoints.setEmergencyApplied(zoneId, false); 

	FUNCTION_EXIT;
}