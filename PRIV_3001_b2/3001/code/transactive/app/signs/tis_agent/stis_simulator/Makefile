# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:   $File: //depot/PRIV_3001/3001/transactive/app/signs/tis_agent/stis_simulator/Makefile $
# @author:  Ripple
# @version: $Revision: #1 $
#
# Last modification: $DateTime: 2018/03/14 13:51:20 $
# Last modified by:  $Author: lim.cy $
#
# STIS Simulator Makefile.
#

PROJ_ROOT_DIR 	= ../../../../../..
PROJ_CODE_DIR	= transactive/app/signs/tis_agent/stis_simulator
PROJ_NAME     	= STISSimulator

PROJ_SOURCE   	= main.cpp \
				STISCommandMonitor.cpp \
				STISCommsObserver.cpp \
				STISMessageProcessor.cpp \
				STISSimulator.cpp \
				STISSimulatorCommandProcessor.cpp \
				VersionGen.cpp \

PROJ_TYPE     	= exe
PROJ_INC_DIR   	= ./src $(PROJ_ROOT_DIR)/code/transactive $(PROJ_ROOT_DIR)/sdk/include/transactive
PROJ_IDL_INC  	= $(PROJ_ROOT_DIR)/build/transactive
PROJ_OUT_DIR	= $(PROJ_ROOT_DIR)/bin/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

PROJ_LIBDIRS	= $(PROJ_ROOT_DIR)/build/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG) \
			$(PROJ_ROOT_DIR)/sdk/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

PROJ_LIBS	 	= TA_GenericSimulator \
			TA_Utilities \
			TA_Version \
		    	TA_Thread \
		    	TA_Sockets \
		    	TA_Synchronisation \
		    	TA_Exceptions \
		    	TA_Utilities \
			clntsh \
			ACE
 

##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
	#Do Nothing
