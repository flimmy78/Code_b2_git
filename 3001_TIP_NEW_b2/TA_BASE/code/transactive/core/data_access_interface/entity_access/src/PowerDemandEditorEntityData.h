/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/entity_access/src/PowerDemandEditorEntityData.h $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
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


