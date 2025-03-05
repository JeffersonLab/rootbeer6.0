#ifndef __g8b_h__
#define __g8b_h__

#include "TExpTable.h"

// This header was created from the table dat/g8b.dat on Fri Aug 19 14:55:39 IST 2011 by running the command:
// ./scripts/table2vars dat/g8b.dat

// To use it, simple include the header
// A globally available ExpTable class - g8bTable is created
// together with global variables relating to each column (g8b_var) - defined below
//
// Calling the member function GetAllForValue(int value, char *variable1, char *variable2=NULL)
// searches for a row in the table and updates all the global variables to values in that row
// Usually it would be a Run number or a run range
// Eg. g8bTable->GetAllForValue(53772,"Run"); would find the row where Run=53772
// and update all the variables to the values from that row.
// Eg. g8bTable->GetAllForValue(53772,"RunMin","RunMax"); would find the row where RunMin <= 53772 <= RunMax
// and update all the variables to the values from that row.


// Create a TExpTable with this file as the actual data table
TExpTable *g8bTable = new TExpTable("/home/clasg8/rootbeer2.1/dat/g8b.dat","g8b");

// Define variables for all the columns in the run table and set their addresses in g8bTable 

// An obscure way to define and set global table and variables that works in both
// interpreted and compiled mode - void *axx are dummies



#endif
