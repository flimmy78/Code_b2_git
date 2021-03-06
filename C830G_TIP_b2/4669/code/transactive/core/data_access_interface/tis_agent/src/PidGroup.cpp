/**
  * The source code in this file is the property of 
  * Ripple Systems Pty Ltd and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/4669_T01271350/4669/transactive/core/data_access_interface/tis_agent/src/PidGroup.cpp $
  * @author christiandw
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * Implementation of PidGroup class
  */

#pragma warning( disable : 4786 )

#include "core/data_access_interface/tis_agent/src/PidGroup.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/TAAssert.h"

namespace TA_IRS_Core
{


	PidGroup::PidGroup( const std::string& name,
			  std::vector<std::string> pidNames)
		: m_name(name), m_pidNames(pidNames) 
	{
		TA_ASSERT(!m_name.empty(), "!m_name.empty() failed");
	}



	PidGroup::~PidGroup()
	{

	}


	std::string PidGroup::getName() const
	{
		return m_name;
	}



	const std::vector<std::string> PidGroup::getPidNames() const
	{
		return m_pidNames;
	} 

} //end namespace TA_IRS_Core
