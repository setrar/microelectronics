


| | | |
|-|-|-|
| [:octocat: Freenove_Ultimate_Starter_Kit_for_Raspberry_Pi](https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_Raspberry_Pi) | | |
| [:tv: Freenove Projects Kit for Raspberry Pi [Overview]](https://www.youtube.com/watch?v=mx_lC_mLy8I) | | |

[<img src=https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_Raspberry_Pi/blob/master/List_Ultimate_RPi_Kit.jpg width=50% height=50% > </img>](https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_Raspberry_Pi/blob/master/List_Ultimate_RPi_Kit.jpg)

## :a: Starting

:round_pushpin: WiringPi Installation Steps

```bash
sudo apt-get update
git clone https://github.com/WiringPi/WiringPi cd WiringPi
./build
```
> Response :
```python
wiringPi Build script
=====================


WiringPi Library
[UnInstall]
[Compile] wiringPi.c
...
GPIO Utility
[Compile] gpio.c
[Compile] readall.c
[Link]
[Install]

All Done.

NOTE: To compile programs with wiringPi, you need to add:
    -lwiringPi
  to your compile line(s) To use the Gertboard, MaxDetect, etc.
  code (the devLib), you need to also add:
    -lwiringPiDev
  to your compile line(s).
```

```
gpio -v
```
> Response
```python
gpio version: 2.70
Copyright (c) 2012-2018 Gordon Henderson
This is free software with ABSOLUTELY NO WARRANTY.
For details type: gpio -warranty

Raspberry Pi Details:
  Type: Pi 4B, Revision: 01, Memory: 4096MB, Maker: Sony 
  * Device tree is enabled.
  *--> Raspberry Pi 4 Model B Rev 1.1
  * This Raspberry Pi supports user-level GPIO access.
```

# References

- [ ] [Raspberry Pi OS with desktop 64 bit Debian version: 11 (bullseye)](https://downloads.raspberrypi.org/raspios_arm64/images/raspios_arm64-2023-05-03/2023-05-03-raspios-bullseye-arm64.img.xz)
```
brew install --cask raspberry-pi-imager
```
- [ ] [GPIO and the 40-pin Header](https://www.raspberrypi.com/documentation/computers/os.html#gpio-and-the-40-pin-header)
