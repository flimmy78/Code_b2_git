#if !defined (TA_3002_App_Bas_BasManager_FireRecoverEquipment_H)
#define TA_3002_App_Bas_BasManager_FireRecoverEquipment_H
#pragma once

#include "boost/shared_ptr.hpp"
#include "core/timers/src/TimedWaitSemaphore.h"
#include "bus/scada/proxy_library/src/IEntityUpdateEventProcessor.h"
#include "bus/scada/proxy_library/src/ScadaProxyFactory.h"
#include "bus/scada/proxy_library/src/DataPointProxySmartPtr.h"
#include "bus/scada/proxy_library/src/DataNodeProxySmartPtr.h"
#include "bus/scada/proxy_library/src/IDataPointProxy.h"
#include "app/bas/BASModeManager/src/CommonDef.h"
#include "app/bas/BASModeManager/src/BasManagerSubscriber.h"


Namespace_TA_IRS_APP_Begin
class FireRecoverEquipment : public TA_Base_Bus::IEntityUpdateEventProcessor
{
public:
	friend class BasManagerSubscriber;
	~FireRecoverEquipment(void);

public:
	void processEntityUpdateEvent(unsigned long entityKey, TA_Base_Bus::ScadaEntityUpdateType updateType);

	void setFireRecoverFlag();

protected:
	FireRecoverEquipment(const std::string& strDatapointName);
	void initializeEquipment();
    void uninitEquipment();

private:
	TA_Base_Bus::DataPointProxySmartPtr m_dpFireRecover;
    TA_Base_Core::TimedWaitSemaphore m_semInitDone;
    bool m_bInitDone;
	std::string m_strEquipmentName;
};

Namespace_TA_IRS_APP_End
#endif //TA_3002_App_Bas_BasManager_FireRecoverEquipment_H