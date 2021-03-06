/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/configuration_updates/src/ConfigUpdateDetails.cpp $
  * @author:  Karen Graham
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * This class holds all the details of a configuration update ready for processing.
  */

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif // defined (_MSC_VER)

#include "core/configuration_updates/src/ConfigUpdateDetails.h"

namespace TA_Base_Core
{
    ConfigUpdateDetails::ConfigUpdateDetails(const TA_Base_Core::ConfigUpdateMessageCorbaDef& updateDetails, const EObjectType type) :
        m_modification(updateDetails.modificationType),
        m_key(updateDetails.assocEntityKey),
        m_type(type)
    {

        unsigned int size = updateDetails.changes.length();
        for (unsigned int i = 0; i < size; ++i)
        {
            std::string element( updateDetails.changes[i] );
            m_changedParams.push_back( element );
        }
    }
}
