/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/core/data_access_interface/src/IResource.h $
  * @author:  Julian Chevalley
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2017/10/31 16:21:54 $
  * Last modified by:  $Author: CM $
  *
  * IResource interface declaration. The IResource interface represents 
  * any Access Controlled resource.
  *
  */


#if !defined(AFX_IRESOURCE_H__FD93CE24_225A_4A69_AC03_915D98770DAB__INCLUDED_)
#define AFX_IRESOURCE_H__FD93CE24_225A_4A69_AC03_915D98770DAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <boost/shared_ptr.hpp>

namespace TA_Base_Core
{
	class IResource  
	{
	public:
		virtual ~IResource() {};

		/** 
		  * getKey
		  *
		  * get the resource key
		  *
		  * @return unsigned long 
		  *
		  */
		virtual unsigned long getKey() = 0;

		/**
		  * getSubsystem
		  *
		  * @return The subsystem associated with this Resource as an unsigned long.
		  */
		virtual unsigned long getSubsystem() = 0;
	};

    typedef boost::shared_ptr<IResource> IResourcePtr;
};


#endif // !defined(AFX_IRESOUCE_H__FD93CE24_225A_4A69_AC03_915D98770DAB__INCLUDED_)
