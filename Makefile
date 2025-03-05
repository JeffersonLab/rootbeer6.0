# The rootbeer makefile

# get root libs
ROOTLIBS	= $(shell root-config --libs)


#if ROOTBEER not defined then make it the current working directory
ifndef ROOTBEER
 OBJDIR		= ./obj/Linux
 BINDIR		= ./bin/Linux
 SODIR		= ./slib/Linux
else
 OBJDIR		= $(ROOTBEER_OBJ)
 BINDIR		= $(ROOTBEER_BIN)
 SODIR		= $(ROOTBEER_SLIB)
endif

#default no debugging
DEBUG		= 0

#define some directories
SRCDIR		= src
INCDIR		= include
DATDIR		= dat
SCRIPTDIR	= scripts
SC		= sample_code
DOCDIR		= doc
PACK		= extra_packages

#name of file with bankdefs
CLASBANKS     	=  $(INCDIR)/clasbanks.ddl

#only require this if building stuff hacked from clas packages
CLASPACK =$(CLAS_PACK)
#CLASPACK = /home/claslib/builds/DEVELOPMENT/packages
#CLASINC = -I$(CLASPACK)/include -I$(CLASPACK)/inc_derived

# Linux with egcs
CXX		= g++
LD		= g++
CC		= gcc
#G77		= g77
G77		= gfortran

# allow debugging with >make DEBUG=1 
ifeq ($(DEBUG),1)
CXXFLAGS      	= -g -Wall -std=c++17 -Wno-write-strings -Wno-restrict -Wno-format-overflow -Wno-stringop-truncation -Wno-deprecated -DR__THREAD -fexceptions -fno-strict-aliasing \
		 -fPIC -I$(ROOTSYS)/include -I./ -I$(INCDIR) $(CLASINC)
CFLAGS	      	= -g -Wno-deprecated -D_REENTRANT -fno-strict-aliasing -I$(INCDIR) $(CLASINC)
#FFLAGS	      	= -g-mcpu=pentium -fno-automatic -finit-local-zero -ffixed-line-length-none \
#		-fno-second-underscore -DLinux

FFLAGS += -g
         FFLAGS += -fno-f2c
#        FFLAGS += -m32
         FFLAGS += -fno-automatic 
         FFLAGS += -fPIC
         FFLAGS += -ffixed-line-length-none
         FFLAGS += -fno-second-underscore
         FFLAGS += -funroll-loops
         FFLAGS += -fomit-frame-pointer

LDFLAGS       	= -g

else

CFLAGS		= -O2 -Wno-deprecated -Wno-unused -D_REENTRANT -fno-strict-aliasing -I$(INCDIR) -I$(SC) $(CLASINC)
CXXFLAGS      	= -std=c++17 -Wno-write-strings -Wno-restrict -Wno-format-overflow -Wno-stringop-truncation -O2 -Wno-deprecated -Wno-unused -Wall -DR__THREAD \
		-fexceptions -fno-strict-aliasing -fPIC -I$(ROOTSYS)/include -I./ -I$(INCDIR) -I$(SC) $(CLASINC)
LDFLAGS       	= -O2 -Wall -Wno-deprecated -Wno-unused
#FFLAGS		=-O2 -mcpu=pentium -fno-automatic -finit-local-zero -ffixed-line-length-none \
#		-fno-second-underscore -DLinux

FFLAGS += -O2
         FFLAGS += -fno-f2c
#        FFLAGS += -m32                                                                                                                             
         FFLAGS += -fno-automatic
         FFLAGS += -fPIC                                                                                                                            
         FFLAGS += -ffixed-line-length-none
         FFLAGS += -fno-second-underscore
         FFLAGS += -funroll-loops
         FFLAGS += -fomit-frame-pointer


endif

SOFLAGS       	= -shared
LIBS          	= $(ROOTLIBS) -lm -ldl -rdynamic
RBLIB		= -L$(SODIR) -lRootBeer


GAWK 		= gawk

LIBPTHREAD	= -lpthread

#------------------------------ some rules ------------------------------

.SUFFIXES: 	.cxx

#rules for .cxx
$(OBJDIR)/%.o: 	$(SRCDIR)/%.cxx $(INCDIR)/%.h 
		$(CXX) $(CXXFLAGS) -o $@ -c $<

%.o: 		%.cxx
		$(CXX) $(CXXFLAGS) -o $@ -c $<


#rule for .C
$(OBJDIR)/%.o: 	$(SRCDIR)/%.C
		$(CXX) $(CXXFLAGS) -o $@ -c $<

#rule for c
$(OBJDIR)/%.o: 	$(SRCDIR)/%.c
		$(CC) $(CFLAGS) -o $@ -c $<

%.o:		%.c
		$(CC) $(CFLAGS) -o $@ -c $<

%.o:		%.F
		$(G77) $(FFLAGS) -DLinux -o $@ -c $<

$(PACK)/eloss_rb/%.o:	$(PACK)/eloss/%.F
		$(G77) $(FFLAGS) -DLinux -o $@ -c $<


#-------------------------------------------------------------------------
BANKDUMPEXE	= $(BINDIR)/bankdump

all:           	$(info OBJDIR="$(ROOTBEER_OBJ)") $(ROOTBEERSO) $(BANKDUMPEXE) getbanks ExpTable


#---------------- all the basic rootbeer librares and executables----------------------------
# should not need to touch this stuff - long and explicit, no fancy rules here

BANKVARS		= bankvars
BANKVARSO		= $(OBJDIR)/bankvars.o $(OBJDIR)/bankvarsDict.o

$(BANKVARS):		$(BANKVARSO)

$(OBJDIR)/bankvars.o:	$(INCDIR)/bankvars.h $(INCDIR)/TRootBeer.h $(INCDIR)/RootBeerTypes.h \
			$(INCDIR)/TBos.h $(INCDIR)/BosTypes.h \
			$(INCDIR)/TDST.h
			$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/bankvars.cxx

$(OBJDIR)/bankvarsDict.o:	$(INCDIR)/bankvars.h $(INCDIR)/TRootBeer.h $(INCDIR)/RootBeerTypes.h \
				$(INCDIR)/TBos.h $(INCDIR)/BosTypes.h \
				$(INCDIR)/TDST.h

			@echo "Generating dictionary bankvarsDict..."
			rootcint -f $(SRCDIR)/bankvarsDict.cxx -c \
			$(INCDIR)/bankvars.h $(INCDIR)/bankvarsLinkDef.h
			$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/bankvarsDict.cxx
			ln -s $(ROOTBEER)/$(SRCDIR)/bankvarsDict_rdict.pcm $(SODIR)

## generate headers, banklist etc
$(INCDIR)/bankvars.h:	$(SCRIPTDIR)/bank2struct.gk $(CLASBANKS) $(DATDIR)/singles.dat
			$(GAWK) -v incdir=$(INCDIR) -v srcdir=$(SRCDIR) \
			-f $(SCRIPTDIR)/bank2struct.gk $(CLASBANKS) > $(INCDIR)/bankheader.h




RBEER    		= RootBeer
ROOTBEERO   		=  $(OBJDIR)/TRootBeer.o  $(OBJDIR)/RootBeerDict.o

$(RBEER):		$(ROOTBEERO)

$(OBJDIR)/TRootBeer.o:	$(INCDIR)/bankvars.h $(INCDIR)/TRootBeer.h $(INCDIR)/RootBeerTypes.h \
			$(SRCDIR)/TRootBeer.cxx
			$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/TRootBeer.cxx


$(OBJDIR)/RootBeerDict.o: $(INCDIR)/bankvars.h $(INCDIR)/TRootBeer.h $(INCDIR)/RootBeerTypes.h \
			$(INCDIR)/RootBeerLinkDef.h  

			@echo "Generating dictionary RootBeerDict..."
			rootcint -f $(SRCDIR)/RootBeerDict.cxx -c \
			$(INCDIR)/TRootBeer.h $(INCDIR)/RootBeerLinkDef.h
			$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/RootBeerDict.cxx
			ln -s $(ROOTBEER)/$(SRCDIR)/RootBeerDict_rdict.pcm $(SODIR)


BOS         		= Bos
BOSO        		= $(OBJDIR)/TBos.o $(OBJDIR)/BosDict.o

$(BOS):			$(BOSO)
$(OBJDIR)/TBos.o:	$(INCDIR)/bankvars.h $(INCDIR)/TRootBeer.h $(INCDIR)/RootBeerTypes.h \
			$(INCDIR)/TBos.h $(INCDIR)/BosTypes.h $(SRCDIR)/TBos.cxx
			$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/TBos.cxx

$(OBJDIR)/BosDict.o: 	$(INCDIR)/bankvars.h $(INCDIR)/TRootBeer.h $(INCDIR)/RootBeerTypes.h  \
			$(INCDIR)/TBos.h $(INCDIR)/BosTypes.h $(INCDIR)/BosLinkDef.h

			@echo "Generating dictionary BosDict..."
			rootcint -f $(SRCDIR)/BosDict.cxx -c $(INCDIR)/TBos.h \
			$(INCDIR)/BosLinkDef.h
			$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/BosDict.cxx
			ln -s $(ROOTBEER)/$(SRCDIR)/BosDict_rdict.pcm $(SODIR)


DST         		= Dst
DSTO        		= $(OBJDIR)/TDST.o $(OBJDIR)/DSTDict.o

$(DST):			$(DSTO)
$(OBJDIR)/TDST.o:	$(SRCDIR)/TDST.cxx $(INCDIR)/bankvars.h $(INCDIR)/TRootBeer.h $(INCDIR)/RootBeerTypes.h \
			$(INCDIR)/TDST.h 
			$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/TDST.cxx

$(OBJDIR)/DSTDict.o: 	$(INCDIR)/bankvars.h $(INCDIR)/TRootBeer.h $(INCDIR)/RootBeerTypes.h \
			$(INCDIR)/TDST.h $(INCDIR)/DSTLinkDef.h

			@echo "Generating dictionary BosDict..."
			rootcint -f $(SRCDIR)/DSTDict.cxx -c $(INCDIR)/TDST.h \
			$(INCDIR)/DSTLinkDef.h
			$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/DSTDict.cxx
			ln -s $(ROOTBEER)/$(SRCDIR)/DSTDict_rdict.pcm $(SODIR)


DSTWriter       	= DSTWriter
DSTWriterO      	= $(OBJDIR)/TDSTWriter.o $(OBJDIR)/DSTWriterDict.o

$(DSTWriter):		$(DSTWriterO)
$(OBJDIR)/TDSTWriter.o:	$(INCDIR)/bankvars.h $(INCDIR)/TRootBeer.h $(INCDIR)/RootBeerTypes.h \
			$(INCDIR)/TBos.h $(INCDIR)/BosTypes.h \
			$(INCDIR)/TDST.h $(SRCDIR)/TDSTWriter.cxx \
			$(INCDIR)/TDSTWriter.h
			$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/TDSTWriter.cxx

$(OBJDIR)/DSTWriterDict.o: 	$(INCDIR)/bankvars.h $(INCDIR)/TRootBeer.h $(INCDIR)/RootBeerTypes.h \
				$(INCDIR)/TBos.h $(INCDIR)/BosTypes.h \
				$(INCDIR)/TDST.h \
				$(INCDIR)/TDSTWriter.h $(INCDIR)/DSTWriterLinkDef.h

			@echo "Generating dictionary BosDict..."
			rootcint -f $(SRCDIR)/DSTWriterDict.cxx -c $(INCDIR)/TDSTWriter.h \
			$(INCDIR)/DSTWriterLinkDef.h
			$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/DSTWriterDict.cxx
			ln -s $(ROOTBEER)/$(SRCDIR)/DSTWriterDict_rdict.pcm $(SODIR)


ROOTBEERUTIL    = 	RootBeerUtil
ROOTBEERUTILO   = 	$(OBJDIR)/RootBeerUtil.o $(OBJDIR)/RootBeerUtilDict.o

$(OBJDIR)/RootBeerUtil.o: 	$(INCDIR)/bankvars.h $(INCDIR)/TRootBeer.h $(INCDIR)/RootBeerTypes.h \
				$(INCDIR)/TBos.h $(INCDIR)/BosTypes.h \
				$(INCDIR)/TDST.h \
				$(INCDIR)/RootBeerUtil.h $(SRCDIR)/RootBeerUtil.cxx
				$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/RootBeerUtil.cxx

$(OBJDIR)/RootBeerUtilDict.o: 	$(INCDIR)/bankvars.h $(INCDIR)/TRootBeer.h $(INCDIR)/RootBeerTypes.h \
				$(INCDIR)/TBos.h $(INCDIR)/BosTypes.h \
				$(INCDIR)/TDST.h \
				$(INCDIR)/RootBeerUtil.h $(INCDIR)/RootBeerUtilLinkDef.h

				@echo "Generating dictionary BosDict..."
			 	rootcint -f $(SRCDIR)/RootBeerUtilDict.cxx -c \
				$(INCDIR)/RootBeerUtil.h $(INCDIR)/RootBeerUtilLinkDef.h
				$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/RootBeerUtilDict.cxx
				ln -s $(ROOTBEER)/$(SRCDIR)/RootBeerUtilDict_rdict.pcm $(SODIR)




ROOTBEERSO  	= $(SODIR)/libRootBeer.so

$(ROOTBEERSO):	$(ROOTBEERO)  $(BOSO)  $(DSTO) $(ROOTBEERUTILO) $(DSTWriterO) $(BANKVARSO)

		$(LD) $(SOFLAGS) $(LDFLAGS) -o $@ $^ $(ROOTLIBS) -lThread

		@echo "$(ROOTBEER) done"




$(BANKDUMPEXE): $(ROOTBEERSO) $(SRCDIR)/bankdump.cxx
		$(CXX) $(CXXFLAGS) -DROOTEXE  -o $(BANKDUMPEXE) $(SRCDIR)/bankdump.cxx $(RBLIB) \
		$(ROOTLIBS) -lThread -lm


EXPTABLESO      = $(SODIR)/libExpTable.so
EXPTABLEO       = $(OBJDIR)/TExpTable.o  $(OBJDIR)/ExpTableDict.o

$(EXPTABLESO):  $(EXPTABLEO)
		$(LD) $(SOFLAGS) $(LDFLAGS) -o $@ $^ $(ROOTLIBS) -lThread

		@echo "$(EXPTABLESO) done"


ExpTable:       $(EXPTABLESO)

$(OBJDIR)/TExpTable.o:  $(INCDIR)/TExpTable.h $(SRCDIR)/TExpTable.cxx
		$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/TExpTable.cxx


$(OBJDIR)/ExpTableDict.o: $(INCDIR)/TExpTable.h $(INCDIR)/ExpTableLinkDef.h
			@echo "Generating dictionary ExpTableDict..."
			rootcint -f $(SRCDIR)/ExpTableDict.cxx -c \
			$(INCDIR)/TExpTable.h $(INCDIR)/ExpTableLinkDef.h
			$(CXX) $(CXXFLAGS) -o $@ -c $(SRCDIR)/ExpTableDict.cxx
			ln -s $(ROOTBEER)/$(SRCDIR)/ExpTableDict_rdict.pcm $(SODIR)


htmldoc:	$(ROOTBEERSO) $(SRCDIR)/TRootBeer.cxx $(SRCDIR)/TDST.cxx $(SRCDIR)/TDSTWriter.cxx\
		$(SRCDIR)/TBos.cxx $(SRCDIR)/TExpTable.cxx
		@echo " Invoking ROOT html automatic documentation"
#		@rm -rf htmldoc
		root -b -n -q sample_code/htmldoc.C


GETBANKS	= $(BINDIR)/getbanks
getbanks:	$(GETBANKS)
$(GETBANKS):	$(SCRIPTDIR)/getbanks
		cp -f $(SCRIPTDIR)/getbanks $(BINDIR)/getbanks

#---------------- end of basic rootbeer librares and executables--------------------------------------------------

#---------------- make tar -----------------------------------------------------------------------------
TD	= $(shell basename `pwd`)
tar:
#rm all obj files in $(PACK) subdirs 
#	rm -f $(PACK)/*/*.o 
	cd ../ ;\
	tar --create --verbose --file $(TD)/$(TD).tar \
	--exclude='*Dict*' \
	--exclude='*.pcm' \
	--exclude='*.so' \
	--exclude='*.o' \
	--exclude='*.d' \
	--exclude='*core*' \
	--exclude='*~' \
	--exclude='htmldoc/*' \
	--exclude='lib/*' \
	--exclude='slib/*' \
	--exclude='bin/*' \
	--exclude='obj/*' \
	$(TD)

#-------------- end make tar ---------------------------------------------------------------------------

clean:  
	/bin/rm -f $(BOSO) $(DSTO) $(ROOTBEERO) $(ROOTUTILO) $(ROOTBEERSO) $(BANKSERVERO) \
	$(EXPTABLESO):  $(EXPTABLEO) \
	$(BANKSERVEREXE) $(BANKDUMPO) $(DSTWriterO) $(BANKDUMPEXE) $(BANKVARSO) $(ROOTBEERUTILO) $(PERFO)
	/bin/rm -f $(INCDIR)/bankvars.h $(INCDIR)/bankvars.h \
	$(SRCDIR)/bankvars.cxx \
	$(INCDIR)/bankvarsLinkDef.h $(SRCDIR)/*Dict.* $(SRCDIR)/*.pcm $(INCDIR)/*Dict.* core* \
	$(SODIR)/*.pcm


#_______________________________________________________________________________________________________________________


# Some more obscure examples on how to turn clas packages into root shared library
# with functions callable in CINT

## incorporation of Eugene's eloss package _____________________________________________________________________________
## Build the library 
ELOSSSO		= $(SODIR)/libeloss.so
ELOSS_RB_DIR	= $(PACK)/eloss_rb

eloss: 		$(ELOSSSO)

# build the shared library by using the .F files from the standard eloss distribution, which must exist, or be linked as 
# extra_packages/eloss
# and some extra .F and .cxx and .h in extra_packages eloss_rb
#
$(ELOSSSO):	$(ELOSS_RB_DIR)/elossDict.o $(ELOSS_RB_DIR)/eLoss.h $(ELOSS_RB_DIR)/elossLinkDef.h \
		$(addsuffix .o, $(basename $(filter %.F %.cxx, $(wildcard $(ELOSS_RB_DIR)/*)))) \
		$(addprefix $(ELOSS_RB_DIR)/, $(addsuffix .o, $(notdir $(basename $(filter %.F, $(wildcard $(PACK)/eloss/*))))))


		$(LD) $(SOFLAGS) $(LDFLAGS) $(ELOSS_RB_DIR)/*.o  -o $@ -lgfortran


$(ELOSS_RB_DIR)/elossDict.o: 	$(ELOSS_RB_DIR)/eLoss.h $(ELOSS_RB_DIR)/elossLinkDef.h
				@echo "Generating dictionary $(PACK)/eloss/elossDict.cxx"
				rootcint -f $(ELOSS_RB_DIR)/elossDict.cxx \
				-c $(ELOSS_RB_DIR)/eLoss.h $(ELOSS_RB_DIR)/elossLinkDef.h
				$(CXX) $(CXXFLAGS) -o $@ -c $(ELOSS_RB_DIR)/elossDict.cxx
				ln -s $(ROOTBEER)/$(ELOSS_RB_DIR)/elossDict_rdict.pcm $(SODIR)

eloss_clean: 
		rm -f $(ELOSS_RB_DIR)/*.o $(ELOSS_RB_DIR)/*Dict* $(ELOSS_RB_DIR)/*.pcm $(SODIR)/libeloss.so $(SODIR)/elossDict_rdict.pcm
#_______________________________________________________________________________________________________________________

## incorporation of g10 momentum correction package ____________________________________________________________________
## Build the library 
G10PCORO	= $(SODIR)/libg10pcor.so
g10pcor:	$(G10PCORO)
$(G10PCORO): 	$(PACK)/g10pcor/g10pcorDict.o $(INCDIR)/g10pcor.h $(INCDIR)/g10pcorLinkDef.h\
		$(addsuffix .o, $(basename $(filter %.F %.c %.cxx, $(wildcard $(PACK)/g10pcor/*))))

		$(LD) $(SOFLAGS) $(LDFLAGS) $(PACK)/g10pcor/*.o  -o $@  -L$(CERN_ROOT)/lib -lkernlib -lg2c

$(PACK)/g10pcor/g10pcorDict.o: $(INCDIR)/g10pcor.h $(INCDIR)/g10pcorLinkDef.h
				@echo "Generating dictionary $(PACK)/g10pcor/g10pcorDict.cxx"
				rootcint -f $(PACK)/g10pcor/g10pcorDict.cxx \
				-c $(INCDIR)/g10pcor.h $(INCDIR)/g10pcorLinkDef.h
				$(CXX) $(CXXFLAGS) -o $@ -c $(PACK)/g10pcor/g10pcorDict.cxx

g10pcor_clean: 
		rm -f $(PACK)/g10pcor/*.o $(PACK)/g10pcor/*Dict* $(SODIR)/libg10pcor.so
#_______________________________________________________________________________________________________________________


## incorporation of g13 momentum correction package, based on g10 (see above)____________________________________________________________________
## Build the library 
G13PCORO	= $(SODIR)/libg13pcor.so
G13PCOR_RB_DIR = $(PACK)/g13pcor

g13pcor:	$(G13PCORO)
$(G13PCORO): 	$(G13PCOR_RB_DIR)/g13pcorDict.o $(G13PCOR_RB_DIR)/DecayTrackCorrections.h  $(G13PCOR_RB_DIR)/DecayTrackFunctions.h  $(INCDIR)/g13pcorLinkDef.h\
		$(addsuffix .o, $(basename $(filter %.F %.c %.cc %.cxx, $(wildcard $(PACK)/g13pcor/*))))

		$(LD) $(SOFLAGS) $(LDFLAGS) $(PACK)/g13pcor/*.o  -o $@  -L$(CERN_ROOT)/lib 

$(PACK)/g13pcor/g13pcorDict.o: $(G13PCOR_RB_DIR)/DecayTrackCorrections.h $(G13PCOR_RB_DIR)/DecayTrackFunctions.h $(INCDIR)/g13pcorLinkDef.h
				@echo "Generating dictionary $(PACK)/g13pcor/g13pcorDict.cxx"
				rootcint -f $(PACK)/g13pcor/g13pcorDict.cxx \
				-c $(G13PCOR_RB_DIR)/DecayTrackCorrections.h $(G13PCOR_RB_DIR)/DecayTrackFunctions.h $(INCDIR)/g13pcorLinkDef.h
				$(CXX) $(CXXFLAGS) -o $@ -c $(PACK)/g13pcor/g13pcorDict.cxx

g13pcor_clean: 
		rm -f $(PACK)/g13pcor/*.o $(PACK)/g13pcor/*Dict* $(SODIR)/libg13pcor.so
#_______________________________________________________________________________________________________________________



#incorporation of c_bos_io _____________________________________________________________________________________________
# This is a substitute library for all the c_bos_io calls. It allow the incorporation of clas packages which 
# use c_bos_io (ie most clas packages). (Only briefly tested)

C_BOS_IO 	= $(SODIR)/libc_bos_io.so
c_bos_io:	$(C_BOS_IO)

$(C_BOS_IO) :   $(ROOTBEERSO) $(PACK)/c_bos_io/c_bos_ioDict.o  \
		$(addsuffix .o, $(basename $(filter %.c %.cc, $(wildcard $(PACK)/c_bos_io/*)))) \
		$(INCDIR)/bostypes.h $(INCDIR)/c_bos_ioLinkDef.h
		$(LD) $(SOFLAGS) $(LDFLAGS) $(PACK)/c_bos_io/*.o  -o $@ $(RBLIB)

$(PACK)/c_bos_io/c_bos_ioDict.o: $(ROOTBEERSO) $(INCDIR)/bostypes.h $(INCDIR)/c_bos_ioLinkDef.h 
				@echo "Generating dictionary $@"
				rootcint -f $(PACK)/c_bos_io/c_bos_ioDict.cxx -c -I$(INCDIR) \
				$(CLASINC) $(INCDIR)/bostypes.h $(INCDIR)/c_bos_ioLinkDef.h
				$(CXX) $(CXXFLAGS) -o $@ -c $(PACK)/c_bos_io/c_bos_ioDict.cxx

c_bos_io_clean: 
		rm -f $(PACK)/c_bos_io/*.o $(PACK)/c_bos_io/*Dict* $(SODIR)/libc_bos_io.so

#_______________________________________________________________________________________________________________________

#shared library PolHandler - an example of a class
#but not very tidy code in the class!

POLHANDLERSO		= $(SODIR)/libPolHandler.so
PolHandler:		$(POLHANDLERSO)
$(POLHANDLERSO):	$(OBJDIR)/PolHandler.o 	$(OBJDIR)/PolHandlerDict.o
			$(LD) $(SOFLAGS) $(LDFLAGS) $^ -o $@ $(ROOTLIBS) $(RBLIB) -L./  -lm

$(OBJDIR)/PolHandler.o: $(ROOTBEERSO) $(SC)/PolHandler.C $(SC)/PolHandler.h
			$(CXX) $(CXXFLAGS) -o $@ -c $(SC)/PolHandler.C

$(OBJDIR)/PolHandlerDict.o: $(ROOTBEERSO) $(SC)/PolHandler.h $(SC)/PolHandlerLinkDef.h
			@echo "Generating dictionary $@"
			#$(ROOTSYS)/bin/rootcint -f $(SC)/PolHandlerDict.cxx -c -I$(INCDIR) $(SC)/PolHandler.h \
			rootcint -f $(SC)/PolHandlerDict.cxx -c -I$(INCDIR) $(SC)/PolHandler.h \
			$(SC)/PolHandlerLinkDef.h
			$(CXX) $(CXXFLAGS) -o $(OBJDIR)/PolHandlerDict.o -c $(SC)/PolHandlerDict.cxx

PolHandler_clean :
	rm -f $(OBJDIR)/PolHandler*.o $(SC)/PolHandlerDict.cxx

#_______________________________________________________________________________________________________________________

