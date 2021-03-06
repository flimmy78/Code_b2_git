/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/bus/mathematical_evaluation/src/RealNumberVariable.cpp $
  * @author:  Ross Tucker
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  */

#include "bus/mathematical_evaluation/src/RealNumberVariable.h"

namespace TA_Base_Bus
{
    RealNumberVariable::RealNumberVariable(const std::string& name, const ContextContainer& context)
    :m_name(name), m_context(context)
    {
    }


    RealNumberVariable::~RealNumberVariable()
    {
    }


    double RealNumberVariable::evaluate() const
    {
        return m_context.getRealNumberValue(m_name);
    }
}
