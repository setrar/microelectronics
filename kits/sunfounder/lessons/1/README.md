:one: Raspberry Pi Pico W LESSON 1	Write Your First Program for Absolute Beginners

:a: 1st Installation

- [ ] Install [:snake: Thonny.org](https://thonny.org)

```
brew install --cask thonny
```

- [ ] Install MicroPython in `Thonny`

<img src=images/Install-Micro-Python.png width='50%' height='50%' > </img>

- [ ] Update the UF2 Bootloader on the Pico Pi

<img src=images/Install-Micro-Python-UF2-bootloader.png width='50%' height='50%' > </img>

- [ ] Select the Pico Pi on Thonny

<img src=images/Select-Micro-Python,png.png width='50%' height='50%' > </img>

:b: Testing

```python
from machine import Pin
myLED=Pin('LED',Pin.OUT)
myLED.value(0)
```

