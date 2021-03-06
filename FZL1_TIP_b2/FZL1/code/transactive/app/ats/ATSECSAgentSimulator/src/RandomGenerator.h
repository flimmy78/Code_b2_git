/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/GZL6_TIP/3002/transactive/app/ats/ATSECSAgentSimulator/src/RandomGenerator.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2012/06/12 13:35:44 $
  * Last modified by:  $Author: builder $
  *
  */

///////////////////////////////////////////////////////////
//
//  RandomGenerator.h
//  Implementation of the Class RandomGenerator
//  Generated by Enterprise Architect
//  Created on:      25-Sep-2003 18:53:34
//  Original author: 
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////


#if !defined(RandomGenerator_B323CC80_49BA_4d42_98A5_8CE9884F7924__INCLUDED_)
#define RandomGenerator_B323CC80_49BA_4d42_98A5_8CE9884F7924__INCLUDED_


#include <string>
#include "core/threads/src/Thread.h"
#include "core/synchronisation/src/ReEntrantThreadLockable.h"


class ATSECSAgentSimulatorDlg;


class RandomGenerator : public TA_Core::Thread
{

public:
	RandomGenerator(ATSECSAgentSimulatorDlg* simulatorDlg, int totalZoneIds);

	virtual ~RandomGenerator();

	virtual void run();
	virtual void terminate();

private:
	RandomGenerator( const RandomGenerator& theRandomGenerator);

protected:
	volatile bool                       m_isRunning;
    TA_Core::ReEntrantThreadLockable    m_lockForDecisionComponentUpdate;
    ATSECSAgentSimulatorDlg*            m_simulatorDlg;
    int                                 m_totalZoneIds;
};

#endif // !defined(RandomGenerator_B323CC80_49BA_4d42_98A5_8CE9884F7924__INCLUDED_)
