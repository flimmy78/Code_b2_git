// File: DutyAgentComms_MessageTypes.h
// Created: 12/04/2006 4:13:31 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef DUTYAGENTCOMMS_MESSAGETYPES_H
#define DUTYAGENTCOMMS_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace DutyAgentComms
	{
		// Root context
		static MessageContext Context("GeneralComms", "DutyAgentComms", CommsMessage);

		// Message Types for context DutyAgentComms
		static const MessageType RightsLibraryCacheUpdate(Context, "40040");
	};
};

#endif // DUTYAGENTCOMMS_MESSAGETYPES_H
