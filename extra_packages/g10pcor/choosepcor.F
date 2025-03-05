c     This function choose one of the momentum corrections based on kinematics
c     Inputs:
c        ifield : integer, torus field setting
c                  = 1 : 2250A
c                  = 2 : 3375A
c        icharge: integer, charge of particle
c        Pm     : real,    momentum before correction
c        theta  : real,    polar angle
c     Outputs(return value)
c        ifunc   : integer, choice of correction function
c                  < 0 : error
c                  = 1 : pppm MM correction
c                  = 2 : pppm TM correction
c                  = 3 : K0   NB correction
c
c     author T. Mibe
      integer function choosepcor(ifield,icharge,Pm,theta)

      implicit none 
      
      integer ifield, icharge
      real    Pm, theta, thave
      integer ifunc, i, ith

      real plimitneg(15),plimitpos(15)
      data plimitneg
     +     /9.9,0.6,0.6,0.5,0.5,
     +      0.5,0.3,0.3,0.3,0.3,
     +      0.3,0.3,0.3,0.3,0.3/
      data plimitpos
     +     /9.999,0.875,0.725,0.575,0.575,
     +      0.425,0.425,0.425,0.425,0.425,
     +      0.425,0.425,0.425,0.425,0.425/

      ifunc= -1

c     Use pppm corrections for high field data
      if (ifield.eq.2) then
         ifunc = 1
         return
      endif

c     Check theta bin
      do i=0,22
         thave = 12+8*(i-1)
         if (abs(theta-thave).le.4) then
            ith = i
         endif
      enddo
      if (ith.gt.15) ith = 15   ! if theta>128 deg, set theta=124 deg.
      if (ith.eq. 0) ith =  1   ! if theta<8 deg, set theta=12 deg.

      
c     h- corrections
      if (icharge.eq.-1) then
         if (Pm.gt.plimitneg(ith)) then
            ifunc = 1
         else
            ifunc = 3
         endif
c     h+ corrections
      else if (icharge.eq.1) then
         if (Pm.gt.plimitpos(ith)) then
            ifunc = 1
         else
            ifunc = 3
         endif
      else
         write(*,*)'choosepcor: unknown charge', icharge
         ifunc = -2
      endif

      choosepcor = ifunc
      return
      end
