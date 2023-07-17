# :cl: C SDK

:gear: Install [Pico SDK](https://github.com/raspberrypi/pico-sdk)

- [ ] Install the requires libraries

```bash
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```

- [ ] Install the Pico SDK in `~/Developer` folder

```bash
git clone https://github.com/raspberrypi/pico-sdk.git
```

- [ ] Init submodules to avoid `TinyUSB submodule is not initialized in the SDK`


```
git submodule update --init
```


- [ ] Setup a `CMakeLists.txt` like:

```cmake
cmake_minimum_required(VERSION 3.13)

# initialize the SDK directly
include(~/Developer/pico-sdk/pico_sdk_init.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
```

- [ ] Write your code (see pico-examples or the Raspberry Pi Pico C/C++ SDK documentation for more information)

About the simplest you can do is a single source file (e.g. hello_usb.c)

```c
/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
```

And add the following to your CMakeLists.txt:

```cmake
if (TARGET tinyusb_device)
    add_executable(hello_usb
            hello_usb.c
            )

    # pull in common dependencies
    target_link_libraries(hello_usb pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(hello_usb 1)
    pico_enable_stdio_uart(hello_usb 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(hello_usb)

elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()
```

- [ ] Build the program

```
mkdir build ; cd build ; \
cmake ..
```

- [ ] Make the program

```
make hello_usb
```

:books: Examples

| :hash: | Episodes |
|-|-|
| [1](1) | Attaching a 7 segment LED via GPIO |                                                               
| [1](1) | DHT-11, DHT-22, and AM2302 Sensors |                                                             
| [1](1) | Attaching a 16x2 LCD via TTL |                                                                     
| [1](1) | Attaching a microphone using the ADC |                                                             
| [1](1) | Attaching a BME280 temperature/humidity/pressure sensor via SPI |                                     
| [1](1) | Attaching a MPU9250 accelerometer/gyroscope via SPI |                                               
| [1](1) | Attaching a MPU6050 accelerometer/gyroscope via I2C |                                               
| [1](1) | Attaching a 16x2 LCD via I2C |                                                                      
| [1](1) | Attaching a BMP280 temp/pressure sensor via I2C |                                                  
| [1](1) | Attaching a LIS3DH Nano Accelerometer via i2c |                                                    
| [1](1) | Attaching a MCP9808 digital temperature sensor via I2C | 
| [1](1) | Attaching a MMA8451 3-axis digital accelerometer via I2C |
| [1](1) | Attaching an MPL3115A2 altimeter via I2C |
| [1](1) | Attaching an OLED display via I2C |
| [1](1) | Attaching a PA1010D Mini GPS module via I2C |
| [1](1) | Attaching a PCF8523 Real Time Clock via I2C |
| [1](1) | Interfacing 1-Wire devices to the Pico |
| [1](1) | Communicating as master and slave via SPI |

# References

- [ ] [Raspberry Pi Pico C/C++ SDK](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
- [ ] [How fast are the fast floating point functions?](https://forums.raspberrypi.com/viewtopic.php?t=308794)
- [ ] [Quick-start your own project](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#quick-start-your-own-project)
- [ ] [How to Program Raspberry Pi Pico using C/C++ SDK](https://circuitdigest.com/microcontroller-projects/how-to-program-raspberry-pi-pico-using-c)
