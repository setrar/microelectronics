


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

```
gpio readall
```
> Response:
```python
+-----+-----+---------+------+---+---Pi 4B--+---+------+---------+-----+-----+
 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
 |     |     |    3.3v |      |   |  1 || 2  |   |      | 5v      |     |     |
 |   2 |   8 |   SDA.1 |   IN | 1 |  3 || 4  |   |      | 5v      |     |     |
 |   3 |   9 |   SCL.1 |   IN | 1 |  5 || 6  |   |      | 0v      |     |     |
 |   4 |   7 | GPIO. 7 |   IN | 1 |  7 || 8  | 1 | IN   | TxD     | 15  | 14  |
 |     |     |      0v |      |   |  9 || 10 | 1 | IN   | RxD     | 16  | 15  |
 |  17 |   0 | GPIO. 0 |   IN | 0 | 11 || 12 | 0 | IN   | GPIO. 1 | 1   | 18  |
 |  27 |   2 | GPIO. 2 |   IN | 0 | 13 || 14 |   |      | 0v      |     |     |
 |  22 |   3 | GPIO. 3 |   IN | 0 | 15 || 16 | 0 | IN   | GPIO. 4 | 4   | 23  |
 |     |     |    3.3v |      |   | 17 || 18 | 0 | IN   | GPIO. 5 | 5   | 24  |
 |  10 |  12 |    MOSI |   IN | 0 | 19 || 20 |   |      | 0v      |     |     |
 |   9 |  13 |    MISO |   IN | 0 | 21 || 22 | 0 | IN   | GPIO. 6 | 6   | 25  |
 |  11 |  14 |    SCLK |   IN | 0 | 23 || 24 | 1 | IN   | CE0     | 10  | 8   |
 |     |     |      0v |      |   | 25 || 26 | 1 | IN   | CE1     | 11  | 7   |
 |   0 |  30 |   SDA.0 |   IN | 1 | 27 || 28 | 1 | IN   | SCL.0   | 31  | 1   |
 |   5 |  21 | GPIO.21 |   IN | 1 | 29 || 30 |   |      | 0v      |     |     |
 |   6 |  22 | GPIO.22 |   IN | 1 | 31 || 32 | 0 | IN   | GPIO.26 | 26  | 12  |
 |  13 |  23 | GPIO.23 |   IN | 0 | 33 || 34 |   |      | 0v      |     |     |
 |  19 |  24 | GPIO.24 |   IN | 0 | 35 || 36 | 0 | IN   | GPIO.27 | 27  | 16  |
 |  26 |  25 | GPIO.25 |   IN | 0 | 37 || 38 | 0 | IN   | GPIO.28 | 28  | 20  |
 |     |     |      0v |      |   | 39 || 40 | 0 | IN   | GPIO.29 | 29  | 21  |
 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
 +-----+-----+---------+------+---+---Pi 4B--+---+------+---------+-----+-----+
```

- [ ]  Tesst with :snake: Python


```python
import RPi.GPIO as GPIO
import time

ledPin = 11                           # define ledPin

def setup():
   GPIO.setmode(GPIO.BOARD)
   GPIO.setup(ledPin, GPIO.OUT)
   GPIO.output(ledPin, GPIO.LOW)      # make ledPin output LOW level print ('using pin%d'%ledPin)
   print ('using pin%d'%ledPin)

def loop():
   while True:
      GPIO.output(ledPin, GPIO.HIGH)  # make ledPin output HIGH level to turn on led
      print ('led turned on >>>')     # print information on terminal
      time.sleep(1)                   # Wait for 1 second
      GPIO.output(ledPin, GPIO.LOW)   # make ledPin output LOW level to turn off led
      print ('led turned off <<<')
      time.sleep(1)                   # Wait for 1 second

def destroy():
    GPIO.cleanup()                    # Release all GPIO

if __name__ == '__main__':            # Program entrance
    print ('Program is starting ... \n')
    setup()
    try:
        loop()
    except KeyboardInterrupt:          # Press ctrl-c to end the program.
        destroy()

```

- [ ] Test with `C`

```c
#include <wiringPi.h>
#include <stdio.h>

#define ledPin 0 //define the led pin number

int main(void)
{
   printf("Program is starting ... \n"); 
   wiringPiSetup(); //Initialize wiringPi.

   pinMode(ledPin, OUTPUT);//Set the pin mode
   printf("Using pin%d\n",ledPin); //Output information on terminal 
   while(1){
      digitalWrite(ledPin, HIGH); //Make GPIO output HIGH level
      printf("led turned on >>>\n"); //Output information on terminal 
      delay(1000); //Wait for 1 second 
      digitalWrite(ledPin, LOW); //Make GPIO output LOW level
      printf("led turned off <<<\n"); //Output information on terminal 
      delay(1000); //Wait for 1 second
   }
}
```

- [ ] Compile and run

```bash
gcc Blink.c -o Blink -lwiringPi ; \
./Blink
```

# References

- [ ] [Raspberry Pi OS with desktop 64 bit Debian version: 11 (bullseye)](https://downloads.raspberrypi.org/raspios_arm64/images/raspios_arm64-2023-05-03/2023-05-03-raspios-bullseye-arm64.img.xz)
```
brew install --cask raspberry-pi-imager
```
- [ ] [GPIO and the 40-pin Header](https://www.raspberrypi.com/documentation/computers/os.html#gpio-and-the-40-pin-header)
