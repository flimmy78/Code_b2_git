/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/ats/ATSECSAgentSimulator/src/ATSECSAgentSimulator.h $
  * @author:  
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
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

class CATSECSAgentSimulatorApp : public TA_Bus::TransActiveWinApp
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
