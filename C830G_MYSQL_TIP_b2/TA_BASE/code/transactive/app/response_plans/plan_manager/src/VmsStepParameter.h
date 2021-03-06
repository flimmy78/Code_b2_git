/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/app/response_plans/plan_manager/src/VmsStepParameter.h $
  * @author:  Katherine Thomson
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  **/

#if !defined(AFX_VMS_STEP_PARAMETER_H__D7BD9004_A234_4B1F_BDE8_B44B8CEF113C__INCLUDED_)
#define AFX_VMS_STEP_PARAMETER_H__D7BD9004_A234_4B1F_BDE8_B44B8CEF113C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined (STEPTYPE_VMS_SET_SCENE) || defined (STEPTYPE_VMS_RESTORE_SCHEDULE) || defined (STEPTYPE_VMS_BLANKOUT)

#include <string>
#include "core/data_access_interface/entity_access/src/PlanAgentDataCorbaDef.h"
#include "PlanStepParameter.h"
#include "PlanStepParameterListCtrl.h"


namespace TA_Base_App
{
    /////////////////////////////////////////////////////////////////////////////
    // VmsStepParameter

    class VmsStepParameter : public PlanStepParameter
    {
    // Operations
    public:
        VmsStepParameter(PlanStep& parent, std::string name, unsigned long vmsKey);
        VmsStepParameter(PlanStep& parent, const VmsStepParameter& parameter);
        VmsStepParameter(const VmsStepParameter& parameter);
        virtual ~VmsStepParameter();

        virtual void addToParameterList(CPlanStepParameterListCtrl& listCtrl);

        void setVmsKey(unsigned long vmsKey);
        void setVmsName(const std::string& vmsName);
        unsigned long getVmsKey() const { return m_vmsKey; }
        std::string getVmsName() const { return m_vmsName; }

    protected:
        virtual TA_Base_App::CPlanStepParameterEditDlg* getEditDialog(bool canEdit);

    private:
        VmsStepParameter& operator=(const VmsStepParameter& parameter);


    // Attributes
    private:
        unsigned long m_vmsKey;
        std::string m_vmsName;
    };
}

#endif // defined (STEPTYPE_VMS_SET_SCENE) || defined (STEPTYPE_VMS_RESTORE_SCHEDULE) || defined (STEPTYPE_VMS_BLANKOUT)

#endif // !defined(AFX_VMS_STEP_PARAMETER_H__D7BD9004_A234_4B1F_BDE8_B44B8CEF113C__INCLUDED_)
