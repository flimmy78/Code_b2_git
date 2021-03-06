/**
  * The source code in this file is the property of
  * MI Services Group (Australia) and is not for
  * redistribution in any form.
  *
  * Source: $File: //depot/PRIV_3001/3001/transactive/app/history/traffic_historian/src/Historian.cpp $
  * @author Katherine Thomson
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:
  *
  * The Historian controls the HistorianProcess.
  *
  */ 

// Ignore STL warnings on Windows.

#if defined( WIN32 )
#pragma warning( disable : 4786 )
#endif // defined( WIN32 )

#include "Historian.h"
#include "HistorianProcess.h"

/**
 * Historian()
 *
 * This is the standard constructor.  
 *
 */
Historian::Historian()
{
    // Do nothing.
}


/**
 * ~Historian()
 *
 * This is the standard destructor.  
 *
 */
Historian::~Historian()
{
    // Do nothing.
}


/**
 * CreateProcess()
 *
 * This method returns a pointer to the instance of the
 * HistorianProcess.
 *
 * @return A pointer to the instance of the HistorianProcess.
 *
 */
GenericDriverProcess* Historian::CreateProcess()
{
    return &HistorianProcess::getInstance();
}


