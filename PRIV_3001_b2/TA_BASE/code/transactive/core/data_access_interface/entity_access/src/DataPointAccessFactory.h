/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/core/data_access_interface/entity_access/src/DataPointAccessFactory.h $
  * @author:  HoaVu
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * DataPointAccessFactory is a singleton that is used to retrieve
  * DataPoint objects defined in database.
  *
  */

#if !defined(DataPointAccessFactory_774454B7_9ED6_4e4d_BB19_917B0DC71137__INCLUDED_)
#define DataPointAccessFactory_774454B7_9ED6_4e4d_BB19_917B0DC71137__INCLUDED_

#include <string>
#include <map>
#include <vector>

#include "core/synchronisation/src/ReEntrantThreadLockable.h"

namespace TA_Base_Core
{
	class DataPointEntityData;
	class IEntityData;
    class IData;

	struct DataPointEventDetails
	{
		std::string eventMessage;
		std::string assetName;
		unsigned long parentKey;
	};

	typedef std::map < unsigned long, DataPointEventDetails > PkeyEventDetailsMap;

	class DataPointAccessFactory
	{

	public:

        // TD18575, use agentName to build the map
        static void getAllDpEventDetails ( const std::string& agentName, PkeyEventDetailsMap & pkeyEventDetailsMap );

        static void getAllDataPointEntitiesWithNameLikeToken ( const std::string& token, std::vector< DataPointEntityData *> & dataPointEntitiesList );

        static void getAllDataPointEntitiesWithAddressLikeToken ( const std::string& token, std::vector< DataPointEntityData *> & dataPointEntitiesList );

	private:

		static void populateEventDetails ( IData * data,
                                         PkeyEventDetailsMap& pkeyEventDetailsMap,
                                         std::vector<std::string> columnNames );

		DataPointAccessFactory();
		DataPointAccessFactory(const DataPointAccessFactory & theDataPointAccessFactory);
		DataPointAccessFactory & operator=(const DataPointAccessFactory & rhs);
		virtual ~DataPointAccessFactory();
	};

} // closes TA_Base_Core

#endif // !defined(DataPointAccessFactory_774454B7_9ED6_4e4d_BB19_917B0DC71137__INCLUDED_)
