/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/scada/OpcBridgeService/src/OpcBridgeService.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  */
// OpcBridgeService.cpp : Defines the entry point for the console application.
//

#if defined(_MSC_VER)
#pragma warning(disable : 4786)
#endif // defined _MSC_VER

#include "bus/generic_service/src/ServiceMain.h"
#include "app/scada/OpcBridgeService/src/OpcBridgeService.h"
#include "app/scada/OpcBridgeLib/src/OpcBridge.h"

template<> TA_Base_Bus::ServiceMain<TA_Base_App::OpcBridge>* TA_Base_Bus::ServiceMain<TA_Base_App::OpcBridge>::m_singleton = NULL;
template<> TA_Base_Core::ReEntrantThreadLockable TA_Base_Bus::ServiceMain<TA_Base_App::OpcBridge>::m_singletonLock;

int main(int argc, char* argv[])
{
	TA_Base_Core::DebugUtil::getInstance().encryptPidInFilenames("TRUE");
	TA_Base_Bus::ServiceMain<TA_Base_App::OpcBridge>& opcBridgeService = TA_Base_Bus::ServiceMain<TA_Base_App::OpcBridge>::getInstance();
    
    opcBridgeService.initialise(OPC_BRIDGE_SERVICE_NAME, 0);
	opcBridgeService.run(argc, argv);

	TA_Base_Bus::ServiceMain<TA_Base_App::OpcBridge>::removeInstance();

	return 0;
}
	
