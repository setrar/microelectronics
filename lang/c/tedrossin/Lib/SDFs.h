#define NUM_FD			4

#define FS_OPEN_READ_ONLY	1	// if file does not exist, fail
#define FS_OPEN_READ_WRITE	2	// if file exists, do not set size to zero
#define FS_OPEN_WRITE		3	// if file exists, set size to zero

#define FS_OPEN_FAIL	0xff

#define ATTR_READ_ONLY	0x01
#define ATTR_HIDDEN		0x02
#define ATTR_SYSTEM		0x04
#define ATTR_VOLUME_ID	0x08
#define ATTR_DIRECTORY	0x10
#define ATTR_ARCHIVE	0x20

#define CD_STACK_SIZE	2
typedef struct{
	uint32_t CurrentDirCluster;
	uint32_t CurrentDirectoryStack[CD_STACK_SIZE];
	uint8_t CdStackPtr;
	uint8_t ShortMode;
} FsStateType;

typedef struct{
    uint8_t Attrib;
    uint32_t Size;
    uint16_t ModDate;
    uint16_t ModTime;
} FsDirInfo;

typedef struct{
    uint16_t Year;  // 0 to 65535
    uint8_t Month; // 1 to 12
    uint8_t Day;  // 1 to 31
    uint8_t Hour; // 0 to 23
    uint8_t Minute; // 0 to 59
    uint8_t Second; // 0 to 59
} ClockType;

#define FS_MOUNT_NORMAL                 0
#define FS_MOUNT_READ_WRITE             0
#define FS_MOUNT_READ_ONLY              1
#define FS_MOUNT_SKIP_FREE_SPACE_COUNT  2
        
uint8_t FsMountFileSystem(uint8_t Flags);
void FsUnmountFileSystem(void);
void FsPushCdStack(void);
void FsPopCdStack(void);
uint8_t FsGetFirstDir(char *Name,FsDirInfo *Info);
uint8_t FsGetNextDir(char *Name,FsDirInfo *Info);
uint8_t FsSeek(uint8_t FdIndex,int32_t Offset,uint8_t Origin);
uint8_t FsClose(uint8_t FdIndex);
uint16_t FsRead(uint8_t FdIndex, uint16_t Count, uint8_t *Data);
uint16_t FsWrite(uint8_t FdIndex, uint16_t Count, uint8_t *Data);
uint8_t FsOpen(uint8_t Mode,char *Name);
uint8_t FsRemove(char *Name);
uint8_t FsMakeDir(char *Name);
uint8_t FsRemoveDir(char *Name);
void FsGetCurrentDirectory(char *Path);
uint8_t FsSetCurrentDirectory(char *Name);
uint32_t FsGetFreeSectors(void);
void FsInit(void);
int32_t FsTell(uint8_t FdIndex);
uint8_t FsMounted(void);
ClockType ClockFetchTime(void);
void ClockSetTime(ClockType It);

// Functions to aid in debug
uint8_t ReadSector(uint32_t Addr);
uint8_t WriteSector(uint32_t Addr);
extern uint8_t *SectorBuf;