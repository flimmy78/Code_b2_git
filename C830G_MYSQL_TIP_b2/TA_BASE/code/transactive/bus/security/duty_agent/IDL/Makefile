# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/bus/security/duty_agent/IDL/Makefile $
# @author:  Ripple
# @version: $Revision: #1 $
#
# Last modification: $DateTime: 2008/11/28 16:26:01 $
# Last modified by:  $Author: builder $

PROJ_ROOT_DIR	= ../../../../../..
PROJ_CODE_DIR	= transactive/bus/security/duty_agent/IDL
PROJ_NAME	= TA_DutyAgentCorbaDef
PROJ_IDL	= \
		  IDutyAgentRespCorbaDef.idl \
		  DutyAgentTypeCorbaDef.idl \
		  IDutyAgentAuthCorbaDef.idl \
		  IDutyAgentAutoDegradeCorbaDef.idl \
		  IDutyAgentMgrCorbaDef.idl \
		  IDutyAgentPeerCorbaDef.idl \
		  IDutyAgentQueryCorbaDef.idl \
		  IDutyAgentCorbaDef.idl
PROJ_IDL_INC	= $(PROJ_ROOT_DIR)/code/transactive
PROJ_TYPE	= lib
PROJ_INC_DIR	= ./src $(PROJ_ROOT_DIR)/code/transactive
PROJ_OUT_DIR	= $(PROJ_ROOT_DIR)/sdk/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)
             
DEPENDENT_LIBRARIES = $(PROJ_ROOT_DIR)/code/transactive/core/exceptions/IDL \
			$(PROJ_ROOT_DIR)/code/transactive/bus/security/authentication_agent/IDL

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
	#Do Nothing
