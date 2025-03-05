// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIBosDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "include/TBos.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void delete_TBos(void *p);
   static void deleteArray_TBos(void *p);
   static void destruct_TBos(void *p);
   static void streamer_TBos(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TBos*)
   {
      ::TBos *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TBos >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TBos", ::TBos::Class_Version(), "include/TBos.h", 17,
                  typeid(::TBos), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TBos::Dictionary, isa_proxy, 16,
                  sizeof(::TBos) );
      instance.SetDelete(&delete_TBos);
      instance.SetDeleteArray(&deleteArray_TBos);
      instance.SetDestructor(&destruct_TBos);
      instance.SetStreamerFunc(&streamer_TBos);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TBos*)
   {
      return GenerateInitInstanceLocal(static_cast<::TBos*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TBos*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TBos::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TBos::Class_Name()
{
   return "TBos";
}

//______________________________________________________________________________
const char *TBos::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TBos*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TBos::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TBos*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TBos::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TBos*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TBos::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TBos*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TBos::Streamer(TBuffer &R__b)
{
   // Stream an object of class TBos.

   TRootBeer::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TBos(void *p) {
      delete (static_cast<::TBos*>(p));
   }
   static void deleteArray_TBos(void *p) {
      delete [] (static_cast<::TBos*>(p));
   }
   static void destruct_TBos(void *p) {
      typedef ::TBos current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TBos(TBuffer &buf, void *obj) {
      ((::TBos*)obj)->::TBos::Streamer(buf);
   }
} // end of namespace ROOT for class ::TBos

namespace {
  void TriggerDictionaryInitialization_BosDict_Impl() {
    static const char* headers[] = {
"include/TBos.h",
nullptr
    };
    static const char* includePaths[] = {
"/home/stuart/Guff/root_6.30.06-install/include/",
"/home/stuart/rootbeer6.0/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "BosDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$include/TBos.h")))  TBos;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "BosDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "include/TBos.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TBos", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("BosDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_BosDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_BosDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_BosDict() {
  TriggerDictionaryInitialization_BosDict_Impl();
}
