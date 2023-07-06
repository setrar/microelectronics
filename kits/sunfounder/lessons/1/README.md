:one: Raspberry Pi Pico W LESSON 1	Write Your First Program for Absolute Beginners

- [ ] Install [:snake: Thonny.org](https://thonny.org)

```
brew install --cask thonny
```

- [ ] Install MicroPython in `Thonny`

<img src=images/Install-Micro-Python.png width='50%' height='50%' > </img>

- [ ] Update the UF2 Bootloader on the Pico Pi

<img src=images/Install-Micro-Python-UF2-bootloader.png width='50%' height='50%' > </img>

- [ ] 

<img src=images/Select-Micro-Python,png.png width='50%' height='50%' > </img>

```python
from machine import Pin
myLED=Pin('LED',Pin.OUT)
myLED.value(0)
```

# References

- [ ] [Getting started with Raspberry Pi Pico](https://projects.raspberrypi.org/en/projects/getting-started-with-the-pico)
