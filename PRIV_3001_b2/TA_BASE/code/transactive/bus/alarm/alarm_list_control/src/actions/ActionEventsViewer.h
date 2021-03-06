/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/bus/alarm/alarm_list_control/src/actions/ActionEventsViewer.h $
 * @author:  Derrick Liew
 * @version: $Revision: #1 $
 *
 * Last modification: $DateTime: 2018/03/14 13:51:20 $
 * Last modified by:  $Author: lim.cy $
 * 
 * This class is for the action that launches the Event Viewer displaying all events
 */

// ActionEventsViewer.h: interface for the ActionEventsViewer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACTIONEVENTSVIEWER_H__C4DA5EE9_3A1B_4E90_B449_95F357D4F660__INCLUDED_)
#define AFX_ACTIONEVENTSVIEWER_H__C4DA5EE9_3A1B_4E90_B449_95F357D4F660__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <string>

#include "bus/alarm/alarm_list_control/src/IAlarmAction.h"


namespace TA_Base_Bus
{

	class ActionEventsViewer : public virtual IAlarmAction  
	{

    public:

        /**
         * Constructor
         *
         * @param bool - This indicates if this action should be available in the alarm list context
         *               menu. This will default to true and the action will be added to the menu.
         */
        ActionEventsViewer(bool isAvailableInContextMenu = true);


        /**
         * Destructor
         */
        virtual ~ActionEventsViewer();


        /**
         * isAvailableInContextMenu
         *
         * This should indicate whether this action is available in the alarm list context menu
         *
         * @return bool - true if this action should be in the context menu. False otherwise
         */
        virtual bool isAvailableInContextMenu() const
        {
            return m_isAvailableInContextMenu;
        }


        /**
         * getMenuEntry
         *
         * This will determine the entry that should appear in any menus that display this action
         *
         * @return string - The menu entry including & for the shortcut letter
         */
        virtual std::string getMenuEntry() const
        {
            return "Events Vie&wer...";
        };


        /**
         * getActionControlId
         *
         * This should return the id to use for the menu item. This id will be used to determine what
         * item the user has selected from the context menu.
         *
         * @return unsigned int - A control id. This should not be the same as any other control id and must be within
         *                        the range 4000 - 4999.
         */
        virtual unsigned int getActionControlId() const
        {
            return EVENTS_VIEWER;
        };


        /**
         * isAvailable
         *
         * This is called when the application/list needs to determine if an action is available at
         * the current time. This is based on the user's access rights as well as which alarms are
         * currently selected.
         *
         * @param IAlarmRetriever& - The object to use to find details and perform actions.
         *
         * @return bool - true if the action is available to the user, false if it is not.
         */
        virtual bool isAvailable(IAlarmRetriever& alarmRetriever);


        /** 
         * performAction
         *
         * This is called when this action needs to be performed. This should only be called once checking
         * that the action isAvailable().
         *
         * @param IAlarmRetriever& - The object to use to find details and perform actions.
         *
         * @exception AlarmActionException - This should be thrown if any error is encountered. The message
         *                                   in the exception should be set to a suitable error message that
         *                                   can be displayed directly to the user.
         */
        virtual void performAction(IAlarmRetriever& alarmRetriever);


    private:
        // Hidden as not required
        ActionEventsViewer(ActionEventsViewer&);
        ActionEventsViewer& operator=(const ActionEventsViewer&);

        bool m_isAvailableInContextMenu;

	};

} // namespace end

#endif // !defined(AFX_ACTIONEVENTSVIEWER_H__C4DA5EE9_3A1B_4E90_B449_95F357D4F660__INCLUDED_)
