# Copyright (c) 2016 myway work
# Author: Liqun Hu
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

"""ILI9486 LCD/Touch module."""
from time import sleep
from math import cos, sin, pi, radians
from sys import implementation
from framebuf import FrameBuffer, RGB565  # type: ignore
import ustruct  # type: ignore
import time



def color565(r, g, b):
    """Convert red, green, blue components to a 16-bit 565 RGB value. Components
    should be values 0 to 255.
    """
    return ((r & 0xF0) << 8) | ((g & 0xFC) << 3) | (b >> 3)

class Display(object):
    """Representation of an ILI9486 TFT LCD."""

    # Constants for interacting with display registers.
    ILI9486_TFTWIDTH    = 320
    ILI9486_TFTHEIGHT   = 480

    ILI9486_NOP         = 0x00
    ILI9486_SWRESET     = 0x01
    ILI9486_RDDID       = 0x04
    ILI9486_RDDST       = 0x09

    ILI9486_SLPIN       = 0x10
    ILI9486_SLPOUT      = 0x11
    ILI9486_PTLON       = 0x12
    ILI9486_NORON       = 0x13

    ILI9486_RDMODE      = 0x0A
    ILI9486_RDMADCTL    = 0x0B
    ILI9486_RDPIXFMT    = 0x0C
    ILI9486_RDIMGFMT    = 0x0A
    ILI9486_RDSELFDIAG  = 0x0F

    ILI9486_INVOFF      = 0x20
    ILI9486_INVON       = 0x21
    ILI9486_GAMMASET    = 0x26
    ILI9486_DISPOFF     = 0x28
    ILI9486_DISPON      = 0x29

    ILI9486_CASET       = 0x2A
    ILI9486_PASET       = 0x2B
    ILI9486_RAMWR       = 0x2C
    ILI9486_RAMRD       = 0x2E

    ILI9486_PTLAR       = 0x30
    ILI9486_MADCTL      = 0x36
    ILI9486_PIXFMT      = 0x3A

    ILI9486_FRMCTR1     = 0xB1
    ILI9486_FRMCTR2     = 0xB2
    ILI9486_FRMCTR3     = 0xB3
    ILI9486_INVCTR      = 0xB4
    ILI9486_DFUNCTR     = 0xB6

    ILI9486_PWCTR1      = 0xC0
    ILI9486_PWCTR2      = 0xC1
    ILI9486_PWCTR3      = 0xC2
    ILI9486_PWCTR4      = 0xC3
    ILI9486_PWCTR5      = 0xC4
    ILI9486_VMCTR1      = 0xC5
    ILI9486_VMCTR2      = 0xC7

    ILI9486_RDID1       = 0xDA
    ILI9486_RDID2       = 0xDB
    ILI9486_RDID3       = 0xDC
    ILI9486_RDID4       = 0xDD

    ILI9486_GMCTRP1     = 0xE0
    ILI9486_GMCTRN1     = 0xE1

    ILI9486_PWCTR6      = 0xFC

    ILI9486_BLACK       = 0x0000
    ILI9486_BLUE        = 0x001F
    ILI9486_RED         = 0xF800
    ILI9486_GREEN       = 0x07E0
    ILI9486_CYAN        = 0x07FF
    ILI9486_MAGENTA     = 0xF81F
    ILI9486_YELLOW      = 0xFFE0  
    ILI9486_WHITE       = 0xFFFF

    ROTATE = {
        0: 0x88,
        90: 0xE8,
        180: 0x48,
        270: 0x28
    }

    def __init__(self, spi, cs, dc, rst,
                 width=ILI9486_TFTWIDTH, height=ILI9486_TFTHEIGHT, rotation=0):

        """Create an instance of the display using SPI communication.  Must
        provide the GPIO pin number for the D/C pin and the SPI driver.  Can
        optionally provide the GPIO pin number for the reset pin as the rst
        parameter.
        """
        self.spi = spi
        self._dc = dc
        self._rst = rst
        self._spi = spi
        self.width = width
        self.height = height
        if rotation not in self.ROTATE.keys():
            raise RuntimeError('Rotation must be 0, 90, 180 or 270.')
        else:
            self.rotation = self.ROTATE[rotation]
        # Set SPI to mode 0, MSB first.
#        spi.set_mode(2)
#        spi.set_bit_order(SPI.MSBFIRST)
#        spi.set_clock_hz(64000000)

    def send(self, data, is_data=True, chunk_size=4096):
        """Write a byte or array of bytes to the display. Is_data parameter
        controls if byte should be interpreted as display data (True) or command
        data (False).  Chunk_size is an optional size of bytes to write in a
        single SPI transaction, with a default of 4096.
        """
        # Convert scalar argument to list so either can be passed as parameter.
        #data = [data & 0xFF]
        # Write data a chunk at a time.
        #for start in range(0, len(data), chunk_size):
        #    end = min(start+chunk_size, len(data))
        #    self._spi.write(data[start:end])
        if is_data:
            self._spi.write(bytearray(data))
        else:
            self._spi.write(bytearray(data))

    def command(self, data):
        """Write a byte or array of bytes to the display as command data."""
        self.send(data, False)

    def data(self, data):
        """Write a byte or array of bytes to the display as display data."""
        self.send(data, True)

    def reset(self):
        """Reset the display, if reset pin is connected."""
        if self._rst is not None:
            self._rst(1)
            time.sleep(.005)
            self._rst(0)
            time.sleep(.02)
            self._rst(1)
            time.sleep(.150)

    def _init(self):
        # Initialize the display.  Broken out as a separate function so it can
        # be overridden by other displays in the future.
        self.command(0xB0)
        self.data(0x00)
        self.command(0x11)
        time.sleep(0.020)
    
        self.command(0x3A)
        self.data(0x66)

        self.command(0x0C)
        self.data(0x66)

        #self.command(0xB6)
        #self.data(0x00)
        #self.data(0x42)
        #self.data(0x3B)

        self.command(0xC2)
        self.data(0x44)

        self.command(0xC5)
        self.data(0x00)
        self.data(0x00)
        self.data(0x00)
        self.data(0x00)
        
        self.command(0xE0)
        self.data(0x0F)
        self.data(0x1F)
        self.data(0x1C)
        self.data(0x0C)
        self.data(0x0F)
        self.data(0x08)
        self.data(0x48)
        self.data(0x98)
        self.data(0x37)
        self.data(0x0A)
        self.data(0x13)
        self.data(0x04)
        self.data(0x11)
        self.data(0x0D)
        self.data(0x00)

        self.command(0xE1)
        self.data(0x0F)
        self.data(0x32)
        self.data(0x2E)
        self.data(0x0B)
        self.data(0x0D)
        self.data(0x05)
        self.data(0x47)
        self.data(0x75)
        self.data(0x37)
        self.data(0x06)
        self.data(0x10)
        self.data(0x03)
        self.data(0x24)
        self.data(0x20)
        self.data(0x00)
    
        self.command(0xE2)
        self.data(0x0F)
        self.data(0x32)
        self.data(0x2E)
        self.data(0x0B)
        self.data(0x0D)
        self.data(0x05)
        self.data(0x47)
        self.data(0x75)
        self.data(0x37)
        self.data(0x06)
        self.data(0x10)
        self.data(0x03)
        self.data(0x24)
        self.data(0x20)
        self.data(0x00)
            
        self.command(0x36)
        self.data(0x88) #change the direct

        self.command(0x11)
        self.command(0x29)

    def begin(self):
        """Initialize the display.  Should be called once before other calls that
        interact with the display are called.
        """
        self.reset()
        self._init()    
    
    def set_window(self, x0=0, y0=0, x1=None, y1=None):
        """Set the pixel address window for proceeding drawing commands. x0 and
        x1 should define the minimum and maximum x pixel bounds.  y0 and y1 
        should define the minimum and maximum y pixel bound.  If no parameters 
        are specified the default will be to update the entire display from 0,0
        to 239,319.
        """
        if x1 is None:
            x1 = self.width-1
        if y1 is None:
            y1 = self.height-1
        self.command(0x2A)        # Column addr set
        self.data(x0 >> 8)
        self.data(x0 & 0xFF)                    # XSTART 
        self.data(x1 >> 8)
        self.data(x1 & 0xFF)                    # XEND
        self.command(0x2B)        # Row addr set
        self.data(y0 >> 8)
        self.data(y0 & 0xFF)                    # YSTART
        self.data(y1 >> 8)
        self.data(y1 & 0xFF)                    # YEND
        self.command(0x2C)        # write to RAM

    def draw_hline(self, x, y, w, color):
        """Draw a horizontal line.

        Args:
            x (int): Starting X position.
            y (int): Starting Y position.
            w (int): Width of line.
            color (int): RGB565 color value.
        """
        if self.is_off_grid(x, y, x + w - 1, y):
            return
        line = color.to_bytes(2, 'big') * w
        self.block(x, y, x + w - 1, y, line)        

    def is_off_grid(self, xmin, ymin, xmax, ymax):
        """Check if coordinates extend past display boundaries.

        Args:
            xmin (int): Minimum horizontal pixel.
            ymin (int): Minimum vertical pixel.
            xmax (int): Maximum horizontal pixel.
            ymax (int): Maximum vertical pixel.
        Returns:
            boolean: False = Coordinates OK, True = Error.
        """
        if xmin < 0:
            print('x-coordinate: {0} below minimum of 0.'.format(xmin))
            return True
        if ymin < 0:
            print('y-coordinate: {0} below minimum of 0.'.format(ymin))
            return True
        if xmax >= self.width:
            print('x-coordinate: {0} above maximum of {1}.'.format(
                xmax, self.width - 1))
            return True
        if ymax >= self.height:
            print('y-coordinate: {0} above maximum of {1}.'.format(
                ymax, self.height - 1))
            return True
        return False
    
    def block(self, x0, y0, x1, y1, data):
        """Write a block of data to display.

        Args:
            x0 (int):  Starting X position.
            y0 (int):  Starting Y position.
            x1 (int):  Ending X position.
            y1 (int):  Ending Y position.
            data (bytes): Data buffer to write.
        """
        self.write_cmd(self.ILI9486_CASET, *ustruct.pack(">HH", x0, x1))
        self.write_cmd(self.ILI9486_PASET, *ustruct.pack(">HH", y0, y1))

        self.write_cmd(self.ILI9486_RAMWR)
        self.data(data)

    def write_cmd(self, command, *args):
        """Write command to OLED (MicroPython).

        Args:
            command (byte): ILI9341 command code.
            *args (optional bytes): Data to transmit.
        """
        self.command(bytearray([command]))
        # Handle any passed data
        if len(args) > 0:
            self.data(bytearray(args))