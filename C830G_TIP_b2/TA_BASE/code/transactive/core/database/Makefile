# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:  $File: //depot/4669_T01271350/TA_BASE/transactive/core/database/Makefile $ 
# Author:  Ripple
# Version: $Revision: #2 $
#
# Last modification: $DateTime: 2011/03/29 13:47:32 $
# Last modified by:  $Author: builder $
#
# Make file for the DataAccessLib classes.
#
#
PROJ_ROOT_DIR	= ../../../..
PROJ_CODE_DIR	= transactive/core/database
PROJ_NAME	= TA_DataAccess
PROJ_SOURCE	= DBException.cpp \
                  ConnectionReaper.cpp \
                  OCIConnection.cpp \
                  OCIAccess.cpp \
                  SimpleDb.cpp \
                  QueryAdapter.cpp \
                  OCIAccessStatusMonitor.cpp \
                  OCIConnectionStatusMonitor.cpp \
                  SimpleDbStatusMonitor.cpp

PROJ_TYPE	= lib
PROJ_INC_DIR	= ./src $(PROJ_ROOT_DIR)/code/transactive
PROJ_OUT_DIR	= $(PROJ_ROOT_DIR)/sdk/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
        #Do Nothing
