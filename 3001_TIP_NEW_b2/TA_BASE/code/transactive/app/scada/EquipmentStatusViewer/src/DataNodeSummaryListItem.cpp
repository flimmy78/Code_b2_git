/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/scada/EquipmentStatusViewer/src/DataNodeSummaryListItem.cpp $
  * @author:  Alan Brims
  * @version: $Revision: #5 $
  *
  * Last modification: $DateTime: 2012/12/10 15:43:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * A specialised DataNode Summary item to be displayed in (or filtered from) the EquipmentStatusListCtrl.
  * This class inherits from the DataNodeListItem and extends that class by extracting summary info
  * for the datanode, and then discards the required datanode proxy once it has loaded so that it 
  * unsubscribes from update messages.
  *
  */

#include "stdafx.h"
#include "core/data_access_interface/entity_access/src/EntityAccessFactory.h"
#include "core/data_access_interface/src/IOperator.h"
#include "core/data_access_interface/src/OperatorAccessFactory.h"
#include "core/data_access_interface/src/ISession.h"
#include "core/data_access_interface/src/SessionAccessFactory.h"
#include "core/data_access_interface/src/ProfileAccessFactory.h"
#include "core/data_access_interface/src/IProfile.h"
#include "core/exceptions/src/ScadaProxyException.h"
#include "core/utilities/src/TAAssert.h"
#include "core/exceptions/src/DataException.h"
#include "equipmentstatusviewer.h"
#include "DataNodeSummaryListItem.h"
#include "bus/scada/proxy_library/src/IDataPointProxy.h"
#include "bus/scada/proxy_library/src/IDataNodeProxy.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


namespace TA_Base_App
{

    //////////////////////////////////////////////////////////////////////
    // Construction/Destruction
    //////////////////////////////////////////////////////////////////////


    DataNodeSummaryListItem::DataNodeSummaryListItem(unsigned long entitykey, TA_Base_Bus::ScadaProxyFactory& proxyFactory, 
													HWND hwndToNotify)
        : DataNodeListItem(entitykey, proxyFactory, hwndToNotify)
    {
    }

    DataNodeSummaryListItem::DataNodeSummaryListItem(boost::shared_ptr<TA_Base_Core::DataNodeEntityData> entityData, 
													TA_Base_Bus::ScadaProxyFactory& proxyFactory,
													HWND hwndToNotify)
        : DataNodeListItem(entityData, proxyFactory, hwndToNotify)
    {
    }

    DataNodeSummaryListItem::~DataNodeSummaryListItem()
    {
    }


    CString DataNodeSummaryListItem::buildNewColumnText( TA_Base_App::EslColumns column )
    {
        //  Get the new text for the requested column. By calling this function 
        //  for each column we need only one try-catch(ScadaProxyException) block.
        CString newText("");
        try
        {
            //  Requested column probably uses a field shared between DataNodes and DataPoints
            newText = DataNodeListItem::buildNewColumnText( column);
        }
        catch (TA_Base_Core::ScadaProxyException& )
        {
            //  The proxy data for this column is not ready yet
        }
        return newText;
    }


    void DataNodeSummaryListItem::processEntityUpdateEvent(unsigned long entityKey, TA_Base_Bus::ScadaEntityUpdateType updateType)
    {
        DataNodeListItem::processEntityUpdateEvent( entityKey, updateType);
    }

} // TA_Base_App
