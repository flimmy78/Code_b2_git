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
#if !defined(EndOfOccCallEvent_H)
#define EndOfOccCallEvent_H

#include "bus/trains/TrainProtocolLibrary/src/TimsEvent.h"


namespace TA_IRS_Bus
{

    /**
     * Incoming end of OCC call
     * @author Adam Radics
     * @version 1.0
     * @created 05-Feb-2008 3:20:05 PM
     */

    class EndOfOccCallEvent : public TimsEvent
    {

    public:

        /**
         * Create a train event from incoming data
         *
         * @exception ProtocolException if the event could not be created ie the event is invalid
         *
         * @param data    The incoming data
         * @param sendingTsi    who sent it
         * @param destinationTsi    where it was sent to
         */
        EndOfOccCallEvent( const TrainMessageData& data,
                           const std::string& sendingTsi,
                           const std::string& destinationTsi );


        /**
         * Destructor
         */
        virtual ~EndOfOccCallEvent();


        /**
         * Gets the type of message this reader is for.
         */
        static TrainMessageType getStaticType();


    protected:

        /**
         * Gets the length of the expected message, so the message length can be validated.
         */
        virtual unsigned short getExpectedMessageLength() const;


    private:

        /**
         * Private default constructor
         */
        EndOfOccCallEvent();


        /**
         * Constant used by getStaticType
         */
        static const TrainMessageType MESSAGE_TYPE;


        /**
         * Expected length of the entire message
         */
        static const unsigned short EXPECTED_MESSAGE_LENGTH;

    };

    /**
    * @author Adam Radics
    * @version 1.0
    * @created 05-Feb-2008 3:20:05 PM
    */
    typedef  boost::shared_ptr< EndOfOccCallEvent > EndOfOccCallEventPtr;


}

#endif // !defined(EndOfOccCallEvent_H)
