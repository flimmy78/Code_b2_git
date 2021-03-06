/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/core/data_access_interface/entity_access/src/PowerDemandEditorEntityData.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * <description>
  *
  */
// InspectorPanelEntityData.h: interface for the InspectorPanelEntityData class.
//
//////////////////////////////////////////////////////////////////////

#include "core/data_access_interface/entity_access/src/EntityData.h"

namespace TA_Base_Core
{

	class PowerDemandEditorEntityData : public EntityData 
	{
	public:
		PowerDemandEditorEntityData();
		PowerDemandEditorEntityData( unsigned long key );
		virtual ~PowerDemandEditorEntityData();

		virtual void invalidate();
		virtual std::string getType();
		static std::string getStaticType();
		static IEntityData* clone(unsigned long key);

    private:
		          
        PowerDemandEditorEntityData( const PowerDemandEditorEntityData & obj );
		PowerDemandEditorEntityData & operator= ( const PowerDemandEditorEntityData &);

        // 
        // The entity type is fixed for all instances of this class.
        // 
        static const std::string ENTITY_TYPE;
	};
    
    typedef boost::shared_ptr<PowerDemandEditorEntityData> PowerDemandEditorEntityDataPtr;
}


