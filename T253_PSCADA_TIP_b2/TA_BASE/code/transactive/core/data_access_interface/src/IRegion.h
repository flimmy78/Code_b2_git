/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/core/data_access_interface/src/IRegion.h $
  * @author:  Gregg Kirkpatrick
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2017/10/31 16:21:54 $
  * Last modified by:  $Author: CM $
  * 
  * IRegion is an interface to a Region object. It allows the Region object implementation
  * to be chagned (e.g. if necessary due to a database schema change) without changing code
  * that uses it.
  *
  */

#if !defined(IREGION_H_INCLUDED)
#define IREGION_H_INCLUDED

#include <string>

#include "core/data_access_interface/src/IItem.h"

namespace TA_Base_Core
{

    class IRegion : public IItem
    {

    public:
        virtual ~IRegion() { };

        /**
         * getDescription
         *
         * Returns the description of this Region. If this is the first time data for this Region
         * has been requested, all the data is loaded from the database.
         *
         * @return The description for this region as a std::string
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception DataException A DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. ACCESSLEVEL should be an 
         *            unsigned long), or if the wrong ammount of data is retrieved.
         */
        virtual std::string getDescription() = 0;

		/**
         * getDisplayName
         *
         * Returns the display name of this Region. If this is the first time data for this Region
         * has been requested, all the data is loaded from the database.
         *
         * @return The display name for this region as a std::string
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception DataException A DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. ACCESSLEVEL should be an 
         *            unsigned long), or if the wrong ammount of data is retrieved.
         */
		virtual std::string getDisplayName() = 0;
    };
} //close namespace TA_Base_Core

#endif // !defined(IREGION_H_INCLUDED)
