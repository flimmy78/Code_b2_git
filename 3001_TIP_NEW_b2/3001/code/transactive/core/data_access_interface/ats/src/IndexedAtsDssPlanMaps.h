 /**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/3001_TIP_NEW/3001/transactive/core/data_access_interface/ats/src/IndexedAtsDssPlanMaps.h $
  * @author Nick Jardine
  * @version $Revision: #2 $
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by: $Author: haijun.li $
  * 
  * IndexedAtsDssPlanMaps is an indexed collection of AtsDssPlanMaps for easy lookup.
  */


#if !defined(IndexedAtsDssPlanMaps_6AAB77B6_9DD3_4b98_A7B1_665FDAC65A0A__INCLUDED_)
#define IndexedAtsDssPlanMaps_6AAB77B6_9DD3_4b98_A7B1_665FDAC65A0A__INCLUDED_

#include <map>

#include "core/data_access_interface/ats/src/IAtsDssPlanMap.h"

namespace TA_IRS_Core
{
    class IndexedAtsDssPlanMaps
    {

    public:

        /**
         * IndexedAtsDssPlanMaps (constructor)
         *
         * Constructs a new instance using a vector of IAtsDssPlanMap
         *
         */
        IndexedAtsDssPlanMaps(IAtsDssPlanMaps dssPlanMaps);

        virtual ~IndexedAtsDssPlanMaps();

		std::string getPlanPath(long dssEvent);

    private:

        // Assignment AtsDssPlanMap not used so it is made private
		IndexedAtsDssPlanMaps& operator=(const IndexedAtsDssPlanMaps &);
		
        // Copy constructor should not be used and has therefore been made private. If a copy
        // constructor is required care should be taken.
        IndexedAtsDssPlanMaps( const IndexedAtsDssPlanMaps& theIndexedAtsDssPlanMaps);  


		typedef std::map<unsigned long, IAtsDssPlanMap* > IndexedDssPlanMaps;
		typedef IndexedDssPlanMaps::iterator IndexedDssPlanMapsIt;
		
		IndexedDssPlanMaps		m_atsDssPlanMaps;
    };
} // closes TA_Core

#endif // !defined(AtsDssPlanMap_6AAB77B6_9DD3_4b98_A7B1_665FDAC65A0A__INCLUDED_)
