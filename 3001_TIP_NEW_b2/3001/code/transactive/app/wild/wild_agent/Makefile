# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/wild/wild_agent/Makefile $
# @author:  Ripple
# @version: $Revision: #4 $
#
# Last modification: $DateTime: 2014/07/14 20:22:57 $
# Last modified by:  $Author: Noel $

PROJ_ROOT_DIR	= ../../../../..
PROJ_CODE_DIR	= transactive/app/wild/wild_agent
PROJ_NAME	= WILDAgent

PROJ_SOURCE	= ATSTrainTableSubscriber.cpp \
		  main.cpp \
		  DataCorrelation.cpp \
	          DataPointCache.cpp \
		  SingletonTrainDataMap.cpp \
		  WildAgent.cpp \
		  WILDConfiguration.cpp \
		  VersionGen.cpp \

PROJ_TYPE	= exe
PROJ_INC_DIR    = ./src $(PROJ_ROOT_DIR)/code/transactive $(PROJ_ROOT_DIR)/sdk/include/transactive
PROJ_OUT_DIR    = $(PROJ_ROOT_DIR)/bin/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

PROJ_LIBS     = \
		TA_AtsAgentCorbaDef \
		TA_AlarmRuleDAI \
		TA_GenericAgent \
		TA_Bus_Event \
		TA_EventTriggeredPlans \
		TA_PlanAgentLibrary \
		TA_PlanAgentCorbaDef \
		TA_PlanDAI \
		TA_PlanAgentDataCorbaDef \
		TA_PlanManagerCorbaDef \
		TA_CorbaUtil \
		TA_AuthenticationLibrary \
		TA_AuthenticationCorbaDef \
                TA_DataPointAgentCorbaDef_Impl \
                TA_DataNodeAgentCorbaDef_Impl \
		TA_ScadaCommonLib \
		TA_ScadaProxyLibrary \
		TA_DataNodeLibrary \
		TA_DataPointLibrary \
		TA_ScadaProxyLibrary \
		TA_DataNodeLibrary \
		TA_ScadaCommonLib \
		TA_ScadaCommonCorbaDef \
		TA_DataRecording \
		TA_DataRecordingDAI \
		TA_MmsCorbaDef \
		TA_DerivedDataPointDAI \
		TA_MathEvaluation \
		TA_Alarm \
		TA_RightsLibrary \
		TA_AuthenticationLibrary \
		TA_SecurityUtilities \
		TA_AuthenticationCorbaDef \
		TA_RightsAgentCorbaDef \
		TA_DutyAgentCorbaDef \
		TA_Timers \
		TA_Thread \
		TA_Naming \
		TA_AlarmAgentCorbaDef \
                TA_EntityStatusUpdateCorbaDef \
		TA_Uuid \
		TA_Message \
                TA_EventProcessing \
				TA_Event \
				TA_EventAgentCorbaDef \
		TA_EntityAccess \
		TA_DAI \
                TA_AlarmRuleDAI \
		TA_CorbaDef \
		TA_NamingCorbaDef \
		TA_MessageCorbaDef \
		TA_ManagedProcess \
		TA_ProcessManagementCorbaDef \
		TA_DataAccess \
		TA_ConfigurationUpdates \
		TA_Utilities \
		TA_Exceptions \
		TA_Version \
		TA_CommonExceptionsCorbaDef \
		TA_Synchronisation \
		TA_ocl \
		TA_mcl \
		ACE \
		clntsh \
		mysqlclient 
             
DEPENDENT_LIBRARIES = $(PROJ_ROOT_DIR)/code/transactive/bus/ats/ats_agent/IDL

PROJ_CFLAGS = -DTA_ASSERT_LOG=1
##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
        #Do Nothing
