#ifndef ATS_SIM_TABLE_ATSWATCHDOG_H
#define ATS_SIM_TABLE_ATSWATCHDOG_H
/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/ats/ATSSimulatorLibrary/src/ATSSimTableAtsWatchdog.h $
  * @author:  Robert van Hugten
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * Declaration file for ATSSimTableAtsWatchdog class
  */
#include "app/ats/ATSSimulatorLibrary/src/ATSSimTable.h"
#include "app/ats/ATSSimulatorLibrary/src/ATSSimCommon.h"
#include "app/ats/ATSSimulatorLibrary/src/ATSSimModbusFrames.h"

namespace TA_IRS_App
{
namespace ATS_Sim
{
    /**
      * @class ATSSimTableAtsWatchdog
      *
      * ATSSimTableAtsWatchdog is a derived table class.
      *
      * TABLE AtsWatchdog 
      *
      */
    class ATSSimTableAtsWatchdog : public ATSSimTable
    {

    public:
        /**
          * Preferred constructor
          * @param parent the owner of this object
          */
        ATSSimTableAtsWatchdog(ATSSimTableQueryProcessor * parent, LocationType loc);

        /**
          * Destructor
          */
        ~ATSSimTableAtsWatchdog();


        /**
          * Accessor for the size of this table
          * @return the size of the data in this table as determined by the
          *         value of m_counter.size()
          */
        unsigned short getTableSize() const;


        /** Virtual streaming operator.
          * Overridden from the base class ATSSimTable::toStream
          */
        virtual void toStream(std::ostream& os) const;
        

        /** Virtual in-stream operator.
          * Overridden from the base class ATSSimTable::toStream
          *
          * Inputs the table data to the stream as a string of bytes using
          * ATSSimUtility::data2string, which at the moment means hexadecimal.
          */
        virtual void fromStream(const std::ostream& os);
        

        /** Place the table data into a stream of bytes for sending through the
          * socket.  This base class' default behaviour is to send the raw
          * as retrieved by getByteVector(ByteVector &);
          * 
          * Derived classes should override either this or getByteVector to
          * ensure that the ByteVector has the appropriate raw data in
          * network order.
          */
        virtual void toNetwork(ByteVector & n);


        /** Accept the stream of bytes from the socket.  Store locally as
          * best suits.  This base class' default behaviour is to accept the
          * raw bytes and store them as such.
          */
        virtual void fromNetwork(const ByteVector & s);

        /**
          * Overloaded accessor for the underlying ByteVector, ie. the
          * std::vector of unsigned chars that represents the table data.
          * 
          * @param bv the vector to fill with this table's raw data.
          */
        virtual void getByteVector(ByteVector & bv) const;

        ///
        ///
        static Word getValueFieldNumber();

        ///
        ///
        static Word getOffsetFieldNumber();

        ///
        ///
        static Word getPauseResumeFieldNumber();

    private:
        ///
        /// All the data in the watchdog table is a single unsigned 2 byte
        /// (ie. Word) number
        Word m_counter;


        ///
        /// Plus an offset, used for adjusting the time value
        Word m_offset;

        ///
        /// A pause flag. The counter is not updated while this is true
        bool m_pause;

        /**
          * Writes the value of the m_counter in a formatted table
          */
        virtual UserResponse * processUserRead(UserQuery * qry);

        /**
          * Allows the "set watchdog" command to set the offset, value of the
          * counter, and pause/resume
          */
        virtual UserResponse * processUserWrite(UserQuery * qry);

        ///
        ///
        static const Word sValueField;

        ///
        ///
        static const Word sOffsetField;

        ///
        ///
        static const Word sPauseResumeField;


    }; // class ATSSimTableAtsWatchdog
} // namespace ATS_Sim
} // namespace TA_IRS_App
#endif // #ifndef ATS_SIM_TABLE_ATSWATCHDOG_H
