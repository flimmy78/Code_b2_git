/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:		$File: //depot/4669_T01271350/4669/transactive/app/ats/AtsAgent/src/CctvRealNumberContext.h $
  * @author:	HoaVu
  * @version:	$Revision: #1 $
  *
  * Last modification:	$DateTime: 2008/11/28 16:26:01 $
  * Last modified by:	$Author: builder $
  *
  * Description:
  *
  *	Boolean Context...Required by the Mathematical_Evaluation library
  *
  */

#ifndef CCTVREALNUMBERCONTEXT_H
#define CCTVREALNUMBERCONTEXT_H

#include "bus/mathematical_evaluation/src/IRealNumberContext.h"

namespace TA_IRS_App
{
	class AtsCctvData;

	class CctvRealNumberContext : public TA_Base_Bus::IRealNumberContext
	{

	public:

		/**
		* Constructor, Destructor
		* 
		*/
		
		CctvRealNumberContext ( AtsCctvData& m_cctvData );
		virtual ~CctvRealNumberContext();


		//
		// Operations required by ICctvRealNumberContext interface
		//


		virtual double getValue ( const std::string & variableName ) const;

	private:

		CctvRealNumberContext();

	protected:

		AtsCctvData&	m_cctvData;

		
	};

} // close namespace TA_Bus

#endif

