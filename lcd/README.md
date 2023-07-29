# LCD (Liquid Crystal Display)

### :a: Wiring

|  Func             |  PICO PORT :hash:  | Comments                         | ILI9486 PORT :hash: | Wiring Colors |
|-------------------|-----|---------------------------------------------------|----|-|
| #define TFT_MISO  | 16  |                                                   | 21 | ![#ffff00](https://placehold.co/15x15/ffff00/ffff00.png) `Yellow` |
| #define TFT_CS    | 17  | // Chip select control pin                        | 24 | ![#ffa500](https://placehold.co/15x15/ffa500/ffa500.png) `Orange` |
| #define TFT_SCLK  | 18  |                                                   | 23 | ![#ffffff](https://placehold.co/15x15/ffffff/ffffff.png) `White`  |
| #define TFT_MOSI  | 19  | // Do not connect to SDO(MISO), only to T_DO!!!   | 19 | ![#008000](https://placehold.co/15x15/008000/008000.png) `Green`  |
| #define TFT_DC    | 20  | // Data Command control pin                       | 18 | ![#0000ff](https://placehold.co/15x15/0000ff/0000ff.png) `Blue`   |
| #define TFT_RST   | 21  | // Reset pin (could connect to Arduino RESET pin) | 22 | ![#808080](https://placehold.co/15x15/808080/808080.png) `Grey`   |
| | | |
| #define TOUCH_CS  | 22  |                                                   | 26 | ![#964b00](https://placehold.co/15x15/964b00/964b00.png) `Brown`  |

- [ ] [Kuman 3.5" Inch 480x320 RGB TFT LCD Pixels Touch Screen with Touch Pen for Raspberry Pi 3 2 Model B B+ A+ A Module SPI Interface SC06](http://www.kumantech.com/kuman-35-inch-tft-lcd-display-480x320-rgb-pixels-touch-screen-monitor-for-raspberry-pi-3-2-model-b-b-a-a-module-spi-interface-with-touch-pen-sc06_p0014.html)


| PIN No. | Symbol | Description                                                             |
|:--------|:-------|-------------------------------------------------------------------------|
| 1       | 3v     | Power Positive (3V power input)                                         |
| 2,4     | 5v     | Power Positive (3V power input)                                         |
| 3,5-18  | NC     | NC                                                                      |
| 19      | MOSI   | SPI Bus Master Output/Slave Input                                       |
| 20, 25  | GND    | Ground                                                                  | 
| 21      | MISO   | SPI Bus Master Input/Slave Output                                       |
| 22      | TP_IRQ | Touch Panel interrupt, Low Level while the touch Panel detects touching |
| 23      | SLCK   | SPI clock of LCD/Touch Panel                                            |
| 24      | TP_CS  | touch Panel chip selection, Low active                                  |
| 26      | LCD_CS | LCD chip selection, low active                                          |

<img src=https://ueeshop.ly200-cdn.com/u_file/UPAB/UPAB620/1704/products/25/436066c712.jpg width=50% height=50% > </img>


### :b: Coding



- [ ] Edit file  `~/Arduino/libraries/TFT_eSPI/User_Setup_Select.h`

* Uncomment the below code as follows:

```diff
- Red being the original code
+ Green the desired code
```

```
diff TFT_eSPI/User_Setup_Select.h ~/Developer/TFT_eSPI-updated/User_Setup_Select.h
```
> Response:
```diff 
30c30
< #include <User_Setup.h>           // Default setup is root library folder
---
> //#include <User_Setup.h>           // Default setup is root library folder
41c41
< //#include <User_Setups/Setup10_RPi_touch_ILI9486.h> // Setup file for ESP8266 configured for ESP8266 and RPi TFT with touch
---
> #include <User_Setups/Setup10_RPi_touch_ILI9486.h> // Setup file for ESP8266 configured for ESP8266 and RPi TFT with touch
```

- [ ] Edit file  `~/Arduino/libraries/TFT_eSPI/User_Setups/Setup10_RPi_touch_ILI9486.h`

* Add the below pin section for the RPI Pico as follows:

* Uncomment the below code as follows:

```diff
- Red being the original code
+ Green the desired code
```

```
diff TFT_eSPI/User_Setups/Setup10_RPi_touch_ILI9486.h ~/Developer/TFT_eSPI-updated/User_Setups/Setup10_RPi_touch_ILI9486.h 
```
> Response:
```diff
9,11c9,11
< #define TFT_CS   PIN_D2  // Chip select control pin D2
< #define TFT_DC   PIN_D3  // Data Command control pin
< #define TFT_RST  PIN_D4  // Reset pin (could connect to NodeMCU RST, see next line)
---
> //#define TFT_CS   PIN_D2  // Chip select control pin D2
> //#define TFT_DC   PIN_D3  // Data Command control pin
> //#define TFT_RST  PIN_D4  // Reset pin (could connect to NodeMCU RST, see next line)
14c14,23
< #define TOUCH_CS PIN_D1     // Chip select pin (T_CS) of touch screen
---
> #define TOUCH_CS  22  // Chip select pin (T_CS) of touch screen
> 
> #define TFT_MOSI  19  // Do not connect to SDO(MISO), only to T_DO!!!
> #define TFT_MISO  16
> #define TFT_SCLK  18
> #define TFT_CS    17  // Chip select control pin
> #define TFT_DC    20  // Data Command control pin
> #define TFT_RST   21  // Reset pin (could connect to Arduino RESET pin)
```

- [ ] Test with the `Color` Code

```c
/*  
 Test the tft.print() viz the libraries embedded write() function

 This sketch used font 2, 4, 7
 
 Make sure all the required fonts are loaded by editing the
 User_Setup.h file in the TFT_eSPI library folder.

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  #########################################################################
 */

#include <SPI.h>

#include <TFT_eSPI.h> // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

#define TFT_GREY 0x5AEB // New colour


void setup(void) {
  tft.init();
  tft.setRotation(2);
}

void loop() {
  
  // Fill screen with random colour so we can see the effect of printing with and without 
  // a background colour defined
  tft.fillScreen(random(0xFFFF));
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);
  // Set the font colour to be white with a black background, set text size multiplier to 1
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(1);
  // We can now plot text on screen using the "print" class
  tft.println("Hello World!");
  
  // Set the font colour to be yellow with no background, set to font 7
  tft.setTextColor(TFT_YELLOW); tft.setTextFont(7);
  tft.println(1234.56);
  
  // Set the font colour to be red with black background, set to font 4
  tft.setTextColor(TFT_RED,TFT_BLACK);    tft.setTextFont(4);
  tft.println((long)3735928559, HEX); // Should print DEADBEEF

  // Set the font colour to be green with black background, set to font 4
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setTextFont(4);
  tft.println("Groop");
  tft.println("I implore thee,");

  // Change to font 2
  tft.setTextFont(2);
  tft.println(F("my foonting turlingdromes.")); // Can store strings in FLASH to save RAM
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  // This next line is deliberately made too long for the display width to test
  // automatic text wrapping onto the next line
  tft.println("Or I will rend thee in the gobberwarts with my blurglecruncheon, see if I don't!");
  
  // Test some print formatting functions
  float fnumber = 123.45;
   // Set the font colour to be blue with no background, set to font 4
  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.print("Float = "); tft.println(fnumber);           // Print floating point number
  tft.print("Binary = "); tft.println((int)fnumber, BIN); // Print as integer value in binary
  tft.print("Hexadecimal = "); tft.println((int)fnumber, HEX); // Print as integer number in Hexadecimal
  delay(10000);
}
```


| | | |
|-|-|-|
| <img src=images/IMG_0465.jpg width='' height='' > </img> | <img src=images/IMG_0469.jpg width='' height='' > </img> | <img src=images/IMG_0473.jpg width='' height='' > </img> |


# References

- [ ] [ Raspberry Pi Pico with GC9A01 Round Display using Arduino IDE and TFT-eSPI Library](https://www.pcbway.com/project/shareproject/Raspberry_Pi_Pico_with_GC9A01_Round_Display_using_Arduino_IDE_and_TFT_eSPI_Library.html)
- [ ] [Why ili9486 LCD need 74HC4094 to make spi to parallel](https://forums.raspberrypi.com/viewtopic.php?t=158640)
- [ ] [Question: Pin Setup Kuman 3.5 Inch](https://github.com/Bodmer/TFT_eSPI/issues/11)

