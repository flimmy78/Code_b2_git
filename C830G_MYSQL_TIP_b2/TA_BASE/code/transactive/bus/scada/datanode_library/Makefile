# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/bus/scada/datanode_library/Makefile $
# @author:  Ripple
# @version: $Revision: #2 $
#
# Last modification: $DateTime: 2009/01/08 11:35:48 $
# Last modified by:  $Author: builder $
#
# This file builds the DataNodeCorbaDef_Impl library.
#
#
PROJ_ROOT_DIR	= ../../../../..
PROJ_CODE_DIR	= transactive/bus/scada/datanode_library
PROJ_NAME	= TA_DataNodeLibrary
PROJ_SOURCE	= DataNode.cpp \
		  DataNodeTypes.cpp \
		  SummaryProcessor.cpp

PROJ_TYPE	= lib
PROJ_INC_DIR	= ./src $(PROJ_ROOT_DIR)/code/transactive
PROJ_OUT_DIR	= $(PROJ_ROOT_DIR)/sdk/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

# Libraries that this library is dependent upon.
DEPENDENT_LIBRARIES = \
	$(PROJ_ROOT_DIR)/code/transactive/core/data_access_interface/PlanAgent/IDL \
	$(PROJ_ROOT_DIR)/code/transactive/core/naming/IDL \
	$(PROJ_ROOT_DIR)/code/transactive/core/alarm/IDL \
	$(PROJ_ROOT_DIR)/code/transactive/bus/scada/proxy_library \
	$(PROJ_ROOT_DIR)/code/transactive/bus/scada/datapoint_library \
	$(PROJ_ROOT_DIR)/code/transactive/bus/scada/common_library \
	$(PROJ_ROOT_DIR)/code/transactive/bus/scada/common_library/IDL
	
##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################
include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
	#Do Nothing
