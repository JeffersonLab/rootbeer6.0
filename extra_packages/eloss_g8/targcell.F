      SUBROUTINE TARGCELL( icell, vertex, cdir, dist, dist1 )
c
c_begin_doc
c  RCS ID string
c  $Id: targcell.F,v 1.8 2002/12/07 19:04:04 pasyuk Exp $
c
c  Documentation for subroutine TARGCELL
c
c  Purpose: calculates track length within LH2 target and its mylar walls.
c  --------
c           g1 run target geometry
c
c  Input Parameters:  (Name - Type - Meaning)
c  ----------------
c  icell     (integer) target cell type: 
c
c		       icell = 0 - no target
c                      icell = 1 - G1A/G1B/G6A/G6b running period 
c                      icell = 2 - G2A running period 
c                      icell = 3 - G1C running period 
c                      icell = 4 - G3 running period
c                      icell = 5 - G6C/G8A running period 
c     
c                
c  vertex(3) (real) vertex coordinates
c  cdir(3)   (real) track direction cosines  
c
c  Output Parameters:  (Name - Type - Meaning)
c  -----------------
c  dist (real)  track length within target material
c  dist1 (real) track length in target wall
c
c  Other routines:
c  ---------------
c  IntersectionSphere, IntersectionCylindre
c
c  Notes:
c  ------
c
c  Author:   Eugene Pasyuk      Created:  Tue Apr  6 16:37:59 EDT 1999
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
c
      INTEGER icell
      REAL vertex(3)
      REAL cdir(3)
      REAL dist
      REAL dist1 
      REAL dir(3)

c     Local pre-defined variables:
c     ---------------------------
c
c      REAL centre(3)

      REAL LC(5)                !Half-length of a cylinder
      REAL LS(5)                !sphere center offset
      REAL RC(5)                !Cylinder radius
      REAL RS(5)                !Sphere radius
      REAL WALL(5)              !wall thickness

      DATA LC/6.0, 4.5, 8.5, 8.5, 8.5/
      DATA LS/6.0, 1., 5., 5., 6.85/
      DATA RC/3., 2., 2., 2., 1.4/
      DATA RS/3., 4., 4., 4., 2.248/
c      DATA WALL/0.017, 0.0127, 0.0127, 0.019/ !originall wall thickness 
      DATA WALL/0.032, 0.0277, 0.0277, 0.034,0.0277/ 
c wall thickness includes superinsulation, which is about 15 mg/cm^2


      DATA dir /0., 0., 1./     !target axis direction cosines


c     RCS information: 

      CHARACTER*132  CFILE, CREVIS, CSTATE, CDATE, CAUTHO, CRCSID
      PARAMETER (CFILE = '$RCSfile: targcell.F,v $')
      PARAMETER (CREVIS = '$Revision: 1.8 $')
      PARAMETER (CSTATE = '$State: Exp $')
      PARAMETER (CDATE = '$Date: 2002/12/07 19:04:04 $')
      PARAMETER (CAUTHO = '$Author: pasyuk $')
      DATA CRCSID/   
     1     '$Id: targcell.F,v 1.8 2002/12/07 19:04:04 pasyuk Exp $'/
      
c     Module information:

      CHARACTER*(*)  CRNAME, CRAUTH
      CHARACTER*100  CRMESS
      PARAMETER (CRNAME='TARGCELL')
      PARAMETER (CRAUTH='Eugene Pasyuk')
c     
c     Local User defined variables:
c     -----------------------------
c
      INTEGER NWRITE
      INTEGER ierr
      INTEGER ierr1 
      INTEGER extrm
      INTEGER i

      REAL pos1(3)
      REAL pos2(3)
      REAL pos1w(3)
      REAL pos2w(3)
      REAL point(3)
      REAL cc(3)
      REAL r
      REAL x

#include "eloss_geom.PAR"

      data nwrite/0/

c     _end_var
c     
c     executable code for routine LH2TARG:
c---- 6----------------------------------------------------------------72


      if(icell.eq.0) then
	dist=0.
	dist1=0.
	return
      endif

      do i = 1,3
         point(i) = vertex(i) + 50.*cdir(i)
         cc(i) = target_offset(i)
      enddo
c---- 6----------------------------------------------------------------72
c     
      IF (NWRITE .LT. 1) THEN
         NWRITE = NWRITE + 1
         write(CRMESS,*) 
     + 'TARGCELL: target position is: ', target_offset

         CALL RECMES(CRNAME,'I',CRMESS)
         
      ENDIF
c     
c------------------------------------------------------------------------------


      call InterCylinder(vertex, cdir, cc, dir, RC(icell),
     $     pos1, ierr)


      if (ierr .eq. 0 .or. ierr .eq. 2 ) then
         dist = 0.
         dist1 = 0.
         return                 ! no intersection, get out
      endif


c---  cylinder or sphere?
      extrm = 0
      if ( pos1(3) .gt. LC(icell)+target_offset(3) ) extrm = 1
      if ( target_offset(3)-LC(icell) .gt. pos1(3)) extrm = -1

c---  sphere
      if (extrm .ne. 0) then 
         cc(3) = extrm*LS(icell) + target_offset(3)
         call IntersectionSphere(vertex, point, cc, RS(icell),
     $        pos1, pos2, ierr)
         if (ierr .eq. 0) then 
            dist = 0.
            dist1 = 0. 
            return              !no intersection, get out
         endif
c---  spheric wall
         r = RS(icell) + wall(icell)
         call IntersectionSphere(vertex, point, cc, r,
     $        pos1w, pos2w, ierr1)

         if (ierr .eq. 2) then
            pos1(1) = pos2(1)
            pos1(2) = pos2(2)
            pos1(3) = pos2(3)
            pos1w(1) = pos2w(1)
            pos1w(2) = pos2w(2)
            pos1w(3) = pos2w(3)
         endif
c---  cylinder wall
      else 
         r = RC(icell) + wall(icell)
         call InterCylinder(vertex, cdir, cc, dir, r,
     $        pos1w, ierr)
      endif

      dist = 0.
      x = 0.

      do i = 1,3
         dist = dist + (pos1(i) - vertex(i))*(pos1(i) - vertex(i))
         x = x + (pos1w(i) - vertex(i))*(pos1w(i) - vertex(i))
      enddo

      dist = sqrt(dist)
      x = sqrt(x)
      dist1 = x - dist

      RETURN
      END


