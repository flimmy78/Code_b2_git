//
// The source code in this file is the property of
// Ripple Systems and is not for redistribution
// in any form.
//
// Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/response_plans/plan_manager/src/MainToolBarManager.h $
// @author:  Bart Golab
// @version: $Revision: #2 $
//
// Last modification: $DateTime: 2012/02/06 16:15:14 $
// Last modified by:  $Author: haijun.li $
//
// <description>

#if !defined(AFX_MAINTOOLBARMANAGER_H__C10F654A_181E_4EEA_99F3_B4FF252ED119__INCLUDED_)
#define AFX_MAINTOOLBARMANAGER_H__C10F654A_181E_4EEA_99F3_B4FF252ED119__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractToolBarManager.h"
#include "PlanManagerCommonDefs.h"


namespace TA_Base_App
{
    /////////////////////////////////////////////////////////////////////////////
    // MainToolBarManager

    class MainToolBarManager : public AbstractToolBarManager
    {
    // Types
    public:
        typedef enum
                {
                    TBT_CATEGORY = 0,
                    TBT_PLAN,
                    TBT_NONE
                }
                EToolBarType;

    // Operations
    public:
        MainToolBarManager();
        virtual ~MainToolBarManager();

        virtual void selectToolBar(EToolBarType toolBarType);
        virtual void hideToolBar();


    protected:
        virtual void initialiseToolBarList();
    };

} // namespace TA_Base_App

#endif // !defined(AFX_MAINTOOLBARMANAGER_H__C10F654A_181E_4EEA_99F3_B4FF252ED119__INCLUDED_)
