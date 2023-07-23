/*
    TftTouch.c: Code to read, scale and calibrate 320x240 TFT touch screen.
                Ted Rossin: 6-16-2022
                            6-20-2022
                     
*/

#include <string.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "Tft320x240.h"
#include "Veeprom.h"
#include "TftTouch.h"

#define TF_PRESSURE_THRESHOLD   4   // Pressure must be above calibrated value minus this value
#define TF_DEFAULT_MX   105
#define TF_DEFAULT_XB   -32
#define TF_DEFAULT_MY   84
#define TF_DEFAULT_YB   -40
#define TF_DEFAULT_MP0  -19
#define TF_DEFAULT_PB0  106
#define TF_DEFAULT_MP1  -13
#define TF_DEFAULT_PB1  130 

#define TOUCH_VEE_LAST      0xfe    // Last location in VEEPROM for calibration data

#define LCD_DATA1   1
#define LCD_DATA0   0

#define LCD_RSN     10
#define LCD_CSN     11

#define LCD_Xp      LCD_DATA0
#define LCD_Xn      LCD_RSN
#define LCD_Yp      LCD_CSN
#define LCD_Yn      LCD_DATA1

#define LCD_AN_SRC_X    0
#define LCD_AN_SRC_Y    1

#define FILTER_SIZE     8
#define FILTER_SHIFT    3
#define MAX_CHANGE      4
#define MIN_TOUCH       13

#define HYST      4 // Amount of hysteresis in raw touch units

#define DIR_X     1
#define DIR_Y     2
#define EN_HYST   4

// See GuiCalibrateTouch for equations.
static int16_t TouchXb;  // b
static int16_t TouchYb;  // b
static int16_t TouchMultX;  // m*128   (9.7 fixed point)
static int16_t TouchMultY;  // m*128   (9.7 fixed point)

static int16_t TouchPb0;    // b
static int16_t TouchPb1;    // b
static int16_t TouchMultP0; // m*128   (9.7 fixed point)
static int16_t TouchMultP1; // m*128   (9.7 fixed point)

static uint16_t RawXLast=0,RawYLast=0;
static uint8_t TouchDir = (DIR_Y | DIR_X);  // Hysteresis is off by default
static uint8_t TouchState = 0;
static uint8_t ValuesLoaded = 0;
static uint8_t Zp;
static uint8_t InitAdc = 0;

typedef struct{
    uint8_t Down;
    uint16_t X;
    uint16_t Y;
} RawTouch_t;

static uint16_t FetchAndFilterSample(uint8_t AnalogChannel)
{
    uint16_t LastResult,Result,Max,Min;
    uint8_t Index,SawZero;
    uint16_t Average;
    
    adc_select_input(AnalogChannel);

    Average = 0; SawZero = 0;
    LastResult = adc_read(); // 12 bit result
    for(Index=0;Index<FILTER_SIZE;Index++){
        Result = adc_read(); // 12 bit result
        if(Result<(MIN_TOUCH<<4)) SawZero = 1;
        Max = (LastResult>((256-MAX_CHANGE)<<4)) ? 0xfff : LastResult+(MAX_CHANGE<<4);
        Min = (LastResult<(MAX_CHANGE<<4)) ? 0x000 : LastResult-(MAX_CHANGE<<4);
        if(Result>=Max) Result = Max;
        if(Result<=Min) Result = Min;
        Average+=Result;
        LastResult = Result;
    }
    Result = SawZero ? 0 : (uint16_t)(Average>>(FILTER_SHIFT+3));
    return(Result);
}    

// Note: I'm using the display in landscape mode so X and Y are swapped

static RawTouch_t RawFetchTouch(void)
{
    RawTouch_t Result;
    uint16_t Limit;
    static uint16_t Z1,Z2;
    
    if(!InitAdc){
        adc_init();
        adc_gpio_init(26);
        adc_gpio_init(27);
        InitAdc = 1;
    }

        // Fetch X
        // Xp and Xn inputs, Yp and Yn outputs, Xn to analog
        // Set Yp to 1 and Yn to 0. Read voltage on Xn

            // Read Touch X
    gpio_set_dir(LCD_Xp, GPIO_IN);
    gpio_set_dir(LCD_Xn, GPIO_IN);
    gpio_set_dir(LCD_Yp, GPIO_OUT);
    gpio_set_dir(LCD_Yn, GPIO_OUT);

    gpio_put(LCD_Yp,0); 
    gpio_put(LCD_Yn,1); 

    sleep_us(100);    
    Result.X = FetchAndFilterSample(LCD_AN_SRC_X);    

        // Fetch Y
        // Xp and Xn output, Yp and Yn inputs, Yp to analog
        // Set Xp to 1 and Xn to 0. Read voltage on Yp

    gpio_set_dir(LCD_Xp, GPIO_OUT);
    gpio_set_dir(LCD_Xn, GPIO_OUT);
    gpio_set_dir(LCD_Yp, GPIO_IN);
    gpio_set_dir(LCD_Yn, GPIO_IN);

    gpio_put(LCD_Xp,0); 
    gpio_put(LCD_Xn,1); 

    sleep_us(100);    
    Result.Y = FetchAndFilterSample(LCD_AN_SRC_Y);    
      
        // Fetch Pressure
    
        // Xp and Yn output, Yp and Xn inputs, Yp and Xn to analog
        // Set Xp to 0 and Yn to 1.  Read voltage on Yp and Xn

    gpio_set_dir(LCD_Xp, GPIO_OUT);
    gpio_set_dir(LCD_Xn, GPIO_IN);
    gpio_set_dir(LCD_Yp, GPIO_IN);
    gpio_set_dir(LCD_Yn, GPIO_OUT);    

    gpio_put(LCD_Xp,0); 
    gpio_put(LCD_Yn,1); 
    
    sleep_us(100);  
    Z1 = FetchAndFilterSample(LCD_AN_SRC_X)>>1;
    Z2 = FetchAndFilterSample(LCD_AN_SRC_Y)>>1;
    Zp = 255-(Z2-Z1);
    Result.Down = 0;
    if(Zp>30){
        if(Result.X>128){ 
            if(Result.Y<128) Limit = 60; else Limit = 85;
        }
        else{    
            if(Result.Y<128) Limit = 85; else Limit = 110;
        }
        Result.Down = (Zp>Limit) ? 1 : 0;
    }

        // Restore pin states to drive display.
    gpio_set_dir(LCD_Xp, GPIO_OUT);
    gpio_set_dir(LCD_Xn, GPIO_OUT);
    gpio_set_dir(LCD_Yp, GPIO_OUT);
    gpio_set_dir(LCD_Yn, GPIO_OUT);
    
    gpio_put(LCD_RSN,1);    
    gpio_put(LCD_CSN,0);

    return(Result);
}

static void LoadTouchCalValues(void)
{
    uint32_t Value,Empty;
    uint8_t VeepromSize = VeeFetchDataSize();
    uint8_t VaddrStart;

        // Mult values are the m of y=mx+b times 128
        // b values have no multiplier but are the negative.
        // Default values are X = 0.824*x - 31.9
        //                    Y = 0.656*y - 40.3

    switch(VeepromSize){
        case 4: // 4 bytes per location
            VaddrStart = TOUCH_VEE_LAST-8/2+1;  // 8 items that are 2 bytes each
            Empty = 0xffffffff;
            Value = VeeRead(VaddrStart+0);
            TouchMultX  = (Value==Empty) ?  TF_DEFAULT_MX : (Value>>16) & 0xffff;
            TouchXb     = (Value==Empty) ?  TF_DEFAULT_XB : Value & 0xffff;

            Value = VeeRead(VaddrStart+1);
            TouchMultY  = (Value==Empty) ?  TF_DEFAULT_MY : (Value>>16) & 0xffff;
            TouchYb     = (Value==Empty) ?  TF_DEFAULT_YB : Value & 0xffff;

            Value = VeeRead(VaddrStart+2);
            TouchMultP0 = (Value==Empty) ?  TF_DEFAULT_MP0 : (Value>>16) & 0xffff;
            TouchPb0    = (Value==Empty) ?  TF_DEFAULT_PB0 : Value & 0xffff;

            Value = VeeRead(VaddrStart+3);
            TouchMultP1 = (Value==Empty) ?  TF_DEFAULT_MP1 : (Value>>16) & 0xffff;
            TouchPb1    = (Value==Empty) ?  TF_DEFAULT_PB1 : Value & 0xffff;
            break;

        case 3: // 3 bytes per location
        case 2: // 2 bytes per location
            Empty = (VeepromSize==2) ? 0xffff : 0xffffff;
            VaddrStart = TOUCH_VEE_LAST-8+1;  // 8 items that are 2 bytes each
            Value = VeeRead(VaddrStart+0);
            TouchMultX  = (Value==Empty) ?  TF_DEFAULT_MX : Value & 0xffff;
            Value = VeeRead(VaddrStart+1);
            TouchXb     = (Value==Empty) ?  TF_DEFAULT_XB : Value & 0xffff;

            Value = VeeRead(VaddrStart+2);
            TouchMultY  = (Value==Empty) ?  TF_DEFAULT_MY : Value & 0xffff;
            Value = VeeRead(VaddrStart+3);
            TouchYb     = (Value==Empty) ?  TF_DEFAULT_YB : Value & 0xffff;

            Value = VeeRead(VaddrStart+4);
            TouchMultP0 = (Value==Empty) ?  TF_DEFAULT_MP0 : Value & 0xffff;
            Value = VeeRead(VaddrStart+5);
            TouchPb0    = (Value==Empty) ?  TF_DEFAULT_PB0 : Value & 0xffff;

            Value = VeeRead(VaddrStart+6);
            TouchMultP1 = (Value==Empty) ?  TF_DEFAULT_MP1 : Value & 0xffff;
            Value = VeeRead(VaddrStart+7);
            TouchPb1    = (Value==Empty) ?  TF_DEFAULT_PB1 : Value & 0xffff;
            break;

        case 1: // 1 byte per location
            Empty = 0xffff;
            VaddrStart = TOUCH_VEE_LAST-8*2+1;  // 8 items that are 2 bytes each
            Value = (VeeRead(VaddrStart+0)<<8) | VeeRead(VaddrStart+1);
            TouchMultX  = (Value==Empty) ?  TF_DEFAULT_MX : Value & 0xffff;
            Value = (VeeRead(VaddrStart+2)<<8) | VeeRead(VaddrStart+3);
            TouchXb     = (Value==Empty) ?  TF_DEFAULT_XB : Value & 0xffff;

            Value = (VeeRead(VaddrStart+4)<<8) | VeeRead(VaddrStart+5);
            TouchMultY  = (Value==Empty) ?  TF_DEFAULT_MY : Value & 0xffff;
            Value = (VeeRead(VaddrStart+6)<<8) | VeeRead(VaddrStart+7);
            TouchYb     = (Value==Empty) ?  TF_DEFAULT_YB : Value & 0xffff;

            Value = (VeeRead(VaddrStart+8)<<8) | VeeRead(VaddrStart+9);
            TouchMultP0 = (Value==Empty) ?  TF_DEFAULT_MP0 : Value & 0xffff;
            Value = (VeeRead(VaddrStart+10)<<8) | VeeRead(VaddrStart+11);
            TouchPb0    = (Value==Empty) ?  TF_DEFAULT_PB0 : Value & 0xffff;

            Value = (VeeRead(VaddrStart+12)<<8) | VeeRead(VaddrStart+13);
            TouchMultP1 = (Value==Empty) ?  TF_DEFAULT_MP1 : Value & 0xffff;
            Value = (VeeRead(VaddrStart+14)<<8) | VeeRead(VaddrStart+15);
            TouchPb1    = (Value==Empty) ?  TF_DEFAULT_PB1 : Value & 0xffff;
            break;

        default:
            TouchMultX  = TF_DEFAULT_MX;
            TouchXb     = TF_DEFAULT_XB;
            TouchMultY  = TF_DEFAULT_MY;
            TouchYb     = TF_DEFAULT_YB;
            TouchMultP0 = TF_DEFAULT_MP0;
            TouchPb0    = TF_DEFAULT_PB0;
            TouchMultP1 = TF_DEFAULT_MP1;
            TouchPb1    = TF_DEFAULT_PB1;
            break;
    }

    ValuesLoaded = 1;
}

TfTouch_t TfFetchTouch(void)
{
    uint16_t X,Y,P0,P1;
    RawTouch_t Touch;
    TfTouch_t Result;
    int32_t Value;

    if(!ValuesLoaded) LoadTouchCalValues();
	// Added digital filter inside these routines to clean up the noise
    Touch = RawFetchTouch();

    X = Touch.X;
    Y = Touch.Y;
    if(TouchDir & EN_HYST){
                // Add hysteresis to get rid of jumping in and out of an object.
        if(TouchDir & DIR_X){ // X was increasing so don't decrease unless it is a bigger change
            if(X<RawXLast){
                if(X>(RawXLast-HYST)) X = RawXLast;
                    else TouchDir &= ~DIR_X;  // Change to decreasing
            }
        }
        else{  // X was decreasing
            if(X>RawXLast){
                if(X<(RawXLast+HYST)) X = RawXLast;
                else TouchDir |= DIR_X;  // Change to increasing
            }            
        }
        if(TouchDir & DIR_Y){ // Y was increasing so don't decrease unless it is a bigger change
            if(Y<RawYLast){
                if(Y>RawYLast-HYST) Y = RawYLast;
                else TouchDir &= ~DIR_Y;  // Change to decreasing
            }
        }
        else{  // Y was decreasing
            if(Y>RawYLast){
                if(Y<RawYLast+HYST) Y = RawYLast;
                else TouchDir |= DIR_Y;  // Change to increasing
            }            
        }
        RawXLast = X;
        RawYLast = Y;
    }
    else{
        RawXLast = 0;
        RawYLast = 0;
    }

        // Fixed point multiply X.7 format for TouchMultX=(319/TouchDivX)*128
    Value = (X * TouchMultX + 0x40)>>7;
    X = Value + TouchXb;
    Value = (Y * TouchMultY + 0x40)>>7;
    Y = Value + TouchYb;
    if(X & 0x8000) X = 0;
    if(Y & 0x8000) Y = 0;
    Result.X = (X>=DISP_WIDTH) ? DISP_WIDTH-1 : X;
    Result.Y = (Y>=DISP_HEIGHT) ? DISP_HEIGHT-1 : Y;

        // Pressure interpolation of X along Y=20 line 
    Value = (Result.X * TouchMultP0 + 0x40)>>7;
    P0 = Value + TouchPb0;
        // Pressure interpolation of X along Y=220 line 
    Value = (Result.X * TouchMultP1 + 0x40)>>7;
    P1 = Value + TouchPb1;     
        // Pressure interpolation of Y along X =Result.X line
    int16_t Mf = ((P1-P0)<<7)/(220-20);
    int16_t Bf = ((P0<<7)-(Mf*20)+0x40)>>7;
    Value = (Result.Y * Mf + 0x40)>>7;
    uint16_t ZCalc = Value + Bf;  

    Result.Down = Zp > (ZCalc-TF_PRESSURE_THRESHOLD) ? 1 : 0; //Touch.Down;  // Zp>(ZCalc-30)
    Result.Pressure = Zp;   

    return(Result);
}

typedef struct{
    uint16_t X;
    uint16_t Y;
    uint8_t Pressure;
    uint8_t Valid;
} GetCalPoint_t;

static GetCalPoint_t GetCalPoint(uint16_t X,uint16_t Y)
{
    uint8_t OkX,OkY,Index,Done = 0;
    RawTouch_t Touch;
    GetCalPoint_t Result;
    uint16_t Xacc,Yacc,Pacc;

    uint16_t TextX = (X<DISP_WIDTH/2) ? 50 : 220;
    uint16_t ValidX = (X<DISP_WIDTH/2) ? 20*2 : 128*2;
    uint16_t ValidY = (Y<DISP_HEIGHT/2) ? 20*2 : 128*2;

    gfSetTextColor(0xffff);
    gfPuts(TextX,Y-10,"Here");
    gfHLine(X-20, Y, 40, 0xffff);  
    gfVLine(X, Y-20, 40, 0xffff);  

    while(!Done){
        Touch = RawFetchTouch();
        if(X<DISP_WIDTH/2)  OkX = (Touch.X<150) ? 1 : 0;
        else                OkX = (Touch.X>300) ? 1 : 0;
        if(Y<DISP_HEIGHT/2) OkY = (Touch.Y<150) ? 1 : 0;
        else                OkY = (Touch.Y>250) ? 1 : 0;     
        if(Touch.Down && OkX && OkY){
            Xacc = 0;  Yacc = 0;  Pacc = 0;
            for(Index=0;Index<16;Index++){
        	    Touch = RawFetchTouch();
                Xacc += Touch.X;
                Yacc += Touch.Y;
                Pacc += Zp;
            }
            Xacc = Xacc>>4;
            Yacc = Yacc>>4;
            Pacc = Pacc>>4;
            if(X<DISP_WIDTH/2)  OkX = (Xacc<120) ? 1 : 0;
            else                OkX = (Xacc>330) ? 1 : 0;
            if(Y<DISP_HEIGHT/2) OkY = (Yacc<150) ? 1 : 0;
            else                OkY = (Yacc>300) ? 1 : 0;            
            if(OkX && OkY) Done = 1;
            else{
                gfClearDisplay();
                gfPuts(80,100,"Try again");
                sleep_ms(1200);
                Result.X = 0;
                Result.Y = 0;
                Result.Pressure = 0;
                Result.Valid = 0;
                return(Result);
            }
        }
    }
    gfHLine(X-20, Y, 40, 0x0000);  
    gfVLine(X, Y-20, 40, 0x0000);
    gfSetTextColor(0x0000);
    gfPuts(TextX,Y-10,"Here");
    Result.X = Xacc;
    Result.Y = Yacc;
    Result.Pressure = Pacc;
    Result.Valid = 1;
    return(Result);
}

void TfCalibrate(void)
{
    uint8_t Index;
    uint16_t X,Y,X20,Y20,X300,Y220;
    uint8_t P20_20,P20_220,P300_20,P300_220;
    uint8_t Done = 0;
    RawTouch_t Touch;
    GetCalPoint_t Result;

    while(!Done){  // Wait for touch to be released
        Touch = RawFetchTouch();
        if(Touch.Down==0) Done = 1;
    }
    Done = 0;

    gfSetTextColor(0xffff);
    gfSetTextBackgroundColor(0x0000);
    gfSelectFont(1);
    gfSetFontZoom(1);
    gfClearDisplay();
    gfPuts(80,100,"Touch and Hold");

    Result = GetCalPoint(20,20);
    if(Result.Valid==0) return;
    X20 = Result.X;
    Y20 = Result.Y;
    P20_20 = Result.Pressure;

    Result = GetCalPoint(300,220);
    if(Result.Valid==0) return;
    X300 = Result.X;
    Y220 = Result.Y;
    P300_220 = Result.Pressure;

    Result = GetCalPoint(300,20);
    if(Result.Valid==0) return;
    P300_20 = Result.Pressure;

    Result = GetCalPoint(20,220);
    if(Result.Valid==0) return;
    P20_220 = Result.Pressure;
    
    TouchMultX = ((300-20)<<7)/(X300-X20);
    TouchXb = (((20<<7)-TouchMultX*X20)+0x40)>>7;
    TouchMultY = ((220-20)<<7)/(Y220-Y20);
    TouchYb = (((20<<7)-TouchMultY*Y20)+0x40)>>7;

    TouchMultP0 = ((P20_20-P300_20)<<7)/(20-300);
    TouchPb0 = ((P20_20<<7)-(TouchMultP0*20)+0x40)>>7;
    TouchMultP1 = ((P20_220-P300_220)<<7)/(20-300);
    TouchPb1 = (((P20_220<<7)-TouchMultP1*20)+0x40)>>7;

    uint8_t VeepromSize = VeeFetchDataSize();
    uint8_t VaddrStart;
       
    switch(VeepromSize){
        case 4:
            VaddrStart = TOUCH_VEE_LAST-8/2+1;
            VeeWrite(VaddrStart+0,((uint32_t)TouchMultX<<16)|(TouchXb&0xffff));
            VeeWrite(VaddrStart+1,((uint32_t)TouchMultY<<16)|(TouchYb&0xffff));
            VeeWrite(VaddrStart+2,((uint32_t)TouchMultP0<<16)|(TouchPb0&0xffff));
            VeeWrite(VaddrStart+3,((uint32_t)TouchMultP1<<16)|(TouchPb1&0xffff));
            break;
        case 3:
        case 2:
            VaddrStart = TOUCH_VEE_LAST-8+1;
            VeeWrite(VaddrStart+0,TouchMultX);
            VeeWrite(VaddrStart+1,TouchXb);
            VeeWrite(VaddrStart+2,TouchMultY);
            VeeWrite(VaddrStart+3,TouchYb);
            VeeWrite(VaddrStart+4,TouchMultP0);
            VeeWrite(VaddrStart+5,TouchPb0);
            VeeWrite(VaddrStart+6,TouchMultP1);
            VeeWrite(VaddrStart+7,TouchPb1);            
            break;
        case 1:
            VaddrStart = TOUCH_VEE_LAST-8*2+1;
            VeeWrite(VaddrStart+0,(TouchMultX>>8) & 0xff);
            VeeWrite(VaddrStart+1, TouchMultX     & 0xff);
            VeeWrite(VaddrStart+2,(TouchXb>>8) & 0xff);
            VeeWrite(VaddrStart+3, TouchXb     & 0xff);            
            VeeWrite(VaddrStart+4,(TouchMultY>>8) & 0xff);
            VeeWrite(VaddrStart+5, TouchMultY     & 0xff);
            VeeWrite(VaddrStart+6,(TouchYb>>8) & 0xff);
            VeeWrite(VaddrStart+7, TouchYb     & 0xff); 
            VeeWrite(VaddrStart+8,(TouchMultP0>>8) & 0xff);
            VeeWrite(VaddrStart+9, TouchMultP0     & 0xff); 
            VeeWrite(VaddrStart+10,(TouchPb0>>8) & 0xff);
            VeeWrite(VaddrStart+11, TouchPb0     & 0xff);
            VeeWrite(VaddrStart+12,(TouchMultP1>>8) & 0xff);
            VeeWrite(VaddrStart+13, TouchMultP1     & 0xff); 
            VeeWrite(VaddrStart+14,(TouchPb1>>8) & 0xff);
            VeeWrite(VaddrStart+15, TouchPb1     & 0xff);           
            break;                     
    }

    gfSetTextColor(0x0000);
    gfPuts(240,200,"Here");
    gfPuts(80,100,"Touch and Hold");
    gfHLine(DISP_WIDTH-40, DISP_HEIGHT-20, 40, 0x0000);  
    gfVLine(DISP_WIDTH-20, DISP_HEIGHT-40, 40, 0x0000);  
    gfSetTextColor(0xffff);
    gfPuts(5,150,"All Done.  Release");

    Done=0;
    while(!Done){
        Touch = RawFetchTouch();
        if(Touch.Down==0) Done = 1;
    }
    gfClearDisplay();
}

void TfEnableHyst(void)
{
    TouchDir |= EN_HYST;
}

void TfDisableHyst(void)
{
    TouchDir &= ~EN_HYST;
}