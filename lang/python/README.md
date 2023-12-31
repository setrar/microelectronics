# Testing the ADC Pins

### Hardware Setup

#### Assembly

1. Solder headers onto your  [Electret Microphone Amplifier - MAX4466 with Adjustable Gain](https://www.adafruit.com/product/1063) 

#### Wiring

The electret microphone breakout is an analog input, meaning we can connect it
to one of the ADC pins on the Raspberry Pi Pico. Make the following connections:

##### Analog Microphone

| __Adafruit Electret Microphone__ | __Raspberry Pi Pico__ |
|----------------------------------|-----------------------|
| OUT                              | ADC2 - GP28 - Pin34   |
| GND                              | Any ground pin        |
| VDD                              | 3V3(OUT)    - Pin36   |

<img src=images/IMG_0447.jpg width=50% height=50% > </img>

##### The Source Code

You can perform the `A/D` conversion in polling, interrupt & FIFO with DMA mode. The ADC conversion speed per sample is `2μs` that is `500kS/s`. The RP2040 microcontroller operates on a `48MHZ` clock frequency which comes from `USB PLL`. So, its ADC takes a `96` CPU clock cycle to perform one conversion. Therefore, the sampling frequency is :

```math
\frac{(96 x 1 )}{48 MHz} = 2 \micro s \text{ per sample (500kS/s)}
```

```python
import machine
from time import sleep

potPin = 28
myPot = machine.ADC(potPin)

while True:
    potVal = myPot.read_u16()
    print(potVal)
    sleep(.2)
```

<img src=images/IMG_0447.png width=50% height=50% > </img>


# References

- [ ] [Successive-approximation (Register) ADC (](https://en.wikipedia.org/wiki/Successive-approximation_ADC)
- [ ] [How to use ADC in Raspberry Pi Pico | ADC Example Code](https://how2electronics.com/how-to-use-adc-in-raspberry-pi-pico-adc-example-code/)
- [ ] [Fast Fourier Transform Tone Detector](https://web.engr.oregonstate.edu/~drakemil/NoteDetector.pdf)
- [ ] [Basic Microphone Circuit and Intial FFT Analysis:](https://pages.github.coecis.cornell.edu/jt658/ECE3400_Group9_2019/lab2.html)
