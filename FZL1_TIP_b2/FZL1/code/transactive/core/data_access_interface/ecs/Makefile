# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:   $File: //depot/GZL6_TIP/3002/transactive/core/data_access_interface/ecs/Makefile $
# @author:  Ripple
# @version: $Revision: #1 $
#
# Last modification: $DateTime: 2012/06/12 13:35:44 $
# Last modified by:  $Author: builder $


PROJ_ROOT_DIR	= ../../../../..
PROJ_CODE_DIR	= transactive/core/data_access_interface/ecs
PROJ_NAME	= TA_ECSDAI

PROJ_SOURCE	= \
			ConfigECSMasterMode.cpp \
			ConfigECSStationMode.cpp \
			ConfigECSZone.cpp \
			ECSMasterMode.cpp \
			ECSMasterModeAccessFactory.cpp \
			ECSMasterModeHelper.cpp \
			ECSStationMode.cpp \
			ECSStationModeAccessFactory.cpp \
			ECSStationModeHelper.cpp \
			ECSZone.cpp \
			ECSZoneAccessFactory.cpp \
			ECSZoneHelper.cpp \

PROJ_TYPE	= lib
PROJ_INC_DIR	= ./src $(PROJ_ROOT_DIR)/code/transactive $(PROJ_ROOT_DIR)/sdk/include/transactive
PROJ_OUT_DIR	= $(PROJ_ROOT_DIR)/build/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

PROJ_CFLAGS = -DTA_ASSERT_LOG=1
##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak


install:
        #Do Nothing
