# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/bus/scada/common_library/IDL/Makefile $
# @author:  Ripple
# @version: $Revision: #1 $
#
# Last modification: $DateTime: 2018/03/14 13:51:20 $
# Last modified by:  $Author: lim.cy $

PROJ_ROOT_DIR	= ../../../../../..
PROJ_CODE_DIR	= transactive/bus/scada/common_library/IDL
PROJ_NAME	= TA_ScadaCommonCorbaDef
PROJ_IDL	=  ScadaCorbaTypes.idl \
                  DataPointCorbaTypes.idl \
                  DataNodeCorbaTypes.idl \
		  IDataNodeAccessCorbaDef.idl \
		  IDataNodeAgentCorbaDef.idl \
		  IDataPointStateUpdateCorbaDef.idl \
		  IDataPointAccessCorbaDef.idl \
		  IDataPointAgentCorbaDef.idl

PROJ_IDL_INC	= $(PROJ_ROOT_DIR)/code/transactive
PROJ_TYPE	= lib
PROJ_INC_DIR	= ./src $(PROJ_ROOT_DIR)/code/transactive
PROJ_OUT_DIR	= $(PROJ_ROOT_DIR)/sdk/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

# Libraries that this library is dependent upon.
DEPENDENT_LIBRARIES = $(PROJ_ROOT_DIR)/code/transactive/core/exceptions/IDL

##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
	#Do Nothing
