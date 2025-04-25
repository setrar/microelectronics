# [MMIC](https://en.wikipedia.org/wiki/Monolithic_microwave_integrated_circuit)


A key concept when you’re choosing between building RF circuits from scratch or using integrated solutions.

---

### **What are discrete transistors?**

**Discrete transistors** are standalone transistor devices packaged individually — not part of an integrated circuit. You can buy them like Lego blocks and design your own amplifiers, mixers, oscillators, etc. They’re used when you want:

- Maximum design flexibility
- Better thermal handling
- Lower parasitic coupling (in some cases)
- High-power RF performance

**Common discrete transistor types for RF:**

| Type | Use |
|------|-----|
| **BJT (Bipolar Junction Transistor)** | Older RF designs, still good at lower GHz |
| **MOSFET** | Used in switching and sometimes RF amps |
| **GaAs FET** | Low noise figure, high frequency |
| **GaN HEMT** | High power, high frequency, very robust |
| **SiGe HBT** | Great for mmWave and high linearity applications |

---

### **What is an MMIC?**

**MMIC** = **Monolithic Microwave Integrated Circuit**  
It’s a complete RF function (e.g., LNA, mixer, switch) built as an **integrated circuit** on a single semiconductor die (like GaAs, GaN, or SiGe).

- You **buy an MMIC** to perform a job: amplify, mix, filter, etc.
- Much smaller footprint
- More consistent performance
- Usually optimized for cost, power, and frequency range

Examples:
- Analog Devices HMC-series
- Qorvo and Skyworks LNAs, PAs
- Mini-Circuits MMIC amplifiers

---

### **Discrete transistor vs. MMIC — Summary Table**

| Feature | Discrete Transistor | MMIC |
|--------|----------------------|------|
| **Design effort** | High (you design circuit) | Low (just design matching network) |
| **Size** | Larger (PCB space) | Tiny footprint |
| **Frequency range** | Wide, customizable | Optimized per part |
| **Thermal handling** | Often better | Depends on package |
| **Flexibility** | Maximum | Limited to built-in function |
| **Ease of use** | Harder | Plug-and-play (relatively) |

---

### **When to use which?**

- **Use discrete transistors** if:
  - You’re building custom circuits from scratch (e.g. learning, prototyping, ultra-specific performance needs)
  - You want to experiment with different topologies (as in Razavi's examples)
  - You need very high power / heat dissipation

- **Use MMICs** if:
  - You want rapid development
  - You don’t need full control over internal transistor-level behavior
  - Size and repeatability matter

Short version: **very hard — but possible, depending on what you mean by “make my own MMIC.”**

Let’s break it down based on what you’re trying to do:

---

### **1. If you mean: “Can I implement MMIC functionality (like an LNA or mixer) *inside an SoC/FPGA*?”**

**Answer:**  
No — **not in the analog RF sense**.

- MMICs are analog, high-frequency **microwave** circuits that operate in the physical world with **transistors, capacitors, and resistors** on specialized semiconductor processes (e.g., GaAs, GaN, SiGe).
- FPGAs and SoCs are **digital or mixed-signal** systems; they can’t perform true analog RF amplification or mixing.
- Even if the FPGA has **high-speed transceivers**, they are designed for digital signals (e.g., SerDes, JESD204B), not analog RF waveforms.

So, you **can’t build an LNA or analog mixer** inside an FPGA fabric.

---

### **2. If you mean: “Can I simulate or approximate RF functions digitally in an FPGA?”**

**Answer:**  
Yes — **that’s what RFSoCs like the ZCU670 are built for.**  
You can implement:

- **Digital downconversion (DDC)** — complex mixers in the digital domain
- **Digital filtering** — CIC, FIR, etc.
- **Modulators / Demodulators** — QAM, PSK, etc.
- **Digital PLLs / NCOs**

In this case, you're not building a MMIC, but you're building **digital signal processing blocks that complement or replace analog RF functions.**

---

### **3. If you mean: “Can I design my own MMIC on silicon, like in a custom chip?”**

**Answer:**  
Yes, but that’s full-on **RFIC or MMIC chip design**, which is a specialized field requiring:

- **Analog/RF IC design skills** (very different from digital/RTL design)
- Tools like **Cadence Virtuoso** for schematic/layout
- Access to foundry PDKs (e.g., from TSMC, GlobalFoundries, Wolfspeed)
- A fab that supports RF-friendly processes (like **GaAs, SiGe, or GaN**)

This is what RFIC engineers do in companies like Qualcomm, Skyworks, or Analog Devices. Usually involves taping out in **CMOS RF**, **SOI**, or **III-V** processes.

---

### **4. Can I integrate an MMIC-like function alongside an FPGA?**

Yes, and this is common:

- You can integrate MMICs or discrete analog RF front-ends **on the same PCB** with an FPGA (like the ZCU670).
- You use the FPGA/SoC for digital DSP, control, beamforming, etc.
- The analog MMICs do the LNA/PA/mixer work, and interface with the RFSoC’s high-speed ADCs and DACs.

---

### **TL;DR**

| Goal | Feasibility | Notes |
|------|-------------|-------|
| Build analog MMIC inside FPGA | ❌ Not possible | FPGAs can’t do analog RF |
| Digitally emulate RF in FPGA | ✅ Yes | Mixers, filters, etc. |
| Design actual MMIC chip | ✅ (Very hard) | Needs analog IC design tools & skills |
| Use MMIC + FPGA on same board | ✅ Yes | Standard in SDR/RF front-ends |

---

If you're curious about trying MMIC design for real, there are academic PDKs (like the **Skywater SKY130** for CMOS, or Wolfspeed for GaN) — and you can run analog sims with **ngspice** or **Xyce**, or go all-in with **Cadence** and **ADS** if you can access them.

# References

- [ ] [ADF5901: 24 GHz VCO and PGA with 2-Channel PA Output](https://www.analog.com/en/products/adf5901.html)
- [ ] [EVAL-RADAR-MMIC: Evaluation Board for the ADF5901, ADF5904, and ADF4159 Chipset for a 24 GHz FMCW Radar](https://www.analog.com/en/resources/evaluation-hardware-and-software/evaluation-boards-kits/eval-radar-mmic.html)
