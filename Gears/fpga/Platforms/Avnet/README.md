# **Artix-7 50T**

The **Artix-7 FPGA AC701** and **Artix-7 50T** (as used on various dev boards like Basys 3) are both part of Xilinx's Artix-7 family, but they differ significantly in **capabilities**, **target use cases**, and **price range**.

Here's a breakdown:

---

### 📦 1. **FPGA Part Differences**

| Feature            | Artix-7 50T (XC7A50T) | Artix-7 AC701 (XC7A200T) |
| ------------------ | --------------------- | ------------------------ |
| Logic Cells        | \~52K                 | \~215K                   |
| Slices (LUT+FF)    | \~8,150               | \~33,650                 |
| DSP Slices         | 120                   | 740                      |
| Block RAM          | \~2.7 Mb              | \~13.5 Mb                |
| Clock Mgmt Tiles   | 5                     | 10                       |
| I/O Pins           | 210                   | 500+                     |
| Transceivers (GTX) | ❌ None                | ✅ 4 x GTX @ 6.6 Gbps     |

---

### 🧰 2. **Board Features**

| Feature      | 50T Dev Boards (e.g. Basys 3) | AC701                                  |
| ------------ | ----------------------------- | -------------------------------------- |
| Cost         | \~\$150–250                   | \~\$2,000                              |
| Target Use   | Education, small projects     | Serious prototyping, signal processing |
| Connectivity | PMODs, USB UART               | FMC, PCIe, Ethernet, DDR3, SFP         |
| Transceivers | ❌ No SERDES                   | ✅ Yes (for high-speed serial links)    |
| DDR Memory   | Often none or small           | ✅ DDR3 SODIMM                          |
| FMC Support  | ❌ No                          | ✅ Yes (standard HPC FMC slot)          |

---

### 🏁 3. **Use Case Suitability**

| Use Case                  | 50T           | AC701                           |
| ------------------------- | ------------- | ------------------------------- |
| Education                 | ✅ Ideal       | ❌ Overkill                      |
| Entry-level FPGA dev      | ✅ Yes         | ❌ Not cost-effective            |
| DSP-heavy designs         | ❌ Too small   | ✅ Meant for it                  |
| PCIe / Gigabit Ethernet   | ❌ Unsupported | ✅ Native support                |
| SDR / O-RAN / RF frontend | ❌ No SERDES   | ✅ Usable with FMC RF front ends |

---

### 🧠 4. **Performance Class**

* **XC7A50T**: Mid-range device, no SERDES, limited resources — good for basic FSMs, AXI peripherals, small DSP blocks.
* **XC7A200T** (on AC701): High-end Artix — more logic, real transceivers, big memory bandwidth — nearly what you'd need for embedded DSP or low-end SDR.

---

### 💡 Summary

| Want to...                                             | Go with                                                    |
| ------------------------------------------------------ | ---------------------------------------------------------- |
| Learn FPGA basics or teach HDL                         | **50T (Basys 3, Nexys A7, etc.)**                          |
| Prototype a real hardware system (DSP, PCIe, Ethernet) | **AC701**                                                  |
| Use SERDES (e.g., high-speed ADC/DAC, JESD204B, etc.)  | **AC701**                                                  |
| Build a full SDR or hardware accelerator               | **AC701** (or even ZU or Kintex/UltraScale for more power) |

# References

- [ ] [7 Series Product Tables and Product Selection Guide (XMP101)
](https://docs.amd.com/v/u/en-US/7-series-product-selection-guide)
- [ ] [Artix 7 FPGAs Data Sheet: DC and AC Switching Characteristics (DS181)](https://docs.amd.com/v/u/en-US/ds181_Artix_7_Data_Sheet)
- [ ] [UARTLite FPGA to Linux: TTY Driver + Python Access via PCIe](https://www.hackster.io/konstantin-tiutin/uartlite-fpga-to-linux-tty-driver-python-access-via-pcie-4a6fd0)
