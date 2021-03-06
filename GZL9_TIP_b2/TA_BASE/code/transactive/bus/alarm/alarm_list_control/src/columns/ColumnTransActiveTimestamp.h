/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/TA_Common_V1_TIP/transactive/bus/alarm/alarm_list_control/src/columns/ColumnTransActiveTimestamp.h $
 * @author:  Karen Graham
 * @version: $Revision: #1 $
 *
 * Last modification: $DateTime: 2015/01/19 17:43:23 $
 * Last modified by:  $Author: CM $
 * 
 * This class provides all the information for the transactive timestamp column.
 *
 * BJR 19/8/04: THIS CLASS IS NOT USED BY THE ALARM MANAGER ANYMORE.
 */

#if !defined(AFX_ColumnTransActiveTimestamp_H__26C75118_4AC8_4594_BBE3_266FC53666A0__INCLUDED_)
#define AFX_ColumnTransActiveTimestamp_H__26C75118_4AC8_4594_BBE3_266FC53666A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bus/alarm/alarm_list_control/src/columns/AbstractAlarmColumn.h"
#include "bus/alarm/alarm_list_control/src/columns/ColumnIdentifiers.h"

namespace TA_Base_Bus
{

    class ColumnTransActiveTimestamp: public AbstractAlarmColumn
	{
	public:

        
        /**
         * Constructor
         *
         * @param int - The width of the column
         * @param bool - Whether the column is currently enabled
         * @param Sort* - The ascending sort for the column. If the sort is NULL then the default sort will be used
         * @param Sort* - The descending sort for the column. If the sort is NULL then the default sort will be used
         * @param IAlarmAction* - The action to perform when the user double-clicks on the column. This can be NULL
         *                        signifying no action.
         */
        ColumnTransActiveTimestamp(int width,
                         bool isEnabled,
                         SORT_COLUMN sortCol,
                         IAlarmAction* doubleClickAction);


        virtual ~ColumnTransActiveTimestamp()
        {
        };


        /**
         * getColumnIdentifier
         *
         * @return long - A unique identifier for this column. This is defined in the file ColumnIdentifiers.h
         */
        virtual long getColumnIdentifier() const
        {
            return COL_TRANSACTIVETIMESTAMP;
        }


        /**
         * getColumnHeaderText
         *
         * @return CString - Returns the column header text
         */
        virtual CString getColumnHeaderText() const
        {
            return "Date/Time";
        }


        /**
         * getItemText
         *
         * @param AlarmDetailCorbaDef* - The alarm to retrieve information for
         * @param DatabaseCache - This object can be used to retrieve database information if necessary
         *
         * @return CString - This returns the text to display in the column for the specified alarm.
         */
        virtual CString getItemText(TA_Base_Core::AlarmDetailCorbaDef* alarm,
                                    DatabaseCache& databaseCache);


        /**
         * setTimeFormat
		 *
		 * Sets the time format used by this column. This function asserts that the time
		 * format is not an empty string, but otherwise it is up to the client to ensure
		 * that the format passed is valid. The default format is "%d-%b-%y %H:%M:%S".
         *
         * @param const CString& - The format string as per the strftime command
         */
        void setTimeFormat(const CString& formatStr);


    private:
        /**
         * operator= - Hidden as not used
         */
        ColumnTransActiveTimestamp& operator=(const ColumnTransActiveTimestamp& rhs);

        /**
         * Copy constructor - Hidden as not used
         */
        ColumnTransActiveTimestamp(const ColumnTransActiveTimestamp&);
 
		// String used to format the date/time as per the strftime command
		CString m_formatStr;
 
	};
} //End of TA_Base_Bus


#endif // !defined(AFX_ColumnTransActiveTimestamp_H__26C75118_4AC8_4594_BBE3_266FC53666A0__INCLUDED_)
