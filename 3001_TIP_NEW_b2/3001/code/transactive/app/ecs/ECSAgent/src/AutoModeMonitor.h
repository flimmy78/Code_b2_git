/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/ecs/ECSAgent/src/AutoModeMonitor.h $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  */
///////////////////////////////////////////////////////////
//
//  AutoModeMonitor.h
//  Implementation of the Class AutoModeMonitor
//  Generated by Enterprise Architect
//  Created on:      25-Sep-2003 18:53:34
//  Original author: 
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////


#if !defined(AutoModeMonitor__INCLUDED_)
#define AutoModeMonitor__INCLUDED_

#include "bus/scada/proxy_library/src/IEntityUpdateEventProcessor.h"
#include "bus/scada/proxy_library/src/DataPointProxySmartPtr.h"
#include "app/ecs/ECSAgent/src/ItaEcsCachedConfig.h"
#include "app/ecs/ECSAgent/src/AbstractFailoverable.h"

class ItaEcsDatapoints;


class AutoModeMonitor: public virtual ItaEcsCachedConfigObserver,
                          public TA_Base_Bus::IEntityUpdateEventProcessor,
                          public virtual AbstractFailoverable
{

public:
    AutoModeMonitor(ItaEcsCachedConfig& theConfig, ItaEcsDatapoints& theDatapoints);
    virtual ~AutoModeMonitor();

protected:

    virtual void processItaEcsCachedConfigUpdate(ItaEcsCachedConfig::EItaEcsCachedConfigItemKey key);
    virtual void processEntityUpdateEvent(unsigned long entityKey, TA_Base_Bus::ScadaEntityUpdateType updateType);

    TA_Base_Core::ReEntrantThreadLockable    m_autoModeProxyLock;
    TA_Base_Bus::DataPointProxySmartPtr         m_autoModeProxy;
    ItaEcsCachedConfig&                         m_theConfig;
	ItaEcsDatapoints&							m_theDatapoints;

private:
    AutoModeMonitor( const AutoModeMonitor& theAutoModeMonitor);

};

#endif // !defined(AutoModeMonitor__INCLUDED_)
