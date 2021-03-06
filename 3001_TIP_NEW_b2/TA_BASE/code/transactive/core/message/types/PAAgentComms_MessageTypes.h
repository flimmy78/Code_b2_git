// File: PAAgentComms_MessageTypes.h
// Created: 12/04/2006 4:13:32 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef PAAGENTCOMMS_MESSAGETYPES_H
#define PAAGENTCOMMS_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace PAAgentComms
	{
		// Root context
		static MessageContext Context("GeneralComms", "PAAgentComms", CommsMessage);

		// Message Types for context PAAgentComms
		static const MessageType AdhocLabelUpdate(Context, "40072");
		static const MessageType AdhocTypeUpdate(Context, "40073");
		static const MessageType BroadcastProgressUpdate(Context, "40074");
		static const MessageType CurrentBroadcastsUpdate(Context, "40075");
		static const MessageType DvaMessagesUpdate(Context, "40076");
		static const MessageType PrioritySchemeUpdate(Context, "40078");
	};
};

#endif // PAAGENTCOMMS_MESSAGETYPES_H
