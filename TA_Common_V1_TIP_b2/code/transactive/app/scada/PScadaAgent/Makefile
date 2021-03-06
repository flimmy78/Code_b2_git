#The source code in this file is the property of
#Ripple Systems and is not for redistribution in any form.
#Source:    $Source: /cvs/1TS-9999-T/code/transactive/app/scada/PScadaAgent/Attic/Makefile,v $
#@author:   Liu Yong
#@version:  $Revision$
#Last modification: $Date$
#Last modified by:  $Author$

PROJ_ROOT_DIR   = ../../../../..
PROJ_CODE_DIR   = transactive/app/scada/PScadaAgent
PROJ_NAME       = PScadaAgent

PROJ_SOURCE     = PScadaAgentMain.cpp \
		  PScadaAgent.cpp \
		  PScadaUnit.cpp \
		  PScadaOutputWorker.cpp \
		  PScadaPollingWorker.cpp \
		  PScadaManager.cpp \
		  PScadaEventHandler.cpp \
		  PScadaMsgTimer.cpp \
		  PScadaDpProcessor.cpp \
		  PScadaCommandPolicy.cpp \
		  VersionGen.cpp

PROJ_TYPE       = exe
PROJ_INC_DIR    = ./src $(PROJ_ROOT_DIR)/code/transactive
PROJ_OUT_DIR    = $(PROJ_ROOT_DIR)/bin/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

PROJ_LIBS     = \
                TA_ScadaAgent \
				TA_CorbaUtil \
				TA_DataPointAgentCorbaDef_Impl \
				TA_DataNodeAgentCorbaDef_Impl \
				TA_AlarmRuleDAI \
				TA_PlanDAI \
				TA_ScadaAgent \
				TA_CorbaUtil \
				TA_GenericAgent \
				TA_Bus_Event \
				TA_EventTriggeredPlans \
				TA_PlanAgentLibrary \
				TA_PlanAgentCorbaDef \
				TA_PlanDAI \
				TA_PlanAgentDataCorbaDef \
				TA_PlanManagerCorbaDef \
				TA_ScadaProxyLibrary \
				TA_ScadaBusinessLibrary \
				TA_ModbusHelperLib \
				TA_DataNodeLibrary \
				TA_DataPointLibrary \
				TA_DerivedDataPointDAI \
				TA_ScadaCommonLib \
				TA_ScadaCommonCorbaDef \
				TA_DataRecording \
				TA_DataRecordingDAI \
				TA_MmsCorbaDef \
				TA_WFGlobalInhibitLib \
				TA_WFGlobalInhibitCorbaDef \
				TA_104Library \
				TA_SOEProcessLibrary \
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
				TA_DAI_SOE \
				TA_AlarmRuleDAI \
				TA_CorbaDef \
				TA_NamingCorbaDef \
				TA_MessageCorbaDef \
				TA_ManagedProcess \
				TA_ProcessManagementCorbaDef \
				TA_DataAccess \
				TA_ConfigurationUpdates \
				TA_Utilities \
				TA_Version \
				TA_ModbusComms \
				TA_FTP \
				TA_Sockets \
				TA_Exceptions \
				TA_CommonExceptionsCorbaDef \
				TA_MathEvaluation \
				TA_Synchronisation \
            	TA_CorbaUtil \
				TA_ocl \
				TA_mcl \
				ACE \
				clntsh \
				mysqlclient

DEPENDENT_LIBRARIES =	$(PROJ_ROOT_DIR)/code/transactive/core/exceptions \
			$(PROJ_ROOT_DIR)/code/transactive/core/versioning \
			$(PROJ_ROOT_DIR)/code/transactive/core/synchronisation \
			$(PROJ_ROOT_DIR)/code/transactive/core/threads \
			$(PROJ_ROOT_DIR)/code/transactive/core/utilities \
			$(PROJ_ROOT_DIR)/code/transactive/core/corba/IDL \
			$(PROJ_ROOT_DIR)/code/transactive/core/corba \
			$(PROJ_ROOT_DIR)/code/transactive/core/naming \
			$(PROJ_ROOT_DIR)/code/transactive/core/naming/IDL \
			$(PROJ_ROOT_DIR)/code/transactive/core/message \
			$(PROJ_ROOT_DIR)/code/transactive/core/database \
			$(PROJ_ROOT_DIR)/code/transactive/core/data_access_interface \
			$(PROJ_ROOT_DIR)/code/transactive/core/data_access_interface/derived_datapoints \
			$(PROJ_ROOT_DIR)/code/transactive/core/process_management \
			$(PROJ_ROOT_DIR)/code/transactive/core/process_management/IDL \
			$(PROJ_ROOT_DIR)/code/transactive/core/configuration_updates \
			$(PROJ_ROOT_DIR)/code/transactive/bus/generic_agent \
            $(PROJ_ROOT_DIR)/code/transactive/bus/scada/scada_agent \
			$(PROJ_ROOT_DIR)/code/transactive/bus/scada/DataNodeAgentCorbaDef_Impl \
			$(PROJ_ROOT_DIR)/code/transactive/bus/scada/DataPointAgentCorbaDef_Impl \
			$(PROJ_ROOT_DIR)/code/transactive/bus/scada/common_library \
			$(PROJ_ROOT_DIR)/code/transactive/bus/scada/datanode_library \
			$(PROJ_ROOT_DIR)/code/transactive/bus/scada/datapoint_library \
			$(PROJ_ROOT_DIR)/code/transactive/bus/scada/proxy_library \
			$(PROJ_ROOT_DIR)/code/transactive/bus/scada/104_library \
			$(PROJ_ROOT_DIR)/code/transactive/bus/security/rights_agent/IDL \
			$(PROJ_ROOT_DIR)/code/transactive/bus/security/rights_library \
			$(PROJ_ROOT_DIR)/code/transactive/bus/security/security_utilities \
			$(PROJ_ROOT_DIR)/code/transactive/bus/security/authentication_agent/IDL \
			$(PROJ_ROOT_DIR)/code/transactive/bus/history/data_recording \
			$(PROJ_ROOT_DIR)/code/transactive/bus/soe/soe_process_library \
			$(PROJ_ROOT_DIR)/code/transactive/bus/event \
			$(PROJ_ROOT_DIR)/code/transactive/bus/response_plans/plan_agent \
			$(PROJ_ROOT_DIR)/code/transactive/bus/modbus_comms \
			$(PROJ_ROOT_DIR)/code/transactive/bus/mathematical_evaluation \
			$(PROJ_ROOT_DIR)/code/transactive/bus/scada/business_library \
			$(PROJ_ROOT_DIR)/code/transactive/bus/scada/ModbusHelper \
			$(PROJ_ROOT_DIR)/code/transactive/core/ocl \
			$(PROJ_ROOT_DIR)/code/transactive/core/sockets \
			$(PROJ_ROOT_DIR)/code/transactive/core/ftp \
			$(PROJ_ROOT_DIR)/code/transactive/core/event \
			$(PROJ_ROOT_DIR)/code/transactive/core/uuid \
			$(PROJ_ROOT_DIR)/code/transactive/core/data_access_interface/data_recording_dai \
			$(PROJ_ROOT_DIR)/code/transactive/core/data_access_interface/plans \
      $(PROJ_ROOT_DIR)/code/transactive/core/data_access_interface/entity_access \
      $(PROJ_ROOT_DIR)/code/transactive/core/data_access_interface/entity_access/IDL \
      $(PROJ_ROOT_DIR)/code/transactive/core/data_access_interface/alarm_rule \
      $(PROJ_ROOT_DIR)/code/transactive/core/timers \
	  $(PROJ_ROOT_DIR)/code/transactive/bus/scada/scada_agent \
	  $(PROJ_ROOT_DIR)/code/transactive/bus/scada/wf_global_inhibit/IDL \
	  $(PROJ_ROOT_DIR)/code/transactive/bus/scada/wf_global_inhibit

PROJ_CFLAGS = -DTA_ASSERT_LOG=1

##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
        #Do Nothing
