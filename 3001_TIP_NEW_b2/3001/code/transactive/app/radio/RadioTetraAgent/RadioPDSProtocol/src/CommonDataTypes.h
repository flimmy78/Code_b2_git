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
#if !defined(PDS_COMMONDATATYPES_H)
#define PDS_COMMONDATATYPES_H


#include "app/radio/RadioTetraAgent/RadioPDSProtocol/src/CommonTypes.h"

#include <set>
#include <vector>


namespace TA_IRS_App
{
    
    /**
     * Typedef for a train message type, its an unsigned char (1 byte number)
     * @author Adam Radics
     * @version 1.0
     * @created 22-Oct-2007 12:19:37 PM
     */
    typedef unsigned char TrainMessageType;


    /**
     * A list of command/event types
     * @author Adam Radics
     * @version 1.0
     * @created 22-Oct-2007 12:19:37 PM
     */
    typedef std::set< TrainMessageType > TrainMessageTypeList;


    /**
     * Raw message data sent and received for train messages
     * @author Adam Radics
     * @version 1.0
     * @created 22-Oct-2007 12:19:37 PM
     */
    typedef std::vector< unsigned char > TrainMessageData;


    /**
     * This is used where exceptions cant be.
     * - Scheduled commands
     * - Batch Commands (multiple commands executed simultaneously)
     *
     * The values are taken directly from the defined exceptions
     * @author Adam Radics
     * @version 1.0
     * @created 22-Oct-2007 12:19:37 PM
     */
    enum ETrainError
    {
        NoError = 0,
        GeneralFailure = 1,
        InvalidTrain = 2,
        ProtocolError = 3,
        TrainBusy = 4,
        TrainTimeout = 5,
        TransmissionFailure = 6,
        AccessDeniedException = 7,
        TransactionCancelled = 8
    };

	/**
	 * The Protocol Message
	 */

	struct structPDSProtocol
	{
		TrainMessageType s_flag;
		TrainMessageType s_messageType;
		TrainMessageType s_trainId;
		TrainMessageType s_messageLength;
		TrainMessageType s_origin;
		TrainMessageType s_Destination;
	};

}

#endif // !defined(CommonDataTypes_H)
