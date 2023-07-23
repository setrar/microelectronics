//Generated using CreateLcdGui (V0.05) by Ted Rossin

#include "WhichDev.h"
#ifdef RASP_PI_PICO
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "pico/stdlib.h"
  #include "Tft320x240.h"
  #include "TftTouch.h"
#else
  #include <xc.h>
  #include <stdint.h>
  #include <string.h>
  #include "WhichDevDsPIC.h"
  #ifdef DSPIC_DEV
    #include "TimerDsPIC.h"
    #include "Veeprom.h"
  #else  // 18F26K40
    #include "Timer18F.h"
  #endif
  #include "TftGraphics.h"
  #include "string_funcs.h"
#endif
#include "gui.h"

#ifdef RASP_PI_PICO
  #define GUI_EESTART 0xfd
  typedef uint32_t ObjParm_t;
#else
  #ifdef DSPIC_DEV
    #define GUI_EESTART	0xfe

  #else  // 18F26K40
    #define GUI_EESTART	0x3f8

  #endif
  typedef uint16_t ObjParm_t;
#endif
#define ID_OFFSET 8

#define TYPE_BUTTON   0
#define TYPE_RECT     1
#define TYPE_TEXT     2
#define TYPE_SPIN     3
#define TYPE_CHECK    4
#define TYPE_DRAW     5
#define TYPE_LIST_BOX 6
#define NUM_PARMS   10

#define FLAG_NONE 		0x00
#define FLAG_STATIC_TEXT	0x01
#define FLAG_DEC 		0x02
#define FLAG_DEC_MULTI_ARROW	0x03
#define FLAG_HEX 		0x04
#define FLAG_HEX_MULTI_ARROW	0x05
#define FLAG_ALPHA		0x06
#define FLAG_ALPHA_NUM		0x07
#define FLAG_ALPHA_NUM_OTH	0x08
#define FLAG_MULTI_SELECT	0x10

#define BUTTON_EXTRA_LINE_SPACE	0
#define BUTTON_X_MARGIN	1
#define BUTTON_Y_MARGIN	2
#define BUTTON_ID	3
#define RECT_BORDER_W	0
#define RECT_FILL	1
#define TEXT_EXTRA_LINE_SPACE	0
#define TEXT_ID	2
#define SPIN_ARROW_HEIGHT	0
#define SPIN_DIGIT_SPACE_X	1
#define SPIN_DIGIT_SPACE_Y	2
#define SPIN_NUM_DIGITS	3
#define SPIN_MIN	4
#define SPIN_MAX	5
#define SPIN_VALUE	6
#define SPIN_ARROW_CLICK_WIDTH	7
#define SPIN_ID	8
#define CHECK_VALUE	0
#define CHECK_ID	1
#define DRAW_ID	0

#define LIST_BOX_MAX_WIDTH	0
#define LIST_BOX_SHOW_ITEMS	1
#define LIST_BOX_MAX_ITEMS	2
#define LIST_BOX_SHOW_WIDTH	3
#define LIST_BOX_ARROW_WIDTH	4
#define LIST_BOX_ARROW_HEIGHT	5
#define LIST_BOX_SCROLL_OFFSET	6
#define LIST_BOX_NUM_ITEMS	7
#define LIST_BOX_SELECTED	8
#define LIST_BOX_TEXT_WR_PTR	9

#define NUM_OBJECTS_Main 6
#define NUM_SCREENS 1

#define EQ_SIZE 10
static struct {
    uint8_t Rd, Wr, Size;
}EqInfo;

typedef struct {
    uint8_t Type; 
    uint16_t X, Y, W, H; 
    uint16_t RGB, BgRGB; 
    uint8_t FontId; 
    uint8_t Flags; 
    const char *Text; 
    ObjParm_t Parm[NUM_PARMS]; 
} Object_t;

typedef struct {
	uint16_t BgColor;
	uint8_t NumObjects;
	Object_t* Obj;
} Screen_t;

static uint8_t mCurrentScreen;
static uint8_t TimerFlags;
static void UpdateItem(uint8_t Index);
#ifndef RASP_PI_PICO
static void LoadTouchCalValues(void);
#endif

static const char TextMain0[]="UP";
static const char TextMain1[]="Down";
static const char TextMain5[]="Timer";

static char TextMain2[6];
static uint16_t SpinMain0;
static char TextMain4[4];

static const Object_t mObjectMain[] = {
    {0,18,109,100,50,0x081f,0x07e6,129,0x0,TextMain0,{ 3,30,10,8,0,0,0,0,0,0}}
   ,{0,16,169,100,50,0x081f,0x07e6,129,0x0,TextMain1,{ 1,3,10,9,0,0,0,0,0,0}}
   ,{2,129,152,120,32,0x0000,0xffe0,129,0x0,TextMain2,{ 0,5,10,0,0,0,0,0,0,0}}
   ,{3,9,10,140,86,0xffff,0x311f,129,0x3,0,{ 25,2,2,5,0,65535,(ObjParm_t)&SpinMain0,28,11,0}}
   ,{2,269,12,36,16,0xffff,0x0000,1,0x0,TextMain4,{ 0,3,12,0,0,0,0,0,0,0}}
   ,{2,272,34,30,8,0xffff,0xfc00,0,0x1,TextMain5,{ 0,20,13,0,0,0,0,0,0,0}}
};

static Screen_t const Screen[] = {
     {0xfc00,NUM_OBJECTS_Main,(Object_t*)mObjectMain}
};

#ifndef RASP_PI_PICO
// See GuiCalibrateTouch for equations.
static uint16_t TouchXb;  // -b
static uint16_t TouchYb;  // -b
static uint16_t TouchMultX;  // m*128   (9.7 fixed point)
static uint16_t TouchMultY;  // m*128   (9.7 fixed point)
#endif

void GuiInit(void)
{
    uint16_t i;

    gfInit();
    GuiEnableTouchHyst();
#ifndef RASP_PI_PICO
    LoadTouchCalValues();
#endif

    mCurrentScreen = 0;
    EqInfo.Rd = 0; 
    EqInfo.Wr = 0; 
    EqInfo.Size = 0;
    TimerFlags = 0;

    // Screen: Main
    strcpy(TextMain2,"12345");
    SpinMain0=10000;
    strcpy(TextMain4,"123");
}

uint16_t GuiGetValue(uint16_t Id)
{
    uint16_t Value=0;

    switch(mCurrentScreen){
        case 0: // Screen: Main
            switch(Id){
                case ID_SPIN_VALUE: Value=SpinMain0; break;
            }
            break;
    }
    return(Value);
}

void GuiGetString(uint16_t Id,char *String)
{
    switch(mCurrentScreen){
        case 0: // Screen: Main
            switch(Id){
                case ID_TEXT_VALUE: strcpy(String,TextMain2); break;
                case ID_TEXT_TIMER: strcpy(String,TextMain4); break;
            }
            break;
    }
}

void GuiSetValue(uint16_t Id,uint16_t Value)
{
    switch(mCurrentScreen){
        case 0: // Screen: Main
            switch(Id){
                case ID_SPIN_VALUE: SpinMain0=Value; UpdateItem(3); break;
            }
            break;
    }
}

void GuiSetString(uint16_t Id,char *String)
{
    switch(mCurrentScreen){
        case 0: // Screen: Main
            switch(Id){
                case ID_TEXT_VALUE: strncpy(TextMain2,String,5); TextMain2[5] = 0; UpdateItem(2); break;
                case ID_TEXT_TIMER: strncpy(TextMain4,String,3); TextMain4[3] = 0; UpdateItem(4); break;
            }
            break;
    }
}

#ifdef RASP_PI_PICO
  #define sprintf1(a,b,c) sprintf(a,b,c)

// REVISIT:  Fix up time
uint16_t FetchTimerms(void)
{
    return(((time_us_64()/1000)&0xffff));
}

void Waitms(uint16_t Amount)
{
    sleep_ms(Amount);
}

/*
 *  Equation is based on signs of variables to protect from the ms timer wrapping.
 *   Note that compares are done unsigned
 * SavedTime  FinalTime  Sample  Equation
 *     0        0        0          Sample>=FinalTime
 *     0        0        1          1
 *     0        1        0          0
 *     0        1        1          Sample>=FinalTime
 *     1        0        0          Sample>=FinalTime
 *     1        0        1          0
 *     1        1        0          1
 *     1        1        1          Sample>=FinalTime
 */
uint8_t TimemsExceeded(uint16_t SavedTime, uint16_t Num)
{
        // If SavedTime has sign bit set(15) and FinalTime does not then the final time wrapped.
        // This means that the time has elapsed only if the current time does not have the sign bit set
        // and the current time is greater than the final time
    uint16_t FinalTime;
    uint16_t Sample;
   
    FinalTime = SavedTime + Num;
    Sample = FetchTimerms();
    if(SavedTime & 0x8000){ 
        if((FinalTime & 0x8000) == (Sample & 0x8000)){ // Sample and FinalTime have the same sign
            return(Sample>=FinalTime ? 1 : 0);
        }
        return((Sample & 0x8000) ? 0 : 1);
    }
    else{  // SavedTime sign is 0
        if((FinalTime & 0x8000) == (Sample & 0x8000)){ // Sample and FinalTime have the same sign
            return(Sample>=FinalTime ? 1 : 0);
        }
        return((Sample & 0x8000) ? 1 : 0);
    }
}

#else

  #define HYST      3

  #define DIR_X     1
  #define DIR_Y     2
  #define EN_HYST   4

#endif

#define TF_TOUCH_JUST_DOWN 1
#define TF_TOUCH_JUST_UP   2
#define TF_TOUCH_IS_DOWN   4

#define GUI_FLAG_SCREEN_JUST_CHANGED    1


    //(0x20 and 0xd0) {0010_0,001_000,0_0100} 0x2104  {1101_0,110_100,1_1010} 0xd69a
#define EDGE_3D_LIGHT 0xd69a
#define EDGE_3D_DARK  0x2104

static void DrawObject(uint8_t Index);

static GuiMessage_t EventQueue[EQ_SIZE];
#ifndef RASP_PI_PICO
static uint8_t TouchDir = (EN_HYST | DIR_Y | DIR_X);
#endif
static uint8_t TouchState = 0;
static uint16_t TouchXLast = 0;
static uint16_t TouchYLast = 0;
static uint8_t mGuiFlags = 0;

static uint16_t RawXLast=0,RawYLast=0;
static const uint16_t SpinDigitLut[5]={1,10,100,1000,10000};
static uint8_t FirstWait=0;
static uint16_t AutoRepeatTime=0;
static struct{
    uint16_t Start;
    uint16_t Period;
} Timer[NUM_TIMERS];

static void SendMessage(uint8_t Id,uint8_t Event,uint16_t X,uint16_t Y)
{
    if(EqInfo.Size==EQ_SIZE) return; // Bummer, the event queue is full
    EventQueue[EqInfo.Wr].Id = Id;
    EventQueue[EqInfo.Wr].Event = Event;
    EventQueue[EqInfo.Wr].X = X;
    EventQueue[EqInfo.Wr].Y = Y;
    EqInfo.Wr++;
    if(EqInfo.Wr==EQ_SIZE) EqInfo.Wr = 0;
    EqInfo.Size++; 
}

GuiMessage_t GuiReadMessage(void)
{
    GuiMessage_t Ret;
    if(EqInfo.Size==0){
        Ret.Id = ID_EMPTY;
        Ret.Event = 0;
        Ret.X = 0;
        Ret.Y = 0;
    }
    else{
        Ret = EventQueue[EqInfo.Rd];
        EqInfo.Rd++;
        if(EqInfo.Rd==EQ_SIZE) EqInfo.Rd = 0;
        EqInfo.Size--;
    }
    return(Ret);
}

static uint8_t GuiPickObject(uint16_t X,uint16_t Y)
{
    uint8_t Limit,Index;
    const Object_t *Obj;
    
    Limit =  Screen[mCurrentScreen].NumObjects;
    for(Index=0;Index<Limit;Index++){
        Obj = &Screen[mCurrentScreen].Obj[Index];
        switch(Obj[0].Type){
            case TYPE_BUTTON:
            case TYPE_SPIN:
            case TYPE_CHECK:
            case TYPE_LIST_BOX:
                if(X>=Obj[0].X && X<=Obj[0].X+Obj[0].W && Y>=Obj[0].Y && Y<=Obj[0].Y+Obj[0].H) return(Index);
                break;
        }
    }

    return(0xff);
}

#if defined(DSPIC_DEV) | defined(RASP_PI_PICO)

#else  
static unsigned char EERead(unsigned int Addr)
{    
    unsigned char RetVal;
            
    NVMADRL = Addr & 0xff;
    NVMADRH = Addr>>8;
    NVMCON1bits.NVMREG0 = 0;
    NVMCON1bits.NVMREG1 = 0;
    NVMCON1bits.RD = 1;
    RetVal = NVMDAT;
    NVMCON1bits.NVMREG1 = 1;  // Restore flash access for table read
    return(RetVal);     
}

static void EEWrite(unsigned int Addr,unsigned char Data)
{    
    NVMADRL = Addr & 0xff;
    NVMADRH = Addr>>8;
    NVMCON1bits.NVMREG0 = 0;
    NVMCON1bits.NVMREG1 = 0;
    NVMDAT = Data;
    NVMCON1bits.WREN = 1;
    INTCONbits.GIE = 0;
    NVMCON2 = 0x55;
    NVMCON2 = 0xaa;
    NVMCON1bits.WR = 1;
    while(NVMCON1bits.WR);
    NVMCON1bits.WREN = 0;
    NVMCON1bits.NVMREG1 = 1;  // Restore flash access for table read
    INTCONbits.GIE = 1;
}
#endif

void GuiStartTimer(uint8_t TimerId,uint16_t Periodms)
{
    if(TimerId>=NUM_TIMERS) return;
    Timer[TimerId].Period = Periodms;
    Timer[TimerId].Start = FetchTimerms();
    TimerFlags |= (1<<TimerId);  // Enable timer
}

void GuiStopTimer(uint8_t TimerId)
{
    if(TimerId>=NUM_TIMERS) return;
    TimerFlags &= ~(1<<TimerId);  // Disable timer
}

static void Draw3dEdge(uint8_t Up,uint16_t X,uint16_t Y,uint16_t W,uint16_t H)
{
    uint16_t BottomColor,TopColor;
    
    BottomColor = Up ? EDGE_3D_DARK : EDGE_3D_LIGHT;
    TopColor = Up ? EDGE_3D_LIGHT : EDGE_3D_DARK;
    
    gfVLine(X+W-1,Y, H,BottomColor);
    gfHLine(X,Y+H-1, W,BottomColor);
    gfVLine(X,Y, H,TopColor);
    gfHLine(X,Y, W,TopColor);
        // Make double thick
    gfVLine(X+1+(W-2)-1,Y+1, H-2,BottomColor);
    gfHLine(X+1,(Y+1)+(H-2)-1, W-2,BottomColor);
    gfVLine(X+1,Y+1, H-2,TopColor);
    gfHLine(X+1,Y+1, W-2,TopColor); 
}

static void RaiseAllButtons(uint8_t Id)
{
    uint8_t NumArrows,ArrowClickHeight,Index;
    uint16_t ArrowClickWidth,X;
    const Object_t *Obj;    
   
    if(Id>=Screen[mCurrentScreen].NumObjects) return;
    Obj = &Screen[mCurrentScreen].Obj[Id];
     switch(Obj[0].Type){
        case TYPE_BUTTON:
            Draw3dEdge(1,Obj[0].X,Obj[0].Y,Obj[0].W,Obj[0].H);
            break;
        case TYPE_LIST_BOX:
            ArrowClickWidth =  Obj[0].Parm[LIST_BOX_ARROW_WIDTH];
            ArrowClickHeight = Obj[0].Parm[LIST_BOX_ARROW_HEIGHT];
	    X = Obj[0].X+Obj[0].W - ArrowClickWidth;
            Draw3dEdge(1,X,Obj[0].Y,ArrowClickWidth,ArrowClickHeight);
            Draw3dEdge(1,X,Obj[0].Y+Obj[0].H-ArrowClickHeight
		,ArrowClickWidth,ArrowClickHeight);
            break;
        case TYPE_SPIN:
            NumArrows = (Obj[0].Flags==FLAG_DEC || Obj[0].Flags == FLAG_HEX) ? 1 : Obj[0].Parm[SPIN_NUM_DIGITS];
            ArrowClickWidth =  Obj[0].Parm[SPIN_ARROW_CLICK_WIDTH];
            ArrowClickHeight = Obj[0].Parm[SPIN_ARROW_HEIGHT];
            switch (Obj[0].Flags) {
                case FLAG_DEC:
                case FLAG_HEX:
                    Draw3dEdge(1,Obj[0].X,Obj[0].Y,Obj[0].W,ArrowClickHeight);
                    Draw3dEdge(1,Obj[0].X,Obj[0].Y+Obj[0].H-ArrowClickHeight,Obj[0].W,ArrowClickHeight);
                    break;
                default:
                    X = Obj[0].X;
                    for(Index=0;Index<Obj[0].Parm[SPIN_NUM_DIGITS];Index++){ 
                        Draw3dEdge(1,X,Obj[0].Y,ArrowClickWidth,ArrowClickHeight);
                        Draw3dEdge(1,X,Obj[0].Y+Obj[0].H-ArrowClickHeight,ArrowClickWidth,ArrowClickHeight);
                        X+= ArrowClickWidth;
                    }
                    break;
            }
     }           
}

static uint8_t LbFetchSelected(uint16_t Index,uint8_t Array[])
{
    uint8_t Val;
    
    Val = Array[Index>>3];
    return((Val&(1<<(Index&7))) ? 1 : 0);
}

static void LbSetSelected(uint8_t Value,uint16_t Index,uint8_t Array[])
{
    if(Value){
        Array[Index>>3] |= (1<<(Index&7));
    }
    else{
        Array[Index>>3] &= ~(1<<(Index&7));
    }
}


static void GuiManageObject(uint16_t X,uint16_t Y)
{
    uint8_t Update,Id,b,NumArrows,ArrowClickHeight,Index,SaveIndex,*Ptr8;
    uint16_t ArrowClickWidth,Val,Amount=0,Loop,SOff;
    const Object_t *Obj;
    char *Ptr=0;
    static uint8_t LastId = 0xff,LastScreen=0xff;
    static uint8_t LastSpinIndex = 0xff;
    
    Id = GuiPickObject(X,Y);
#ifdef LA_DEBUG
    LATAbits.LA0 = LATAbits.LA0 ? 0 : 1;  // Toggle debug clock edge
    LATAbits.LA1 =  (Id != 0xff) ? 1 : 0;
    LATAbits.LA2 =  (TouchState & TF_TOUCH_JUST_DOWN) ? 1 : 0;
#endif
   
    if(TouchState & TF_TOUCH_JUST_UP){ // Id was set to Id before touch released but it is currently invalid
        LastId = 0xff;
    }
    else{  // Check to see if touch moved outside a selectable object (either moved to invalid object or a different object.
           // If so, need to raise all the previous objects buttons.
        if(LastId != 0xff){
            if(LastId != Id){
                if(LastScreen==mCurrentScreen) RaiseAllButtons(LastId);
                if(Id!=0xff){
                    TouchState |= TF_TOUCH_JUST_DOWN;
                }
            }
        }
        else{ // Last ID was not valid (0xff)
            if(Id!=0xff){ // Touch was down but not on an ID then it went to a valid ID.
                TouchState |= TF_TOUCH_JUST_DOWN;
            }        
        }
        LastId = Id;
    	LastScreen = mCurrentScreen;
    }
   
    if(Id==0xff){
        LastSpinIndex = 0xff;
        return;
    }
    
    Obj = &Screen[mCurrentScreen].Obj[Id];
    switch(Obj[0].Type){
        case TYPE_BUTTON:
            if(TouchState & TF_TOUCH_JUST_DOWN){
                Draw3dEdge(0,Obj[0].X,Obj[0].Y,Obj[0].W,Obj[0].H);
                SendMessage(Obj[0].Parm[BUTTON_ID],EVENT_PUSHED,0,0);  // Id,EVENT,X,Y
            }
            else if(TouchState & TF_TOUCH_JUST_UP){
                 Draw3dEdge(1,Obj[0].X,Obj[0].Y,Obj[0].W,Obj[0].H);
            }
            break;
            
        case TYPE_CHECK:
            if(TouchState & TF_TOUCH_JUST_DOWN){
                b = *(uint16_t*)Obj[0].Parm[CHECK_VALUE];
                *(uint16_t*)Obj[0].Parm[CHECK_VALUE] = b ? 0 : 1;
                UpdateItem(Id);
                SendMessage(Obj[0].Parm[CHECK_ID],EVENT_CHANGED,0,0);  // Id,EVENT,X,Y
            }
            break;

        case TYPE_LIST_BOX:
            X-=Obj[0].X;  Y-=Obj[0].Y;
            ArrowClickWidth =  Obj[0].Parm[LIST_BOX_ARROW_WIDTH];
            ArrowClickHeight = Obj[0].Parm[LIST_BOX_ARROW_HEIGHT];
            Update = 0;        
            if(TouchState & TF_TOUCH_JUST_UP){
                RaiseAllButtons(Id);                
            }
            else if(TouchState & TF_TOUCH_JUST_DOWN){
                AutoRepeatTime = FetchTimerms();
                if(X>Obj[0].W-ArrowClickWidth){
                    Update = 1;
                }
                else{
                    Update = 2;
                }
                FirstWait = 1;
                TouchState = TF_TOUCH_IS_DOWN;
            }
            else{
                if(X>Obj[0].W-ArrowClickWidth){  // Scroll arrow region
                    if(FirstWait){
                        if(TimemsExceeded(AutoRepeatTime, 400)){ // Wait 400ms before auto advance
                            FirstWait = 0;
                            AutoRepeatTime = FetchTimerms();
                            Update = 1;
                        }
                    }
                    else{
                        if(TimemsExceeded(AutoRepeatTime, 150)){
                            AutoRepeatTime = FetchTimerms();
                            Update = 1;
                        }
                    }
                }
            }
            if(Update==1){
                Update = 0;
                if(Y<ArrowClickHeight && X>Obj[0].W-ArrowClickWidth){
                    Val = *(uint16_t*)Obj[0].Parm[LIST_BOX_SCROLL_OFFSET];
                    if(Val!=0){
                        *(uint16_t*)Obj[0].Parm[LIST_BOX_SCROLL_OFFSET] = Val-1;
                        Update = 1;
                    }
                    if(FirstWait || LastSpinIndex==0xff){
                         Draw3dEdge(0,Obj[0].X+Obj[0].W-ArrowClickWidth,Obj[0].Y,ArrowClickWidth,ArrowClickHeight);
                         LastSpinIndex = 0;
                    }
                    else{
                        if(LastSpinIndex!=0xff && LastSpinIndex!=0){  // Previously had   
                            RaiseAllButtons(Id);
                            Draw3dEdge(0,Obj[0].X+Obj[0].W-ArrowClickWidth,Obj[0].Y,ArrowClickWidth,ArrowClickHeight);
                            LastSpinIndex = 0;
                        }
                    }
                }
                else if(Y>Obj[0].H-ArrowClickHeight && X>Obj[0].W-ArrowClickWidth){
                    Val = *(uint16_t*)Obj[0].Parm[LIST_BOX_SCROLL_OFFSET];
                    if(*(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS]<=Obj[0].Parm[LIST_BOX_SHOW_ITEMS]){
                        *(uint16_t*)Obj[0].Parm[LIST_BOX_SCROLL_OFFSET] = 0;
                        Update = (Val==0) ? 0 : 1;
                    }
                    else if(Val<(*(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS]-Obj[0].Parm[LIST_BOX_SHOW_ITEMS])){
                       *(uint16_t*)Obj[0].Parm[LIST_BOX_SCROLL_OFFSET] = Val+1;
                        Update = 1;
                    }
                    if(FirstWait || LastSpinIndex==0xff){
                         Draw3dEdge(0,Obj[0].X+Obj[0].W-ArrowClickWidth,Obj[0].Y+Obj[0].H-ArrowClickHeight,ArrowClickWidth,ArrowClickHeight);
                         LastSpinIndex = 1;
                    }
                    else{
                        if(LastSpinIndex!=0xff && LastSpinIndex!=1){  // Previously had   
                            RaiseAllButtons(Id);
                            Draw3dEdge(0,Obj[0].X+Obj[0].W-ArrowClickWidth,Obj[0].Y+Obj[0].H-ArrowClickHeight,ArrowClickWidth,ArrowClickHeight);
                            LastSpinIndex = 1;
                        }
                    }
                }
                else{  // Touch down on list box but not over a button (in the center instead)
                    RaiseAllButtons(Id);
                    LastSpinIndex = 0xff;
                }
                if(Update){
                    UpdateItem(Id);
                }
            }
            else if(Update==2){  // Click in text area of list box
                Ptr8 = (uint8_t*)Obj[0].Parm[LIST_BOX_SELECTED];
                Val = 2;
                Amount = *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS];      
                if(Amount>Obj[0].Parm[LIST_BOX_SHOW_ITEMS]) Amount = Obj[0].Parm[LIST_BOX_SHOW_ITEMS];            
                SOff = *(uint16_t*)Obj[0].Parm[LIST_BOX_SCROLL_OFFSET];
                gfSelectFont(Obj[0].FontId & 0x7f);
                gfSetFontZoom(Obj[0].FontId & 0x80 ? 2 : 1);   
                for(Loop=0;Loop<Amount;Loop++){   
                    if(Y>=Val && Y<(Val+gfGetFontHeight())){
                        if(!(Obj[0].Flags & FLAG_MULTI_SELECT)){
                            GuiLbSetAllSelected(mCurrentScreen,Id+ID_OFFSET,0);
                        }
                        LbSetSelected(LbFetchSelected(Loop+SOff,Ptr8)?0:1,Loop+SOff,Ptr8);
                        break;
                    }
                    Val+=gfGetFontHeight();
                }      
                UpdateItem(Id);
                SendMessage(Id+ID_OFFSET,EVENT_CHANGED,0,0);  // Id,EVENT,X,Y
            }
            break;
            

        case TYPE_SPIN:
            X-=Obj[0].X;  Y-=Obj[0].Y;
            NumArrows = (Obj[0].Flags==FLAG_DEC || Obj[0].Flags == FLAG_HEX) ? 1 : Obj[0].Parm[SPIN_NUM_DIGITS];
            ArrowClickWidth =  Obj[0].Parm[SPIN_ARROW_CLICK_WIDTH];
            ArrowClickHeight = Obj[0].Parm[SPIN_ARROW_HEIGHT];
            Update = 0;
            
            if(TouchState & TF_TOUCH_JUST_UP){
                RaiseAllButtons(Id);                
            }
            else if(TouchState & TF_TOUCH_JUST_DOWN){
                AutoRepeatTime = FetchTimerms();
                Update = 1;  
                FirstWait = 1;
                TouchState = TF_TOUCH_IS_DOWN;
            }
            else{
                if(FirstWait){
                    if(TimemsExceeded(AutoRepeatTime, 400)){ // Wait 400ms before auto advance
                        FirstWait = 0;
                        AutoRepeatTime = FetchTimerms();
                        Update = 1;
                    }
                }
                else{
                    if(TimemsExceeded(AutoRepeatTime, 150)){
                        AutoRepeatTime = FetchTimerms();
                        Update = 1;
                    }
                }
            }
            
            if(Update){
                Update = 0;
                switch (Obj[0].Flags) {
                    case FLAG_DEC:
                    case FLAG_HEX:
                        if(Y<ArrowClickHeight){
                            Val = *(uint16_t*)Obj[0].Parm[SPIN_VALUE] + 1;
                            if(Val>Obj[0].Parm[SPIN_MAX]) Val = Obj[0].Parm[SPIN_MAX];
                            *(uint16_t*)Obj[0].Parm[SPIN_VALUE] = Val;
                            Update = 1;
                            if(FirstWait || LastSpinIndex==0xff){
                                 Draw3dEdge(0,Obj[0].X,Obj[0].Y,Obj[0].W,ArrowClickHeight);
                                 LastSpinIndex = 0;
                            }
                            else{
                                if(LastSpinIndex!=0xff && LastSpinIndex!=0){  // Previously had   
                                    RaiseAllButtons(Id);
                                    Draw3dEdge(0,Obj[0].X,Obj[0].Y,Obj[0].W,ArrowClickHeight);
                                    LastSpinIndex = 0;
                                }
                            }
                        }
                        else if(Y>Obj[0].H-ArrowClickHeight){
                            Val = *(uint16_t*)Obj[0].Parm[SPIN_VALUE];
                            if(Val!=0) Val--; 
                            if(Val<=Obj[0].Parm[SPIN_MIN]) Val = Obj[0].Parm[SPIN_MIN];
                            *(uint16_t*)Obj[0].Parm[SPIN_VALUE] = Val;
                            Update = 1;
                            if(FirstWait || LastSpinIndex==0xff){
                                 Draw3dEdge(0,Obj[0].X,Obj[0].Y+Obj[0].H-ArrowClickHeight,Obj[0].W,ArrowClickHeight);
                                 LastSpinIndex = 1;
                            }
                            else{
                                if(LastSpinIndex!=0xff && LastSpinIndex!=1){  // Previously had   
                                    RaiseAllButtons(Id);
                                    Draw3dEdge(0,Obj[0].X,Obj[0].Y+Obj[0].H-ArrowClickHeight,Obj[0].W,ArrowClickHeight);
                                    LastSpinIndex = 1;
                                }
                            }
                        }
                        else{  // Touch down on spin control but not over a button (in the center instead)
                            RaiseAllButtons(Id);
                            LastSpinIndex = 0xff;
                        }
                        break;
			
                    default:
                        Index = SaveIndex = X/ArrowClickWidth;
                        b = 0;
                        if(Obj[0].Flags==FLAG_DEC_MULTI_ARROW || Obj[0].Flags==FLAG_HEX_MULTI_ARROW){                            
                            Amount = 0;  b = 1;
                            if(Index<Obj[0].Parm[SPIN_NUM_DIGITS]){
                                Index = Obj[0].Parm[SPIN_NUM_DIGITS]-Index-1;
                                if(Obj[0].Flags==FLAG_HEX_MULTI_ARROW){
                                    Amount = 1<<(Index<<2);
                                }
                                else{
                                     Amount = SpinDigitLut[Index];
                                }
                            }
                        }
                        else{
                            if(Index>=Obj[0].Parm[SPIN_NUM_DIGITS]) Index = SaveIndex = Obj[0].Parm[SPIN_NUM_DIGITS]-1;
                            Ptr = (char *)(&Obj[0].Text[Index]);
                        }
                        if(Y<ArrowClickHeight){
                            if(b){  // FLAG_DEC_MULTI_ARROW or FLAG_HEX_MULTI_ARROW
                                    // Check for sign flip to detec overflow
                                b = (*(uint16_t*)Obj[0].Parm[SPIN_VALUE]) & 0x8000 ? 1 : 0;
                                Val = *(uint16_t*)Obj[0].Parm[SPIN_VALUE] + Amount;
                                if(b && ((Val&0x8000)==0)) Val = Obj[0].Parm[SPIN_MAX]; 
                                if(Val>Obj[0].Parm[SPIN_MAX]) Val = Obj[0].Parm[SPIN_MAX];
                                *(uint16_t*)Obj[0].Parm[SPIN_VALUE] = Val;
                            }
                            else{
                                b = Ptr[0];
                                Ptr[0] = b+1;
                                if(Obj[0].Flags ==FLAG_ALPHA){
                                    if(Ptr[0]=='[') Ptr[0]='a';
                                    if(Ptr[0]=='{') Ptr[0] = 'A';
                                }
                                else if(Obj[0].Flags==FLAG_ALPHA_NUM){
                                    if(Ptr[0]==':') Ptr[0]='A';
                                    if(Ptr[0]=='[') Ptr[0]='a';
                                    if(Ptr[0]=='{') Ptr[0] = '0';
                                }
                                else{
                                     if(Ptr[0]>'~') Ptr[0] = ' ';
                                }
                            }
                            Update = 1;
                            if(FirstWait || LastSpinIndex==0xff){
                                X = SaveIndex*ArrowClickWidth;
                                Draw3dEdge(0,Obj[0].X+X,Obj[0].Y,ArrowClickWidth,ArrowClickHeight);
                                LastSpinIndex = SaveIndex;
                            }
                            else{
                                if(LastSpinIndex!=0xff && LastSpinIndex!=SaveIndex){    
                                    RaiseAllButtons(Id);
                                    X = SaveIndex*ArrowClickWidth;
                                    Draw3dEdge(0,Obj[0].X+X,Obj[0].Y,ArrowClickWidth,ArrowClickHeight);
                                    LastSpinIndex = SaveIndex;
                                }
                            }
                        }
                        else if(Y>Obj[0].H-ArrowClickHeight){
                            if(b){  // FLAG_DEC_MULTI_ARROW or FLAG_HEX_MULTI_ARROW
                                Val = *(uint16_t*)Obj[0].Parm[SPIN_VALUE];
                                if(Val>=Amount) Val-=Amount; 
                                if(Val<=Obj[0].Parm[SPIN_MIN]) Val = Obj[0].Parm[SPIN_MIN];
                                *(uint16_t*)Obj[0].Parm[SPIN_VALUE] = Val;
                            }
                            else{
                                b = Ptr[0];
                                Ptr[0] = b-1;
                                if(Obj[0].Flags ==FLAG_ALPHA){
                                    if(Ptr[0]=='@') Ptr[0]='z';
                                    if(Ptr[0]=='`') Ptr[0] = 'Z';
                                }
                                else if(Obj[0].Flags==FLAG_ALPHA_NUM){
                                    if(Ptr[0]=='@') Ptr[0]='9';
                                    if(Ptr[0]=='`') Ptr[0]='Z';
                                    if(Ptr[0]=='/') Ptr[0] = 'z';
                                }
                                else{
                                     if(Ptr[0]<' ') Ptr[0] = '~';
                                }
                            }
                            Update = 1;
                            if(FirstWait || LastSpinIndex==0xff){
                                X = SaveIndex*ArrowClickWidth;
                                Draw3dEdge(0,Obj[0].X+X,Obj[0].Y+Obj[0].H-ArrowClickHeight,ArrowClickWidth,ArrowClickHeight);
                                LastSpinIndex = SaveIndex + Obj[0].Parm[SPIN_NUM_DIGITS];
                            }
                            else{
                                if(LastSpinIndex!=0xff && LastSpinIndex!=SaveIndex){    
                                    RaiseAllButtons(Id);
                                     X = SaveIndex*ArrowClickWidth;
                                    Draw3dEdge(0,Obj[0].X+X,Obj[0].Y+Obj[0].H-ArrowClickHeight,ArrowClickWidth,ArrowClickHeight);
                                    LastSpinIndex = SaveIndex + Obj[0].Parm[SPIN_NUM_DIGITS];
                                }
                            }
                        }
                        else{  // Touch down on spin control but not over a button (in the center instead)
                            RaiseAllButtons(Id);
                            LastSpinIndex = 0xff;
                        }
                        break;
                }
                if(Update){ 
                    UpdateItem(Id);
                    SendMessage(Obj[0].Parm[SPIN_ID],EVENT_CHANGED,0,0);  // Id,EVENT,X,Y
                }
            }
            break;
    }
}

    // Set W to zero to skip background draw of ExtraLineSpace
static void DrawText(char s[],uint8_t FontId,uint8_t ExtraLineSpace,uint16_t X, uint16_t Y,uint16_t W
    , uint16_t RGB, uint16_t BgRGB)
{
    uint8_t b,Dx;
    uint16_t XSave;
    char c;
   
    if(s==0) return; 
    gfSetTextColor(RGB);
    gfSetTextBackgroundColor(BgRGB);
    gfSelectFont(FontId & 0x7f);
    gfSetFontZoom(FontId & 0x80 ? 2 : 1);
 
    XSave = X;
    Dx = gfGetFontWidth();
        // Deal with <CR> and Parm[TEXT_EXTRA_LINE_SPACE]
    for (b = 0; s[b]; b++){
        c = s[b];
        if (c == '\n') {
            Y += gfGetFontHeight();
            if(W) gfRectFill(XSave, Y, W,ExtraLineSpace,BgRGB);
            Y += ExtraLineSpace;
            X = XSave;
        }
        else{
            gfPutc(X,Y,c);
            X+=Dx;
        }
    }
}

static void DrawTextFillToEnd(char s[],uint8_t FontId,uint8_t ExtraLineSpace,uint16_t X, uint16_t Y,uint16_t W
    , uint16_t RGB, uint16_t BgRGB)
{
    uint8_t b,Dx;
    uint16_t XSave;
    char c;
   
    if(s==0) return; 
    gfSetTextColor(RGB);
    gfSetTextBackgroundColor(BgRGB);
    gfSelectFont(FontId & 0x7f);
    gfSetFontZoom(FontId & 0x80 ? 2 : 1);
 
    XSave = X;
    Dx = gfGetFontWidth();
        // Deal with <CR> and Parm[TEXT_EXTRA_LINE_SPACE]
    for (b = 0; s[b]; b++){
        c = s[b];
        if (c == '\n') {
            gfRectFill(X,Y,W-(X-XSave),gfGetFontHeight(),BgRGB);
            Y += gfGetFontHeight();
            if(W) gfRectFill(XSave, Y, W,ExtraLineSpace,BgRGB);
            Y += ExtraLineSpace;
            X = XSave;
        }
        else{
            gfPutc(X,Y,c);
            X+=Dx;
        }
    }
    gfRectFill(X,Y,W-(X-XSave),gfGetFontHeight(),BgRGB);
}

static void UpdateItem(uint8_t Index)
{
    uint8_t b,Loop,NumArrows,*Ptr8;
    uint16_t X,Y,W,H,XOff,X1,Y1,Fg,Bg;
    char s[50],Format[10]; 
    char *Ptr;
    const Object_t *Obj;
    
    if(Index > Screen[mCurrentScreen].NumObjects) return;
        // Don't draw between the time the screen is requested to change and INIT_SCREEN has not been handled
    if(mGuiFlags & GUI_FLAG_SCREEN_JUST_CHANGED) return;
    Obj = &Screen[mCurrentScreen].Obj[Index];
    switch(Obj[0].Type){
        case TYPE_SPIN:
            NumArrows = (Obj[0].Flags==FLAG_DEC || Obj[0].Flags == FLAG_HEX) ? 1 : Obj[0].Parm[SPIN_NUM_DIGITS];
            X = Obj[0].X;
            Y = Obj[0].Y;
            W = Obj[0].W;
            H = Obj[0].H;
            switch (Obj[0].Flags) {
                case FLAG_DEC:
                case FLAG_DEC_MULTI_ARROW:
                    sprintf1(Format, "%%0%du", Obj[0].Parm[SPIN_NUM_DIGITS]);
                    sprintf1(s, Format, *(uint16_t*)Obj[0].Parm[SPIN_VALUE]);
                    break;
                case FLAG_HEX:
                case FLAG_HEX_MULTI_ARROW:
                    sprintf1(Format, "%%0%dx", Obj[0].Parm[SPIN_NUM_DIGITS]);
                    sprintf1(s, Format, *(uint16_t*)Obj[0].Parm[SPIN_VALUE]);
                    break;
                default:
                    strcpy(s, Obj[0].Text);
                    break;
            }   
            if (NumArrows == 1) {                  
                DrawText(s, Obj[0].FontId, 0
                    ,X + Obj[0].Parm[SPIN_DIGIT_SPACE_X]+1
                    ,Y + Obj[0].Parm[SPIN_ARROW_HEIGHT]+Obj[0].Parm[SPIN_DIGIT_SPACE_Y]
                    ,0,Obj[0].RGB,Obj[0].BgRGB);                  
            }
            else {
                Format[1] = 0;  XOff = X + Obj[0].Parm[SPIN_DIGIT_SPACE_X] + 1;
                for (Loop = 0; Loop < NumArrows; Loop++) {
                    Format[0] = s[Loop];
                    DrawText(Format, Obj[0].FontId, 0
                        ,XOff
                        ,Y + Obj[0].Parm[SPIN_ARROW_HEIGHT]+Obj[0].Parm[SPIN_DIGIT_SPACE_Y]
                        ,0,Obj[0].RGB,Obj[0].BgRGB);
                    XOff += gfGetFontWidth() + 2*Obj[0].Parm[SPIN_DIGIT_SPACE_X];
                }
            }
            break;
            
        case TYPE_TEXT:
                // Note: Set W to zero to skip background fill of extra line space
            DrawText((char*)Obj[0].Text,Obj[0].FontId,Obj[0].Parm[TEXT_EXTRA_LINE_SPACE]
                    ,Obj[0].X,Obj[0].Y,Obj[0].W,Obj[0].RGB,Obj[0].BgRGB);
            break;
            
        case TYPE_CHECK:
            X  = Obj[0].X + 1;          Y = Obj[0].Y + 1;
            X1 = X + Obj[0].H - 2;     Y1 = Y + Obj[0].H - 2;
            b = *(uint16_t*)Obj[0].Parm[CHECK_VALUE];
            gfLine(X,  Y, X1, Y1, b ? Obj[0].RGB : Obj[0].BgRGB);
            gfLine(X, Y1, X1,  Y, b ? Obj[0].RGB : Obj[0].BgRGB);
            break;

        case TYPE_LIST_BOX:
                // Note: Set W to zero to skip background fill of extra line space
            Y = Obj[0].Y+2;
            W = Obj[0].W-Obj[0].Parm[LIST_BOX_ARROW_WIDTH]-3;
            Y1 = Obj[0].Parm[LIST_BOX_MAX_WIDTH]+1;
            X1 = *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS];      
            if(X1>Obj[0].Parm[LIST_BOX_SHOW_ITEMS]) X1 = Obj[0].Parm[LIST_BOX_SHOW_ITEMS];
            Ptr = (char *)Obj[0].Text;
            XOff = *(uint16_t*)Obj[0].Parm[LIST_BOX_SCROLL_OFFSET];
            Ptr += (XOff*Y1);            
            Fg=Obj[0].RGB;  Bg=Obj[0].BgRGB;
            Ptr8 = (uint8_t*)Obj[0].Parm[LIST_BOX_SELECTED];
            for(Loop=0;Loop<X1;Loop++){
                b = LbFetchSelected(Loop+XOff,Ptr8);
                DrawTextFillToEnd(Ptr,Obj[0].FontId,0,Obj[0].X+2,Y,W,b?Bg:Fg,b?Fg:Bg);
                Y+=gfGetFontHeight();
                Ptr += Y1;
            }
            for(;Loop<Obj[0].Parm[LIST_BOX_SHOW_ITEMS];Loop++){
                DrawTextFillToEnd(" ",Obj[0].FontId,0,Obj[0].X+2,Y,W,Fg,Bg);
                Y+=gfGetFontHeight();
            }
            break;

        default:
            DrawObject(Index);
            break;
    }
}

static void DrawArrowButton(uint8_t Up, uint16_t X, uint16_t Y, uint16_t ButtonWidth, uint16_t ButtonHeight, uint16_t ArrowWidth
    , uint16_t ArrowHeight, uint16_t Color)
{
    uint16_t X0, Y0, X1, Y1, X2, Y2;
    
    X0 = X + ButtonWidth / 2;	Y0 = (Up) ? Y + 4 : Y + ArrowHeight - 1;
    X1 = X0 - ArrowWidth / 2;     Y1 = (Up) ? Y + ArrowHeight - 1 : Y + 4;
    X2 = X1 + ArrowWidth;	Y2 = Y1;
    gfLine(X0, Y0, X1, Y1, Color);
    gfLine(X1, Y1, X2, Y2, Color);
    gfLine(X2, Y2, X0, Y0, Color);
    Draw3dEdge(1, X, Y, ButtonWidth, ButtonHeight);
}

static void DrawObject(uint8_t Index)
{
    uint8_t b,Loop,NumArrows,*Ptr8;
    uint16_t X,Y,W,H,XOff;
    uint16_t X0,X1,Y0,Y1,ArrowWidth,ButtonWidth,ButtonHeight;
    char s[50],Format[10],*Ptr; 
    const Object_t *Obj;
    
    if(Index > Screen[mCurrentScreen].NumObjects) return;
    Obj = &Screen[mCurrentScreen].Obj[Index];
    
    switch(Obj[0].Type){
        case TYPE_RECT:
            if (Obj[0].Parm[RECT_FILL]) {
                gfRectFill(Obj[0].X, Obj[0].Y, Obj[0].W, Obj[0].H,Obj[0].RGB);
            }
            else{
                X = Obj[0].X;
                Y = Obj[0].Y;
                W = Obj[0].W;
                H = Obj[0].H;
                for (b = 0; b < Obj[0].Parm[RECT_BORDER_W]; b++) {
                    gfRect(X+b,Y+b, W-b-b, H-b-b, Obj[0].RGB);
                }
            }
            break;

        case TYPE_TEXT:
                // Note: Set W to zero to skip background fill of extra line space
            DrawText((char*)Obj[0].Text,Obj[0].FontId,Obj[0].Parm[TEXT_EXTRA_LINE_SPACE]
                    ,Obj[0].X,Obj[0].Y,Obj[0].W,Obj[0].RGB,Obj[0].BgRGB);
            break;
            
        case TYPE_CHECK:
            gfRectFill(Obj[0].X,Obj[0].Y,Obj[0].H+3, Obj[0].H, Obj[0].BgRGB);
            gfRect(Obj[0].X+1,Obj[0].Y+1,Obj[0].H-2, Obj[0].H-2, Obj[0].RGB);
            if( *(uint16_t*)Obj[0].Parm[CHECK_VALUE]){
                X0 = Obj[0].X + 1;          Y0 = Obj[0].Y + 1;
                X1 = X0 + Obj[0].H - 2;     Y1 = Y0 + Obj[0].H - 2;
                gfLine(X0, Y0, X1, Y1, Obj[0].RGB);
                gfLine(X0, Y1, X1, Y0, Obj[0].RGB);
            }
                // Note: Set W to zero to skip background fill of extra line space
            DrawText((char*)Obj[0].Text,Obj[0].FontId,0
                    ,Obj[0].X+Obj[0].H+3,Obj[0].Y,0,Obj[0].RGB,Obj[0].BgRGB);
            break;

        case TYPE_BUTTON:
            X = Obj[0].X;
            Y = Obj[0].Y;
            W = Obj[0].W;
            H = Obj[0].H;
            gfRectFill(X+2,Y+2,W-4,H-4,Obj[0].BgRGB);
            DrawText((char*)Obj[0].Text, Obj[0].FontId, Obj[0].Parm[BUTTON_EXTRA_LINE_SPACE]
                 ,X + Obj[0].Parm[BUTTON_X_MARGIN],Y + Obj[0].Parm[BUTTON_Y_MARGIN],0
                 ,Obj[0].RGB,Obj[0].BgRGB);
            Draw3dEdge(1,X+1, Y+1, W-2, H-2);
            break;

        case TYPE_LIST_BOX:
            X = Obj[0].X;
            Y = Obj[0].Y;
            W = Obj[0].W;
            H = Obj[0].H;
            gfRectFill(X,Y,W,H,Obj[0].BgRGB);
            ButtonWidth =  Obj[0].Parm[LIST_BOX_ARROW_WIDTH];
            ButtonHeight = Obj[0].Parm[LIST_BOX_ARROW_HEIGHT];
            gfRect(X,Y,W-ButtonWidth,H,Obj[0].RGB);
            gfVLine(X+W, Y,H,Obj[0].RGB);
            X0 = Obj[0].X+Obj[0].W - ButtonWidth;
            DrawArrowButton(1, X0, Y, ButtonWidth, ButtonHeight, ButtonWidth-4, ButtonHeight-4,Obj[0].RGB);
            DrawArrowButton(0, X0, Y+H-ButtonHeight, ButtonWidth, ButtonHeight, ButtonWidth-4, ButtonHeight-4,Obj[0].RGB);
            Y+=2;
            W -= (ButtonWidth+3);
            Y1 = Obj[0].Parm[LIST_BOX_MAX_WIDTH]+1;
            X1 = *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS];      
            if(X1>Obj[0].Parm[LIST_BOX_SHOW_ITEMS]) X1 = Obj[0].Parm[LIST_BOX_SHOW_ITEMS];
            Ptr = (char *)Obj[0].Text;
            XOff = *(uint16_t*)Obj[0].Parm[LIST_BOX_SCROLL_OFFSET];
            Ptr += (XOff*Y1);            
	    Y0=Obj[0].RGB;  X0=Obj[0].BgRGB;
            Ptr8 = (uint8_t*)Obj[0].Parm[LIST_BOX_SELECTED];
            for(Loop=0;Loop<X1;Loop++){
                b = LbFetchSelected(Loop+XOff,Ptr8);
                DrawTextFillToEnd(Ptr,Obj[0].FontId,0,Obj[0].X+2,Y,W,b?X0:Y0,b?Y0:X0);
                Y+=gfGetFontHeight();
                Ptr += Y1;
            }      
            break;

        case TYPE_SPIN:
            NumArrows = (Obj[0].Flags==FLAG_DEC || Obj[0].Flags == FLAG_HEX) ? 1 : Obj[0].Parm[SPIN_NUM_DIGITS];
            X = Obj[0].X;
            Y = Obj[0].Y;
            W = Obj[0].W;
            H = Obj[0].H;
            gfRectFill(X+1, Y+1, W-2, H-2, Obj[0].BgRGB);
            switch (Obj[0].Flags) {
                case FLAG_DEC:
                case FLAG_DEC_MULTI_ARROW:
                    sprintf1(Format, "%%0%dd", Obj[0].Parm[SPIN_NUM_DIGITS]);
                    sprintf1(s, Format, *(uint16_t*)Obj[0].Parm[SPIN_VALUE]);
                    break;
                case FLAG_HEX:
                case FLAG_HEX_MULTI_ARROW:
                    sprintf1(Format, "%%0%dx", Obj[0].Parm[SPIN_NUM_DIGITS]);
                    sprintf1(s, Format, *(uint16_t*)Obj[0].Parm[SPIN_VALUE]);
                    break;
                default:
                    strcpy(s, Obj[0].Text);
                    break;
            }   
            if (NumArrows == 1) {                  
                DrawText(s, Obj[0].FontId, 0
                    ,X + Obj[0].Parm[SPIN_DIGIT_SPACE_X]+1
                    ,Y + Obj[0].Parm[SPIN_ARROW_HEIGHT]+Obj[0].Parm[SPIN_DIGIT_SPACE_Y]
                    ,0,Obj[0].RGB,Obj[0].BgRGB);                  
            }
            else {
                Format[1] = 0;  XOff = X + Obj[0].Parm[SPIN_DIGIT_SPACE_X] + 1;
                for (Loop = 0; Loop < NumArrows; Loop++) {
                    Format[0] = s[Loop];
                    DrawText(Format, Obj[0].FontId, 0
                        ,XOff
                        ,Y + Obj[0].Parm[SPIN_ARROW_HEIGHT]+Obj[0].Parm[SPIN_DIGIT_SPACE_Y]
                        ,0,Obj[0].RGB,Obj[0].BgRGB);
                    XOff += gfGetFontWidth() + 2*Obj[0].Parm[SPIN_DIGIT_SPACE_X];
                }
            }

            ArrowWidth = (NumArrows > 1) ? gfGetFontWidth() : Obj[0].Parm[SPIN_ARROW_HEIGHT];
            if (ArrowWidth > W - 4) ArrowWidth = W - 4;
            XOff = (NumArrows > 1) ? X + Obj[0].Parm[SPIN_DIGIT_SPACE_X] : X + (W - ArrowWidth) / 2;
            ButtonWidth = (NumArrows > 1) ? gfGetFontWidth() + 2 * Obj[0].Parm[SPIN_DIGIT_SPACE_X] : W;
            X0 = X;
            Y0 = Y + Obj[0].Parm[SPIN_ARROW_HEIGHT];
            Y1 = H - Obj[0].Parm[SPIN_ARROW_HEIGHT] - Obj[0].Parm[SPIN_ARROW_HEIGHT]; // Vertical Line Height
            gfVLine(X0, Y0, Y1, Obj[0].RGB);
            gfVLine(X0 + W - 1, Y0, Y1, Obj[0].RGB);
            for (Loop = 0; Loop < NumArrows; Loop++) {
                DrawArrowButton(1, X0, Y, ButtonWidth, Obj[0].Parm[SPIN_ARROW_HEIGHT], ArrowWidth, Obj[0].Parm[SPIN_ARROW_HEIGHT] - 3,Obj[0].RGB);
                DrawArrowButton(0, X0, Y + H - Obj[0].Parm[SPIN_ARROW_HEIGHT], ButtonWidth
                    , Obj[0].Parm[SPIN_ARROW_HEIGHT], ArrowWidth, Obj[0].Parm[SPIN_ARROW_HEIGHT] - 3, Obj[0].RGB);
                X0 += gfGetFontWidth() + (Obj[0].Parm[SPIN_DIGIT_SPACE_X]<<1);
                if (Loop < NumArrows - 1) gfVLine(X0 - 1, Y0, Y1, Obj[0].RGB);
            } 
            break;

	case TYPE_DRAW:
            gfRectFill(Obj[0].X, Obj[0].Y, Obj[0].W, Obj[0].H,Obj[0].BgRGB);
            break;	
    }
}

void GuiDraw(uint8_t ScreenId)
{
    mCurrentScreen = ScreenId;
    SendMessage(ID_INIT_SCREEN,ScreenId,0,0);
    mGuiFlags |= GUI_FLAG_SCREEN_JUST_CHANGED;
        // Will now wait for the INIT_SCREEN message to be removed from the event queue before drawing the screen
}

void GuiWaitForMessage(void)
{
    uint8_t Id,Index,NumObjects,Found,Done;
    uint16_t X,Y;
#ifdef RASP_PI_PICO
    TfTouch_t Touch;
#else    
    gfTouch_t Touch;
#endif
    union{
        struct{  // Through trial and error
            uint8_t Low;  
            uint8_t High;
        } Parts;
        uint16_t All;
    } Pieces;
    
        // look to see if INIT_SCREEN message has been read then draw screen
    if(mGuiFlags & GUI_FLAG_SCREEN_JUST_CHANGED){ 
        Found = 0;
        for(Index = EqInfo.Rd,Id=0;Id<EqInfo.Size;Id++){
            if(EventQueue[Index].Id==ID_INIT_SCREEN) Found=1;
            Index = (Index==EQ_SIZE) ? 0 : Index+1;
        }
        if(!Found){ // the ID_INIT_SCREEN message has been consumed
            Done = 0;
            while(!Done){  // Wait for touch to be released
#ifdef RASP_PI_PICO
                Touch = TfFetchTouch();
#else
                Touch = gfFetchTouch();
#endif
                if(Touch.Down==0) Done = 1;
            }
    
	    mGuiFlags &= ~GUI_FLAG_SCREEN_JUST_CHANGED;
            NumObjects = Screen[mCurrentScreen].NumObjects;
            gfRectFill(0,0,DISP_WIDTH,DISP_HEIGHT,Screen[mCurrentScreen].BgColor);
            for(Index=0;Index<NumObjects;Index++){
                DrawObject(Index);  
            }
        }
    }
    
        // Only way out is if there is a message in the event queue
    while(EqInfo.Size==0){
       
        for(Index=0;Index<GUI_NUM_TIMERS;Index++){
            if(TimerFlags & (1<<Index)){
                if(TimemsExceeded(Timer[Index].Start, Timer[Index].Period)){
                    Timer[Index].Start = FetchTimerms();
                    SendMessage(ID_TIMER0+Index,0,0,0);
                }
            }
        }
#ifdef RASP_PI_PICO
        Touch = TfFetchTouch();
        X = Touch.X;
        Y = Touch.Y;
        TouchState &= ~TF_TOUCH_JUST_DOWN;
        if(Touch.Down){
            if(TouchState & TF_TOUCH_IS_DOWN){
                if(X!=TouchXLast || Y!=TouchYLast){
                    SendMessage(ID_TOUCH,EVENT_MOVED,X,Y);  // Id,EVENT,X,Y
                    TouchXLast = X;  TouchYLast = Y;
                }
            }
            else{
               SendMessage(ID_TOUCH,EVENT_DOWN,X,Y);  // Id,EVENT,X,Y
               TouchState = TF_TOUCH_JUST_DOWN | TF_TOUCH_IS_DOWN;
               TouchXLast = X;  TouchYLast = Y;
            }
            GuiManageObject(X,Y);
        }
        else{  // Touch is up.
            if(TouchState & TF_TOUCH_IS_DOWN){
                SendMessage(ID_TOUCH,EVENT_UP,0,0);  // Id,EVENT,X,Y
                TouchState = TF_TOUCH_JUST_UP;
                GuiManageObject(TouchXLast,TouchYLast);
            }
            else{
                TouchState = 0;
            }
        }        
#else	
               // Added digital filter inside these routines to clean up the noise on Y
        Touch = gfFetchTouch();
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
        
        TouchState &= ~TF_TOUCH_JUST_DOWN;
        if(Touch.Down && X>=10 && Y>=10){
            
                // Fixed point multiply X.7 format for TouchMultX=(319/TouchDivX)*128
            Pieces.All = X * TouchMultX;            
            X = Pieces.Parts.High<<1; //X = Result>>7;
            X += (Pieces.Parts.Low & 0x80) ? 1 : 0;
	    X-= TouchXb;
            Pieces.All = Y * TouchMultY;           
            Y = Pieces.Parts.High<<1; //Y = Result>>7;
            Y += (Pieces.Parts.Low & 0x80) ? 1 : 0;
	    Y -= TouchYb;
            
            if(TouchState & TF_TOUCH_IS_DOWN){
                if(X!=TouchXLast || Y!=TouchYLast){
                    SendMessage(ID_TOUCH,EVENT_MOVED,X,Y);  // Id,EVENT,X,Y
                    TouchXLast = X;  TouchYLast = Y;
                }
            }
            else{
               SendMessage(ID_TOUCH,EVENT_DOWN,X,Y);  // Id,EVENT,X,Y
               TouchState = TF_TOUCH_JUST_DOWN | TF_TOUCH_IS_DOWN;
               TouchXLast = X;  TouchYLast = Y;
            }

            GuiManageObject(X,Y);
        }
        else{  // Touch is up.
            if(TouchState & TF_TOUCH_IS_DOWN){
                SendMessage(ID_TOUCH,EVENT_UP,0,0);  // Id,EVENT,X,Y
                TouchState = TF_TOUCH_JUST_UP;
                GuiManageObject(TouchXLast,TouchYLast);
            }
            else{
                TouchState = 0;
            }
        }
#endif
    }
}

GuiRect_t GuiFetchRect(uint8_t ScreenId,uint8_t ObjectId)
{
    uint8_t Fail = 0;
    Object_t *Obj;
    GuiRect_t Result;
   
    if(ScreenId>=NUM_SCREENS) Fail=1;
    ObjectId-=ID_OFFSET;
    if(ObjectId>=Screen[ScreenId].NumObjects) Fail=1;
    if(Fail){
        Result.X = 0;
        Result.Y = 0;
        Result.W = 0;
        Result.H = 0;
	return(Result);
    }
    Obj = &Screen[ScreenId].Obj[ObjectId];
    Result.X = Obj[0].X;
    Result.Y = Obj[0].Y;
    Result.W = Obj[0].W;
    Result.H = Obj[0].H;
    return(Result);
}

#ifdef RASP_PI_PICO

void GuiCalibrateTouch(void)
{
    TfCalibrate();
}

void GuiEnableTouchHyst(void)
{
    TfEnableHyst();
}

void GuiDisableTouchHyst(void)
{
    TfDisableHyst();
}

#else

static void LoadTouchCalValues(void)
{

#if defined(DSPIC_DEV) | defined(RASP_PI_PICO)
    uint32_t Value;

    Value = VeeRead(GUI_EESTART+0);
    TouchMultX = (Value==0xffffffff) ? 200 : (Value>>16) & 0xffff;
    TouchXb    = (Value==0xffffffff) ?  20 : Value & 0xffff;

    Value = VeeRead(GUI_EESTART+1);
    TouchMultY = (Value==0xffffffff) ? 152 : (Value>>16) & 0xffff;
    TouchYb    = (Value==0xffffffff) ?  18 : Value & 0xffff;
#else
    unsigned int Value;

    Value = (EERead(GUI_EESTART+0)<<8) | EERead(GUI_EESTART+1);
    TouchMultX = (Value==0xffff) ? 200 : Value;
    Value = (EERead(GUI_EESTART+2)<<8) | EERead(GUI_EESTART+3);
    TouchXb = (Value==0xffff) ? 20 : Value;
    
    Value = (EERead(GUI_EESTART+4)<<8) | EERead(GUI_EESTART+5);
    TouchMultY = (Value==0xffff) ? 152 : Value;
    Value = (EERead(GUI_EESTART+6)<<8) | EERead(GUI_EESTART+7);
    TouchYb = (Value==0xffff) ? 18 : Value;
#endif
}

void GuiCalibrateTouch(void)
{
    uint8_t Index;
    uint16_t X,Y,X20,Y20,X300,Y220;
    uint8_t Done = 0;
    gfTouch_t Touch;
   
    gfSetTextColor(0xffff);
    gfSetTextBackgroundColor(0x0000);
    gfSelectFont(1);
    gfSetFontZoom(1);
    gfRectFill(0,0,DISP_WIDTH,DISP_HEIGHT,0x0000);
    gfPuts(80,100,"Touch and Hold");
    gfPuts(50,10,"Here");
    gfHLine(0, 20, 40, 0xffff);  
    gfVLine(20, 0, 40, 0xffff);  

    while(!Done){  // Wait for touch to be released
        Touch = gfFetchTouch();
        if(Touch.Down==0) Done = 1;
    }
    Done = 0;

    while(!Done){
        Touch = gfFetchTouch();
        X = Touch.X;
        Y = Touch.Y;
        if(Touch.Down && X>20 && Y>20){
            X20 = 0;  Y20 = 0;
            for(Index=0;Index<16;Index++){
        	Touch = gfFetchTouch();
                X20 += Touch.X;
                Y20 += Touch.Y;
            }
            X20 = X20>>4;
            Y20 = Y20>>4;
            if(X20<60 && Y20<60) Done = 1;
            else{
                gfRectFill(0,0,DISP_WIDTH,DISP_HEIGHT,0x0000);
                gfPuts(80,100,"Try again");
                Waitms(1200);
                return;
            }
        }
    }
    gfHLine(0, 20, 40, 0x0000);  
    gfVLine(20, 0, 40, 0x0000);
    gfSetTextColor(0x0000);
    gfPuts(50,10,"Here");
    gfSetTextColor(0xffff);
    gfPuts(240,200,"Here");
    gfHLine(DISP_WIDTH-40, DISP_HEIGHT-20, 40, 0xffff);  
    gfVLine(DISP_WIDTH-20, DISP_HEIGHT-40, 40, 0xffff);  
 
    Done=0;
    while(!Done){
        Touch = gfFetchTouch();
        X = Touch.X;
        Y = Touch.Y;
        if(Touch.Down && X>128 && Y>128){
            X300=0;  Y220=0;
            for(Index=0;Index<16;Index++){
        	Touch = gfFetchTouch();
                X300 += Touch.X;
                Y220 += Touch.Y;
            }
            X300 = X300>>4;
            Y220 = Y220>>4;
            if(X300>180 && Y220>180) Done = 1;
            else{
                gfRectFill(0,0,DISP_WIDTH,DISP_HEIGHT,0x0000);
                gfPuts(80,100,"Try again");
                Waitms(1200);
                return;
            }
            Done = 1;
        }
    }
    TouchMultX = ((300-20)<<7)/(X300-X20);
    TouchXb = ((TouchMultX*X20-(20<<7))+0x40)>>7;
    TouchMultY = ((220-20)<<7)/(Y220-Y20);
    TouchYb = ((TouchMultY*Y20-(20<<7))+0x40)>>7;

#if defined(DSPIC_DEV) | defined(RASP_PI_PICO)
    VeeWrite(GUI_EESTART+0,((uint32_t)TouchMultX<<16)|TouchXb);
    VeeWrite(GUI_EESTART+1,((uint32_t)TouchMultY<<16)|TouchYb);
#else
    EEWrite(GUI_EESTART+0,TouchMultX>>8); EEWrite(GUI_EESTART+1,TouchMultX&0xff);
    EEWrite(GUI_EESTART+2,TouchXb>>8);    EEWrite(GUI_EESTART+3,TouchXb&0xff);
    EEWrite(GUI_EESTART+4,TouchMultY>>8); EEWrite(GUI_EESTART+5,TouchMultY&0xff);
    EEWrite(GUI_EESTART+6,TouchYb>>8);    EEWrite(GUI_EESTART+7,TouchYb&0xff);
#endif


    gfSetTextColor(0x0000);
    gfPuts(240,200,"Here");
    gfPuts(80,100,"Touch and Hold");
    gfHLine(DISP_WIDTH-40, DISP_HEIGHT-20, 40, 0x0000);  
    gfVLine(DISP_WIDTH-20, DISP_HEIGHT-40, 40, 0x0000);  
    gfSetTextColor(0xffff);
    gfPuts(5,150,"All Done.  Release");

    Done=0;
    while(!Done){
        Touch = gfFetchTouch();
        if(Touch.Down==0) Done = 1;
    }
}

void GuiEnableTouchHyst(void)
{
    TouchDir |= EN_HYST;
}

void GuiDisableTouchHyst(void)
{
    TouchDir &= ~EN_HYST;
}
#endif

uint16_t GuiLbGetNum(uint8_t ScreenId, uint16_t Id)
{
    const Object_t *Obj;

    Id-=ID_OFFSET;    
    Obj = &Screen[ScreenId].Obj[Id];
    if(Obj[0].Type==TYPE_LIST_BOX){
        return(*(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS]);
    }
    return(0);
}

uint8_t GuiLbGetSelected(uint8_t ScreenId, uint16_t Id,uint16_t Index)
{
    const Object_t *Obj;
    uint16_t NumItems;
    uint8_t *Ptr8;

    Id-=ID_OFFSET;    
    Obj = &Screen[ScreenId].Obj[Id];
    if(Obj[0].Type==TYPE_LIST_BOX){
        NumItems = *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS];
        if(Index>=NumItems) return(0);
        Ptr8 = (uint8_t*)Obj[0].Parm[LIST_BOX_SELECTED];
        return(LbFetchSelected(Index,Ptr8));   
    }
    return(0);
}

void GuiLbSetSelected(uint8_t ScreenId, uint16_t Id,uint16_t Index,uint8_t Value)
{
    const Object_t *Obj;
    uint16_t NumItems;
    uint8_t *Ptr8;

    Id-=ID_OFFSET;    
    Obj = &Screen[ScreenId].Obj[Id];
    if(Obj[0].Type==TYPE_LIST_BOX){
        NumItems = *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS];
        if(Index>=NumItems) return;
        Ptr8 = (uint8_t*)Obj[0].Parm[LIST_BOX_SELECTED];
        LbSetSelected(Value,Index,Ptr8);
        if(ScreenId==mCurrentScreen) UpdateItem(Id);
    }
    return;
}

void GuiLbSetAllSelected(uint8_t ScreenId, uint16_t Id,uint8_t Value)
{
    const Object_t *Obj;
    uint16_t NumItems,Index;
    uint8_t *Ptr8;

    Id-=ID_OFFSET;    
    Obj = &Screen[ScreenId].Obj[Id];
    if(Obj[0].Type==TYPE_LIST_BOX){
        NumItems = *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS];
        Ptr8 = (uint8_t*)Obj[0].Parm[LIST_BOX_SELECTED];
        for(Index=0;Index<NumItems;Index++) LbSetSelected(Value,Index,Ptr8);
        if(NumItems && ScreenId==mCurrentScreen) UpdateItem(Id);
    }
    return;
}

void GuiLbAddToEnd(uint8_t ScreenId, uint16_t Id,char *String)
{
    const Object_t *Obj;
    uint16_t NumItems,MaxWidth;
    char *Ptr; 
    uint8_t *Ptr8;

    Id-=ID_OFFSET;    
    Obj = &Screen[ScreenId].Obj[Id];
    if(Obj[0].Type==TYPE_LIST_BOX){
        NumItems = *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS];
        if(NumItems>=Obj[0].Parm[LIST_BOX_MAX_ITEMS]) return;
        Ptr = (char *)Obj[0].Parm[LIST_BOX_TEXT_WR_PTR];
        MaxWidth = Obj[0].Parm[LIST_BOX_MAX_WIDTH];
        Ptr += NumItems*(MaxWidth+1);
        strncpy(Ptr,String,MaxWidth); 
        Ptr[MaxWidth]=0;  // Should not be needed 
        Ptr8 = (uint8_t*)Obj[0].Parm[LIST_BOX_SELECTED];
        LbSetSelected(0,NumItems,Ptr8);
        *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS] = NumItems+1;
        if(ScreenId==mCurrentScreen) UpdateItem(Id);
    }                       
}

void GuiLbInsertItem(uint8_t ScreenId, uint16_t Id,uint16_t Index,char *String)
{
    const Object_t *Obj;
    uint16_t NumItems,MaxWidth,Loop;
    uint8_t *Ptr8;
    char *SrcPtr,*DstPtr,*SavePtr;

    Id-=ID_OFFSET;    
    Obj = &Screen[ScreenId].Obj[Id];
    if(Obj[0].Type==TYPE_LIST_BOX){
        NumItems = *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS];
        if((NumItems+1)>=Obj[0].Parm[LIST_BOX_MAX_ITEMS]) return;  // No space
        SrcPtr = SavePtr = (char *)Obj[0].Parm[LIST_BOX_TEXT_WR_PTR];
        if(Index>NumItems) Index=NumItems;  // Just add to end
        MaxWidth = Obj[0].Parm[LIST_BOX_MAX_WIDTH];
        Ptr8 = (uint8_t*)Obj[0].Parm[LIST_BOX_SELECTED];
            // Make space for new item
        if(NumItems){
            SrcPtr += (NumItems-1)*(MaxWidth+1);
            DstPtr = SrcPtr + MaxWidth+1;  // New item after last
            for(Loop=NumItems;Loop>Index;Loop--){
                strcpy(DstPtr,SrcPtr);  // Length already truncated if needed
                DstPtr -= (MaxWidth+1);
                SrcPtr -= (MaxWidth+1);
                LbSetSelected(LbFetchSelected(Loop-1,Ptr8),Loop,Ptr8);
            }
        }
            // Add item into space created 
        DstPtr = SavePtr + Index*(MaxWidth+1); 
        strncpy(DstPtr,String,MaxWidth); 
        DstPtr[MaxWidth]=0;  // Should not be needed 
        *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS] = NumItems+1;
        LbSetSelected(0,Index,Ptr8);
        if(ScreenId==mCurrentScreen) UpdateItem(Id);
    }
    return;
}

void GuiLbRemoveItem(uint8_t ScreenId, uint16_t Id,uint16_t Index)
{
    const Object_t *Obj;
    uint16_t NumItems,MaxWidth,Loop,SbOffset;
    uint8_t *Ptr8;
    char *SrcPtr,*DstPtr;
     
    Id-=ID_OFFSET;    
    Obj = &Screen[ScreenId].Obj[Id];
    if(Obj[0].Type==TYPE_LIST_BOX){
        DstPtr = (char *)Obj[0].Parm[LIST_BOX_TEXT_WR_PTR];
        NumItems = *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS];
        if(Index>=NumItems) return;
        MaxWidth = Obj[0].Parm[LIST_BOX_MAX_WIDTH];
        DstPtr += Index*(MaxWidth+1);
        SrcPtr = DstPtr + MaxWidth + 1;  // Last Item
        Ptr8 = (uint8_t*)Obj[0].Parm[LIST_BOX_SELECTED];
        for(Loop=Index;Loop<NumItems-1;Loop++){
            strcpy(DstPtr,SrcPtr);  // Length already truncated if needed
            DstPtr += (MaxWidth+1);
            SrcPtr += (MaxWidth+1);
            LbSetSelected(LbFetchSelected(Loop+1,Ptr8),Loop,Ptr8);
        }
        NumItems--;
        *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS] = NumItems;
        SbOffset = *(uint16_t*)Obj[0].Parm[LIST_BOX_SCROLL_OFFSET];
        if(SbOffset){
            if(SbOffset+Obj[0].Parm[LIST_BOX_SHOW_ITEMS]>NumItems){
                *(uint16_t*)Obj[0].Parm[LIST_BOX_SCROLL_OFFSET] = SbOffset-1;
            }
        }
	if(ScreenId==mCurrentScreen) UpdateItem(Id);
    }
    return;
}

void GuiLbRemoveAllItems(uint8_t ScreenId, uint16_t Id)
{
    const Object_t *Obj;
    uint16_t Loop;
    uint8_t *Ptr8;

    Id-=ID_OFFSET;    
    Obj = &Screen[ScreenId].Obj[Id];
    if(Obj[0].Type==TYPE_LIST_BOX){
        *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS] = 0;
        Ptr8 = (uint8_t*)Obj[0].Parm[LIST_BOX_SELECTED];
        for(Loop=0;Loop<Obj[0].Parm[LIST_BOX_MAX_ITEMS];Loop++){
            LbSetSelected(0,Loop,Ptr8);
        }
        if(ScreenId==mCurrentScreen) UpdateItem(Id);
    }
    return;
}
                        
void GuiLbReplaceItem(uint8_t ScreenId, uint16_t Id,uint16_t Index,char *String)
{
    const Object_t *Obj;
    uint16_t MaxWidth;
    char *Ptr;
    
    Id-=ID_OFFSET;    
    Obj = &Screen[ScreenId].Obj[Id];
    if(Obj[0].Type==TYPE_LIST_BOX){
        if(Index >= *(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS]) return;
        Ptr = (char *)Obj[0].Parm[LIST_BOX_TEXT_WR_PTR];
        MaxWidth = Obj[0].Parm[LIST_BOX_MAX_WIDTH]; 
        Ptr += Index*(MaxWidth+1); 
        strncpy(Ptr,String,MaxWidth); 
        Ptr[MaxWidth]=0;  // Should not be needed 
        if(ScreenId==mCurrentScreen) UpdateItem(Id);
    }                       
}

void GuiLbGetItem(uint8_t ScreenId, uint16_t Id,uint16_t Index,char *String)
{
    const Object_t *Obj;
    uint16_t MaxWidth;
    char *Ptr;

    Id-=ID_OFFSET;    
    Obj = &Screen[ScreenId].Obj[Id];
    String[0] = 0;
    if(Obj[0].Type==TYPE_LIST_BOX){
        if(Index>=*(uint16_t*)Obj[0].Parm[LIST_BOX_NUM_ITEMS]) return;
        Ptr = (char *)Obj[0].Parm[LIST_BOX_TEXT_WR_PTR];
        MaxWidth = Obj[0].Parm[LIST_BOX_MAX_WIDTH];                   
        Ptr += Index*(MaxWidth+1); 
        strcpy(String,Ptr); 
    }                       
}
