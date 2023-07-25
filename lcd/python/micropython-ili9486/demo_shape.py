"""ILI9341 demo (shapes)."""
from time import sleep
from ili9486 import Display, color565
from machine import Pin, SPI


def test():
    """Test code."""

    spi = SPI(0,
              baudrate=10000000,
              polarity=1,
              phase=1,
              bits=8,
              firstbit=SPI.MSB,
              sck=Pin(18),
              mosi=Pin(19),
              miso=Pin(16))
    display = Display(spi, dc=Pin(15), cs=Pin(17), rst=Pin(14))

    display.clear(color565(64, 0, 255))
    sleep(1)

    display.clear()

    display.draw_hline(10, 319, 229, color565(255, 0, 255))
    sleep(1)


test()


