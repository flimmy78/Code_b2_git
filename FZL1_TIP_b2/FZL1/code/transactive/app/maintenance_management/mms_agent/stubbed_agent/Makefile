# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:   $File: //depot/GZL6_TIP/3002/transactive/app/maintenance_management/mms_agent/stubbed_agent/Makefile $
# @author:  Ripple
# @version: $Revision: #1 $
#
# Last modification: $DateTime: 2012/06/12 13:35:44 $
# Last modified by:  $Author: builder $

MMSAPI_STUB	= 1
PROJ_ROOT_DIR	= ../../../../../..
PROJ_SRC_DIR	= ../src
PROJ_CODE_DIR	= transactive/app/maintenance_management/mms_agent
PROJ_NAME	= MmsAgent_Stubbed
PROJ_SOURCE	=	main.cpp \
		MmsAgent.cpp \
		MmsConnection.cpp \
		VersionGen.cpp \
		MmsConnectionTester.cpp \
		DatabaseCache.cpp \
		MmsAlarmSubmitter.cpp \
		MmsJobRequestSubmitter.cpp \
		MmsMessageUtil.cpp \
		MmsStubbedApiWrapper.cpp \
		MmsPeriodicSubmitter.cpp \
		MmsServerState.cpp \
		PeriodicThread.cpp


PROJ_TYPE	= exe
PROJ_INC_DIR	= ../src  $(PROJ_ROOT_DIR)/code/transactive \
                         $(PROJ_ROOT_DIR)/sdk/include/transactive \
			 $(PROJ_ROOT_DIR)/code

PROJ_CFLAGS	= -DUNIX -DMMSAPI_STUB

PROJ_LIBS     = \
		TA_CorbaUtil \
		TA_AuthenticationCorbaDef \
		TA_DataNodeAgentCorbaDef_Impl \
		TA_DataPointAgentCorbaDef_Impl \
		TA_ScadaCommonLib \
		TA_ScadaProxyLibrary \
		TA_DataNodeLibrary \
		TA_DataPointLibrary \
		TA_ScadaProxyLibrary \
		TA_DataNodeLibrary \
		TA_ScadaCommonLib \
		TA_ScadaCommonCorbaDef \
		TA_PlanDAI \
		TA_AlarmRuleDAI \
		TA_RightsLibrary \
		TA_RightsAgentCorbaDef \
		TA_SecurityUtilities \
		TA_AuthenticationLibrary \
		TA_AuthenticationCorbaDef \
		TA_DutyAgentCorbaDef \
		TA_DerivedDataPointDAI \
		TA_DataRecording \
		TA_DataRecordingDAI \
		TA_Timers \
		TA_Thread \
		TA_Naming \
		TA_GenericAgent \
		TA_DAI \
		TA_EventTriggeredPlans \
		TA_PlanAgentLibrary \
		TA_PlanAgentCorbaDef \
		TA_PlanDAI \
		TA_PlanAgentDataCorbaDef \
		TA_PlanManagerCorbaDef \
		TA_Message \
                TA_EventProcessing \
		TA_Uuid \
		TA_ManagedProcess \
		TA_Alarm \
		TA_AlarmAgentCorbaDef \
                TA_EntityStatusUpdateCorbaDef \
		TA_EntityAccess \
                TA_DAI \
                TA_AlarmRuleDAI \
		TA_DataAccess\
		TA_CorbaDef \
		TA_NamingCorbaDef \
		TA_MessageCorbaDef \
		TA_ProcessManagementCorbaDef \
		TA_DataAccess \
		TA_ConfigurationUpdates \
		TA_Utilities \
		TA_MmsDai \
		TA_DAI \
		TA_Exceptions \
		TA_CommonExceptionsCorbaDef \
		TA_Version \
		TA_MathEvaluation \
		TA_Sockets \
		TA_Synchronisation \
		TA_MmsCorbaDef \
		MMSAPI \
		trace \
                dmqcl \
		TA_ocl \
		clntsh \
                ACE

PROJ_OUT_DIR =  $(PROJ_ROOT_DIR)/bin/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

DEPENDENT_LIBRARIES = \
                $(PROJ_ROOT_DIR)/code/transactive/core/data_access_interface/mms_dai 

##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
        #Do Nothing
