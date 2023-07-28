# LCD (Liquid Crystal Display)

---

### :warning::warning::warning::warning::warning: [ILI9486 Screen with ESP32 SPI and Parallel](https://github.com/Bodmer/TFT_eSPI/issues/299)


[Waveshare_ILI9486](https://github.com/ImpulseAdventure/Waveshare_ILI9486)

Arduino library for Waveshare ILI9486 supporting the Waveshare 3.5" & 4" TFT Touch Shields for Arduino. Includes GFX-compatible API and touchscreen driver

[ILI9486 LCD with SPI interface [Solved] Big thanks to Cal from ImpulseAdventure!](https://forum.arduino.cc/t/ili9486-lcd-with-spi-interface-solved-big-thanks-to-cal-from-impulseadventure/600239/5)

 I would be reluctant to adapt their Waveshare driver into the mainline code as it isn't really packaged as a library, the API doesn't follow common convention, nor does it provide much applicability outside of this specific display — hence the interest in identifying a suitable alternate library.

[Why ili9486 LCD need 74HC4094 to make spi to parallel](https://forums.raspberrypi.com/viewtopic.php?t=158640)

- [ ] [Question: Pin Setup Kuman 3.5 Inch](https://github.com/Bodmer/TFT_eSPI/issues/11)

<img src='https://camo.githubusercontent.com/84a047c16778056a999f05964e0740ab0c4e993d207826c6130ecb74b603f9c6/687474703a2f2f692e696d6775722e636f6d2f514231706838732e706e67' width='' height='' . </img>

|  Func     |  PICO PORT :hash:  | ILI9486 PORT :hash: |
|-|-|-|
| LCD_RST  | 21                  | 22 |
| LCD_DC   | 20                  | 18 |
| LCD_MISO | 16                  | 21 |
| LCD_CS   | 17                  | 24 |
| LCD_SCK  | 18                  | 23 |
| LCD_MOSI | 19                  | 19 | 


---

# References

- [ ] [ Raspberry Pi Pico with GC9A01 Round Display using Arduino IDE and TFT-eSPI Library](https://www.pcbway.com/project/shareproject/Raspberry_Pi_Pico_with_GC9A01_Round_Display_using_Arduino_IDE_and_TFT_eSPI_Library.html)
