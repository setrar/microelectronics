// Veeprom.h: Ted Rossin 8-13-2021 // originally for dsPIC porting to Pico 5-31-2022
//                       6-06-2022

    // Two pages are used
    


#include <pico/stdlib.h>
#include <hardware/flash.h> 

#define VEE_MAX_ADDR 0xfe   // Only need to change this if growing the payload size to a large number
                            // make sure value is less than 0xff.
                            // Memory usage is based on the number of different addresses used not on this value
                            // which just sets the largest address that can be used.                            

typedef struct{
    uint8_t ValidBufferNumber;
    uint16_t NextValidOffset;   
}VeeDebugInfo;

typedef struct{
    uint8_t Addr;
    uint32_t Data;   
}VeeDebugReadRawInfo;

uint32_t VeeRead(uint8_t VEEAddr);
void VeeWrite(uint8_t VEEAddr,uint32_t Data);
void VeeErase(void);
uint32_t VeeFetchDataSize(void);
VeeDebugInfo VeeDebugFetchInfo(void);
VeeDebugReadRawInfo VeeDebugReadRawBuffer0(uint16_t Offset);
VeeDebugReadRawInfo VeeDebugReadRawBuffer1(uint16_t Offset);
void VeeDebugBlowCache(void);
