#ifndef DBCACHELOOKUP_H_INCLUDED
#define DBCACHELOOKUP_H_INCLUDED
/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/bus/security/security_utilities/src/DbCacheLookup.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2018/03/14 13:51:20 $
  *  Last modified by:  $Author: lim.cy $
  *
  *  Template for managing a database pkey keyed map of access factories.
  */
namespace TA_Base_Bus
{
	template<class Key, class Value, class AccessFactory >
	class DbCacheLookup
	{
	public:

		typedef Value* (AccessFactory::*MemPtr)(const Key, const bool);
		typedef typename std::map<Key,Value*>::iterator MapIt;
        typedef typename std::map<Key,Value*>::value_type MapValue;
		typedef typename std::vector<Value*>::const_iterator ConstVectorIt;
		
		DbCacheLookup( std::map<Key,Value*>& dbMap, AccessFactory& factory, MemPtr memPtr );

		Value* lookup( const Key& key );

		// forced multiple update to the cache (for efficiency)
		void set( const std::vector<Value*>& newValue );

	private:
		//DbCacheLookup(const DbCacheLookup& dbCacheLookup);

		std::map<Key,Value*>&   m_dbMap;
		AccessFactory& m_factory;
		MemPtr         m_memPtr;
	};

	template<class Key, class Value, class AccessFactory >
		DbCacheLookup<Key,Value,AccessFactory>::DbCacheLookup(
				std::map<Key,Value*>& dbMap, AccessFactory& factory, MemPtr memPtr ) :
			m_dbMap(dbMap),
			m_factory(factory),
			m_memPtr(memPtr)
		{
		}

	template<class Key, class Value, class AccessFactory>
		Value* DbCacheLookup<Key,Value,AccessFactory>::lookup( const Key& key )
		{
			Value* rval = 0;
			MapIt it;

			it = m_dbMap.find( key );

			// found key
			if( m_dbMap.end() == it )
			{
				std::auto_ptr<Value> newValue( (m_factory.*m_memPtr)(key,false) );
				rval = newValue.get();
				m_dbMap.insert( MapValue(key,newValue.release()) );
			}

			// not found key
			else
			{
				rval = it->second;
			}
			return( rval );
		}

	template<class Key, class Value, class AccessFactory>
		void DbCacheLookup<Key,Value,AccessFactory>::set( const std::vector<Value*>& newValue )
	{
		ConstVectorIt newIt;
		MapIt it;

		// set value
		for( newIt = newValue.begin(); newIt != newValue.end(); newIt++ )
		{
			// found key
			if( (it = m_dbMap.find((*newIt)->getKey())) != m_dbMap.end() )
			{
				delete it->second;
				it->second = *newIt;
			}

			// not found key
			else
			{
				m_dbMap.insert( MapValue((*newIt)->getKey(), *newIt) );
			}
		}
	}
}
#endif // DBCACHELOOKUP_H_INCLUDED
