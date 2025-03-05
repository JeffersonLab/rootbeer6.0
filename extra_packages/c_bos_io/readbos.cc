#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ntypes.h>
#define READBOS
#include <bostypes.h>
#include <RootBeerTypes.h>
#include <bankvars.h>

int lastbankindex=-1;
void *lastbankaddress=NULL;
int lastbanksector=-1;
int lastbanktype=0;	//0=single 1=multi


int getBankIndex(const char *);

char *madeBankList[500];	//hold pointers to temporarily made banks
char makeBankTotal=0;		//no of temp banks
int previousEventNo=0;		//no of last event from HEAD.


void initbos()
{
  //dummy
}

int fparm_c(char *mess)
{
  return(1); //dummy
}
int getBOS(BOSbank *bcs, int lun, char *list)
{
  int ierr = 0;
  fprintf(stderr,"Sorry getBOS isn't abailable in the ROOTBEER wrapper for c_bos_io\n");
  return(!ierr);
}

/* A write routine with less problems than fseqr but reqires a unit number*/
int putBOS(BOSbank *bcs, int lun, char *list)
{
  int ierr = 0;
  fprintf(stderr,"Sorry putBOS isn't abailable in the ROOTBEER wrapper for c_bos_io\n");
  return(!ierr);
}

void *getBank(BOSbank *bcs, const char *name){
  int index;
  void **address=NULL;
  lastbankaddress=NULL;	// save the address
  lastbanksector=-1;
  lastbankindex=-1;

  index=getBankIndex(name);
  if(bankAddress[index].nBank==NULL){	//ie single sector bank
    if((int)bankAddress[index].nRow[0]>0){	// bank present
      return(*bankAddress[index].address);
      lastbankindex=index;
    }
    else{
      return(NULL);
    }
  }
  else{					//multi sector bank
    if(*bankAddress[index].nBank>0){	// some sectors fired
      address=(void**)*bankAddress[index].address;
      lastbankaddress=address[0];	// save the address
      lastbanksector=0;
      lastbankindex=index;
      return(address[0]);		//return first instance
    }
    else{
      return(NULL);	
    }
  }
  
  return NULL;
}

void *getNextBank(BOSbank *bcs, bankHeader_t *bank){
  void **address=NULL;
  int sector;
  int index;

  if(lastbankaddress!=NULL){
    sector=lastbanksector+1;
    index=lastbankindex;
    if(sector<*bankAddress[index].nBank){
      address=(void**)*bankAddress[lastbankindex].address;
      lastbankaddress=address[sector];	// save the address
      lastbanksector=sector;
      return(address[sector]);
    }
  }
  return NULL;
}

void *getGroup(BOSbank *bcs, const char *name, int j)
{
  int index,sect;
  void **address=NULL;
  int *secarray=NULL;
  lastbankaddress=NULL;	// save the address
  lastbanksector=-1;
  lastbankindex=-1;

  index=getBankIndex(name);
  if(bankAddress[index].nBank==NULL){	//ie single sector bank
    fprintf(stderr,"Warning: %s is a single sector bank - getGroup() is for multi sector banks\n",name); 
    return NULL;
  }
  else{					//multi sector bank
    if(*bankAddress[index].nBank>0){	// some sectors fired
      secarray=*bankAddress[index].bankSec;
      address=(void**)*bankAddress[index].address;
      for(sect=0;sect<*bankAddress[index].nBank;sect++){
	if(secarray[sect]==j){ 	
	  lastbankaddress=address[sect]; 	// save the address
	  lastbanksector=j;
	  lastbankindex=index;
	  return(address[sect]);		//return first instance
	}
      }
      return NULL;
    }
  }
  return NULL;
}

void *makeBank(BOSbank *bcs, char *bankname, int banknum, int ncol, int nrow)
{
  return NULL;
}

void *dropBank(BOSbank *bcs, char *bankname, int banknum)
{
  return NULL;
}

void bankList(BOSbank *bcs, char *list, char *banklist)
{
}

void dropAllBanks(BOSbank *bcs, char *list)
{
}

void cleanBanks(BOSbank *bcs)
{
}

void formatBank(char *bankname, char *bankformat)
{
}

void open_fpack(char *filename)
{
}

int GetData()
{
return 0;
}

void open_fpack_unit(char *filename,char *dataname,int unitnum)
{
}

void close_fpack_unit(char *dataname)
{
}

void rewind_fpack_unit(char *dataname)
{
}

int GetData_unit(char *dataname)
{
return 0;
}

int fileLength(char *datafile)
{
  return 0;
}

FileParameters_t fileQuery(char *datafile)
{
 FileParameters_t fileParameters;
 int ierr;
 return(fileParameters);
}

int getBankIndex(const char *name){ 
  int n;
  for(n=0;n<nBankTypes;n++){
    //    fprintf(stdout, "combank = %.4s %s\n",bankAddress[n].name, name);
    if(strncmp(name,bankAddress[n].name,4)==0){
      break;
    }
  }
  if(n==nBankTypes){
    fprintf(stderr,"Fatal Error: Don't know about \"%s\" bank, can't get Index\n",name);
    exit(0);
  }
  else{
    return n;
  }
}
      
