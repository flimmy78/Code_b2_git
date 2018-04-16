// File: PMSAgentAlarms_MessageTypes.h
// Created: 12/04/2006 4:13:33 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef PMSAGENTALARMS_MESSAGETYPES_H
#define PMSAGENTALARMS_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace PMSAgentAlarms
	{
		// Root context
		static MessageContext Context("Alarm", "PMSAgentAlarms", AlarmMessage);

		// Message Types for context PMSAgentAlarms
		static const MessageType RTUCommsError(Context, "50047");
		static const MessageType RTUExternalSystemCommsError(Context, "50048");
	};
};

#endif // PMSAGENTALARMS_MESSAGETYPES_H
