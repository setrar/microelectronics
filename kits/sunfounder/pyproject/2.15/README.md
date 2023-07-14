[2.15 Two Kinds of Transistors](https://docs.sunfounder.com/projects/euler-kit/en/latest/pyproject/py_transistor.html)


```python
import machine
button = machine.Pin(14, machine.Pin.IN)
signal = machine.Pin(15, machine.Pin.OUT)

while True:
    button_status = button.value()
    if button_status== 1:
        signal.value(1)
    elif button_status == 0:
        signal.value(0)
```

<img src=images/IMG_0418.jpg width=50% height=50% > </img>


# References

- [ ] [S8050 NPN Transistor](https://components101.com/transistors/s8050-transistor-pinout-equivalent-datasheet)
- [ ] [S8050 Datasheet: NPN Transistor for Low Signal Applications](https://www.ultralibrarian.com/2022/06/14/s8050-datasheet-npn-transistor-for-low-signal-applications-ulc)

The S8050 is a low voltage, high current NPN transistor that can be used as Class B push-pull amplifiers. 
S8050 is a [`bipolar junction transistor`](https://en.wikipedia.org/wiki/Bipolar_junction_transistor) where electrons are major carriers, and holes are minor carriers. 
