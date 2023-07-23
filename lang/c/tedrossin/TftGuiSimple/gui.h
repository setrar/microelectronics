//Generated using CreateLcdGui (V0.05) by Ted Rossin

#define SCREEN_Main 0

#define GUI_TIMER0  0
#define GUI_TIMER1  1
#define GUI_TIMER2  2
#define GUI_TIMER3  3
#define GUI_TIMER4  4
#define GUI_NUM_TIMERS 5

#define EVENT_UP      0
#define EVENT_DOWN    1
#define EVENT_MOVED   2
#define EVENT_PUSHED  3
#define EVENT_CHANGED 4

#define ID_EMPTY 0
#define ID_TOUCH 1
#define ID_INIT_SCREEN 2
#define ID_TIMER0 3
#define ID_TIMER1 4
#define ID_TIMER2 5
#define ID_TIMER3 6
#define ID_TIMER4 7
    // Screen: Main
#define ID_BUTTON_UP 8
#define ID_BUTTON_DOWN 9
#define ID_TEXT_VALUE 10
#define ID_SPIN_VALUE 11
#define ID_TEXT_TIMER 12
#define ID_TEXT_X1 13

typedef struct{
    uint16_t X, Y, W, H;
} GuiRect_t;

typedef struct {
    uint8_t Id;
    uint8_t Event;
    uint16_t X, Y;
}GuiMessage_t;

void GuiInit(void);
uint16_t GuiGetValue(uint16_t Id);
void GuiGetString(uint16_t Id, char* String);
void GuiSetValue(uint16_t Id, uint16_t Value);
void GuiSetString(uint16_t Id, char* String);
GuiMessage_t GuiReadMessage(void);
void GuiStartTimer(uint8_t TimerId, uint16_t Periodms);
void GuiStopTimer(uint8_t TimerId);
void GuiDraw(uint8_t ScreenId);
void GuiWaitForMessage(void);
GuiRect_t GuiFetchRect(uint8_t ScreenId,uint8_t ObjectId);
void GuiCalibrateTouch(void);
void GuiEnableTouchHyst(void);
void GuiDisableTouchHyst(void);

void GuiLbAddToEnd(uint8_t ScreenId, uint16_t Id,char *String);
uint16_t GuiLbGetNum(uint8_t ScreenId, uint16_t Id);
uint8_t GuiLbGetSelected(uint8_t ScreenId, uint16_t Id, uint16_t Index);
void GuiLbSetSelected(uint8_t ScreenId, uint16_t Id, uint16_t Index, uint8_t Value);
void GuiLbSetAllSelected(uint8_t ScreenId, uint16_t Id, uint8_t Value);
void GuiLbInsertItem(uint8_t ScreenId, uint16_t Id, uint16_t Index, char* String);
void GuiLbRemoveItem(uint8_t ScreenId, uint16_t Id, uint16_t Index);
void GuiLbRemoveAllItems(uint8_t ScreenId, uint16_t Id);
void GuiLbReplaceItem(uint8_t ScreenId, uint16_t Id, uint16_t Index, char* String);
void GuiLbGetItem(uint8_t ScreenId, uint16_t Id,uint16_t Index,char *String);
