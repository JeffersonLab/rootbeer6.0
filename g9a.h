#ifndef __g9a_h__
#define __g9a_h__

#include "TExpTable.h"

// This header was created from the table /home/stuart/g9FROST/g9a_allruns.dat on Wed 21 Nov 21:08:35 GMT 2018 by running the command:
// ./scripts/table2vars /home/stuart/g9FROST/g9a_allruns.dat g9a

// To use it, simple include the header
// A globally available ExpTable class - g9aTable is created
// together with global variables relating to each column (g9a_var) - defined below
//
// Calling the member function GetAllForValue(int value, char *variable1, char *variable2=NULL)
// searches for a row in the table and updates all the global variables to values in that row
// Usually it would be a Run number or a run range
// Eg. g9aTable->GetAllForValue(53772,"Run"); would find the row where Run=53772
// and update all the variables to the values from that row.
// Eg. g9aTable->GetAllForValue(53772,"RunMin","RunMax"); would find the row where RunMin <= 53772 <= RunMax
// and update all the variables to the values from that row.


// Create a TExpTable with this file as the actual data table
TExpTable *g9aTable = new TExpTable("/home/stuart/g9FROST/g9a_allruns.dat","g9a");

// Define variables for all the columns in the run table and set their addresses in g9aTable 

// An obscure way to define and set global table and variables that works in both
// interpreted and compiled mode - void *axx are dummies


Int_t   g9a_Run;                        void *a2  = g9aTable->SetVarAddress("Run",&g9a_Run);
Int_t   g9a_AmoRun;                     void *a3  = g9aTable->SetVarAddress("AmoRun",&g9a_AmoRun);
Char_t  g9a_Date[200];                  void *a4  = g9aTable->SetVarAddress("Date",g9a_Date);
Char_t  g9a_TStart[200];                void *a5  = g9aTable->SetVarAddress("TStart",g9a_TStart);
Char_t  g9a_TEnd[200];                  void *a6  = g9aTable->SetVarAddress("TEnd",g9a_TEnd);
Int_t   g9a_Files;                      void *a7  = g9aTable->SetVarAddress("Files",&g9a_Files);
Int_t   g9a_Events;                     void *a8  = g9aTable->SetVarAddress("Events",&g9a_Events);
Char_t  g9a_Target[200];                void *a9  = g9aTable->SetVarAddress("Target",g9a_Target);
Float_t g9a_Live;                       void *a10 = g9aTable->SetVarAddress("Live",&g9a_Live);
Int_t   g9a_EBeam;                      void *a11 = g9aTable->SetVarAddress("EBeam",&g9a_EBeam);
Float_t g9a_IBeam;                      void *a12 = g9aTable->SetVarAddress("IBeam",&g9a_IBeam);
Float_t g9a_Torus;                      void *a13 = g9aTable->SetVarAddress("Torus",&g9a_Torus);
Char_t  g9a_Radiator[200];              void *a14 = g9aTable->SetVarAddress("Radiator",g9a_Radiator);
Float_t g9a_CohEdge;                    void *a15 = g9aTable->SetVarAddress("CohEdge",&g9a_CohEdge);
Char_t  g9a_TargPol[200];               void *a16 = g9aTable->SetVarAddress("TargPol",g9a_TargPol);
Float_t g9a_TPol;                       void *a17 = g9aTable->SetVarAddress("TPol",&g9a_TPol);
Float_t g9a_TPolStatErr;                void *a18 = g9aTable->SetVarAddress("TPolStatErr",&g9a_TPolStatErr);
Float_t g9a_TPolSysErr;                 void *a19 = g9aTable->SetVarAddress("TPolSysErr",&g9a_TPolSysErr);
Char_t  g9a_Plate[200];                 void *a20 = g9aTable->SetVarAddress("Plate",g9a_Plate);
Char_t  g9a_Stat[200];                  void *a21 = g9aTable->SetVarAddress("Stat",g9a_Stat);
Char_t  g9a_Comment[200];               void *a22 = g9aTable->SetVarAddress("Comment",g9a_Comment);

#endif
