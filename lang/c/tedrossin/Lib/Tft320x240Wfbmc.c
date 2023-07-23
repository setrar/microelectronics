// Tft320x240Wfb:  Windowed Frame Buffer version of 320x240 TFT touchscreen display funcions
//          Ted Rossin  5-20-2022
//                      8-22-2022

#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"
#include "Tft320x240Wfbmc.h"

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

static uint8_t Core1Running = 0;

#define CMD_NOP         0
#define CMD_DRAW_LINE   1

queue_t Queue;
typedef struct{
    //uint8_t Cmd;
    uint16_t x0,y0,x1,y1;
    uint16_t Color;
} Cmd_t;

static void core1_entry();

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

    if(!Core1Running){
        queue_init (&Queue,sizeof(Cmd_t),50);
        Core1Running = 1;
        multicore_launch_core1(core1_entry);
        //multicore_fifo_push_blocking(CMD_NOP);
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
    uint8_t Done = 0;
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

    while(!queue_is_empty(&Queue));  // Wait for all the lines to be drawn.

    if(ClearBuffer){
        //while(!Done){        
        while(Ptr!=EndPtr){
                // Unwind loop for performance    
            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;
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

            if(Ptr+8>EndPtr) Done = 1;                        
        }

            // update remainder
        while(Ptr!=EndPtr){
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
    State[ActiveIndex].Fb[Offset] = Color;
}



void wgfLine(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t Color)
{
    //uint32_t Return;
    Cmd_t CmdInfo;

    //Return = multicore_fifo_pop_blocking(); // Wait for last command to finish
    //CmdInfo.Cmd = CMD_DRAW_LINE;
    CmdInfo.x0 = x0;
    CmdInfo.y0 = y0;
    CmdInfo.x1 = x1;
    CmdInfo.y1 = y1;
    CmdInfo.Color = Color;
    queue_add_blocking (&Queue,&CmdInfo);
    //multicore_fifo_push_blocking(CMD_DRAW_LINE);
}


// Some help from Bresenham
static void wgfLineWork(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t Color)
{
    int16_t dx, sx = x0<x1 ? 1 : -1;
    int16_t dy, sy = y0<y1 ? 1 : -1; 
    int16_t err, e2; 
    uint32_t Offset; 

    if(State[ActiveIndex].Fb==NULL) return;
    dx = x1-x0;  if(dx<0) dx = -dx;
    dy = y1-y0;  if(dy<0) dy = -dy;
    err = dx>dy ? dx : -dy;
		// -1/2 = 0 but -1 >> 1 is -1 so clean up the math
    if(err == -1) err = 0; else err = err>>1;

    uint16_t *Ptr = State[ActiveIndex].Fb;
    uint16_t Height = State[ActiveIndex].Height;
    
    while(1){
        //wgfDrawPixel(x0,y0,Color);
        Offset = x0*Height+y0;  // Display is rotated
        Ptr[Offset] = Color;
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx;}
        if (e2 < dy) { err += dx; y0 += sy;}   
    }
}

static void core1_entry() 
{
    //static uint32_t Cmd;
    Cmd_t CmdInfo;

    while(1){
        //Cmd = multicore_fifo_pop_blocking();
        queue_remove_blocking (&Queue,&CmdInfo);
//        switch(CmdInfo.Cmd){
//            case CMD_DRAW_LINE:
                wgfLineWork(CmdInfo.x0,CmdInfo.y0,CmdInfo.x1,CmdInfo.y1,CmdInfo.Color);
//               break;
//       }
        //multicore_fifo_push_blocking(1);    // Send Done
    }
}