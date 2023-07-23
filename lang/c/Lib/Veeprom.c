/* 
 * Veeprom.c: Simple emulation of EEPROM using flash memory.
 *    Ted Rossin  8-13-2021 dsPIC version started porting to Pico 5-31-2022
 *                6-06-2022
 */

#include <pico/stdlib.h>
#include <hardware/sync.h>
#include <hardware/flash.h>
#include "Veeprom.h"

    // Values that can be modified either by hacking this code or through CMakeLists.txt
    // For example, add this line after the add_executable section: 
    // target_compile_definitions(${PROJECT_NAME}  PRIVATE VEE_PAYLOAD_SIZE=3 VEE_VALID_BUFFER_MARKER=0xab01)

#ifndef VEE_NUM_SECTORS_PER_BUFFER
    #define VEE_NUM_SECTORS_PER_BUFFER  1
#endif
#ifndef VEE_VALID_BUFFER_MARKER
    #define VEE_VALID_BUFFER_MARKER  0x01b2   // Use a different value for different applications so left over data does not get misused
#endif
#ifndef VEE_ERASED_BUFFER_MARKER
    #define VEE_ERASED_BUFFER_MARKER  0xffff // if VEE_VALID_BUFFER_MARKER_SIZE is changed, need more or less digits
#endif
#ifndef VEE_VALID_BUFFER_MARKER_SIZE
    #define VEE_VALID_BUFFER_MARKER_SIZE  2  // Must be less than 5 without a code change
#endif
#ifndef VEE_PAYLOAD_SIZE
    #define VEE_PAYLOAD_SIZE  4 // Size of data (1 to 4).
                                // Changing this size above 4 will require access functions (VeeWrite and VeeRead) to change
#endif   

    // Calculated values and values that require code changes if modified 

#define VEE_ENTRY_SIZE   (VEE_PAYLOAD_SIZE+1)   // Size of entry (1 byte for address + N bytes for data)  
#define VEE_NUM_BUFFERS  2  // Don't change this.  Just increase VEE_NUM_SECTORS_PER_BUFFER.
#define VEE_FLASH_START  (PICO_FLASH_SIZE_BYTES - VEE_NUM_BUFFERS*VEE_NUM_SECTORS_PER_BUFFER*FLASH_SECTOR_SIZE)
#define VEE_FLASH_SECTOR_SIZE  FLASH_SECTOR_SIZE
#define VEE_PAGE_OFFSET_MASK    (FLASH_PAGE_SIZE-1)
#define VEE_PAGE_MASK   (~VEE_PAGE_OFFSET_MASK)

#define LAST_ENTRY_PAGE_OFFSET_N  (VEE_ENTRY_SIZE*(FLASH_PAGE_SIZE/VEE_ENTRY_SIZE)-VEE_ENTRY_SIZE)
#define LAST_ENTRY_PAGE_OFFSET_0  (VEE_ENTRY_SIZE*((FLASH_PAGE_SIZE-VEE_VALID_BUFFER_MARKER_SIZE)/VEE_ENTRY_SIZE)-VEE_ENTRY_SIZE+VEE_VALID_BUFFER_MARKER_SIZE)

#define VEE_BUFFER_OFFSET (VEE_NUM_SECTORS_PER_BUFFER*FLASH_SECTOR_SIZE)
#define VEE_MAX_OFFSET  VEE_BUFFER_OFFSET

    // Some checks for sanity
#if VEE_VALID_BUFFER_MARKER_SIZE>4
  #VEE_VALID_BUFFER_MARKER_SIZE_must_be_4_or_less
#endif
#if VEE_VALID_BUFFER_MARKER_SIZE+VEE_ENTRY_SIZE>FLASH_PAGE_SIZE
  #VEE_VALID_BUFFER_MARKER_SIZE_plus_VEE_ENTRY_SIZE_must_be_less_or_equal_to_FLASH_PAGE_SIZE
#endif
#if VEE_PAYLOAD_SIZE>4
  #VEE_PAYLOAD_SIZE_must_be less_than_5_or_change_vee_write_and_vee_read
#endif
#if VEE_PAYLOAD_SIZE<1
  #VEE_PAYLOAD_SIZE_must_be greater_than_0
#endif
#if VEE_MAX_ADDR*VEE_ENTRY_SIZE+VEE_VALID_BUFFER_MARKER_SIZE>=VEE_NUM_SECTORS_PER_BUFFER*FLASH_SECTOR_SIZE
    #VEE_MAX_ADDR_times_VEE_ENTRY_SIZE_plus_VEE_VALID_BUFFER_MARKER_SIZE_is_greater_or_equal_to_buffer_size
#endif
#if VEE_MAX_ADDR>0xfe
    #VEE_MAX_ADDR_must_be_less_than_0xff
#endif 

   // Some cached values to speed things up.
static uint8_t ValidBufferNumber = 0xff;
static uint16_t NextValidOffset = VEE_VALID_BUFFER_MARKER_SIZE;
static uint8_t PageBuffer[FLASH_PAGE_SIZE];
static uint32_t PageBufferAddr = 0xffffffff;

static uint8_t *VeeFlashStart = (uint8_t *) (XIP_BASE + VEE_FLASH_START);

static void EraseSector(uint32_t Addr)
{
    int IntFlags;

    IntFlags = save_and_disable_interrupts();    
    flash_range_erase(VEE_FLASH_START + Addr, FLASH_SECTOR_SIZE);
    restore_interrupts(IntFlags);
    PageBufferAddr = 0xffffffff;  // Blow Page Buffer cache
}

static void LoadPageBuffer(uint32_t Addr)
{
    int i;
    uint32_t PageAddr;

    PageAddr = Addr & VEE_PAGE_MASK;
    if(PageAddr == PageBufferAddr) return;

    PageBufferAddr = PageAddr;

    for(i=0;i<FLASH_PAGE_SIZE;i++){
        PageBuffer[i] = VeeFlashStart[PageAddr++];
    }
}

static void WriteOneWord(uint32_t Addr,uint8_t VeeAddr,uint32_t Data)
{
    int i,IntFlags;
    uint32_t PageAddr,Offset;

    PageAddr = Addr & VEE_PAGE_MASK;
    LoadPageBuffer(Addr);

    Offset = Addr & VEE_PAGE_OFFSET_MASK; 
    PageBuffer[Offset+0] = VeeAddr;
    for(i=0;i<VEE_PAYLOAD_SIZE;i++){
        PageBuffer[Offset+i+1] = (Data>>(8*(VEE_PAYLOAD_SIZE-1-i))) & 0xff;
    }

    IntFlags = save_and_disable_interrupts();
    flash_range_program(VEE_FLASH_START+PageAddr, PageBuffer, FLASH_PAGE_SIZE);
    restore_interrupts(IntFlags);
}

static void UpdateNextValidOffset(uint32_t Addr)
{
    uint16_t i,Payload,Blank,PageOffset;

    LoadPageBuffer(Addr);   
    for(i=VEE_VALID_BUFFER_MARKER_SIZE;i<VEE_FLASH_SECTOR_SIZE*VEE_NUM_SECTORS_PER_BUFFER;i+=VEE_ENTRY_SIZE){
                    // Need to detect stradle of page
        if((i&VEE_PAGE_MASK) != ((i+VEE_ENTRY_SIZE-1) & VEE_PAGE_MASK)){
            i = (i+VEE_ENTRY_SIZE) & VEE_PAGE_MASK;  // bump to zero offset of next page 
            LoadPageBuffer(Addr+i);  
        }            
        Blank = 1;
	    PageOffset = i & VEE_PAGE_OFFSET_MASK;
        for(Payload=0;Payload<VEE_ENTRY_SIZE;Payload++){
            if(PageBuffer[PageOffset+Payload] != 0xff) Blank = 0;
        }            
        if(Blank){  // Found an empty location so this is the end of the list.
            NextValidOffset = i;
            return;
        }
    }
    NextValidOffset = VEE_MAX_OFFSET;   // All filled up case
    return; 
}

static void VeeEraseBuffer(uint32_t Addr)
{
    uint16_t Sector,SectorOffset;
    
    SectorOffset = 0;
    for(Sector=0;Sector<VEE_NUM_SECTORS_PER_BUFFER;Sector++){
        EraseSector(Addr+SectorOffset);
        SectorOffset+=VEE_FLASH_SECTOR_SIZE;
    }     
}

static uint32_t FetchBufferHeader(uint32_t Addr)
{
    int i;
    uint32_t Value = 0;

    for(i=0;i<VEE_VALID_BUFFER_MARKER_SIZE;i++){
        Value = (Value<<8) | VeeFlashStart[Addr+i];
    }
    return(Value);
}

static void WriteValidHeader(uint32_t Addr)
{
    int i,IntFlags;
    uint32_t PageAddr,Offset,Marker;

    PageAddr = Addr & VEE_PAGE_MASK;
    LoadPageBuffer(Addr);

    Offset = Addr & VEE_PAGE_OFFSET_MASK; 
    Marker = VEE_VALID_BUFFER_MARKER;
    for(i=0;i<VEE_VALID_BUFFER_MARKER_SIZE;i++){
        PageBuffer[Offset+i] = (Marker>>(8*(VEE_VALID_BUFFER_MARKER_SIZE-1-i))) & 0xff;
    }

    IntFlags = save_and_disable_interrupts();
    flash_range_program(VEE_FLASH_START+PageAddr, PageBuffer, FLASH_PAGE_SIZE);
    restore_interrupts(IntFlags);
}

static uint32_t FetchBaseAddr(void)
{
    uint32_t FlashData;

    if(ValidBufferNumber != 0xff){
       return(ValidBufferNumber==1 ? VEE_BUFFER_OFFSET : 0); 
    }
    FlashData = FetchBufferHeader(0); 
    if(FlashData == VEE_VALID_BUFFER_MARKER){
        ValidBufferNumber = 0;
        UpdateNextValidOffset(0);      
        return(0);
    }
    if(FlashData != VEE_ERASED_BUFFER_MARKER){  // Memory is trashed
        VeeEraseBuffer(0);
        VeeEraseBuffer(VEE_BUFFER_OFFSET);
        WriteValidHeader(0);    
        ValidBufferNumber = 0;  NextValidOffset = VEE_VALID_BUFFER_MARKER_SIZE;
        return(0);
    }

        // Read header of buffer 1
    FlashData = FetchBufferHeader(VEE_BUFFER_OFFSET);   
    if(FlashData == VEE_VALID_BUFFER_MARKER){
        ValidBufferNumber = 1;
        UpdateNextValidOffset(VEE_BUFFER_OFFSET);      
        return(VEE_BUFFER_OFFSET);
    }
      
       // Neither page is valid so pick page 0
    VeeEraseBuffer(0);
    VeeEraseBuffer(VEE_BUFFER_OFFSET);
    WriteValidHeader(0);   
    ValidBufferNumber = 0;   NextValidOffset = VEE_VALID_BUFFER_MARKER_SIZE; 
    return(0);
}

uint32_t NextAddrBack(uint32_t Addr)
{
    uint32_t NewAddr,PageNumber;

    if(Addr==VEE_VALID_BUFFER_MARKER_SIZE) return(Addr);
    NewAddr = Addr - VEE_ENTRY_SIZE;
    if((NewAddr&VEE_PAGE_MASK) != (Addr & VEE_PAGE_MASK)){   
        PageNumber = NewAddr & VEE_PAGE_MASK;
        if(PageNumber>=VEE_BUFFER_OFFSET) PageNumber-=VEE_BUFFER_OFFSET;
        if(PageNumber==0)
            NewAddr = (NewAddr & VEE_PAGE_MASK)+LAST_ENTRY_PAGE_OFFSET_0;
        else    
            NewAddr = (NewAddr & VEE_PAGE_MASK)+LAST_ENTRY_PAGE_OFFSET_N;  // bump to last offset of previous page
    }    
    return(NewAddr);
}

uint32_t NextAddrForward(uint32_t Addr)
{
    uint32_t NewAddr;

    NewAddr = Addr + VEE_ENTRY_SIZE;
    if(((NewAddr+VEE_ENTRY_SIZE-1)&VEE_PAGE_MASK) != (Addr & VEE_PAGE_MASK)){       
        NewAddr = (NewAddr+VEE_ENTRY_SIZE) & VEE_PAGE_MASK;  // bump to zero offset of next page
    }
    return(NewAddr);
}

uint32_t VeeRead(uint8_t VEEAddr)
{
    int i;
    uint32_t FlashData;
    uint32_t BaseAddr,Offset,Addr;
    uint8_t MemAddr,Done=0;
    uint32_t EmptyValue;

    switch(VEE_PAYLOAD_SIZE){
        case 1:  EmptyValue = 0x000000ff; break;
        case 2:  EmptyValue = 0x0000ffff; break;
        case 3:  EmptyValue = 0x00ffffff; break;
        case 4:  EmptyValue = 0xffffffff; break;
        default: EmptyValue = 0xffffffff; break;
    }
    
        // Invalid address
    if(VEEAddr > VEE_MAX_ADDR) return(EmptyValue);    
    BaseAddr = FetchBaseAddr();
    if(NextValidOffset==VEE_VALID_BUFFER_MARKER_SIZE) return(EmptyValue);  // Empty buffer
    
        // Do a linear search from the last entry at the bottom to the top of the buffer to find most recent version
    Offset = NextAddrBack(NextValidOffset);
    while(!Done){
        Addr = BaseAddr + Offset;
        MemAddr = VeeFlashStart[Addr+0];       
        if(MemAddr == VEEAddr){
            FlashData = 0;
            for(i=0;i<VEE_PAYLOAD_SIZE;i++){
                FlashData = (FlashData<<8) | VeeFlashStart[Addr+i+1];
            }          
            return(FlashData);
        }
        if(Offset == VEE_VALID_BUFFER_MARKER_SIZE) Done=1;
        else Offset = NextAddrBack(Offset);        
    } 
       // Address not found
    return(EmptyValue);
}

    //Copies current buffer to other buffer packing just the current values
    //After copy, erase current buffer and mark new buffer as current.
static void Migrate(uint8_t VEEWriteAddr,uint32_t WriteData)
{
    uint32_t SourceBufferAddr,DestBufferAddr,Data;
    uint16_t VEEAddr,NewNextValidOffset;
    uint8_t WroteNewData = 0;
    
    if(ValidBufferNumber == 0xff) return;
    
    SourceBufferAddr = (ValidBufferNumber==1) ? VEE_BUFFER_OFFSET : 0; 
    DestBufferAddr   = (ValidBufferNumber==0) ? VEE_BUFFER_OFFSET : 0;  
    NewNextValidOffset = VEE_VALID_BUFFER_MARKER_SIZE;

    for(VEEAddr=0;VEEAddr<=VEE_MAX_ADDR;VEEAddr++){
        Data = VeeRead(VEEAddr);
        if(Data != 0xffffffff){
            if(VEEAddr==VEEWriteAddr){
                Data = WriteData;
                WroteNewData = 1;
            }
            WriteOneWord(DestBufferAddr+NewNextValidOffset,VEEAddr,Data);
            NewNextValidOffset = NextAddrForward(NewNextValidOffset);
        }
    }
    WriteValidHeader(DestBufferAddr);
    VeeEraseBuffer(SourceBufferAddr);
    ValidBufferNumber = (ValidBufferNumber==1) ? 0 : 1;
    NextValidOffset = NewNextValidOffset;
    if(!WroteNewData){
        WriteOneWord(DestBufferAddr+NextValidOffset,VEEWriteAddr,WriteData);
        NextValidOffset = NextAddrForward(NextValidOffset);
    }
}

void VeeWrite(uint8_t VEEAddr,uint32_t Data)
{
    uint8_t Ret;
    uint32_t BaseAddr;
    
            // Invalid address check
    if(VEEAddr > VEE_MAX_ADDR) return;
        // Skip the write if the data is the same as existing value
    if(VeeRead(VEEAddr)==Data) return;
    
    BaseAddr = FetchBaseAddr();
    if(NextValidOffset>=VEE_MAX_OFFSET){  // All filled up.  Migrate to alternate page
        Migrate(VEEAddr,Data);        
        return;
    }
    WriteOneWord(BaseAddr+NextValidOffset,VEEAddr,Data);
    NextValidOffset = NextAddrForward(NextValidOffset);
    return;
}

void VeeErase(void)
{
    VeeEraseBuffer(0);
    VeeEraseBuffer(0+VEE_BUFFER_OFFSET);
    WriteValidHeader(0);   
    ValidBufferNumber = 0;   NextValidOffset = VEE_VALID_BUFFER_MARKER_SIZE; 
}

uint32_t VeeFetchDataSize(void)
{
    return(VEE_PAYLOAD_SIZE);
}

VeeDebugInfo VeeDebugFetchInfo(void)
{
    VeeDebugInfo Ret;
    
    Ret.NextValidOffset = NextValidOffset;
    Ret.ValidBufferNumber = ValidBufferNumber;
    
    return(Ret);
}

void VeeDebugBlowCache(void)
{
    ValidBufferNumber = 0xff;
    NextValidOffset = VEE_VALID_BUFFER_MARKER_SIZE;
    PageBufferAddr = 0xffffffff;
}

VeeDebugReadRawInfo VeeDebugReadRawBuffer1(uint16_t Offset)
{
    int i;
    uint32_t Addr,Loop;
    VeeDebugReadRawInfo Ret;
      
    Addr = 0;
    for(Loop=0;Loop<Offset;Loop++){
        if(Loop==0) Addr=VEE_VALID_BUFFER_MARKER_SIZE;
        else        Addr=NextAddrForward(Addr);
    }
    Addr += VEE_BUFFER_OFFSET;
    if(Addr==VEE_BUFFER_OFFSET){
        Ret.Addr = 0;
        Ret.Data = FetchBufferHeader(VEE_BUFFER_OFFSET);
    }
    else{
        Ret.Addr = VeeFlashStart[Addr+0];
            Ret.Data = 0;
            for(i=0;i<VEE_PAYLOAD_SIZE;i++){
                Ret.Data = (Ret.Data<<8) | VeeFlashStart[Addr+i+1];
            }    
    }
    return(Ret);
}

VeeDebugReadRawInfo VeeDebugReadRawBuffer0(uint16_t Offset)
{
    int i;
    uint32_t Addr,Loop;
    VeeDebugReadRawInfo Ret;
      
    Addr = 0;
    for(Loop=0;Loop<Offset;Loop++){
        if(Loop==0) Addr=VEE_VALID_BUFFER_MARKER_SIZE;
        else        Addr=NextAddrForward(Addr);
    }
    if(Addr==0){
        Ret.Addr = 0;
        Ret.Data = FetchBufferHeader(0);
    }
    else{
        Ret.Addr = VeeFlashStart[Addr+0];
            Ret.Data = 0;
            for(i=0;i<VEE_PAYLOAD_SIZE;i++){
                Ret.Data = (Ret.Data<<8) | VeeFlashStart[Addr+i+1];
            }
    }  
    return(Ret);
}