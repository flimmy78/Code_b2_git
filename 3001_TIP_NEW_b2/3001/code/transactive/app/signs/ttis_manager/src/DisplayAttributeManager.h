/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  *
  * Source:    $File: //depot/3001_TIP_NEW/3001/transactive/app/signs/ttis_manager/src/DisplayAttributeManager.h $
  * @author:   Adam Radics
  * @version:  $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * This handles the time and priority controls
  * on the display page.
  *
  */


#if !defined(DisplayAttributeManager_H)
#define DisplayAttributeManager_H


#include <vector>
//xufeng++ 2006/11/06 TD14367
#include "CallbackDateTimeCtrl.h"
//++xufeng 2006/11/06 TD14367
#include "core/data_access_interface/tis_agent_4669/IDL/src/TisMessageDataDefinitions.h"
#include "bus/mfc_extensions/src/coloured_controls/ColourCombo.h"

using TA_Base_Bus::ColourCombo;

namespace TA_IRS_App
{

    class DisplayAttributeManager: public IDateTimeListener
    {

    public:


        // represents the type of message
        // to be sent
        enum TimeType
        {
            MESSAGE_CYCLIC = 0,
            MESSAGE_CONTINUOUS = 1
        };


        /**
          * DisplayAttributeManager
          *
          * Constructor
          *
          * @param priorityCombo        The priority combo box
          * @param timeTypeContinuous   The continuous radio button
          * @param timeTypeCyclic       The cyclic radio button
          * @param startTime            The start time time control
          * @param endTime              The end time time control
          * @param repeatInterval       The repeat interval time control
          *
          */
    // xufeng++ 2006/11/06 TD14367
    /*
    DisplayAttributeManager(ColourCombo& priorityCombo,
                                CButton& timeTypeContinuous,
                                CButton& timeTypeCyclic,
                                CDateTimeCtrl& startTime,
                                CDateTimeCtrl& endTime,
                                CDateTimeCtrl& repeatInterval,
                                CStatic& startTimeLabel,
                                CStatic& endTimeLabel,
                                CStatic& repeatIntervalLabel);
    */
    // ++xufeng 2006/11/06 TD14367
    DisplayAttributeManager(ColourCombo& priorityCombo,
                                CButton& timeTypeContinuous,
                                CButton& timeTypeCyclic,
                                CallbackDateTimeCtrl& startTime,
                                CallbackDateTimeCtrl& endTime,
                                CDateTimeCtrl& repeatInterval,
                                CStatic& startTimeLabel,
                                CStatic& endTimeLabel,
                                CStatic& repeatIntervalLabel);


        ~DisplayAttributeManager();


        /**
          * onTimeTypeContinuous
          *
          * Called when the time type is set to cyclic,
          * (Button press)
          */
        void onTimeTypeContinuous();


        /**
          * onTimeTypeCyclic
          *
          * Called when the time type is set to continuous,
          * (Button press)
          */
        void onTimeTypeCyclic();

        // xufeng++ 2006/11/06 TD14367
        /**
          * dateTimeChanged
          *
          * Gets called when a date/time is changed.
          *
          * @param control   the control that was changed
          */
        virtual void dateTimeChanged(CallbackDateTimeCtrl* control);
        // ++xufeng 2006/11/06 TD14367

        /**
          * getPriority
          *
          * gets the priority from the drop down priority box
          *
          * @return the priority from 1 to 8
          */
        unsigned short getPriority() const;


        /**
          * getMessageType
          *
          * Gets whether cyclic or continuous are set.
          *
          * @return the message type.
          */
        TimeType getMessageType() const;


        /**
          * getStartTime
          *
          * gets the start time HHMM
          *
          * @return the start time. HHMM.
          */
        CTime getStartTime() const;


        /**
          * getEndTime
          *
          * gets the end time HHMM
          *
          * @return the end time. HHMM.
          */
        CTime getEndTime() const;


        /**
          * getRepeatInterval
          *
          * Gets the repeat interval (in seconds).
          *
          * @return the repeat interval.
          */
        unsigned short getRepeatInterval() const;


        /**
          * enableTimeControls
          *
          * Enables or disables the time selection controls
          *
          * @param timeTypeEnabled  whether the time type selection can be enabled
          *
          */
        void enableTimeControls( bool timeTypeEnabled = true);


        /**
          * setPriority
          *
          * Set the default priority and whether the user can change it or if its disabled.
          * The message type will change to cyclic/continuous based on the given priority.
          *
          * @param newPriority  The new priority (if 6 will be set to 7)
          * @param canChange    true if the priority selection should be enabled.
          *
          */
        void setPriority( unsigned short newPriority, bool canChange = true);


        /**
          * setRepeatInterval
          *
          * Sets the repeat interval, and whether it can be changed by the user.
          * If it cannot be changed it will be disabled even when in cyclic mode.
          *
          * @param repeatInterval   The new repeat interval ( 1 to 999)
          * @param canChange        Whether it can be changed or not.
          *
          */
        void setRepeatInterval( unsigned short repeatInterval, bool canChange = true );


        /**
          * blankAndDisableTimeAndPriority
          *
          * This is called when nothing is selected on the pre-defined page.
          * It sets the message type to continuous, and blanks out the time controls.
          * It blanks out the priority and clears the priority box.
          *
          */
        void blankAndDisableTimeAndPriority();


    private:


        enum MessagePriorityType
        {
            NORMAL_PRIORITY_ONLY = 0,
            EMERGENCY_PRIORITY_ONLY = 1
        };


        /**
          * setMessagePriorityType
          *
          * Set what priorities are available in the priority selection combo
          *
          * @param prioritiesEnabled    all, normal only, or emergency only.
          */
        void setMessagePriorityType(MessagePriorityType prioritiesEnabled);


        /**
          * timeTypeChanged
          *
          * enables/disables controls based on whether cyclic or
          * continuous is selected.
          */
        void timeTypeChanged();


        DisplayAttributeManager(){}

        // The display attribute controls
        ColourCombo* m_priorityCombo;
        CButton* m_timeTypeContinuous;
        CButton* m_timeTypeCyclic;
        // xufeng++ 2006/11/06 TD14367
        CallbackDateTimeCtrl* m_startTime;
        CallbackDateTimeCtrl* m_endTime;
        // CDateTimeCtrl* m_startTime;
        // CDateTimeCtrl* m_endTime;
        // ++xufeng 2006/11/06 TD14367
        CDateTimeCtrl* m_repeatInterval;
        CStatic* m_startTimeLabel;
        CStatic* m_endTimeLabel;
        CStatic* m_repeatIntervalLabel;

        // this is used to determine which time-selection options
        // should be enabled and disabled
        bool m_repeatIntervalEnabled;

        // the time type - cyclic or continuous
        TimeType m_timeType;

        // the enabled priorities
        MessagePriorityType m_messagePrioritesEnabled;

    };

} // TA_IRS_App

#endif // !defined(DisplayAttributeManager_H)
