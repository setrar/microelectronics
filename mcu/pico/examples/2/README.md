


- [ ] [Getting started with Raspberry Pi Pico](https://projects.raspberrypi.org/en/projects/getting-started-with-the-pico)

| :hash: | Description |
|-|-|
| [:one:](README.md#one-blink-the-onboard-led) |  Blink the onboard LED |
| [:two:](README.md#two--use-digital-inputs-and-outputs) | Use digital inputs and outputs |
| [:three:](README.md#three--control-led-brightness-with--pwm) | Control LED brightness with PWM |
| [:four:](README.md#four-control-a-led-with-an-analogue-input) | Control an LED with an analogue input |


#### :one: [Blink the onboard LED](https://projects.raspberrypi.org/en/projects/getting-started-with-the-pico/5)


```python
from machine import Pin
led = Pin(25, Pin.OUT)

led.toggle()
```

<img src=images/IMG_4395.jpg width='50%' height='50%' > </img>

#### :two:  [Use digital inputs and outputs](https://projects.raspberrypi.org/en/projects/getting-started-with-the-pico/6)

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

#### :three:  [Control LED brightness with ](https://projects.raspberrypi.org/en/projects/getting-started-with-the-pico/7) [PWM](https://en.wikipedia.org/wiki/Pulse-width_modulation)

```python
from machine import Pin, PWM
from time import sleep

pwm = PWM(Pin(15))

pwm.freq(1000)

while True:
    for duty in range(65025):
       pwm.duty_u16(duty)
       sleep(0.0001)
    for duty in range(65025, 0, -1):
       pwm.duty_u16(duty)
       sleep(0.0001)
```
<img src=images/IMG_4390.jpg width='50%' height='50%' > </img>

#### :four: [Control a LED with an analogue input](https://projects.raspberrypi.org/en/projects/getting-started-with-the-pico/8)

- [ ] Turn the potentiometer and observe the output values (from >0 to 2^16)

```python
from machine import ADC, Pin
import time

adc = ADC(Pin(26))

while True:
    print(adc.read_u16())
    time.sleep(1)
```

- [ ] Turn the potentiometer and observe led 

```python
from machine import Pin, PWM, ADC

pwm = PWM(Pin(15))
adc = ADC(Pin(26))

pwm.freq(1000)

while True:
    duty = adc.read_u16()
    pwm.duty_u16(duty)
```

<img src=images/IMG_4394.jpg width='50%' height='50%' > </img>

