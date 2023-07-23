// Tft320x240Wfb:  Windowed Frame Buffer version of 320x240 TFT touchscreen display funcions
//          Ted Rossin  5-20-2022
//                      6-30-2022

#include <stdlib.h>
#include "pico/stdlib.h"
#include "Tft320x240Wfb.h"

#define LCD_RDN     8
#define LCD_WRN     9
#define LCD_RSN     10
#define LCD_CSN     11
#define LCD_RSTN    12

#define LCD_DATA_MASK   0xff

#define MAX_WINDOWS 4
static uint8_t UsedList[MAX_WINDOWS] = {0,0,0,0};
static uint8_t ActiveIndex = 0;
static struct{
    uint16_t *Fb;
    uint16_t Width,Height;
    uint16_t OffsetX,OffsetY;
    uint16_t ClearColor;
} State[MAX_WINDOWS];

void wgfSetActiveWindow(int Id)
{
    if(Id>0 && Id<=MAX_WINDOWS){
        ActiveIndex = Id-1;
    }
}

static void LcdWriteCmd(uint8_t Data)  
{    
    gpio_put(LCD_RSN,0);
    gpio_put_masked(LCD_DATA_MASK,Data);
    gpio_put(LCD_WRN,0); 
    gpio_put(LCD_WRN,1); 
    gpio_put(LCD_RSN,1);    
}

static void LcdWriteData(uint8_t Data)
{ 
    gpio_put_masked(LCD_DATA_MASK,Data);
    gpio_put(LCD_WRN,0);
    gpio_put(LCD_WRN,1);
}

int wgfInit(uint16_t x,uint16_t y,uint16_t w,uint16_t h)
{
    uint8_t Index,Id;
    uint16_t *Ptr,*EndPtr;
    uint16_t *Fb;

    Id = 0; // Find a free index
    for(Index=0;Index<MAX_WINDOWS;Index++){
        if(UsedList[Index]==0){
            Id = Index+1;
            break;
        }
    }
    if(Id==0) return(0);  // No more windows available.  All are in use.
    Fb = (uint16_t *)malloc(w*h*sizeof(uint16_t));
    if(Fb==NULL) return(0);
    ActiveIndex = Id-1;
    UsedList[ActiveIndex] = 1;
        
    State[ActiveIndex].ClearColor = 0x0000;
    State[ActiveIndex].Width = w; State[ActiveIndex].Height = h;
    State[ActiveIndex].OffsetX = x;  State[ActiveIndex].OffsetY = y;
    State[ActiveIndex].Fb = Fb;
  
    Ptr=Fb;
    EndPtr = &Fb[w*h];
    while(Ptr!=EndPtr){
        *Ptr++=0x0000;
    }
    return(Id); 
}

void wgfFree(int Id)
{
    if(Id>0 && Id<=MAX_WINDOWS){
        Id--;
        if(State[Id].Fb != NULL) free(State[Id].Fb);
        State[Id].Fb = NULL;
        UsedList[Id] = 0;
    }
}

static void SetRegion(uint16_t x1, uint16_t y1, uint16_t x2,uint16_t y2)
{
    uint16_t swap;
        // X1 must be less than or equal to x2
        // Y1 must be less than or equal to y2
    if(x2<x1){ swap = x1;  x1=x2;  x2=swap; }
    if(y2<y1){ swap = y1;  y1=y2;  y2=swap; }
        // X: 0 to 319,  Y: 0 to 239
    LcdWriteCmd(0x2a); // Column Address Set
    LcdWriteData(0);
	LcdWriteData((uint8_t)y1);	// Start Column
    LcdWriteData(0);
	LcdWriteData((uint8_t)y2); // End Column
    LcdWriteCmd(0x2b);	// Page Address Set (Row)
	LcdWriteData(x1>>8);
	LcdWriteData((uint8_t)x1);	// Start Row
	LcdWriteData(x2>>8);
	LcdWriteData((uint8_t)x2);	// End Row
	LcdWriteCmd(0x2c);	// Memory Write: Send (EndC-StartC+1)*(EndR-StartR+1) pixels
}

// REVISIT: Find a nice multiple of 8 for while loop then use remainder (modulo) to add little loop at end to
//          make up the difference.  This will improve performance
void wgfUpdateDisplay(uint8_t ClearBuffer)
{
    uint16_t Data,*Ptr;
    uint16_t *EndPtr;
    uint16_t ClearColor;

    if(UsedList[ActiveIndex]==0) return;
    if(State[ActiveIndex].Fb==NULL) return;
    Ptr=State[ActiveIndex].Fb; 
    EndPtr = &State[ActiveIndex].Fb[State[ActiveIndex].Width*State[ActiveIndex].Height];   
    SetRegion(State[ActiveIndex].OffsetX,State[ActiveIndex].OffsetY
        ,State[ActiveIndex].OffsetX+State[ActiveIndex].Width-1,State[ActiveIndex].OffsetY+State[ActiveIndex].Height-1);
    ClearColor = State[ActiveIndex].ClearColor;

    if(ClearBuffer){        
        while(Ptr!=EndPtr){
            //LcdWriteData16(*Ptr);
                // Unwind loop for performance    
            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;
// Can't unwind the loop unless there is an end of loop check before each new transmit which 
// may remove the performance gain.  With a fixed screen size, this was possible but not with
// the variable window size.
#ifdef HELL
            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;

            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;

            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;            

            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;

            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;

            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;

            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor; 
#endif            
        }
    }
    else{
        while(Ptr!=EndPtr){
            //LcdWriteData16(*Ptr++);
                // Unwind loop for performance 
            Data = *Ptr++;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
#ifdef HELL
            Data = *Ptr++;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);

            Data = *Ptr++;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);

            Data = *Ptr++;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
#endif                      
        }
    }        
}

void wgfSetClearColor(uint16_t Color)
{
    State[ActiveIndex].ClearColor = Color;
}

void wgfDrawPixel(uint16_t X,uint16_t Y,uint16_t Color)
{
    uint32_t Offset = X*State[ActiveIndex].Height+Y;  // Display is rotated
    //if(State[ActiveIndex].Fb!=NULL) State[ActiveIndex].Fb[Offset] = Color;
    State[ActiveIndex].Fb[Offset] = Color;
}

// Some help from Bresenham
void wgfLine(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t Color)
{
    int16_t dx, sx = x0<x1 ? 1 : -1;
    int16_t dy, sy = y0<y1 ? 1 : -1; 
    int16_t err, e2; 

    if(State[ActiveIndex].Fb==NULL) return;
    dx = x1-x0;  if(dx<0) dx = -dx;
    dy = y1-y0;  if(dy<0) dy = -dy;
    err = dx>dy ? dx : -dy;
		// -1/2 = 0 but -1 >> 1 is -1 so clean up the math
    if(err == -1) err = 0; else err = err>>1;

    while(1){
        wgfDrawPixel(x0,y0,Color);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }   
    }
}
