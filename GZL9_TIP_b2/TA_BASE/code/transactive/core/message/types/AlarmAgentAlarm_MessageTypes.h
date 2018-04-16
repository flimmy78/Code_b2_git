// File: AlarmAgentAlarm_MessageTypes.h
// Created: 12/04/2006 4:13:29 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef ALARMAGENTALARM_MESSAGETYPES_H
#define ALARMAGENTALARM_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace AlarmAgentAlarm
	{
		// Root context
		static MessageContext Context("Alarm", "AlarmAgentAlarm", AlarmMessage);

		// Message Types for context AlarmAgentAlarm
		static const MessageType AlarmAgentCacheMaxAlarm(Context, "50001");
		static const MessageType AlarmsLoaded(Context, "50002");
		static const MessageType FailedToExecutePlan(Context, "50003");
	};
};

#endif // ALARMAGENTALARM_MESSAGETYPES_H
