


- [ ] [How to Set Up and Program Raspberry Pi Pico W, Pico](https://www.tomshardware.com/how-to/raspberry-pi-pico-setup)


```mermaid
stateDiagram-v2
    direction LR
    [*] --> GP28 : Pin 34
    GP28 --> GND : (+)
    GND --> [*] : Pin 38
```


```python
from machine import Pin
import utime

led = Pin(28, Pin.OUT)
led.low()

while True:
   led.toggle()
   print("Toggle")
   utime.sleep(1)
```

<img src=images/IMG_4388.jpg width='50%' height='50%' > </img>

- [ ] [Getting started with Raspberry Pi Pico](https://projects.raspberrypi.org/en/projects/getting-started-with-the-pico)

```mermaid
stateDiagram-v2
    direction LR
    [*] --> GP15 : Pin 20
    GP15 --> GND : (+)
    GND --> [*] : Pin 38
```


```python
from machine import Pin, Timer
led = Pin(15, Pin.OUT)
timer = Timer()

def blink(timer):
    led.toggle()

timer.init(freq=2.5, mode=Timer.PERIODIC, callback=blink)
```

<img src=images/IMG_4390.jpg width='50%' height='50%' > </img>


```python
from machine import Pin
import time

led = Pin(15, Pin.OUT)
button = Pin(14, Pin.IN, Pin.PULL_DOWN)

while True:
    if button.value():
        led.toggle()
        time.sleep(0.5)
```

<img src=images/IMG_4391.jpg width='50%' height='50%' > </img>