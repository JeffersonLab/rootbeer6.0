// c wrapper for g10 momentum correction routine
// returns new four vector
// use include/g10pcor.h for function prototype in calling routine
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <kinematics.h>
#include <g10pcor.h>

extern "C" void g10pcor_(int*, int*, float*, int*, float*, int*);

int g10pcor(int itorus, int iicharge, int iicor, TLorentzVector* p4)
{
  int iistat=-9;
  float mass=-9.;
  float pold[3]={0.,0.,0.};
  float pnew[3]={0.,0.,0.};

  //  printf("p4 =  before corr "); v4print(stdout,*p4);

  mass = p4->M();
  pold[0] = p4->X();
  pold[1] = p4->Y();
  pold[2] = p4->Z();

  g10pcor_(&itorus,&iicharge,pold,&iicor,pnew,&iistat);

  p4->SetXYZM(pnew[0],pnew[1],pnew[2],mass);

  //  printf("p4c = after corr "); v4print(stdout,*p4);

  return iistat;
}
