# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/bus/security/rights_agent/policy_decision_point/Makefile $
# @author:  Ripple
# @version: $Revision: #1 $
#
# Last modification: $DateTime: 2018/03/14 13:51:20 $
# Last modified by:  $Author: lim.cy $
#
# Make file for the Right Agent Policy decision point classes.
#
PROJ_ROOT_DIR	= ../../../../../..
PROJ_CODE_DIR	= transactive/bus/security/rights_agent/policy_decision_point
PROJ_NAME	= TA_PolicyDecisionPoint
PROJ_SOURCE	= ActionAttributeSelector.cpp \
		  AttributeSet.cpp \
		  CompareFunction.cpp \
		  Condition.cpp \
		  ConstAttributeSelector.cpp \
		  Context.cpp \
		  Function.cpp \
		  Policy.cpp \
		  PolicyCombiningAlg.cpp \
		  PolicySet.cpp \
		  ResourceAttributeSelector.cpp \
		  Rule.cpp \
		  RuleCombiningAlg.cpp \
		  SubjectAttributeSelector.cpp \
		  Target.cpp \
		  UnmatchedTarget.cpp \
		  ValueSet.cpp
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
