/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/response_plans/plan_manager/src/TisConfigAccess.h $
  * @author:  Bart Golab
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * This is a utility class. It's used to retrieve from the database
  * various TIS related configuration data items.
  *
  */

#if !defined(AFX_TISCONFIGACCESS_H__7ED31E52_E6DD_4577_8BAD_A6A06BF9C28B__INCLUDED_)
#define AFX_TISCONFIGACCESS_H__7ED31E52_E6DD_4577_8BAD_A6A06BF9C28B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>
#include <set>
#include "core/data_access_interface/tis_agent_4669/src/IPredefinedMessageLibrary.h"
#include "core/data_access_interface/PlanAgent/IDL/src/PlanAgentDataCorbaDef.h"


namespace TA_Base_App
{
    /////////////////////////////////////////////////////////////////////////////
    // TisConfigAccess

    class TisConfigAccess
    {
    // Types
    public:
        // Extend TA_Base_Core::PredefinedMessage with a copy ctor and an assignment
        // operator so that it can be used with STL containers.
        struct PredefinedTisMessage : public TA_Base_Core::PredefinedMessage
        {
            PredefinedTisMessage()
            {
                messageTag = TA_Base_Core::TIS_UNDEFINED_MESSAGE_ID;
                librarySection = 0;
                description = "";
                priority = 0;
                message = "";
                englishOnly = true;
                repeatInterval = 0;
            }

            PredefinedTisMessage(const TA_Base_Core::PredefinedMessage& predefinedMessage)
            {
                *this = predefinedMessage;
            }

            PredefinedTisMessage& operator=(const TA_Base_Core::PredefinedMessage& predefinedMessage)
            {
                if (this != &predefinedMessage)
                {
                    messageTag = predefinedMessage.messageTag;
                    librarySection = predefinedMessage.librarySection;
                    description = predefinedMessage.description;
                    priority = predefinedMessage.priority;
                    message = predefinedMessage.message;
                    englishOnly = predefinedMessage.englishOnly;
                    repeatInterval = predefinedMessage.repeatInterval;
                }

                return *this;
            }
        };

        typedef std::vector<PredefinedTisMessage> PredefinedTisMessageList;
        typedef std::set<std::string> TisStationNameSet;
        typedef std::set<std::string> TisStationLevelSet;
        typedef std::set<std::string> TisPidSet;


    // Operations
    public:
        static std::string getSTisMessageText(const TA_Base_Core::TISMessage& message);
        static std::string getTTisMessageText(const TA_Base_Core::TISMessage& message);
        static PredefinedTisMessageList getSTisMessages(unsigned short libraryVersion);
        static PredefinedTisMessageList getTTisMessages(unsigned short libraryVersion);
        static TisStationNameSet getSTisStations();
        static TisStationLevelSet getSTisLevels(const std::string& stationName = "");
        static TisPidSet getSTisPids(const std::string& stationName = "");

    private:
        static std::string getTisMessageText(const TA_Base_Core::TISMessage& message, const std::string& libraryType);
        static void getTisMessages(unsigned short libraryVersion, const std::string& libraryType, PredefinedTisMessageList& messages);
    };
}

#endif // !defined(AFX_TISCONFIGACCESS_H__7ED31E52_E6DD_4577_8BAD_A6A06BF9C28B__INCLUDED_)
