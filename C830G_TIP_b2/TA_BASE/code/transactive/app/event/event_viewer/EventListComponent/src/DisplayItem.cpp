/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/event/event_viewer/EventListComponent/src/DisplayItem.cpp $
 * @author:  Nick Jardine
 * @version: $Revision: #1 $
 *
 * Last modification: $DateTime: 2008/11/28 16:26:01 $
 * Last modified by:  $Author: builder $
 * 
 * DisplayItem is the base class for data items that can be displayed by the Event List Component. The application using
 * the Event List Component should define a sub-class of DisplayItem for each type of data it wishes to display in the 
 * Event List Component.
 */

#include "app/event/event_viewer/EventListComponent/src/stdafx.h"
#include "app/event/event_viewer/EventListComponent/src/EventListComponent.h"
#include "app/event/event_viewer/EventListComponent/src/DisplayItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

std::string DisplayItem::s_sortColumn("");
bool DisplayItem::s_sortAscending = true;

DisplayItem::DisplayItem() 
{

}

DisplayItem::~DisplayItem()
{

}

const std::string& DisplayItem::getCompleteColumnData( const std::string& columnName )
{
    // This default implementation just returns the data from the pure
    // virtual method defined by derived classes.
    return getColumnData( columnName );
}

void DisplayItem::setSortInfo(const std::string& sortColumn, const bool sortAscending)
{
    s_sortColumn = sortColumn;
    s_sortAscending = sortAscending;
}
