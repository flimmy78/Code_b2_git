/**
  * TimeFunction.cpp
  *
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/history/history_viewer/src/TimeFunction.cpp $
  * @author:  Craig Grant
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * This class contains time conversion routines.
  * This class is a singleton.
  *
  */

#include <string>

#include "app/history/history_viewer/src/stdafx.h"
#include "app/history/history_viewer/src/historyviewer.h"
#include "app/history/history_viewer/src/TimeFunction.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/exceptions/src/HistoryInitialisationException.h"

#include "cots/ACE/5_3/ACE_wrappers/ace/OS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace TA_App
{
    //
    // TimeFunction
    //
    TimeFunction::TimeFunction()
    {
        GetTimeZoneInformation( &m_TimeZoneInformation );
    }

    //
    // ~TimeFunction
    //
    TimeFunction::~TimeFunction()
    {
    }

    
    //
    // ConvertToUTC
    //
    CString TimeFunction::ConvertToUTC(const COleDateTime& inTime)
    {
        CTime newTime(inTime.GetYear(), inTime.GetMonth(), inTime.GetDay(),
			          inTime.GetHour(), inTime.GetMinute(), inTime.GetSecond());
        newTime.GetLocalTm();
        return( newTime.FormatGmt( "%d/%m/%Y %H:%M" ) );
    }


#ifdef USE_OCCI
    // 
    // ConvertToLocal
    //
    void TimeFunction::ConvertToLocal(const oracle::occi::Date& inDate, COleDateTime& outTime)
    {
        //
        // Get the values from the oracle Date object
        //
        int year;
        unsigned int month, day, hour, minute, second;
        inDate.getDate(year, month, day, hour, minute, second);

        //
        // Place them in a SYSTEMTIME object
        //
        SYSTEMTIME universalTime, localTime;
        universalTime.wYear = year;
        universalTime.wMonth = month;
        universalTime.wDay = day;
        universalTime.wHour = hour;
        universalTime.wMinute = minute;
        universalTime.wSecond = second;
        universalTime.wMilliseconds = 0;
        universalTime.wDayOfWeek = 0;

        //
        // Convert the UTC time to local time
        //
        SystemTimeToTzSpecificLocalTime(&m_TimeZoneInformation, &universalTime, &localTime);

        //
        // Set the values in outTime
        //
        outTime.SetDateTime(localTime.wYear, localTime.wMonth, localTime.wDay, 
					        localTime.wHour, localTime.wMinute, localTime.wSecond);

        return;
    }
#endif // USE_OCCI


    // 
    // ConvertToLocal
    //
    void TimeFunction::ConvertToLocal(const std::string& inDate, COleDateTime& outTime)
    {
        //
        // Parse the date/time string - this throws an exception, but let it be caught
        // higher up.
        //
        time_t parsedInDate = ParseDateTime(inDate);
        ConvertToLocal(parsedInDate, outTime);
    }


    // 
    // ConvertToLocal
    // 
    void TimeFunction::ConvertToLocal(time_t inDate, COleDateTime& outTime)
    {
        struct tm newtime;
        ACE_OS::localtime_r( &inDate, &newtime ); 

        //
        // Place them in a SYSTEMTIME object
        //
        SYSTEMTIME universalTime, localTime;
        universalTime.wYear = newtime.tm_year + 1900;
        universalTime.wMonth = newtime.tm_mon + 1;
        universalTime.wDay = newtime.tm_mday;
        universalTime.wHour = newtime.tm_hour;
        universalTime.wMinute = newtime.tm_min;
        universalTime.wSecond = newtime.tm_sec;
        universalTime.wMilliseconds = 0;
        universalTime.wDayOfWeek = 0;

        //
        // Convert the UTC time to local time
        //
        SystemTimeToTzSpecificLocalTime(&m_TimeZoneInformation, &universalTime, &localTime);

        //
        // Set the values in outTime
        //
        outTime.SetDateTime(localTime.wYear, localTime.wMonth, localTime.wDay, 
					        localTime.wHour, localTime.wMinute, localTime.wSecond);
    }


    // 
    // ParseDateTime
    //
    time_t TimeFunction::ParseDateTime(const std::string& inDate)
    {
        LOG ( SourceInfo, TA_Core::DebugUtil::FunctionEntry, "ParseDateTime" );

        //
        // The date string should have no non-numeric characters. This test will determine that.
        //
        int numberTest = inDate.find_first_not_of("0123456789");
        
        //
        // The target string MUST bet 14 characters long, and 14 characters long ONLY
        // If the correct database select has been used this will be guaranteed.
        // We have not used an assert here as it could be possible to load the data with a valid 
        // string and get something invalid
        //
        if ((14 != inDate.size()) || (-1 != numberTest))
        {
            TA_THROW(TA_Core::HistoryInitialisationException("Invalid time field"));
        }

        std::string strYear = inDate.substr(0,4);
        std::string strMonth = inDate.substr(4,2);
        std::string strDay = inDate.substr(6,2);
        std::string strHour = inDate.substr(8,2);
        std::string strMinute = inDate.substr(10,2);
        std::string strSecond = inDate.substr(12,2);

        int iYear = atoi(strYear.c_str());
        int iMonth = atoi(strMonth.c_str());
        int iDay = atoi(strDay.c_str());
        int iHour = atoi(strHour.c_str());
        int iMinute = atoi(strMinute.c_str());
        int iSecond = atoi(strSecond.c_str());

        //
        // Need to sanity check the date data, as mktime won't do it for us
        // NB: It is not checked that the day is valid for the month
        //
        bool dateSanityError = false;
        dateSanityError = (iSecond > 59 || iMinute > 59 || iHour > 24);
        dateSanityError = (dateSanityError || iDay > 31 && iDay != 0);
        dateSanityError = (dateSanityError || iMonth > 12 || iMonth == 0);
        dateSanityError = (dateSanityError || iYear > 2038 || iYear < 1900);
        if (dateSanityError)
        {
            TA_THROW(TA_Core::HistoryInitialisationException("Invalid time field"));
        }

        const int FEBRUARY = 2;
        const int APRIL = 4;
        const int JUNE = 6;
        const int SEPTEMBER = 9;
        const int NOVEMBER = 11;

        //
        // Now need to check that the day is valid based on the month/year
        //
        if (iMonth == APRIL || iMonth == JUNE || iMonth == SEPTEMBER || iMonth == NOVEMBER) // 30 days
        {
	        if (iDay == 31)
	        {
		        TA_THROW(TA_Core::HistoryInitialisationException("Invalid time field"));
	        }
        }
        else if (iMonth == FEBRUARY) // more processing necessary
        {		
	        if (0 == (iYear%4) && (0 != (iYear%100) || 0 == (iYear%400))) // This is a leap year
	        {
		        if (iDay > 29)
		        {
			        TA_THROW(TA_Core::HistoryInitialisationException("Invalid time field"));
		        }
	        }
	        else // not a leap year
	        {
		        if (iDay > 28)
		        {
			        TA_THROW(TA_Core::HistoryInitialisationException("Invalid time field"));
		        }
	        }
        }
        // else - don't need to check for 31 days, as we did that above

        struct tm newtm;

        newtm.tm_sec = iSecond;		//seconds
        newtm.tm_min = iMinute;		// hours 
        newtm.tm_hour = iHour;		// minutes 
        newtm.tm_mday = iDay;		// day of the month 
        newtm.tm_mon = iMonth-1;	// month of Year - goes from 0 to 11
        newtm.tm_year = iYear-1900;	// years since 1900 - this structure only deals with years 
							        // between 1901 and 2038
        newtm.tm_isdst = 0;			// disable daylight savings - this could have implications

        time_t value;
        value = mktime(&newtm);
        
        // check that the time conversion worked successfully
        if (-1 == value) // conversion failed
        {
	        TA_THROW(TA_Core::HistoryInitialisationException("Invalid time field"));
        }

        return value;
    }

} // TA_App


