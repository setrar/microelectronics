# LCD (Liquid Crystal Display)

---

### :warning::warning::warning::warning::warning: [ILI9486 Screen with ESP32 SPI and Parallel](https://github.com/Bodmer/TFT_eSPI/issues/299)


[Waveshare_ILI9486](https://github.com/ImpulseAdventure/Waveshare_ILI9486)

Arduino library for Waveshare ILI9486 supporting the Waveshare 3.5" & 4" TFT Touch Shields for Arduino. Includes GFX-compatible API and touchscreen driver

[ILI9486 LCD with SPI interface [Solved] Big thanks to Cal from ImpulseAdventure!](https://forum.arduino.cc/t/ili9486-lcd-with-spi-interface-solved-big-thanks-to-cal-from-impulseadventure/600239/5)

 I would be reluctant to adapt their Waveshare driver into the mainline code as it isn't really packaged as a library, the API doesn't follow common convention, nor does it provide much applicability outside of this specific display — hence the interest in identifying a suitable alternate library.

[Why ili9486 LCD need 74HC4094 to make spi to parallel](https://forums.raspberrypi.com/viewtopic.php?t=158640)

---

# References

- [ ] [ ](https://www.pcbway.com/project/shareproject/Raspberry_Pi_Pico_with_GC9A01_Round_Display_using_Arduino_IDE_and_TFT_eSPI_Library.html)

- [ ] [Install Arduino IDE on Raspberry Pi](https://www.raspberrypi-spy.co.uk/2020/12/install-arduino-ide-on-raspberry-pi/)

```
apt install arduino
```

 - [ ] Open the IDE

 > Menu > Electronics > Arduino IDE

 > Now under the “Tools” menu select “Board” followed by “Boards Manager”.

 > In the search box type “pico” and press “Enter”. The search result should present you with “Arduino Mbed OS RP2040 Boards” by the “Arduino”.

  Click “Install”
