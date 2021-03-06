/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/4677_TIP/4677/transactive/app/radio/radio_manager_gui/src/RadioStatusPage/ResourceButton/PatchGroupRadioResourceButtonStrategy.h $
 * @author:  zou chunzhong
 * @version: $Revision: #2 $
 *
 * Last modification: $DateTime: 2009/12/15 19:31:45 $
 * Last modified by:  $Author: grace.koh $
 * 
 */

#ifndef PATCH_GROUP_RADIO_RESOURCE_BUTTON_STRATEGY_H_INCLUDED
#define PATCH_GROUP_RADIO_RESOURCE_BUTTON_STRATEGY_H_INCLUDED

#include "app/radio/radio_manager_gui/src/RadioStatusPage/ResourceButton/RadioResourceButtonStrategy.h"

class PatchGroupRadioResourceButtonStrategy : public RadioResourceButtonStrategy
{

public:
	PatchGroupRadioResourceButtonStrategy();

	virtual ~PatchGroupRadioResourceButtonStrategy();

	virtual int assignmentBehaviour(bool pOnInit);

	virtual bool removeAssignedResource();	

	virtual void selectionBehaviour();

	virtual void unselectionBehaviour();

	virtual void cancelCurrentOperation(ApiState state);

};
#endif