      SUBROUTINE STCOUNTER( vertex, cdir, dist )
c
c_begin_doc
c  RCS ID string
c  $Id: stcounter.F,v 1.5 2002/06/11 16:46:05 pasyuk Exp $
c
c  Documentation for subroutine STCOUNTER
c
c  Purpose: Calculate track length within the start counter scintillator
c  --------
c
c  Input Parameters:  (Name - Type - Meaning)
c  ----------------
c  vertex(3) (real) vertex coordinates
c  cdir(3)   (real) track direction cosines  
c
c  Output Parameters:  (Name - Type - Meaning)
c  -----------------
c  dist (real) track length within the scintillator
c
c  Other routines:
c  ---------------
c  IntesectionPlan 
c
c  Notes:
c  ------
c
c  Author:   Eugene Pasyuk      Created:  Tue Apr  6 16:38:45 EDT 1999
c  -------
c
c  Major revisions:
c  ----------------
c     
c
c_end_doc
c
      IMPLICIT NONE
      SAVE 
c
c_begin_var
c  input/output variables:
c  -----------------------
      REAL vertex(3)
      REAL cdir(3)
      REAL dist
c
c  Local pre-defined variables:
c  ---------------------------

      REAL d_leg                !distance from beam axis to the 
                                !face of scintillator
      REAL thickness            !scintillator thickness
      REAL half_length          !half length of the leg
      REAL pi

      DATA d_leg/10.2/
      DATA thickness/0.32/      
c changed thickness from 0.3 to 0.32 per Gordon's estimate of wrapping maerial
      DATA half_length/20.0/
      DATA pi/3.14159265359/
c  RCS information: 
      CHARACTER*132  CFILE, CREVIS, CSTATE, CDATE, CAUTHO, CRCSID
      PARAMETER (CFILE = '$RCSfile: stcounter.F,v $')
      PARAMETER (CREVIS = '$Revision: 1.5 $')
      PARAMETER (CSTATE = '$State: Exp $')
      PARAMETER (CDATE = '$Date: 2002/06/11 16:46:05 $')
      PARAMETER (CAUTHO = '$Author: pasyuk $')
      DATA CRCSID/   
     1'$Id: stcounter.F,v 1.5 2002/06/11 16:46:05 pasyuk Exp $'   
     2/   
c  Module information:
      CHARACTER*(*)  CRNAME, CRAUTH
      CHARACTER*100  CRMESS
      PARAMETER (CRNAME='STCOUNTER')
      PARAMETER (CRAUTH='Eugene Pasyuk')
c
c  Local User defined variables:
c  -----------------------------
      INTEGER NWRITE
      integer i
      integer ierr
      REAL alpha
      REAL w
      REAL phi 
      REAL point(3)
      REAL np(3)
      REAL start(3)
      REAL theta
      REAL dir(3)
      REAL aupoint(3)
      REAL norme
      REAL csinus

      DATA NWRITE/0/


#ifdef Linux
c for Linux these functions are not implemeted in standard library

      REAL sind, cosd, angle
      sind(angle) = sin( angle*pi/180. )
      cosd(angle) = cos( angle*pi/180. )

#endif

#include "eloss_geom.PAR"


c_end_var
c
c  executable code for routine STCOUNTER:
c----6----------------------------------------------------------------72
c
      IF (NWRITE .LT. 1) THEN
        NWRITE = NWRITE + 1
         write(CRMESS,*) 
     + 'STCOUNTER: ST offset is: ', st_offset
c        CRMESS='This is a STCOUNTER routine, this message written once'
        CALL RECMES(CRNAME,'I',CRMESS)
      ENDIF

c
c-------------Intersection avec le Start Counter
c

      alpha = atan2(cdir(2),cdir(1))
      alpha = 3.*alpha/pi
      w = nint(alpha)
      phi = w*60.

      np(1) = cosd(phi)
      np(2) = sind(phi)
      np(3) = 0.

      do i = 1,3
         point(i) = vertex(i) + 50.*cdir(i)
         start(i) = d_leg*np(i)
      enddo

      call IntersectionPlan(vertex, point, start, np, aupoint, ierr)

      theta = 90.
      
      if ( aupoint(3) .gt. (half_length + st_offset) ) then !leg or nose?
         theta = 60.
      endif

      dir(1) = sind(theta)*cosd(phi)
      dir(2) = sind(theta)*sind(phi)
      dir(3) = cosd(theta)

      norme = 0.
      do i = 1,3
         norme = norme+(aupoint(i)-vertex(i))*(aupoint(i)-vertex(i))
      enddo
      norme = sqrt(norme)
      
      csinus = 0.
      do i = 1,3
         csinus = csinus+(aupoint(i)-vertex(i))*dir(i)
      enddo

      csinus = csinus/norme
      dist = thickness/csinus

      RETURN
      END
c
c------------------------------------------------------------------------------




