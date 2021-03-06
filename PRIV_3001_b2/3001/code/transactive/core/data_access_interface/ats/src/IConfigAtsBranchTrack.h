/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/PRIV_3001/3001/transactive/core/data_access_interface/ats/src/IConfigAtsBranchTrack.h $
  * @author Nick Jardine
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by: $Author: lim.cy $
  * 
  * IConfigAtsBranchTrack - This is the interface supported by objects that allow configuration of
  * AtsBranchTracks. It provides methods for retrieving, settings, and writing data for an AtsBranchTrack object.
  * The set methods in this interface do not set the values in the database
  * straight away. They only set the values in the object after validating that
  * they are correct.
  */

#if !defined(IConfigAtsBranchTrack_9E7AE6B0_D600_4de9_9290_A8480311C649__INCLUDED_)
#define IConfigAtsBranchTrack_9E7AE6B0_D600_4de9_9290_A8480311C649__INCLUDED_

#include <string>

#include "core/data_access_interface/ats/src/IAtsBranchTrack.h"
#include "core/data_access_interface/src/IConfigItem.h"

namespace TA_IRS_Core
{

    class IConfigAtsBranchTrack : public virtual TA_Base_Core::IConfigItem, public virtual IAtsBranchTrack
    {

    public:

        
        virtual ~IConfigAtsBranchTrack() {};

        virtual void setAtsBranchId(const std::string& id) =0;
        virtual void setTrack(const std::string& track) =0;        
        
        /**
         * deleteThisObject
         *
         * Remove this AtsBranchTrack from the database. Once this method has been executed, the
         * AtsBranchTrackHelper object should be destroyed.
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
         * pre: - this AtsBranchTrack was initially loaded from the database
         *      - writeAtsBranchTrackData() has already been called
         */
        virtual void deleteThisObject(bool cascade=false) = 0;

    };
    
    typedef std::vector<IConfigAtsBranchTrack*> IConfigAtsBranchTracks;
    typedef IConfigAtsBranchTracks::iterator    IConfigAtsBranchTracksIt;
} //close namespace TA_IRS_Core
#endif // !defined(IConfigAtsBranchTrack_9E7AE6B0_D600_4de9_9290_A8480311C649__INCLUDED_)
