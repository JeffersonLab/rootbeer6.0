// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIRootBeerUtilDict
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
#include "include/RootBeerUtil.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace {
  void TriggerDictionaryInitialization_RootBeerUtilDict_Impl() {
    static const char* headers[] = {
"include/RootBeerUtil.h",
nullptr
    };
    static const char* includePaths[] = {
"/home/stuart/Guff/root_6.30.06-install/include/",
"/home/stuart/rootbeer6.0/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "RootBeerUtilDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "RootBeerUtilDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "include/RootBeerUtil.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"createBeerObject", payloadCode, "@",
"getBit", payloadCode, "@",
"getEpics", payloadCode, "@",
"getNextFile", payloadCode, "@",
"resetNextFile", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("RootBeerUtilDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_RootBeerUtilDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_RootBeerUtilDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_RootBeerUtilDict() {
  TriggerDictionaryInitialization_RootBeerUtilDict_Impl();
}
