/*
 * The source code in this file is the property of Ripple Systems and is not for redistribution in any form.
 *
 * Source : $File: //depot/PRIV_3001/TA_BASE/transactive/app/response_plans/plan_agent/src/DssManager.h $
 * @author  Huang Qi
 * @version $Revision: #1 $
 * Last modification : $DateTime: 2018/03/14 13:51:20 $
 * Last modified by : $Author: lim.cy $
 *
 * 
 */

#ifndef DSSMANAGER_H
#define DSSMANAGER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>


namespace TA_Base_App
{

class DssEngine;
class ITriggerObserver;

class DssManager
{
public:
    DssManager();
    virtual ~DssManager();

    void enable( const bool bEnable = true );
    void init( const bool bEnable = true );
    void uninit();

private:
	DssManager( const DssManager& );
	const DssManager& operator=( const DssManager& );

    void initTriggerObservers( const bool bEnable );
    void uninitTriggerObservers();

    ITriggerObserver* createTriggerObserver( const bool bEnable, const int nType, const unsigned long ulKey );

private:
    DssEngine* m_pDssEngine;
    std::list<ITriggerObserver*> m_lstTriggerObservers;
};

} // namespace TA_Base_App

#endif // DSSMANAGER_H
