// IRASelectedCall.h: interface for the IRASelectedCall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IRASELECTEDCALL_H__F67F631F_B2C2_446F_A53D_2FCEBC073873__INCLUDED_)
#define AFX_IRASELECTEDCALL_H__F67F631F_B2C2_446F_A53D_2FCEBC073873__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

namespace TA_Base_Core
{
    class IRASelectedCall 
    {
	public:
        virtual ~IRASelectedCall() {};
		
		virtual std::string getTetraid() = 0;

		virtual std::string getID() = 0;

		virtual std::string getLocation() = 0;     
    };

} 

#endif // !defined(AFX_IRASELECTEDCALL_H__F67F631F_B2C2_446F_A53D_2FCEBC073873__INCLUDED_)

 