/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/mfc_extensions/src/auto_sort_list_ctrl/ISortingCallback.h $
  * @author Jade Lee
  * @version $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by: $Author: haijun.li $
  * 
  * Simple callback function for use in conjunction with AutoSortListCtrl
  * 
  */

#pragma once

#include "bus/mfc_extensions/src/auto_sort_list_ctrl/AutoSortListCtrl.h"

namespace TA_Base_Bus
{
    class ISortingCallback
    {
    public:
        /**
         * sortCallback
         *
         * User defined sorting function
         *
         * @return positive value if item lParam2 before lParam1, negative if lParam1 should
         *      come first
         *
         * @param lParam1, lParam2 user defined values passed in from sort operation (app specific)
         * @param columnIndex the index of the column being sorted
         * @param currentSort defines the type of sorting specified (ie ascending or descending)
         */
        virtual int sortCallback(LPARAM lParam1, LPARAM lParam2, int columnIndex, AutoSortListCtrl::ECurrentSort currentSort) = 0;
    };

}
