#ifndef CACHED_DATA_H
#define CACHED_DATA_H
/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/history/data_recording/src/CachedData.h $
 * @author:  Jade Welton
 * @version: $Revision: #2 $
 *
 * Last modification: $DateTime: 2012/02/06 16:15:14 $
 * Last modified by:  $Author: haijun.li $
 * 
 * Holds the most current data for one specific Item. 
 *
 */

#include <vector>

#include "bus/history/data_recording/src/IDataSink.h"

namespace TA_Base_Bus
{
    class Datum;

    struct CachedData
    {
        unsigned long           m_id;               // Unique identifier for the Item
        time_t                  m_timestamp;        // Source time for the data
        std::vector<Datum>      m_data;             // The data
        int                     m_quality;          // Quality of data (type specific)

        CachedData( unsigned long id, time_t timestamp, const std::vector<Datum>& data, int quality )
        : m_id( id ), m_timestamp( timestamp ), m_data( data ), m_quality( quality )
        {
            // Nothing else
        }
    };
}

#endif // CACHED_DATA_H
