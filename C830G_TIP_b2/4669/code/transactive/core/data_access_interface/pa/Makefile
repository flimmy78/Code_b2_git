# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:   $File: //depot/4669_T01271350/4669/transactive/core/data_access_interface/pa/Makefile $
# @author:  Ripple
# @version: $Revision: #1 $
#
# Last modification: $DateTime: 2008/11/28 16:26:01 $
# Last modified by:  $Author: builder $

PROJ_ROOT_DIR	= ../../../../..
PROJ_CODE_DIR	= transactive/core/data_access_interface/pa
PROJ_NAME	= TA_PADAI


PROJ_SOURCE	= \
ConfigPaAtsTriggeredBroadcast.cpp \
ConfigPaDvaMessage.cpp \
ConfigPaDvaMessageVersion.cpp \
ConfigPaStation.cpp \
ConfigPaTrainDvaMessage.cpp \
ConfigPaZone.cpp \
ConfigPaZoneGroup.cpp \
DatabaseQueryHelper.cpp \
PaAtsTriggeredBroadcast.cpp \
PaAtsTriggeredBroadcastAccessFactory.cpp \
PaAtsTriggeredBroadcastHelper.cpp \
PaDvaMessage.cpp \
PaDvaMessageAccessFactory.cpp \
PaDvaMessageHelper.cpp \
PaDvaMessageVersion.cpp \
PaDvaMessageVersionAccessFactory.cpp \
PaDvaMessageVersionHelper.cpp \
PaStation.cpp \
PaStationAccessFactory.cpp \
PaStationHelper.cpp \
PaTrainDvaMessage.cpp \
PaTrainDvaMessageAccessFactory.cpp \
PaTrainDvaMessageHelper.cpp \
PaZone.cpp \
PaZoneAccessFactory.cpp \
PaZoneGroup.cpp \
PaZoneGroupAccessFactory.cpp \
PaZoneGroupHelper.cpp \
PaZoneHelper.cpp \

		  
PROJ_TYPE	= lib
PROJ_INC_DIR	= ./src $(PROJ_ROOT_DIR)/code/transactive $(PROJ_ROOT_DIR)/sdk/include/transactive
PROJ_OUT_DIR	= $(PROJ_ROOT_DIR)/build/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

PROJ_LIBS	= TA_DAI

PROJ_CFLAGS = -DTA_ASSERT_LOG=1
##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak


install:
        #Do Nothing
