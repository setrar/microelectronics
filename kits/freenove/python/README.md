


| | | |
|-|-|-|
| [:octocat: Freenove_Ultimate_Starter_Kit_for_Raspberry_Pi](https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_Raspberry_Pi) | | |
| [:tv: Freenove Projects Kit for Raspberry Pi [Overview]](https://www.youtube.com/watch?v=mx_lC_mLy8I) | | |

[<img src=https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_Raspberry_Pi/blob/master/List_Ultimate_RPi_Kit.jpg width=50% height=50% > </img>](https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_Raspberry_Pi/blob/master/List_Ultimate_RPi_Kit.jpg)

## :a: Starting

- [ ]  Test with :snake: Python


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


<img src=images/IMG_4405.jpg width=50% height=50% > </img>

# References

- [ ] [Raspberry Pi OS with desktop 64 bit Debian version: 11 (bullseye)](https://downloads.raspberrypi.org/raspios_arm64/images/raspios_arm64-2023-05-03/2023-05-03-raspios-bullseye-arm64.img.xz)
```
brew install --cask raspberry-pi-imager
```
- [ ] [GPIO and the 40-pin Header](https://www.raspberrypi.com/documentation/computers/os.html#gpio-and-the-40-pin-header)
- [ ] [Processing.org](https://processing.org)
```
brew install processing
```
