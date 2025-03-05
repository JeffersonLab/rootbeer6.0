// hacked for g8
#include <kinematics.h>
#include <eloss.h>



/*--------------------------------------------*/
void initeloss(float targx, float targy, float targz, float st_offset){

  eloss_geom_.st_offset = st_offset;
  
  eloss_geom_.target_offset[0] = targx; /* set to default at CLAS center */
  eloss_geom_.target_offset[1] = targy;
  eloss_geom_.target_offset[2] = targz;
  return;
}
/*
 *-------------------------------------------------------------------------
 */



