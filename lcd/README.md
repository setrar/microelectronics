# LCD (Liquid Crystal Display)


- [ ] [How do I use the 3.5inch RPi Display with the pico?](https://www.reddit.com/r/raspberrypipico/comments/wzrpw0/how_do_i_use_the_35inch_rpi_display_with_the_pico)

I have this screen [3.5inch_RPi_Display](http://www.lcdwiki.com/3.5inch_RPi_Display) and a pico. I am new to screens and could only get that one at the moment. How could I connect them so I can display stuff on it from the pico? I was told "I dont see why it wont work"

- [ ] [🚴‍♂️chez_man69](https://www.reddit.com/user/chez_man69/)

I did end up solving it. There was no documentation for this model as far as i could find so I used other images to figure it out.

Just need some drivers first

What I have (Where my wires are etc) for anyone in the future https://imgur.com/a/Ol74ny2
Some things that helped :
- [ ] [Connect an SPI LCD TFT Display to Your Raspberry Pi Pico With MicroPython - ILI9341 Driver](https://youtu.be/suCTwxlYgnM?t=252)
- [ ] https://spotpear.com/uploads/picture/learn/raspberry-pi/rpi-pico/pico-restouch-lcd-2.8/pico-restouch-lcd-2.8-02.jpg

| By [unknown.png](https://cdn.discordapp.com/attachments/898384284010811452/1013396080425177088/unknown.png) | The LCD Hat going on top of the Pi, the pin numbers are inverted | |
|-|-|-|
| <img src=images/unknown.png width='' height='' > </img> |  <img src=images/unknown-label.png width='' height='' > </img> | <img src=images/b421c0e53d336396dc0592f764d0bc27f0341032.png width='' height='' > </img> | 

| DESCRIPTION                        |                  |   :parking:      |   :parking:     |        | DESCRIPTION                          |
|------------------------------------|------------------|-----------------:|----------------:|--------|--------------------------------------|
|                                    | NC               | :one:            | :two:           | 5V     | Power positive (5V power input)      |
|                                    | NC               | :three:          | :four:          | 5V     | Power positive (5V power input)      |
|                                    | NC               | :five:           | :six:           | GND    | Ground                               |
|                                    | NC               | :seven:          | :eight:         | NC     |                                      |
| Ground                             | GND              | :nine:           | :one::zero:     | NC     |                                      |
| Touch Panel interrupt, low level   | TP_IRQ           | :one::one:       | :one::two:      | NC     |                                      |
|                                    | NC               | :one::three:     | :one::four:     | GND    | Ground                               |
|                                    | NC               | :one::five:      | :one::six:      | NC     |                                      |
|                                    | NC               | :one::seven:     | :one::eight:    | LCD_RS (DC) | Instruction/Data Register selection  |
| SPI data input of LCD/Touch Panel  | LCD_SI / (MOSI)  | :one::nine:      | :two::zero:     | GND    | Ground                               |
| SPI data output of Touch Panel     | TP_SO   (MISO?)  | :two::one:       | :two::two:      | RST    | Reset                                |
| SPI clock of LCD/Touch Panel       | LCD_SCK / TP_SCK | :two::three:     | :two::four:     | LCD_CS | LCD chip selection, low active       |
| Ground                             | GND              | :two::five:      | :two::six:      | TP_CS  | Touch Panel chip selection, low active |

|  Func     |  PICO PORT :hash:  | ILI9486 PORT :hash: |
|-|-|-|
| LCD_RST  | 14                  | 22 |
| LCD_DC   | 15                  | 18 |
| LCD_MISO | 16                  | 21 |
| LCD_CS   | 17                  | 24 |
| LCD_SCK  | 18                  | 23 |
| LCD_MOSI | 19                  | 19 | 

|  Func     |  PICO PORT :hash:  | ILI9486 PORT :hash: |
|-|-|-|
| LCD_BL   | 13                | | 
| TP_CS    | 16                |   |
| TP_IRQ   | 17                |  |


:round_pushpin: Articles

- [ ] [3.5" ILI9488/ILI9486 w ESP32](https://forum.arduino.cc/t/3-5-ili9488-ili9486-w-esp32/480035/3)


```python
# PICO PORT     # ILI9486 PORT
LCD_DC   = 8    # 17 Data / Command
LCD_CS   = 9    # 23 Chip Selection
LCD_SCK  = 10   # 24 Clock
LCD_MOSI = 11   # 20 LCD_SI 
LCD_MISO = 12   # 
LCD_BL   = 13   # 
LCD_RST  = 15   # 21 Reset
TP_CS    = 16   #  
TP_IRQ   = 17   #  
```

- [ ] [What is the D/C pin on the 1.8" TFT LCD breakout?](https://forums.adafruit.com/viewtopic.php?t=51949)

> by adafruit_support_bill » Mon Mar 31, 2014 3:47 pm

That is a data/command pin. SPI has no formal standard and there are lots variations on it. Instead of separate CS pins for data and command, they use one CS pin and the D/C to toggle between them.
 
> by xenoc » Mon Mar 31, 2014 4:06 pm

Interesting. By this, do you mean that for the LCD controller, the MOSI pin is used for receiving data and commands, and that D/C is set by the master to indicate which it is being sent?

> by adafruit_support_bill » Mon Mar 31, 2014 4:16 pm

That is right.

| | | |
|-|-|-|
| <img src=images/IMG_0437.jpg width='' height='' > </img> | <img src=images/IMG_0438.jpg width='' height='' > </img> | <img src=images/IMG_0441.jpg width='' height='' > </img> |

[Connect an SPI LCD TFT Display to Your Raspberry Pi Pico With MicroPython - ILI9341 Driver](https://www.youtube.com/watch?v=suCTwxlYgnM&t=252s)<img src=images/fritzing-1.png width=50% height=50% > </img>

---

- [ ] [3.5 inch RPi Display](https://www.youtube.com/watch?v=5DAn_5-1Jg4)
- [ ] [LCD Wiki: 3.5inch RPi Display](http://www.lcdwiki.com/3.5inch_RPi_Display)
- [ ] [Waveshare: 3.5inch RPi LCD (A), 480x320](https://www.waveshare.com/3.5inch-rpi-lcd-a.htm)
- [ ] [thin-film-transistor liquid-crystal display (TFT LCD)](https://en.wikipedia.org/wiki/TFT_LCD)
- [ ] [a-Si TFT LCD Single Chip Driver 320RGBx480 Resolution and 262K-color ](http://www.lcdwiki.com/res/MRB3503/ILI9486_Datasheet.pdf)

| |
|-|
| SKU MPI3501 |
| LCD Type TFT | 
| LCD Interface	SPI(Fmax:32MHz) |
| Touch Screen Type Resistive |
| Touch Screen Controller XPT2046 |
| Colors 65536 |
| Driver IC	ILI9486 |
| Backlight LED |
| Resolution 320*240 (Pixel) |
| Aspect Ratio 8:5 |
| Backlight Current	120ma |
| Power Dissipation	0.13A*5V |
| Operating Temp. (℃)	-20~60 |
| Active Area	48.96x73.44(mm) |
| Product Size	85.42*55.60(mm) |
| Package Size	118*72*34 (mm) |
| Rough Weight(Package containing)	75 (g) |


### [Interface](https://www.waveshare.com/3.5inch-rpi-lcd-a.htm/#:~:text=pin,symbol)

| PIN NO.	                       | SYMBOL	          | DESCRIPTION                                                             |
|--------------------------------|------------------|-------------------------------------------------------------------------|
| 1, 17	                         | 3.3V	            | Power positive (3.3V power input)                                       |
| 2, 4	                         | 5V	              | Power positive (5V power input)                                         |
| 3, 5, 7, 8, 10, 12, 13, 15, 16 | NC               | NC                                                                      |
| 6, 9, 14, 20, 25	             | GND	            | Ground                                                                  |
| 11	                           | TP_IRQ	          | Touch Panel interrupt, low level while the Touch Panel detects touching |
| 18	                           | LCD_RS	          | Instruction/Data Register selection                                     |
| 19	                           | LCD_SI / TP_SI	  | SPI data input of LCD/Touch Panel                                       |
| 21	                           | TP_SO	          | SPI data output of Touch Panel                                          |
| 22	                           | RST	            | Reset                                                                   |
| 23	                           | LCD_SCK / TP_SCK	| SPI clock of LCD/Touch Panel                                            |
| 24		                         | LCD_CS	          | LCD chip selection, low active                                          |
| 26                             | TP_CS            | Touch Panel chip selection, low active                                  |

## [PinOUT](https://pinout.xyz)

| DESCRIPTION                        |                  |   :parking:      |   :parking:     |        | DESCRIPTION                          |
|------------------------------------|------------------|-----------------:|----------------:|--------|--------------------------------------|
| Power positive (3.3V power input)  | 3.3V             | :one:            | :two:           | 5V     | Power positive (5V power input)      |
|                                    | NC               | :three:          | :four:          | 5V     | Power positive (5V power input)      |
|                                    | NC               | :five:           | :six:           | GND    | Ground                               |
|                                    | NC               | :seven:          | :eight:         | NC     |                                      |
| Ground                             | GND              | :nine:           | :one::zero:     | NC     |                                      |
| Touch Panel interrupt, low level   | TP_IRQ           | :one::one:       | :one::two:      | NC     |                                      |
|                                    | NC               | :one::three:     | :one::four:     | GND    | Ground                               |
|                                    | NC               | :one::five:      | :one::six:      | NC     |                                      |
|                                    | NC               | :one::seven:     | :one::eight:    | LCD_RS | Instruction/Data Register selection  |
| SPI data input of LCD/Touch Panel  | LCD_SI / TP_SI   | :one::nine:      | :two::zero:     | GND    | Ground                               |
| SPI data output of Touch Panel     | TP_SO            | :two::one:       | :two::two:      | RST    | Reset                                |
| SPI clock of LCD/Touch Panel       | LCD_SCK / TP_SCK | :two::three:     | :two::four:     | LCD_CS | LCD chip selection, low active       |
| Ground                             | GND              | :two::five:      | :two::six:      | TP_CS  | Touch Panel chip selection, low active |


| The LCD Hat going on top of the Pi, the pin numbers are inverted | [:warning: RPi4 SPI Pinouts](https://pinout.xyz/pinout/spi) | | 
|-|-|-|
| <img src=images/IMG_0006.JPG width='' height='' > </img> | <img src=images/RPI4-pins.png width=200% height=200% > </img> | <img src=images/IMG_0455.jpg width='' height='' > </img> |




<img src=images/rpi-pico-pinout.png width='' height='' > </img>

# References


- [ ] [MIPI Display Serial Interface unified driver: Rust :gear:](https://github.com/almindor/mipidsi)

- [ ] [Getting Started with the Arduino TFT Screen](https://docs.arduino.cc/retired/getting-started-guides/TFT)
- [ ] [:octocat: TFT eSPI](https://github.com/Bodmer/TFT_eSPI)
- [ ] [:octocat: Python_ILI9486](https://github.com/ustropo/Python_ILI9486)
- [ ] [ILI9486_Datasheet](https://www.waveshare.com/w/upload/7/78/ILI9486_Datasheet.pdf)
- [ ] [Re: Library for ILI9486](https://forum.micropython.org/viewtopic.php?t=8343#p66692)
- [ ] [The py-driver (originally from waveshare) I am using for this display is among the example files in](https://ctx.graphics/uctx/downloads/uctx-examples.tar.gz)

- [ ] [WHAT COULD GO WRONG: SPI](https://hackaday.com/2016/07/01/what-could-go-wrong-spi)

:round_pushpin: Rust

- [ ] [2D vector graphics for micropython with ctx](https://ctx.graphics/uctx/#/main.py)
- [ ] [Rust LILYGO T-Display with RP2040](https://circuit4us.medium.com/rust-lilygo-t-display-with-rp2040-a93635240d7b)

# References

- [ ] [Introduction to SPI Interface](https://www.analog.com/en/analog-dialogue/articles/introduction-to-spi-interface.html)
- [ ] [Displaying Images on ESP32 with Rust!](https://lilymara.xyz/posts/images-esp32/)
