#ifndef PA_SIM_TABLE_ISCSALARM_H
#define PA_SIM_TABLE_ISCSALARM_H
/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/simulator/pa/PASimulatorLibrary/src/PASimTableIscsAlarm.h $
  * @author:  Robert van Hugten
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  * 
  * Declaration file for PASimTableIscsAtcData class
  */
#include "PASimTable.h"
#include "PASimCommon.h"

namespace TA_IRS_App
{
namespace PA_Sim
{
    const int NumberOfAtcBytes = 22;

    /**
      * @class PASimTableIscsAtcData
      *
      * PASimTableIscsAtcData is a derived table class.
      *
      * TABLE IscsAtcData 
      *
      */
    class PASimTableIscsAtcData : public PASimTable
    {

    public:
        /**
          * Preferred constructor
          * @param parent the owner of this object
          */
        PASimTableIscsAtcData(PASimTableQueryProcessor * parent, LocationType loc);

        /**
          * Destructor
          */
        ~PASimTableIscsAtcData();


        /**
          * Accessor for the size of this table
          * @return the size of the data in this table as determined by the
          *         value of m_tableData.size()
          */
        unsigned short getTableSize() const;


        /** Virtual streaming operator.
          * Overridden from the base class PASimTable::toStream
          */
        virtual void toStream(std::ostream& os) const;
        

        /** Virtual in-stream operator.
          * Overridden from the base class PASimTable::toStream
          *
          * Inputs the table data to the stream as a string of bytes using
          * PASimUtility::data2string, which at the moment means hexadecimal.
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

    private:
        /**
          * struct representing the data in an IscsAtcData table
          */
        typedef struct PASimTableIscsAtcDataRecord
        {
            Word                physicalTrainNumber;
            Byte                atcStatusReportCodeHeader;
            Byte                atcStatusReport[NumberOfAtcBytes];
        };

        /**
          * 
          */
        PASimTableIscsAtcDataRecord * m_tableData;


        /**
          * overridden to make this class concrete. To be implemented later.
          */
        virtual UserResponse * processUserRead(UserQuery * ur);

        /**
          * overridden to make this class concrete. To be implemented later.
          */
        virtual UserResponse * processUserWrite(UserQuery * ur);

        static const int NumberOfOCCRecords;
        static const int NumberOfMSSRecords;
        static const int NumberOfDPTRecords;
    }; // class PASimTableIscsAtcData
} // namespace PA_Sim
} // namespace TA_IRS_App
#endif // #ifndef PA_SIM_TABLE_ISCSALARM_H
