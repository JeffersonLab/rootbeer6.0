#ifndef __allruns2_h__
#define __allruns2_h__

#include "TExpTable.h"

// This header was created from the table dat/allruns2.dat on Fri Aug 19 12:11:04 IST 2011 by running the command:
// scripts/table2vars dat/allruns2.dat

// To use it, simple include the header
// A globally available ExpTable class - allruns2Table is created
// together with global variables relating to each column (allruns2_var) - defined below
//
// Calling the member function GetAllForValue(int value, char *variable1, char *variable2=NULL)
// searches for a row in the table and updates all the global variables to values in that row
// Usually it would be a Run number or a run range
// Eg. allruns2Table->GetAllForValue(53772,"Run"); would find the row where Run=53772
// and update all the variables to the values from that row.
// Eg. allruns2Table->GetAllForValue(53772,"RunMin","RunMax"); would find the row where RunMin <= 53772 <= RunMax
// and update all the variables to the values from that row.


// Create a TExpTable with this file as the actual data table
TExpTable *allruns2Table = new TExpTable("dat/allruns2.dat","allruns2");

// Define variables for all the columns in the run table and set their addresses in allruns2Table 

// An obscure way to define and set global table and variables that works in both
// interpreted and compiled mode - void *axx are dummies


Int_t   allruns2_Run;                   void *a2  = allruns2Table->SetVarAddress("Run",&allruns2_Run);
Int_t   allruns2_AmoRun;                void *a3  = allruns2Table->SetVarAddress("AmoRun",&allruns2_AmoRun);
Char_t  allruns2_S_Date[200];           void *a4  = allruns2Table->SetVarAddress("S_Date",allruns2_S_Date);
Char_t  allruns2_S_Time[200];           void *a5  = allruns2Table->SetVarAddress("S_Time",allruns2_S_Time);
Int_t   allruns2_File;                  void *a6  = allruns2Table->SetVarAddress("File",&allruns2_File);
Int_t   allruns2_Event;                 void *a7  = allruns2Table->SetVarAddress("Event",&allruns2_Event);
Int_t   allruns2_Time;                  void *a8  = allruns2Table->SetVarAddress("Time",&allruns2_Time);
Char_t  allruns2_Target[200];           void *a9  = allruns2Table->SetVarAddress("Target",allruns2_Target);
Float_t allruns2_LiveF;                 void *a10 = allruns2Table->SetVarAddress("LiveF",&allruns2_LiveF);
Float_t allruns2_LiveC;                 void *a11 = allruns2Table->SetVarAddress("LiveC",&allruns2_LiveC);
Int_t   allruns2_Beam;                  void *a12 = allruns2Table->SetVarAddress("Beam",&allruns2_Beam);
Float_t allruns2_I;                     void *a13 = allruns2Table->SetVarAddress("I",&allruns2_I);
Int_t   allruns2_Torus;                 void *a14 = allruns2Table->SetVarAddress("Torus",&allruns2_Torus);
Int_t   allruns2_Mini;                  void *a15 = allruns2Table->SetVarAddress("Mini",&allruns2_Mini);
Int_t   allruns2_ec_hi;                 void *a16 = allruns2Table->SetVarAddress("ec_hi",&allruns2_ec_hi);
Int_t   allruns2_ec_lo;                 void *a17 = allruns2Table->SetVarAddress("ec_lo",&allruns2_ec_lo);
Int_t   allruns2_cc_hi;                 void *a18 = allruns2Table->SetVarAddress("cc_hi",&allruns2_cc_hi);
Int_t   allruns2_FcupA;                 void *a19 = allruns2Table->SetVarAddress("FcupA",&allruns2_FcupA);
Char_t  allruns2_Radiat[200];           void *a20 = allruns2Table->SetVarAddress("Radiat",allruns2_Radiat);
Char_t  allruns2_Good[200];             void *a21 = allruns2Table->SetVarAddress("Good",allruns2_Good);
Float_t allruns2_Edge;                  void *a22 = allruns2Table->SetVarAddress("Edge",&allruns2_Edge);

#endif
