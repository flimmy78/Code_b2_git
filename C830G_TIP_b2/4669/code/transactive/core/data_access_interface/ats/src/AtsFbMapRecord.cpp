 /**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/4669_T01271350/4669/transactive/core/data_access_interface/ats/src/AtsFbMapRecord.cpp $
  * @author Nick Jardine
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by: $Author: builder $
  * 
  * AtsFbMapRecord is an implementation of IAtsFbMapRecord. It holds the data specific to an AtsFbMapRecord entry
  * in the database, and allows read-only access to that data.
  */

#if defined(_MSC_VER)
	#pragma warning(disable:4290)	// C++ Exception Specification ignored
#endif // defined _MSC_VER

#include "core/data_access_interface/ats/src/AtsFbMapRecord.h"

#include "core/utilities/src/TAAssert.h"

namespace TA_IRS_Core
{
	const std::string AtsFbMapRecord::TRACK_INNERBOUND			= "IT";
	const std::string AtsFbMapRecord::TRACK_CENTRALINNERBOUND	= "CIT";
	const std::string AtsFbMapRecord::TRACK_OUTERBOUND			= "OT";
	const std::string AtsFbMapRecord::TRACK_CENTRALOUTERBOUND	= "COT";

    AtsFbMapRecord::AtsFbMapRecord(const unsigned long key)
    {
        m_atsFbMapRecordHelper = new AtsFbMapRecordHelper(key);
    }

    AtsFbMapRecord::AtsFbMapRecord(unsigned long row, TA_Base_Core::IData& data)
     : m_atsFbMapRecordHelper( new AtsFbMapRecordHelper(row, data))
    {
    }

    AtsFbMapRecord::~AtsFbMapRecord() 
	{
        delete m_atsFbMapRecordHelper;
        m_atsFbMapRecordHelper=NULL;
    }

	unsigned long AtsFbMapRecord::getBranchId()
	{
        TA_ASSERT(m_atsFbMapRecordHelper != NULL,"The AtsFbMapRecordHelper pointer is null.");
        return m_atsFbMapRecordHelper->getBranchId();
    }

	std::string AtsFbMapRecord::getBranchIdAsString()
	{
        TA_ASSERT(m_atsFbMapRecordHelper != NULL,"The AtsFbMapRecordHelper pointer is null.");
        return m_atsFbMapRecordHelper->getBranchIdAsString();
    }

	std::string AtsFbMapRecord::getTrack()
	{
        TA_ASSERT(m_atsFbMapRecordHelper != NULL,"The AtsFbMapRecordHelper pointer is null.");
        return m_atsFbMapRecordHelper->getTrack();
    }

	unsigned long AtsFbMapRecord::getMinAbscissa()
	{
        TA_ASSERT(m_atsFbMapRecordHelper != NULL,"The AtsFbMapRecordHelper pointer is null.");
        return m_atsFbMapRecordHelper->getMinAbscissa();
    }

	unsigned long AtsFbMapRecord::getMaxAbscissa()
	{
        TA_ASSERT(m_atsFbMapRecordHelper != NULL,"The AtsFbMapRecordHelper pointer is null.");
        return m_atsFbMapRecordHelper->getMaxAbscissa();
    }

	double AtsFbMapRecord::getZoneId()
	{
        TA_ASSERT(m_atsFbMapRecordHelper != NULL,"The AtsFbMapRecordHelper pointer is null.");
        return m_atsFbMapRecordHelper->getZoneId();
    }

	std::string AtsFbMapRecord::getZoneTypeName()
	{
        TA_ASSERT(m_atsFbMapRecordHelper != NULL,"The AtsFbMapRecordHelper pointer is null.");
        return m_atsFbMapRecordHelper->getZoneTypeName();
    }

	unsigned long AtsFbMapRecord::getKey()
	{
        TA_ASSERT(m_atsFbMapRecordHelper != NULL,"The AtsFbMapRecordHelper pointer is null.");
        return m_atsFbMapRecordHelper->getKey();
    }

	std::string AtsFbMapRecord::getName()
    {
        TA_ASSERT(m_atsFbMapRecordHelper != NULL,"The AtsFbMapRecordHelper pointer is null.");

        std::ostringstream name;
		name << m_atsFbMapRecordHelper->getBranchId();
        name << "/";
		name << m_atsFbMapRecordHelper->getTrack();
		name << " - ";
		name << m_atsFbMapRecordHelper->getZoneId();

        return name.str();
    }


    void AtsFbMapRecord::invalidate()
    {
        TA_ASSERT(m_atsFbMapRecordHelper != NULL,"The AtsFbMapRecordHelper pointer is null.");
        m_atsFbMapRecordHelper->invalidate();
    }

} // closes TA_Core
