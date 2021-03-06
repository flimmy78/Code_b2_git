/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:		$File: //depot/PRIV_3001/3001/transactive/app/ats/AtsAgent/src/CctvBooleanContext.h $
  * @author:	HoaVu
  * @version:	$Revision: #1 $
  *
  * Last modification:	$DateTime: 2018/03/14 13:51:20 $
  * Last modified by:	$Author: lim.cy $
  *
  * Description:
  *
  *	Boolean Context...Required by the Mathematical_Evaluation library
  *
  */

#ifndef CCTVBOOLEANCONTEXT_H
#define CCTVBOOLEANCONTEXT_H

#include "bus/mathematical_evaluation/src/IBooleanContext.h"

namespace TA_IRS_App
{
	class AtsCctvData;

	class CctvBooleanContext : public TA_Base_Bus::IBooleanContext
	{

	public:

		/**
		* Constructor, Destructor
		* 
		*/
		
		CctvBooleanContext ( AtsCctvData& m_cctvData );
		virtual ~CctvBooleanContext();


		//
		// Operations required by ICctvBooleanContext interface
		//


		virtual bool getValue ( const std::string & variableName ) const;

	private:

		CctvBooleanContext();

	protected:

		AtsCctvData&	m_cctvData;

		
	};

} // close namespace TA_Bus

#endif

