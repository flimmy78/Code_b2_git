#ifndef PA_SIM_TABLE_MODBUS_TCP_H
#define PA_SIM_TABLE_MODBUS_TCP_H
/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/simulator/pa/PASimulatorLibrary/src/PASimStandardModbusTcpTable.h $
  * @author:  Robert van Hugten
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * Declaration file for PASimTablePATrain class
  */
#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4284)
#endif // #ifdef WIN32

#include "bus/modbus_comms/src/DataBlock.h"

#include "app/simulator/pa/PASimulatorLibrary/src/PASimTable.h"
#include "app/simulator/pa/PASimulatorLibrary/src/PASimCommon.h"
#include "app/simulator/pa/PASimulatorLibrary/src/PASimTableEnum.h"

namespace TA_IRS_App
{
    class AbstractScenario;
namespace PA_Sim
{
    /**
      * @class PASimTablePATrain
      *
      * PASimTablePATrain is a derived table class.
      *
      * TABLE PATrain 
      *
      */
    class PASimTableStandardModbus : public PASimTable
    {

    public:
        /**
          * Preferred constructor
          * @param parent the owner of this object
          */
        PASimTableStandardModbus(int startAddress, 
                                  int endAddress, 
                                  PASimTableQueryProcessor* parent, 
                                  LocationType loc);

        /**
          * Destructor
          */
        ~PASimTableStandardModbus();


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

        void resetAllData2Zero();

        int getRegisterValue(int address);
        int setRegisterValue(int address, int val);
		int setMultiRegistersValues(int startAddress, int endAddress, ByteVector& data);

/*    protected:*/

        /**
          * overridden to make this class concrete. To be implemented later.
          */
        virtual UserResponse * processUserRead(UserQuery * ur);

        /**
          * overridden to make this class concrete. To be implemented later.
          */
        virtual UserResponse * processUserWrite(UserQuery * ur);
		virtual UserResponse * processUserIncQuery(UserQuery * query);

        virtual void processReadQuery(ModbusQuery * query);
        virtual void processWriteQuery(ModbusQuery * query);


        int isWriteQueryIllegal(ModbusQuery * query);

        int m_startAddress;
        int m_endAddress;
        ByteVector m_data;
        PASimTableStandardModbus* m_leftChild;
        PASimTableStandardModbus* m_rightChild;

    }; // class PASimTableStandardModbus

} // namespace PA_Sim
} // namespace TA_IRS_App
#endif // #ifndef PA_SIM_TABLE_MODBUS_TCP_H
