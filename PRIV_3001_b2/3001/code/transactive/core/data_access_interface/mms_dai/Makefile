# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:   $File: //depot/PRIV_3001/3001/transactive/core/data_access_interface/mms_dai/Makefile $
# @author:  Ripple
# @version: $Revision: #1 $
#
# Last modification: $DateTime: 2018/03/14 13:51:20 $
# Last modified by:  $Author: lim.cy $


PROJ_ROOT_DIR	= ../../../../..
PROJ_CODE_DIR	= transactive/core/data_access_interface/mms_dai
PROJ_NAME	= TA_MmsDai

PROJ_SOURCE	= MmSchedulingData.cpp \
		  MmSchedulingHelper.cpp \
		  MmSchedulingAccessFactory.cpp \
	 	  ConfigMmScheduling.cpp
		  
PROJ_TYPE	= lib
PROJ_INC_DIR    = ./src $(PROJ_ROOT_DIR)/code/transactive $(PROJ_ROOT_DIR)/sdk/include/transactive
PROJ_OUT_DIR    = $(PROJ_ROOT_DIR)/build/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

PROJ_CFLAGS = -DTA_ASSERT_LOG=1
##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak


install:
        #Do Nothing
