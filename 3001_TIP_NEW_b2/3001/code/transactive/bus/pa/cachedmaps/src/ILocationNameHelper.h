/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/3001_TIP_NEW/3001/transactive/bus/pa/cachedmaps/src/ILocationNameHelper.h $
  * @author Jade Lee
  * @version $Revision: #3 $
  * Last modification: $DateTime: 2012/03/26 10:45:17 $
  * Last modified by: $Author: qi.huang $
  * 
  * Simple interface function to allow retrieval of a location name from a key value
  *
  */

#ifndef ILOCATIONNAMEHELPER_INCLUDED
#define ILOCATIONNAMEHELPER_INCLUDED

namespace TA_IRS_Bus
{
    class ILocationNameHelper
    {
    public:
        /**
         * getLocationNameFromKey
         *
         * @return the name of the location identified by 'locationKey'
         *
         * @exception TransactiveException if the input key is invalid
         *
         */
        virtual std::string getLocationNameFromKey( unsigned long locationKey ) = 0;

        virtual unsigned long getLocationOrderIdFromKey( unsigned long ulLocationKey ) = 0;
    };
} // end namespace TA_IRS_Bus

#endif // ILOCATIONNAMEHELPER_INCLUDED