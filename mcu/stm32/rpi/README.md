# Running on the Raspberry Pi

- [ ] Step 1: Check SWD Pins of Microcontroller [ST-Nucleo-F446RE](https://os.mbed.com/platforms/ST-Nucleo-F446RE/)

* Position on the MCU

<img src=images/STM32-MX-PinOut-View.png	width=50% height=50% > </img>

* Position on the Connector (CN) PINS

Pin A13 and Pin A14 are connected on the Connector 7 (CN7)

<img src=images/STM32-JTAG-PinOut-View.png	width=50% height=50% > </img>

- [ ] Step 2: Take a Look on Raspberry Pi Pinout

<img src=images/FUI1HTGJ6MGF3EM.jpg	width=90% height=90% > </img>

- [ ] Step 3: Adapt Your Circuit

Now, when you know which PINs are SWD compliant, adapt your circuit diagram to have needed connections.

| | STM32 | RPI |
|-|-|-|
| SWDIO | CN7 :a::one::three:| :two::four: |
| SWDCLK | CN7 :a::one::four: | :two::five:  |

- [ ] Step 4: Install OpenOCD on Raspberry Pi

```
sudo apt install openocd
```
> Response:
```powershell
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
The following additional packages will be installed:
  libcapstone4 libgpiod2 libhidapi-hidraw0 libjaylink0 libjim0.81
The following NEW packages will be installed:
  libcapstone4 libgpiod2 libhidapi-hidraw0 libjaylink0 libjim0.81 openocd
0 upgraded, 6 newly installed, 0 to remove and 19 not upgraded.
Need to get 4,136 kB of archives.
After this operation, 16.4 MB of additional disk space will be used.
Do you want to continue? [Y/n] y
Get:1 http://deb.debian.org/debian bullseye/main arm64 libcapstone4 arm64 4.0.2-3 [534 kB]
Get:2 http://deb.debian.org/debian bullseye/main arm64 libgpiod2 arm64 1.6.2-1 [37.9 kB]
Get:3 http://deb.debian.org/debian bullseye/main arm64 libhidapi-hidraw0 arm64 0.10.1+dfsg-1 [12.0 kB]
Get:4 http://deb.debian.org/debian bullseye/main arm64 libjaylink0 arm64 0.2.0-1 [21.6 kB]
Get:5 http://archive.raspberrypi.org/debian bullseye/main arm64 libjim0.81 arm64 0.81+dfsg0-2 [116 kB]
Get:6 http://archive.raspberrypi.org/debian bullseye/main arm64 openocd arm64 0.12.0-1+rpt1 [3,414 kB]
Fetched 4,136 kB in 1s (3,318 kB/s)  
Selecting previously unselected package libcapstone4:arm64.
(Reading database ... 110647 files and directories currently installed.)
Preparing to unpack .../0-libcapstone4_4.0.2-3_arm64.deb ...
Unpacking libcapstone4:arm64 (4.0.2-3) ...
Selecting previously unselected package libgpiod2:arm64.
Preparing to unpack .../1-libgpiod2_1.6.2-1_arm64.deb ...
Unpacking libgpiod2:arm64 (1.6.2-1) ...
Selecting previously unselected package libhidapi-hidraw0:arm64.
Preparing to unpack .../2-libhidapi-hidraw0_0.10.1+dfsg-1_arm64.deb ...
Unpacking libhidapi-hidraw0:arm64 (0.10.1+dfsg-1) ...
Selecting previously unselected package libjaylink0:arm64.
Preparing to unpack .../3-libjaylink0_0.2.0-1_arm64.deb ...
Unpacking libjaylink0:arm64 (0.2.0-1) ...
Selecting previously unselected package libjim0.81:arm64.
Preparing to unpack .../4-libjim0.81_0.81+dfsg0-2_arm64.deb ...
Unpacking libjim0.81:arm64 (0.81+dfsg0-2) ...
Selecting previously unselected package openocd.
Preparing to unpack .../5-openocd_0.12.0-1+rpt1_arm64.deb ...
Unpacking openocd (0.12.0-1+rpt1) ...
Setting up libjaylink0:arm64 (0.2.0-1) ...
Setting up libhidapi-hidraw0:arm64 (0.10.1+dfsg-1) ...
Setting up libcapstone4:arm64 (4.0.2-3) ...
Setting up libgpiod2:arm64 (1.6.2-1) ...
Setting up libjim0.81:arm64 (0.81+dfsg0-2) ...
Setting up openocd (0.12.0-1+rpt1) ...
Processing triggers for man-db (2.9.4-2) ...
Processing triggers for libc-bin (2.31-13+rpt2+rpi1+deb11u5) ...
```

- [ ] Step 5: Find Interface and Target

* `Interface` describes our programmer - in our case Raspberry Pi. Let's type in Raspberry's console:

```
ls /usr/share/openocd/scripts/interface
```

* `Target` describes a microcontroller which we want to program. Let's see the supported ones:

```
ls /usr/share/openocd/scripts/target/
```

- [ ] Step 6: Prepare OpenOCD Configuration File

```
cat /usr/share/openocd/scripts/openocd.cfg
```
> Response:
```powershell
source [find interface/raspberrypi2-native.cfg]
transport select swd
set WORKAREASIZE 0x2000 
source [find target/stm32f4x.cfg]
reset_config srst_only srst_nogate
adapter srst delay 100
adapter srst pulse_width 100
init
targets
reset halt
```

# References

- [ ] [Wireless Programming and Debugging With STM32 and RPi](https://www.instructables.com/Wireless-Programming-and-Debugging-With-STM32-and-)
