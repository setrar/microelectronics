:five: [Raspberry Pi Pico W LESSON 5: Reading Analog Voltages Using a Potentiometer](https://youtu.be/ODWwErH_iGA)


```python
import machine
from time import sleep

potPin = 28
myPot = machine.ADC(potPin)

while True:
    potVal = myPot.read_u16()
    print(potVal)
    sleep(.5)
```

```math

m = \frac{(y_2 - y_1)}{(x_2 - x_1)} = \frac{(3.3 - 0)}{(65535 - 144)}

```
