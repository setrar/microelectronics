# LCD (Liquid Crystal Display)


- [ ] [3.5 inch RPi Display](https://www.youtube.com/watch?v=5DAn_5-1Jg4)
- [ ] [LCD Wiki: 3.5inch RPi Display](http://www.lcdwiki.com/3.5inch_RPi_Display)
- [ ] [Waveshare: 3.5inch RPi LCD (A), 480x320](https://www.waveshare.com/3.5inch-rpi-lcd-a.htm)

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


### Interface

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

|                  |   :parking:      |   :parking:     |        |
|------------------|-----------------:|----------------:|--------|
| 3.3V             | :one:            | :two:           | 5V     |
| NC               | :three:          | :four:          | 5V     |
| NC               | :five:           | :six:           | GND    |
| NC               | :seven:          | :eight:         | NC     |
| GND              | :nine:           | :one::zero:     | NC     |
| TP_IRQ           | :one::one:       | :one::two:      | NC     |
| NC               | :one::three:     | :one::four:     | GND    |
| NC               | :one::five:      | :one::six:      | NC     |
| NC               | :one::seven:     | :one::eight:    | LCD_RS |
| LCD_SI / TP_SI   | :one::nine:      | :two::zero:     | GND    |
| TP_SO            | :two::one:       | :two::two:      | RST    |
| LCD_SCK / TP_SCK | :two::three:     | :two::four:     | LCD_CS |
| GND              | :two::five:      | :two::six:      | TP_CS  |

<img src=images/IMG_0006.JPG width=50% height=50% > </img>



# References


- [ ] [Getting Started with the Arduino TFT Screen](https://docs.arduino.cc/retired/getting-started-guides/TFT)
- [ ] [:octocat: TFT eSPI](https://github.com/Bodmer/TFT_eSPI)
