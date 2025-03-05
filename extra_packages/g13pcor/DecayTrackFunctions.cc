//Author: Paul Mattione (06/11/2007)

#include "DecayTrackFunctions.h"

/* DecayTrackFunctions.C:
   Useful Track Functions
*/

int Calc_dtfSector(const TLorentzVector &locP4){
  return Calc_dtfSector(locP4.Vect());
}

int Calc_dtfSector(const TVector3 &locP4){
/* Calculates and returns the sector of CLAS the track went through */
  return Calc_dtfSector(locP4.Phi());
}

int Calc_dtfSector(double locPhi){
  locPhi += 3.14159265359/6.0;
  if(locPhi < 0.0)
    locPhi += 2*3.14159265359;
  int locSector = int(floor(locPhi*3.0/3.14159265359)) + 1;
  return locSector;
}

double Calc_dtfAlpha(int locSector){
  return 3.14159265359*(double(locSector) - 1.0)/3.0;
}

double Calc_dtfSectorNormLabPhi(const TLorentzVector &locP4){
  return Calc_dtfSectorNormLabPhi(locP4.Vect(), 0);
}

double Calc_dtfSectorNormLabPhi(const TLorentzVector &locP4, int locSector){
  return Calc_dtfSectorNormLabPhi(locP4.Vect(), locSector);
}

double Calc_dtfSectorNormLabPhi(const TVector3 &locP3){
  return Calc_dtfSectorNormLabPhi(locP3, 0);
}

double Calc_dtfSectorNormLabPhi(const TVector3 &locP3, int locSector){
//calculates the lab phi for the sector (-pi/6 < phi < pi/6)
  if((locSector < 1) || (locSector > 6))
    locSector = Calc_dtfSector(locP3);
  double locLabPhi = atan2(locP3.Py(),locP3.Px());

  if(locSector < 4)
    locLabPhi -= Calc_dtfAlpha(locSector);
  else if(locSector > 4)
    locLabPhi += Calc_dtfAlpha(8 - locSector);
  else if(locLabPhi > 0)
    locLabPhi -= 3.14159265359;
  else{locLabPhi += 3.14159265359;}
  return locLabPhi;
}

double Calc_dtfSectorNormLabPhi(double locLabPhi){
  int locSector = Calc_dtfSector(locLabPhi);
  return Calc_dtfSectorNormLabPhi(locLabPhi, locSector);
}

double Calc_dtfSectorNormLabPhi(double locLabPhi, int locSector){
//calculates the lab phi for the sector (-pi/6 < phi < pi/6)
  if(locSector < 4)
    locLabPhi -= Calc_dtfAlpha(locSector);
  else if(locSector > 4)
    locLabPhi += Calc_dtfAlpha(8 - locSector);
  else if(locLabPhi > 0)
    locLabPhi -= 3.14159265359;
  else{locLabPhi += 3.14159265359;}
  return locLabPhi;
}

void Convert_dtfLabtoBogdanCoords(vector<double> &locBogdanParams, const TLorentzVector &locP4, const TVector3 &locVertex, int locSector){
  //Note, these are converted bogdan params (1st param is p instead of -q/p)
  double locCosA, locSinA, locYtrk;
  double locAlpha = Calc_dtfAlpha(locSector);

  locBogdanParams.resize(5);
  locCosA = cos(locAlpha);
  locSinA = sin(locAlpha);
  locYtrk = locVertex.X()*locCosA + locVertex.Y()*locSinA;

  //calculates the trackparams for the parent
  locBogdanParams[0] = locP4.P(); //p
  locBogdanParams[1] = asin((locP4.Py()*locCosA - locP4.Px()*locSinA)/locP4.P()); //lambda
  locBogdanParams[2] = atan2(locP4.Px()*locCosA + locP4.Py()*locSinA,locP4.Pz()); //phi
  locBogdanParams[3] = locYtrk*cos(locBogdanParams[2]) - locVertex.Z()*sin(locBogdanParams[2]); //d0
  locBogdanParams[4] = locVertex.Y()*locCosA - locVertex.X()*locSinA - locYtrk*tan(locBogdanParams[1])/sin(locBogdanParams[2]); //z0
}

void Convert_dtfBogdantoLabCoords(const vector<double> &locBogdanParams, TLorentzVector &locP4, TVector3 &locVertex, int locSector, double locMass){
  //Note, these are converted bogdan params (1st param is p instead of -q/p)
  double locAlpha = Calc_dtfAlpha(locSector);

  locP4.SetPx(locBogdanParams[0]*(cos(locBogdanParams[1])*sin(locBogdanParams[2])*cos(locAlpha) - sin(locBogdanParams[1])*sin(locAlpha)));
  locP4.SetPy(locBogdanParams[0]*(cos(locBogdanParams[1])*sin(locBogdanParams[2])*sin(locAlpha) + sin(locBogdanParams[1])*cos(locAlpha)));
  locP4.SetPz(locBogdanParams[0]*cos(locBogdanParams[1])*cos(locBogdanParams[2]));
  locP4.SetE(sqrt(locP4.P()*locP4.P() + locMass*locMass));

  locVertex.SetX(-1.0*locBogdanParams[4]*sin(locAlpha));
  locVertex.SetY(locBogdanParams[4]*cos(locAlpha));
  locVertex.SetZ(-1.0*locBogdanParams[3]/sin(locBogdanParams[2]));
}

void Convert_dtfLabtoSectorCoords(int locSector, const TVector3 &locLabVertex, TVector3 &locSectorVertex){
  double locAlpha = Calc_dtfAlpha(locSector);
  locSectorVertex.SetX(locLabVertex.Z());
  locSectorVertex.SetY(locLabVertex.X()*cos(locAlpha) + locLabVertex.Y()*sin(locAlpha));
  locSectorVertex.SetZ(locLabVertex.Y()*cos(locAlpha) - locLabVertex.X()*sin(locAlpha));
}

void Convert_dtfSectortoLabCoords(int locSector, const TVector3 &locSectorVertex, TVector3 &locLabVertex){
  double locAlpha = Calc_dtfAlpha(locSector);
  locLabVertex.SetX(locSectorVertex.Y()*cos(locAlpha) - locSectorVertex.Z()*sin(locAlpha));
  locLabVertex.SetY(locSectorVertex.Y()*sin(locAlpha) + locSectorVertex.Z()*cos(locAlpha));
  locLabVertex.SetZ(locSectorVertex.X());
}

void Construct_dtfCovMatrix(TMatrixD& locCovMatrix, const vector<double>& locBogdanSigma, const vector<double>& locBogdanCorrelations){
  int loc_i, loc_j, locCorrelationIndex = 0, locCorrelationSize = 0;
  locCovMatrix.ResizeTo(5, 5);
  locCovMatrix.Zero();
  for(loc_i = int(locBogdanSigma.size()) - 1; loc_i > 0; loc_i--)
    locCorrelationSize += loc_i;
  if(locCorrelationSize != int(locBogdanCorrelations.size())){
    cout << "WARNING: INCORRECT NUMBER OF CORRELATION TERMS.  CANNOT CONSTRUCT COVARIANCE MATRIX.  EMPTY MATRIX RETURNED." << endl;
    return;
  }

  for(loc_i = 0; loc_i < int(locBogdanSigma.size()); loc_i++){ //build covariance matrix
    for(loc_j = 0; loc_j < int(locBogdanSigma.size()); loc_j++){
      if(loc_i <= loc_j){
        locCovMatrix(loc_i,loc_j) = locBogdanSigma[loc_i]*locBogdanSigma[loc_j];
        if(loc_i != loc_j){
          locCovMatrix(loc_i,loc_j) = locCovMatrix(loc_i, loc_j)*locBogdanCorrelations[locCorrelationIndex];
          locCovMatrix(loc_j,loc_i) = locCovMatrix(loc_i, loc_j);
          locCorrelationIndex++;
        }
      }    
    }
  }
}

void Dismantle_dtfCovMatrix(const TMatrixD& locCovMatrix, vector<double>& locBogdanSigma, vector<double>& locBogdanCorrelations){
  if(locCovMatrix.GetNrows() != locCovMatrix.GetNcols()){
    cout << "WARNING: COVARIANCE MATRIX IS NOT SQUARE, CANNOT DISMANTLE" << endl;
    return;
  }
  int loc_i, loc_j;
  locBogdanSigma.resize(0);
  locBogdanCorrelations.resize(0);
  for(loc_i = 0; loc_i < locCovMatrix.GetNrows(); loc_i++)
    locBogdanSigma.push_back(sqrt(locCovMatrix(loc_i, loc_i)));
  for(loc_i = 0; loc_i < locCovMatrix.GetNrows(); loc_i++){ //deconstruct covariance matrix
    for(loc_j = 0; loc_j < locCovMatrix.GetNrows(); loc_j++){
      if((loc_i < loc_j) && (loc_i != loc_j))
        locBogdanCorrelations.push_back(locCovMatrix(loc_i, loc_j)/(locBogdanSigma[loc_i]*locBogdanSigma[loc_j]));
    }
  }
}

double Calc_dtfDOCA(const TVector3 &locUnitDir1, const TVector3 &locUnitDir2, const TVector3 &locVertex1, const TVector3 &locVertex2){
  TVector3 locInterDOCA1, locInterDOCA2;
  return Calc_dtfInterDOCA(locUnitDir1, locUnitDir2, locVertex1, locVertex2, locInterDOCA1, locInterDOCA2);
}

double Calc_dtfInterDOCA(const TVector3 &locUnitDir1, const TVector3 &locUnitDir2, const TVector3 &locVertex1, const TVector3 &locVertex2, TVector3 &locInterDOCA1, TVector3 &locInterDOCA2){
  //originated from code by Jörn Langheinrich
  //you can use this function to find the DOCA to a fixed point by calling this function with locUnitDir1 and 2 parallel, and the fixed vertex as locVertex2
  double locUnitDot = locUnitDir1*locUnitDir2;
  double locDenominator = locUnitDot*locUnitDot - 1.0; /// scalar product of directions
  double locDistVertToInterDOCA1 = 0.0, locDistVertToInterDOCA2 = 0.0; //distance from vertex to DOCA point

  if(fabs(locDenominator) < 1.0e-15) //parallel
    locDistVertToInterDOCA1 = (locVertex2 - locVertex1)*locUnitDir2/locUnitDot; //the opposite
  else{
    double locA = (locVertex1 - locVertex2)*locUnitDir1;
    double locB = (locVertex1 - locVertex2)*locUnitDir2;
    locDistVertToInterDOCA1 = (locA - locUnitDot*locB)/locDenominator;
    locDistVertToInterDOCA2 = (locUnitDot*locA - locB)/locDenominator;
  }

  locInterDOCA1 = locVertex1 + locDistVertToInterDOCA1*locUnitDir1; //intersection point of DOCA line and track 1
  locInterDOCA2 = locVertex2 + locDistVertToInterDOCA2*locUnitDir2; //intersection point of DOCA line and track 2
  double locDOCA = (locInterDOCA1 - locInterDOCA2).Mag();
  return ((locVertex2.Z() > locVertex1.Z()) ? locDOCA : -1.0*locDOCA);
}

double Calc_dtfS(const TLorentzVector& locBeamP4, const TLorentzVector& locTargetP4){
  return (locBeamP4.M2() + 2.0*locBeamP4.E()*locTargetP4.E() - 2.0*locBeamP4.P()*locTargetP4.P()*cos(locTargetP4.Angle(locBeamP4.Vect())) + locTargetP4.M2());
}

double Calc_dtfT(const TLorentzVector& locBeamP4, const TLorentzVector& locMesonP4){
  return (locBeamP4.M2() - 2.0*locBeamP4.E()*locMesonP4.E() + 2.0*locBeamP4.P()*locMesonP4.P()*cos(locMesonP4.Angle(locBeamP4.Vect())) + locMesonP4.M2());
}

double Calc_dtfU(const TLorentzVector& locBeamP4, const TLorentzVector& locHadronP4){
  return (locBeamP4.M2() - 2.0*locBeamP4.E()*locHadronP4.E() + 2.0*locBeamP4.P()*locHadronP4.P()*cos(locHadronP4.Angle(locBeamP4.Vect())) + locHadronP4.M2());
}

