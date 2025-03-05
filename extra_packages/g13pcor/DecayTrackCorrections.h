//Author: Paul Mattione (12/14/2005)

/* DecayTrackCorrections.h:
   This code contains the variable and function declarations for the DecayTrackCorrections.C code.
   For detailed information on this code, refer to DecayTrackCorrections.C
*/

#ifndef DecayTrackCorrections_h
#define DecayTrackCorrections_h

#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "TObject.h"
#include "TObjArray.h"
#include "TFile.h"
#include "TH2D.h"
#include "TF1.h"
#include "TF2.h"
#include "TF3.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "DecayTrackFunctions.h"
//#include "DecayCaldbServer.h"

using namespace std;

void Create_dtcCorrectionFunctions(int locRunNumber);
double Correct_dtcTrackMomentum(int locRunNumber, int locID, const TLorentzVector &locP4);
double Correct_dtcTrackMomentum(int locRunNumber, int locID, int locSector, const TLorentzVector &locP4);
void Correct_dtcTrackAngles(int locRunNumber, int locID, int locSector, double &locBogdanLambda, double &locBogdanPhi);
void Correct_dtcTrackLocation(int locRunNumber, int locID, int locSector, const vector<double> &locBogdanParamsOrig, vector<double> &locBogdanParamsOrigCorr);
double Correct_dtcPhotonEnergy(int locRunNumber, double locPhotonEnergy, int locDetectID);
double Correct_dtcPhotonEnergy_TaggerCalib(int locRunNumber, double locPhotonEnergy, int locDetectID);

TObjArray* Get_dtcPCorrFuncArray();
TObjArray* Get_dtcBogdanLambdaCorrFuncArray();
TObjArray* Get_dtcBogdanPhiCorrFuncArray();
TObjArray* Get_dtcBogdanD0CorrFuncArray();
TObjArray* Get_dtcBogdanZ0CorrFuncArray();
TObjArray* Get_dtcSCPaddleMatchingPositivesFuncArray();
TObjArray* Get_dtcSCPaddleMatchingNegativesFuncArray();
TFile* Get_dtcBeamECorrFile();
TH1D* Get_dtcBeamECorrHist1();
TH1D* Get_dtcBeamECorrHist2();

//these don't belong here, but i don't care
void Setup_dtcSCPaddleMap(int locRunNumber);
int Determine_dtcSCPaddle(int locRunNumber, double locQ, double locP, double locTheta, double locVertexZ);
double Determine_dtcThetaFromSCPaddle(int locRunNumber, double locQ, double locP, double locSCPaddle, double locVertexZ);
double Determine_dtcThetaFromSCPaddle(int locRunNumber, double locQ, double locP, double locSCPaddle, int locVertexZBin);

#endif
