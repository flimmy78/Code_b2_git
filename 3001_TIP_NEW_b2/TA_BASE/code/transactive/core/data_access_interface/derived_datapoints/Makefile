# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:  $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/derived_datapoints/Makefile $ 
# Author:  Ripple
# Version: $Revision: #2 $
#
# Last modification: $DateTime: 2012/02/06 16:15:14 $
# Last modified by:  $Author: haijun.li $
#

PROJ_ROOT_DIR	= ../../../../..
PROJ_CODE_DIR	= transactive/core/data_access_interface/derived_datapoints
PROJ_NAME	= TA_DerivedDataPointDAI
PROJ_SOURCE	= ConfigConfiguredDerivedState.cpp \
		  ConfigConfiguredInputAssociation.cpp \
		  ConfigDerivedOutputAssociation.cpp \
		  DerivedDataPointEntityData.cpp \
		  DerivedDataPointHelper.cpp \
		  ConfigDerivedDataPoint.cpp \
		  DerivedDataPointAccessFactory.cpp \
		  DerivedDataPointConfigCache.cpp
PROJ_TYPE	= lib
PROJ_INC_DIR	= ./src $(PROJ_ROOT_DIR)/code/transactive
PROJ_OUT_DIR	= $(PROJ_ROOT_DIR)/sdk/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

PROJ_CFLAGS = -DTA_ASSERT_LOG=1
##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
        #Do Nothing
