// File: ECSAgentAlarms_MessageTypes.h
// Created: 12/04/2006 4:13:31 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef ECSAGENTALARMS_MESSAGETYPES_H
#define ECSAGENTALARMS_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace ECSAgentAlarms
	{
		// Root context
		static MessageContext Context("Alarm", "ECSAgentAlarms", AlarmMessage);

		// Message Types for context ECSAgentAlarms
		static const MessageType EcsInterAgentCommsFailure(Context, "50022");
		static const MessageType EcsInvalidConfiguration(Context, "50023");
		static const MessageType EcsZoneEmergencyNormalisation(Context, "50024");
		static const MessageType EcsZoneOnFireAlarm(Context, "50499");
		static const MessageType EcsZoneCongestedAlarm(Context, "50500");
	};
};

#endif // ECSAGENTALARMS_MESSAGETYPES_H