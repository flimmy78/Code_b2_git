# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:   $File: //depot/TA_Product_ECSPlan/TA_BASE/transactive/bus/response_plans/PlanDataAccess/Makefile $
# @author:  Ripple
# @version: $Revision: #1 $
#
# Last modification: $DateTime: 2013/07/17 15:33:29 $
# Last modified by:  $Author: CM $
#
PROJ_ROOT_DIR	= ../../../../..
PROJ_CODE_DIR	= transactive/bus/response_plans/common
PROJ_NAME	= TA_PlanCommonBus
PROJ_SOURCE	= RpcAgency.cpp MessageReceiver.cpp MessageSender.cpp PlanInternetional.cpp
PROJ_TYPE	= lib
PROJ_INC_DIR	= ./src $(PROJ_ROOT_DIR)/code/transactive
PROJ_OUT_DIR	= $(PROJ_ROOT_DIR)/sdk/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

# Libraries that this library is dependent upon.
DEPENDENT_LIBRARIES = $(PROJ_ROOT_DIR)/code/transactive/bus/response_plans/plan_agent/IDL

##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
        #Do Nothing
