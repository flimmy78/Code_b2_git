// File: OsssAgentStateUpdateRequest_MessageTypes.h
// Created: 12/04/2006 4:13:32 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef OSSSAGENTSTATEUPDATEREQUEST_MESSAGETYPES_H
#define OSSSAGENTSTATEUPDATEREQUEST_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace OsssAgentStateUpdateRequest
	{
		// Root context
		static MessageContext Context("StateUpdate", "OsssAgentStateUpdateRequest", StateUpdateMessage);

		// Message Types for context OsssAgentStateUpdateRequest
		static const MessageType OsssAgentStateUpdateRequest(Context, "10038");
	};
};

#endif // OSSSAGENTSTATEUPDATEREQUEST_MESSAGETYPES_H
