//************************************ dstmaker_ppi0_npip.C **********************************//
//                               A part of the rootbeer package                               //
//                                                                                            //
//                       Stuart Fegan, Chan Kim, George Washinton University                  //
//                                                                                            //
//         Based on dstmaker.C by Ken Livingston, University of Glasgow                       //
//        and modifications made in June 2011 by Josephine McAndrew, University of Edinburgh  //
//                                                                                            //
//        March 4, 2018 - Picking up from Jo's skim code, which could produce skims for both  //
//                        the p pi0 reaction and n pi+                                        //
//                        Contains next to no particle ID, just candidate events. Files might //
//                        be massive                                                          //
//                                                                                            //
// *********************************** dstmaker_ppi0_npip.C **********************************//
// 
// Note: Here the data is being skimmed for analysis of the ppi0 and npi+ channels.
//
//
// It makes a rootDST from one or more bos or rootDST files
// Can also put hists, or other root things in the output file
// Customize the following
// 1. The line with "char *mybanks[]={....." - this selects the banks to use
// 2. The dropBanks() function - for any used banks to be dropped from DST output
// 3. makeCuts() to decide which events to write to DST
// See http://nuclear.gla.ac.uk/~kl/rootbeer/manual/html/node5.php
// Or the tutorial in doc/manual.ps

#include "RootBeerUtil.h"
#include "TDSTWriter.h"
#include "TH1.h"                // eg. for 1D Histogram   
#include "TH2.h"                // eg. for 2D Histogram    
#include "TMath.h"

using namespace std;

class TRootBeer *rootbeer;	// the main BANK file handler object
class TDSTWriter *dstwriter;	// the writer object
class TFile *outFile;           // the file to put the results

int   nEventsTot=0;	       	// ie do all events in all files
int   dstEventCount=0;     	// Events written to DST
char  InFileName[128];	
char  OutFileName[128];	

// ----------------------- Declare Histograms here ---------------------------------

//class   TH1F *taghits;

//class   TH1F *z_h;
//class   TH1F *mass_proton_h;
//class   TH1F *mass_pos_h;
//class   TH1F *mass_pip_h;

//class   TH2F *beta_mom_h;
//class   TH2F *beta_mom_pos_h;
//class   TH2F *beta_mom_pos_cut_h;

// ---------------------------------------------------------------------------------

TRootBeer *createBeerObject();	// create instance of rootbeer Class.
int   dropBanks();		// drop banks (ie not write to DST - MUST CUSTOMIZE)
int   makeCuts();		// cuts - (MUST CUSTOMIZE)
int   closeUp();	        // Close files etc
void  printUsage();
int   parseArgs(int,char **);
void  dstmaker_ppi0_npip(int, char *, char *);

#ifdef ROOTEXE
int main(int argc,char **argv){
  if((parseArgs(argc,argv))!=0) return(-1);
  dstmaker_ppi0_npip(nEventsTot,InFileName,OutFileName);
  return(0);
}
#endif

void dstmaker_ppi0_npip(int nEvents, char *file, char *outFileName){   // The main function

  char 	inFile[128];	       		// holds the current input file name
  int 	fileNo=0;	       		// current file no if sorting though a list
  int   event=0;		    	// Event counter
  int   eventTot=0;	        	// Total event count
  int   lastHeadEvent=0;                // to get event number from HEAD bank

  outFile=new TFile(outFileName,"recreate");  	//Open the output file
  dstwriter = new TDSTWriter(outFile);		//Create the dstwriter
  dropBanks();					//Drop and banks you don't want in DST (CUSTOMIZE BELOW)

  // Example histogram

  // taghits = new TH1F("taghits","taghits",50,0,50);
  //taghits->GetXaxis()->SetTitle("Hits per event");

  // Set up histograms already defined above

  // z_h = new TH1F("z_vertex","Z co-ordinate of event vertex, all 1-particle events", 100, -70, 30);
  //z_h->GetXaxis()->SetTitle("z-position of vertex");

  // mass_proton_h = new TH1F("mass_proton","Mass squared of the proton", 2800,-0.3,2.5);
  // mass_proton_h->GetXaxis()->SetTitle("mass squared");

  // mass_pos_h = new TH1F("mass_pos","Positive particle mass squared", 2800,-0.3,2.5);
  // mass_pos_h->GetXaxis()->SetTitle("mass squared");

  //mass_pip_h = new TH1F("mass_pip","Mass squared of the pi+", 2800,-0.3,2.5);
  // mass_pip_h->GetXaxis()->SetTitle("mass squared");

 // beta_mom_h = new TH2F("beta","Beta vs. mementum, everything in 1-particle events",300,0,3,120,0,1.2);
 // beta_mom_h ->GetXaxis()->SetTitle("momentum");
 // beta_mom_h->GetYaxis()->SetTitle("beta");

 // beta_mom_pos_h = new TH2F("beta_pos","Beta vs. momentum for positive particle",300,0,3,120,0,1.2);
 // beta_mom_pos_h ->GetXaxis()->SetTitle("momentum");
 // beta_mom_pos_h->GetYaxis()->SetTitle("beta");

 // beta_mom_pos_cut_h = new TH2F("beta_pos_cut","Beta vs. momentum for positive particle after cut on pi+ and proton masses",300,0,3,120,0,1.2);
 // beta_mom_pos_cut_h ->GetXaxis()->SetTitle("momentum");
 // beta_mom_pos_cut_h->GetYaxis()->SetTitle("beta");

  // ** DONT FORGET TO DEFINE THE BANKS YOU WANT RIGHT HERE
  // This line can be generated by running:
  // >getbanks -Nevents <BosFile| rootDSTFile>
  char *mybanks[]={"HEAD","EPIC","EVNT","SCPB","MVRT","STPB","TAGR","TGBI", "null"};	// make list of banks you want to use - Hideko's banks + EPIC

// ** DONT FORGET TO DEFINE THE BANKS YOU WANT RIGHT HERE
  
  // ********************* Main file loop ***************************************************

  while((fileNo=getNextFile(inFile,file))!=-1){  	// loop while files are still avialable 
    fprintf(stderr,"Sorting file - %s\n",inFile);
    if((rootbeer=createBeerObject(inFile))==NULL) return; // create rootbeer object
    rootbeer->SetBankStatus(mybanks,ON);		//set up the banks
    rootbeer->StartServer();                  		// start the server running
    rootbeer->ListServedBanks();		     	// list the banks which will be served
    dstwriter->Init(rootbeer);				// Init the writer


    // the main sort loop ********************************************************************
    while(event>=0){                                    // do all events
      event = rootbeer->GetEvent();			// get the next event from the server

      if(HEAD[0].NEVENT){                                  //If EVENT no in HEAD = 0, set it to previous one
        lastHeadEvent=HEAD[0].NEVENT;
      }
      else{
        HEAD[0].NEVENT=lastHeadEvent;
      }

      if(makeCuts()==0){	        		// Check passed the cuts
	dstwriter->WriteDST();                     	// Write the event in the Tree
	//	taghits->Fill(TAGR_NH);			// eg. fill with no of hits in TAGR bank
	dstEventCount++;		     		// increment the count	
      }
      eventTot++;
      if(eventTot%10000 == 0) fprintf(stdout,"Sorted\t%d\tWrote\t%d\n",eventTot,dstEventCount);
      if((nEvents>0)&&(eventTot >=nEvents)) break;		//break if nEvents done
    } 

    //End the main sort loop ****************************************************************

    delete rootbeer;					// delet the rootbeer object   
    fprintf(stdout,"Read %d events from %s\n",abs(event),inFile); //print the stats 
    if((nEvents>0)&&(eventTot >=nEvents)) break;	//break if nEvents done
  }

  closeUp();						// close files delete things etc
}

// *************************************************************************** 
//                         CUSTOMIZE THIS FUNCTION                           *
//                                                                           *
//                              TO DROP BANKS                                * 
//                                                                           *
// *************************************************************************** 
//                                                                           *
//                                                                           *

int dropBanks(){
  // Now the ones from the above lot which we DON'T WANT to write out 
  // - for example
  // dstwriter->DropBank("SCR ");

  return 0;
}
//                                                                           *
//                                                                           *
// ***************************************************************************
//                                                                           *
//                           END OF BANK DROP                                * 
//                                                                           *
// ***************************************************************************





// *************************************************************************** 
//                         CUSTOMIZE THIS FUNCTION                           *
//                                                                           *
//                         CUTS AND CONDITION FILTER                         * 
//                                                                           *
//             This function has to return 0 to get the event recorded.      *
// *************************************************************************** 
//                                                                           *
//                                                                           *

int makeCuts(){
  
  int nhit=0,nNeutral=0,nPos=0,posID=0,nID=0;
  
  if((EPIC_NS)||(TESC_NH)) return 0; // To record these banks, as required to know beam polarisation settings
  if((!EVNT_NH)||(!TAGR_NH)) return -1;    //fail if EVNT or TAGR missing
  
//   if((EVNT_NH<4) &&(EVNT_NH>0) && (TAGR_NH !=0)){  
    
//     for(nhit=0;nhit<EVNT_NH;nhit++){  //loop over all hist
      
//       // cout << "nhit: " << nhit << endl;
      
//       if(EVNT[nhit].Charge == 0){ // neutral particle
// 	nNeutral++;
// 	nID=nhit;
// 	//	cout << "Neutron!" << "     " << nID << endl;
//       }
//       else{                       // charged particle
// 	//must have valid dc and either sc or ec
// 	if((EVNT[nhit].DCstat == 0)||((EVNT[nhit].ECstat == 0)&&(EVNT[nhit].SCstat == 0))) return -1;
	
// 	if(EVNT[nhit].Charge==1){ //look for positive particle
// 	  nPos++;
// 	  posID=nhit;
// 	  //cout << "Positive particle!" << "     " << posID << "     " << EVNT[posID].Mass << endl;
// 	}
// 	else return -1;
//       }
//     }
//   }
//   else return -1;
  
//   if(EVNT_NH==1){       // if 1 event then must be a proton or a pi+ ie. one positive hit
//     if(nNeutral!=0) return -1;
//   }
//   if(EVNT_NH==2){       // if 2 events then must be a proton+neutral or a neutral+pi+ ie. one positive + one neutral hit
//     if (nNeutral!=1) return -1;
//     if (nPos!=1) return -1; 
//   }
//   if(EVNT_NH==3){       // if 3 events then must be a proton+2neutral
//     if (nNeutral!=2) return -1;
//     if (nPos!=1) return -1;
//   }
  
  //      cout << "nhit again: " << nhit << " "<<nPiPlus<<" "<<nProt<< " " << nNeutral << "working" << endl;
  
  //cout << "Proton mass again: " << EVNT[pID].Mass << " n "<< nProt<<endl;
  
  // if(nProt)mass_proton_h->Fill(EVNT[pID].Mass);
  //else if(nPiPlus)mass_pip_h->Fill(EVNT[pipID].Mass);
  //else cout<<"should not be here ! "<<nhit<<" "<<EVNT_NH<<endl;
  
  return 0;
}  // End of function

//                                                                           *
//                                                                           *
// *************************************************************************** 
//                                                                           *
//                     END OF CUTS AND CONDITION FILTER                      *
//                                                                           *
// *************************************************************************** 



int parseArgs(int argc,char **argv){
  switch(argc){
  case(1):				// 1 or 2 args not enough
  case(2):
    printUsage();
    return(-1);
    break;
  case(3):				// 3 args dstmaker_ppi0_npip <infile> <outfile>
    if((strstr(argv[1],"-N"))!=NULL){
      printUsage();
      return(-1);
    }
    else{
      strcpy(InFileName,argv[1]);
      strcpy(OutFileName,argv[2]);
    }
    break;
  case(4):				// 4 args must be "dstmaker_ppi0_npip -N# <infile> <outfile>" 
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

void printUsage(){
  fprintf(stderr,"\nusage:\n\n");
  fprintf(stderr,"dstmaker_ppi0_npip -h   Print this message\n\n");
  fprintf(stderr,"dstmaker_ppi0_npip [-Nevents] <infile> <dstfile> \n");
  fprintf(stderr,"dstmaker_ppi0_npip [-Nevents] <-Lfilelist> <dstfile> \n");
}


int closeUp(){
  fprintf(stdout,"Wrote %d events to %s\n",dstEventCount,OutFileName);
  delete dstwriter;			// delete the DST writer object
  outFile->Write();			// close the files
  outFile->Close();
  return 0;
}
