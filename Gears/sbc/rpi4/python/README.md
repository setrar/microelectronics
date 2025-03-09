# :snake: Python


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


<img src=../images/IMG_4405.jpg width=50% height=50% > </img>
