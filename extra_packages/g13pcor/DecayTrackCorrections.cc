//Author: Paul Mattione (10/03/2007)

#include "DecayTrackCorrections.h"

/* DecayTrackCorrections.C:
   For eg3, first correct the momentum via the eloss package. 
   Then call the Correct_dtcTrackMomentum function:
   Correct_dtcTrackMomentum(int locRunNumber, int locID, const TLorentzVector &locP4)

   Other functions present correct the track angle and position.  If you wish to use those,
   first correct the track angle, then position, then momentum.
*/

TObjArray *dtcPCorrFuncArray = NULL;
TObjArray *dtcBogdanLambdaCorrFuncArray = NULL;
TObjArray *dtcBogdanPhiCorrFuncArray = NULL;
TObjArray *dtcBogdanD0CorrFuncArray = NULL;
TObjArray *dtcBogdanZ0CorrFuncArray = NULL;
TObjArray *dtcSCPaddleMatchingPositivesFuncArray = NULL;
TObjArray *dtcSCPaddleMatchingNegativesFuncArray = NULL;
TFile *dtcBeamECorrFile = NULL;
TH1D *dtcBeamECorrHist1 = NULL;
TH1D *dtcBeamECorrHist2 = NULL;

TObjArray* Get_dtcPCorrFuncArray(){return dtcPCorrFuncArray;}
TObjArray* Get_dtcBogdanPhiCorrFuncArray(){return dtcBogdanPhiCorrFuncArray;}
TObjArray* Get_dtcBogdanLambdaCorrFuncArray(){return dtcBogdanLambdaCorrFuncArray;}
TObjArray* Get_dtcBogdanD0CorrFuncArray(){return dtcBogdanD0CorrFuncArray;}
TObjArray* Get_dtcBogdanZ0CorrFuncArray(){return dtcBogdanZ0CorrFuncArray;}

TObjArray* Get_dtcSCPaddleMatchingPositivesFuncArray(){return dtcSCPaddleMatchingPositivesFuncArray;}
TObjArray* Get_dtcSCPaddleMatchingNegativesFuncArray(){return dtcSCPaddleMatchingNegativesFuncArray;}
TFile* Get_dtcBeamECorrFile(){return dtcBeamECorrFile;}
TH1D* Get_dtcBeamECorrHist1(){return dtcBeamECorrHist1;}
TH1D* Get_dtcBeamECorrHist2(){return dtcBeamECorrHist2;}

void Create_dtcCorrectionFunctions(int locRunNumber){

  TF2 *loc2DFunc;
  TF1 *loc1DFunc;
  char *locFuncName;
  int loc_q, loc_f, loc_s;
  TObjArray *locBogdanDependentCorrFuncArray, *locSectorFuncs, *locChargeFuncs;
 
  if(((locRunNumber >= 45512) && (locRunNumber <= 46113)) || ((locRunNumber >= 53095) && (locRunNumber <= 55204))){

    if(dtcPCorrFuncArray != NULL) //functions already created
      return;

    //beam ecorrs
    if((locRunNumber >= 53095) && (locRunNumber <= 55204)){
      dtcBeamECorrFile = new TFile("/home/nicholas/packages/utilities/decayutils/dh_BeamEnergyCorrections.root", "READ");
      dtcBeamECorrHist1 = (TH1D*)dtcBeamECorrFile->Get("dh_BeamECorrFactorg13a_1D_0");
      dtcBeamECorrHist2 = (TH1D*)dtcBeamECorrFile->Get("dh_BeamECorrFactorg13b_1D_0");
    }

    dtcPCorrFuncArray = new TObjArray(3); //1st index p dependent corrs, second lambda, 3rd phi

    locBogdanDependentCorrFuncArray = new TObjArray(6);
    for(loc_f = 0; loc_f < 2; loc_f++){ //+/- charge
      locChargeFuncs = new TObjArray(6);
      for(loc_q = 0; loc_q < 6; loc_q++){
        locFuncName = new char[100];
        sprintf(locFuncName, "DCElossFunc_Mass%d_Sector%d_", loc_f + 1, loc_q + 1);
        loc1DFunc = new TF1(locFuncName,"[0]*exp(-1.0*[1]*(x + [2]))*(x >= [3])",0.0,10.0);
        delete locFuncName;
        locChargeFuncs->AddAt(loc1DFunc, loc_q);
      }
      locBogdanDependentCorrFuncArray->AddAt(locChargeFuncs, loc_f);
    }
    dtcPCorrFuncArray->AddAt(locBogdanDependentCorrFuncArray, 0);

//DCELoss Corrs:
    if((locRunNumber >= 45512) && (locRunNumber <= 46113)){
      //HEAVY CHARGED TRACKS //proton
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[0])[0])->SetParameters(0.404188, 9.61746, 0.0869865, 0.3);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[0])[1])->SetParameters(0.106765, 6.99911, 0.0922961, 0.3);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[0])[2])->SetParameters(0.128106, 8.36966, 0.0991567, 0.3);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[0])[3])->SetParameters(0.186976, 8.44586, 0.0908118, 0.3);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[0])[4])->SetParameters(0.250403, 8.32322, 0.0887129, 0.3);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[0])[5])->SetParameters(0.327241, 8.49505, 0.0865519, 0.3);

      //LIGHT CHARGED TRACKS //pions & kaons //negligible so ignored
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[0])->SetParameters(0.0, 0.0, 0.0, 0.1);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[1])->SetParameters(0.0, 0.0, 0.0, 0.1);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[2])->SetParameters(0.0, 0.0, 0.0, 0.1);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[3])->SetParameters(0.0, 0.0, 0.0, 0.1);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[4])->SetParameters(0.0, 0.0, 0.0, 0.1);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[5])->SetParameters(0.0, 0.0, 0.0, 0.1);
    }
    if((locRunNumber >= 53095) && (locRunNumber <= 55204)){
      //HEAVY CHARGED TRACKS //proton
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[0])[0])->SetParameters(0.020522, 12.4813, -0.25483, 0.3);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[0])[1])->SetParameters(0.018627, 10.7399, -0.247917, 0.3);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[0])[2])->SetParameters(0.0176381, 11.1829, -0.24356, 0.3);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[0])[3])->SetParameters(0.01956, 11.8341, -0.255268, 0.3);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[0])[4])->SetParameters(0.0210577, 11.0642, -0.264584, 0.3);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[0])[5])->SetParameters(0.0223242, 11.5093, -0.270388, 0.3);

      //LIGHT CHARGED TRACKS //pions & kaons
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[0])->SetParameters(0.0338425, 4.78706, 0.401107, 0.1);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[1])->SetParameters(0.0673667, 8.43022, 0.331273, 0.1);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[2])->SetParameters(0.12103, 12.004, 0.291959, 0.1);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[3])->SetParameters(0.240462, 14.5617, 0.207088, 0.1);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[4])->SetParameters(0.0361619, 6.97183, 0.311385, 0.1);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[5])->SetParameters(0.0220346, 4.23435, 0.400461, 0.1);

/*
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[0])->SetParameters(0.0, 0.0, 0.0, 0.0);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[1])->SetParameters(0.0, 0.0, 0.0, 0.0);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[2])->SetParameters(0.0, 0.0, 0.0, 0.0);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[3])->SetParameters(0.0, 0.0, 0.0, 0.0);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[4])->SetParameters(0.0, 0.0, 0.0, 0.0);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[1])[5])->SetParameters(0.0, 0.0, 0.0, 0.0);
*/
    }

    locBogdanDependentCorrFuncArray = new TObjArray(2);
    for(loc_f = 0; loc_f < 2; loc_f++){ //+/- charge
      locChargeFuncs = new TObjArray(6);
      for(loc_q = 0; loc_q < 6; loc_q++){
        locSectorFuncs = new TObjArray(10);
        for(loc_s = 0; loc_s < 10; loc_s++){
          locFuncName = new char[100];
          sprintf(locFuncName, "FieldMapFunc_Charge%d_Sector%d_PhiBin%d", loc_f + 1, loc_q + 1, loc_s + 1);
          loc1DFunc = new TF1(locFuncName,"-1.0*(x*x)*([0] + [1]/x)",0.0,6.0);
          delete locFuncName;
          locSectorFuncs->AddAt(loc1DFunc, loc_s);
        }
        locChargeFuncs->AddAt(locSectorFuncs, loc_q);
      }
      locBogdanDependentCorrFuncArray->AddAt(locChargeFuncs, loc_f);
    }
    dtcPCorrFuncArray->AddAt(locBogdanDependentCorrFuncArray, 1);

    //Phi Field map corrs
    if((locRunNumber >= 45512) && (locRunNumber <= 46113)){ //eg3
      //POSITIVELY CHARGED TRACKS
      //Sector 1
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[0])->SetParameters(0.00317586, -0.0032779);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[1])->SetParameters(-0.000188902, 0.000396031);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[2])->SetParameters(-0.00147003, 0.0027971);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[3])->SetParameters(-0.000186823, 0.00225022);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[4])->SetParameters(-0.000866766, 0.00344683);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[5])->SetParameters(0.000873853, 0.00261813);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[6])->SetParameters(0.0013347, 0.00290989);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[7])->SetParameters(0.00179251, 0.0035998);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[8])->SetParameters(0.00247318, 0.00338714);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[9])->SetParameters(-0.00183603, 0.00958572);
      //Sector 2
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[0])->SetParameters(0.00484639, -0.0117212);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[1])->SetParameters(0.00261184, -0.00581283);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[2])->SetParameters(0.000779676, -0.00197395);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[3])->SetParameters(0.00157184, -5.74286e-05);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[4])->SetParameters(0.00185243, 0.00183841);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[5])->SetParameters(0.00163495, 0.00337468);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[6])->SetParameters(0.000977399, 0.00610086);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[7])->SetParameters(-0.000495576, 0.0102963);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[8])->SetParameters(0.000107828, 0.0121203);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[9])->SetParameters(0.000182438, 0.0152144);
      //Sector 3
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[0])->SetParameters(0.0081286, -0.0130728);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[1])->SetParameters(0.00750899, -0.00943285);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[2])->SetParameters(0.00676295, -0.00678689);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[3])->SetParameters(0.00363484, -0.00220021);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[4])->SetParameters(0.00146771, 0.000763533);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[5])->SetParameters(0.000187274, 0.00278123);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[6])->SetParameters(-0.00162225, 0.00643246);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[7])->SetParameters(-0.00550267, 0.0120655);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[8])->SetParameters(-0.00847998, 0.0170138);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[9])->SetParameters(-0.00910224, 0.0215926);
      //Sector 4
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[0])->SetParameters(0.00545006, -0.01314);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[1])->SetParameters(0.00563323, -0.0106109);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[2])->SetParameters(0.00239094, -0.00403906);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[3])->SetParameters(0.00146926, -0.00129876);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[4])->SetParameters(-0.00042345, 0.00228097);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[5])->SetParameters(-0.000854451, 0.00516371);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[6])->SetParameters(-0.00119523, 0.00719511);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[7])->SetParameters(-0.00211747, 0.0103735);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[8])->SetParameters(-0.00300358, 0.013553);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[9])->SetParameters(0.00166077, 0.0121929);
      //Sector 5
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[0])->SetParameters(0.00452704, -0.0148247);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[1])->SetParameters(0.00426282, -0.0121293);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[2])->SetParameters(0.00103692, -0.00707349);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[3])->SetParameters(0.00359653, -0.00825969);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[4])->SetParameters(0.000929881, -0.00343423);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[5])->SetParameters(-0.000209362, -0.000404061);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[6])->SetParameters(0.0012235, -0.000754106);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[7])->SetParameters(0.000678669, 0.00269878);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[8])->SetParameters(-0.00158008, 0.00702833);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[9])->SetParameters(0.000149227, 0.00812049);
      //Sector 6
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[0])->SetParameters(0.00728358, -0.0115777);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[1])->SetParameters(0.00476769, -0.00678308);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[2])->SetParameters(0.0038496, -0.00549965);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[3])->SetParameters(0.00191158, -0.00240088);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[4])->SetParameters(0.00146774, -0.00137825);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[5])->SetParameters(-7.09803e-05, 0.00049378);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[6])->SetParameters(-0.0013891, 0.00342958);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[7])->SetParameters(-0.00327749, 0.00656464);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[8])->SetParameters(-0.00573821, 0.0106953);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[9])->SetParameters(-0.00572011, 0.0132632);

      //NEGATIVELY CHARGED TRACKS
      //Sector 1
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[0])->SetParameters(0.00650057, -0.00990176);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[1])->SetParameters(0.00555829, -0.00682484);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[2])->SetParameters(0.00161424, -0.0015537);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[3])->SetParameters(0.000873135, -0.000220803);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[4])->SetParameters(0.000188663, 0.000854815);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[5])->SetParameters(-0.00118672, 0.00308132);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[6])->SetParameters(-0.00282858, 0.00544778);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[7])->SetParameters(-0.0040381, 0.00708588);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[8])->SetParameters(-0.00553489, 0.00946327);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[9])->SetParameters(-0.00904257, 0.0172908);
      //Sector 2
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[0])->SetParameters(0.00467199, -0.00425627);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[1])->SetParameters(0.00313667, -0.000346293);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[2])->SetParameters(0.00295586, -0.000379937);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[3])->SetParameters(0.00257921, 0.00101925);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[4])->SetParameters(0.0009484, 0.00330867);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[5])->SetParameters(0.000649309, 0.00419162);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[6])->SetParameters(7.11453e-05, 0.00513724);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[7])->SetParameters(-0.000564277, 0.0065223);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[8])->SetParameters(-0.00174392, 0.00802098);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[9])->SetParameters(-0.00467512, 0.0125584);
      //Sector 3
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[0])->SetParameters(-0.00338999, 0.00232827);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[1])->SetParameters(-0.00426178, 0.00485314);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[2])->SetParameters(-0.00350484, 0.00542393);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[3])->SetParameters(-0.0030435, 0.00668112);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[4])->SetParameters(-0.00241835, 0.00823078);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[5])->SetParameters(-0.000935551, 0.00836164);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[6])->SetParameters(0.000844528, 0.00825422);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[7])->SetParameters(0.000829063, 0.0104732);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[8])->SetParameters(0.00138475, 0.0119111);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[9])->SetParameters(0.00225804, 0.0122681);
      //Sector 4
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[0])->SetParameters(0.000888416, -0.00630941);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[1])->SetParameters(-0.00233218, -0.00257776);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[2])->SetParameters(-0.00191616, -0.00220661);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[3])->SetParameters(-0.00123285, -0.00186063);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[4])->SetParameters(-0.00113573, -0.000494375);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[5])->SetParameters(1.41593e-06, -0.00124219);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[6])->SetParameters(0.000300456, -0.000216866);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[7])->SetParameters(0.00111884, -2.04318e-05);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[8])->SetParameters(0.000442001, 0.00121719);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[9])->SetParameters(-0.00326546, 0.00777796);
      //Sector 5
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[0])->SetParameters(0.00268434, -0.0054917);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[1])->SetParameters(0.00167397, -0.0035642);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[2])->SetParameters(0.000468585, -0.00148545);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[3])->SetParameters(0.00137588, -0.00189504);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[4])->SetParameters(0.00105167, -0.000964046);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[5])->SetParameters(0.000100417, 0.00131449);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[6])->SetParameters(0.000317679, 0.00110491);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[7])->SetParameters(-0.000652763, 0.00294255);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[8])->SetParameters(-0.00148662, 0.00403681);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[9])->SetParameters(-0.00541093, 0.0111612);
      //Sector 6
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[0])->SetParameters(-0.00207716, -0.00421535);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[1])->SetParameters(-0.00237928, -0.00304195);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[2])->SetParameters(-0.00207621, -0.00179448);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[3])->SetParameters(-0.00110436, -0.00109905);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[4])->SetParameters(-0.00154794, 0.00151158);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[5])->SetParameters(-0.00084596, 0.00164627);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[6])->SetParameters(-0.000892893, 0.00359015);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[7])->SetParameters(-0.000762587, 0.00498962);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[8])->SetParameters(-0.000775619, 0.00661638);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[9])->SetParameters(-0.00169969, 0.011454);
    }

    if((locRunNumber >= 53095) && (locRunNumber < 54042)){ //g13a
      //POSITIVELY CHARGED TRACKS
      //Sector 1
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[0])->SetParameters(0.00641114, -0.00362136);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[1])->SetParameters(0.00259979, -0.000644704);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[2])->SetParameters(0.00138986, 0.000624791);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[3])->SetParameters(0.00123554, 0.000825082);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[4])->SetParameters(0.00127088, 0.00103121);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[5])->SetParameters(-0.000266112, 0.00285639);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[6])->SetParameters(-0.000255668, 0.00372791);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[7])->SetParameters(-0.00142787, 0.00531868);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[8])->SetParameters(-0.00305142, 0.00682035);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[9])->SetParameters(-0.00737498, 0.0115154);
      //Sector 2
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[0])->SetParameters(0.00845663, -0.00908856);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[1])->SetParameters(0.00266302, -0.00133729);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[2])->SetParameters(0.00267311, 0.00047332);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[3])->SetParameters(0.00175751, 0.002883);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[4])->SetParameters(0.00127099, 0.00479656);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[5])->SetParameters(0.000633454, 0.00662845);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[6])->SetParameters(-0.00179117, 0.00996997);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[7])->SetParameters(-0.00409168, 0.013472);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[8])->SetParameters(-0.00621847, 0.0168902);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[9])->SetParameters(-0.00733487, 0.0196396);
      //Sector 3
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[0])->SetParameters(0.015117, -0.014061);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[1])->SetParameters(0.0100761, -0.00761977);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[2])->SetParameters(0.00609515, -0.00320319);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[3])->SetParameters(0.00383819, -0.000600024);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[4])->SetParameters(0.000747481, 0.00253025);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[5])->SetParameters(-0.00262981, 0.00603954);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[6])->SetParameters(-0.00558311, 0.00892736);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[7])->SetParameters(-0.00895203, 0.0125854);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[8])->SetParameters(-0.0123809, 0.0170906);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[9])->SetParameters(-0.0145337, 0.0217193);
      //Sector 4
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[0])->SetParameters(0.006743, -0.0112732);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[1])->SetParameters(0.00576135, -0.00712431);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[2])->SetParameters(0.0028224, -0.00300205);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[3])->SetParameters(0.00379608, -0.00258383);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[4])->SetParameters(0.000794289, 0.00126677);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[5])->SetParameters(0.00146068, 0.00215859);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[6])->SetParameters(-0.000434186, 0.00514725);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[7])->SetParameters(-0.0032664, 0.00938972);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[8])->SetParameters(-0.00486629, 0.0130656);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[9])->SetParameters(-0.00415045, 0.0149955);
      //Sector 5
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[0])->SetParameters(0.00708634, -0.00444936);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[1])->SetParameters(0.00181075, -0.000284964);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[2])->SetParameters(0.00250335, -0.000487641);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[3])->SetParameters(0.0013969, 0.00064521);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[4])->SetParameters(0.00175207, 2.9951e-05);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[5])->SetParameters(0.00305896, -0.000724451);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[6])->SetParameters(0.00337366, -0.00091012);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[7])->SetParameters(0.00302823, -0.000145335);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[8])->SetParameters(0.00155278, 0.00181364);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[9])->SetParameters(0.000304934, 0.00348011);
      //Sector 6
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[0])->SetParameters(0.0115435, -0.0150332);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[1])->SetParameters(0.00722806, -0.00939);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[2])->SetParameters(0.00533434, -0.00638207);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[3])->SetParameters(0.0033515, -0.00384407);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[4])->SetParameters(0.00122699, -0.000630752);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[5])->SetParameters(0.00136334, 0.000631668);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[6])->SetParameters(-0.0012057, 0.00399939);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[7])->SetParameters(-0.00368187, 0.00773016);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[8])->SetParameters(-0.0053141, 0.0106049);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[9])->SetParameters(-0.00430914, 0.0125069);

      //NEGATIVELY CHARGED TRACKS
      //Sector 1
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[0])->SetParameters(-0.00233274, -0.00152019);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[1])->SetParameters(0.00460717, -0.00559106);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[2])->SetParameters(0.00457271, -0.00379451);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[3])->SetParameters(0.00366269, -0.00292954);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[4])->SetParameters(0.00205647, -0.00074812);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[5])->SetParameters(0.00208179, -0.000168197);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[6])->SetParameters(-0.00137021, 0.00343098);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[7])->SetParameters(-0.00246856, 0.00515585);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[8])->SetParameters(-0.00263422, 0.00661108);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[9])->SetParameters(-0.00453828, 0.0107686);
      //Sector 2
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[0])->SetParameters(0.00487604, -0.00581733);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[1])->SetParameters(0.00160409, -0.00214493);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[2])->SetParameters(0.00213117, -0.00112258);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[3])->SetParameters(0.00028776, 0.00134466);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[4])->SetParameters(-0.000398992, 0.00268466);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[5])->SetParameters(0.000350016, 0.00299485);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[6])->SetParameters(-0.00379992, 0.00762159);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[7])->SetParameters(-0.00729434, 0.0124343);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[8])->SetParameters(-0.00690098, 0.0136595);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[9])->SetParameters(-0.0113931, 0.0206652);
      //Sector 3
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[0])->SetParameters(-0.00705374, 0.00339377);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[1])->SetParameters(-0.00659088, 0.00376459);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[2])->SetParameters(-0.00630575, 0.00490364);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[3])->SetParameters(-0.0037477, 0.00416979);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[4])->SetParameters(-0.00123477, 0.00412156);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[5])->SetParameters(-0.00029057, 0.00534505);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[6])->SetParameters(0.00193657, 0.00549643);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[7])->SetParameters(0.00230765, 0.0076423);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[8])->SetParameters(0.0037289, 0.00844072);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[9])->SetParameters(-0.000408592, 0.0146209);
      //Sector 4
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[0])->SetParameters(0.00212401, -0.00704978);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[1])->SetParameters(-0.0004114, -0.00351679);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[2])->SetParameters(0.000349446, -0.00263422);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[3])->SetParameters(0.000744761, -0.00166128);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[4])->SetParameters(0.000292732, 0.000112169);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[5])->SetParameters(0.000705017, 0.00158116);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[6])->SetParameters(0.00117538, 0.00234219);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[7])->SetParameters(0.000628487, 0.00419897);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[8])->SetParameters(-0.000135395, 0.00646489);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[9])->SetParameters(-0.0060237, 0.013437);
      //Sector 5
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[0])->SetParameters(0.00500779, -0.0113442);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[1])->SetParameters(0.0037629, -0.00784118);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[2])->SetParameters(0.00552946, -0.00779312);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[3])->SetParameters(0.00373027, -0.00486962);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[4])->SetParameters(0.00194981, -0.00201156);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[5])->SetParameters(0.000301835, 0.00120464);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[6])->SetParameters(-0.0007833, 0.00342312);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[7])->SetParameters(-0.00288491, 0.00674306);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[8])->SetParameters(-0.0039101, 0.00927813);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[9])->SetParameters(-0.00663364, 0.014917);
      //Sector 6
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[0])->SetParameters(-0.0015393, -0.000167027);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[1])->SetParameters(0.000522847, -0.00226775);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[2])->SetParameters(0.000696938, -0.00156164);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[3])->SetParameters(0.00164595, -0.00179733);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[4])->SetParameters(0.00198012, -0.00145702);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[5])->SetParameters(0.00419828, -0.00245807);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[6])->SetParameters(0.00497051, -0.00224853);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[7])->SetParameters(0.00557531, -0.00125039);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[8])->SetParameters(0.00481356, 0.000421468);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[9])->SetParameters(0.00166579, 0.00421255);
    }

    if((locRunNumber >= 54042) && (locRunNumber <= 55204)){ //g13b

      //POSITIVELY CHARGED TRACKS
      //Sector 1
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[0])->SetParameters(0.00891537, -0.00832744);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[1])->SetParameters(0.00499659, -0.00498948);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[2])->SetParameters(0.00369437, -0.00387875);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[3])->SetParameters(0.00256808, -0.00291516);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[4])->SetParameters(0.00272222, -0.00321054);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[5])->SetParameters(0.00237329, -0.00235468);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[6])->SetParameters(0.00214958, -0.00184438);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[7])->SetParameters(0.000308902, 0.000580954);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[8])->SetParameters(-0.00117692, 0.00235847);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[0])[9])->SetParameters(-0.00568936, 0.00734159);

      //Sector 2
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[0])->SetParameters(0.0107098, -0.0123305);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[1])->SetParameters(0.00635181, -0.00527339);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[2])->SetParameters(0.00487814, -0.00190607);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[3])->SetParameters(0.00433144, -0.000110079);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[4])->SetParameters(0.00288525, 0.00267699);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[5])->SetParameters(0.0016198, 0.00552779);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[6])->SetParameters(-0.000125559, 0.00813399);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[7])->SetParameters(-0.0034126, 0.0126413);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[8])->SetParameters(-0.00601249, 0.0164413);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[1])[9])->SetParameters(-0.0084906, 0.0206404);

      //Sector 3
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[0])->SetParameters(0.00627078, -0.00733196);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[1])->SetParameters(0.00552626, -0.00440814);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[2])->SetParameters(0.00348792, -0.00112953);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[3])->SetParameters(0.00128432, 0.00167887);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[4])->SetParameters(-0.00221866, 0.00615518);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[5])->SetParameters(-0.00314913, 0.00789983);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[6])->SetParameters(-0.00681491, 0.0123067);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[7])->SetParameters(-0.00783696, 0.014536);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[8])->SetParameters(-0.0115875, 0.0197153);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[2])[9])->SetParameters(-0.00840155, 0.0201074);

      //Sector 4
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[0])->SetParameters(0.00338039, -0.00846848);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[1])->SetParameters(0.00423127, -0.00653645);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[2])->SetParameters(0.00434222, -0.00525603);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[3])->SetParameters(0.00322851, -0.00324753);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[4])->SetParameters(0.00108616, 0.000289176);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[5])->SetParameters(0.00167319, 0.000727812);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[6])->SetParameters(0.000910024, 0.00261927);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[7])->SetParameters(-0.000352915, 0.00527485);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[8])->SetParameters(-0.00204891, 0.0090844);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[3])[9])->SetParameters(-0.00238021, 0.0117649);

      //Sector 5
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[0])->SetParameters(0.00211334, -0.00824808);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[1])->SetParameters(0.000121631, -0.00530191);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[2])->SetParameters(0.00126118, -0.0052333);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[3])->SetParameters(0.00277425, -0.00554644);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[4])->SetParameters(0.00362811, -0.00582051);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[5])->SetParameters(0.00417935, -0.00523709);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[6])->SetParameters(0.0044058, -0.00444829);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[7])->SetParameters(0.00433973, -0.00275497);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[8])->SetParameters(0.0051195, -0.001724);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[4])[9])->SetParameters(0.00316653, 0.00164187);

      //Sector 6
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[0])->SetParameters(0.0118398, -0.0158559);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[1])->SetParameters(0.00944784, -0.012127);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[2])->SetParameters(0.00803769, -0.00986281);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[3])->SetParameters(0.00608232, -0.00722384);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[4])->SetParameters(0.00466892, -0.00474868);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[5])->SetParameters(0.00375409, -0.00295003);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[6])->SetParameters(0.00214174, -0.000143565);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[7])->SetParameters(-0.00110527, 0.00433329);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[8])->SetParameters(-0.00233637, 0.00706256);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[0])[5])[9])->SetParameters(-0.00158419, 0.0086935);

      //NEGATIVELY CHARGED TRACKS
      //Sector 1
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[0])->SetParameters(0.00351803, -0.00694571);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[1])->SetParameters(0.00861753, -0.00913353);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[2])->SetParameters(0.0065397, -0.00603762);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[3])->SetParameters(0.00485909, -0.00363013);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[4])->SetParameters(0.003095, -0.000739809);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[5])->SetParameters(0.00149072, 0.00206944);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[6])->SetParameters(-0.00137371, 0.0063377);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[7])->SetParameters(-0.00370498, 0.00984724);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[8])->SetParameters(-0.00546548, 0.0130561);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[0])[9])->SetParameters(-0.0054761, 0.0165256);

      //Sector 2
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[0])->SetParameters(0.00322975, -0.00890204);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[1])->SetParameters(0.00329489, -0.00718907);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[2])->SetParameters(0.00337565, -0.00605142);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[3])->SetParameters(0.00328459, -0.00423726);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[4])->SetParameters(0.00142819, -0.000907621);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[5])->SetParameters(0.00120166, 0.000539718);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[6])->SetParameters(0.000223627, 0.00284755);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[7])->SetParameters(-0.00222572, 0.00728842);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[8])->SetParameters(-0.00570669, 0.0124859);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[1])[9])->SetParameters(-0.00757675, 0.0182894);

      //Sector 3
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[0])->SetParameters(-0.000989559, -0.0025269);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[1])->SetParameters(-0.00266549, -0.000863505);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[2])->SetParameters(-0.00109289, -0.00107764);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[3])->SetParameters(-1.93624e-05, -0.00088568);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[4])->SetParameters(0.00186512, -0.000606286);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[5])->SetParameters(0.00338599, -0.000637106);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[6])->SetParameters(0.00513645, -0.000607683);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[7])->SetParameters(0.00504266, 0.00177069);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[8])->SetParameters(0.00341561, 0.00545816);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[2])[9])->SetParameters(-0.0027964, 0.0132583);

      //Sector 4
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[0])->SetParameters(0.00693165, -0.012702);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[1])->SetParameters(0.00343017, -0.00739888);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[2])->SetParameters(0.00173349, -0.00427328);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[3])->SetParameters(0.00121884, -0.00203838);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[4])->SetParameters(0.00185684, -0.00107323);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[5])->SetParameters(0.00134562, 0.00139824);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[6])->SetParameters(0.000788506, 0.00353011);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[7])->SetParameters(0.000664521, 0.0050664);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[8])->SetParameters(-0.00220384, 0.00985983);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[3])[9])->SetParameters(-0.00890479, 0.0186711);

      //Sector 5
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[0])->SetParameters(0.0131089, -0.0155431);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[1])->SetParameters(0.00896296, -0.00991939);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[2])->SetParameters(0.00864612, -0.00920508);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[3])->SetParameters(0.0070706, -0.00684563);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[4])->SetParameters(0.00445014, -0.00347329);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[5])->SetParameters(0.00354548, -0.00173504);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[6])->SetParameters(0.00180288, 0.000491472);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[7])->SetParameters(0.000482227, 0.00237143);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[8])->SetParameters(-0.00185149, 0.00524772);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[4])[9])->SetParameters(-0.00511735, 0.0103121);

      //Sector 6
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[0])->SetParameters(0.000658573, -0.00539495);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[1])->SetParameters(0.00122631, -0.00568356);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[2])->SetParameters(0.00138268, -0.00484268);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[3])->SetParameters(0.00312917, -0.00555021);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[4])->SetParameters(0.0034209, -0.00440919);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[5])->SetParameters(0.00506526, -0.00494596);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[6])->SetParameters(0.00588796, -0.00462128);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[7])->SetParameters(0.00611539, -0.00299095);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[8])->SetParameters(0.00542047, -0.00123565);
      ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[1])[5])[9])->SetParameters(0.00442319, 0.0015839);
    }

    //theta dependent
    locBogdanDependentCorrFuncArray = new TObjArray(2);
    for(loc_f = 0; loc_f < 2; loc_f++){ //+/- charge
      locChargeFuncs = new TObjArray(6);
      for(loc_q = 0; loc_q < 6; loc_q++){
        locFuncName = new char[100];
        sprintf(locFuncName, "ThetaMisalignmentFunc_Charge%d_Sector%d", loc_f + 1, loc_q + 1);
        loc2DFunc = new TF2(locFuncName,"-1.0*x*x*([0] + [1]*y + [2]*y*y + [3]*y*y*y + [4]*y*y*y*y + [5]*y*y*y*y*y + [6]*y*y*y*y*y*y + [7]*y*y*y*y*y*y*y)*(y >= [8])*(y <= [9])",0.0,6.0,0.0,2.1);
        delete locFuncName;
        locChargeFuncs->AddAt(loc2DFunc, loc_q);
      }
      locBogdanDependentCorrFuncArray->AddAt(locChargeFuncs, loc_f);
    }
    dtcPCorrFuncArray->AddAt(locBogdanDependentCorrFuncArray, 2);

    if((locRunNumber >= 45512) && (locRunNumber <= 46113)){
      //POSITIVELY CHARGED TRACKS
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[0])->SetParameters(-0.0051726, 0.0582518, -0.395533, 1.37989, -2.43279, 2.22309, -1.00828, 0.179656, 0.2, 1.7);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[1])->SetParameters(0.0132735, -0.189874, 0.892678, -1.94358, 2.24721, -1.42523, 0.467323, -0.061768, 0.2, 2);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[2])->SetParameters(0.011757, -0.186562, 1.06172, -2.78191, 3.77995, -2.74802, 1.01174, -0.147889, 0.2, 1.9);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[3])->SetParameters(0.0520698, -0.548961, 2.0811, -3.84659, 3.85365, -2.138, 0.61791, -0.072525, 0.2, 1.95);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[4])->SetParameters(0.0118262, -0.11639, 0.301288, -0.0284807, -0.772757, 1.03453, -0.527701, 0.0964383, 0.2, 1.85);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[5])->SetParameters(-0.00252172, 0.0296825, -0.232591, 0.949727, -1.88905, 1.8782, -0.898523, 0.164629, 0.2, 1.75);

      //NEGATIVELY CHARGED TRACKS
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[0])->SetParameters(0.0135156, -0.207383, 1.22492, -3.6257, 5.79531, -5.0384, 2.23875, -0.3982, 0.1, 1.55);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[1])->SetParameters(-0.0102974, 0.139655, -0.595928, 1.18214, -1.26323, 0.744524, -0.2252, 0.0266957, 0.1, 1.8);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[2])->SetParameters(-0.00776626, 0.106995, -0.573639, 1.53428, -2.17792, 1.63149, -0.604941, 0.0869846, 0.1, 1.8);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[3])->SetParameters(0.00465075, -0.112792, 0.916003, -3.28644, 5.89768, -5.52955, 2.5939, -0.480793, 0.1, 1.6);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[4])->SetParameters(0.021385, -0.322182, 1.84629, -5.23491, 7.92049, -6.46559, 2.68206, -0.443204, 0.1, 1.7);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[5])->SetParameters(0.0110703, -0.166353, 0.917541, -2.60759, 4.16162, -3.67085, 1.65041, -0.293606, 0.1, 1.55);
    }
    if((locRunNumber >= 53095) && (locRunNumber < 54042)){ //g13a
      //POSITIVELY CHARGED TRACKS
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[0])->SetParameters(0.0366265, -0.306144, 0.894008, -1.11534, 0.5305, 0.0458935, -0.111657, 0.0243585, 0.25, 2);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[1])->SetParameters(-0.0361525, 0.270545, -0.916143, 1.85236, -2.22568, 1.50935, -0.527886, 0.0737106, 0.25, 2.05);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[2])->SetParameters(0.0136114, -0.174251, 0.86626, -2.03637, 2.49998, -1.63972, 0.542036, -0.0707395, 0.25, 2.05);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[3])->SetParameters(0.0461411, -0.464037, 1.64238, -2.81072, 2.60301, -1.33912, 0.36182, -0.0401791, 0.25, 2.05);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[4])->SetParameters(0.150293, -1.32197, 4.42787, -7.40387, 6.74579, -3.38111, 0.869551, -0.0888213, 0.25, 2.1);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[5])->SetParameters(0.013748, -0.170855, 0.61976, -0.923986, 0.50373, 0.0855749, -0.172411, 0.043051, 0.25, 1.85);
      //NEGATIVELY CHARGED TRACKS
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[0])->SetParameters(0.0360369, -0.444268, 2.04898, -4.79355, 6.21412, -4.46562, 1.65514, -0.246312, 0.15, 1.9);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[1])->SetParameters(-0.0297131, 0.340226, -1.28616, 2.40268, -2.51043, 1.49363, -0.473625, 0.0620671, 0.2, 1.95);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[2])->SetParameters(-0.0130333, 0.176029, -0.819464, 1.88735, -2.34688, 1.58279, -0.541954, 0.0735913, 0.15, 2);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[3])->SetParameters(-0.0122784, 0.128121, -0.541348, 1.06914, -1.05655, 0.531031, -0.124536, 0.00952708, 0.15, 1.8);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[4])->SetParameters(0.0272442, -0.298603, 1.20741, -2.52146, 2.9471, -1.9202, 0.648975, -0.0885886, 0.15, 2);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[5])->SetParameters(-0.0255461, 0.280917, -1.2977, 2.94363, -3.52193, 2.27365, -0.749249, 0.0987306, 0.2, 2.05);
    }
    if((locRunNumber >= 54042) && (locRunNumber <= 55204)){ //g13b
      //POSITIVELY CHARGED TRACKS
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[0])->SetParameters(0.0413956, -0.347936, 1.02701, -1.27423, 0.55436, 0.134564, -0.175079, 0.0372907, 0.25, 2);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[1])->SetParameters(-0.0287225, 0.246756, -0.896145, 1.8552, -2.23459, 1.50849, -0.523989, 0.0726145, 0.25, 2.05);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[2])->SetParameters(0.00971817, -0.120651, 0.630395, -1.68014, 2.37595, -1.78838, 0.675814, -0.100812, 0.25, 2.05);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[3])->SetParameters(0.0304861, -0.33694, 1.29945, -2.42998, 2.49023, -1.44509, 0.449249, -0.0582218, 0.25, 2.05);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[4])->SetParameters(0.0541669, -0.476851, 1.46674, -1.97593, 1.06617, 0.0255735, -0.217372, 0.0537799, 0.25, 2.1);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[0])[5])->SetParameters(0.0210637, -0.230209, 0.809286, -1.18739, 0.608457, 0.17186, -0.259127, 0.063338, 0.25, 1.85);
      //NEGATIVELY CHARGED TRACKS
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[0])->SetParameters(0.0246543, -0.352494, 1.7763, -4.47524, 6.14808, -4.60877, 1.76321, -0.269159, 0.15, 1.9);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[1])->SetParameters(0.0350205, -0.355161, 1.69492, -4.18713, 5.62917, -4.15004, 1.57021, -0.237872, 0.2, 1.95);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[2])->SetParameters(-0.00883149, 0.136825, -0.678481, 1.69072, -2.28065, 1.65259, -0.602232, 0.0866196, 0.15, 2);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[3])->SetParameters(0.00177449, -0.076226, 0.54188, -1.72265, 2.78191, -2.32368, 0.955632, -0.153373, 0.15, 1.8);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[4])->SetParameters(0.0331046, -0.432161, 2.06025, -4.97343, 6.57753, -4.76589, 1.76626, -0.261208, 0.15, 2);
      ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[1])[5])->SetParameters(-0.00559326, 0.0350093, -0.158533, 0.291345, -0.117223, -0.160719, 0.156325, -0.0375417, 0.2, 2.05);
    }

//LAMBDA CORR
//y is lambda, x is phi
    dtcBogdanLambdaCorrFuncArray = new TObjArray(2);
    for(loc_f = 0; loc_f < 2; loc_f++){ //+/- charge
      TObjArray *locChargeFuncs = new TObjArray(6);
      for(loc_q = 0; loc_q < 6; loc_q++){
        locFuncName = new char[100];
        sprintf(locFuncName, "BogdanLambdaCorr2DDependFunc_Charge%d_Sector%d", loc_f + 1, loc_q + 1);
        loc2DFunc = new TF2(locFuncName,"(([0] + [1]*x)*sin(y) + ([2] + [3]*x)*cos(y) + [4] + [5]*exp(-1.0*[6]*(x + [7])))*(x < 2.0)",0.0,2.1,-0.45,0.45);
        delete locFuncName;
        locChargeFuncs->AddAt(loc2DFunc, loc_q);
      }
      dtcBogdanLambdaCorrFuncArray->AddAt(locChargeFuncs, loc_f);
    }

    if((locRunNumber >= 45512) && (locRunNumber <= 46113)){
      //POSITIVELY CHARGED TRACKS
      ((TF2*)(*(TObjArray*)(*dtcBogdanLambdaCorrFuncArray)[0])[0])->SetParameters(-0.000787527, -0.00753237, -0.00710548, -0.00420913, 0.00804556, 0.0, 0.0, 0.0);
      ((TF2*)(*(TObjArray*)(*dtcBogdanLambdaCorrFuncArray)[0])[1])->SetParameters(0.00216334, -0.00823305, -0.00193322, -0.00475655, 0.00316598, 0.0, 0.0, 0.0);
      ((TF2*)(*(TObjArray*)(*dtcBogdanLambdaCorrFuncArray)[0])[2])->SetParameters(-4.97573e-05, -0.00393492, 0.0124833, -0.00184816, -0.0146224, 0.0, 0.0, 0.0);
      ((TF2*)(*(TObjArray*)(*dtcBogdanLambdaCorrFuncArray)[0])[3])->SetParameters(0.00113879, -0.00641557, 0.0099591, -0.00176928, -0.0109369, 0.0, 0.0, 0.0);
      ((TF2*)(*(TObjArray*)(*dtcBogdanLambdaCorrFuncArray)[0])[4])->SetParameters(0.00414755, -0.00708431, 0.0142652, -0.00284864, -0.0141962, 0.0, 0.0, 0.0);
      ((TF2*)(*(TObjArray*)(*dtcBogdanLambdaCorrFuncArray)[0])[5])->SetParameters(-0.00567284, -0.00108348, -0.00746564, -0.00406756, 0.0077154, 0.0, 0.0, 0.0);

      //NEGATIVELY CHARGED TRACKS
      ((TF2*)(*(TObjArray*)(*dtcBogdanLambdaCorrFuncArray)[1])[0])->SetParameters(-0.0179896, 0.0099279, -0.00328619, -0.00787018, 0.00399951, -0.0405153, 12.1453, 0.0898773);
      ((TF2*)(*(TObjArray*)(*dtcBogdanLambdaCorrFuncArray)[1])[1])->SetParameters(-0.0180206, 0.0115222, -0.00933954, -0.00529596, 0.00967564, -0.0694843, 15.9314, 0.100938);
      ((TF2*)(*(TObjArray*)(*dtcBogdanLambdaCorrFuncArray)[1])[2])->SetParameters(-0.0176382, 0.0155055, 0.0288885, -0.00193974, -0.0288399, -0.0527593, 15.2692, 0.0731635);
      ((TF2*)(*(TObjArray*)(*dtcBogdanLambdaCorrFuncArray)[1])[3])->SetParameters(-0.0148866, 0.00794703, 0.014874, -0.00161077, -0.0143715, -0.0529386, 12.5911, 0.11087);
      ((TF2*)(*(TObjArray*)(*dtcBogdanLambdaCorrFuncArray)[1])[4])->SetParameters(-0.0190835, 0.00747674, 0.0300979, 0.0, -0.0308202, -0.0129371, 8.03937, 0.109086);
      ((TF2*)(*(TObjArray*)(*dtcBogdanLambdaCorrFuncArray)[1])[5])->SetParameters(-0.0318762, 0.0251708, 0.0143925, -0.00591179, -0.0144847, -0.0146763, 9.432, 0.0830534);
    }
//PHI CORR
//y is lambda, x is phi
    dtcBogdanPhiCorrFuncArray = new TObjArray(2);
    for(loc_f = 0; loc_f < 2; loc_f++){ //+/- charge
      TObjArray *locChargeFuncs = new TObjArray(6);
      for(loc_q = 0; loc_q < 6; loc_q++){
        locFuncName = new char[100];
        sprintf(locFuncName, "BogdanPhiCorr2DDependFunc_Charge%d_Sector%d", loc_f + 1, loc_q + 1);
        loc2DFunc = new TF2(locFuncName,"(([0] + [1]*y)*cos(x) + ([2] + [3]*y)*sin(x) + [4])*(x < [5])",0.0,2.1,-0.45,0.45);
        delete locFuncName;
        locChargeFuncs->AddAt(loc2DFunc, loc_q);
      }
      dtcBogdanPhiCorrFuncArray->AddAt(locChargeFuncs, loc_f);
    }

    if((locRunNumber >= 45512) && (locRunNumber <= 46113)){
      //POSITIVELY CHARGED TRACKS
      ((TF2*)(*(TObjArray*)(*dtcBogdanPhiCorrFuncArray)[0])[0])->SetParameters(0.00171091, 0.00538017, 0.00424165, -0.000707422, -0.00389457, 2.0);
      ((TF2*)(*(TObjArray*)(*dtcBogdanPhiCorrFuncArray)[0])[1])->SetParameters(1.09972e-05, 0.0112006, 0.00138409, 0.00320378, 0.000641203, 2.0);
      ((TF2*)(*(TObjArray*)(*dtcBogdanPhiCorrFuncArray)[0])[2])->SetParameters(-0.00249204, 0.0152177, -0.00149701, -7.01866e-05, 0.00433363, 2.0);
      ((TF2*)(*(TObjArray*)(*dtcBogdanPhiCorrFuncArray)[0])[3])->SetParameters(-0.00151991, 0.00810956, -0.00077116, 0.00456, 0.00180357, 2.0);
      ((TF2*)(*(TObjArray*)(*dtcBogdanPhiCorrFuncArray)[0])[4])->SetParameters(-0.00193573, 0.0138019, -0.00250587, 0.0013756, 0.00165289, 2.0);
      ((TF2*)(*(TObjArray*)(*dtcBogdanPhiCorrFuncArray)[0])[5])->SetParameters(-0.0029946, 0.0107688, -0.00103903, 0.0031133, 0.00134087, 2.0);

      //NEGATIVELY CHARGED TRACKS
      ((TF2*)(*(TObjArray*)(*dtcBogdanPhiCorrFuncArray)[1])[0])->SetParameters(-0.000611416, 0.010208, 0.000241418, -0.0090126, 0.00070669, 1.7);
      ((TF2*)(*(TObjArray*)(*dtcBogdanPhiCorrFuncArray)[1])[1])->SetParameters(-0.00228109, 0.00673076, 0.00241599, -0.00230879, 0.00136865, 1.4);
      ((TF2*)(*(TObjArray*)(*dtcBogdanPhiCorrFuncArray)[1])[2])->SetParameters(-0.0043446, -0.00667052, 0.000252745, 0.00339905, 0.00391922, 1.3);
      ((TF2*)(*(TObjArray*)(*dtcBogdanPhiCorrFuncArray)[1])[3])->SetParameters(-0.00155417, 0.00234569, 0.000693408, -0.0101061, 0.00149892, 1.5);
      ((TF2*)(*(TObjArray*)(*dtcBogdanPhiCorrFuncArray)[1])[4])->SetParameters(0.000910176, 0.00465841, 0.000634919, -0.00533051, -0.001711, 1.8);
      ((TF2*)(*(TObjArray*)(*dtcBogdanPhiCorrFuncArray)[1])[5])->SetParameters(-0.00361921, -0.00175741, -0.00352873, 0.00325473, 0.0041403, 1.5);
    }
//D0 CORR
/* //x is phi corr, y is phi orig, z is d0 orig
    dtcBogdanD0CorrFuncArray = new TObjArray(2);
    for(loc_f = 0; loc_f < 2; loc_f++){ //+/- charge
      TObjArray *locChargeFuncs = new TObjArray(6);
      for(loc_q = 0; loc_q < 6; loc_q++){
        locFuncName = new char[100];
        sprintf(locFuncName, "BogdanD0CorrFunc_Charge%d_Sector%d", loc_f + 1, loc_q + 1);
        loc3DFunc = new TF3(locFuncName,"((sin(x)/sin(y) - 1.0)*z - [0]*sin(x) + [1]*cos(x))*(x <= [2])",0.0,3.2,0.0,3.2,-100.0,100.0);
        delete locFuncName;
        locChargeFuncs->AddAt(loc3DFunc, loc_q);
      }
      dtcBogdanD0CorrFuncArray->AddAt(locChargeFuncs, loc_f);
    }

    //POSITIVELY CHARGED TRACKS
    //NEGATIVELY CHARGED TRACKS */

/* //Z0 CORR
//y is lambda, x is phi
    dtcBogdanZ0CorrFuncArray = new TObjArray(2);
    for(loc_f = 0; loc_f < 2; loc_f++){ //+/- charge
      TObjArray *locChargeFuncs = new TObjArray(6);
      for(loc_q = 0; loc_q < 6; loc_q++){
        locFuncName = new char[100];
        sprintf(locFuncName, "BogdanZ0CorrFunc_Charge%d_Sector%d", loc_f + 1, loc_q + 1);
        loc2DFunc = new TF2(locFuncName,"[0] - [1]*tan(y)/sin(x)",0.0,3.2,-0.55,0.55);
        delete locFuncName;
        locChargeFuncs->AddAt(loc2DFunc, loc_q);
      }
      dtcBogdanZ0CorrFuncArray->AddAt(locChargeFuncs, loc_f);
    }

    //POSITIVELY CHARGED TRACKS
    //NEGATIVELY CHARGED TRACKS */

  } //end eg3 corrections
}

double Correct_dtcTrackMomentum(int locRunNumber, int locID, const TLorentzVector &locP4){
  return Correct_dtcTrackMomentum(locRunNumber, locID, Calc_dtfSector(locP4), locP4);
}

double Correct_dtcTrackMomentum(int locRunNumber, int locID, int locSector, const TLorentzVector &locP4){
//locID is the particle's PDG ID (seb ID).
//This function assumes you have already corrected for eloss in the target.
//If you want to correct the track angles as well, call this function first (for eg3).
//FOR eg3: YOU MUST CORRECT FOR ELOSS FIRST!!! FOR g13: YOU MUST CORRECT FOR THIS FIRST!!!

  double locInputP = locP4.P();
  double locLabTheta = locP4.Theta();
  double locSectorNormLabPhi = Calc_dtfSectorNormLabPhi(locP4.Vect(), locSector);

  double locPCorrected = locInputP;
  if((locRunNumber >= 45512) && (locRunNumber <= 46113)){
    if(dtcPCorrFuncArray == NULL){
      cout << "WARNING: MOMENTUM CORRECTIONS NOT SETUP, CORRECTIONS NOT PERFORMED." << endl;
      return locPCorrected;
    }

    int locQIndex;
    if((locID == 2212) || (locID == 211) || (locID == 321)) //proton, pi+, k+
      locQIndex = 0;
    else if((locID == -211) || (locID == -321))
      locQIndex = 1;
    else{return locPCorrected;} //no pcorrs for particle

    int locPhiBin = int(floor((locSectorNormLabPhi + 0.5236)/0.08727));

    int locMassIndex;
    if(locID == 2212) //proton only
      locMassIndex = 0;
    else
      locMassIndex = 1;

    locPCorrected += ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[locMassIndex])[locSector - 1])->Eval(locInputP);
    if((locPhiBin >= 1) && (locPhiBin <= 10))
      locPCorrected += ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[locQIndex])[locSector - 1])[locPhiBin - 1])->Eval(locInputP);
    locPCorrected += ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[locQIndex])[locSector - 1])->Eval(locInputP, locLabTheta);
  } //end eg3 corrections

  if((locRunNumber >= 53095) && (locRunNumber <= 55204)){ //g13 corrs
    if(dtcPCorrFuncArray == NULL){
      cout << "WARNING: MOMENTUM CORRECTIONS NOT SETUP, CORRECTIONS NOT PERFORMED." << endl;
      return locPCorrected;
    }

    int locQIndex;
    if((locID == 2212) || (locID == 211) || (locID == 321)) //proton, pi+, k+
      locQIndex = 0;
    else if((locID == -211) || (locID == -321))
      locQIndex = 1;
    else{return locPCorrected;} //no pcorrs for particle

    int locPhiBin = int(floor((locSectorNormLabPhi + 0.5236)/0.08727)); //returns a num from 0 to 11, only want 1-10

    int locMassIndex;
    if(locID == 2212) //proton only
      locMassIndex = 0;
    else
      locMassIndex = 1;

    locPCorrected += ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[0])[locMassIndex])[locSector - 1])->Eval(locInputP);
    if((locPhiBin >= 1) && (locPhiBin <= 10))
      locPCorrected += ((TF1*)(*(TObjArray*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[1])[locQIndex])[locSector - 1])[locPhiBin - 1])->Eval(locInputP);
    locPCorrected += ((TF2*)(*(TObjArray*)(*(TObjArray*)(*dtcPCorrFuncArray)[2])[locQIndex])[locSector - 1])->Eval(locInputP, locLabTheta);
  } //end g13 corrections

  return locPCorrected;
}

void Correct_dtcTrackAngles(int locRunNumber, int locID, int locSector, double &locBogdanLambda, double &locBogdanPhi){
  double locBogdanLambdaOrig = locBogdanLambda;
  double locBogdanPhiOrig = locBogdanPhi;
  if((locRunNumber >= 45512) && (locRunNumber <= 46113)){

    if((dtcBogdanLambdaCorrFuncArray == NULL) || (dtcBogdanPhiCorrFuncArray == NULL)){
      cout << "WARNING: ANGLE CORRECTIONS NOT SETUP, CORRECTIONS NOT PERFORMED." << endl;
      return;
    }

    int locQIndex;
//    if((locID == 2212) || (locID == 211) || (locID == 321)) //proton, piplus, or kplus
    if(locID == 2212) //proton
      locQIndex = 0;
//    else if((locID == -211) || (locID == -321)) //piminus or kminus
    else if(locID == -211) //piminus
      locQIndex = 1;
    else{
//      cout << "WARNING: ANGLE CORRECTIONS NOT SETUP FOR THIS PARTICLE, CORRECTIONS NOT PERFORMED." << endl;
      return;
    }

    locBogdanLambda += ((TF2*)(*(TObjArray*)(*dtcBogdanLambdaCorrFuncArray)[locQIndex])[locSector - 1])->Eval(locBogdanPhiOrig, locBogdanLambdaOrig);
    locBogdanPhi += ((TF2*)(*(TObjArray*)(*dtcBogdanPhiCorrFuncArray)[locQIndex])[locSector - 1])->Eval(locBogdanPhiOrig, locBogdanLambdaOrig);
  }
}

void Correct_dtcTrackLocation(int locRunNumber, int locID, int locSector, const vector<double> &locBogdanParamsOrig, vector<double> &locBogdanParamsOrigCorr){
  if((locRunNumber >= 45512) && (locRunNumber <= 46113)){
    //easier to read
    double locLambdaOrig = locBogdanParamsOrig[1];
    double locPhiOrig = locBogdanParamsOrig[2];
    double locLambdaCorr = locBogdanParamsOrigCorr[1];
    double locPhiCorr = locBogdanParamsOrigCorr[2];

    double locR = 110.9342; //locR = the radius of the circle defined by the curving front end of the dc region 1, superlayer 1
    double locA = 53.0449;  //locA = the distance from the center of the circle to the beamline //in eq, understood to be pos for ytrk_center < 0
    double locB = -0.0003;  //locB = the distance along xtrk from the center of the circle to xtrk = 0 //in eq, understood to be pos for xtrk_center > 0

    double locXtrk = -1.0*locBogdanParamsOrig[3]/sin(locPhiOrig); //the xtrk of the track when ytrk = 0.

    //locXDCFlatPlane = the xtrk point the track would hit the DC if it were flat (not curved in front)
    double locXDCFlatPlane = locXtrk + (locR - locA)/tan(locPhiCorr);
    double locL; //distance along the track from the region 1 (superlayer 1) dc hit to the ytrk = 0 point on the track
    if(locXDCFlatPlane <= locB) //hit the flat plane
      locL = (locR - locA)/(cos(locLambdaCorr)*sin(locPhiCorr));
    else //hit the curved plane, messy:
      locL = ((locB - locXtrk)*cos(locPhiCorr) - locA*sin(locPhiCorr) + sqrt(locR*locR - (locA*cos(locPhiCorr) + (locB - locXtrk)*sin(locPhiCorr))*(locA*cos(locPhiCorr) + (locB - locXtrk)*sin(locPhiCorr))))/cos(locLambdaCorr);
    double locDeltaLambda = locLambdaCorr - locLambdaOrig;
    double locDeltaPhi = locPhiCorr - locPhiOrig;
    double locDistLambda = locL*sqrt(2.0 - 2.0*cos(locDeltaLambda));
    if(locDeltaLambda < 0.0)
      locDistLambda *= -1.0;
    double locDistPhi = locL*sqrt(2.0 - 2.0*cos(locDeltaPhi));
    if(locDeltaPhi < 0.0)
      locDistPhi *= -1.0;
    locBogdanParamsOrigCorr[3] = locL*cos(locLambdaOrig)*sin(locPhiOrig)*cos(locPhiCorr) - locXtrk*sin(locPhiCorr) - locL*cos(locLambdaOrig)*cos(locPhiOrig)*sin(locPhiCorr);
    locBogdanParamsOrigCorr[4] = locBogdanParamsOrig[4] + locL*sin(locLambdaOrig) - locL*cos(locLambdaOrig)*sin(locPhiOrig)*tan(locLambdaCorr)/sin(locPhiCorr);
  }
}

double Correct_dtcPhotonEnergy(int locRunNumber, double locPhotonEnergy, int locDetectID){
  if((locRunNumber >= 45512) && (locRunNumber <= 46113))
    locPhotonEnergy += 0.00771;

  if((locRunNumber >= 53164) && (locRunNumber <= 54036)){ //g13a (NO LH2!! //or = 1)
    int locBin = dtcBeamECorrHist1->GetXaxis()->FindBin(locRunNumber);
    double locCorrFactor = dtcBeamECorrHist1->GetBinContent(locBin);
    if(locCorrFactor < 0.1) //no entry for run
      locCorrFactor = 1.0;
    locPhotonEnergy *= locCorrFactor;
  }

  if((locRunNumber >= 54042) && (locRunNumber <= 55140)){ //g13b (NO LH2!! //or = 1)
    int locBin = dtcBeamECorrHist2->GetXaxis()->FindBin(locRunNumber);
    double locCorrFactor = dtcBeamECorrHist2->GetBinContent(locBin);
    locPhotonEnergy *= locCorrFactor;
  }
  return locPhotonEnergy;
}


double Correct_dtcPhotonEnergy_TaggerCalib(int locRunNumber, double locPhotonEnergy, int locDetectID){
return locPhotonEnergy;
/*  if((locDetectID <= 0) || (locDetectID > 767)){
    cout << "ERROR: DETECT ID INVALID IN Correct_dtcPhotonEnergy_TaggerCalib.  PHOTON ENERGY NOT CORRECTED" << endl;
    return locPhotonEnergy;
  }
  vector<double> locECorrectFactor;
  string locRunIndex = getenv("CLAS_CALDB_RUNINDEX");
  if(!DecayCaldbServer::Get_DecayCaldbServer().Get_ConnectionStatus())
    DecayCaldbServer::Get_DecayCaldbServer().Connect("clasdb.jlab.org", "clasuser", "");
  Get_dcsValues<double>("TAG_CALIB", "tag_e", "ecor", locRunIndex, locRunNumber, 767, locECorrectFactor);
  if(locECorrectFactor.size() != 767){
    cout << "ERROR: DecayCaldbServer::Get_Values FAILED IN Correct_dtcPhotonEnergy_TaggerCalib.  PHOTON ENERGY NOT CORRECTED" << endl;
    return locPhotonEnergy;
  }
  return locPhotonEnergy*locECorrectFactor[locDetectID - 1];
*/
}

void Setup_dtcSCPaddleMap(int locRunNumber){
  int loc_f, loc_q, loc_l;
  TObjArray *locPanelFuncArray, *locVertZFuncArray;
  TF1 *loc1DFunc;
  ostringstream locFuncName;

  if((locRunNumber >= 53333) && (locRunNumber <= 53862)){

    if(dtcSCPaddleMatchingPositivesFuncArray != NULL) //functions already created
      return;

    //POSITIVES
    dtcSCPaddleMatchingPositivesFuncArray = new TObjArray(4);
    for(loc_l = 0; loc_l < 4; loc_l++){ //vertz
      locVertZFuncArray = new TObjArray(8);
      for(loc_f = 0; loc_f < 8; loc_f++){ //pbins
        locPanelFuncArray = new TObjArray(4);
        for(loc_q = 0; loc_q < 4; loc_q++){ //panel (roughly)
          locFuncName.str("");
          locFuncName << "SCPaddleMap_Pos_ZBin" << (loc_l + 1) << "_PBin" << (loc_f + 1) << "_Panel" << (loc_q + 1);
          loc1DFunc = new TF1(locFuncName.str().c_str(),"[0] + [1]*x + [2]*x*x", 0.5, 48.5); //panel ranges are smaller, but doesn't matter here
          locPanelFuncArray->AddAt(loc1DFunc, loc_q);
        }
        locVertZFuncArray->AddAt(locPanelFuncArray, loc_f);
      }
      dtcSCPaddleMatchingPositivesFuncArray->AddAt(locVertZFuncArray, loc_l);
    }

    //POSITIVES
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[0])[0])->SetParameters(0.375451, 0.0178835, 0.000210843);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[0])[1])->SetParameters(0.591496, -0.00383418, 0.000740874);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[0])[2])->SetParameters(-0.0990929, 0.0417272, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[0])[3])->SetParameters(-2.58194, 0.104485, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[1])[0])->SetParameters(0.306515, 0.0214474, 0.00013105);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[1])[1])->SetParameters(0.58554, -0.00654045, 0.000803491);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[1])[2])->SetParameters(-0.18358, 0.043283, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[1])[3])->SetParameters(-2.66922, 0.105925, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[2])[0])->SetParameters(0.288165, 0.0202574, 0.000182742);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[2])[1])->SetParameters(0.523211, -0.00399974, 0.000768869);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[2])[2])->SetParameters(-0.169154, 0.042458, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[2])[3])->SetParameters(-2.67609, 0.105925, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[3])[0])->SetParameters(0.262128, 0.0211932, 0.00016566);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[3])[1])->SetParameters(0.502461, -0.00434469, 0.000792975);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[3])[2])->SetParameters(-0.168391, 0.042458, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[3])[3])->SetParameters(-2.67533, 0.105925, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[4])[0])->SetParameters(0.243771, 0.0219047, 0.000152375);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[4])[1])->SetParameters(0.506859, -0.00434469, 0.000792975);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[4])[2])->SetParameters(-0.163993, 0.042458, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[4])[3])->SetParameters(-2.67093, 0.105925, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[5])[0])->SetParameters(0.230549, 0.0221075, 0.000165396);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[5])[1])->SetParameters(0.505595, -0.00434469, 0.000792975);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[5])[2])->SetParameters(-0.165258, 0.042458, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[5])[3])->SetParameters(-2.67219, 0.105925, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[6])[0])->SetParameters(0.210265, 0.0240898, 9.1647e-05);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[6])[1])->SetParameters(0.491167, -0.00434469, 0.000792975);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[6])[2])->SetParameters(-0.179686, 0.042458, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[6])[3])->SetParameters(-2.68662, 0.105925, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[7])[0])->SetParameters(0.208659, 0.0231522, 0.000134268);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[7])[1])->SetParameters(0.491064, -0.00434469, 0.000792975);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[7])[2])->SetParameters(-0.179788, 0.042458, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[0])[7])[3])->SetParameters(-2.68672, 0.105925, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[0])[0])->SetParameters(0.380167, 0.0184725, 0.000200382);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[0])[1])->SetParameters(0.589793, -0.00305663, 0.000734025);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[0])[2])->SetParameters(-0.101174, 0.0422621, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[0])[3])->SetParameters(-2.43787, 0.101485, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[1])[0])->SetParameters(0.310577, 0.0222104, 0.000113482);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[1])[1])->SetParameters(0.575872, -0.00532453, 0.000791226);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[1])[2])->SetParameters(-0.174649, 0.0435389, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[1])[3])->SetParameters(-2.57295, 0.10405, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[2])[0])->SetParameters(0.294796, 0.0205342, 0.000181106);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[2])[1])->SetParameters(0.491176, -0.00116882, 0.000728055);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[2])[2])->SetParameters(-0.129612, 0.0418761, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[2])[3])->SetParameters(-2.58549, 0.10405, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[3])[0])->SetParameters(0.267998, 0.0215613, 0.000159929);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[3])[1])->SetParameters(0.456985, -0.000158423, 0.000720611);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[3])[2])->SetParameters(-0.135501, 0.0418761, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[3])[3])->SetParameters(-2.59137, 0.10405, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[4])[0])->SetParameters(0.248393, 0.0224201, 0.000144702);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[4])[1])->SetParameters(0.460943, -0.000158423, 0.000720611);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[4])[2])->SetParameters(-0.131542, 0.0418761, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[4])[3])->SetParameters(-2.58742, 0.10405, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[5])[0])->SetParameters(0.235337, 0.0225146, 0.000159645);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[5])[1])->SetParameters(0.458358, -0.000158423, 0.000720611);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[5])[2])->SetParameters(-0.134127, 0.0418761, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[5])[3])->SetParameters(-2.59, 0.10405, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[6])[0])->SetParameters(0.224001, 0.0226074, 0.000179256);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[6])[1])->SetParameters(0.460034, -0.000158423, 0.000720611);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[6])[2])->SetParameters(-0.132451, 0.0418761, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[6])[3])->SetParameters(-2.58832, 0.10405, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[7])[0])->SetParameters(0.213466, 0.023356, 0.000144968);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[7])[1])->SetParameters(0.448156, -0.000158423, 0.000720611);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[7])[2])->SetParameters(-0.14433, 0.0418761, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[1])[7])[3])->SetParameters(-2.6002, 0.10405, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[0])[0])->SetParameters(0.363025, 0.0225599, 8.39314e-05);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[0])[1])->SetParameters(0.603683, -0.00330929, 0.000747254);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[0])[2])->SetParameters(-0.102905, 0.0428773, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[0])[3])->SetParameters(-2.66731, 0.107675, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[1])[0])->SetParameters(0.319792, 0.0224896, 0.000112);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[1])[1])->SetParameters(0.568428, -0.00411508, 0.000779698);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[1])[2])->SetParameters(-0.166418, 0.0438981, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[1])[3])->SetParameters(-2.72514, 0.108432, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[2])[0])->SetParameters(0.304801, 0.0207048, 0.000181018);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[2])[1])->SetParameters(0.459869, 0.00165038, 0.000689762);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[2])[2])->SetParameters(-0.132544, 0.0425542, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[2])[3])->SetParameters(-2.7347, 0.108432, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[3])[0])->SetParameters(0.276167, 0.0217759, 0.00016409);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[3])[1])->SetParameters(0.262659, 0.0148977, 0.000454574);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[3])[2])->SetParameters(-0.150434, 0.0425542, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[3])[3])->SetParameters(-2.75259, 0.108432, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[4])[0])->SetParameters(0.257032, 0.0223822, 0.000159754);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[4])[1])->SetParameters(0.270105, 0.0148977, 0.000454574);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[4])[2])->SetParameters(-0.142988, 0.0425542, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[4])[3])->SetParameters(-2.74515, 0.108432, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[5])[0])->SetParameters(0.243354, 0.0225119, 0.000177211);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[5])[1])->SetParameters(0.269114, 0.0148977, 0.000454574);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[5])[2])->SetParameters(-0.143979, 0.0425542, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[5])[3])->SetParameters(-2.74614, 0.108432, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[6])[0])->SetParameters(0.230155, 0.0231709, 0.000162242);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[6])[1])->SetParameters(0.263137, 0.0148977, 0.000454574);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[6])[2])->SetParameters(-0.149956, 0.0425542, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[6])[3])->SetParameters(-2.75212, 0.108432, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[7])[0])->SetParameters(0.217923, 0.0239899, 0.000138687);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[7])[1])->SetParameters(0.257142, 0.0148977, 0.000454574);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[7])[2])->SetParameters(-0.155951, 0.0425542, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[2])[7])[3])->SetParameters(-2.75811, 0.108432, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[0])[0])->SetParameters(0.367507, 0.0227888, 9.55477e-05);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[0])[1])->SetParameters(0.62109, -0.00372395, 0.000760118);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[0])[2])->SetParameters(-0.0937902, 0.0431391, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[0])[3])->SetParameters(-2.61715, 0.106919, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[1])[0])->SetParameters(0.324994, 0.0232335, 9.40298e-05);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[1])[1])->SetParameters(0.546578, -0.00190086, 0.000749306);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[1])[2])->SetParameters(-0.122294, 0.0432434, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[1])[3])->SetParameters(-2.72178, 0.108787, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[2])[0])->SetParameters(0.310322, 0.0211846, 0.00017563);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[2])[1])->SetParameters(0.447812, 0.00313023, 0.000672666);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[2])[2])->SetParameters(-0.156777, 0.0437531, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[2])[3])->SetParameters(-2.72562, 0.108787, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[3])[0])->SetParameters(0.281477, 0.0223222, 0.000154871);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[3])[1])->SetParameters(0.32168, 0.0113686, 0.000524851);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[3])[2])->SetParameters(-0.170881, 0.0437531, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[3])[3])->SetParameters(-2.73972, 0.108787, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[4])[0])->SetParameters(0.262383, 0.0228229, 0.00015609);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[4])[1])->SetParameters(0.327913, 0.0113686, 0.000524851);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[4])[2])->SetParameters(-0.164649, 0.0437531, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[4])[3])->SetParameters(-2.73349, 0.108787, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[5])[0])->SetParameters(0.246925, 0.0231772, 0.000165491);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[5])[1])->SetParameters(0.325971, 0.0113686, 0.000524851);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[5])[2])->SetParameters(-0.16659, 0.0437531, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[5])[3])->SetParameters(-2.73543, 0.108787, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[6])[0])->SetParameters(0.233799, 0.0236248, 0.000166871);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[6])[1])->SetParameters(0.324125, 0.0113686, 0.000524851);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[6])[2])->SetParameters(-0.168436, 0.0437531, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[6])[3])->SetParameters(-2.73728, 0.108787, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[7])[0])->SetParameters(0.222609, 0.0245756, 0.000114485);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[7])[1])->SetParameters(0.30635, 0.0113686, 0.000524851);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[7])[2])->SetParameters(-0.186211, 0.0437531, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[3])[7])[3])->SetParameters(-2.75505, 0.108787, 0.0);



    //NEGATIVES
    dtcSCPaddleMatchingNegativesFuncArray = new TObjArray(4);
    for(loc_l = 0; loc_l < 4; loc_l++){ //vertz
      locVertZFuncArray = new TObjArray(8);
      for(loc_f = 0; loc_f < 8; loc_f++){ //pbins
        locPanelFuncArray = new TObjArray(4);
        for(loc_q = 0; loc_q < 4; loc_q++){ //panel (roughly)
          locFuncName.str("");
          locFuncName << "SCPaddleMap_Neg_ZBin" << (loc_l + 1) << "_PBin" << (loc_f + 1) << "_Panel" << (loc_q + 1);
          loc1DFunc = new TF1(locFuncName.str().c_str(),"[0] + [1]*x + [2]*x*x", 0.5, 48.5); //panel ranges are smaller, but doesn't matter here
          locPanelFuncArray->AddAt(loc1DFunc, loc_q);
        }
        locVertZFuncArray->AddAt(locPanelFuncArray, loc_f);
      }
      dtcSCPaddleMatchingNegativesFuncArray->AddAt(locVertZFuncArray, loc_l);
    }

    //NEGATIVES
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[0])[0])->SetParameters(-1.67691, 0.110599, -0.000911224);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[0])[1])->SetParameters(-1.67691, 0.110599, -0.000911224);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[0])[2])->SetParameters(-0.606084, 0.0481797, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[0])[3])->SetParameters(-3.33991, 0.116877, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[1])[0])->SetParameters(-1.193, 0.127958, -0.00220393);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[1])[1])->SetParameters(-0.532349, 0.0498396, -4.09992e-05);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[1])[2])->SetParameters(-0.392205, 0.0443934, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[1])[3])->SetParameters(-2.73122, 0.103798, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[2])[0])->SetParameters(-0.409866, 0.0649836, -0.000827051);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[2])[1])->SetParameters(-0.0540321, 0.0206185, 0.000424883);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[2])[2])->SetParameters(-0.398037, 0.0452408, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[2])[3])->SetParameters(-2.74828, 0.104644, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[3])[0])->SetParameters(-0.36398, 0.0662988, -0.000924215);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[3])[1])->SetParameters(-0.107078, 0.0268664, 0.000307118);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[3])[2])->SetParameters(-0.316673, 0.0435534, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[3])[3])->SetParameters(-3.2405, 0.117187, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[4])[0])->SetParameters(-0.221471, 0.0546533, -0.00065339);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[4])[1])->SetParameters(0.0345528, 0.0189361, 0.000426858);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[4])[2])->SetParameters(-0.392224, 0.0459049, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[4])[3])->SetParameters(-3.20787, 0.117187, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[5])[0])->SetParameters(-0.14766, 0.0481129, -0.000472859);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[5])[1])->SetParameters(0.167504, 0.0109211, 0.000550414);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[5])[2])->SetParameters(-0.384309, 0.0459049, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[5])[3])->SetParameters(-3.19995, 0.117187, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[6])[0])->SetParameters(-0.113075, 0.0461968, -0.000441255);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[6])[1])->SetParameters(0.168255, 0.0109211, 0.000550414);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[6])[2])->SetParameters(-0.383558, 0.0459049, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[6])[3])->SetParameters(-3.1992, 0.117187, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[7])[0])->SetParameters(-0.0869095, 0.0446712, -0.000419004);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[7])[1])->SetParameters(0.170857, 0.0109211, 0.000550414);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[7])[2])->SetParameters(-0.380956, 0.0459049, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[0])[7])[3])->SetParameters(-3.1966, 0.117187, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[0])[0])->SetParameters(-0.865805, 0.0601038, -0.000114649);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[0])[1])->SetParameters(-0.865805, 0.0601038, -0.000114649);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[0])[2])->SetParameters(-0.602086, 0.0485529, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[0])[3])->SetParameters(-3.31227, 0.116646, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[1])[0])->SetParameters(-1.17523, 0.124875, -0.00208887);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[1])[1])->SetParameters(-0.587788, 0.053749, -9.44251e-05);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[1])[2])->SetParameters(-0.402813, 0.0451631, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[1])[3])->SetParameters(-2.683, 0.103034, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[2])[0])->SetParameters(-0.426708, 0.0665946, -0.000852996);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[2])[1])->SetParameters(-0.0804301, 0.0225003, 0.000406693);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[2])[2])->SetParameters(-0.425274, 0.046451, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[2])[3])->SetParameters(-2.71111, 0.104404, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[3])[0])->SetParameters(-0.366913, 0.0665473, -0.000912248);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[3])[1])->SetParameters(-0.0730796, 0.0247816, 0.000354048);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[3])[2])->SetParameters(-0.339834, 0.0446893, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[3])[3])->SetParameters(-2.78096, 0.106349, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[4])[0])->SetParameters(-0.218055, 0.0542531, -0.000621635);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[4])[1])->SetParameters(0.0120172, 0.0209791, 0.000399176);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[4])[2])->SetParameters(-0.245081, 0.0423146, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[4])[3])->SetParameters(-2.77444, 0.106349, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[5])[0])->SetParameters(-0.145551, 0.0479606, -0.000448807);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[5])[1])->SetParameters(0.224339, 0.00669312, 0.000646117);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[5])[2])->SetParameters(-0.23556, 0.0423146, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[5])[3])->SetParameters(-2.76492, 0.106349, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[6])[0])->SetParameters(-0.109045, 0.0458864, -0.000413136);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[6])[1])->SetParameters(0.227024, 0.00669312, 0.000646117);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[6])[2])->SetParameters(-0.232875, 0.0423146, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[6])[3])->SetParameters(-2.76223, 0.106349, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[7])[0])->SetParameters(-0.069423, 0.0420306, -0.000301586);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[7])[1])->SetParameters(0.237638, 0.00669312, 0.000646117);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[7])[2])->SetParameters(-0.222262, 0.0423146, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[1])[7])[3])->SetParameters(-2.75162, 0.106349, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[0])[0])->SetParameters(-0.971302, 0.0664922, -0.00019677);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[0])[1])->SetParameters(-0.971302, 0.0664922, -0.00019677);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[0])[2])->SetParameters(-0.629876, 0.0498408, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[0])[3])->SetParameters(-3.11074, 0.112412, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[1])[0])->SetParameters(-1.19889, 0.126563, -0.00210694);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[1])[1])->SetParameters(-0.611173, 0.0555666, -0.000112652);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[1])[2])->SetParameters(-0.416266, 0.0460605, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[1])[3])->SetParameters(-2.74768, 0.10515, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[2])[0])->SetParameters(-0.552702, 0.0782347, -0.00110636);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[2])[1])->SetParameters(-0.114409, 0.0248318, 0.000383743);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[2])[2])->SetParameters(-0.395588, 0.0462206, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[2])[3])->SetParameters(-2.54139, 0.100945, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[3])[0])->SetParameters(-0.374391, 0.0673875, -0.000916117);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[3])[1])->SetParameters(-0.089416, 0.0261075, 0.000345889);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[3])[2])->SetParameters(-0.347379, 0.0454699, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[3])[3])->SetParameters(-2.53866, 0.100945, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[4])[0])->SetParameters(-0.231041, 0.0559568, -0.000653072);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[4])[1])->SetParameters(0.0101846, 0.0212321, 0.000411435);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[4])[2])->SetParameters(-0.29516, 0.0443546, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[4])[3])->SetParameters(-2.53049, 0.100945, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[5])[0])->SetParameters(-0.157848, 0.0497702, -0.000485416);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[5])[1])->SetParameters(0.0714795, 0.0185861, 0.00043538);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[5])[2])->SetParameters(-0.299322, 0.0443546, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[5])[3])->SetParameters(-2.53465, 0.100945, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[6])[0])->SetParameters(-0.125536, 0.0484012, -0.000473907);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[6])[1])->SetParameters(0.0729661, 0.0185861, 0.00043538);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[6])[2])->SetParameters(-0.297836, 0.0443546, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[6])[3])->SetParameters(-2.53317, 0.100945, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[7])[0])->SetParameters(-0.0907084, 0.0457013, -0.00040986);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[7])[1])->SetParameters(0.0797143, 0.0185861, 0.00043538);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[7])[2])->SetParameters(-0.291087, 0.0443546, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[2])[7])[3])->SetParameters(-2.52642, 0.100945, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[0])[0])->SetParameters(-1.55484, 0.103478, -0.000769908);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[0])[1])->SetParameters(-1.55484, 0.103478, -0.000769908);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[0])[2])->SetParameters(-0.645703, 0.050733, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[0])[3])->SetParameters(-3.26209, 0.11647, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[1])[0])->SetParameters(-1.17255, 0.123098, -0.00199887);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[1])[1])->SetParameters(-0.641529, 0.0576667, -0.000134893);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[1])[2])->SetParameters(-0.429931, 0.0468953, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[1])[3])->SetParameters(-2.74869, 0.105683, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[2])[0])->SetParameters(-0.40721, 0.064713, -0.000782166);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[2])[1])->SetParameters(-0.144002, 0.0267263, 0.00036834);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[2])[2])->SetParameters(-0.400959, 0.0468744, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[2])[3])->SetParameters(-2.81303, 0.107899, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[3])[0])->SetParameters(-0.37501, 0.0674218, -0.000900967);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[3])[1])->SetParameters(-0.126427, 0.0288033, 0.00031313);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[3])[2])->SetParameters(-0.352571, 0.0461131, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[3])[3])->SetParameters(-3.05756, 0.114211, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[4])[0])->SetParameters(-0.23071, 0.0557863, -0.00062489);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[4])[1])->SetParameters(0.0597747, 0.0177415, 0.000488853);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[4])[2])->SetParameters(-0.134499, 0.0403481, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[4])[3])->SetParameters(-3.05207, 0.114211, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[5])[0])->SetParameters(-0.16535, 0.0508199, -0.000498458);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[5])[1])->SetParameters(0.199063, 0.00902826, 0.000629897);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[5])[2])->SetParameters(-0.131738, 0.0403481, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[5])[3])->SetParameters(-3.04931, 0.114211, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[6])[0])->SetParameters(-0.120077, 0.0478879, -0.000440698);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[6])[1])->SetParameters(0.201888, 0.00902826, 0.000629897);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[6])[2])->SetParameters(-0.128913, 0.0403481, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[6])[3])->SetParameters(-3.04648, 0.114211, 0.0);

    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[7])[0])->SetParameters(-0.105443, 0.0484362, -0.000498158);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[7])[1])->SetParameters(0.197676, 0.00902826, 0.000629897);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[7])[2])->SetParameters(-0.133125, 0.0403481, 0.0);
    ((TF1*)(*(TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[3])[7])[3])->SetParameters(-3.0507, 0.114211, 0.0);
  }
}

int Determine_dtcSCPaddle(int locRunNumber, double locQ, double locP, double locTheta, double locVertexZ){

  TObjArray *locPanelFuncArray;
  int loc_i, locPBin;
  TF1 *locFunc;
  int locMaxPaddle = (locRunNumber <= 55204) ? 48 : 57;

  if((dtcSCPaddleMatchingPositivesFuncArray == NULL) || (dtcSCPaddleMatchingNegativesFuncArray == NULL))
    return 0;

//  int locVertexZBin = int(floor((locVertexZ - locTargetOffset + locTargetLength/2.0)/(locTargetLength/4.0)));
  int locVertexZBin = int(floor((locVertexZ + 40.0)/10.0));
  if(locVertexZBin < 0)
    locVertexZBin = 0;
  if(locVertexZBin > 3)
    locVertexZBin = 3;

  if(locQ > 0.0){
    locPBin = int((locP - 0.4)/0.2);
    if(locPBin < 0)
      locPBin = 0;
    if(locPBin > 7)
      locPBin = 7;
    locPanelFuncArray = (TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[locVertexZBin])[locPBin];
  }else if(locQ < 0.0){
    locPBin = int((locP - 0.1)/0.2);
    if(locPBin < 0)
      locPBin = 0;
    if(locPBin > 7)
      locPBin = 7;
    locPanelFuncArray = (TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[locVertexZBin])[locPBin];
  }else{return 0;}

  //Panel 1
  locFunc = (TF1*)(*locPanelFuncArray)[0];
  if(locFunc->Eval(23.5) > locTheta){
    for(loc_i = 0; loc_i <= 23; loc_i++){ //if 0 then missed (beam pipe)
      if(locFunc->Eval(loc_i + 0.5) >= locTheta)
        return loc_i;
    }
    return 23; //should be impossible
  }

  //Panel 2
  locFunc = (TF1*)(*locPanelFuncArray)[1];
  if(locFunc->Eval(34.5) > locTheta){
    for(loc_i = 24; loc_i <= 34; loc_i++){ //if there was a gap between the functions, assume 24 is blocked, assign 24
      if(locFunc->Eval(loc_i + 0.5) >= locTheta)
        return loc_i;
    }
    return 34; //should be impossible
  }

  //Panel 3
  locFunc = (TF1*)(*locPanelFuncArray)[2];
  if(locFunc->Eval(39.5) > locTheta){
    for(loc_i = 35; loc_i <= 39; loc_i++){ //if there was a gap between the functions, assume 35 is blocked, assign 35
      if(locFunc->Eval(loc_i + 0.5) >= locTheta)
        return loc_i;
    }
    return 39; //should be impossible
  }

  //Panel 4
  locFunc = (TF1*)(*locPanelFuncArray)[3];
  if(locFunc->Eval(locMaxPaddle + 0.5) > locTheta){
    for(loc_i = 40; loc_i <= locMaxPaddle; loc_i++){ //if there was a gap between the functions, assume 40 is blocked, assign 40
      if(locFunc->Eval(loc_i + 0.5) >= locTheta)
        return loc_i;
    }
    return locMaxPaddle; //should be impossible
  }
  return 0;
}


double Determine_dtcThetaFromSCPaddle(int locRunNumber, double locQ, double locP, double locSCPaddle, double locVertexZ){
//  int locVertexZBin = int(floor((locVertexZ - locTargetOffset + locTargetLength/2.0)/(locTargetLength/4.0)));
  int locVertexZBin = int(floor((locVertexZ + 40.0)/10.0));
  if(locVertexZBin < 0)
    locVertexZBin = 0;
  if(locVertexZBin > 3)
    locVertexZBin = 3;

  return Determine_dtcThetaFromSCPaddle(locRunNumber, locQ, locP, locSCPaddle, locVertexZBin);
}

double Determine_dtcThetaFromSCPaddle(int locRunNumber, double locQ, double locP, double locSCPaddle, int locVertexZBin){
  TObjArray *locPanelFuncArray;
  int locPBin;
  TF1 *locFunc;

  if((dtcSCPaddleMatchingPositivesFuncArray == NULL) || (dtcSCPaddleMatchingNegativesFuncArray == NULL))
    Setup_dtcSCPaddleMap(locRunNumber);

  if(locQ > 0.0){
    locPBin = int((locP - 0.4)/0.2);
    if(locPBin < 0)
      locPBin = 0;
    if(locPBin > 7)
      locPBin = 7;
    locPanelFuncArray = (TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingPositivesFuncArray)[locVertexZBin])[locPBin];
  }else if(locQ < 0.0){
    locPBin = int((locP - 0.1)/0.2);
    if(locPBin < 0)
      locPBin = 0;
    if(locPBin > 7)
      locPBin = 7;
    locPanelFuncArray = (TObjArray*)(*(TObjArray*)(*dtcSCPaddleMatchingNegativesFuncArray)[locVertexZBin])[locPBin];
  }else{return 0.0;}

  //Panel 1
  if(locSCPaddle <= 23.5){
    locFunc = (TF1*)(*locPanelFuncArray)[0];
    return locFunc->Eval(locSCPaddle);
  }

  //Panel 2
  if((locSCPaddle >= 23.5) && (locSCPaddle <= 34.5)){
    locFunc = (TF1*)(*locPanelFuncArray)[1];
    return locFunc->Eval(locSCPaddle);
  }

  //Panel 3
  if((locSCPaddle >= 34.5) && (locSCPaddle <= 39.5)){
    locFunc = (TF1*)(*locPanelFuncArray)[2];
    return locFunc->Eval(locSCPaddle);
  }

  //Panel 4
  if(locSCPaddle >= 39.5){
    locFunc = (TF1*)(*locPanelFuncArray)[3];
    return locFunc->Eval(locSCPaddle);
  }
  return 0.0;
}
