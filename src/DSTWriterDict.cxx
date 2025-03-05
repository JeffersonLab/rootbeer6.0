// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIDSTWriterDict
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
#include "include/TDSTWriter.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void delete_TDSTWriter(void *p);
   static void deleteArray_TDSTWriter(void *p);
   static void destruct_TDSTWriter(void *p);
   static void streamer_TDSTWriter(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TDSTWriter*)
   {
      ::TDSTWriter *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TDSTWriter >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TDSTWriter", ::TDSTWriter::Class_Version(), "include/TDSTWriter.h", 15,
                  typeid(::TDSTWriter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TDSTWriter::Dictionary, isa_proxy, 16,
                  sizeof(::TDSTWriter) );
      instance.SetDelete(&delete_TDSTWriter);
      instance.SetDeleteArray(&deleteArray_TDSTWriter);
      instance.SetDestructor(&destruct_TDSTWriter);
      instance.SetStreamerFunc(&streamer_TDSTWriter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TDSTWriter*)
   {
      return GenerateInitInstanceLocal(static_cast<::TDSTWriter*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TDSTWriter*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TDSTWriter::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TDSTWriter::Class_Name()
{
   return "TDSTWriter";
}

//______________________________________________________________________________
const char *TDSTWriter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDSTWriter*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TDSTWriter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TDSTWriter*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TDSTWriter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDSTWriter*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TDSTWriter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TDSTWriter*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TDSTWriter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TDSTWriter.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TDSTWriter(void *p) {
      delete (static_cast<::TDSTWriter*>(p));
   }
   static void deleteArray_TDSTWriter(void *p) {
      delete [] (static_cast<::TDSTWriter*>(p));
   }
   static void destruct_TDSTWriter(void *p) {
      typedef ::TDSTWriter current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TDSTWriter(TBuffer &buf, void *obj) {
      ((::TDSTWriter*)obj)->::TDSTWriter::Streamer(buf);
   }
} // end of namespace ROOT for class ::TDSTWriter

namespace {
  void TriggerDictionaryInitialization_DSTWriterDict_Impl() {
    static const char* headers[] = {
"include/TDSTWriter.h",
nullptr
    };
    static const char* includePaths[] = {
"/home/stuart/Guff/root_6.30.06-install/include/",
"/home/stuart/rootbeer6.0/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "DSTWriterDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$include/TDSTWriter.h")))  TDSTWriter;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "DSTWriterDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "include/TDSTWriter.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TDSTWriter", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("DSTWriterDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_DSTWriterDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_DSTWriterDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_DSTWriterDict() {
  TriggerDictionaryInitialization_DSTWriterDict_Impl();
}
