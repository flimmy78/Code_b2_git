# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:   $File: //depot/3001_TIP_NEW/3001/transactive/bus/maintenance_management/mms_api/Makefile $
# @author:  Ripple
# @version: $Revision: #2 $
#
# Last modification: $DateTime: 2012/02/06 16:15:14 $
# Last modified by:  $Author: haijun.li $

PROJ_ROOT_DIR	= ../../../../..
PROJ_CODE_DIR	= transactive/bus/maintenance_management/mms_api
PROJ_NAME	= MmsAgentApi
PROJ_SOURCE	=	MmsApi.cpp
			


PROJ_TYPE	= lib
PROJ_INC_DIR	= ./src  $(PROJ_ROOT_DIR)/code/transactive \
                         $(PROJ_ROOT_DIR)/sdk/include/transactive \
			 $(PROJ_ROOT_DIR)/code \
			 $(PROJ_ROOT_DIR)/code/cots/BEAMessageQ/include

PROJ_CFLAGS	= -DUNIX

PROJ_LIBS     = \
	TA_Sockets \
		trace \
                dmqcl

PROJ_OUT_DIR =  $(PROJ_ROOT_DIR)/build/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)


##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
        #Do Nothing
