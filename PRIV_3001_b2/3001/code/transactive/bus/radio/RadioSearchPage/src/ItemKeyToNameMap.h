/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/PRIV_3001/3001/transactive/bus/radio/RadioSearchPage/src/ItemKeyToNameMap.h $
  * @author Jade Lee
  * @version $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by: $Author: lim.cy $
  * 
  * Simple class to maintain a (cached) map of key to name data, as taken
  * from IItem (or potentially other) **data access interfaces**
  *
  */

#pragma once

#include <map>

template <class T>
class ItemKeyToNameMap
{
public:
    typedef std::map<unsigned long, std::string> KeyToNameMap;

    /**
     * refreshUsing
     *
     * Refreshes the internal key=>name map using the input data
     * @param dataArray array of data to be used to refresh the map
     *          *the individual elements of this array will be deleted*
     *          This array should have been obtained via a database access factory method
     */
    void refreshUsing(std::vector<T*>& dataArray);
 
    /**
     * getKey
     *
     * @return the key corresponding to input name
     * @param name the name to search through the map for
     */
    unsigned long getKey(const std::string& name);

    /**
     * getName
     *
     * @return the name corresponding to input key
     * @param key the key to search through the map for
     */
    std::string getName(unsigned long key) const;

    const KeyToNameMap& getInternalMap() const { return m_keyToNameMap; }

private:

    KeyToNameMap m_keyToNameMap;
};

#include "ItemKeyToNameMap.inl"
