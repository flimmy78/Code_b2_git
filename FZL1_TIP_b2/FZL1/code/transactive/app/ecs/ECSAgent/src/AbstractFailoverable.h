/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/GZL6_TIP/3002/transactive/app/ecs/ECSAgent/src/AbstractFailoverable.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2012/06/12 13:35:44 $
  * Last modified by:  $Author: builder $
  *
  */
// AbstractFailoverable.h: interface for the AbstractFailoverable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AbstractFailoverable_INCLUDED)
#define AbstractFailoverable_INCLUDED

#include "core/synchronisation/src/Condition.h"

class AbstractFailoverable  
{

public:
    AbstractFailoverable()
        : m_isEnabled(false)
    {
    }


    virtual ~AbstractFailoverable()
    {
    }

    virtual void setControl(bool isOnStartup=false)
    {
        // Implicitly threadsafe
        m_isEnabled=true;
        m_enableSignal.signal();
    }
    virtual void setMonitor(bool isOnStartup=false)
    {
        // Implicitly threadsafe
        m_isEnabled=false;
        m_enableSignal.signal();
    }

protected:
    volatile bool m_isEnabled;

    //TD4303, to notify derived class that enable changed
    TA_Base_Core::Condition     m_enableSignal;
    
};


#endif // !defined(AbstractFailoverable_INCLUDED)
