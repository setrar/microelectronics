# LCD (Liquid Crystal Display)


|  Func             |  PICO PORT :hash:  | Comments                         | ILI9486 PORT :hash: |
|-------------------|-----|---------------------------------------------------|----|
| #define TFT_MISO  | 16  |                                                   | 21 | 
| #define TFT_CS    | 17  | // Chip select control pin                        | 24 |
| #define TFT_SCLK  | 18  |                                                   | 23 |
| #define TFT_MOSI  | 19  | // Do not connect to SDO(MISO), only to T_DO!!!   | 19 |
| #define TFT_DC    | 20  | // Data Command control pin                       | 18 |
| #define TFT_RST   | 21  | // Reset pin (could connect to Arduino RESET pin) | 22 |
| | | |
| #define TOUCH_CS  | 22  |                                                   | 26 |

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


---

# References

- [ ] [ Raspberry Pi Pico with GC9A01 Round Display using Arduino IDE and TFT-eSPI Library](https://www.pcbway.com/project/shareproject/Raspberry_Pi_Pico_with_GC9A01_Round_Display_using_Arduino_IDE_and_TFT_eSPI_Library.html)
- [ ] [Why ili9486 LCD need 74HC4094 to make spi to parallel](https://forums.raspberrypi.com/viewtopic.php?t=158640)
- [ ] [Question: Pin Setup Kuman 3.5 Inch](https://github.com/Bodmer/TFT_eSPI/issues/11)

