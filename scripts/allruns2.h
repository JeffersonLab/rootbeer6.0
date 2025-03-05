#include "TExpTable.h"

//variables which relate to the columns in the run table
Int_t	RT_Run;
Int_t	RT_AmoRun;
Char_t	RT_S_Date[120];
Char_t	RT_S_Time[120];
Int_t	RT_File;
Int_t	RT_Event;
Int_t	RT_Time;
Char_t	RT_Target[120];
Float_t	RT_LiveF;
Float_t	RT_LiveC;
Int_t	RT_Beam;
Float_t	RT_I;
Int_t	RT_Torus;
Int_t	RT_Mini;
Int_t	RT_ec_hi;
Int_t	RT_ec_lo;
Int_t	RT_cc_hi;
Int_t	RT_FcupA;
Char_t	RT_Radiat[120];
Char_t	RT_Good[120];
Float_t	RT_Edge;


//struct relating the variables to the column headings in the run table
struct VarNames RunTableVariables[] = {
  {"Run",	&RT_Run},
  {"AmoRun",	&RT_AmoRun},
  {"S_Date",	RT_S_Date},
  {"S_Time",	RT_S_Time},
  {"File",	&RT_File},
  {"Event",	&RT_Event},
  {"Time",	&RT_Time},
  {"Target",	RT_Target},
  {"LiveF",	&RT_LiveF},
  {"LiveC",	&RT_LiveC},
  {"Beam",	&RT_Beam},
  {"I",	&RT_I},
  {"Torus",	&RT_Torus},
  {"Mini",	&RT_Mini},
  {"ec_hi",	&RT_ec_hi},
  {"ec_lo",	&RT_ec_lo},
  {"cc_hi",	&RT_cc_hi},
  {"FcupA",	&RT_FcupA},
  {"Radiat",	RT_Radiat},
  {"Good",	RT_Good},
  {"Edge",	&RT_Edge},
  {NULL,	NULL},
};
Char_t *RunTableName = "allruns2.dat";
