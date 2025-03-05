/* c wrapper for energy loss routine
returns new four vector
DJT JUL-99

use include file include/eloss.h for function proto-type in calling routine

note that mom_p_out means after (out of) the absorber and not output of the routine
ergo mom_in (into the absorber) is the mom out(put) from the routine

 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <kinematics.h>
#include "eLoss.h"

extern "C" void momcor_(float*,float*,float*,int*,int*,float*);
extern "C" void initeloss(float,float,float,float);


TLorentzVector *eLoss(TLorentzVector *p_out, float pmass, TVector3 vertex, int iflag, \
int icell)
{
  float mom_p_out[3];                /* proton momentum */
  float mom_p_in[3];                /* proton momentum */
  float vert[3];                /* vertex */
  TLorentzVector *p_in;

  p_in = new TLorentzVector();

  /*printf("p_out =  before corr "); v4print(stdout,p_out);*/
  mom_p_out[0] = (float)p_out->X();
  mom_p_out[1] = (float)p_out->Y();
  mom_p_out[2] = (float)p_out->Z();
  //fprintf(stderr,"%f,%f,%f\n",mom_p_out[0],mom_p_out[1],mom_p_out[2]);
  vert[0] = vertex.X();
  vert[1] = vertex.Y();
  vert[2] = vertex.Z();
/*  iflag = 1; */
  momcor_(mom_p_out,&pmass,vert,&iflag,&icell,mom_p_in);
  p_in->SetXYZM((double)mom_p_in[0],(double)mom_p_in[1],(double)mom_p_in[2],pmass);
  return(p_in);
}

void initELoss(float targx, float targy, float tagrz, float st_offset){
  initeloss(targx, targy, tagrz, st_offset);
}
