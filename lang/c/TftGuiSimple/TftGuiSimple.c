/*
   TftGuiSimple.c:  Get that GUI generating code working
 
	Ted Rossin:	 6-07-2022
				 6-18-2022 
  
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "Tft320x240.h"
#include "gui.h"

#define NO_CHANGE_NEEDED    0xff

void main()
{
    GuiMessage_t Msg;
    uint16_t Value,Timer;
    uint8_t ChangeScreenId,ScreenId;
    char s[10];
       
    GuiInit();
                       
    ChangeScreenId = NO_CHANGE_NEEDED;
    ScreenId = SCREEN_Main;
    GuiDraw(ScreenId); 
    
    Value = 10000;  Timer = 0;
    while(1){
        GuiWaitForMessage();
        do{
            Msg = GuiReadMessage();
            switch(ScreenId){
                case SCREEN_Main:
                    switch(Msg.Id){
                        case ID_INIT_SCREEN:  // Set new initial values just before new screen is drawn
                            sprintf(s,"%05u",Value);                           
                            GuiSetString(ID_TEXT_VALUE,s); 
                            
                            GuiSetValue(ID_SPIN_VALUE,Value);
                            GuiStartTimer(GUI_TIMER0,100); 
                            break;
                        case ID_BUTTON_UP:
                            Value++;
                            sprintf(s,"%05u",Value);
                            GuiSetString(ID_TEXT_VALUE,s);
                            GuiSetValue(ID_SPIN_VALUE,Value);
                            break;
                        case ID_BUTTON_DOWN:
                            Value--;  
                            sprintf(s,"%05u",Value);
                            GuiSetString(ID_TEXT_VALUE,s);
                            GuiSetValue(ID_SPIN_VALUE,Value);                 
                            break;
                        case ID_SPIN_VALUE:
                            Value = GuiGetValue(ID_SPIN_VALUE);
                            sprintf(s,"%05u",Value);
                            GuiSetString(ID_TEXT_VALUE,s);
                            break;
                        case ID_TIMER0:
                            sprintf(s,"%03d",Timer++);
                            if(Timer>999) Timer = 0;
                            GuiSetString(ID_TEXT_TIMER,s);
                            break;
                    }
                    break;
            }
        }while(Msg.Id != ID_EMPTY);
        
            // See if the screen should be changed.
        if(ChangeScreenId!=NO_CHANGE_NEEDED){
            ScreenId = ChangeScreenId;
            ChangeScreenId = NO_CHANGE_NEEDED;           
            GuiDraw(ScreenId);
        }
    }   
}