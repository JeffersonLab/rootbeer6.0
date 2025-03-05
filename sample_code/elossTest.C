//************************************* rbtest.C *****************************//
//                      A part of the rootbeer package                        //
//                                                                            //
//                  Ken Livingstn (k.livingston@physics,gla,ac,uk)            //
//                                                                            //
//      Version         Date                    Comment                       //
//      1               21st Feb 2003                                         //
//      1.2d            23st Mar 2004           Simplified                    //
//      2.0             16th Sep 2005           All in root framework         //
//      2.1             20st Feb 2006           Buf fix edition               //
//                                                                            //
// ******************************* elossTest.C **********************************//

// A sample code to access BANKs in root.
// This code can be run as a root macro, or built as an executable:
// See http://nuclear.gla.ac.uk/~kl/rootbeer/manual/html/node5.php
// Or the tutorial in doc/manual.ps

// ******** required headers ********************************************
//                                                                      *
#include "RootBeerUtil.h"	//gets everything for RootBeer scheme
#include "TFile.h"              // for root files
//                                                                      *
// ******** end of required headers *************************************

// ******** my headers here *********************************************
//                                                                      *
#include "TH1.h"                // eg. for 1D Histogram                 
#include "TH2.h"                // eg. for 2D Histogram
#include "TFile.h"
#include "TLorentzVector.h"
#include "particleDEF.h"        //Particle Definitions
#include "extra_packages/eloss_rb/eLoss.h"
#include "kinematics.h"

//                                                                      *
// ******** end of my headers here **************************************



// ********** required global variables *********************************
//                                                                      *
// They are global to get easily filled by parseArgs()
int 	nEventsTot=0;			// ie do all events in all files
char  	InFileName[128];		// in file name parsed from args 
char  	OutFileName[128];		// out file name parsed from args

class TRootBeer *rootbeer;        	// The main class
//                                                                      *
// ********** end of required global variables **************************

// **************** my global variables *********************************
//                                                                      *
// Eg. my hists are global to be easily accessed from the 
// root> prompt after the function is called as a macro
class   TH1F *eloss;              	// Histogram the energy losses

//                                                                      *
// **********************************************************************


// ********* required functions defined in this code ******************** 
//                                                                      *
void printUsage();			// print usage when run as exe       
int  parseArgs(int,char **);		// parse args when run as exe
//                                                                      *
// ********* end of required functions defined in this code ************* 

// ********* my functions defined in this code ************************** 
//                                                                      *
void elossTest(int, char *,char *); // main func. (same name as this macro)
//                                                                      *
// ********* end of my functions defined in this code ******************* 


// ---------- FUNCTION DEFINITIONS BEGIN HERE ---------------------

// ---------- Required main() for making an executable -------------
#ifdef ROOTEXE
int main(int argc,char **argv){		
  if((parseArgs(argc,argv))!=0) return(-1);	//parse input args
  elossTest(nEventsTot,InFileName,OutFileName);	//call user function
  return(0);
}
#endif
// ---------- end of required main() for making an executable ------

// ---------- user main function  -----------------------------------------------
// This gets called by main() when running as an executable,
// or interactively from the root> prompt.
// should have the same name as this file (minus the .C suffix)
// customize the "non-required" sections
 
void elossTest(int nEvents, char *file, char *outFileName){   // main user function

  // *****************variables which are required***********************
  //                                                                    *
  int	event=0;             	// Event counter for current file
  int	eventTot=0;	       	// Total event count
  class	TFile *outFile;         // the file to put the results
  char 	inFile[128];	       	// holds the current file name
  int 	fileNo=0;	       	// current file no if sorting though a list
  //                                                                    *
  // ********* end of variables which are required **********************


  // ******************* my variables ***********************************
  //                                                                    *
  char 	name[100];			 // hold temp names for hists 
  TLorentzVector *p_in=NULL,*p_out=NULL; // momenta before and after eloss correction
  TVector3	vert;			 // the vertex
  //                                                                    *
  // ******************* end of my variables ****************************
  
  // ************************* required init stuff **********************
  //                                                                    *
#ifdef ROOTEXE					//if running as an executable
  outFile=new TFile(outFileName,"recreate");	//open output file 
#endif
  eventTot=0;			 		// init the total event counter
  //
  //                                                                    *
  // ****************** end of required init stuff **********************

  // ******* User initialisation ****************************************
  //                                                                    *
  //
  // ** DONT FORGET TO DEFINE THE BANKS YOU WANT RIGHT HERE
  // This line can be generated by running:
  // >getbanks -Nevents <BosFile| rootDSTFile>
  char *mybanks[]={"EVNT","null"};	// make a list of the banks you want to use
  // ** DONT FORGET TO DEFINE THE BANKS YOU WANT RIGHT HERE
  //
  //Set up my histograms (variables already defined as globals above)
  //                                                                    *
  // ******* End of User initialisation  ********************************
  eloss = new TH1F("eloss","Proton energy loss in target and start counter",50,0,50); //for hit rate of paddles   
  eloss ->GetXaxis()->SetTitle("Energy loss (MeV)");
  //targ_X, targ_y, targ_z, st_offset 
  initELoss(0.0,0.0,0.0,2.0);
  p_in = new TLorentzVector();
  p_out = new TLorentzVector();

  // ********************** main file loop **********************************************************
  //                                                                                                *
  while((fileNo=getNextFile(inFile,file))!=-1){  // loop while files are still avialable 

    // Start of user stuff to do before sorting each file  ---------------
    fprintf(stderr,"Sorting file - %s\n",inFile);
    // End of user stuff to do before sorting each file  ---------------


    if((rootbeer=createBeerObject(inFile))==NULL) return; 	// create rootbeer object
    rootbeer->SetBankStatus(mybanks,ON);			// switch on the banks required
    rootbeer->StartServer();                  			// start the server running
    rootbeer->ListServedBanks();			       	// list the banks which will be served

    event=0;		//zero the event counter for the file

    // ********************** main event loop ******************************************************
    //                                                                                             *

    while(event>=0){                                           	// do all events
      event = rootbeer->GetEvent();                            	// get next event

      // Start of user customized section ----------------------------

      //eg of handling of single sector bank TAGR
      for(int row=0;row<EVNT_NH;row++){ 		 	// loop over rows in TAGR bank
	// get eloss correction for all protons
	if(EVNT[row].ID==2212){					// do protons only
	  //construct 4 vector 
	  p_out->SetXYZM(EVNT[row].Pmom*EVNT[row].Cx,
			EVNT[row].Pmom*EVNT[row].cy,
			EVNT[row].Pmom*EVNT[row].cz,
       			PROTON_MASS);
	  // make 3vector for vertex
	  vert.SetXYZ(EVNT[row].X,EVNT[row].Y,EVNT[row].Z);
	  //         *p_in=*eLoss(p_out,PROTON_MASS,vert,2,7);
	  //*p_in=*eLoss(p_out,PROTON_MASS,vert,ELOSS_TAGR_BUT_G9A,7);
	  	  //*p_in=*eLoss(p_out,PROTON_MASS,vert,ELOSS_TAGR_BUT_G9A,ELOSS_CELL_g9a);
	  	  *p_in=*eLoss(p_out,PROTON_MASS,vert,2,9);
	  
	  //histogram out the eloss in MeV
	  eloss->Fill(1000.0*(p_in->P()-p_out->P()));
	  //fprintf(stderr,"p_loss=%5.2f \n",1000.0*(p_in.P()-p_out.P()));
	}
      }
      
     // End of user customized section ----------------------------

      eventTot++;
      if(eventTot%1000 == 0) fprintf(stdout,"done %d\n",eventTot);
      if((nEvents>0)&&(eventTot >=nEvents)) break;		//break if nEvents done
    }
    //                                                                                             *
    // ********************** end of main event loop ***********************************************

    // Start of user stuff to do after sorting each file  ---------------
    fprintf(stdout,"sorted %d events from file: %s\n",abs(event),inFile);
    // End of user stuff to do after sorting each file  ---------------

    delete rootbeer;                              		//Call the class destructor
    if((nEvents>0)&&(eventTot >=nEvents)) break;		//break if nEvents done
  }
  //                                                                                                *
  // ********************** end of main file loop ***************************************************



  // ******** Do any final stuff here ***********************************
  //                                                                    *
  
  // Start of user stuff to do at the end  ------------------------
  fprintf(stdout,"Sorted Total of  %d events\n",eventTot);
  // End of user stuff to do at the end  --------------------------

#ifdef ROOTEXE
  //if it's an executable, write to the output file
  outFile->Write();
  outFile->Close();
#endif
  //                                                                    *
  // ********************************************************************
}
// ---------- end of user main function  -----------------------------------------------



// ---------- required parseArgs() function  -------------------------------------------
// parses the input args when running as an executable
// set up the no of events, and input and output file names in global variables
// or prints usage
int parseArgs(int argc,char **argv){
  switch(argc){
  case(1):				// 1 or 2 args not enough
  case(2):
    printUsage();
    return(-1);
    break;
  case(3):				// 3 args elossTest <infile> <outfile>
    if((strstr(argv[1],"-N"))!=NULL){
      printUsage();
      return(-1);
    }
    else{
      strcpy(InFileName,argv[1]);
      strcpy(OutFileName,argv[2]);
    }
    break;
  case(4):				// 4 args must be "elossTest -N# <infile> <outfile>" 
    if(strncmp(argv[1],"-N",2)!=0){  	//print usage then exit */
      printUsage();
      return(-1);
    }
    else{
      sscanf(argv[1]+2,"%d",&nEventsTot);	//get the required event no
      strcpy(InFileName,argv[2]);
      strcpy(OutFileName,argv[3]);
    }      
    break;
  default:
    printUsage();
    return(-1);
    break;
  }
  return(0);
}
// ---------- end of required parseArgs() function  -------------------------------------

// ---------- required printUsage() function  -------------------------------------------
// When running as executable, gets called if no args, or silly args
void printUsage(){
  fprintf(stderr,"\nusage:\n\n");
  fprintf(stderr,"elossTest -h   Print this message\n\n");
  fprintf(stderr,"elossTest [-Nevents] <infile> <outfile.root> \n");
  fprintf(stderr,"elossTest [-Nevents] <-Lfilelist> <outfile.root> \n");
}
// ---------- end of required printUsage() function  -------------------------------------------
