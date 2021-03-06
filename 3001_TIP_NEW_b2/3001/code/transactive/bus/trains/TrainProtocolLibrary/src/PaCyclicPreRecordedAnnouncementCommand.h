/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $Source$
  * @author:  Adam Radics
  * @version: $Revision$
  *
  * Last modification: $Date$
  * Last modified by:  $Author$
  *
  */
#if !defined(PaCyclicPreRecordedAnnouncementCommand_H)
#define PaCyclicPreRecordedAnnouncementCommand_H


#include "bus/trains/TrainProtocolLibrary/src/TimsCommand.h"
#include "bus/trains/TrainCommonLibrary/src/ProtocolPaTypes.h"


//forward declaration

namespace TA_IRS_Bus
{

    class PaCommandReceivedEvent;
    typedef boost::shared_ptr< PaCommandReceivedEvent > PaCommandReceivedEventPtr;
}


namespace TA_IRS_Bus
{

    /**
     * Command to make a cyclic pre recorded announcement
     * @author Adam Radics
     * @version 1.0
     * @created 05-Feb-2008 3:20:15 PM
     */

    class PaCyclicPreRecordedAnnouncementCommand : public TimsCommand
    {

    public:

        /**
         * cyclic pre recorded announcement command.
         *
         * @param trainId
         * @param origin    Command origin
         * @param requestMode
         * @param messageId
         * @param libraryVersion
         * @param period
         * @param duration
         * @param announcementId
         */
        PaCyclicPreRecordedAnnouncementCommand( CommonTypes::TrainIdType trainId,
                                                unsigned char origin,
                                                ProtocolPaTypes::EPaRequestMode requestMode,
                                                //unsigned char messageId,
                                                unsigned short messageId,
                                                //unsigned short libraryVersion,
                                                unsigned long libraryVersion,
                                                unsigned short period,
                                                unsigned short duration,
                                                unsigned char announcementId );


        /**
         * Destructor
         */
        virtual ~PaCyclicPreRecordedAnnouncementCommand();


        /**
         * Sets the response to this command, if it is not the matching response then the command will not accept the response.
         *
         * @return if the command accepted the response, and if the response should be considered consumed or not
         *
         * @param response
         */
        virtual TrainCommand::TrainResponseResult setResponse( TrainEventPtr response );


        /**
         * If this command resulted in a command received, return the event reader.
         *
         * @return a PaCommandReceivedEvent if the response was a command received, an empty PaCommandReceivedEventPtr otherwise.
         */
        PaCommandReceivedEventPtr getCommandReceivedResponse();


        /**
         * Returns a log string with information about this command.
         *
         * @return a string to log
         */
        virtual std::string getLogString();


    private:

        /**
         * Private default constructor
         */
        PaCyclicPreRecordedAnnouncementCommand();


        /**
         * The type of this message
         */
        static const TrainMessageType MESSAGE_TYPE;


        /**
         * The length of this message
         */
        static const unsigned short MESSAGE_LENGTH;


        /**
         * offset into the message of the request type field
         */
        static const unsigned short REQUEST_MODE_POSITION;


        /**
         * offset into the message of the identifier table type field
         */
        static const unsigned short IDENTIFIER_TABLE_TYPE_POSITION;


        /**
         * identifier table type value
         */
        static const unsigned short IDENTIFIER_TABLE_TYPE_VALUE;


        /**
         * offset into the message of the identifier table offset field (message id)
         */
        static const unsigned short IDENTIFIER_TABLE_OFFSET_POSITION;


        /**
         * offset into the message of the library version
         */
        static const unsigned short LIBRARY_VERSION_POSITION;


        /**
         * offset into the message of the T1 (duration)
         */
        static const unsigned short T1_DURATION_POSITION;


        /**
         * offset into the message of the T2 (period)
         */
        static const unsigned short T2_PERIOD_POSITION;


        /**
         * offset into the message of the request type field
         */
        static const unsigned short ANNOUNCEMENT_ID_POSITION;


        /**
         * Whether a request or override
         */
        ProtocolPaTypes::EPaRequestMode m_requestMode;


        /**
         * The ID of the message to play
         */
        //unsigned char m_messageId;
        unsigned short m_messageId;


        /**
         * The library version the message comes from
         */
        //unsigned short m_libraryVersion;
        unsigned long m_libraryVersion;


        /**
         * The T1/Duration value
         */
        unsigned short m_t1Duration;


        /**
         * The T2/Period value
         */
        unsigned short m_t2Period;


        /**
         * the announcement ID
         */
        unsigned char m_announcementId;

    };


    typedef boost::shared_ptr< PaCyclicPreRecordedAnnouncementCommand > PaCyclicPreRecordedAnnouncementCommandPtr;

}

#endif // !defined(PaCyclicPreRecordedAnnouncementCommand_H)
