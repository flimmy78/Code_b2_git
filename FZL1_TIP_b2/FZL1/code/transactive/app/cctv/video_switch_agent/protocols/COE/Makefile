# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:   $File: //depot/WXL1_TIP/3002/transactive/app/cctv/video_switch_agent/protocols/COE/Makefile $
# @author:  Ripple
# @version: $Revision: #4 $
#
# Last modification: $DateTime: 2013/07/30 17:42:30 $
# Last modified by:  $Author: huang.wenbo $
#
# This file builds the TA_COESwitchAgent library.
#

PROJ_ROOT_DIR 		= ../../../../../../..
PROJ_CODE_DIR		= transactive/app/cctv/video_switch_agent/protocols/COE
PROJ_NAME 			= TA_COESwitchAgent

PROJ_SOURCE 		= COECamera.cpp \
	        	    COECommunicationsHandler.cpp \
              		COECommunicationsChannel.cpp \
              		COEHelper.cpp \
              		ReceivedDataProcessor.cpp \
              		AbstractCOERequestCommand.cpp \
              		COEInterfaceFactory.cpp \
              		COESwitchManager.cpp \
              		COEVideoInput.cpp \
              		COEVideoOutput.cpp \
              		COESequence.cpp \
					CommandCreateHelper.cpp \
					PlaybackCtrlCommand.cpp \
					PtzCtrlCommand.cpp \
					RecordingPlaybackCommand.cpp \
	        	    SwitchQuadInputsCommand.cpp \
	        	    SwitchInputToOutputCommand.cpp \
              		SummaryPollingCommand.cpp \
              		SetSequenceConfigCommand.cpp \
			        AddressHelper.cpp

PROJ_TYPE   		= lib
PROJ_INC_DIR 		= ./src $(PROJ_ROOT_DIR)/build/$(OPERATING_SYSTEM)_$(STRING_FLAG)/transactive \
				$(PROJ_ROOT_DIR)/code/transactive \
				$(PROJ_ROOT_DIR)/sdk/include/transactive
				
PROJ_OUT_DIR		= $(PROJ_ROOT_DIR)/build/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)

PROJ_LIBS			= TA_TrainAgentCorbaDef TA_VideoSwitchAgentCorbaDef

PROJ_LIBDIRS		= $(PROJ_ROOT_DIR)/build/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG) \
				$(PROJ_ROOT_DIR)/sdk/$(OPERATING_SYSTEM)_$(STRING_FLAG)$(RELEASE_FLAG)
			
	
##############################################################
# The main include file that has all the wiz bang stuff for neato compiling
##############################################################

include $(PROJ_ROOT_DIR)/code/tools/build/CommonMakefile.mak

install:
	#Do Nothing
