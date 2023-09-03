# Oscilloscope

[Digilent: Analog Discovery 3](ad3)


# References

- [ ] [Electronics Foundations: Basic Circuits](https://www.linkedin.com/learning/electronics-foundations-basic-circuits/what-is-an-oscilloscope-14154695)
- [ ] [Nyquist Sampling Theorem: Conserving Signal Characteristics](https://resources.ema-eda.com/home/2023-nyquist-sampling-theorem-conserving-signal-characteristics)

What is an oscilloscope?

> Bandwith: 
- Range of frequencies that can be measured
- 10 MHz to 100 MHz recommended

> Sampling Rate: (for Digital Oscilloscope)
- Home many times per second the signal is measured
- Recommended at least 100 [MS/s](https://www.analog.com/en/design-center/glossary/msps.html)  (Mega [Million] Samples per seconds)

- [ ] [Expand this book for more information on digitizer fundamentals.](https://www.ni.com/docs/en-US/bundle/ni-scope/page/digitizers/fundamentals.html)

- Bandwidth
- Flatness
- Resolution
- [Sample Rate](https://www.ni.com/docs/en-US/bundle/ni-scope/page/digitizers/sample_rate.html)


```math
\begin{gather}
  \text{MS/s (Mega [Million] Sample per Seconds) } \to 1 * 10^6 \text{ Samples per seconds} \\
  1 \mu s \text{(micro seconds)} \to 1 * 10^{-6} seconds
  
\end{gather}
```

> The following figure illustrates a 1 MHz sine wave sampled by a 2 MS/s ADC and a 20 MS/s ADC.

> The faster ADC digitizes 20 points per cycle of the input signal compared with 2 points per cycle with the slower ADC. 
<img src=images/loc_eps_sample_rate.gif width=50% height=50% > <img>

- Record Length
- Vertical Range and Offset
- Input Coupling
- Impedance and Impedance Matching
- Probes and Their Effects
- Accuracy
- Noise
- Thermal Shutdown
- Triggering
- Clocking
- Time Stamping
  
---

- [ ] [Oscilloscope Music - Pictures from Sound](https://www.youtube.com/watch?v=ZaTuFB5QXHo)
- [ ] [oscilloscopemusic.com](https://oscilloscopemusic.com/)
- [ ] [What is Osci Music???](https://www.youtube.com/watch?v=qUOAYvdiHFk) (With Audacity explanation)
- [ ] [Oscilloscope! by Hansi Raber](https://oscilloscopemusic.com/software/oscilloscope/)

```
brew install oscilloscope
```

---

- [ ] [#1099 How I learned electronics](https://www.youtube.com/watch?v=Bgrubw6B_us)

- [ ] [Tektronix](https://www.tek.com/)
- [ ] [10 Reasons Every Hobbyist needs an Oscilloscope](https://www.hackster.io/news/10-reasons-every-hobbyist-needs-an-oscilloscope-507df34f38d9)

- [ ] [:tv: How to use an oscilloscope / What is an oscilloscope / Oscilloscope tutorial](https://www.youtube.com/watch?v=CzY2abWCVTY)

