#include <stdio.h>
#include <tusb.h>
#include "pico/stdlib.h"
#include "Serial.h"

void SerialInit(void)
{
    stdio_init_all();
        // Wait for connection or host code will hang forever.  There is a compile switch for
        // this but seems to be timeout related which is no good as it may take minutes for the
        // user to light up the host code after plugging in the PICO to the USB port. 
    while (!tud_cdc_connected()) { sleep_ms(100);  }
}

void SerialPutBytes(uint8_t Data[],uint16_t Count)
{
    uint16_t i;

    for(i=0;i<Count;i++){
        putchar(Data[i]);
    }
    fflush(stdout);
}

void SerialPutByte(uint8_t Data)
{
    putchar(Data);
    fflush(stdout);
}

static uint8_t SavePeekValue,SavePeekValueValid=0,Terminator=0;

char *SerialGets(char *s,int Num)
{
    int i;
    char c,*ptr=s;

    for(i=0;i<Num-1;i++){
        c=SerialGetByte();
        SerialPutByte(c);

        if(c == '\r' || c=='\n'){
            if(!Terminator) Terminator = c;
            if(c==Terminator){
                *s++ = '\n';
                *s = 0;
                return(ptr);
            }
            continue;
        }
        if(i && (c==8 || c==0x7f)){ // Backspace or Delete 
			s--;  i--;
		}
        else{
            *s++ = c;
        }
    }
    *s = 0;
    return(NULL);      
}

uint8_t SerialPeekByte(void)
{
    int In;

    In = getchar_timeout_us(0);
    if(In == PICO_ERROR_TIMEOUT ) return(0);
    SavePeekValue = In & 0xff;
    SavePeekValueValid = 1;
    return(1);
}

uint8_t SerialGetByte(void)
{
    if(SavePeekValueValid){
        SavePeekValueValid = 0;
        return(SavePeekValue);
    }
    while(!SerialPeekByte()); // Work-around for stdio bug in sdk.  Calling getchar when
                        // no character is present causes a hang even when a byte arrives!
    SavePeekValueValid = 0;
    return(SavePeekValue);
}

/*  // Code I found in a forum
uint16_t get_block(uint8_t *buffer,uint16_t Length) {
  uint16_t buffer_index= 0;
  while (1) {
    int c = getchar_timeout_us(100000);
    if (c != PICO_ERROR_TIMEOUT && buffer_index < Length) {
      buffer[buffer_index++] = (c & 0xFF);
    } else {
      break;
    }
  }
  return buffer_index;
}
*/
