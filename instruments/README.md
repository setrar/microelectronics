# Testing Instruments

| Instrument                        | Analogy                    | What it shows                                                                        | Domain           | Phase info?                  |
| --------------------------------- | -------------------------- | ------------------------------------------------------------------------------------ | ---------------- | ---------------------------- |
| **[Multimeter](multimeter)**                    | 🖼️ *Still picture*        | One static value (e.g. DC voltage, resistance)                                       | None (static)    | ❌                            |
| **[Oscilloscope](oscilloscope)**                  | 🎞️ *Video*                | Voltage changing **over time**                                                       | Time domain      | ✅ (implicitly, via waveform) |
| **Spectrum Analyzer**             | 📈 *Black-and-white movie* | Signal **amplitude vs frequency** (how much energy at each frequency)                | Frequency domain | ❌                            |
| **[VNA (Vector Network Analyzer)](vna)** | 🎬 *Full-color 3D movie*   | Both **amplitude and phase vs frequency** (complex frequency response, S-parameters) | Frequency domain | ✅                            |

### In essence:

* **Spectrum Analyzer** tells you *what frequencies* are present and *how strong* they are.
* **VNA** tells you *how a network affects signals* at each frequency — including **phase delay, reflection, and transmission** (S₁₁, S₂₁, etc.).

So if the oscilloscope is a time-domain video,
the **spectrum analyzer** is a *frequency-domain video in grayscale*,
and the **VNA** is the *full-color 3D version* that shows both magnitude and phase — i.e. **the complete story**.


# References

- [ ] Thunderscope
  - [ ] [EEVengers/ThunderScope](https://github.com/EEVengers/ThunderScope)
  - [ ] [ThunderScope: An Open Source Software Defined Oscilloscope](https://hackaday.io/project/180090-thunderscope)
