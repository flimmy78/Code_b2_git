// File: ECSAgentStateUpdateRequest_MessageTypes.h
// Created: 12/04/2006 4:13:31 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef ECSAGENTSTATEUPDATEREQUEST_MESSAGETYPES_H
#define ECSAGENTSTATEUPDATEREQUEST_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace ECSAgentStateUpdateRequest
	{
		// Root context
		static MessageContext Context("StateUpdate", "ECSAgentStateUpdateRequest", StateUpdateMessage);

		// Message Types for context ECSAgentStateUpdateRequest
		static const MessageType EcsAgentStateUpdateRequest(Context, "10022");
	};
};

#endif // ECSAGENTSTATEUPDATEREQUEST_MESSAGETYPES_H
