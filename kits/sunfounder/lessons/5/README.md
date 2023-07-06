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
