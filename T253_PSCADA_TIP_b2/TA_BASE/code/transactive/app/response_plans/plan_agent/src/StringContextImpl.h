/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:		$File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/scada/datapoint_library/src/BooleanContext.h $
  * @author:	HoaVu
  * @version:	$Revision: #2 $
  *
  * Last modification:	$DateTime: 2012/02/06 16:15:14 $
  * Last modified by:	$Author: haijun.li $
  *
  * Description:
  *
  *	Boolean Context...Required by the Mathematical_Evaluation library
  *
  */

#ifndef STRING_CONTEXT_IMPL_H
#define STRING_CONTEXT_IMPL_H

#include "bus/mathematical_evaluation/src/IStringContext.h"

namespace TA_Base_App
{

	class StringContextImpl : public TA_Base_Bus::IStringContext
	{

	public:

		/**
		* Constructor, Destructor
		* 
		*/
		StringContextImpl();
        StringContextImpl( const std::map<std::string, std::string>& mapExchangingData );
		//StringContextImpl ( IExpressionNodeNotification * userOfExpression ); // for callback operation
		virtual ~StringContextImpl();


		//
		// Operations required by IBooleanContext interface
		//


		virtual std::string getValue(const std::string& name) const;
	private:
		std::map<std::string, std::string> m_mapExchangingData;
		
	};

} // close namespace TA_Base_App

#endif

