/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/configuration/config_plugins/pa_ats_triggered_broadcast/src/TA_PAAtsTriggeredBroadcastConfigPlugin.cpp $
  * @author:  Karen Graham
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  * 
  * This is the 'mainline' of the DLL. This is the entry point and is run when the 
  * main Configuration Editor application loads the DLL.
  */

#pragma warning(disable:4786 4284)

#include "StdAfx.h"

#include <afxdllx.h> // This header must come after StdAfx.h

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace TA_IRS_App
{
    static AFX_EXTENSION_MODULE TA_PaAtsTriggeredBroadcastConfigPluginDLL = { NULL, NULL };

    extern "C" int APIENTRY
    DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
    {
	    // Remove this if you use lpReserved
	    UNREFERENCED_PARAMETER(lpReserved);

	    if (dwReason == DLL_PROCESS_ATTACH)
	    {
		    TRACE0("TA_PAATSTRIGGEREDBROADCASTCONFIGPLUGIN.DLL Initializing!\n");
		    
		    // Extension DLL one-time initialization
		    if (!AfxInitExtensionModule(TA_PaAtsTriggeredBroadcastConfigPluginDLL, hInstance))
			    return 0;

		    // Insert this DLL into the resource chain
		    // NOTE: If this Extension DLL is being implicitly linked to by
		    //  an MFC Regular DLL (such as an ActiveX Control)
		    //  instead of an MFC application, then you will want to
		    //  remove this line from DllMain and put it in a separate
		    //  function exported from this Extension DLL.  The Regular DLL
		    //  that uses this Extension DLL should then explicitly call that
		    //  function to initialize this Extension DLL.  Otherwise,
		    //  the CDynLinkLibrary object will not be attached to the
		    //  Regular DLL's resource chain, and serious problems will
		    //  result.

		    new CDynLinkLibrary(TA_PaAtsTriggeredBroadcastConfigPluginDLL);
	    }
	    else if (dwReason == DLL_PROCESS_DETACH)
	    {
		    TRACE0("TA_PAATSTRIGGEREDBROADCASTCONFIGPLUGIN.DLL Terminating!\n");
		    // Terminate the library before destructors are called
		    AfxTermExtensionModule(TA_PaAtsTriggeredBroadcastConfigPluginDLL);
	    }
	    return 1;   // ok
    }


    /**
      * createComponent
      *
      * Creates an IConfigurableComponent object and returns it to the caller. All further
      * communication between the DLL and main application will happen through this interface.
      *
      * @param const string& - This is the name of the component displaying in the selection bar so we
      *                        can use the same name in the DLL for sending audit messages etc.
      * @param const std::vector<std::string>& - The entity types to load. This parameter can be ignored for
      *                                          this particular module
      *
      * @return IConfigurableComponent*		A new PaAtsTriggeredBroadcastComponent object which implements
      *                                     the IConfigurableComponent interface.
      *                                     NOTE: The caller is responsible for deleting the pointer.
      */
    extern "C" __declspec(dllexport) TA_Base_App::IConfigurableComponent* createComponent(const std::string& componentName,
                                                                             const std::vector<std::string>& entityTypes)
    {
	    return new PaAtsTriggeredBroadcastComponent(componentName);
    }

}


