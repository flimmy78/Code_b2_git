/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/history/scada_historian/scada_historian_data_access/src/OCIAccessExtended.h $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  */
#ifndef OCIACCESS_EXTENDED
#define OCIACCESS_EXTENDED

#include "app/history/scada_historian/scada_historian_data_access/src/OCIInsertAccess.h"
#include "core/database/src/BindVars.h"


namespace TA_App
{
        class OCIAccessExtended : public OCIInsertAccess
        {
        public:

	        OCIAccessExtended(const char* hostName, const char* databaseName,
		        const char* userName, const char* password, int max_iterations);

	        virtual ~OCIAccessExtended() {}

	        bool execArrayInsert(const std::string& command, long &retCode, BindVars *bindVector = 0, 
		        int bindType = InsertDBAccess::BY_NAME, int commit = 1);

	        void setMaxIterations(int iterations) { m_maxIterations = iterations; }

        protected:

	        int m_maxIterations;
        };

    
} // TA_App

#endif // OCIACCESS_EXTENDED
