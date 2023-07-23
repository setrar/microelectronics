/*
   SDFs.c:  FAT 12,16 and 32 file system

 
	Ted Rossin:	 11-30-2011   8-18-2022

				 8-18-2022  Fixed up FsSeek to allow negative offset.  Also fixed FsOpen to work with a 
				 			filename from ROM (constant)
				 8-07-2022  Got things working on the Pico
				 8-05-2022  Port to Pico
    
  To do:  
	1. Look for common code to dump into subroutine to save code size.
  
  Someday:
	1. Finish FsDelete.
		a. It would be great if end of dir marker was moved forward as well but not super critical.  It just makes for long ls commands.
		b. If end of dir marker is moved out of a cluster, then it would be super if that cluster could be freed up.  So, unless a is 
		   implemented, there is no need for b.  If a is implemented and b is not, the clusters will be wasted until directory is removed.
	

*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/rtc.h"
#include <ctype.h>
#include "string.h"

#include "SDcard.h"
#include "SDFs.h"

#ifndef CACHE_SIZE
    #define CACHE_SIZE  10
#endif

#define CACHE_INVALID	0
#define CACHE_VALID		1
#define CACHE_DIRTY		2
#define CACHE_KEEP		4

#define FS_REMOVE		4
#define FS_CREATE_DIR	5
#define FS_REMOVE_DIR	6	

extern ClockType ClockFetchTime(void);
extern void ClockSetTime(ClockType It);

#define SECTOR_FETCH8(Index) SectorBuf[Index]
 // Can't do type cast due to odd address faults (bummer)
  #define SECTOR_FETCH16(Index) (((uint16_t)SectorBuf[Index+1]<<8) | (uint16_t)SectorBuf[Index+0])
  #define SECTOR_FETCH32(Index) (((uint32_t)SectorBuf[Index+3]<<24) | ((uint32_t)SectorBuf[Index+2]<<16) | ((uint32_t)SectorBuf[Index+1]<<8) | (uint32_t)SectorBuf[Index+0])
  #define SECTOR_WRITE32(Index,Val) ({SectorBuf[Index+3]=(Val)>>24; SectorBuf[Index+2]=(Val)>>16;  SectorBuf[Index+1]=(Val)>>8; SectorBuf[Index]=(Val);})         
  #define SECTOR_WRITE16(Index,Val) ({SectorBuf[Index+1]=(Val)>>8; SectorBuf[Index]=(Val);})
  #define BUF_WRITE32(Buffer,Val)   ({Buffer[3]=(Val)>>24; Buffer[2]=(Val)>>16;  Buffer[1]=(Val)>>8;  Buffer[0]=(Val);})
//  #define BUF_FETCH32(Buffer) (*(uint32_t *)Buffer)     

#define CLUSTER_NOT_FOUND 	0xffffffff
#define TEMP_BUFFER			0xffffffff
#define CLUSTER_END_OF_CHAIN	0xffffffff
#define SECTOR_NOT_FOUND	0xffffffff

#define FD_FLAGS_OPEN	    1
#define FD_FLAGS_READ_ONLY  2
#define FD_FLAGS_MKDIR		4


#define ATTR_LONG_NAME	(ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID)

    // Used for opening a file to write or read
#define ATTR_READ_WRITE			0x00
#define ATTR_MASK_READ_WRITE	0x19

    // Used for opening a file to read
#define ATTR_READ			0x00
#define ATTR_MASK_READ		0x18

    // Used for path qualification
#define ATTR_DIR			ATTR_DIRECTORY
#define ATTR_MASK_DIR		ATTR_DIRECTORY	

    // Used for directory listing
#define ATTR_READ_DIR		0x00
#define ATTR_MASK_READ_DIR	0x0e

	// Used to see if file exists before creating a directory
#define ATTR_ANY			0x00
#define ATTR_MASK_ANY		0x00

#define DIR_ENTRY_FREE		0xe5

   // Master Boot record offsets (Sector 0)
#define MBR_ACTIVE	    0x1be   // 1 byte
#define MBR_PARTITION_TYPE  0x1c2   // 1 byte
#define MBR_PARTITION_START 0x1c6   // 4 bytes
#define MBR_PARTITION_COUNT 0x1ca   // 4 bytes

#define BS_OEM_Name		3   // 8 bytes
#define BPB_BYTES_PER_SECTOR	11  // 2 bytes
#define BPB_SEC_PER_CLUSTER	13  // 1 byte
#define BPB_RSVD_SEC_CNT	14  // 2 bytes
#define	BPB_NUM_FATS		16  // 1 byte
#define BPB_ROOT_ENT_CNT	17  // 2 bytes
#define BPB_TOT_SEC16		19  // 2 bytes
#define BPB_FAT_SZ16		22  // 2 bytes
#define BPB_TOT_SEC32		32  // 4 bytes
#define BPB_ROOT_CLUS		44  // 4 bytes

static struct{
    uint16_t BytesPerSec;
    uint8_t BytesPerSecShift;
    uint16_t SecPerClus;
    uint8_t SecPerClusShift;
    uint16_t RsvdSecCnt;
    uint8_t NumFATs;
    uint16_t RootEntCnt;
    uint16_t TotSec16;
    uint16_t FATSz16;
    uint32_t TotSec32;
    uint32_t FirstClusterSector;
    uint32_t FirstRootDirSecNum;
} BSC;  // BootSectorCommon

#define BPB_FAT_SZ32		36  // 4 bytes

static struct{
    uint32_t FATSz32;
    uint32_t RootClust;   /// Root directory cluster
} BootSectorFAT32;

static struct{
    uint8_t FatType;
    uint8_t ReadOnly;
    uint8_t ValidFreeCluster;
    uint32_t FirstFATSecNum;
    uint32_t CountofClusters;
    uint32_t FreeClusterOffset;
    uint32_t NumFreeClusters;
} FatInfo;

// Saved a bunch of code space by going to individual arrays.  Having this struct size a non-power of 2 is bad.
//static struct{
//    uint8_t *Sect;
//    uint32_t Tag;
//    uint8_t State;
//} Cache[CACHE_SIZE];
static uint8_t *CacheSect[CACHE_SIZE];
static uint32_t CacheTag[CACHE_SIZE];
static uint8_t CacheState[CACHE_SIZE];

static uint8_t SectCache[CACHE_SIZE][512];
static uint8_t Lru[CACHE_SIZE];
uint8_t *SectorBuf = NULL;
static uint8_t *SectorWrBuf = NULL;

static FsStateType FsState;

/*
	// structure arrays don't seem to work correctly (for sure the debug watch window does not work
	// also, if the size is not a power of two, multiplies are required to access the element.
	
static struct {
    uint32_t StartCluster;
    uint32_t CurrentCluster;
    uint32_t Size;
    uint32_t ByteOffset;
    uint32_t CurrentSector;
    uint8_t SectorOffsetInCluster;
    uint8_t Flags;
    uint16_t  ByteOffsetInSector;
    uint32_t DirSector;
    uint16_t  DirOffsetInSector;  
} Fd[NUM_FD];
*/

static uint32_t FdStartCluster[NUM_FD];
static uint32_t FdCurrentCluster[NUM_FD];
static uint32_t FdSize[NUM_FD];
static uint32_t FdByteOffset[NUM_FD];

static uint32_t FdCurrentSector[NUM_FD];
static uint8_t FdSectorOffsetInCluster[NUM_FD];
static uint8_t FdFlags[NUM_FD];
static uint16_t  FdByteOffsetInSector[NUM_FD];
static uint32_t FdDirSector[NUM_FD];
static uint16_t  FdDirOffsetInSector[NUM_FD]; 

static void InitSectCache(void);
static uint32_t FetchFreeCluster(uint32_t StartIndex);
static uint32_t FetchFreeCount(uint32_t StartIndex);

static uint8_t ClockNotRunning = 1;

/*static struct repeating_timer TimerInfo;
static int Party = 0;

static bool ClockTick(struct repeating_timer *t)
{
	Party++;

	return(true);
}
*/
static void StartClock(void)
{
	datetime_t t;

	if(ClockNotRunning){ 
		rtc_init();

		t.year = 2022;
		t.month = 8;
		t.day = 7;
		t.hour = 15;
		t.min = 49;
		t.sec = 0;
		t.dotw = 1;

		rtc_set_datetime(&t);
		ClockNotRunning = 0;
	}
	
}

ClockType ClockFetchTime(void)
{
	datetime_t t;
	ClockType RetVal;

	rtc_get_datetime(&t);

    RetVal.Year = t.year;
    RetVal.Month = t.month;
    RetVal.Day = t.day;
    RetVal.Hour = t.hour;
    RetVal.Minute = t.min;
    RetVal.Second = t.sec;

    return(RetVal);
}

void ClockSetTime(ClockType It)
{
	datetime_t t;

	t.year = It.Year;
    t.month = It.Month;
    t.day = It.Day;
    t.hour = It.Hour;
    t.min = It.Minute;
    t.sec = It.Second;
	t.dotw = 0;

	rtc_set_datetime(&t);
}

void FsPushCdStack(void)
{
	if(FsState.CdStackPtr==CD_STACK_SIZE) return;
    FsState.CurrentDirectoryStack[FsState.CdStackPtr++] = FsState.CurrentDirCluster;
}

void FsPopCdStack(void)
{
    if(FsState.CdStackPtr==0) return;
    FsState.CurrentDirCluster = FsState.CurrentDirectoryStack[--FsState.CdStackPtr];
}

static void InitSectCache(void)
{
    uint8_t Loop;

    for(Loop=0;Loop<CACHE_SIZE;Loop++){
		CacheTag[Loop] = 0xffffffff;
        CacheState[Loop] = CACHE_INVALID;
		Lru[Loop] = Loop;
		CacheSect[Loop] = SectCache[Loop];
    }
}

static void UpdateLru(uint8_t HitId)
{
    uint8_t Index,Loop;

    for(Index=0;Index<CACHE_SIZE;Index++){
		if(HitId ==Lru[Index]){
			for(Loop=Index;Loop!=0;Loop--) Lru[Loop] = Lru[Loop-1];
			Lru[0] = HitId;
		}
    }
}

uint8_t ReadSector(uint32_t Addr)
{
    uint8_t Index,Resp;

    for(Index=0;Index<CACHE_SIZE;Index++){
		if(CacheTag[Index]==Addr && (CacheState[Index] & CACHE_VALID)){
			SectorBuf = CacheSect[Index];
			UpdateLru(Index);
			return(0);  // Hit Cache
		}
    }
    
		// Missed the cache so pick a victim and load the sector into the cache
    for(Resp=CACHE_SIZE-1;Resp!=0xff;Resp--){
		Index = Lru[Resp];
		if(!(CacheState[Index] & CACHE_KEEP)) break;
	}
	if(Resp==0xff) return(0xff);  // Cache is messed up.  All entries are marked keep.  Should only be one.	
    if((CacheState[Index] & (CACHE_VALID | CACHE_DIRTY))==(CACHE_VALID|CACHE_DIRTY)){ // Have to write back old data
		Resp = SDWriteSector(CacheTag[Index],CacheSect[Index]);
		if(Resp) return(Resp);
		CacheState[Index] = CACHE_VALID;
	}
    Resp = SDReadSector(Addr,CacheSect[Index]);
    if(Resp) return(Resp); // Error encountered
    CacheTag[Index] = Addr;
    CacheState[Index] = CACHE_VALID;
    SectorBuf = CacheSect[Index];
	UpdateLru(Index);
    return(0);
}

static uint8_t FlushCache(void)
{
    uint8_t Index,Resp;

    for(Index=0;Index<CACHE_SIZE;Index++){
		if((CacheState[Index] & (CACHE_VALID | CACHE_DIRTY))==(CACHE_VALID|CACHE_DIRTY)){
			Resp = SDWriteSector(CacheTag[Index],CacheSect[Index]);
			CacheState[Index] = CACHE_VALID;
		}
    }
    return(0);
}
    
	// Points SectorWrBuf to a cache buffer and prevents the buffer
	// from being used for other reads.
	//  1. AllocateSectorBuffer
	//  2. write crap into SectorWrBuf[0 to 511]
	//  3. DeallocateSectorBuffer to throw changes away and free up the buffer to be used by the read cache again.
static uint8_t AllocateSectorBuffer(uint32_t Addr)
{
    uint8_t Index,Resp,*ptr;
    uint16_t It;

		// Make sure address is not already in use

   for(Index=0;Index<CACHE_SIZE;Index++){
		if(CacheTag[Index]==Addr && (CacheState[Index] & CACHE_VALID)){
			break;  // Found a hit
		}
    }		
		// Pick a victim using Least Recently Used array if missed the cache
	if(Index==CACHE_SIZE) Index = Lru[CACHE_SIZE-1];
    if((CacheState[Index] & (CACHE_VALID | CACHE_DIRTY))==(CACHE_VALID | CACHE_DIRTY)){ // Have to write back old data
		Resp = SDWriteSector(CacheTag[Index],CacheSect[Index]);
		if(Resp) return(Resp);
	}
	CacheTag[Index] = Addr;
	CacheState[Index] = CACHE_VALID | CACHE_DIRTY | CACHE_KEEP;
	SectorWrBuf = CacheSect[Index];
		// Zero out buffer
	ptr = SectorWrBuf;
	for(It=0;It<512;It++) *ptr++ = 0;
    return(0);
}
	// Throws away allocated sector buffer
static uint8_t DeallocateSectorBuffer(uint32_t Addr)
{
   uint8_t Index;
   
   for(Index=0;Index<CACHE_SIZE;Index++){
		if(CacheTag[Index]==Addr && (CacheState[Index] & CACHE_KEEP)){
			CacheState[Index] = CACHE_INVALID;
			return(0);
		}
    }
    return(0xff);  // Entry not found
}

static uint8_t MarkSectorBufferDirty(uint32_t Addr)
{
   uint8_t Index;
   
   for(Index=0;Index<CACHE_SIZE;Index++){
		if(CacheTag[Index]==Addr && (CacheState[Index] & CACHE_VALID)){
			CacheState[Index] = CACHE_VALID | CACHE_DIRTY;	
			return(0);
		}
    }
    return(0xff);  // Entry not found
}

static uint8_t EndOfChain(uint32_t Cluster)
{
    if(FatInfo.FatType==32){
		if(Cluster >= 0x0ffffff8) return(1);
    }
    if(FatInfo.FatType==16){
		if(Cluster >= 0xfff8) return(1);
    }
    if(FatInfo.FatType==12){
		if(Cluster >= 0xff8) return(1);
    }
    if(Cluster==0) return(1);  // Tolerate faults
    return(0);
}

static uint32_t FetchFat(uint32_t Index)
{
    uint32_t Offset,Sector;
    uint8_t Save;

    Offset = (FatInfo.FatType==32) ? (Index<<2)
								   : (FatInfo.FatType==16) ? (Index<<1) : Index + (Index>>1);
    Sector = FatInfo.FirstFATSecNum + (Offset>>9);
    Offset = Offset & 0x1ff;
    if(ReadSector(Sector)){
		//printf("Unable to read sector 0x%x\n",Sector);
		return(0xffffffff);
    }
    if(FatInfo.FatType==32){
		return(SECTOR_FETCH32(Offset) & 0x0fffffff);
    }
    if(FatInfo.FatType==16){
		return(SECTOR_FETCH16(Offset));
    }

	// Ugly FAT 12 code
    if(Offset == 511){ // Bummer FAT12 entry spans two sectors
		Save = SectorBuf[511];
		if(ReadSector(Sector+1)){
			//printf("Unable to read sector 0x%x\n",Sector+1);
			return(0xffffffff);
		}
		return( (SectorBuf[0]<<4) | (Save>>4));
    }
    else{
		if(Index & 1){
			return((SectorBuf[Offset+1]<<4) | (SectorBuf[Offset+0]>>4));
		}
		else{
			return(((SectorBuf[Offset+1]&0x0f)<<8) | SectorBuf[Offset+0]);
		}
    }
}

static uint8_t WriteFat(uint32_t Index,uint32_t Value)
{	
    uint32_t Offset,Sector,Tmp;
    uint8_t Save;

    Offset = (FatInfo.FatType==32) ? (Index<<2)
								   : (FatInfo.FatType==16) ? (Index<<1) : Index + (Index>>1);
    Sector = FatInfo.FirstFATSecNum + (Offset>>9);
    Offset = Offset & 0x1ff;
    if(ReadSector(Sector)){
		//printf("Unable to read sector 0x%x\n",Sector);
		return(0xff);
    }
    MarkSectorBufferDirty(Sector);
    if(FatInfo.FatType==32){
			// Only write low 28-bits (those are the rules)
        Tmp = (Value & 0x0fffffff) | (SECTOR_FETCH32(Offset) & 0xf0000000);
		SECTOR_WRITE32(Offset,(Value & 0x0fffffff) | (SECTOR_FETCH32(Offset) & 0xf0000000));
		return(0);
    }
    if(FatInfo.FatType==16){
//        SectorBuf[Offset+1]=(Value)>>8; SectorBuf[Offset]=(Value);;
		SECTOR_WRITE16(Offset,Value & 0xffff);
		return(0);
    }

		// Ugly FAT 12 code
    if(Offset==511){ // Bummer FAT12 entry spans two sectors
		Save = SectorBuf[511];
			// Write Value[3:0] into SectorBuf[511][7:4]
		SectorBuf[511] = ((Value & 0x0f)<<4) | (Save & 0x0f);
		if(ReadSector(Sector+1)){
			//printf("Unable to read sector 0x%x\n",Sector+1);
			return(0xff);
		}
		MarkSectorBufferDirty(Sector+1);
			// Write Value[11:4] into SectorBuf[0][7:0]
		SectorBuf[0] = Value>>4;
    }
    else{
		if(Index & 1){
				// Write Value[11:4] to Offset+1[7:0] and Value[3:0] to Offset+0[7:4]
			SectorBuf[Offset+1] = Value>>4;
			Save = SectorBuf[Offset+0] & 0x0f;
			SectorBuf[Offset+0] = ((Value & 0x0f)<<4) | Save;
		}
		else{
				// Write Value[11:8] to Offset+1[3:0] and Value[7:0] to Ofset+0
			Save = SectorBuf[Offset+1] & 0xf0;
			SectorBuf[Offset+1] = Save | (Value>>8);
			SectorBuf[Offset+0] = Value & 0xff;
		}
    }
    return(0);
}

void FsInit(void)
{
	uint8_t Index;
		
	InitSectCache();	
	for(Index=0;Index<NUM_FD;Index++){
		FdFlags[Index]=0;
	}
	FsState.CdStackPtr = 0;
	FsState.ShortMode = 0;
	FsState.CurrentDirCluster = 0; // Root directory
	FatInfo.NumFreeClusters = 0;
	FatInfo.FreeClusterOffset = 0xffffffff;
	FatInfo.ReadOnly = 1;
    FatInfo.ValidFreeCluster = 0;
	BSC.BytesPerSecShift = 0;  // Way to mark file system as unmounted
}

void FsUnmountFileSystem(void)
{
	uint8_t FdIndex;
	
	for(FdIndex=0;FdIndex<NUM_FD;FdIndex++){
		FsClose(FdIndex);
	}
	FlushCache();
	FsInit();  // Reset all the state to unmounted system.
}

uint8_t FsMountFileSystem(uint8_t Flags)
{
	uint8_t Type,Resp;
    uint16_t RootDirSectors;
    uint32_t FATSz;
    uint32_t TotSec;
    uint8_t Shift;
    uint16_t PartitionStartSector;

	FsInit();
	if(ClockNotRunning) StartClock();
	Type = SDInit();
	if(Type==SD_INVALID_CARD){
//puts("SDFs: SDInit() call failed\r\n");
		return(SD_INVALID_CARD);		
	}
//puts("SDFs: past SDInit()\r\n");
		// Fetch Master Boot record
    if((Resp=ReadSector(0))){
//puts("SDFs: ReadSector(0) failed\r\n");        
		return(SD_INVALID_CARD);
    }
    PartitionStartSector = SECTOR_FETCH32(MBR_PARTITION_START);

    if(ReadSector(PartitionStartSector)){
//puts("SDFs: ReadSector(PartitionStartSector) failed\r\n");        
		return(SD_INVALID_CARD);
    }
//puts("SDFs: loading up structures\r\n");
		// Populate the data structure

    BSC.BytesPerSec = SECTOR_FETCH16(BPB_BYTES_PER_SECTOR);
    if(BSC.BytesPerSec != 512){
//puts("Bytes per sector is not 512 so can't play\r\n");	
		return(SD_INVALID_FS);
    }
    BSC.BytesPerSecShift = 9;
    BSC.SecPerClus = SECTOR_FETCH8(BPB_SEC_PER_CLUSTER);
    for(Shift=0;Shift<8;Shift++){
		if((1<<Shift) == BSC.SecPerClus) break;
    }
    BSC.SecPerClusShift = Shift;
    BSC.RsvdSecCnt = SECTOR_FETCH16(BPB_RSVD_SEC_CNT);
    BSC.NumFATs = SECTOR_FETCH8(BPB_NUM_FATS);
    BSC.RootEntCnt = SECTOR_FETCH16(BPB_ROOT_ENT_CNT);
    BSC.TotSec16 = SECTOR_FETCH16(BPB_TOT_SEC16);
    BSC.FATSz16 = SECTOR_FETCH16(BPB_FAT_SZ16);
    BSC.TotSec32 = SECTOR_FETCH32(BPB_TOT_SEC32);

    BootSectorFAT32.FATSz32 = SECTOR_FETCH32(BPB_FAT_SZ32);
    BootSectorFAT32.RootClust = SECTOR_FETCH32(BPB_ROOT_CLUS);

        // directory entries are 32 bytes
    RootDirSectors = ((BSC.RootEntCnt<<5) + (BSC.BytesPerSec-1)) >> BSC.BytesPerSecShift;
    FATSz = (BSC.FATSz16 != 0) ? BSC.FATSz16 : BootSectorFAT32.FATSz32;
   
    FatInfo.FirstFATSecNum = PartitionStartSector + BSC.RsvdSecCnt;

		//BSC.FirstRootDirSecNum = FatInfo.FirstFATSecNum + (BSC.NumFATs * FATSz);
    BSC.FirstRootDirSecNum = FatInfo.FirstFATSecNum;
    for(Shift=0;Shift<BSC.NumFATs;Shift++){
		BSC.FirstRootDirSecNum += FATSz;
    }
		// This is the first sector of cluster 2 (later 2 sectors will be subtracted to get to first sector of cluster 0
    BSC.FirstClusterSector = BSC.FirstRootDirSecNum + RootDirSectors;
    TotSec = (BSC.TotSec16 != 0) ? BSC.TotSec16 : BSC.TotSec32;
    FatInfo.CountofClusters = (TotSec - BSC.FirstClusterSector) >> BSC.SecPerClusShift;
    BSC.FirstClusterSector -= (BSC.SecPerClus + BSC.SecPerClus);

    if(FatInfo.CountofClusters < 4085){
		FatInfo.FatType = 12;
    }else if(FatInfo.CountofClusters < 65525){
		FatInfo.FatType = 16;
    }
    else{
		FatInfo.FatType = 32;
    }

    FatInfo.ReadOnly = Flags & FS_MOUNT_READ_ONLY;
    if(!FatInfo.ReadOnly){
		FatInfo.FreeClusterOffset = FetchFreeCluster(2);
		if(FatInfo.FreeClusterOffset == 0xffffffff){
			FatInfo.NumFreeClusters = 0;
		}
		else{
            FatInfo.ValidFreeCluster = 0; 
            FatInfo.NumFreeClusters = 0xffffffff;
		}
	}
	return(Type);
}

//Load up GetNextSec.Cluster and .SectInCluster with current cluster and sector offset in cluster.
//Then call GetNextSector to advance to next sector.  GetNextSector will return SECTOR_NOT_FOUND if
// it runs into a problem.
static struct{
    uint32_t Cluster;
    uint16_t SectInCluster;
} GetNextSec;
static uint32_t GetNextSector(uint8_t Amount)
{
    uint32_t ClustSect;
    
    GetNextSec.SectInCluster+=Amount;
    if(GetNextSec.SectInCluster >= BSC.SecPerClus){
    	GetNextSec.SectInCluster = 0;
		GetNextSec.Cluster = FetchFat(GetNextSec.Cluster);
		if(EndOfChain(GetNextSec.Cluster)){
			return(SECTOR_NOT_FOUND);
		}
	}
		// This evilness should be in a common function.
    if(GetNextSec.Cluster==0){ // Root Directory 
		if(FatInfo.FatType==32){
			ClustSect = BSC.FirstClusterSector + (BootSectorFAT32.RootClust << BSC.SecPerClusShift);
		}
		else{
			ClustSect = BSC.FirstRootDirSecNum;
		}
    }	
    else{
		ClustSect = BSC.FirstClusterSector;
	}
	
	return(ClustSect + (GetNextSec.Cluster << BSC.SecPerClusShift) + GetNextSec.SectInCluster);
}

static struct{
    uint32_t Cluster;  // Current cluster being accessed
    uint32_t ClustSect;// First sector of the cluster
    uint16_t SectIndex; // Sector index inside the cluster  
    uint16_t Index;     // Index inside the sector
//    uint8_t Flags;	//  0=EmptyCheck,1=Empty
}DirState;

uint8_t FsGetFirstDir(char *Name,FsDirInfo *Info)
{
    uint8_t Resp;

    if(FsState.CurrentDirCluster==0){ // Root Directory 
		if(FatInfo.FatType==32){
			DirState.ClustSect = BSC.FirstClusterSector + (BootSectorFAT32.RootClust << BSC.SecPerClusShift);
			DirState.Cluster = BootSectorFAT32.RootClust;
		}
		else{
			DirState.ClustSect = BSC.FirstRootDirSecNum;
			DirState.Cluster = 0;
		}
    }
    else{
		DirState.ClustSect = BSC.FirstClusterSector + (FsState.CurrentDirCluster << BSC.SecPerClusShift);
		DirState.Cluster = FsState.CurrentDirCluster;
    }
    DirState.SectIndex = 0;
    DirState.Index = 0;
	Resp = FsGetNextDir(Name,Info);
	return(Resp);
}

uint8_t FsGetNextDir(char *Name,FsDirInfo *Info)
{
    uint8_t i,Done=0;
    //uint32_t FileCluster,FileSize;
    char ShortName[13],*ptr;
    //uint8_t Buf[4];
    uint8_t LdirCheckSum=0,LdirValid,LastWasLongDir=0;
    char LongName[256];

		// If file system is not mounted
	if(BSC.BytesPerSecShift==0) return(0xff);
	
		// Rely on sector cache to make this only read the SD memory when the sector changes
    if(ReadSector(DirState.ClustSect+DirState.SectIndex)){
		return(0xff);
    }

    while(!Done){
		if(DirState.Index==512){
			DirState.Index = 0;  DirState.SectIndex++;
			if(DirState.Cluster==0){  // Traversing root directory on FAT12 or FAT16 volume
				if(DirState.SectIndex>(BSC.RootEntCnt>>5)){
					//printf("Didn't find last directory marker for root directory\n");
					//printf("End of Directory\n");
					return(0xff);
				}
			}
			else if(DirState.SectIndex>BSC.SecPerClus){ // Need to get next cluster chain value
				DirState.SectIndex = 0;
				DirState.Cluster = FetchFat(DirState.Cluster);
				if(EndOfChain(DirState.Cluster)){
					//printf("End of Directory\n");
					Info->Size = 0;
					Name[0] = 0;
					return(0);					
				}
				DirState.ClustSect = BSC.FirstClusterSector 
						   + (DirState.Cluster << BSC.SecPerClusShift);
			}
		
			if(ReadSector(DirState.ClustSect+DirState.SectIndex)){
				//printf("Unable to read sector %d\n",DirState.ClustSect + DirState.SectIndex);
				return(0xff);
			}
		}
		if(SectorBuf[DirState.Index]==DIR_ENTRY_FREE){  // Free directory slot
			LastWasLongDir = 0;
		}
		else if(SectorBuf[DirState.Index]==0){  // Remaining indexes are free
			//printf("End of Directory\n");
			Info->Size = 0;
			Name[0] = 0;
			return(0);
		}
		else{
			if(SectorBuf[DirState.Index+11]==0xf){  // Long Dir Attribute
				uint8_t Offset = ((SectorBuf[DirState.Index+0] & 0x3f)-1);
				Offset = (Offset<<3) + (Offset<<2) + Offset; // *13
				for(i=1;i<10;i+=2) LongName[Offset++]=SectorBuf[DirState.Index+i];
				for(i=14;i<26;i+=2) LongName[Offset++]=SectorBuf[DirState.Index+i];
				for(i=28;i<32;i+=2) LongName[Offset++]=SectorBuf[DirState.Index+i];
				if(SectorBuf[DirState.Index+0] & 0x40){
					LongName[Offset] = 0;  // Just in case.
					LdirCheckSum = SectorBuf[DirState.Index+13];
				}
				else{
					if(LdirCheckSum != SectorBuf[DirState.Index+13]){ // Corrupted long dir entry
						LdirCheckSum = 0;
					}
				}
				LastWasLongDir = 1;
			}
			else{
					// Copy base name
					// Short name is padded with spaces so no need for NULL check just copy 11 bytes  
				for(i=0;i<11;i++){
					ShortName[i] = SectorBuf[DirState.Index+i];
				}
				ShortName[11]=0;
				if(SectorBuf[DirState.Index+11] & 8){  // Volumne Label
					for(i=10;i!=0 && ShortName[i]==' ';i--) ShortName[i]=0;
					LdirValid = 0;  LastWasLongDir = 0;
				}
				else{  
					for(i=7;i!=0 && ShortName[i]==' ';i--) ShortName[i]='.';
					i+=2;  ShortName[i-1] = '.';
					if(SectorBuf[DirState.Index+8]!=' '){
						ShortName[i  ] = SectorBuf[DirState.Index+8];
						ShortName[i+1] = SectorBuf[DirState.Index+9];
						ShortName[i+2] = SectorBuf[DirState.Index+10];
						ShortName[i+3] = 0;
						if(ShortName[i+2]==' ') ShortName[i+2] = 0;
						if(ShortName[i+1]==' ') ShortName[i+1] = 0;
					}
					else{
						ShortName[i-1] = 0;
					}
						// Compute SumCheck of Name for long dir support
					LdirValid = 0;
					if(LastWasLongDir){
						uint8_t Tmp,Sum = 0;
						for (i=0; i<11; i++) {
							//Sum = ((Sum & 1) ? 0x80 : 0) + (Sum >> 1) + SectorBuf[DirState.Index+i];
                            Tmp = (Sum>>1) + SectorBuf[DirState.Index+i];
                            if(Sum&1) Sum = Tmp + 0x80;
                            else      Sum = Tmp;
						}
						if(Sum==LdirCheckSum) LdirValid=1;
					}
				}

				//FileSize = SECTOR_FETCH32(DirState.Index+28);
				ptr = (LdirValid && !FsState.ShortMode) ? LongName : ShortName;
				while(*ptr) *Name++ = *ptr++;
				*Name = 0; // NULL terminator
				Info->Attrib = SectorBuf[DirState.Index+11];
				Info->Size = SECTOR_FETCH32(DirState.Index+28);
				Info->ModDate = SECTOR_FETCH16(DirState.Index+24);
				Info->ModTime = SECTOR_FETCH16(DirState.Index+22);
				LastWasLongDir = 0;
				Done = 1;
			}
		}
		DirState.Index += 32;
    }
	return(0);   
}

static uint32_t FindFile(char *Name,uint32_t ClusterStart,uint8_t Attrib, uint8_t AttribMask,uint8_t FdIndex);
static uint32_t GetClusterName(uint32_t SearchCluster,uint32_t ClusterStart,uint8_t Attrib, uint8_t AttribMask);

static uint32_t GetPathClusterOfPath(char *Name)
{
    uint32_t Cluster = FsState.CurrentDirCluster;
    char KeepGoing;
    uint8_t StartIndex,Index;
    
    StartIndex = 0;
    if(Name[0]=='/'){  // Absolute path
		Cluster = 0;
		StartIndex++;
    }
    while(1){
		for(Index=StartIndex;Name[Index] != '/' && Name[Index];Index++);
		KeepGoing = (Name[Index]=='/') ? 1 : 0;
		Name[Index] = 0;
		if(Index==StartIndex){
			return(Cluster);
		}
	
		Cluster = FindFile(&Name[StartIndex],Cluster,ATTR_DIR,ATTR_MASK_DIR,0xff);
		if(Cluster==CLUSTER_NOT_FOUND){
			return(CLUSTER_NOT_FOUND);
		}
		if(!KeepGoing){
			return(Cluster);
		}	    
		StartIndex = Index+1;
   }
}

// Origin 0: SEEK_SET (from begining of file)
//        1: SEEK_CUR (from current location)
//        2: SEEK_END (from end of file)

uint8_t FsSeek(uint8_t FdIndex,int32_t Offset,uint8_t Origin)
{
    uint32_t NewByteOffset;
    uint32_t NewSectorOffset,NewClusterOffset;
    uint32_t CurSectorOffset,CurClusterOffset;
    uint32_t Cluster,Loop,NumClustersToWalk;

    if(FdIndex>= NUM_FD){
		return(0xff);
    }
    if(!(FdFlags[FdIndex] & FD_FLAGS_OPEN)){
		return(0xff);
    }

    if(Origin==0){
		NewByteOffset = Offset;	
    }
    else if(Origin==1){
		if((int32_t)FdByteOffset[FdIndex] + Offset <0)
			NewByteOffset = 0;
		else
			NewByteOffset = FdByteOffset[FdIndex] + Offset;
    }
    else if(Origin==2){
		if(Offset < FdSize[FdIndex]){
			NewByteOffset = FdSize[FdIndex] - Offset;
		}
		else{
			NewByteOffset = 0;
		}
    }
    else{
		NewByteOffset = 0;
    }
    if(NewByteOffset>=FdSize[FdIndex]) NewByteOffset = (FdSize[FdIndex]) ? FdSize[FdIndex]-1 : 0;


    CurSectorOffset = FdByteOffset[FdIndex]>>BSC.BytesPerSecShift;
    CurClusterOffset = CurSectorOffset>>BSC.SecPerClusShift;

    FdByteOffset[FdIndex] = NewByteOffset;
    FdByteOffsetInSector[FdIndex] = NewByteOffset & ((1<<BSC.BytesPerSecShift)-1);

    NewSectorOffset = NewByteOffset>>BSC.BytesPerSecShift;
    if(NewSectorOffset==CurSectorOffset){
		return(0);
    }
    NewClusterOffset = NewSectorOffset>>BSC.SecPerClusShift;
   
    FdSectorOffsetInCluster[FdIndex] = NewSectorOffset & ((1<<BSC.SecPerClusShift)-1);

    if(NewClusterOffset==CurClusterOffset){
		FdCurrentSector[FdIndex] = BSC.FirstClusterSector 
								  + (FdCurrentCluster[FdIndex]<<BSC.SecPerClusShift) 
								  + FdSectorOffsetInCluster[FdIndex];
		return(0);
    }
    
        // Need to walk FAT table to go N cluster
    if(NewClusterOffset < CurClusterOffset){
		Cluster = FdStartCluster[FdIndex];
		NumClustersToWalk = NewClusterOffset;
    }
    else{
		Cluster = FdCurrentCluster[FdIndex];
		NumClustersToWalk = NewClusterOffset-CurClusterOffset;
    }
    for(Loop=0;Loop<NumClustersToWalk;Loop++){
		Cluster = FetchFat(Cluster);
		if(Cluster==0xffffffff || Cluster==0){
			return(0xff);
		}
    }
    FdCurrentCluster[FdIndex] = Cluster;
    FdCurrentSector[FdIndex] = BSC.FirstClusterSector 
							  + (Cluster<<BSC.SecPerClusShift) 
							  + FdSectorOffsetInCluster[FdIndex];
	return(0);
}

static void WriteStartCluster(uint8_t FdIndex,uint16_t Offset)
{
    uint8_t Buf[4];

	BUF_WRITE32(Buf,FdStartCluster[FdIndex]);
	SectorBuf[Offset+20+1] = Buf[3];   	SectorBuf[Offset+20+0] = Buf[2];
	SectorBuf[Offset+26+1] = Buf[1];	SectorBuf[Offset+26+0] = Buf[0];
}

static void LoadDateTime(uint16_t DirOffset)
{
		/*
		Bits 0-4: Day of month, valid value range 1-31 inclusive.
		Bits 5-8: Month of year, 1 = January, valid value range 1-12 inclusive.
		Bits 9-15: Count of years from 1980, valid value range 0-127 inclusive (1980-2107).
		
		Bits 0-4: 2-second count, valid value range 0-29 inclusive (0 - 58 seconds).
		Bits 5-10: Minutes, valid value range 0-59 inclusive.
		Bits 11-15: Hours, valid value range 0-23 inclusive.
		*/
    uint16_t Val;
    ClockType CurrentTime;
    
    CurrentTime = ClockFetchTime();
    
    Val = ((CurrentTime.Year-1980)<<9) | (CurrentTime.Month<<5) | (CurrentTime.Day);
	SECTOR_WRITE16(24+DirOffset,Val);  //ModDate
	Val = ((CurrentTime.Hour)<<11) | (CurrentTime.Minute<<5) | (CurrentTime.Second>>1);
	SECTOR_WRITE16(22+DirOffset,Val);  //ModTime
}

uint8_t FsClose(uint8_t FdIndex)
{
    uint16_t Offset;
    uint8_t i;

    if(FdIndex>= NUM_FD){
		return(0xff);
    }
    if(FdFlags[FdIndex]==0) return(0xff);  // Already closed
    
	if(FdFlags[FdIndex] & FD_FLAGS_MKDIR){
		if(ReadSector(FdDirSector[FdIndex])){
			return(0xFF);
		}
		Offset = FdDirOffsetInSector[FdIndex];
		MarkSectorBufferDirty(FdDirSector[FdIndex]);
		SectorBuf[Offset+11] = ATTR_DIRECTORY;
		WriteStartCluster(FdIndex,Offset);
		for(i=28;i<32;i++) SectorBuf[Offset+i] = 0;	// File size is zero.
		LoadDateTime(Offset);
	}
	else if(!(FdFlags[FdIndex] & FD_FLAGS_READ_ONLY)){
		uint32_t FileSize;
			// May need to update file size
		if(ReadSector(FdDirSector[FdIndex])){
			return(0xFF);
		}
		Offset = FdDirOffsetInSector[FdIndex];
		FileSize = SECTOR_FETCH32(Offset+28);
		if(FileSize != FdSize[FdIndex]){
			//MarkSectorBufferDirty(FdDirSector[FdIndex]);
			SECTOR_WRITE32(Offset+28,FdSize[FdIndex]);
		}       
			// Need to write start cluster
//		Buf[3] = SectorBuf[Offset+20+1];   	Buf[2] = SectorBuf[Offset+20+0];
//		Buf[1] = SectorBuf[Offset+26+1];	Buf[0] = SectorBuf[Offset+26+0];
//		FileSize = BUF_FETCH32(Buf);
        FileSize = ((uint32_t)SectorBuf[Offset+20+1]<<24) | ((uint32_t)SectorBuf[Offset+20+0]<<16)
                 | ((uint32_t)SectorBuf[Offset+26+1]<< 8) | ((uint32_t)SectorBuf[Offset+26+0]<< 0);               
		if(FileSize != FdStartCluster[FdIndex]){
			//MarkSectorBufferDirty(FdDirSector[FdIndex]);
			WriteStartCluster(FdIndex,Offset);
		}
		LoadDateTime(Offset);
		MarkSectorBufferDirty(FdDirSector[FdIndex]);
	}
	FlushCache();
	FdFlags[FdIndex] = 0;
	
    return(0);
}

static void UpdateFdState(uint8_t FdIndex,uint16_t Offset)
{
    FdByteOffset[FdIndex] += Offset;
    FdByteOffsetInSector[FdIndex] += Offset;
    if(FdByteOffsetInSector[FdIndex]==512){
		FdByteOffsetInSector[FdIndex] = 0;
		FdSectorOffsetInCluster[FdIndex]++;
		FdCurrentSector[FdIndex]++;
		if(FdSectorOffsetInCluster[FdIndex]==BSC.SecPerClus){
			FdSectorOffsetInCluster[FdIndex] = 0;
			FdCurrentCluster[FdIndex] = FetchFat(FdCurrentCluster[FdIndex]);
			FdCurrentSector[FdIndex] = BSC.FirstClusterSector + (FdCurrentCluster[FdIndex]<<BSC.SecPerClusShift);
		}
    }
}

uint16_t FsRead(uint8_t FdIndex, uint16_t Count, uint8_t *Data)
{
    uint16_t Index,Loop;
    uint32_t Remain;
    uint8_t *ptr;
	uint16_t ReturnCount;

    if(FdIndex>= NUM_FD){
		return(0);
	}
	if(!(FdFlags[FdIndex] & FD_FLAGS_OPEN)){
		return(0);
	}
	Remain = FdSize[FdIndex] - FdByteOffset[FdIndex];
	if(Count>Remain) Count = Remain;

	if(Count==0) return(0);
	ReturnCount = Count;
	while(1){
		if(ReadSector(FdCurrentSector[FdIndex])){
			return(0);
		}
		ptr = &SectorBuf[FdByteOffsetInSector[FdIndex]];
		Index = FdByteOffsetInSector[FdIndex];
		if(Count+Index > 512){
			Loop = 512-Index;
		}
		else{
			Loop = Count;
		}
		for(Index=0;Index<Loop;Index++){
			*Data++ = *ptr++;
		}
		Count -= Loop;
		UpdateFdState(FdIndex,Loop);
		if(Count==0){
			return(ReturnCount);
		}
    }
    return(0);
}

uint16_t FsWrite(uint8_t FdIndex, uint16_t Count, uint8_t *Data)
{
    uint16_t Index;

    if(FdIndex>= NUM_FD){
		return(0);    
	}
	if(!(FdFlags[FdIndex] & FD_FLAGS_OPEN)){
		return(0);
	}

    uint8_t NewClusterAllocated;
    
    if(FdCurrentSector[FdIndex] != 0){    
		if(ReadSector(FdCurrentSector[FdIndex])){
			return(0);
		}
		MarkSectorBufferDirty(FdCurrentSector[FdIndex]);  // Bug fix for problem Jens found
	}

	for(Index=0;Index<Count;Index++){
		if(FdByteOffsetInSector[FdIndex]==0){ // Need new sector
			NewClusterAllocated = 0;
			if(FdSectorOffsetInCluster[FdIndex]==0){  // Need new or next cluster
				if(FdByteOffset[FdIndex]>=FdSize[FdIndex]){ // Need new cluster
							// Allocate new cluster to chain.
					if(FatInfo.NumFreeClusters==0){
						return(Index);  // No more space to add another directory
					}
					uint32_t NewCluster;
					NewCluster = FetchFreeCluster(FatInfo.FreeClusterOffset);
					if(NewCluster==0xffffffff){						
						return(Index);  // No more space to add another directory					
					}
					if(FdByteOffset[FdIndex]==0){  // Need to save start cluster in directory on close
						FdStartCluster[FdIndex] = NewCluster;
					}
					WriteFat(NewCluster,CLUSTER_END_OF_CHAIN);
					WriteFat(FdCurrentCluster[FdIndex],NewCluster);
					FdCurrentCluster[FdIndex] = NewCluster;
	
					FatInfo.FreeClusterOffset++;
					FatInfo.NumFreeClusters--;
					NewClusterAllocated = 1;
				}
				else{  // Need next cluster
						// If first 
					if(FdByteOffset[FdIndex]!=0){ // If start of existing file there is no need for new cluster
						FdCurrentCluster[FdIndex] = FetchFat(FdCurrentCluster[FdIndex]);
						if(EndOfChain(FdCurrentCluster[FdIndex])){ // File is corrupted						
							return(Index);  // No more space						
						}
					}
				}
				FdCurrentSector[FdIndex] = BSC.FirstClusterSector + (FdCurrentCluster[FdIndex]<<BSC.SecPerClusShift);
			}  // End of next cluster
			if(NewClusterAllocated){
				if(AllocateSectorBuffer(FdCurrentSector[FdIndex])){
					return(Index);
				}
				SectorBuf = SectorWrBuf;
				MarkSectorBufferDirty(FdCurrentSector[FdIndex]);
			}
			else{
				if(ReadSector(FdCurrentSector[FdIndex])){
					return(Index);
				}
				MarkSectorBufferDirty(FdCurrentSector[FdIndex]);			
			}
		}  // End of Need new sector
		
			// Write the byte!			
		SectorBuf[FdByteOffsetInSector[FdIndex]++] = *Data++;
			// Check to see if end of sector.
		if(FdByteOffsetInSector[FdIndex]==512){ 
			FdByteOffsetInSector[FdIndex] = 0;
			FdCurrentSector[FdIndex]++;
			FdSectorOffsetInCluster[FdIndex]++;
			if(FdSectorOffsetInCluster[FdIndex]==BSC.SecPerClus){
				FdSectorOffsetInCluster[FdIndex] = 0;
			}
		}
		FdByteOffset[FdIndex]++;

// REVISIT: It seems that this could be done only at sector boundary when ByteOffsetInSector is 0 or on exit
		if(FdByteOffset[FdIndex]>=FdSize[FdIndex]) FdSize[FdIndex]=FdByteOffset[FdIndex];
	}

    return(Count);
}

static void MakeDirEntry(uint8_t DotDotMode,uint32_t Cluster)
{
	uint8_t Buf[4],Len;
	uint8_t Offset = DotDotMode ? 32 : 0;
	
	SectorBuf[Offset+0] = '.';
	SectorBuf[Offset+1] = (DotDotMode) ? '.' : ' ';
	for(Len=Offset+2;Len<Offset+11;Len++) SectorBuf[Len] = ' ';
	SectorBuf[Offset+11] = ATTR_DIRECTORY;
	BUF_WRITE32(Buf,Cluster);
	SectorBuf[Offset+20+1] = Buf[3];   	SectorBuf[Offset+20+0] = Buf[2];
	SectorBuf[Offset+26+1] = Buf[1];	SectorBuf[Offset+26+0] = Buf[0];
	LoadDateTime(Offset);
}

	// Mode == 1 is Read only
	// Mode == 2 is Read/Write	
    // Mode == 3 is Write (erases previous version and starts fresh)  Need to free up clusters.
    // Mode == 4 is remove file
    // Mode == 5 is create directory
    // Mode == 6 is remove directory
uint8_t FsOpen(uint8_t Mode,char *Name)
{
    uint8_t Len,Index;
    uint8_t Byte;
    uint8_t PathFound=0;
    uint32_t Cluster,SaveCluster;
    uint8_t Attr,AttrMask;
	char Path[500];

		// If file system is not mounted
	if(BSC.BytesPerSecShift==0) return(FS_OPEN_FAIL);

	Len = strlen(Name);;

    if(Len==0) return(0xff);
	
    for(Index=Len-1;Index!=0;Index--){
    	if(Name[Index]=='/'){
			strncpy(Path,Name,500);	// Required as name could come from ROM so can't set elements to zero.
			Path[Index] = 0;
			PathFound = 1;
			break;
		}
    }
    if(PathFound){  // Absolute path
		Cluster = GetPathClusterOfPath(Path);
		if(Cluster==CLUSTER_NOT_FOUND) return(0xff);
		Index++;
    }
    else{
		if(Name[0]=='/'){
			Cluster = 0;
			Index = 1;
		}
		else{
			Cluster = FsState.CurrentDirCluster;
			Index = 0;
		}
    }
    if(Mode==FS_OPEN_READ_WRITE || Mode==FS_OPEN_WRITE){
		Attr = ATTR_READ_WRITE;
		AttrMask = ATTR_MASK_READ_WRITE;
    }
    else{ // Also used for FS_REMOVE
		if(Mode==FS_REMOVE_DIR){
			Attr = ATTR_DIRECTORY;
			AttrMask = ATTR_MASK_DIR;
		}
		else{
			Attr = ATTR_READ;
			AttrMask = ATTR_MASK_READ;		
		}
    }
    if(Mode==FS_CREATE_DIR){  // Need to match on any file
		Attr = ATTR_ANY;
		AttrMask = ATTR_MASK_ANY;
    }
    Len = Index;
		// Find a free file descriptor
    for(Index=0;Index<NUM_FD;Index++){
		if(FdFlags[Index]==0) break;
	}
	if(Index==NUM_FD) return(0xff);
	
	SaveCluster = Cluster;
    Cluster = FindFile(&Name[Len],Cluster,Attr,AttrMask,Index);
  
    if(Mode==FS_CREATE_DIR){
		if(Cluster!=CLUSTER_NOT_FOUND) return(FS_OPEN_FAIL);  // name must not exist
			// Create directory
		Cluster = FindFile(&Name[Len],SaveCluster,ATTR_READ_WRITE,ATTR_MASK_READ_WRITE,Index);
		if(Cluster==CLUSTER_NOT_FOUND) return(FS_OPEN_FAIL);
	}
	else{
		if(Cluster==CLUSTER_NOT_FOUND) return(FS_OPEN_FAIL);
    }
    
	FdFlags[Index] = FD_FLAGS_OPEN;
	if(Mode==FS_OPEN_READ_ONLY) FdFlags[Index] |= FD_FLAGS_READ_ONLY;
	if(Mode!=FS_REMOVE && Mode!=FS_REMOVE_DIR){
		FdStartCluster[Index] = Cluster;    // Will be loaded with LongDir start cluster in FindFile
		FdSectorOffsetInCluster[Index] = 0; // Will be loaded with LongDir start Offset in sector in FindFile
		FdByteOffset[Index] = 0;			// Will be loaded with LongDir start byte offset in sector in FindFile
	}
	FdCurrentCluster[Index] = Cluster;
	//FdSize[Index];  // Set in FindFile

	FdByteOffsetInSector[Index] = 0; 
// This was all needed to work around a simulator issue
	//	FdCurrentSector[Index] = (Cluster==0) ? 0 : BSC.FirstClusterSector + (Cluster<<BSC.SecPerClusShift);uint32_t CurSec,Poo;
uint32_t CurSec,Poo;	
CurSec =  Cluster<<BSC.SecPerClusShift;
Poo = BSC.FirstClusterSector;
CurSec +=  Poo;
FdCurrentSector[Index] = (Cluster==0) ? 0 : CurSec;


	//FdDirSector[Index]; // Set in FindFile
	//FdDirOffsetInSector[Index];  // Set in FindFile
	
	if(Cluster!=0 && (Mode==FS_OPEN_WRITE || Mode==FS_REMOVE || Mode==FS_REMOVE_DIR)){ // Write only so blow away existing file by freeing up the clusters.
		uint32_t NextCluster;
		do{
			NextCluster = FetchFat(Cluster);
			WriteFat(Cluster,0);	// Free Up cluster
			if(Cluster<FatInfo.FreeClusterOffset) FatInfo.FreeClusterOffset = Cluster;
			FatInfo.NumFreeClusters++;
			Cluster = NextCluster;
		}while(!EndOfChain(Cluster)); 
		if(Mode==FS_REMOVE || Mode==FS_REMOVE_DIR){
			uint16_t Offset;
			uint8_t Done = 0,First = 1;
			
			FdFlags[Index] = 0;  // This file is no longer open or exists.
				// Fetch start of directory entry
			GetNextSec.Cluster = FdStartCluster[Index];  				// Starting Cluster.  Filled in by FindFile
			GetNextSec.SectInCluster = FdSectorOffsetInCluster[Index];  // Starting sector offset in cluster.  Filled in by FindFile.
			Offset = FdByteOffset[Index];                				// Starting byte offset
			Cluster = GetNextSector(0); // Don't advance (cluster variable used as sector variable)
			
			while(!Done){
				if(First){
					First = 0;
					if(ReadSector(Cluster)){
						return(0xff);
					}
					MarkSectorBufferDirty(Cluster);	
				}
				SectorBuf[Offset] = DIR_ENTRY_FREE;
				if(Cluster==FdDirSector[Index] && Offset==FdDirOffsetInSector[Index]) Done = 1;
				Offset+=32;
				if(!Done && Offset==512){
					Offset=0;  First=1;
					Cluster=GetNextSector(1);
				}
			}
			FlushCache();
		}
		else{	// Open for write only so set size to zero
			FdStartCluster[Index] = 0;
			FdCurrentCluster[Index] = 0;
			FdCurrentSector[Index] = 0;
			FdSize[Index] = 0;
		}
	}
	
	if(Mode==FS_CREATE_DIR){
			// Allocate a cluster to hold directory (will need to zero out the entire cluster)
		Byte = 0;
		if(FsWrite(Index,1,&Byte)!=1){
			FdFlags[Index] = 0;
			return(FS_OPEN_FAIL);
		}
		FdFlags[Index] |= FD_FLAGS_MKDIR;

			// Zero out entire cluster (1st cluster is zeroed by FsWrite above
		for(Len=1;Len<BSC.SecPerClus;Len++){
			if(AllocateSectorBuffer(FdCurrentSector[Index]+Len)) return(FS_OPEN_FAIL);
			MarkSectorBufferDirty(FdCurrentSector[Index]+Len);
		}
		
		// FdStartCluster[Index] is cluster of .
		// SaveCluster is cluster of .. 
		// FdCurrentSector[Index] is first sector of directory cluster
			// Create . and .. 
		if(ReadSector(FdCurrentSector[Index])) return(FS_OPEN_FAIL);
		MakeDirEntry(0,FdStartCluster[Index]);	// make .
		MakeDirEntry(1,SaveCluster);			// make ..
		MarkSectorBufferDirty(FdCurrentSector[Index]);
		FsClose(Index);
	}
	
	return(Index);
}

/*
	0. Use FindCluster to find directory just like FsOpen or FsGetFirstDir
			RetVal = FsGetFirstDir(FsState.CurrentDirCluster,Name,&DirInfo);
	1. Make sure directory is empty
		a. See if possible to reuse directory search or if the code has to be copied here.
	2. If empty, then free up clusters pointed to by cluster chain in director entry
	3. Remove long name and short name entry just like FsDelete.
*/
uint8_t FsRemoveDir(char *Name)
{
	uint8_t Index;

	uint32_t Addr = FsState.CurrentDirCluster;
	uint8_t RetVal;
	char Buf[14];
	FsDirInfo DirInfo;

		// First Make sure directory is empty
		
	Addr = FsState.CurrentDirCluster;  // Save current path
	if(FsSetCurrentDirectory(Name)){
		//puts("Can't find directory\r\n");
		return(FS_OPEN_FAIL);
	}
	FsState.ShortMode = 1;  // Used to make First and Next Dir just return the short name to save memory.
	RetVal = FsGetFirstDir(Buf,&DirInfo);
	if(RetVal){
		//puts("Can't read directory\r\n");
		FsState.ShortMode = 0;
		FsState.CurrentDirCluster = Addr;  // Restore path		
		return(FS_OPEN_FAIL);
	}

	while(Buf[0]){
		if(!(Buf[0]=='.' && (Buf[1]==0 || (Buf[1]=='.' && Buf[2]==0)))){
			FsState.ShortMode = 0;
			FsState.CurrentDirCluster = Addr;  // Restore path		
			return(FS_OPEN_FAIL);
		}	
		RetVal = FsGetNextDir(Buf,&DirInfo);		
		if(RetVal){
			//puts("Can't read directory\r\n");
			Buf[0] = 0;
		}
	}
	FsState.ShortMode = 0;
	FsState.CurrentDirCluster = Addr;  // Restore path						
	Index = FsOpen(FS_REMOVE_DIR,Name);

	FlushCache();
	if(Index != FS_OPEN_FAIL){ 
		FdFlags[Index]=0;
		return(0);
	}
	return(FS_OPEN_FAIL);
}

uint8_t FsMakeDir(char *Name)
{
	uint8_t Index;
	
	Index = FsOpen(FS_CREATE_DIR,Name);
	if(Index != FS_OPEN_FAIL){ 
		return(0);
	}
	return(FS_OPEN_FAIL);
}

uint8_t FsRemove(char *Name)
{
	uint8_t Index;
	
	Index = FsOpen(FS_REMOVE,Name);	
	if(Index != FS_OPEN_FAIL){ 
		FdFlags[Index]=0;
		return(0);
	}
	return(FS_OPEN_FAIL);
}

static char *GetCurrentDirPtr;

static void GetCurrentDirPathPutByte(char c)
{
	*GetCurrentDirPtr++ = c;
}

void FsGetCurrentDirectory(char *Path)
{
    uint32_t Cluster = FsState.CurrentDirCluster;
    uint8_t Index,Loop;
    uint32_t ClusterList[15];

    ClusterList[0] = FsState.CurrentDirCluster;
    Index = 1;
    while(Cluster != 0 && Index<15){  // Search backward until root is found
		Cluster = FindFile("..",Cluster,ATTR_READ_DIR,ATTR_MASK_READ_DIR,0xff);
		ClusterList[Index++] = Cluster;
    }
	GetCurrentDirPtr = Path;
	GetCurrentDirPathPutByte('/');
    for(Loop=Index-2;Loop <254; Loop--){  // change Loop to signed char and use Loop>=0
		if(GetClusterName(ClusterList[Loop],ClusterList[Loop+1],ATTR_READ_DIR,ATTR_MASK_READ_DIR)){
			GetCurrentDirPathPutByte(0);
			return;
		}
		GetCurrentDirPathPutByte('/');
    }
	GetCurrentDirPathPutByte(0);
}


uint8_t FsSetCurrentDirectory(char *Name)
{
    uint32_t Cluster = FsState.CurrentDirCluster;
    char KeepGoing;
    uint8_t StartIndex,Index;
    
		// If file system is not mounted
    if(BSC.BytesPerSecShift==0) return(0xff);    
    StartIndex = 0;
    if(Name[0]=='/'){  // Absolute path
		Cluster = 0;
		StartIndex++;
    }
    while(1){
		for(Index=StartIndex;Name[Index] != '/' && Name[Index];Index++);
		KeepGoing = (Name[Index]=='/') ? 1 : 0;
		Name[Index] = 0;
		if(Index==StartIndex){
			FsState.CurrentDirCluster = Cluster;
			return(0);  // Path found
		}
		Cluster = FindFile(&Name[StartIndex],Cluster,ATTR_DIR,ATTR_MASK_DIR,0xff);
		if(Cluster==CLUSTER_NOT_FOUND){
			return(0xff);
		}
		if(!KeepGoing){
			FsState.CurrentDirCluster = Cluster;
			return(0);  // Path found
		}	    
		StartIndex = Index+1;
   }
}

static uint8_t LocalStringUnsignedInt(char *s,uint16_t Val,signed char Digits)
{
    int Index=0;
    char zero_char = ' ';
    if(Digits<0){ zero_char = '0';  Digits = -Digits; }

    if(Val > 9999){
        s[Index++] = (Val/10000) + '0';
    }
    else{
        if(Digits > 4){
            s[Index++] = zero_char;
        }
    }
    if(Val > 999){
        s[Index++] = ((Val/1000) % 10) + '0';
    }
    else{
        if(Digits > 3){
            s[Index++] = zero_char;
        }
    }
    if(Val > 99){
        s[Index++] = ((Val/100) % 10) + '0';
    }
    else{
        if(Digits > 2){
            s[Index++] = zero_char;
        }
    }
    if(Val > 9){
        s[Index++] = ((Val/10) % 10) + '0';
    }
    else{
        if(Digits > 1){
            s[Index++] = zero_char;
        }
   }
   s[Index++] = (Val % 10) + '0';
   s[Index] = 0;
   return(Index);
}

static uint32_t BaseFindFile(uint32_t SearchCluster,char *Name,uint32_t ClusterStart
    ,uint8_t Attrib, uint8_t AttribMask, uint8_t FdIndex)
{
    
    uint32_t FileCluster,FileSize;
    uint8_t i;
    char *ptr;
    uint8_t Done;
    uint16_t Index;     // Index inside the sector
    uint32_t Cluster;  // Current cluster being accessed
    uint32_t ClustSect;// First sector of the cluster
    uint16_t SectIndex; // Sector index inside the cluster
    
    char ShortName[13];
    uint8_t Buf[8];
    uint8_t LdirCheckSum=0,LdirValid,LastWasLongDir=0;
    char LongName[256];

    
		// New variables for creating new file or directory
	uint8_t OpenForReadWrite = 0;
    uint8_t NumDirEntriesForNew=0;
    uint8_t NumDirEntriesFree;
	uint32_t NewDirCluster=0;	// Cluster of first free Dir entry
    uint16_t NewDirSectIndex=0;	// Sector offset inside cluster
    uint16_t NewDirIndex=0;   // Byte index inside sector
    uint32_t RemainFreeCluster;
    uint16_t RemainFreeSectIndex;
    uint16_t RemainFreeIndex;
    uint8_t WriteEndOfDirMarker;
    char NewShortName[12];
    uint8_t j,c,ShortIndex,LastDotIndex;
    uint8_t Dots=0,Lossy=0;
    uint8_t Match;
    uint8_t LossyMatch;
    uint8_t NewShortSum;
    uint16_t Val;
    uint16_t Digits[] = {1,10,100,1000,1000};

	// Note that directories are a cluster chain so it may span multiple clusters which
	// will require that the FAT be read when the end of a cluster is reached before the
	// end of the directory.  The root directory for FAT12 and FAT16 is just a linear list
	// of sectors.

		// If file system is not mounted
	if(BSC.BytesPerSecShift==0) return(CLUSTER_NOT_FOUND);
	
	//if(*Name==0) return(CLUSTER_NOT_FOUND);  // Name is set to "" when used for pwd.
	if(Attrib==ATTR_READ_WRITE && AttribMask==ATTR_MASK_READ_WRITE){       
		OpenForReadWrite = 1;
		// This function is only called with these parameters when a FsOpen call is made
		// with read/write mode.  If the file is found and there is write permission
		// then this function works like it did in read only mode.  If the file is not
		// found, it will need to create a new directory.  While doing this, it needs
		// to make sure that the file name does not already exist in read only mode.
		// If it fails for any reason it needs to return CLUSTER_NOT_FOUND.
		
		// Instead of missing the attribute match when looking for the file,
		// change the Attrib and AttribMask to read and then when the file is found
		// check if there is also write permission.  If not, return CLUSTER_NOT_FOUND
	
		//Attrib=ATTR_READ;  AttribMask=ATTR_MASK_READ;
		Attrib=ATTR_READ_DIR;  AttribMask=ATTR_MASK_READ_DIR;
			// Calculate length of name to figure out how many directory entries are required
		NumDirEntriesForNew = 1;  // Start with one for short name
		ptr = Name;
		Done = 0;
		while(!Done){
			for(i=0;i<13;i++){
				if(*ptr++==0) Done=1;
			}
			NumDirEntriesForNew++;
			if(*ptr==0) Done=1;
		}
		NumDirEntriesFree = 0;
		LossyMatch = 0;
		
			// Calculate new short name
			
			// Count Dots
		Dots = 0;  LastDotIndex = 0;
		for(i=0;Name[i];i++){
			if(Name[i]=='.'){ 
				Dots++;  LastDotIndex = i;
			}
		}
		Lossy = 0;

		for(i=0;i<12;i++) NewShortName[i] = ' ';
		ShortIndex = 0;
		uint8_t JumpToLastDot;
		JumpToLastDot = 0;
		for(i=0;Name[i];i++){
			c = Name[i];
			if(c>='a' && c<='z') c = c - 0x20; // Convert to lower case
			else if(c=='+' || c==',' || c==';' || c=='=' || c=='[' || c==']'){ c='_'; Lossy=1; }
			if(c!=' ' && c!='\t' && c!='.') NewShortName[ShortIndex++] = c;
			else{
				if(c==' ' || c=='\t') Lossy=1;
				else if(c=='.'){
					if(Dots==1){
						ShortIndex = 8;
					}
					else{
						Lossy = 1;
						Dots--;
					}
				}
			}
			if(ShortIndex==8){
			   if(i>=7 && Name[i+1]!='.' && Name[i+1]!=0) Lossy=1;
			   if(Dots && !JumpToLastDot){ i = LastDotIndex; JumpToLastDot = 1; }
			   else break;
			}
			if(ShortIndex==11){ 
				if(Name[i+1]) Lossy = 1;
				break;
			}
		}
		if(Lossy){ 
			for(i=0;NewShortName[i]!=' ';i++);
			if(i>=6) i=6;
			NewShortName[i]='~';  NewShortName[i+1]='1'; 
			Buf[7] = 0;
			LossyMatch = 0;
		}
	}
	
    if(ClusterStart==0){ // Root Directory 
		if(FatInfo.FatType==32){
			ClustSect = BSC.FirstClusterSector + (BootSectorFAT32.RootClust << BSC.SecPerClusShift);
			Cluster = BootSectorFAT32.RootClust;
		}
		else{
			ClustSect = BSC.FirstRootDirSecNum;
			Cluster = 0;
		}
    }
    else{
		ClustSect = BSC.FirstClusterSector + (ClusterStart << BSC.SecPerClusShift);
		Cluster = ClusterStart;
    }

    if(ReadSector(ClustSect)){
		return(CLUSTER_NOT_FOUND);
    }    
    Done = 0;  SectIndex = 0;
    for(Index=0;!Done;Index+=32){        
		if(Index==512){
			Index = 0;  SectIndex++;
			if(Cluster==0){  // Traversing root directory on FAT12 or FAT16 volume
				if(SectIndex>(BSC.RootEntCnt>>5)){
					// Didn't find last directory marker for root directory
					return(CLUSTER_NOT_FOUND);
				}
			}
			else if(SectIndex>BSC.SecPerClus){ // Need to get next cluster chain value
				SectIndex = 0;
				Cluster = FetchFat(Cluster);
				if(EndOfChain(Cluster)){
					// If a directory is perfectly filled to the end of a cluster and no cluster is allocated past it,
					// it seems that if a new file is being created, then the cluster would need to be allocated and the new entry placed there.

					if(OpenForReadWrite){
							// Allocate new cluster to chain.
						if(FatInfo.NumFreeClusters==0){ 
							return(CLUSTER_NOT_FOUND);  // No more space to add another directory
						}
						NewDirCluster = FetchFreeCluster(FatInfo.FreeClusterOffset);
						if(NewDirCluster==0xffffffff) return(CLUSTER_NOT_FOUND);
						WriteFat(NewDirCluster,CLUSTER_END_OF_CHAIN);
						WriteFat(Cluster,NewDirCluster);
		
						FatInfo.FreeClusterOffset++;
						FatInfo.NumFreeClusters--;
							// Be lazy and stick new file entry into new cluster
						NewDirSectIndex = 0;	// Sector offset inside cluster
						NewDirIndex = 0;   // Byte index inside sector
						NumDirEntriesFree=NumDirEntriesForNew;
						RemainFreeCluster = NewDirCluster;
						RemainFreeSectIndex = 0;
						RemainFreeIndex = NumDirEntriesForNew<<5;
						if(RemainFreeIndex > 512){
							RemainFreeIndex -= 512;
							RemainFreeSectIndex = 1;
						}	
						break;
					}
					else{ 
						return(CLUSTER_NOT_FOUND); 
					}
				}
				ClustSect = BSC.FirstClusterSector + (Cluster << BSC.SecPerClusShift);
			}
	
			if(ReadSector(ClustSect+SectIndex)){
				return(CLUSTER_NOT_FOUND);
			}
		}
        
		if(SectorBuf[Index]==DIR_ENTRY_FREE){  // Free directory slot
			LastWasLongDir = 0;
			if(OpenForReadWrite){
				if(NumDirEntriesFree==0){
					NewDirCluster = Cluster;	// Cluster of first free Dir entry
						// ClustSect = BSC.FirstClusterSector + (Cluster << BSC.SecPerClusShift);
					NewDirSectIndex = SectIndex;	// Sector offset inside cluster
					NewDirIndex = Index;   // Byte index inside sector
					NumDirEntriesFree=1;
				}
				else{
					if(NumDirEntriesFree!=NumDirEntriesForNew) NumDirEntriesFree++;
				}
			}           
		}        
		else if(SectorBuf[Index]==0){  // Remaining indexes are free
			Done = 1;
			if(OpenForReadWrite){
				if(NumDirEntriesFree!=NumDirEntriesForNew){
					NewDirCluster = Cluster;	// Cluster of first free Dir entry
						// ClustSect = BSC.FirstClusterSector + (Cluster << BSC.SecPerClusShift);
					NewDirSectIndex = SectIndex;	// Sector offset inside cluster
					NewDirIndex = Index;   // Byte index inside sector
					NumDirEntriesFree=NumDirEntriesForNew;
				}
				RemainFreeCluster = Cluster;
				RemainFreeSectIndex = SectIndex;
				RemainFreeIndex = Index;
			}             
		}       
		else{            
			if(OpenForReadWrite){
				if(NumDirEntriesFree!=NumDirEntriesForNew) NumDirEntriesFree=0;
			}            
			if(SectorBuf[Index+11]==ATTR_LONG_NAME){  // Long Dir Attribute                
				uint8_t Offset = ((SectorBuf[Index+0] & 0x3f)-1);
                if(Offset<20){  // Only space for a filename less than 256 bytes 13 char/Offset
                        // 13 characters per directory entry.
                    Offset = (Offset<<3) + (Offset<<2) + Offset; // *13 = *8 + *4 + *1
                    for(i=1;i<10;i+=2) LongName[Offset++]=SectorBuf[Index+i];
                    for(i=14;i<26;i+=2) LongName[Offset++]=SectorBuf[Index+i];
                    for(i=28;i<32;i+=2) LongName[Offset++]=SectorBuf[Index+i]; 
                }
                else{
                    LongName[Offset] = 0;
                }
				if(SectorBuf[Index+0] & 0x40){  // First entry of long name
					LongName[Offset] = 0;  // Just in case.
          
					LdirCheckSum = SectorBuf[Index+13];     
                    if(FdIndex != 0xff){  // FdIndex set to 0xff for change directory since it is not used.
						// save sector and offset for FsRemove				
                        FdStartCluster[FdIndex] = Cluster;  		   // Starting Cluster.
                        FdSectorOffsetInCluster[FdIndex] = SectIndex;  // Starting sector offset in cluster.                     
                        FdByteOffset[FdIndex] = Index;                 // Starting byte offset	
                    } 					
				}
				else{
					if(LdirCheckSum != SectorBuf[Index+13]){ // Corrupted long dir entry
						LdirCheckSum = 0;
					}                      
				}
				LastWasLongDir = 1;     
			} 
			else{                
					// Short name is padded with spaces so no need for NULL check just copy 11 bytes  
				for(i=0;i<11;i++){
					ShortName[i] = SectorBuf[Index+i];
				}
				ShortName[11]=0;
					// If open for read/write and new name is lossy, make a list of all matching short
					// names to see what the final new short name should be.
				if(OpenForReadWrite){
					if(Lossy){ 	
						for(i=0;i<8;i++){
							if(ShortName[i]=='~'){
								// If shortname has a ~ before new short name
								// then it is only a match if the characters leading up
								// were a match and there are numbers all the way out to index 7
					
								Match = 1;
								if(NewShortName[i]!='~'){
									for(j=i+1;j<8;j++){
									   if(ShortName[j]<'0' || ShortName[j]>'9') break;
									}
									if(j!=8) Match=0;
								}
								if(Match){ 
									if(!LossyMatch){
										if(AllocateSectorBuffer(TEMP_BUFFER)) return(CLUSTER_NOT_FOUND);
										SectorWrBuf[0] = 1;  // Zero is not valid
										LossyMatch = 1;
									}
									i++;
									for(j=0;i+j<8 && ShortName[i+j]!=' ';j++) Buf[j] = ShortName[i+j];
									Dots = j;
									Val = 0;
									if(Dots>4){ Val = 0xffff; }
									else{
										for(j=0;j<Dots;j++){
											uint16_t It = Digits[Dots-j-1];
											uint8_t k;
											for(k=0;k<Buf[j]-'0';k++) Val+=It;
										}
									}
									if(Val<512*8){
										SectorWrBuf[Val>>3] |= (1<<(Val&7));
									}
								}
							}
							else if(ShortName[i]!=NewShortName[i]) break;
						}
					}
				}                
				if(SectorBuf[Index+11] & ATTR_VOLUME_ID){ 
					for(i=10;i!=0 && ShortName[i]==' ';i--) ShortName[i]=0;
					LdirValid = 0;  LastWasLongDir = 0;
				}
				else{  
					for(i=7;i!=0 && ShortName[i]==' ';i--) ShortName[i]='.';
					i+=2;  ShortName[i-1] = '.';
					if(SectorBuf[Index+8]!=' '){
						ShortName[i  ] = SectorBuf[Index+8];
						ShortName[i+1] = SectorBuf[Index+9];
						ShortName[i+2] = SectorBuf[Index+10];
						ShortName[i+3] = 0;
						if(ShortName[i+2]==' ') ShortName[i+2] = 0;
						if(ShortName[i+1]==' ') ShortName[i+1] = 0;
					}
					else{
						ShortName[i-1] = 0;
					}
						// Compute SumCheck of Name for long dir support
					LdirValid = 0;
					if(LastWasLongDir){
						uint8_t Tmp,Sum = 0;                        
						for (i=0; i<11; i++) {                            
							//Sum = ((Sum & 1) ? 0x80 : 0) + (Sum >> 1) + SectorBuf[Index+i];
                            Tmp = (Sum>>1) + SectorBuf[Index+i];
                            if(Sum&1) Sum = Tmp + 0x80;
                            else      Sum = Tmp;                            
						}                       
						if(Sum==LdirCheckSum) LdirValid=1;
					}
				}                
//				Buf[3] = SectorBuf[Index+20+1];   Buf[2] = SectorBuf[Index+20+0];
//				Buf[1] = SectorBuf[Index+26+1];	  Buf[0] = SectorBuf[Index+26+0];
//				FileCluster = BUF_FETCH32(Buf);
                FileCluster = ((uint32_t)SectorBuf[Index+20+1]<<24) | ((uint32_t)SectorBuf[Index+20+0]<<16)
                            | ((uint32_t)SectorBuf[Index+26+1]<< 8) | ((uint32_t)SectorBuf[Index+26+0]<< 0);
    
				FileSize = SECTOR_FETCH32(Index+28);
					// Try to match the long name first then if not, try the short name.
					// Matching is case insensitive as per the FAT rules. 
               
				if((SectorBuf[Index+11] & AttribMask) == Attrib){                     
					if(SearchCluster==0){                        
						if(LdirValid){                              
							for(i=0;Name[i] && LongName[i];i++){
								if(toupper(Name[i]) != toupper(LongName[i])){ 
                                    break;
                                }
							}                           
							if(Name[i]==LongName[i]){                                 
								if(OpenForReadWrite){
									if(SectorBuf[Index+11] & (ATTR_READ_ONLY|ATTR_DIR)) return(CLUSTER_NOT_FOUND);
								}
                                
                                if(FdIndex != 0xff){
                                    FdSize[FdIndex] = FileSize;
                                    FdDirSector[FdIndex] = ClustSect+SectIndex;
                                    FdDirOffsetInSector[FdIndex] = Index;
                                    if(!LdirValid){  // Just the short name is valid so FsRemove will just free this entry
                                        FdStartCluster[FdIndex] = Cluster;  		   // Starting Cluster. 
                                        FdSectorOffsetInCluster[FdIndex] = SectIndex;  // Starting sector offset in cluster. 
                                        FdByteOffset[FdIndex] = Index;                 // Starting byte offset		
                                    }
                                }
//#ifdef HELL                                  
								return(FileCluster);
//#endif                                
							}       
						}
						for(i=0;Name[i] && ShortName[i];i++){
							if(toupper(Name[i]) != toupper(ShortName[i])) break;
						}                         
						if(Name[i]==ShortName[i]) {
							if(OpenForReadWrite){
								if(SectorBuf[Index+11] & (ATTR_READ_ONLY|ATTR_DIR)) return(CLUSTER_NOT_FOUND);
							}                            
                            if(FdIndex!=0xff){
                                FdSize[FdIndex] = FileSize;
                                FdDirSector[FdIndex] = ClustSect+SectIndex;
                                FdDirOffsetInSector[FdIndex] = Index;
                                if(!LdirValid){  // Just the short name is valid so FsRemove will just free this entry
                                    FdStartCluster[FdIndex] = Cluster;  		   // Starting Cluster. 
                                    FdSectorOffsetInCluster[FdIndex] = SectIndex;  // Starting sector offset in cluster. 
                                    FdByteOffset[FdIndex] = Index;                 // Starting byte offset	
                                }
                            }
//#ifdef HELL                            
							return(FileCluster);
//#endif                            
						}                        
					}                     
					else{
                        
                        if(SearchCluster==FileCluster){
							if(LdirValid){
//#ifdef HELL                                
								for(i=0;LongName[i];i++) GetCurrentDirPathPutByte(LongName[i]);
//#endif
							}
							else{
//#ifdef HELL                                
								for(i=0;ShortName[i];i++)
                                    GetCurrentDirPathPutByte(ShortName[i]);
//#endif
							} 
//#ifdef HELL                            
							return(0);
//#endif
						}                       
					}                        
				}
				LastWasLongDir = 0;          
			}      
		}  
    }     
    if(OpenForReadWrite){
			// Figure out final new short name based on table made while searching directory for a match.		
		if(LossyMatch){
			Match = 0;
			for(Val=0;Val<512;Val++){
				c = SectorWrBuf[Val];
				if(c != 0xff){
					for(i=0;i<8;i++){
						if((c & (1<<i)) == 0){
							Val = (Val<<3)|i;
							Dots = 1;
							if(Val>9) Dots=2;
							if(Val>99) Dots=3;
							if(Val>999) Dots=4;
							Match = 1;
							break;
						}
					}
					break;
				}
			}
			
			if(DeallocateSectorBuffer(TEMP_BUFFER)) return(CLUSTER_NOT_FOUND);
			
			if(!Match){ // Did not find a free hole (0 to 4095 used)
				// REVISIT: can do multiple passes and try again
				//          but 4095 files with the same name is a bit
				//          much for a tiny file system so just crap out for now.
				return(CLUSTER_NOT_FOUND);
			}
			for(i=0;i<8;i++){  // Figure out length of shortname
				if(NewShortName[i]==' ') break;
			}
			NewShortName[i-Dots-1] = '~';
			LocalStringUnsignedInt(Buf,Val,0);
			for(c=0;c<Dots;c++) NewShortName[i-Dots+c] = Buf[c];
		}
	
		NewShortSum = 0;
        uint8_t Tmp;
		for(i=0; i<11; i++) {
			//NewShortSum = ((NewShortSum & 1) ? 0x80 : 0) + (NewShortSum >> 1) + NewShortName[i];
            Tmp = (NewShortSum>>1) + NewShortName[i];
            if(NewShortSum&1) NewShortSum = Tmp + 0x80;
            else      NewShortSum = Tmp;
		}    
    
			// Detect if end of dir marker needs to be moved.  Also, allocate new cluster
			// if directory spills over end of cluster chain.  This can be done sequentially.
			// As directory entries are filled in, check to see if the remaining key is
			// being overwritten.  If so, shove it at the end.

		if(NewDirCluster==0){ // Root Directory of non FAT 32  
			ClustSect = BSC.FirstRootDirSecNum;
		}
		else{	
			ClustSect = BSC.FirstClusterSector + (NewDirCluster << BSC.SecPerClusShift);
		}
					//NewDirIndex = Index;   // Byte index inside sector
		if(ReadSector(ClustSect+NewDirSectIndex)){
			return(CLUSTER_NOT_FOUND);  // Unable to read sector that should exist
		}
		WriteEndOfDirMarker = 0;	
		
		for(NumDirEntriesFree=0;NumDirEntriesFree<NumDirEntriesForNew;NumDirEntriesFree++){
			if(NumDirEntriesFree==NumDirEntriesForNew-1){ // Short name entry
					// Save sector and offset of directory for size update.
                if(FdIndex!=0xff){
                    FdSize[FdIndex] = 0;	
                    FdDirSector[FdIndex] = ClustSect+NewDirSectIndex;
                    FdDirOffsetInSector[FdIndex] = NewDirIndex;
                }
				for(i=0;i<11;i++)  SectorBuf[NewDirIndex+i] = NewShortName[i];
// REVISIT: for new directory change attribute!				
				SectorBuf[NewDirIndex+11] = ATTR_READ_WRITE;  // Attribute read/write
				for(i=12;i<22;i++) SectorBuf[NewDirIndex+i] = 0; // Reserved, Create Time and date (not supported) also cluster low to 0 (not allocated)
				LoadDateTime(NewDirIndex);
				for(i=26;i<32;i++) SectorBuf[NewDirIndex+i] = 0; // Set cluster high to 0 (not allocated) and File size to zero		
			}
			else{  // Long name entry (If 3, this is called with 1 then 2)
				uint8_t Offset =  NumDirEntriesForNew-NumDirEntriesFree-1;
				SectorBuf[NewDirIndex+0] = (NumDirEntriesFree==0) ? 0x40 + Offset : Offset;
				Offset--;  // Get back to zero based.
				Offset = (Offset<<3) + (Offset<<2) + Offset; // *13
				Done = 0;
				for(i=1;i<32;i+=2){  
					SectorBuf[NewDirIndex+i] = (Done) ? 0xff : Name[Offset];  
					SectorBuf[NewDirIndex+i+1] = (Done) ? 0xff : 0;  
					if(Name[Offset++]==0) Done=1;
					if(i==9) i=12;
					if(i==24) i=26;
				}
				SectorBuf[NewDirIndex+11] = ATTR_LONG_NAME;
				SectorBuf[NewDirIndex+12] = 0;
				SectorBuf[NewDirIndex+13] = NewShortSum;
				SectorBuf[NewDirIndex+26] = 0;
				SectorBuf[NewDirIndex+27] = 0;
			}
			MarkSectorBufferDirty(ClustSect+NewDirSectIndex);
			if(RemainFreeCluster==NewDirCluster && RemainFreeSectIndex==NewDirSectIndex && RemainFreeIndex==NewDirIndex){
				WriteEndOfDirMarker = 1;
			}
			
			NewDirIndex+=32;
			if(NewDirIndex>=512){
				NewDirSectIndex++;
				NewDirIndex = 0;  // Skipped into new sector
				if(NewDirSectIndex>BSC.SecPerClus){ // Skipped into new cluster
					NewDirSectIndex = 0;
					Cluster = NewDirCluster;
					NewDirCluster = FetchFat(Cluster);
					if(EndOfChain(NewDirCluster)){  // Get more space
						if(FatInfo.NumFreeClusters==0){ 
							return(CLUSTER_NOT_FOUND);  // No more space to add another directory
						}
						NewDirCluster = FetchFreeCluster(FatInfo.FreeClusterOffset);
						if(NewDirCluster==0xffffffff) return(CLUSTER_NOT_FOUND);
						WriteFat(NewDirCluster,CLUSTER_END_OF_CHAIN);
						WriteFat(Cluster,NewDirCluster);

						FatInfo.FreeClusterOffset++;
						FatInfo.NumFreeClusters--;
					}
					ClustSect = BSC.FirstClusterSector + (NewDirCluster << BSC.SecPerClusShift);
				}
				if(ReadSector(ClustSect+NewDirSectIndex)){
					return(CLUSTER_NOT_FOUND);  // Unable to read sector that should exist
				}
			}
		}
			// If this will be in a new sector, the code above will have either just allocated it or just read it into the cache.
		if(WriteEndOfDirMarker && NewDirIndex<512){
			for(i=0;i<32;i++) SectorBuf[NewDirIndex+i]=0;
			MarkSectorBufferDirty(ClustSect+NewDirSectIndex);
		}
		return(0);	// New empty file
    }
    return(CLUSTER_NOT_FOUND);
}

static uint32_t GetClusterName(uint32_t SearchCluster,uint32_t ClusterStart,uint8_t Attrib, uint8_t AttribMask)
{
    return(BaseFindFile(SearchCluster,"",ClusterStart,Attrib,AttribMask,0xff));
}

static uint32_t FindFile(char *Name,uint32_t ClusterStart,uint8_t Attrib, uint8_t AttribMask,uint8_t FdIndex)
{ 
    return(BaseFindFile(0,Name,ClusterStart,Attrib,AttribMask,FdIndex));
}

static uint32_t FetchFreeCluster(uint32_t StartIndex)
{
    uint32_t Offset,Sector,FATLimit,FATIndex;
    uint8_t Save;

    Offset = (FatInfo.FatType==32) ? (StartIndex<<2)
				   : (FatInfo.FatType==16) ? (StartIndex<<1) : StartIndex + (StartIndex>>1);
    Sector = FatInfo.FirstFATSecNum + (Offset>>9);
    Offset = Offset & 0x1ff;
    FATLimit = FatInfo.CountofClusters;
    FATIndex = StartIndex;

    if(ReadSector(Sector)){
		//printf("Unable to read sector 0x%x\n",Sector);
		return(0xffffffff);
    }

    if(FatInfo.FatType==32){
		while(1){
			if((SECTOR_FETCH32(Offset) & 0x0fffffff)==0) return(FATIndex);
			FATIndex++;
			if(FATIndex>=FATLimit) return(0xffffffff); // No free clusters
			Offset+=4;
			if(Offset>=512){
				Sector++;
				if(ReadSector(Sector)){
					//printf("Unable to read sector 0x%x\n",Sector);
					return(0xffffffff);
				}
				Offset = 0;
			}
		}
    }

    if(FatInfo.FatType==16){
		while(1){
			if((SECTOR_FETCH16(Offset))==0) return(FATIndex);
			FATIndex++;
			if(FATIndex>=FATLimit) return(0xffffffff); // No free clusters
			Offset+=2;
			if(Offset>=512){
				Sector++;
				if(ReadSector(Sector)){
					//printf("Unable to read sector 0x%x\n",Sector);
					return(0xffffffff);
				}
				Offset = 0;
			}
		}
    }
    else{	// Ugly FAT 12 code
		while(1){
			Offset = (FATIndex + (FATIndex>>1) ) & 0x1ff;
			if(Offset == 511){ // Bummer FAT12 entry spans two sectors
				Save = SectorBuf[511];   Sector++;
				if(ReadSector(Sector)){
					//printf("Unable to read sector 0x%x\n",Sector);
					return(0xffffffff);
				}
				if( ((SectorBuf[0]<<4) | (Save>>4)) == 0) return(FATIndex);
				FATIndex++;
				if(FATIndex>=FATLimit) return(0xffffffff); // No free clusters
			}
			else{
				if(FATIndex & 1){
					if( ((SectorBuf[Offset+1]<<4) | (SectorBuf[Offset+0]>>4)) == 0) return(FATIndex);
				}
				else{
					if( (((SectorBuf[Offset+1]&0x0f)<<8) | SectorBuf[Offset+0]) == 0) return(FATIndex);
				}
				FATIndex++;
				if(FATIndex>=FATLimit) return(0xffffffff); // No free clusters
				if(Offset==510){
					Sector++;
					if(ReadSector(Sector)){
						//printf("Unable to read sector 0x%x\n",Sector);
						return(0xffffffff);
					}
				}
			}
		}
    }
}

static uint32_t FetchFreeCount(uint32_t StartIndex)
{
    uint32_t Index;
    uint32_t FatLimit;
    uint32_t FreeCount = 0;

    FatLimit = FatInfo.CountofClusters;

    for(Index=StartIndex;Index<FatLimit;){
		Index = FetchFreeCluster(Index);
		if(Index==0xffffffff) return(FreeCount);
		FreeCount++;  Index++;
    }
    return(FreeCount);
}

uint32_t FsGetFreeSectors(void)
{
    if(!FatInfo.ValidFreeCluster){
        FatInfo.NumFreeClusters = FetchFreeCount(FatInfo.FreeClusterOffset + 1);
        FatInfo.ValidFreeCluster = 1;
    }
    return(FatInfo.NumFreeClusters<<BSC.SecPerClusShift);
}

int32_t FsTell(uint8_t FdIndex)
{
	if(FdIndex>= NUM_FD){
		return(-1);
    }
    if(!(FdFlags[FdIndex] & FD_FLAGS_OPEN)){
		return(-1);
    }
	return(FdByteOffset[FdIndex]);
}

uint8_t FsMounted(void)
{
	if(BSC.BytesPerSecShift==0) return(0);
	return(1);
}