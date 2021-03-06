/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/PRIV_3001/3001/transactive/bus/pa/cachedmaps/src/ICachedMapFilter.h $
  * @author Jade Lee
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by: $Author: lim.cy $
  * 
  * Interface (helper) class to allow user defined filters to be applied
  * to cached maps record fetch requests 
  *
  * @see GenericCachedMap::getAllRecords
  *
  */

#if !defined(ICachedMapFilter_4EBD5CE7_C4D0_43BC_A835_518CA9141975__INCLUDED_)
#define ICachedMapFilter_4EBD5CE7_C4D0_43BC_A835_518CA9141975__INCLUDED_

namespace TA_IRS_Bus
{

    template <class DbRecordType>
    class ICachedMapFilter
    {
    public:
    
        virtual ~ICachedMapFilter() {}
    
        /**
         * isMatch
         *
         * @return true if the input record is a match for this filter
         *         (the filter accepts the record)
         *
         * @param record the record to test for a match
         *
         */
        virtual bool isMatch(const DbRecordType& record) const = 0;
    };

} // end namespace TA_IRS_Bus

#endif // ICachedMapFilter_4EBD5CE7_C4D0_43BC_A835_518CA9141975__INCLUDED_
