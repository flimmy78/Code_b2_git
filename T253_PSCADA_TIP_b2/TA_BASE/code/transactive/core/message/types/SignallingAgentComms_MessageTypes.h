// File: SignallingAgentComms_MessageTypes.h
// Created: 12/04/2006 4:13:33 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef SIGNALLINGAGENTCOMMS_MESSAGETYPES_H
#define SIGNALLINGAGENTCOMMS_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace SignallingAgentComms
	{
		// Root context
		static MessageContext Context("GeneralComms", "SignallingAgentComms", CommsMessage);

		// Message Types for context SignallingAgentComms
		static const MessageType SignallingPasMessage(Context, "40122");
		static const MessageType TrainSignallingUpdate(Context, "40123");
		static const MessageType SignallingPidsMessage(Context, "40197");
	};
};

#endif // SIGNALLINGAGENTCOMMS_MESSAGETYPES_H
