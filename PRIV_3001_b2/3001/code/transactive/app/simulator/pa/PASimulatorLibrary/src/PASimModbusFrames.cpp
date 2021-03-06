/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/simulator/pa/PASimulatorLibrary/src/PASimModbusFrames.cpp $
  * @author:  Robert van Hugten
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  */

// for ntohs,ntohl,htonl,htons
#if !defined( WIN32 )
#include <arpa/inet.h>
#else
#include <winsock2.h>
#endif // !WIN32

#include "app/simulator/pa/PASimulatorLibrary/src/PASimModbusFrames.h"
#include "core/sockets/src/ISocket.h"

#include <algorithm>
#include <iostream>

using namespace TA_IRS_App::PA_Sim;

// ModbusFrame::ModbusFrame(Byte functionCode)
// : m_functionCode(functionCode)
// , m_tableAddress(0)
// , m_tableSize(0)
// , m_exceptionCode(0)
// , m_tableData(0)
// , m_crc(0)
// , m_socket(0)
// {
// }
// 
// ModbusFrame::~ModbusFrame()
// {
// }
// 
// ModbusQuery::ModbusQuery(Byte functionCode)
// :ModbusFrame(functionCode)
// {
// }
// 
// ModbusReadQuery::ModbusReadQuery()
// :ModbusQuery(PASim_FC_Read)
// {
// }
// 
// union TheseTwoBytes
// {
//     unsigned char two_uchars[2];
//     unsigned short one_ushort;
// };
// 
// //
// //  Modified Read Query Packet Format
// //
// //     BYTE  | SIZE  |  DESCRIPTION           | DATA
// //  ---------+-------+------------------------+------------------
// //      1    |   1   |  Function Code         | 0x04
// //  ---------+-------+------------------------+------------------
// //     2-3   |   2   |  Starting Address      | 0x0064
// //           |       |  (a.k.a. Table Number) |
// //  ---------+-------+------------------------+------------------
// //
// //  Alstom 'Beautified' Modbus Read Query Packet Format
// //
// //     BYTE  | SIZE  |  DESCRIPTION           | DATA
// //  ---------+-------+------------------------+------------------
// //      0    |   1   |  Device Address        | 0x00
// //  ---------+-------+------------------------+------------------
// //      1    |   1   |  Function Code         | 0x04
// //  ---------+-------+------------------------+------------------
// //     2-3   |   2   |  Starting Address      | 0x0064
// //           |       |  (a.k.a. Table Number) |
// //  ---------+-------+------------------------+------------------
// //     4-5   |   2   |  Number Of Words       | 0x0064
// //           |       |  To Read (Table Size)  |
// //  ---------+-------+------------------------+------------------
// //     6-7   |   2   |  CRC (zero)            | 0x0000
// //  ---------+-------+------------------------+------------------
// //  
// void ModbusReadQuery::fromNetwork(std::vector<unsigned char>::iterator & iter)
// {
//     // UNUSED variables
//     // Byte deviceAddress= iter[0];
//     // Byte functionCode = iter[1];
// 
//     // 
//     // NOTE
//     // On Solaris, the following code snippet causes a core dump on the
//     // second line:
//     // 
//     //     unsigned short * networkShortP = (unsigned short *)(&(iter[1]));
//     //     unsigned short networkShort = *networkShortP;
//     //
//     // as does replacing the first line with the following.
//     //
//     //     unsigned short * networkShortP = (unsigned short *)((void *)((&(*iter))+1));
//     //
//     // There does not appear to be any good reason for such.  Even gdb is able
//     // to "print *networkShortP" correctly in both cases, and dumping memory
//     // with "x/2b networkShortP" is also good.
//     //
//     // Our fix is to use a union hack, which ought to do the same thing, just
//     // one byte at a time.
//     //
//     TheseTwoBytes r_two_bytes;
//     r_two_bytes.two_uchars[0] = iter[2];
//     r_two_bytes.two_uchars[1] = iter[3];
// 
//     unsigned short networkShort = r_two_bytes.one_ushort; 
//     m_tableAddress = ntohs(networkShort);
// 
//     //
//     // expected table size
//     r_two_bytes.two_uchars[0] = iter[4];
//     r_two_bytes.two_uchars[1] = iter[5];
//     networkShort = r_two_bytes.one_ushort; 
//     m_tableSize = ntohs(networkShort) * 2; // our table size is in bytes, normal modbus is in words
//     
//     iter+=getHeaderSize();
// 
//     //
//     // zero'd crc
//     r_two_bytes.two_uchars[0] = iter[0];
//     r_two_bytes.two_uchars[1] = iter[1];
//     networkShort = r_two_bytes.one_ushort; 
//     m_crc = ntohs(networkShort);
//     
//     iter+=getFooterSize();
// }
// 
// int ModbusReadQuery::getHeaderSize() const
// {
//     return 6;
// }
// 
// int ModbusReadQuery::getFooterSize() const
// {
//     return 2;
// }
// 
// ModbusWriteQuery::ModbusWriteQuery()
// :ModbusQuery(PASim_FC_Write)
// {
// }
// 
// //
// //  Modified Write Query Packet Format
// //
// //      BYTE    |   SIZE    | DESCRIPTION          | DATA
// //  ------------+-----------+----------------------+------------
// //       1      |     1     | Function Code        | 0x10
// //  ------------+-----------+----------------------+------------
// //      2-3     |     2     | Starting Address     | 0x0064
// //              |           | (a.k.a. Table Number)|
// //  ------------+-----------+----------------------+------------
// //      4-5     |     2     | Number of Words      | 0x10
// //  ------------+-----------+----------------------+------------
// //      6 to    |           | Data exchanged       |
// //  (Table size |    ...    | between              |   ...
// //   - 1 + 6)   |           | devices              |
// //  ------------+-----------+----------------------+------------
// //  
// void ModbusWriteQuery::fromNetwork(std::vector<unsigned char>::iterator & iter)
// {
//     // UNUSED Byte functionCode = *iter;
// 
//     //
//     // Header
//     //
//     // See the NOTE in ModbusReadQuery::fromNetwork for why the roundabout
//     // approach is required for accessing stuff from the iterator.
//     TheseTwoBytes w_two_bytes;
//     w_two_bytes.two_uchars[0] = iter[2];
//     w_two_bytes.two_uchars[1] = iter[3];
//     unsigned short networkShort = w_two_bytes.one_ushort; 
//     m_tableAddress = ntohs(networkShort);
// 
//     //
//     // table size (number of registers)
//     w_two_bytes.two_uchars[0] = iter[4];
//     w_two_bytes.two_uchars[1] = iter[5];
//     networkShort = w_two_bytes.one_ushort; 
//     m_tableSize = ntohs(networkShort) * 2; // table size is twice the number of registers
// 
//     // UNUSED Byte byteCount = iter[6];
//     
//     iter += getHeaderSize();
// 
//     //
//     // Data
//     //
//     // Must ensure just enough storage in the table.
//     // Really need to use resize() rather than reserve(), as std::copy doesn't
//     // increase the size(), just copies
//     m_tableData.resize(m_tableSize);
//     std::copy(iter,iter+m_tableSize,m_tableData.begin());
//     // unsigned char * data = iter+5;
//     // memcpy(&(m_tableData[0]),data,m_tableSize);
//     iter += m_tableSize;
// 
//     //
//     // Footer
//     //
//     // crc
//     w_two_bytes.two_uchars[0] = iter[0];
//     w_two_bytes.two_uchars[1] = iter[1];
//     networkShort = w_two_bytes.one_ushort; 
//     m_crc = ntohs(networkShort);
// 
//     iter += getFooterSize();
// }
// 
// int ModbusWriteQuery::getHeaderSize() const
// {
//     return 7;
// }
// 
// int ModbusWriteQuery::getFooterSize() const
// {
//     return 2;
// }
// 
// ModbusResponse::ModbusResponse(Byte functionCode)
// :ModbusFrame(functionCode)
// {
// }
// 
// ModbusReadResponse::ModbusReadResponse()
// :ModbusResponse(PASim_FC_Read)
// {
// }
// 
// //
// //  Modified Read Response Packet Format
// //
// //     BYTE  | SIZE  |  DESCRIPTION           | DATA
// //  ---------+-------+------------------------+------------------------
// //      0    |   1   |  Device Address        | 0x00
// //  ---------+-------+------------------------+------------------------
// //      1    |   1   |  Function Code         | 0x04
// //  ---------+-------+------------------------+------------------------
// //      2    |   1   |  Byte Count            | 0x00
// //  ---------+-------+------------------------+------------------------
// //     3 to  |       |  Data                  |
// //    (table |  ...  |  exchanged             | ...
// //     size  |       |  between               |
// //   - 1 + 6)|       |  devices               |
// //  ---------+-------+------------------------+------------------------
// //      2    |   1   |  Byte Count            | 0x00
// //  ---------+-------+------------------------+------------------------
// //
// //  
// void ModbusReadResponse::toNetwork(std::vector<unsigned char> & packet)
// {
//     unsigned char * pktShrtPtr = 0;
//     unsigned short networkShort = 0;
//     //
//     // Header
//     //
//     // address
//     packet.push_back(0);
//     //
//     // function code
//     packet.push_back(m_functionCode);
// 
//     if (m_exceptionCode == PASim_EC_NoException)
//     {
//         //
//         // dysfunctional byte count
//         packet.push_back(0);
//         //
//         // table ("starting") address
// //        networkShort = htons(m_tableAddress);
// //        pktShrtPtr = (unsigned char *)((void *)(&networkShort));
// //        packet.push_back(*pktShrtPtr);
// //        packet.push_back(*(pktShrtPtr+1));
// 
//         //
//         // Data
//         //
//         // If the table data is empty, there isn't really any harm in iterating
//         // over the non-existent data, however it might mean we're supposed to
//         // push the exception code as the data instead.
//         if (! m_tableData.empty())
//         {
//             for ( ByteVector::iterator iter = m_tableData.begin() ;
//                   iter != m_tableData.end() ;
//                   iter++
//                 )
//             {
//                 packet.push_back(*iter);
//             }
//         }
//     }
//     else // if (m_exceptionCode != PASim_EC_NoException)
//     {
//         packet.push_back(m_exceptionCode);
//     }
// 
//     //
//     // Footer
//     //
//     // crc
//     networkShort=htons(m_crc);
//     pktShrtPtr = (unsigned char *)((void *)(&networkShort));
//     packet.push_back(*pktShrtPtr);
//     packet.push_back(*(pktShrtPtr+1));
// }
// 
// 
// ModbusWriteResponse::ModbusWriteResponse()
// :ModbusResponse(PASim_FC_Write)
// {
// }
// 
// //
// //  Modified Write Response Packet Format
// // 
// //     BYTE  | SIZE  |  DESCRIPTION           | DATA
// //  ---------+-------+------------------------+------------------------
// //      1    |   1   |  Function Code         | 0x04
// //  ---------+-------+------------------------+------------------------
// //     2-3   |   2   |  Starting Address      | 0x0064
// //           |       |  (a.k.a. Table Number) |
// //  ---------+-------+------------------------+------------------------
// //      4    |   1   |  Response Value        | 0 if good
// //  ---------+-------+------------------------+------------------------
// //  
// void ModbusWriteResponse::toNetwork(std::vector<unsigned char> & packet)
// {
//     //
//     // Header
//     //
//     // dysfunctional address
//     packet.push_back(0);
//     //
//     // function code
//     packet.push_back(m_functionCode);
// 
//     if (m_exceptionCode == PASim_EC_NoException)
//     {
//         //
//         // table ("starting") address
//         unsigned short networkShort = htons(m_tableAddress);
//         unsigned char * pktShrtPtr = (unsigned char *)((void *)(&networkShort));
//         packet.push_back(*pktShrtPtr);
//         packet.push_back(*(pktShrtPtr+1));
// 
//         //
//         // table size ("number of registers written")
//         networkShort = htons(m_tableSize/2); // number of registers is half the table size
//         pktShrtPtr = (unsigned char *)((void *)(&networkShort));
//         packet.push_back(*pktShrtPtr);
//         packet.push_back(*(pktShrtPtr+1));
//     }
//     else // if (m_exceptionCode != PASim_EC_NoException)
//     {
//         packet.push_back(m_exceptionCode);
//     }
// 
//     //
//     // Footer
//     //
//     // crc
//     unsigned short networkShort=htons(m_crc);
//     unsigned char * pktShrtPtr = (unsigned char *)((void *)(&networkShort));
//     packet.push_back(*pktShrtPtr);
//     packet.push_back(*(pktShrtPtr+1));
// }
ModbusFrame::ModbusFrame(Byte functionCode)
: m_functionCode(functionCode)
, m_transactionIdentifier(0)
, m_protocolIdentifier(0)
, m_length(0)
, m_unitIdentifier(0)
, m_exceptionCode(0)
, m_socket(0)
{
}

ModbusFrame::~ModbusFrame()
{
}

ModbusQuery::ModbusQuery(Byte functionCode)
:ModbusFrame(functionCode)
{
}

ModbusReadQuery::ModbusReadQuery()
:ModbusQuery(PASim_FC_Read)
{
}

union TheseTwoBytes
{
    unsigned char two_uchars[2];
    unsigned short one_ushort;
};

//
//  Modbus via TCP/IP Read Query Packet Format
//
//     BYTE  | SIZE  |  DESCRIPTION           | DATA
//  ---------+-------+------------------------+------------------ -
//     1-2   |   2   |  Transaction Identifier| 0x0015            |
//  ---------+-------+------------------------+------------------ |
//     3-4   |   2   |  Protocol Identifier   | 0x0000            |
//  ---------+-------+------------------------+------------------Header
//     5-6   |   2   | Number of the following|                   | 
//           |       |  bytes                 |                   |
//  ---------+-------+------------------------+------------------ |
//      7    |   1   |  Unit Identifier       | 0xFF              |
//  ---------+-------+------------------------+------------------ -
//      8    |   1   |  Function code         | 0x04
//  ---------+-------+------------------------+------------------
//     9-10  |   2   |  Start address         | 0x0009
//  ---------+-------+------------------------+------------------
//     11-12 |   2   |  Quantity of Input Reg | 0x0001
  
void ModbusReadQuery::fromNetwork(std::vector<unsigned char>::iterator & iter)
{
    // UNUSED variables
    // Byte deviceAddress= iter[0];
    // Byte functionCode = iter[1];

    // 
    // NOTE
    // On Solaris, the following code snippet causes a core dump on the
    // second line:
    // 
    //     unsigned short * networkShortP = (unsigned short *)(&(iter[1]));
    //     unsigned short networkShort = *networkShortP;
    //
    // as does replacing the first line with the following.
    //
    //     unsigned short * networkShortP = (unsigned short *)((void *)((&(*iter))+1));
    //
    // There does not appear to be any good reason for such.  Even gdb is able
    // to "print *networkShortP" correctly in both cases, and dumping memory
    // with "x/2b networkShortP" is also good.
    //
    // Our fix is to use a union hack, which ought to do the same thing, just
    // one byte at a time.
    
    // Process header
    TheseTwoBytes r_two_bytes;
    r_two_bytes.two_uchars[0] = iter[0];
    r_two_bytes.two_uchars[1] = iter[1];

    unsigned short networkShort = r_two_bytes.one_ushort; 
    m_transactionIdentifier = ntohs(networkShort);

    r_two_bytes.two_uchars[0] = iter[2];
    r_two_bytes.two_uchars[1] = iter[3];
    networkShort = r_two_bytes.one_ushort; 
    m_protocolIdentifier = ntohs(networkShort);
    
    r_two_bytes.two_uchars[0] = iter[4];
    r_two_bytes.two_uchars[1] = iter[5];
    networkShort = r_two_bytes.one_ushort;
    m_length = ntohs(networkShort);

    m_unitIdentifier = iter[6];

    // Process data
    r_two_bytes.two_uchars[0] = iter[8];
    r_two_bytes.two_uchars[1] = iter[9];
    networkShort = r_two_bytes.one_ushort;
    m_startAddress = ntohs(networkShort);
    
    r_two_bytes.two_uchars[0] = iter[10];
    r_two_bytes.two_uchars[1] = iter[11];
    networkShort = r_two_bytes.one_ushort;
    m_registersQuantity = ntohs(networkShort);

    iter += (getHeaderSize() + 5);
}

int ModbusReadQuery::getHeaderSize() const
{
    return 7;
}

int ModbusWriteQuery::getHeaderSize() const
{
    return 7;
}

ModbusWriteQuery::ModbusWriteQuery()
:ModbusQuery(PASim_FC_Write)
{
}

//
//  Modbus via TCP/IP Write Query Packet Format
//
//     BYTE  | SIZE  |  DESCRIPTION           | DATA
//  ---------+-------+------------------------+------------------ -
//     1-2   |   2   |  Transaction Identifier| 0x0015            |
//  ---------+-------+------------------------+------------------ |
//     3-4   |   2   |  Protocol Identifier   | 0x0000            |
//  ---------+-------+------------------------+------------------Header
//     5-6   |   2   | Number of the following|                   | 
//           |       |  bytes                 |                   |
//  ---------+-------+------------------------+------------------ |
//      7    |   1   |  Unit Identifier       | 0xFF              |
//  ---------+-------+------------------------+------------------ -
//      8    |   1   |  Function code         | 0x10
//  ---------+-------+------------------------+------------------
//     9-10  |   2   |  Start address         | 0x0009
//  ---------+-------+------------------------+------------------
//     11-12 |   2   |  Quantity of Input Reg | 0x0001
//  ---------+-------+------------------------+------------------
//      13   |   1   |  Byte Count            | 0x04
//  ---------+-------+------------------------+------------------
//     14-.. |ByteCnt|  Register Values       | 00 0A 01 02

void ModbusWriteQuery::fromNetwork(std::vector<unsigned char>::iterator & iter)
{
    // UNUSED Byte functionCode = *iter;

    //
    // Header
    //
    // See the NOTE in ModbusReadQuery::fromNetwork for why the roundabout
    // approach is required for accessing stuff from the iterator.

    // Process header
    TheseTwoBytes r_two_bytes;
    r_two_bytes.two_uchars[0] = iter[0];
    r_two_bytes.two_uchars[1] = iter[1];
    
    unsigned short networkShort = r_two_bytes.one_ushort; 
    m_transactionIdentifier = ntohs(networkShort);
    
    r_two_bytes.two_uchars[0] = iter[2];
    r_two_bytes.two_uchars[1] = iter[3];
    networkShort = r_two_bytes.one_ushort; 
    m_protocolIdentifier = ntohs(networkShort);
    
    r_two_bytes.two_uchars[0] = iter[4];
    r_two_bytes.two_uchars[1] = iter[5];
    networkShort = r_two_bytes.one_ushort;
    m_length = ntohs(networkShort);
    
    m_unitIdentifier = iter[6];

    // UNUSED Byte byteCount = iter[6];
    
    iter += getHeaderSize();
    iter += 1; // Skip function code
    //
    // Data
    //
    // Must ensure just enough storage in the table.
    // Really need to use resize() rather than reserve(), as std::copy doesn't
    // increase the size(), just copies
    // Process data
    r_two_bytes.two_uchars[0] = iter[0];
    r_two_bytes.two_uchars[1] = iter[1];
    networkShort = r_two_bytes.one_ushort;
    m_startAddress = ntohs(networkShort);
    iter += 2;

    r_two_bytes.two_uchars[0] = iter[0];
    r_two_bytes.two_uchars[1] = iter[1];
    networkShort = r_two_bytes.one_ushort;
    m_registersQuantity = ntohs(networkShort);
    iter += 2;

/*    m_byteCount = iter[0];*/
    m_byteCount = m_registersQuantity * 2;
    iter += 1;

    m_registersValue.resize(m_byteCount);
    std::copy(iter,iter+m_byteCount,m_registersValue.begin());

    iter += m_byteCount;

}

// int ModbusWriteQuery::getHeaderSize() const
// {
//     return 7;
// }


ModbusResponse::ModbusResponse(Byte functionCode)
:ModbusFrame(functionCode)
{
}

ModbusReadResponse::ModbusReadResponse()
:ModbusResponse(PASim_FC_Read)
{
}

//
//  Modbus via TCP/IP read Query reponse Packet Format
//
//     BYTE  | SIZE  |  DESCRIPTION           | DATA
//  ---------+-------+------------------------+------------------ -
//     1-2   |   2   |  Transaction Identifier| 0x0015            |
//  ---------+-------+------------------------+------------------ |
//     3-4   |   2   |  Protocol Identifier   | 0x0000            |
//  ---------+-------+------------------------+------------------Header
//     5-6   |   2   | Number of the following|                   | 
//           |       |  bytes                 |                   |
//  ---------+-------+------------------------+------------------ |
//      7    |   1   |  Unit Identifier       | 0xFF              |
//  ---------+-------+------------------------+------------------ -
//      8    |   1   |  Function code         | 0x04
//  ---------+-------+------------------------+------------------
//      9    |   1   |  Byte Count            | 0x04
//  ---------+-------+------------------------+------------------
//     10-.. |ByteCnt|  Register Values       | 00 0A 01 02

void ModbusReadResponse::toNetwork(std::vector<unsigned char> & packet)
{
    unsigned char * pktShrtPtr = 0;
    unsigned short networkShort = 0;
    //
    // Fill Header
    //
    // Transaction Identifier
    networkShort=htons(m_transactionIdentifier);
    pktShrtPtr = (unsigned char *)((void *)(&networkShort));
    packet.push_back(*pktShrtPtr);
    packet.push_back(*(pktShrtPtr+1));
    //
    // Protocol Identifier
    packet.push_back(0);
    packet.push_back(0);

    // number of the following bytes
    networkShort=htons(m_length);
    pktShrtPtr = (unsigned char *)((void *)(&networkShort));
    packet.push_back(*pktShrtPtr);
    packet.push_back(*(pktShrtPtr+1)); 

    // Unit Identifier
    packet.push_back(m_unitIdentifier);

    packet.push_back(m_functionCode);
    
    packet.push_back(m_byteCount);

    if (! m_registersValue.empty())
    {
        for ( ByteVector::iterator iter = m_registersValue.begin() ;
        iter != m_registersValue.end() ;
        iter++
            )
        {
            packet.push_back(*iter);
        }
     }
//     if (m_exceptionCode == PASim_EC_NoException)
//     {
//         //
//         // dysfunctional byte count
//         packet.push_back(0);
//         //
//         // table ("starting") address
// //        networkShort = htons(m_tableAddress);
// //        pktShrtPtr = (unsigned char *)((void *)(&networkShort));
// //        packet.push_back(*pktShrtPtr);
// //        packet.push_back(*(pktShrtPtr+1));
// 
//         //
//         // Data
//         //
//         // If the table data is empty, there isn't really any harm in iterating
//         // over the non-existent data, however it might mean we're supposed to
//         // push the exception code as the data instead.
//         if (! m_tableData.empty())
//         {
//             for ( ByteVector::iterator iter = m_tableData.begin() ;
//                   iter != m_tableData.end() ;
//                   iter++
//                 )
//             {
//                 packet.push_back(*iter);
//             }
//         }
//     }
//     else // if (m_exceptionCode != PASim_EC_NoException)
//     {
//         packet.push_back(m_exceptionCode);
//     }
}


ModbusWriteResponse::ModbusWriteResponse()
:ModbusResponse(PASim_FC_Write)
{
}

//
//  Modbus via TCP/IP write reponse Packet Format
//
//     BYTE  | SIZE  |  DESCRIPTION           | DATA
//  ---------+-------+------------------------+------------------ -
//     1-2   |   2   |  Transaction Identifier| 0x0015            |
//  ---------+-------+------------------------+------------------ |
//     3-4   |   2   |  Protocol Identifier   | 0x0000            |
//  ---------+-------+------------------------+------------------Header
//     5-6   |   2   | Number of the following|                   | 
//           |       |  bytes                 |                   |
//  ---------+-------+------------------------+------------------ |
//      7    |   1   |  Unit Identifier       | 0xFF              |
//  ---------+-------+------------------------+------------------ -
//      8    |   1   |  Function code         | 0x10
//  ---------+-------+------------------------+------------------
//     9-10  |   2   |  Start Address         | 0x0012
//  ---------+-------+------------------------+------------------
//    11-12  |   2   |  quantity of register  | 0x0003

void ModbusWriteResponse::toNetwork(std::vector<unsigned char> & packet)
{
    unsigned char * pktShrtPtr = 0;
    unsigned short networkShort = 0;
    //
    // Fill Header
    //
    // Transaction Identifier
    networkShort=htons(m_transactionIdentifier);
    pktShrtPtr = (unsigned char *)((void *)(&networkShort));
    packet.push_back(*pktShrtPtr);
    packet.push_back(*(pktShrtPtr+1));
    //
    // Protocol Identifier
    packet.push_back(0);
    packet.push_back(0);
    
    // number of the following bytes
    networkShort=htons(m_length);
    pktShrtPtr = (unsigned char *)((void *)(&networkShort));
    packet.push_back(*pktShrtPtr);
    packet.push_back(*(pktShrtPtr+1)); 
    
    // Unit Identifier
    packet.push_back(m_unitIdentifier); 
    
    packet.push_back(m_functionCode);
    

    networkShort=htons(m_startAddress);
    pktShrtPtr = (unsigned char *)((void *)(&networkShort));
    packet.push_back(*pktShrtPtr);
    packet.push_back(*(pktShrtPtr+1)); 
    
    
    networkShort=htons(m_registersQuantity);
    pktShrtPtr = (unsigned char *)((void *)(&networkShort));
    packet.push_back(*pktShrtPtr);
    packet.push_back(*(pktShrtPtr+1)); 
//     if (m_exceptionCode == PASim_EC_NoException)
//     {
//         //
//         // table ("starting") address
//         unsigned short networkShort = htons(m_tableAddress);
//         unsigned char * pktShrtPtr = (unsigned char *)((void *)(&networkShort));
//         packet.push_back(*pktShrtPtr);
//         packet.push_back(*(pktShrtPtr+1));
// 
//         //
//         // table size ("number of registers written")
//         networkShort = htons(m_tableSize/2); // number of registers is half the table size
//         pktShrtPtr = (unsigned char *)((void *)(&networkShort));
//         packet.push_back(*pktShrtPtr);
//         packet.push_back(*(pktShrtPtr+1));
//     }
//     else // if (m_exceptionCode != PASim_EC_NoException)
//     {
//         packet.push_back(m_exceptionCode);
//     }
}

