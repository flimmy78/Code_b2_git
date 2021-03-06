// File: PAAgentAudit_MessageTypes.h
// Created: 12/04/2006 4:13:32 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef PAAGENTAUDIT_MESSAGETYPES_H
#define PAAGENTAUDIT_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace PAAgentAudit
	{
		// Root context
		static MessageContext Context("Audit", "PAAgentAudit", AuditMessage);

		// Message Types for context PAAgentAudit
		static const MessageType PaAgentBroadcastState(Context, "30182");
		static const MessageType PaAgentBroadcastStateFailure(Context, "30183");
		static const MessageType PaAgentDependencyFailure(Context, "30184");
		static const MessageType PaAgentDVAMessageUpdate(Context, "30185");
		static const MessageType PAAgentOnlineUpdate(Context, "30186");
		static const MessageType PaBroadcastEventTriggeredStationDvaForAreaRequest(Context, "30187");
		static const MessageType PaBroadcastEventTriggeredStationDvaForGroupRequest(Context, "30188");
		static const MessageType PaBroadcastEventTriggeredStationDvaForStationRequest(Context, "30189");
		static const MessageType PaBroadcastEventTriggeredStationDvaRequest(Context, "30190");
		static const MessageType PaBroadcastStationDvaRequest(Context, "30191");
		static const MessageType PaBroadcastStationLiveRequest(Context, "30192");
		static const MessageType PaBroadcastStationMusicRequest(Context, "30193");
		static const MessageType PaChangeBroadcastId(Context, "30194");
		static const MessageType PaFEPCNotResponding(Context, "30195");
		static const MessageType PaRecordAdhocRequest(Context, "30196");
		static const MessageType PaRemoveBroadcast(Context, "30197");
		static const MessageType PaRetryStationBroadcastRequest(Context, "30198");
		static const MessageType PaSetAdhocLabel(Context, "30199");
		static const MessageType PaSetAdhocType(Context, "30200");
		static const MessageType PaStationBroadcastResult(Context, "30201");
		static const MessageType PaTerminateBroadcast(Context, "30202");
		static const MessageType PaTrainBroadcastFailure(Context, "30203");
		static const MessageType PaZoneBroadcastFailure(Context, "30204");
		static const MessageType TrainPAContinueLiveAnnouncement(Context, "30205");
		static const MessageType TrainPACyclic(Context, "30206");
		static const MessageType TrainPAEndLiveAnnouncement(Context, "30207");
		static const MessageType TrainPAPrerecorded(Context, "30208");
		static const MessageType TrainPASetupLiveAnnouncement(Context, "30209");
		static const MessageType PaPrioritySchemeUpdate(Context, "30562");
	};
};

#endif // PAAGENTAUDIT_MESSAGETYPES_H
