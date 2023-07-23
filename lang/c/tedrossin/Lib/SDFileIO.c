/*
  SDFileIO.c:  Implementation of standard looking file I/O routines built
             on top of SDFs
	Ted Rossin:	8-14-2022
			    8-18-2022

  To do:
    1. Code up fgets correctly.  Current implementation is garbage
*/

#include <stdio.h>
#include <stdarg.h>
#include "pico/stdlib.h"


#include "SDFs.h"
#include "SDcard.h"
#include "SDFileIO.h"

int fputs (const char *__restrict s, FILE *__restrict fp)
{
    unsigned int Len;
    uint8_t Fd;
    
    if(fp==NULL) return(-1);
    Fd = fp->_file; 
    for(Len=0;s[Len];Len++);
    if(FsWrite(Fd,Len,(uint8_t *)s) != Len){
        return(-1);
    }
    return(0);
}

#define FGETS_BUFFER_SIZE	40
char *fgets(char *__restrict s,int Size,FILE *__restrict fp)
{
    uint8_t Buffer[FGETS_BUFFER_SIZE];
    int fgetsCount = 0,BackUp = 0;
    static unsigned char *ptr;
    char c,*dest,*save = s;
    unsigned char Done=0;
    uint8_t Fd;
    
    if(fp==NULL) return(NULL);
    Fd = fp->_file;  

    dest = s;
    while(--Size && !Done){
    	if(fgetsCount==0){
    	    fgetsCount = FsRead(Fd,FGETS_BUFFER_SIZE,Buffer); 
            BackUp = 0;	
			ptr = Buffer;
		}
		if(fgetsCount){
			c = *ptr++;
			*s++ = c; 
			if(c=='\n'){
				Done = 1;
			}
			fgetsCount--; BackUp++;
		}
		else{
			Done = 1;
			if(s==dest){ 
				return(NULL);
			}
		}
    }
    *s = 0;
    BackUp = FGETS_BUFFER_SIZE-BackUp;
    if(BackUp){
        FsSeek(Fd,-BackUp,1);  // From current
    }
    return(save);
}

int fseek (FILE *fp, long offset, int origin)
{
    uint8_t Fd;
    
    if(fp==NULL) return(-1);
    Fd = fp->_file;  

    return(FsSeek(Fd,offset,origin));
}

size_t fread (void *__restrict Buffer, size_t Size, size_t Num, FILE *__restrict fp)
{
    unsigned int Total;
    uint8_t Fd;
    
    if(fp==NULL) return(0);
    Fd = fp->_file; 
    
    if(Size==1) Total = Num;
    else Total = Num*Size;

    return(FsRead(Fd,Total,(uint8_t *)Buffer)/Size); 	
}

//unsigned int fwrite(unsigned char *Buffer,unsigned int Size,unsigned int Num,FILE *fp)
size_t fwrite (const void *__restrict Buffer, size_t Size, size_t Num, FILE *fp)
{
    unsigned int Total;
    uint8_t Fd;
    
    if(fp==NULL) return(0);
    Fd = fp->_file;  
    
    if(Size==1) Total = Num;
    else Total = Num*Size;

    return(FsWrite(Fd,Total,(uint8_t *)Buffer)/Size); 	
}

FILE *fopen(const char *__restrict Fname, const char *__restrict Attrib)
{
    uint8_t i,RetVal;
    static FILE FdList[NUM_FD];

    if(!FsMounted()){
        uint8_t Type;

        Type = FsMountFileSystem(FS_MOUNT_READ_WRITE);
        if(Type==SD_INVALID_CARD || Type==SD_INVALID_FS){
            return(NULL);
        }
    }
    for(i=0;i<NUM_FD;i++) FdList[i]._file = i;

	if((Attrib[0]=='r' && Attrib[1]==0) || (Attrib[0]=='r' && Attrib[1]=='b' && Attrib[2]==0)){
		RetVal = FsOpen(FS_OPEN_READ_ONLY,(char *)Fname);
		if(RetVal==FS_OPEN_FAIL) return(NULL);  
		return(&FdList[RetVal]);
    }
    if((Attrib[0]=='w' && Attrib[1]==0) || (Attrib[0]=='r' && Attrib[1]=='w' && Attrib[2]==0)){  // Write or Read/Write
		RetVal = FsOpen(FS_OPEN_READ_WRITE,(char *)Fname);
		if(RetVal==FS_OPEN_FAIL) return(NULL);  
		return(&FdList[RetVal]);
    } 
    return(NULL);  // Fail
}

long ftell(FILE *fp)
{
    uint8_t Fd;
    
    if(fp==NULL) return(-1);
    Fd = fp->_file; 

    return(FsTell(Fd));
}

int fprintf (FILE *__restrict fp, const char *__restrict format, ...)
{
    int Len;
    uint8_t Fd;
    char s[1000];
    
    if(fp==NULL) return(-1);
    Fd = fp->_file; 

    va_list argp;
    va_start(argp, format);
    vsprintf(s, format, argp);

    for(Len=0;s[Len];Len++);
    if(FsWrite(Fd,Len,(uint8_t *)s) != Len) return(0);
    va_end (argp);
    return(Len);
}

    // For some reason all these other functions can be overridden except fclose so
    // the name is changed to fclose2 and a define in FileIO.h convertes fclose calls to fclose2
//int fclose(FILE *fp)
int fclose2(FILE *fp)
{
    uint8_t Fd;
    
    if(fp==NULL) return(-1);
    Fd = fp->_file; 

	return(FsClose(Fd));
}