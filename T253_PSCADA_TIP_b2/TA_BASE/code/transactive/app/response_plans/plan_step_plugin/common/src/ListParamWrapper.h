#ifndef LISTPARAMWRAPPER_INCLUDE
#define LISTPARAMWRAPPER_INCLUDE

#include <string>
#include <list>
#include <vector>
#include <map>
#include <memory>
#include <sstream>

#include "bus/response_plans/PlanDataAccess/src/Serialization.h"
#include "ParameterType.h"
#include "ICompareRule.h"
#include "IParameterWrapper.h"

template<class BasicType>
class ListParamWrapper : public IParameterWrapper
{
public:
    ListParamWrapper( const int nInputType, const std::string& strUniqueName, const std::string& strDisplayName, std::list<BasicType>& refSrc,
        std::auto_ptr<ICompareRule> ptrValidateRule = NullCompareRule, std::auto_ptr<ICompareRule> ptrDisplayRule = NullCompareRule );
    virtual ~ListParamWrapper();

    virtual std::string uniqueName();
    virtual std::string displayName();
    virtual std::string displayValue();
    virtual int type();
    virtual bool show();
    virtual bool valid();

    void convertToDisplayValue( const BasicType& refSrc, std::string& strDisplayValue );
    void convertToActualValue( const std::string& strDisplayValue, BasicType& refSrc );

private:
    std::string m_strUniqueName;
    std::string m_strDisplayName;
    std::string m_strDisplayValue;
    int m_nInputType;
    std::list<BasicType>& m_refSrc;
    std::auto_ptr<ICompareRule> m_ptrValidateRule;
    std::auto_ptr<ICompareRule> m_ptrDisplayRule;
};

template<class BasicType>
ListParamWrapper<BasicType>::ListParamWrapper( const int nInputType, const std::string& strUniqueName, const std::string& strDisplayName,
    std::list<BasicType>& refSrc, std::auto_ptr<ICompareRule> ptrValidateRule, std::auto_ptr<ICompareRule> ptrDisplayRule ) :
    m_strUniqueName( strUniqueName.c_str() ),
    m_strDisplayName( strDisplayName.c_str() ),
    m_strDisplayValue( "" ),
    m_nInputType( nInputType ),
    m_refSrc( refSrc ),
    m_ptrValidateRule( ptrValidateRule ),
    m_ptrDisplayRule( ptrDisplayRule )
{
}

template<class BasicType>
ListParamWrapper<BasicType>::~ListParamWrapper()
{
}

template<typename BasicType>
void ListParamWrapper<BasicType>::convertToActualValue( const std::string& strDisplayValue, BasicType& refSrc )
{
    std::istringstream ostConvert( strDisplayValue );

    ostConvert >> refSrc;
}

template<typename BasicType>
void ListParamWrapper<BasicType>::convertToDisplayValue( const BasicType& refSrc, std::string& strDisplayValue )
{
    std::stringstream ostConvert;

    ostConvert << refSrc;

    ostConvert >> strDisplayValue;
}

template<class BasicType>
bool ListParamWrapper<BasicType>::valid()
{
    bool bValid = true;

    if ( NULL != m_ptrValidateRule.get() )
    {
        bValid = m_ptrValidateRule->result();
    }

    return bValid;
}

template<class BasicType>
bool ListParamWrapper<BasicType>::show()
{
    bool bShow = true;

    if ( NULL != m_ptrDisplayRule.get() )
    {
        bShow = m_ptrDisplayRule->result();
    }

    return bShow;
}

template<class BasicType>
int ListParamWrapper<BasicType>::type()
{
    return m_nInputType;
}

template<class BasicType>
std::string ListParamWrapper<BasicType>::displayValue()
{
    return m_strDisplayValue;
}

template<class BasicType>
std::string ListParamWrapper<BasicType>::displayName()
{
    return m_strDisplayName;
}

template<class BasicType>
std::string ListParamWrapper<BasicType>::uniqueName()
{
    return m_strUniqueName;
}

#endif