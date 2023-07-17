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
