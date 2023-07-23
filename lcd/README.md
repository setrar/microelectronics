# LCD (Liquid Crystal Display)


- [ ] [3.5 inch RPi Display](https://www.youtube.com/watch?v=5DAn_5-1Jg4)
- [ ] [LCD Wiki: 3.5inch RPi Display](http://www.lcdwiki.com/3.5inch_RPi_Display)
- [ ] [Waveshare: 3.5inch RPi LCD (A), 480x320](https://www.waveshare.com/3.5inch-rpi-lcd-a.htm)
- [ ] [thin-film-transistor liquid-crystal display (TFT LCD)](https://en.wikipedia.org/wiki/TFT_LCD)

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
| Ground                             | GND              | :two::five:      | :two::six:      | TP_CS  |

<img src=images/IMG_0006.JPG width=50% height=50% > </img>



# References


- [ ] [Getting Started with the Arduino TFT Screen](https://docs.arduino.cc/retired/getting-started-guides/TFT)
- [ ] [:octocat: TFT eSPI](https://github.com/Bodmer/TFT_eSPI)
- [ ] [:octocat: Python_ILI9486](https://github.com/ustropo/Python_ILI9486)
- [ ] [ILI9486_Datasheet](https://www.waveshare.com/w/upload/7/78/ILI9486_Datasheet.pdf)
- [ ] [Re: Library for ILI9486](https://forum.micropython.org/viewtopic.php?t=8343#p66692)
- [ ] [The py-driver (originally from waveshare) I am using for this display is among the example files in](https://ctx.graphics/uctx/downloads/uctx-examples.tar.gz)
```python
from machine import Pin,SPI,PWM
import framebuf
import time
import os

LCD_DC   = 8
LCD_CS   = 9
LCD_SCK  = 10
LCD_MOSI = 11
LCD_MISO = 12
LCD_BL   = 13
LCD_RST  = 15
TP_CS    = 16
TP_IRQ   = 17

class LCD():

    def __init__(self):
        self.RED   =   0x07E0
        self.GREEN =   0x001f
        self.BLUE  =   0xf800
        self.WHITE =   0xffff
        self.BLACK =   0x0000
        
        self.width = 480
        self.height = 160
        
        self.cs = Pin(LCD_CS,Pin.OUT)
        self.rst = Pin(LCD_RST,Pin.OUT)
        self.dc = Pin(LCD_DC,Pin.OUT)
        
        self.tp_cs =Pin(TP_CS,Pin.OUT)
        self.irq = Pin(TP_IRQ,Pin.IN)
        
        self.cs(1)
        self.dc(1)
        self.rst(1)
        self.tp_cs(1)
        self.spi = SPI(1,60_000_000,sck=Pin(LCD_SCK),mosi=Pin(LCD_MOSI),miso=Pin(LCD_MISO))
              
        self.init_display()

        
    def write_cmd(self, cmd):
        self.cs(1)
        self.dc(0)
        self.cs(0)
        self.spi.write(bytearray([cmd]))
        self.cs(1)

    def write_data(self, buf):
        self.cs(1)
        self.dc(1)
        self.cs(0)
        #self.spi.write(bytearray([0X00]))
        self.spi.write(bytearray([buf]))
        self.cs(1)


    def init_display(self):
        """Initialize dispaly"""  
        self.rst(1)
        time.sleep_ms(5)
        self.rst(0)
        time.sleep_ms(10)
        self.rst(1)
        time.sleep_ms(5)
        self.write_cmd(0x21)
        self.write_cmd(0xC2)
        self.write_data(0x33)
        self.write_cmd(0XC5)
        self.write_data(0x00)
        self.write_data(0x1e)
        self.write_data(0x80)
        self.write_cmd(0xB1)
        self.write_data(0xB0)
        self.write_cmd(0x36)
        self.write_data(0x28)
        self.write_cmd(0XE0)
        self.write_data(0x00)
        self.write_data(0x13)
        self.write_data(0x18)
        self.write_data(0x04)
        self.write_data(0x0F)
        self.write_data(0x06)
        self.write_data(0x3a)
        self.write_data(0x56)
        self.write_data(0x4d)
        self.write_data(0x03)
        self.write_data(0x0a)
        self.write_data(0x06)
        self.write_data(0x30)
        self.write_data(0x3e)
        self.write_data(0x0f)
        self.write_cmd(0XE1)
        self.write_data(0x00)
        self.write_data(0x13)
        self.write_data(0x18)
        self.write_data(0x01)
        self.write_data(0x11)
        self.write_data(0x06)
        self.write_data(0x38)
        self.write_data(0x34)
        self.write_data(0x4d)
        self.write_data(0x06)
        self.write_data(0x0d)
        self.write_data(0x0b)
        self.write_data(0x31)
        self.write_data(0x37)
        self.write_data(0x0f)
        self.write_cmd(0X3A)
        self.write_data(0x55)
        self.write_cmd(0x11)
        time.sleep_ms(120)
        self.write_cmd(0x29)
        
        self.write_cmd(0xB6)
        self.write_data(0x00)
        self.write_data(0x62)
        
        self.write_cmd(0x36)
        self.write_data(0x28)
    def blit_buffer(self, buffer,x,y,w,h):
        self.write_cmd(0x2A)
        self.write_data(int(x/256))
        self.write_data(int(x&255))
        self.write_data(int((x+w-1)/256))
        self.write_data(int((x+w-1)&255))

        self.write_cmd(0x2B)
        self.write_data(int(y/256))
        self.write_data(int(y&255))
        self.write_data(int((y+h-1)/256))
        self.write_data(int((y+h-1)&255))
        
        self.write_cmd(0x2C)
        
        self.cs(1)
        self.dc(1)
        self.cs(0)
        self.spi.write(buffer)
        self.cs(1)
    def bl_ctrl(self,duty):
        pwm = PWM(Pin(LCD_BL))
        pwm.freq(1000)
        if(duty>=100):
            pwm.duty_u16(65535)
        else:
            pwm.duty_u16(655*duty)
    def touch_get(self): 
        if self.irq() == 0:
            self.spi = SPI(1,5_000_000,sck=Pin(LCD_SCK),mosi=Pin(LCD_MOSI),miso=Pin(LCD_MISO))
            self.tp_cs(0)
            X_Point = 0
            Y_Point = 0
            for i in range(0,3):
                self.spi.write(bytearray([0XD0]))
                Read_date = self.spi.read(2)
                time.sleep_us(10)
                Y_Point=Y_Point+(((Read_date[0]<<8)+Read_date[1])>>3)
                
                self.spi.write(bytearray([0X90]))
                Read_date = self.spi.read(2)
                X_Point=X_Point+(((Read_date[0]<<8)+Read_date[1])>>3)

            X_Point=X_Point/3
            Y_Point=Y_Point/3
            
            self.tp_cs(1) 
            self.spi = SPI(1,60_000_000,sck=Pin(LCD_SCK),mosi=Pin(LCD_MOSI),miso=Pin(LCD_MISO))

            X_Point = int((X_Point-430)*480/3270)
            if(X_Point>480):
                X_Point = 480
            elif X_Point<0:
                X_Point = 0
            Y_Point = 320-int((Y_Point-430)*320/3270)


            Result_list = [X_Point,Y_Point]
            #print(Result_list)
            return(Result_list)

```
- [ ] [2D vector graphics for micropython with ctx](https://ctx.graphics/uctx/#/main.py)
- [ ] [Rust LILYGO T-Display with RP2040](https://circuit4us.medium.com/rust-lilygo-t-display-with-rp2040-a93635240d7b)
```rust
#![no_std]
#![no_main]

use defmt_rtt as _;
use embedded_hal::digital::v2::OutputPin;
use panic_probe as _;

use rp2040_hal as hal;

use display_interface_spi::SPIInterfaceNoCS;
use fugit::RateExtU32;
use mipidsi::{Builder, Orientation};

use embedded_graphics::{
    mono_font::{ascii::FONT_10X20, MonoTextStyle},
    pixelcolor::Rgb565,
    prelude::*,
    primitives::{Line, PrimitiveStyle},
    text::Text,
};
use hal::{
    clocks::{init_clocks_and_plls, Clock},
    pac,
    sio::Sio,
    watchdog::Watchdog,
};

#[link_section = ".boot2"]
#[used]
pub static BOOT2: [u8; 256] = rp2040_boot2::BOOT_LOADER_GENERIC_03H;

#[rp2040_hal::entry]
fn main() -> ! {
    let mut pac = pac::Peripherals::take().unwrap();
    let core = pac::CorePeripherals::take().unwrap();
    let mut watchdog = Watchdog::new(pac.WATCHDOG);
    let sio = Sio::new(pac.SIO);

    // External high-speed crystal on the pico board is 12Mhz
    let external_xtal_freq_hz = 12_000_000u32;
    let clocks = init_clocks_and_plls(
        external_xtal_freq_hz,
        pac.XOSC,
        pac.CLOCKS,
        pac.PLL_SYS,
        pac.PLL_USB,
        &mut pac.RESETS,
        &mut watchdog,
    )
    .ok()
    .unwrap();

    let mut delay = cortex_m::delay::Delay::new(core.SYST, clocks.system_clock.freq().to_Hz());

    let pins = hal::gpio::Pins::new(
        pac.IO_BANK0,
        pac.PADS_BANK0,
        sio.gpio_bank0,
        &mut pac.RESETS,
    );

    let mut pw_en = pins.gpio22.into_push_pull_output();
    pw_en.set_high().unwrap();

    let lcd_dc = pins.gpio1.into_push_pull_output();

    let mut _lcd_cs = pins.gpio5.into_mode::<hal::gpio::FunctionSpi>();
    let mut _lcd_clk = pins.gpio2.into_mode::<hal::gpio::FunctionSpi>();
    let mut _lcd_mosi = pins.gpio3.into_mode::<hal::gpio::FunctionSpi>();

    let lcd_rst = pins
        .gpio0
        .into_push_pull_output_in_state(hal::gpio::PinState::High);

    let mut lcd_bl = pins.gpio4.into_push_pull_output();
    lcd_bl.set_high().unwrap();

    let spi = hal::Spi::<_, _, 8>::new(pac.SPI0);
    let spi = spi.init(
        &mut pac.RESETS,
        clocks.peripheral_clock.freq(),
        10.MHz(),
        &embedded_hal::spi::MODE_0,
    );
    let di = SPIInterfaceNoCS::new(spi, lcd_dc);

    let mut display = Builder::st7789_pico1(di)
        .init(&mut delay, Some(lcd_rst))
        .unwrap(); // delay provider from your MCU
    display
        .set_orientation(Orientation::Landscape(true))
        .unwrap();

    display.clear(Rgb565::BLUE).unwrap();

    Line::new(
        Point::zero(),
        Point::new((240 - 1) as i32, (135 - 1) as i32),
    )
    .into_styled(PrimitiveStyle::with_stroke(Rgb565::RED, 1))
    .draw(&mut display)
    .unwrap();

    let style = MonoTextStyle::new(&FONT_10X20, Rgb565::WHITE);
    // Create a text at position (20, 30) and draw it using the previously defined style
    Text::new("Hello World!", Point::new(20, 30), style)
        .draw(&mut display)
        .unwrap();

    loop {}
}
```
