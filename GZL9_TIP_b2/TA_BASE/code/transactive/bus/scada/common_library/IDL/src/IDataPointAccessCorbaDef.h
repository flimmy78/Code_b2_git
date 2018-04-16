// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.
#ifndef __IDataPointAccessCorbaDef_hh__
#define __IDataPointAccessCorbaDef_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_IDataPointAccessCorbaDef
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_IDataPointAccessCorbaDef
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_IDataPointAccessCorbaDef
#endif



#ifndef __CommonExceptionsCorbaDef_hh_EXTERNAL_GUARD__
#define __CommonExceptionsCorbaDef_hh_EXTERNAL_GUARD__
#include <CommonExceptionsCorbaDef.h>
#endif
#ifndef __ScadaCorbaTypes_hh_EXTERNAL_GUARD__
#define __ScadaCorbaTypes_hh_EXTERNAL_GUARD__
#include <ScadaCorbaTypes.h>
#endif
#ifndef __DataPointCorbaTypes_hh_EXTERNAL_GUARD__
#define __DataPointCorbaTypes_hh_EXTERNAL_GUARD__
#include <DataPointCorbaTypes.h>
#endif
#ifndef __IDataPointStateUpdateCorbaDef_hh_EXTERNAL_GUARD__
#define __IDataPointStateUpdateCorbaDef_hh_EXTERNAL_GUARD__
#include <IDataPointStateUpdateCorbaDef.h>
#endif



#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif





_CORBA_MODULE TA_Base_Bus

_CORBA_MODULE_BEG

#ifndef __TA__Base__Bus_mIDataPointAccessCorbaDef__
#define __TA__Base__Bus_mIDataPointAccessCorbaDef__

  class IDataPointAccessCorbaDef;
  class _objref_IDataPointAccessCorbaDef;
  class _impl_IDataPointAccessCorbaDef;
  
  typedef _objref_IDataPointAccessCorbaDef* IDataPointAccessCorbaDef_ptr;
  typedef IDataPointAccessCorbaDef_ptr IDataPointAccessCorbaDefRef;

  class IDataPointAccessCorbaDef_Helper {
  public:
    typedef IDataPointAccessCorbaDef_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_IDataPointAccessCorbaDef, IDataPointAccessCorbaDef_Helper> IDataPointAccessCorbaDef_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_IDataPointAccessCorbaDef,IDataPointAccessCorbaDef_Helper > IDataPointAccessCorbaDef_out;

#endif

  // interface IDataPointAccessCorbaDef
  class IDataPointAccessCorbaDef {
  public:
    // Declarations for this interface type.
    typedef IDataPointAccessCorbaDef_ptr _ptr_type;
    typedef IDataPointAccessCorbaDef_var _var_type;

    static _ptr_type _duplicate(_ptr_type);
    static _ptr_type _narrow(::CORBA::Object_ptr);
    static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
    
    static _ptr_type _nil();

    static inline void _marshalObjRef(_ptr_type, cdrStream&);

    static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
      omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static _core_attr const char* _PD_repoId;

    // Other IDL defined within this scope.
    
  };

  class _objref_IDataPointAccessCorbaDef :
    public virtual ::CORBA::Object,
    public virtual omniObjRef
  {
  public:
    void registerMonitorAgentForStateUpdate(const char* uniqueId, ::TA_Base_Bus::IDataPointStateUpdateCorbaDef_ptr dpStateUpdateServantRef);
    void setAlarmProperty(::CORBA::ULong dpKey, const char* sessionId, const ::TA_Base_Bus::DataPointCorbaTypes::SAlarmProperty& newAlarmProperty);
    ScadaCorbaTypes::UTag* getFieldValue(::CORBA::ULong dpKey);
    ScadaCorbaTypes::UTag* getRawValue(::CORBA::ULong dpKey);
    void writeDataPointValue(::CORBA::ULong dpKey, const char* sessionId, const ::TA_Base_Bus::ScadaCorbaTypes::UTag& value, ::CORBA::ULong triggeringEntity, const char* triggeringEntityValue);
    void writeDataPointValueWithoutLoggingEvent(::CORBA::ULong dpKey, const char* sessionId, const ::TA_Base_Bus::ScadaCorbaTypes::UTag& value, ::CORBA::ULong triggeringEntity, const char* triggeringEntityValue);
    void setOverride(::CORBA::ULong dpKey, const char* sessionId, const ::TA_Base_Bus::ScadaCorbaTypes::UTag& value);
    void removeOverride(::CORBA::ULong dpKey, const char* sessionId);
    void setMeterCorrectionValue(::CORBA::ULong dpKey, const char* sessionId, ::CORBA::Double correctionValue);
    void setInputInhibitState(::CORBA::ULong dpKey, const char* sessionId, ::TA_Base_Bus::ScadaCorbaTypes::EInputInhibitState inhibit);
    void setOutputInhibitState(::CORBA::ULong dpKey, const char* sessionId, ::TA_Base_Bus::ScadaCorbaTypes::EOutputInhibitState inhibit);
    ScadaCorbaTypes::SLastOperatorInfo* getLastOperatorInfo(::CORBA::ULong dpKey);
    ::CORBA::Boolean getIsMMSAlarmInhibited(::CORBA::ULong dpKey);
    ScadaCorbaTypes::EInputInhibitState getInputInhibitState(::CORBA::ULong dpKey);
    ScadaCorbaTypes::EOutputInhibitState getOutputInhibitState(::CORBA::ULong dpKey);
    ::CORBA::Boolean isWriteable(::CORBA::ULong dpKey);

    inline _objref_IDataPointAccessCorbaDef()  { _PR_setobj(0); }  // nil
    _objref_IDataPointAccessCorbaDef(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_IDataPointAccessCorbaDef();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_IDataPointAccessCorbaDef(const _objref_IDataPointAccessCorbaDef&);
    _objref_IDataPointAccessCorbaDef& operator = (const _objref_IDataPointAccessCorbaDef&);
    // not implemented

    friend class IDataPointAccessCorbaDef;
  };

  class _pof_IDataPointAccessCorbaDef : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_IDataPointAccessCorbaDef() : _OMNI_NS(proxyObjectFactory)(IDataPointAccessCorbaDef::_PD_repoId) {}
    virtual ~_pof_IDataPointAccessCorbaDef();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_IDataPointAccessCorbaDef :
    public virtual omniServant
  {
  public:
    virtual ~_impl_IDataPointAccessCorbaDef();

    virtual void registerMonitorAgentForStateUpdate(const char* uniqueId, ::TA_Base_Bus::IDataPointStateUpdateCorbaDef_ptr dpStateUpdateServantRef) = 0;
    virtual void setAlarmProperty(::CORBA::ULong dpKey, const char* sessionId, const ::TA_Base_Bus::DataPointCorbaTypes::SAlarmProperty& newAlarmProperty) = 0;
    virtual ScadaCorbaTypes::UTag* getFieldValue(::CORBA::ULong dpKey) = 0;
    virtual ScadaCorbaTypes::UTag* getRawValue(::CORBA::ULong dpKey) = 0;
    virtual void writeDataPointValue(::CORBA::ULong dpKey, const char* sessionId, const ::TA_Base_Bus::ScadaCorbaTypes::UTag& value, ::CORBA::ULong triggeringEntity, const char* triggeringEntityValue) = 0;
    virtual void writeDataPointValueWithoutLoggingEvent(::CORBA::ULong dpKey, const char* sessionId, const ::TA_Base_Bus::ScadaCorbaTypes::UTag& value, ::CORBA::ULong triggeringEntity, const char* triggeringEntityValue) = 0;
    virtual void setOverride(::CORBA::ULong dpKey, const char* sessionId, const ::TA_Base_Bus::ScadaCorbaTypes::UTag& value) = 0;
    virtual void removeOverride(::CORBA::ULong dpKey, const char* sessionId) = 0;
    virtual void setMeterCorrectionValue(::CORBA::ULong dpKey, const char* sessionId, ::CORBA::Double correctionValue) = 0;
    virtual void setInputInhibitState(::CORBA::ULong dpKey, const char* sessionId, ::TA_Base_Bus::ScadaCorbaTypes::EInputInhibitState inhibit) = 0;
    virtual void setOutputInhibitState(::CORBA::ULong dpKey, const char* sessionId, ::TA_Base_Bus::ScadaCorbaTypes::EOutputInhibitState inhibit) = 0;
    virtual ScadaCorbaTypes::SLastOperatorInfo* getLastOperatorInfo(::CORBA::ULong dpKey) = 0;
    virtual ::CORBA::Boolean getIsMMSAlarmInhibited(::CORBA::ULong dpKey) = 0;
    virtual ScadaCorbaTypes::EInputInhibitState getInputInhibitState(::CORBA::ULong dpKey) = 0;
    virtual ScadaCorbaTypes::EOutputInhibitState getOutputInhibitState(::CORBA::ULong dpKey) = 0;
    virtual ::CORBA::Boolean isWriteable(::CORBA::ULong dpKey) = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_IDataPointAccessCorbaDef;

_CORBA_MODULE_END



_CORBA_MODULE POA_TA_Base_Bus
_CORBA_MODULE_BEG

  class IDataPointAccessCorbaDef :
    public virtual TA_Base_Bus::_impl_IDataPointAccessCorbaDef,
    public virtual ::PortableServer::ServantBase
  {
  public:
    virtual ~IDataPointAccessCorbaDef();

    inline ::TA_Base_Bus::IDataPointAccessCorbaDef_ptr _this() {
      return (::TA_Base_Bus::IDataPointAccessCorbaDef_ptr) _do_this(::TA_Base_Bus::IDataPointAccessCorbaDef::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_TA_Base_Bus
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr

void operator<<=(::CORBA::Any& _a, TA_Base_Bus::IDataPointAccessCorbaDef_ptr _s);
void operator<<=(::CORBA::Any& _a, TA_Base_Bus::IDataPointAccessCorbaDef_ptr* _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, TA_Base_Bus::IDataPointAccessCorbaDef_ptr& _s);



inline void
TA_Base_Bus::IDataPointAccessCorbaDef::_marshalObjRef(::TA_Base_Bus::IDataPointAccessCorbaDef_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}




#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_IDataPointAccessCorbaDef
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_IDataPointAccessCorbaDef
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_IDataPointAccessCorbaDef
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_IDataPointAccessCorbaDef
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_IDataPointAccessCorbaDef
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_IDataPointAccessCorbaDef
#endif

#endif  // __IDataPointAccessCorbaDef_hh__

