/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/PRIV_3001/3001/transactive/core/data_access_interface/ats/src/IConfigAtsFbMapRecord.h $
  * @author Nick Jardine
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by: $Author: lim.cy $
  * 
  * IConfigAtsFbMapRecord - This is the interface supported by objects that allow configuration of
  * AtsFbMapRecords. It provides methods for retrieving, settings, and writing data for an AtsFbMapRecord object.
  * The set methods in this interface do not set the values in the database
  * straight away. They only set the values in the object after validating that
  * they are correct.
  */

#if !defined(IConfigAtsFbMapRecord_9E7AE6B0_D600_4de9_9290_A8480311C649__INCLUDED_)
#define IConfigAtsFbMapRecord_9E7AE6B0_D600_4de9_9290_A8480311C649__INCLUDED_

#include <string>

#include "core/data_access_interface/ats/src/IAtsFbMapRecord.h"
#include "core/data_access_interface/src/IConfigItem.h"

namespace TA_IRS_Core
{

    class IConfigAtsFbMapRecord : public virtual TA_Base_Core::IConfigItem, public virtual IAtsFbMapRecord
    {

    public:

        
        virtual ~IConfigAtsFbMapRecord() {};
        
        virtual void setBranchIdAsString(const std::string& id) =0;
        virtual void setMinAbscissa(unsigned long minAbscissa) =0;
		virtual void setMaxAbscissa(unsigned long maxAbscissa) =0;
		virtual void setZoneId(double zoneId) =0; 
		virtual void setZoneTypeName(std::string zoneTypeName) =0;
		virtual void setArmId(double armId) =0;
        
        /**
         * deleteThisObject
         *
         * Remove this AtsFbMapRecord from the database. Once this method has been executed, the
         * AtsFbMapRecordHelper object should be destroyed.
         *
         * @exception DatabaseException 
         *            - if there is a problem writing the data to the database.
         *            - if references to this record exists in AT_FIXED_BLOCK_MAP table.  
		 *				These can be removed by specifying the cascade option.
         *
         * @param cascade
         *        - force the removal of this record by removing all references to this record
         *          in other tables (AT_FIXED_BLOCK_MAP).  This should be set to true to prevent the 
         *          DatabaseException from being thrown.
         *
         * pre: - this AtsFbMapRecord was initially loaded from the database
         *      - writeAtsFbMapRecordData() has already been called
         */
        virtual void deleteThisObject(bool cascade=false) = 0;

    };
    
    typedef std::vector<IConfigAtsFbMapRecord*> IConfigAtsFbMapRecords;
    typedef IConfigAtsFbMapRecords::iterator    IConfigAtsFbMapRecordsIt;
} //close namespace TA_IRS_Core
#endif // !defined(IConfigAtsFbMapRecord_9E7AE6B0_D600_4de9_9290_A8480311C649__INCLUDED_)
