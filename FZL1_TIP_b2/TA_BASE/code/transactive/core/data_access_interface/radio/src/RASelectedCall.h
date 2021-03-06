// RASelectedCall.h: interface for the RASelectedCall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RASELECTEDCALL_H__02A25803_F865_465A_B13A_0E7B293704B1__INCLUDED_)
#define AFX_RASELECTEDCALL_H__02A25803_F865_465A_B13A_0E7B293704B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <algorithm>
#include <functional>
#include "core/data_access_interface/radio/src/IRASelectedCall.h"

namespace TA_Base_Core
{
    class RASelectedCall : public IRASelectedCall
    {
    public:
		static const unsigned long rowLimit;
		
        RASelectedCall(
            const unsigned long& key,
            const std::string& tetraid,
			const std::string& callID,
			const std::string& location
			);

		virtual std::string getTetraid();

		virtual std::string getID();

		virtual std::string getLocation();

        virtual ~RASelectedCall();

	private:
		unsigned long m_key;
        std::string m_tetraid;
		std::string m_id;
		std::string m_location;	
    };  

} // closes TA_Base_Core

#endif // !defined(AFX_RASELECTEDCALL_H__02A25803_F865_465A_B13A_0E7B293704B1__INCLUDED_)


 