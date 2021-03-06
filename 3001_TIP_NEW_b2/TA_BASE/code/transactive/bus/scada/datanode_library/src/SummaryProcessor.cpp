/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/scada/datanode_library/src/SummaryProcessor.cpp $
  * @author:  Ripple
  * @version: $Revision: #5 $
  *
  * Last modification: $DateTime: 2014/07/11 18:24:37 $
  * Last modified by:  $Author: haijun.li $
  *
  *	The SummaryProcessor thread is responsible 
  * for generating events and submitting
  * them.
  *
  *
  */


#ifdef __WIN32__
#pragma warning(disable:4786)
#endif


#include "bus/scada/datanode_library/src/SummaryProcessor.h"

namespace TA_Base_Bus
{
    SummaryProcessor*                        SummaryProcessor::m_singleton = NULL;
    TA_Base_Core::NonReEntrantThreadLockable SummaryProcessor::m_singletonLock;


    SummaryProcessor* SummaryProcessor::getInstance()
	{
		if ( m_singleton == NULL )
		{
			TA_THREADGUARD( m_singletonLock );
			if ( m_singleton == NULL )
			{
				m_singleton = new SummaryProcessor();
			}
		}
		return m_singleton;
	}	

    void SummaryProcessor::removeInstance( SummaryProcessor*& removeMe )
	{
		TA_THREADGUARD( m_singletonLock );
		if ( removeMe == m_singleton && m_singleton != NULL)
		{
			delete m_singleton;
			m_singleton = NULL;
			removeMe = NULL;
		}
	}


	SummaryProcessor::SummaryProcessor()
	:
	m_queueHandler(NULL)
	{  
		m_queueHandler = new SummaryQueueHandler();
	}

	SummaryProcessor::~SummaryProcessor()
	{
		if (m_queueHandler != NULL )
		{
			delete m_queueHandler;
			m_queueHandler = NULL;
		}
	}
    
	void SummaryProcessor::setEntityMap(const std::map<unsigned long, IEntity*>* entityMap)
	{
        TA_ASSERT( NULL != entityMap, "entityMap cannot be NULL" );

        m_queueHandler->setEntityMap(entityMap);
    }

    void SummaryProcessor::queueItemUnique(SummaryRequest item, bool forceHandle)
    {
        m_queueHandler->queueItemUnique(item, forceHandle);    
    }

	void SummaryProcessor::setOperatorMode(TA_Base_Core::EOperationMode operationMode)
	{
		m_queueHandler->setOperationMode(operationMode);
	}
}
