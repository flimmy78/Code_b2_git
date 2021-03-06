/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/system_control/control_station/src/GraphWorxCommunicator.cpp $
  * @author:  Karen Graham
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *  
  * This class will communicate with GraphWorX. It will launch a GraphWorX instance and
  * continue to send it messages through its lifetime.
  * This is different to the GraphWorXApplication in that it ensures the GraphWorX instance
  * is always running and only hides it when the user logs out.
  */


#include "app\system_control\control_station\src\StdAfx.h"
#include "core\synchronisation\src\ThreadGuard.h"
#include "app\system_control\control_station\src\GraphWorxManager.h"
#include "app\system_control\control_station\src\GraphWorxCommunicator.h"
#include "app\system_control\control_station\src\gwx32.h"
#include "core\exceptions\src\GraphWorxException.h"
#include "core\utilities\src\DebugUtil.h"

#include "app\system_control\control_station\src\ControlStationConstants.h"
#include "app\system_control\control_station\src\ControlStationRootDialog.h"

#include <objbase.h>  // For CoInitializeEx
#include <tlhelp32.h> // For process control

using TA_Base_Core::DebugUtil;
using TA_Base_Core::TransactiveException;

GraphWorxCommunicator::GraphWorxCommunicator(IGraphWorxManager::GraphWorXInstance& instance, GraphWorxManager& manager) 
 : m_graphWorXWindow(instance),
   m_manager(manager),
   m_currentChildDisplay(""),
   m_isTerminating(false),
   m_shouldLaunchGraphWorx(false),
   m_shouldShutdownGraphWorx(false),
   m_isValidLoad(true),
   m_isShowing(false)
{
}


GraphWorxCommunicator::~GraphWorxCommunicator()
{
    FUNCTION_ENTRY("~GraphWorxCommunicator");
    try
    {
        CoUninitialize();
    }
    catch ( ... )
    {
        // Catch all exceptions so we don't get errors filtering out
        LOG( SourceInfo, DebugUtil::ExceptionCatch, "Unknown", "Caught in destructor of GraphWorxCommunicator");
    }
    FUNCTION_EXIT;
}


void GraphWorxCommunicator::run()
{
    LOG( SourceInfo, DebugUtil::FunctionEntry, "run");

    CoInitializeEx( NULL, COINIT_MULTITHREADED  );

    while (!isTerminating() && m_isValidLoad)
    {
        try
        {
            runGraphWorx();

            // Now just enter our standard processing loop. We will only exit this loop
            // if we are told to terminate OR if the GraphWorX instances goes (ie gets
            // closed or crashes).
            while ( !isTerminating() && m_isValidLoad)
            {
                //LOG_GENERIC(SourceInfo,DebugUtil::DebugDebug,"Going to check to see if the graphworx display is still alive");

                // Perform a harmless call on GraphWorx to see if it is still running
                // If it is not we will exit this loop and go back to the top. This will
                // result in GraphWorx being restarted.
                // Within this same call we get the current display that GraphWorx is showing.
                // This way if GraphWorx does terminate at some point we restart it with the
                // correct display.
                try
                {
                    if (m_graphWorXWindow.graphworx != NULL)
                    {
                        m_graphWorXWindow.display = m_graphWorXWindow.graphworx->GetFileName();
                    }
                }
                catch ( ... )
                {
                    LOG_GENERIC(SourceInfo,DebugUtil::DebugError,"Graphworx instance has just died.  Have to open a new one");
                    // Break out of the loop cos we need to start GraphWorx again.
                    break;
                }

                if (shouldLaunchGraphWorx())
                {
                    LOG_GENERIC(SourceInfo,DebugUtil::DebugInfo,"Going to show graphworx");
                    showGraphWorx();
                    setShouldLaunchGraphWorx(false);
                    m_manager.incrementNumberReady();
                }

                if (shouldShutdownGraphWorx())
                {
                    LOG_GENERIC(SourceInfo,DebugUtil::DebugInfo,"Going to hide graphworx");
                    hideGraphWorx();
                    setShouldShutdownGraphWorx(false);
                    m_manager.incrementNumberReady();
                }

                Sleep(1000);
            }
        }
        catch ( ... )
        {
            LOG(SourceInfo, DebugUtil::ExceptionCatch, "Unknown", "run() of GraphWorxCommunicator threw an unknown exception");
            // We will loop around now and restart it.
        }
    } //end while !isTerminating


    if (m_isValidLoad)
    {
        LOG_GENERIC(SourceInfo,DebugUtil::DebugInfo,"The load is not valid, going to terminate GraphWorX now");
        terminateGraphWorx();
    }

    LOG( SourceInfo, DebugUtil::FunctionExit, "run");
}


void GraphWorxCommunicator::terminate()
{
    setIsTerminating(true);
}


void GraphWorxCommunicator::runGraphWorx()
{
    LOG( SourceInfo, DebugUtil::FunctionEntry, "runGraphWorx");

    try
    {
        TA_Base_Core::ThreadGuard guard(m_loadingLock);

        // If the display is empty then there is no point continuing
        if (m_graphWorXWindow.display.empty() )
        {
            TA_THROW( TransactiveException("Startup display passed to be loaded is empty") );
        }

        // If the background display is not specified, then we'll just launch the startup
        // display as it is, otherwise, we have to open the background display first then
        // the startup display (fix for issue #1787).  By doing so the startup display will
        // be displayed with the windows properties set in the background display - so if
        // the background display is set with no title bar and no system menu, the startup
        // display will be also be opened with no title bar and no system menu even if the
        // gdf itself is set with both title bar and system menu.  When the startup display
        // is copied across, it will be displayed with its own properties - with title bar 
        // and system menu, so user will be able to close it.
        if (m_graphWorXWindow.background.empty() )
        {
            LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugInfo, "Background display is empty, so we're just going to display the startup display, %s", m_graphWorXWindow.display.c_str());
            loadBaseDisplay(m_graphWorXWindow.display);  
        }
        else
        {
            LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugInfo, "Background display is %s. Going to open it now", m_graphWorXWindow.background.c_str());
            loadBaseDisplay(m_graphWorXWindow.background);

            // We open up the startup display now
            if (m_graphWorXWindow.graphworx->IsRuntimeMode())
            {
                DisplayInformation* info = new struct DisplayInformation;

                if (info != NULL)
                {
                    info->display = CString(m_graphWorXWindow.display.c_str());
                    info->asset = "";
                    info->position = m_graphWorXWindow.left;
                    ControlStationRootDialog::getInstance().PostMessage(WM_LAUNCH_DISPLAY, (WPARAM)info);
                }
                else
                {
                    LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugWarn, "new returned a NULL for display info");
                }
            }
            else
            {
                // If the background display is somehow not running, then we'll have to just open up
                // the display as it is.
                LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugInfo, "Opening the startup display now", m_graphWorXWindow.display.c_str());
                if (!m_graphWorXWindow.graphworx->FileOpen(m_graphWorXWindow.display.c_str()))
                {
                    TA_THROW( TransactiveException("Failed to perform a FileOpen on the GraphWorX instance") );
                }
                LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugInfo, "Setting the dimension of display to left = %d, top = %d, width = %d, height = %d", m_graphWorXWindow.left,m_graphWorXWindow.top,m_graphWorXWindow.width,m_graphWorXWindow.height);
                m_graphWorXWindow.graphworx->SetWindowDimensionsPixels(m_graphWorXWindow.left,m_graphWorXWindow.top,m_graphWorXWindow.width,m_graphWorXWindow.height);
                m_graphWorXWindow.graphworx->StartRuntime();
            }
        }

        m_isValidLoad = true;
        LOG_GENERIC(SourceInfo,DebugUtil::DebugInfo,"Successfully started up graphworx");
    }
    catch ( TransactiveException& )
    {
        // Catch because we don't want this to propagate. It has served it's purpose as we have skipped all
        // functionality we didn't want to execute (after an error occurred). So now we can continue the thread.
        LOG( SourceInfo, DebugUtil::ExceptionCatch, "TransactiveException","GraphworX Load Failed");
        if ( m_graphWorXWindow.graphworx != NULL)
        {
            delete m_graphWorXWindow.graphworx;
            m_graphWorXWindow.graphworx = NULL;
        }

        m_isValidLoad = false;
    }
    catch ( ... )
    {
        LOG(SourceInfo, DebugUtil::ExceptionCatch, "Unknown", "Thrown while GraphWorX was attempting to start up.");
        if ( m_graphWorXWindow.graphworx != NULL)
        {
            delete m_graphWorXWindow.graphworx;
            m_graphWorXWindow.graphworx = NULL;
        }

        // it's a valid load, we're just having problem launching the graphworx display
        m_isValidLoad = false;
    }

    // Now check if GraphWorX is meant to be showing. If this is a relaunch because GraphWorX
    // was closed then we need to show or hide GraphWorx at the right time.
    if ( m_isShowing && m_isValidLoad )
    {
        // Ensure GraphWorx loads the latest login details.
        ControlStationRootDialog::getInstance().PostMessage(WM_LOGIN_DETAILS_CHANGED);

        // Now get it to display since we were showing before.
        showGraphWorx();
    }

    LOG( SourceInfo, DebugUtil::FunctionExit, "runGraphWorx");
}


void GraphWorxCommunicator::loadBaseDisplay(const std::string& baseDisplay)
{
    FUNCTION_ENTRY("loadBaseDisplay");

    // set the valid load to false first since we haven't successfully loaded it yet
    m_isValidLoad = false;

    m_graphWorXWindow.graphworx = new IGwx32;
    if (m_graphWorXWindow.graphworx == NULL)
    {
        TA_THROW( TransactiveException("new IGwx32 returned NULL. Cannot continue to load GraphWorx") );
    }

    COleException pError; 
    if (!m_graphWorXWindow.graphworx->CreateDispatch("Gwx32.Display",&pError) )
    {
        char msg[256];
        pError.GetErrorMessage(msg,256);
        std::string error = "CreateDispatch failed with error: ";
        error += msg;
        TA_THROW( TransactiveException(error) );
    }

    if ( !m_graphWorXWindow.graphworx->FileNew())
    {
        TA_THROW( TransactiveException("Failed to perform a FileNew on the GraphWorX instance") );
    }

    // We open up the hidden display first
    if (!m_graphWorXWindow.graphworx->FileOpen(baseDisplay.c_str()))
    {
        TA_THROW( TransactiveException("Failed to perform a FileOpen on the GraphWorX instance") );
    }

    try
    {
        LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugInfo, "Setting the dimension of display to left = %d, top = %d, width = %d, height = %d", m_graphWorXWindow.left,m_graphWorXWindow.top,m_graphWorXWindow.width,m_graphWorXWindow.height);
        m_graphWorXWindow.graphworx->SetWindowDimensionsPixels(m_graphWorXWindow.left,m_graphWorXWindow.top,m_graphWorXWindow.width,m_graphWorXWindow.height);
        m_graphWorXWindow.graphworx->StartRuntime();
    }
    catch(...)
    {
        TA_THROW( TransactiveException("Caught some exception when setting the dimension/starting the display") );
    }

    FUNCTION_EXIT
}

void GraphWorxCommunicator::printDisplay()
{
    FUNCTION_ENTRY("printDisplay");
    // To print the display, first need to get the correct part of the display...    
    unsigned long popupCount = m_graphWorXWindow.graphworx->GetOpenPopupCount();

    // Only useful if the graphworx instance is actually showing something (i.e. has more than one popup)
    if (popupCount > 0)
    {
        // Will always be interested only in the first popup
        IGwx32 displayToPrint = IGwx32(m_graphWorXWindow.graphworx->GetOpenPopupByIndex(0));

        // Set the background to white temporarily for the print
        unsigned long backgroundColor = displayToPrint.GetBackgroundColor();
        displayToPrint.SetBackgroundColor(RGB(255,255,255));
        

        // Tell the graphworx window to print
        LOG_GENERIC(SourceInfo,DebugUtil::DebugInfo,"Requesting print-preview dialog from GraphWorX");
        PostMessage((HWND)displayToPrint.GetFrameWindowHandle(),WM_COMMAND, /*57609*/ID_FILE_PRINT_PREVIEW, 0);

        // And finally reset the background color        
        displayToPrint.SetBackgroundColor(backgroundColor);
    }

    FUNCTION_EXIT;
}


void GraphWorxCommunicator::terminateGraphWorx()
{
    // Now shutdown GraphWorX properly as we have finished.
    try
    {
        hideGraphWorx();
        if (m_graphWorXWindow.graphworx != NULL)
        {
            m_graphWorXWindow.graphworx->StopRuntime();
            m_graphWorXWindow.graphworx->ExitApplication();
            delete m_graphWorXWindow.graphworx;
            m_graphWorXWindow.graphworx = NULL;
        }
    }
    catch ( ... )
    {
        LOG( SourceInfo, DebugUtil::ExceptionCatch, "Unknown", "Exception caught while trying to close GraphWorx");
        LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugError, "Could not terminate GraphWorx");
    }
}


void GraphWorxCommunicator::launchGraphWorx()
{
    LOG( SourceInfo, DebugUtil::FunctionEntry, "launchGraphWorx");

    if (!m_isValidLoad)
    {
        using TA_Base_Core::GraphWorxException;
        TA_THROW( GraphWorxException("GraphWorx is not running", GraphWorxException::NOT_RUN) );
    }

    setShouldLaunchGraphWorx(true);
    LOG( SourceInfo, DebugUtil::FunctionExit, "launchGraphWorx");
}


void GraphWorxCommunicator::shutdownGraphWorx()
{
    LOG( SourceInfo, DebugUtil::FunctionEntry, "shutdownGraphWorx");

    setShouldShutdownGraphWorx(true);

    LOG( SourceInfo, DebugUtil::FunctionExit, "shutdownGraphWorx");
}


void GraphWorxCommunicator::showGraphWorx()
{
    LOG( SourceInfo, DebugUtil::FunctionEntry, "showGraphWorx");

    TA_Base_Core::ThreadGuard guard(m_loadingLock);
    m_isShowing = true;

    try
    {
        if (m_graphWorXWindow.graphworx != NULL)
        {
            m_graphWorXWindow.graphworx->ShowWindow();
        }
    }
    catch ( ... )
    {
        LOG( SourceInfo, DebugUtil::ExceptionCatch, "Unknown", "Exception caught while trying to start GraphWorx runtime and show the window");
        LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugError, "Could not start GraphWorx runtime and display it");
    }

    LOG( SourceInfo, DebugUtil::FunctionExit, "showGraphWorx");
}


void GraphWorxCommunicator::hideGraphWorx()
{
    LOG( SourceInfo, DebugUtil::FunctionEntry, "hideGraphWorx");
    m_isShowing = false;

    try
    {
        if (m_graphWorXWindow.graphworx != NULL)
        {
            // just post this message to cancel the popup menu just in case it wasn't cancelled before.
            ::PostMessage(HWND_BROADCAST, WM_CANCELMODE, 0, 0);
            m_graphWorXWindow.graphworx->HideWindow();
        }
    }
    catch ( ... )
    {
        LOG( SourceInfo, DebugUtil::ExceptionCatch, "Unknown", "Exception caught while trying to stop GraphWorx runtime and hide the window");
        LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugError, "Could not stop GraphWorx runtime and hide it");
    }

    LOG( SourceInfo, DebugUtil::FunctionExit, "hideGraphWorx");
}


void GraphWorxCommunicator::setIsTerminating(const bool isTerminating)
{
    TA_Base_Core::ThreadGuard guard(m_variableLock);
    m_isTerminating = isTerminating;
}


bool GraphWorxCommunicator::isTerminating()
{
    TA_Base_Core::ThreadGuard guard(m_variableLock);
    return m_isTerminating;
}


void GraphWorxCommunicator::setShouldLaunchGraphWorx(const bool shouldLaunch)
{
    TA_Base_Core::ThreadGuard guard(m_variableLock);
    m_shouldLaunchGraphWorx = shouldLaunch;
}


bool GraphWorxCommunicator::shouldLaunchGraphWorx()
{
    TA_Base_Core::ThreadGuard guard(m_variableLock);
    return m_shouldLaunchGraphWorx;
}


void GraphWorxCommunicator::setShouldShutdownGraphWorx(const bool shouldShutdown)
{
    TA_Base_Core::ThreadGuard guard(m_variableLock);
    m_shouldShutdownGraphWorx = shouldShutdown;
}


bool GraphWorxCommunicator::shouldShutdownGraphWorx()
{
    TA_Base_Core::ThreadGuard guard(m_variableLock);
    return m_shouldShutdownGraphWorx;
}


bool GraphWorxCommunicator::isGraphWorxInstanceBesideLaunchBar(const unsigned long screenWidth)
{
    // If the width of the GraphWorx instance is less than that of the screen then
    // it is running next to the launch bar. We use a buffer of 10 pixels to make
    // sure the size is definitely smaller and not just one or two pixels out.
    return (m_graphWorXWindow.width < (screenWidth-10));
}


std::string GraphWorxCommunicator::getDisplay()
{
    return m_graphWorXWindow.display;
}


std::string GraphWorxCommunicator::getChildDisplay()
{
    return m_currentChildDisplay;
}


bool GraphWorxCommunicator::loadComplete(const unsigned long leftPosition)
{
    FUNCTION_ENTRY("loadComplete");
    if ((m_graphWorXWindow.left <= leftPosition) && 
        ((m_graphWorXWindow.left + m_graphWorXWindow.width) >= leftPosition))
    {
        LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugInfo, "Completed loading GraphWorX display at position %d", leftPosition);
        m_manager.incrementNumberReady();
        FUNCTION_EXIT;
        return true;
    }
    LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, "Load completed on another GWX instance.  Ignoring.");
    FUNCTION_EXIT;
    return false;
}
