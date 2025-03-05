c     G10 momentum correction
c
c     Status: debug
c     Author: T. Mibe, N. Baltzell, M. Mirazita
c
c     Inputs:
c        torus  : integer, torus current (Ampere)
c        icharge: integer, charge of particle 
c        pold   : real,  3 momentum before correction
c        icor   : choice of correction functions
c                  = 1 : pppm MM correction
c                  = 2 : pppm TM correction
c                  = 3 : K0   NB correction
c                  = 4 : Combined correction (currently, 1+3)
c     Outputs
c        pnew   : real, 3 momentum after correction
c        istat  : integer,
c                  < 0 : error
c                  = 1 : correction was measured
c                  = 2 : correction was not measured, extrapolated
c
      subroutine g10pcor(torus,icharge,pold,icor,pnew,istat)

      implicit none
      integer  torus, icharge, icor, istat, ifunc
      real     pold(3), pnew(3)
      integer  ifield
      real     Pm, phi, theta, Pc, Ec, deg2rad, bfactor
      integer  choosepcor
      parameter(deg2rad=3.1415927/180.)

      integer  lo_curr,hi_curr
      data     lo_curr,hi_curr/2250,3375/

      if (torus.lt.0) then
         write(*,*)'g10pcor:ERROR: invalid torus current', torus
         istat = -1
         return
      endif
      if (icharge.eq.0) then
         write(*,*)'g10pcor:ERROR: charge = 0'
         istat = -2
         return
      endif
      if ((icor.lt.0).or.(icor.gt.4)) then
         write(*,*)'g10pcor:ERROR: invalid switch', icor
         istat = -3
         return
      endif


      ifunc = -1
      Pm    = sqrt(pold(1)**2+pold(2)**2+pold(3)**2)
      theta = acos(pold(3)/Pm) /deg2rad
      phi   = atan2(pold(2),pold(1))/deg2rad
      if(phi.lt.-30) phi = phi+360.

c *** Check appropriate correction function 
      if (icor.eq.4) ifunc = choosepcor(ifield,icharge,Pm,theta)

C *** Choose the correction according to torus current and scale the momentum (untested!)
      if ((icor.eq.1).or.(ifunc.eq.1)) then
         if (torus.eq.2250) then
            ifield = 1
            bfactor= 1.0
         else if (torus.eq.3375) then
            ifield = 2
            bfactor= 1.0
         else
            if (abs(torus-lo_curr).lt.abs(torus-hi_curr)) then
               ifield=1
               bfactor= float(lo_curr)/float(torus)
            else
               ifield=2
               bfactor= float(hi_curr)/float(torus)
            endif
         endif
      else
c     tempolary prescription for TM, NB corrections
         ifield = 1
         if (torus.eq.2250) then
            bfactor = 1.0
         else
            bfactor = float(lo_curr)/float(torus)
         endif
      endif

      Pm = Pm*bfactor

      if (icor.eq.1) then       ! MM's correction
         call pcorpppm_mm(ifield,icharge,Pm,theta,phi,Pc,Ec,istat)
      else if (icor.eq.2) then  ! TM's correction
         call pcorpppm_tm(ifield,icharge,Pm,theta,phi,Pc,Ec,istat)
      else if (icor.eq.3) then  ! NB's correction
         call pcork0_nb(ifield,icharge,Pm,theta,phi,Pc,Ec,istat)
      else if (icor.eq.4) then  ! combined correction
         if (ifunc.eq.1) then
            call pcorpppm_mm(ifield,icharge,Pm,theta,phi,Pc,Ec,istat)
         else if (ifunc.eq.2) then
            call pcorpppm_tm(ifield,icharge,Pm,theta,phi,Pc,Ec,istat)
         else if (ifunc.eq.3) then
            call pcork0_nb(ifield,icharge,Pm,theta,phi,Pc,Ec,istat)
         endif
      endif

      pnew(1) = Pc*sin(theta*deg2rad)*cos(phi*deg2rad)/bfactor
      pnew(2) = Pc*sin(theta*deg2rad)*sin(phi*deg2rad)/bfactor
      pnew(3) = Pc*cos(theta*deg2rad)                 /bfactor

      return
      end
