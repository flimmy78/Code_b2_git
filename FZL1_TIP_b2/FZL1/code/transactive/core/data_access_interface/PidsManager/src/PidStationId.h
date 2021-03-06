 /**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/GZL6_TIP/3002/transactive/core/data_access_interface/PidsManager/src/PidStationId.h $
  * @author Nick Jardine
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2012/06/12 13:35:44 $
  * Last modified by: $Author: builder $
  * 
  * PidStationId is an implementation of IPidStationId. It holds the data specific to an PidStationId entry
  * in the database, and allows read-only access to that data.
  */


#if !defined(PidStationId_6AAB77B6_9DD3_4b98_A7B1_665FDAC65A0A__INCLUDED_)
#define PidStationId_6AAB77B6_9DD3_4b98_A7B1_665FDAC65A0A__INCLUDED_

#include <string>

#include "core/data_access_interface/PidsManager/src/PidStationIdHelper.h"
#include "core/data_access_interface/PidsManager/src/IPidStationId.h"

namespace TA_IRS_Core
{
    class PidStationId : public IPidStationId
    {

    public:

        /**
         * PidStationId (constructor)
         *
         * Construct an PidStationId class based around a key.
         *
         * @param key The key of this PidStationId in the database
         */
        PidStationId(const unsigned long idKey);

        /**
         * PidStationId (constructor)
         *
         * Constructs a new instance using the information provided in TA_Base_Core::IData interface
         *
         * @see PidStationIdHelper::PidStationIdHelper(TA_Base_Core::IData*)
         *
         */
        PidStationId(unsigned long row, TA_Base_Core::IData& data);

        virtual ~PidStationId();

        /**
         * getKey
         *
         * Returns the key for this item.
         *
         * @return The key for this item as an unsigned long.
         */
        virtual unsigned long getKey();

        /**
         * getName
         *
         * Returns the name of this item. If this is the first time data for this item
         * has been requested, all the data is loaded from the database.
         *
         * @return The name for this item as a std::string
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception TA_Base_Core::DataException A TA_Base_Core::DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. ACCESSLEVEL should be an 
         *            unsigned long), or if the wrong ammount of data is retrieved.
         */
        virtual std::string getName();


		virtual unsigned long getStationId();
        virtual unsigned long getTaLocation();
 
        virtual void invalidate();
		
    private:

        // Assignment PidStationId not used so it is made private
		PidStationId& operator=(const PidStationId &);
		
        // Copy constructor should not be used and has therefore been made private. If a copy
        // constructor is required care should be taken. The copy constructor fo the PidStationIdHelper
        // has only been written for ConfigLocation objects and will not copy the PidStationId helper
        // for a read-only object (ie this one).
        PidStationId( const PidStationId& thePidStationId);  


        TA_IRS_Core::PidStationIdHelper * m_PidStationIdHelper;
    };
} // closes TA_IRS_Core

#endif // !defined(PidStationId_6AAB77B6_9DD3_4b98_A7B1_665FDAC65A0A__INCLUDED_)
