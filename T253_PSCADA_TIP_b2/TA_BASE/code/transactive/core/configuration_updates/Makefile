# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:  $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/core/configuration_updates/Makefile $ 
# Author:  Ripple
# Version: $Revision: #1 $
#
# Last modification: $DateTime: 2017/10/31 16:21:54 $
# Last modified by:  $Author: CM $
#
# Make file for the ConfigurationUpdates classes.
#

PROJ_ROOT_DIR	= ../../../..
PROJ_CODE_DIR	= transactive/core/configuration_updates
PROJ_NAME	= TA_ConfigurationUpdates
PROJ_SOURCE	= ConfigUpdateDetails.cpp \
		  ConfigMessageSubscriber.cpp \
	      	  OnlineUpdateListener.cpp \
		  EObjectType.cpp \
                  MessageObjectTypeMap.cpp \
		  VersionGen.cpp
PROJ_TYPE	= lib
PROJ_INC_DIR	= ./src $(PROJ_ROOT_DIR)/code/transactive
PROJ_OUT_DIR	= $(PROJ_ROOT_DIR)/sdk/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

DEPENDENT_LIBRARIES = \
	$(PROJ_ROOT_DIR)/code/transactive/core/message/IDL \
	$(PROJ_ROOT_DIR)/code/transactive/core/corba/IDL

##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
	#Do Nothing

