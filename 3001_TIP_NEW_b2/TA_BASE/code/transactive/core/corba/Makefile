# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:  $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/corba/Makefile $ 
# Author:  Ripple
# Version: $Revision: #2 $
#
# Last modification: $DateTime: 2012/02/06 16:15:14 $
# Last modified by:  $Author: haijun.li $
#
# Make file for the CorbaUtil classes.
#
#
PROJ_ROOT_DIR	= ../../../..
PROJ_CODE_DIR	= transactive/core/corba
PROJ_NAME	= TA_CorbaUtil
PROJ_SOURCE	= CorbaUtil.cpp \
		  ServantBase.cpp \
		  ServantActivator.cpp
PROJ_TYPE	= lib
PROJ_INC_DIR	= ./src $(PROJ_ROOT_DIR)/code/transactive
PROJ_OUT_DIR	= $(PROJ_ROOT_DIR)/sdk/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

DEPENDENT_LIBRARIES = \
		$(PROJ_ROOT_DIR)/code/transactive/core/corba/IDL \
	 	$(PROJ_ROOT_DIR)/code/transactive/core/message/IDL \
	 	$(PROJ_ROOT_DIR)/code/transactive/core/exceptions/IDL \
       		$(PROJ_ROOT_DIR)/code/transactive/core/naming/IDL

# Libraries that this library is dependent upon.
# DEPENDENT_LIBRARIES

##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
	#Do Nothing
