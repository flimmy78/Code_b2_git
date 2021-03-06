/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/core/exceptions/src/GraphWorxException.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * <description>
  *
  */
// GraphWorxException.cpp: implementation of the GraphWorxException class.
//
//////////////////////////////////////////////////////////////////////

#include "core\exceptions\src\GraphWorxException.h"
#include "core\utilities\src\DebugUtil.h"

namespace TA_Base_Core
{

	//////////////////////////////////////////////////////////////////////
	// Construction/Destruction
	//////////////////////////////////////////////////////////////////////

	GraphWorxException::GraphWorxException(const char *msg,
								 const EFail type)
		throw(): m_type(type),
		         TransactiveException(msg)
	{
		logException();
	}


	GraphWorxException::~GraphWorxException() throw()
	{

	}

	//////////////////////////////////////////////////////////////////////
	// Member Functions
	//////////////////////////////////////////////////////////////////////

	void GraphWorxException::logException()
	{
            using TA_Base_Core::DebugUtil;

		switch(m_type)
        {
        case(INVALID_FILE):
            LOG0( SourceInfo, DebugUtil::DebugFatal, "Mandatory Configuration Parameter: Missing: StartupDisplay" );
            break;
        case(NOT_RUN):
            LOG(SourceInfo,DebugUtil::ExceptionDetails,"GraphWorxException","GraphWorx could not be run");
            break;
        case(FILE_OPEN_ERROR):
            LOG(SourceInfo,DebugUtil::ExceptionDetails,"GraphWorxException","Specified schematic could not be opened");
            break;
        }
	}

} // Closes TA_Base_Core
