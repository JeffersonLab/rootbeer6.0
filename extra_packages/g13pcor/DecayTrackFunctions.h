//Author: Paul Mattione (06/11/2007)

/* DecayTrackFunctions.h:
   This code contains the variable and function declarations for the DecayTrackFunctions.C code.
   For detailed information on this code, refer to DecayTrackFunctions.C
*/

#ifndef DecayTrackFunctions_h
#define DecayTrackFunctions_h

#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TObject.h"
#include "TMatrixD.h"
#include "TVector3.h"
#include "TLorentzVector.h"

using namespace std;

// Calculates the sector of the CLAS detector the track passed through.
int Calc_dtfSector(const TLorentzVector &locP4);
int Calc_dtfSector(const TVector3 &locP4);
int Calc_dtfSector(double locPhi);

// Calculates the Alpha angle that corresponds to the CLAS detector sector
double Calc_dtfAlpha(int locSector);
// Calculates the lab phi for the sector (-pi/6 < phi < pi/6)
double Calc_dtfSectorNormLabPhi(const TLorentzVector &locP4);
double Calc_dtfSectorNormLabPhi(const TLorentzVector &locP4, int locSector);
double Calc_dtfSectorNormLabPhi(const TVector3 &locP3, int locSector);
double Calc_dtfSectorNormLabPhi(const TVector3 &locP3);
double Calc_dtfSectorNormLabPhi(double locLabPhi, int locSector);
double Calc_dtfSectorNormLabPhi(double locLabPhi);

// Converts Lab Coordinate Params to Modified Bogdan Track Parameters (Bogdan with q/p -> p).
void Convert_dtfLabtoBogdanCoords(vector<double> &locBogdanParams, const TLorentzVector &locP4, const TVector3 &locVertex, int locSector);
// Converts Modified Bogdan Track Parameters (Bogdan with q/p -> p) to Lab Coordinate Params.
void Convert_dtfBogdantoLabCoords(const vector<double> &locBogdanParams, TLorentzVector &locP4, TVector3 &locVertex, int locSector, double locMass);

void Convert_dtfLabtoSectorCoords(int locSector, const TVector3 &locLabVertex, TVector3 &locSectorVertex);
void Convert_dtfSectortoLabCoords(int locSector, const TVector3 &locSectorVertex, TVector3 &locLabVertex);

// Constructs and Returns a Covariance Matrix from the Sigmas and the Correlations
void Construct_dtfCovMatrix(TMatrixD& locCovMatrix, const vector<double>& locBogdanSigma, const vector<double>& locBogdanCorrelations);
// Dismantles a Covariance Matrix and Returns the Sigmas and Correlations
void Dismantle_dtfCovMatrix(const TMatrixD& locCovMatrix, vector<double>& locBogdanSigma, vector<double>& locBogdanCorrelations);

// Calculates DOCA between two tracks.
double Calc_dtfDOCA(const TVector3 &locUnitDir1, const TVector3 &locUnitDir2, const TVector3 &locVertex1, const TVector3 &locVertex2);
// Calculates the point on each track that is the intersection between the DOCA line and each track, as well as the doca
double Calc_dtfInterDOCA(const TVector3 &locUnitDir1, const TVector3 &locUnitDir2, const TVector3 &locVertex1, const TVector3 &locVertex2, TVector3 &locInterDOCA1, TVector3 &locInterDOCA2);

// Mandelstam Variables
double Calc_dtfS(const TLorentzVector& locBeamP4, const TLorentzVector& locTargetP4);
double Calc_dtfT(const TLorentzVector& locBeamP4, const TLorentzVector& locMesonP4);
double Calc_dtfU(const TLorentzVector& locBeamP4, const TLorentzVector& locHadronP4);

#endif
