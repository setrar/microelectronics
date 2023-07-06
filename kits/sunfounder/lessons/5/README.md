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
m = \frac{(y_2 - y_1)}{(x_2 - x_1)} = \frac{(3.3 - 0)}{(65535 - 144)} = ( \frac{3.3}{65391} )
```

```math
y_2 - y_1 = m(x - x_1)
```

```math
y - 0 = ( \frac{3.3}{65391} ) (x - 144)
```

```math
y = \frac{3.3}{65391}x - (\frac{144 * 3.3}{65391})
```

```math
Voltage = \frac{3.3}{65391} potVal - (\frac{144 * 3.3}{65391})
```

```python
import machine
from time import sleep

potPin = 28
myPot = machine.ADC(potPin)

while True:
    potVal = myPot.read_u16()
    voltage = (3.3/65391)*potVal-(144*3.3/65391)
    print(voltage)
    sleep(.5)
```

<img src=images/python-3.3v.png width='75%' height='75%' > </img>
