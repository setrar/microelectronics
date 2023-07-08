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

- [ ] Calculating the [Rate of Change](https://www.varsitytutors.com/hotmath/hotmath_help/topics/rate-of-change)


```math
\text{ slope } = \frac{\text { rise }}{\text { run }} \to \text{ rate of change } = \frac{\text {change in y}}{\text {change in x}}
```

```math
\text{ rate of change } = \frac{\text {change in volts (max 3.3v, min 0v)}}{\text {change in potentiometer reading at (max and min)}}
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

<img src=images/IMG_4392.jpg width='50%' height='50%' > </img>

