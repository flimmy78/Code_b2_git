/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/4669_T01271350/TA_BASE/transactive/core/data_access_interface/archive_manager_dai/src/ArchiveOnline.cpp $
  * @author Katherine Thomson
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * ArchiveOnline is an implementation of IArchiveOnline. It holds the data specific to a 
  * ArchiveOnline entry in the database, and allows read-only access to that data.
  */

#include "core/data_access_interface/archive_manager_dai/src/ArchiveOnline.h"

namespace TA_Base_Core
{
    //
    // ArchiveOnline
    //
    ArchiveOnline::ArchiveOnline( unsigned long key )
        : m_archiveOnlineHelper( key )
    {
        // Do nothing.
    }


    //
    // getKey
    //
    unsigned long ArchiveOnline::getKey()
    {
        return m_archiveOnlineHelper.getKey();
    }


    //
    // getOnlinePeriodInDays
    //
    unsigned short ArchiveOnline::getOnlinePeriodInDays()
    {
        return m_archiveOnlineHelper.getOnlinePeriodInDays();
    }


    //
    // getDataExpiryInDays
    //
    unsigned short ArchiveOnline::getDataExpiryInDays()
    {
        return m_archiveOnlineHelper.getDataExpiryInDays();
    }


    //
    // invalidate
    //
    void ArchiveOnline::invalidate()
    {
        m_archiveOnlineHelper.invalidate();
    }

} // closes TA_Base_Core
