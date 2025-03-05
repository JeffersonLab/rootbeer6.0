


{
// Root macro to set up RootBeer, Bos, DST classes,
// and to set up for compilation of any functions using
// to sort Bos format data and rootDST format

//set include path for CINT to find inlcudes in macros
#pragma includepath ./ ./include
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("ROOTBEER"))+"/include");
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("ROOTBEER")));
  gInterpreter->AddIncludePath("/home/claslib/builds/G8G9/packages/include");

//   gInterpreter->GenerateDictionary("std::vector<TLorentzVector>","TLorentzVector.h");
//   gInterpreter->GenerateDictionary("std::vector<TVector3>","TVector3.h");
//   gInterpreter->GenerateDictionary("std::vector<TVector2>","TVector2.h");


  gROOT->SetMacroPath(Form(".:%s/sample_code:./include:%s/:%s",gSystem->Getenv("ROOTBEER"),gSystem->Getenv("ROOTBEER"),gROOT->GetMacroPath()));

// load the mklib()  function which allows makes a shared library in
// $(TOP_DIR)/slib/Linux/libXX_C.so from <ANYDIR>/XX.C
gROOT->ProcessLine(".L MacroMaker.C");

// load any required libraries
//gSystem->Load("/usr/lib/libpthread.so");
//gSystem->Load("$ROOTSYS/lib/libThread.so");
gSystem->Load("/usr/lib64/root/libThread.so");
gSystem->Load("libRootBeer"); //Load the bos shared objects
gSystem->Load("libPhysics");
gSystem->Load("$ROOTBEER_SLIB/libeloss");
//gSystem->Load("$ROOTBEER_SLIB/libg13pcor"); 
gSystem->Load("libExpTable");
//Set local includes in path

gSystem->SetIncludePath("-I./ -I./include");

}
