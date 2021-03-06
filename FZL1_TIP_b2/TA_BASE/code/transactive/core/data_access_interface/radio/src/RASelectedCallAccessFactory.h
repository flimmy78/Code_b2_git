// RASelectedCallAccessFactory.h: interface for the RASelectedCallAccessFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RASELECTEDCALLACCESSFACTORY_H__13483CC1_4597_4585_9BEA_00E839C61858__INCLUDED_)
#define AFX_RASELECTEDCALLACCESSFACTORY_H__13483CC1_4597_4585_9BEA_00E839C61858__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <utility>
#include <vector>

#include "core/data_access_interface/src/IDatabase.h"
#include "core/data_access_interface/src/DatabaseFactory.h"
#include "core/data_access_interface/radio/src/IRASelectedCall.h"
#include "core/synchronisation/src/NonReEntrantThreadLockable.h"

namespace TA_Base_Core
{

	class RASelectedCallAccessFactory
	{
    public:
        typedef std::vector<IRASelectedCall*> SelectedCallHistoryList;

    public:
        virtual ~RASelectedCallAccessFactory();

        /**
         * getInstance
         *
         * Creates and returns an instance of this object.
         *
         * @return A reference to an instance of a ComponentAccessFactory object.
         */
        static RASelectedCallAccessFactory& getInstance();

		RASelectedCallAccessFactory::SelectedCallHistoryList getList(const std::string& mft) const;

		void addTetraid( const std::string& mft, const std::string& tsiNumber,const std::string& id,const std::string& location) const ;

    private:
        // This class is a singleton and so the constructor, copy constructor and
        // assignment operator are all made private.
        RASelectedCallAccessFactory() { };
        RASelectedCallAccessFactory& operator=(const RASelectedCallAccessFactory &) { };
        RASelectedCallAccessFactory( const RASelectedCallAccessFactory& ) {};

        static RASelectedCallAccessFactory* s_instance;
        static NonReEntrantThreadLockable m_singletonLock;	
    };

} // closes TA_Base_Core

#endif // !defined(AFX_RASELECTEDCALLACCESSFACTORY_H__13483CC1_4597_4585_9BEA_00E839C61858__INCLUDED_)




 