# ZCU706

The **HW-Z7-ZC706 REV 2.0** refers to the **Xilinx ZC706 Evaluation Kit**, Revision 2.0, manufactured by Xilinx (now part of AMD). It is a powerful development and evaluation platform based on the **Zynq-7000 All Programmable SoC**, specifically the **Zynq XC7Z045-2FFG900C**.

---

### 🔧 **Board Overview**

| Feature                     | Description                                                    |
| --------------------------- | -------------------------------------------------------------- |
| **FPGA SoC**                | Xilinx Zynq-7000 XC7Z045-2FFG900C                              |
| **Processing System (PS)**  | Dual-core ARM Cortex-A9 @ up to 1GHz                           |
| **Programmable Logic (PL)** | Artix-7 equivalent with 350K logic cells, 218K LUTs, 545 BRAMs |
| **Speed Grade**             | -2 (mid-grade performance)                                     |
| **Package**                 | FFG900 (900-pin flip-chip BGA)                                 |

---

### 🧠 **Memory Subsystem**

* **1 GB DDR3 SODIMM (32-bit) for PS**
* **1 GB DDR3 Component Memory (64-bit) for PL**
* **128 MB Quad SPI Flash (Micron)**
* **8 GB SDHC Card (supplied)**
* **EEPROM for MAC Address**

---

### 🔌 **Interfaces and Connectivity**

| Interface Type       | Details                                         |
| -------------------- | ----------------------------------------------- |
| **Ethernet**         | 1x Gigabit Ethernet PHY (Marvell 88E1116R)      |
| **USB**              | USB-JTAG, USB-UART, USB OTG (host/device)       |
| **PCIe**             | 1x PCIe Gen2 x4 (connected to PL)               |
| **FMC (HPC)**        | 1x High-Pin Count FMC connector                 |
| **HDMI**             | HDMI output via ADV7511                         |
| **SATA**             | 1x SATA 2.0 interface                           |
| **Display**          | 1x HDMI out, 1x VGA out                         |
| **Audio**            | SSM2603 codec: Line-in, Line-out, Mic-in        |
| **UART**             | 2x UARTs (1x via USB bridge, 1x PL optional)    |
| **CAN**              | Optional via PL logic                           |
| **Buttons/Switches** | 5 pushbuttons, 8 DIP switches, 4 slide switches |
| **LEDs**             | 8 user LEDs, status LEDs for power, DONE, etc.  |

---

### ⚡ **Power Architecture**

* Supplied by 12V DC input jack or PCIe connector
* On-board PMIC for multiple voltage rails
* Monitored through Power Management IC

---

### 🔍 **Debug and Configuration**

* USB-JTAG (Digilent-compatible)
* Onboard Xilinx Platform Cable logic for JTAG
* Configuration via JTAG, Quad SPI, SD card, or USB

---

### 📦 **Software Support**

* **Xilinx Tools:** Vivado Design Suite, SDK (now Vitis)
* **OS Support:** PetaLinux, Ubuntu via ARM, custom Linux via Yocto
* **Demos and Reference Designs:** HDMI, Ethernet, Linux BSP, VDMA video pipeline, etc.

---

### 🧩 **Typical Applications**

* High-performance embedded processing
* Real-time video/image processing
* Network acceleration and protocol offloading
* Signal processing (e.g., SDR, radar)
* System prototyping for Zynq-7000 SoC

---

Great comparison—both the **ZC706** and **AC701** are Xilinx/AMD development boards, but they target **very different use cases and user needs**. Here’s a deep-dive comparison between the **Zynq-7000-based ZC706** and the **Artix-7-based AC701**:

---

## 🔁 **Quick Summary**

| Feature                 | **ZC706**                                        | **AC701**                                    |
| ----------------------- | ------------------------------------------------ | -------------------------------------------- |
| **Target Device**       | Zynq-7000 SoC (XC7Z045-2FFG900C)                 | Artix-7 FPGA (XC7A200T-2FBG676C)             |
| **Processing System**   | Dual-core ARM Cortex-A9 (hard processor)         | None (FPGA-only device)                      |
| **Logic Cells**         | \~350K                                           | \~215K                                       |
| **DSP Slices**          | 900                                              | 740                                          |
| **BRAM (36Kb blocks)**  | 545                                              | 365                                          |
| **Transceivers (GTX)**  | 16 × 6.6 Gbps (via PL)                           | None                                         |
| **Target Applications** | Embedded SoC, Linux-capable systems, video, etc. | Cost-sensitive DSP, basic comms, prototyping |

---

## 🧠 **Processing Capabilities**

| Aspect        | **ZC706**                      | **AC701**                              |
| ------------- | ------------------------------ | -------------------------------------- |
| ARM Processor | Dual-core ARM Cortex-A9 (1GHz) | None                                   |
| OS Support    | PetaLinux, Ubuntu ARM, Yocto   | Baremetal soft CPUs (e.g., MicroBlaze) |
| DDR3 for PS   | 1 GB via SODIMM                | None (no hard processor)               |

---

## 🎛️ **Memory**

| Memory Type | **ZC706**               | **AC701**               |
| ----------- | ----------------------- | ----------------------- |
| PL DDR3     | 1 GB (component memory) | 1 GB DDR3 (for PL only) |
| Flash       | 128 MB QSPI             | 128 MB QSPI             |
| SD Card     | 8 GB SDHC supplied      | SD Card slot            |

---

## 🔌 **I/O & Expansion**

| Interface Type | **ZC706**                   | **AC701**                            |
| -------------- | --------------------------- | ------------------------------------ |
| FMC            | 1x HPC (High Pin Count)     | 1x HPC                               |
| HDMI           | Output (via ADV7511)        | None                                 |
| Ethernet       | 1 Gbps (Marvell PHY)        | 1 Gbps (Marvell PHY)                 |
| USB            | USB OTG, USB UART, USB-JTAG | USB-UART, USB-JTAG                   |
| PCIe           | Gen2 x4                     | None (no hard PCIe block on Artix-7) |
| Audio          | Codec onboard (SSM2603)     | None                                 |
| Display        | HDMI out + VGA out          | None                                 |
| GPIOs          | Switches, LEDs, Buttons     | Switches, LEDs, Buttons              |

---

## 🔧 **Power & Configuration**

| Feature               | **ZC706**                 | **AC701**           |
| --------------------- | ------------------------- | ------------------- |
| Power Input           | 12V jack or PCIe          | 12V jack            |
| Configuration Options | JTAG, QSPI, SD, USB       | JTAG, QSPI, BPI, SD |
| JTAG Interface        | Onboard Digilent USB-JTAG | Onboard USB-JTAG    |

---

## 📦 **Design Tools & Ecosystem**

\| Tools Used              | Vivado, Vitis, PetaLinux                  | Vivado, Vitis                               |
\| Reference Designs       | Linux BSP, HDMI pipeline, VDMA, etc.      | DDR3, Ethernet, FFT, FIR filter             |
\| Soft Processor Support  | Optional (MicroBlaze in PL)               | Yes (MicroBlaze in PL only)                 |

---

## 🧪 **Ideal Use Cases**

| Use Case                         | **ZC706**                           | **AC701**                               |
| -------------------------------- | ----------------------------------- | --------------------------------------- |
| Embedded Linux Systems           | ✅ (via ARM Cortex-A9)               | ❌ (not feasible)                        |
| Real-time Video Processing       | ✅ (HDMI, VDMA, PL DDR)              | 🚫 (no video I/O or processing blocks)  |
| Cost-sensitive FPGA development  | ❌ (High-end board)                  | ✅ (lower cost, good for training/demos) |
| Signal Processing (e.g. FIR/FFT) | ✅ (more resources, 900 DSPs)        | ✅ (adequate DSPs, limited BRAM)         |
| PCIe & High-Speed Interfaces     | ✅ (PCIe x4, FMC HPC)                | ❌ (no PCIe or SERDES transceivers)      |
| SDR/Communications Prototyping   | ✅ (good for moderate RF front ends) | 🚫 (no transceivers)                    |

---

## 💰 **Cost (Approx.)**

| Board     | MSRP (as of last known release) |
| --------- | ------------------------------- |
| **ZC706** | \~\$2,000+ USD                  |
| **AC701** | \~\$1,200 USD                   |

---

## 🧠 Conclusion

* Choose **ZC706** if you want:

  * Embedded processing + programmable logic
  * Running Linux or high-level apps
  * PCIe, HDMI, or multimedia support
  * A serious prototyping platform for SoC design

* Choose **AC701** if you want:

  * Pure FPGA logic evaluation (no processor)
  * Cost-efficient prototyping and training
  * Simple DSP/logic designs
  * FMC experimentation without high overhead

---

The **ZC706** is **not directly supported** by **Yosys**, because:

### ⚠️ Yosys does **not** support Xilinx Zynq-7000 (ZC706) officially.

Yosys is primarily focused on:

| FPGA Family                           | Support Status                                           |
| ------------------------------------- | -------------------------------------------------------- |
| Lattice iCE40                         | ✅ Fully supported via `nextpnr-ice40`                    |
| Lattice ECP5                          | ✅ Fully supported via `nextpnr-ecp5`                     |
| Xilinx 7-Series (Artix, Kintex, Zynq) | 🚧 Partial, experimental (via **SymbiFlow** / **F4PGA**) |
| Xilinx UltraScale/+                   | ❌ Not supported                                          |
| Intel/Altera                          | ❌ Not supported (proprietary toolchains only)            |

---

## 🛠️ Can you target ZC706 through **SymbiFlow (now F4PGA)**?

In theory:

* ZC706 uses **Zynq-7000 XC7Z045** – a **7-Series device**
* SymbiFlow/F4PGA **only supports a limited subset** of 7-Series chips like:

  * **Artix-7 100T** (used on the Nexys A7)
  * **Kintex-7 325T** (partial)
  * **Zynq-7000 support** is **very experimental and limited to small parts**, like the **XC7Z010**

> **XC7Z045**, the chip on ZC706, is **too large** and complex for current open-source bitstream tools.

---

## 🧾 Summary

| Feature                      | Supported for ZC706?          |
| ---------------------------- | ----------------------------- |
| Yosys (synthesis only)       | ✅ (generic Verilog synthesis) |
| nextpnr for place & route    | ❌ (not for Zynq-7000)         |
| Bitstream generation (open)  | ❌ (Zynq-7000 not supported)   |
| SymbiFlow/F4PGA full support | ❌ (no support for XC7Z045)    |

---

### ✅ You *can* still use Yosys **as a synthesizer only**, then export EDIF to Vivado, but it’s non-standard and requires manual effort.

Great question — **Project X-Ray** is an essential part of the open-source FPGA ecosystem, but its support for the **ZC706 (Zynq-7000, XC7Z045)** is **not sufficient to generate a bitstream** today.

Here’s a detailed breakdown:

---

## 🧬 **What is Project X-Ray?**

Project X-Ray is the reverse-engineering effort under the **F4PGA (formerly SymbiFlow)** umbrella that documents the **bitstream format of Xilinx 7-Series FPGAs**.

It enables:

* Bitstream generation using open tools (e.g., Yosys + nextpnr + prjxray)
* Open-source place & route (nextpnr-xilinx)
* Architecture understanding for new backends

---

## ❌ **Limitations for ZC706 / XC7Z045**

| Feature                    | Status for ZC706 (XC7Z045)                                                    |
| -------------------------- | ----------------------------------------------------------------------------- |
| Device family              | 7-Series                                                                      |
| Bitstream format           | Partially understood                                                          |
| Support in Project X-Ray   | ✅ For Artix-7 and small Kintex-7<br>❌ Not for large Zynq-7000 (e.g., XC7Z045) |
| FASM/Bitstream generation  | ❌ Not possible for ZC706                                                      |
| Routing and placement data | ❌ Incomplete or absent                                                        |

**In short:** Project X-Ray does not yet support the Zynq-7000 **PL fabric** in the **XC7Z045** chip used on ZC706. The reverse engineering of its bitstream format is not complete due to:

* The size/complexity of the device
* Lack of open documentation for Zynq's tight PS-PL integration
* Priority on smaller, more common parts (e.g., Artix-7 100T)

---

## ✅ What is Supported in Project X-Ray?

| Supported Device Examples   | Notes                                  |
| --------------------------- | -------------------------------------- |
| Artix-7 35T, 50T, 100T      | Full bitstream generation with nextpnr |
| Kintex-7 70T (partial)      | Experimental                           |
| XC7Z010 / XC7Z020 (partial) | Very limited, no full support          |

---

## 🧠 Conclusion

* **Project X-Ray is an amazing foundation**, but **ZC706 is too large and complex** to be currently supported.
* The **bitstream for XC7Z045 is not yet open**.
* You **cannot** use fully open-source tools like Yosys + nextpnr + X-Ray to **synthesize, place, route, and bitstream** for the ZC706.


# References

- [ ] [AMD Zynq™ 7000 SoC ZC706 Evaluation Kit](https://www.amd.com/en/products/adaptive-socs-and-fpgas/evaluation-boards/ek-z7-zc706-g.html)
     - [ ] Part Number: EK-Z7-ZC706-G
     - [ ] Lead Time: Discontinued
     - [ ] Device Support: Zynq 7000
