/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/ats/ATSECSAgentSimulator/src/ATSECSAgentSimulator.h $
  * @author:  
  * @version: $Revision: #3 $
  *
  * Last modification: $DateTime: 2013/07/15 18:11:22 $
  * Last modified by:  $Author: qi.huang $
  * 
  *
  */

#if !defined(AFX_ATSECSAGENTSIMULATOR_H__13EF9430_909E_4319_9238_94999F357E69__INCLUDED_)
#define AFX_ATSECSAGENTSIMULATOR_H__13EF9430_909E_4319_9238_94999F357E69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "bus/generic_gui/src/TransActiveWinApp.h"

/////////////////////////////////////////////////////////////////////////////
// CATSECSAgentSimulatorApp:
// See ATSECSAgentSimulator.cpp for the implementation of this class
//

class CATSECSAgentSimulatorApp : public TA_Base_Bus::TransActiveWinApp
{
public:
	CATSECSAgentSimulatorApp();
    virtual int ExitInstance();

    
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CATSECSAgentSimulatorApp)
	public:
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CATSECSAgentSimulatorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATSECSAGENTSIMULATOR_H__13EF9430_909E_4319_9238_94999F357E69__INCLUDED_)
