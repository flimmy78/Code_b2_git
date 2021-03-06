/*
 * The source code in this file is the property of
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source : $File: //depot/PRIV_3001/3001/transactive/app/pa/PAAgent/src/IPasDataProcessor.h $
 * @author  J. Dalin
 * @version $Revision: #1 $
 * Last modification : $DateTime: 2018/03/14 13:51:20 $
 * Last modified by : $Author: lim.cy $
 *
 * 
 */

#ifndef IPASDATAPROCESSOR_H
#define IPASDATAPROCESSOR_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace TA_Base_Bus
{
    template<class DataType> class DataBlock;
}

namespace TA_IRS_App
{

class IPasDataProcessor
{
public:
    virtual void processData( const TA_Base_Bus::DataBlock<unsigned short>& dbData ) = 0;
    virtual void getDataFailed( int nReason ) = 0;
};

class IPasSerialDataProcessor
{
public:
    // Return value indicate whether need to continue: true - continue, false - break
    virtual bool processNewData( const TA_Base_Bus::DataBlock<unsigned short>& dbData ) = 0;

    // Return value indicate whether need to continue: true - continue, false - break
    virtual bool processRemainData( const TA_Base_Bus::DataBlock<unsigned short>& dbData ) = 0;

    virtual void processFinalData( const TA_Base_Bus::DataBlock<unsigned short>& dbData ) = 0;

    virtual void serialProcessFailed( int nReason ) = 0;
};

} // namespace TA_IRS_App

#endif // IPASDATAPROCESSOR_H
