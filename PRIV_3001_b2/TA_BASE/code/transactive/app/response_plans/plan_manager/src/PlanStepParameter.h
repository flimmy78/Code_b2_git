/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/response_plans/plan_manager/src/PlanStepParameter.h $
  * @author:  Bart Golab
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * <description>
  *
  **/

#if !defined(AFX_PLANSTEPPARAMETER_H__6E86DB81_546B_4AEF_8498_D480C3E5E5BF__INCLUDED_)
#define AFX_PLANSTEPPARAMETER_H__6E86DB81_546B_4AEF_8498_D480C3E5E5BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "PlanStepParameterListCtrl.h"


namespace TA_Base_App
{
  class CPlanStepParameterEditDlg;
  class PlanStep;


  /////////////////////////////////////////////////////////////////////////////
    // PlanStepParameter

    class PlanStepParameter
    {
    // Operations
    public:
        PlanStepParameter(PlanStep& parent,std::string name);
        virtual ~PlanStepParameter();

        virtual void addToParameterList(CPlanStepParameterListCtrl &listCtrl) = 0;

        virtual void editParameter();
        virtual void viewParameter();

        PlanStep* getParentStep() const { return &m_parent; }
        const std::string &getName() const;

    protected:
        virtual TA_Base_App::CPlanStepParameterEditDlg* getEditDialog(bool canEdit) = 0;


    private:
        PlanStepParameter(const PlanStepParameter &other);
        PlanStepParameter &operator=(const PlanStepParameter &other);


    // Attributes
    private:
        std::string  m_name;
        PlanStep&    m_parent;
    };
}

#endif // !defined(AFX_PLANSTEPPARAMETER_H__6E86DB81_546B_4AEF_8498_D480C3E5E5BF__INCLUDED_)
