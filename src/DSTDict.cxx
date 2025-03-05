// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIDSTDict
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
#include "include/TDST.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void delete_TDST(void *p);
   static void deleteArray_TDST(void *p);
   static void destruct_TDST(void *p);
   static void streamer_TDST(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TDST*)
   {
      ::TDST *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TDST >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TDST", ::TDST::Class_Version(), "include/TDST.h", 19,
                  typeid(::TDST), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TDST::Dictionary, isa_proxy, 16,
                  sizeof(::TDST) );
      instance.SetDelete(&delete_TDST);
      instance.SetDeleteArray(&deleteArray_TDST);
      instance.SetDestructor(&destruct_TDST);
      instance.SetStreamerFunc(&streamer_TDST);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TDST*)
   {
      return GenerateInitInstanceLocal(static_cast<::TDST*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TDST*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TDST::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TDST::Class_Name()
{
   return "TDST";
}

//______________________________________________________________________________
const char *TDST::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDST*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TDST::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDST*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TDST::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDST*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TDST::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDST*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TDST::Streamer(TBuffer &R__b)
{
   // Stream an object of class TDST.

   TRootBeer::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TDST(void *p) {
      delete (static_cast<::TDST*>(p));
   }
   static void deleteArray_TDST(void *p) {
      delete [] (static_cast<::TDST*>(p));
   }
   static void destruct_TDST(void *p) {
      typedef ::TDST current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TDST(TBuffer &buf, void *obj) {
      ((::TDST*)obj)->::TDST::Streamer(buf);
   }
} // end of namespace ROOT for class ::TDST

namespace {
  void TriggerDictionaryInitialization_DSTDict_Impl() {
    static const char* headers[] = {
"include/TDST.h",
nullptr
    };
    static const char* includePaths[] = {
"/home/stuart/Guff/root_6.30.06-install/include/",
"/home/stuart/rootbeer6.0/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "DSTDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$include/TDST.h")))  TDST;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "DSTDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "include/TDST.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TDST", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("DSTDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_DSTDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_DSTDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_DSTDict() {
  TriggerDictionaryInitialization_DSTDict_Impl();
}
