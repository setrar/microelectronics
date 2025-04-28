# FPGA

| **FPGA** | **eFPGA** | **FPGA Chiplet** |
|:---|:---|:---|
| Full, standalone programmable chip. | Small programmable block *inside* another ASIC. | Small FPGA **die** mounted as a **separate mini-chip** inside a multi-chip package. |
| Example: Xilinx Artix-7, Lattice iCE40. | Example: Flex Logix EFLX block inside an SoC. | Example: AMD/Xilinx Versal FPGAs with "AI Engine" chiplets. |
| You buy a complete FPGA device. | You tape out your ASIC with eFPGA inside. | Companies combine chiplets (FPGA + CPU + Memory) into one "super chip." |

---

### ✨ Simple image:
- **FPGA** = A house you bought, already built.
- **eFPGA** = An extra flexible room *built inside* your house.
- **FPGA Chiplet** = You ordered a **whole small house**, *built separately*, *then glued* into your big house.

---

### 🔥 FPGA Chiplet idea:
- **Chiplets** are *modular dies* manufactured independently and connected together inside a package (using advanced packaging like **2.5D interposers** or **3D stacking**).
- Instead of designing a single giant chip (which becomes very expensive and hard), you design smaller specialized dies (CPU chiplet, FPGA chiplet, AI chiplet) and combine them.
- **Example**: AMD uses CPU + GPU + IO chiplets in Ryzen; similarly, Xilinx's Versal Adaptive SoCs use "programmable logic chiplets" connected to fast NoCs.

---

### ⚡ Advantages of FPGA chiplets:
- Faster time to market: reuse old designs.
- Better yield: small dies are easier and cheaper to manufacture.
- Heterogeneous system: mix FPGA logic, CPU cores, accelerators, memory controllers as you like.
- Lower power and cost at very high performance.

---

### 📸 Quick comparison:

| FPGA Monolith | FPGA Chiplet |
|:---|:---|
| Big single die (large FPGA). | Multiple small dies combined (small FPGA block + CPU + others). |
| Limited scaling beyond ~600mm² die size. | Easier to scale: mix & match chiplets. |
| Expensive if any manufacturing defect. | Higher yield (defect in one chiplet doesn’t waste everything). |

---

### 🚀 To summarize:
> **Chiplet FPGA** = A piece of FPGA inside a modular system — but **still** a full FPGA **die** (not like an eFPGA, which is soft IP).

Good — you're asking exactly the right questions at the cutting edge!  
Let’s explain carefully:

---

## 🧠 What is **eFPGA Hard IP**?

- **eFPGA** = **embedded FPGA**: a small programmable fabric that sits *inside* your ASIC.
- **Hard IP** = **pre-designed, pre-verified silicon layout** (GDSII), **not** just code or schematics.

Thus:

> **eFPGA Hard IP** = A *physically ready*, *fixed size*, *hardwired* block of programmable logic that you can **drop into your chip** during tape-out, just like adding a memory block or PCIe controller.

---
## 🏗 How it's different from other IPs:

| **Soft IP** | **Hard IP** |
|:---|:---|
| HDL description (Verilog/VHDL). | Physical, placed-and-routed layout (GDSII/LEF/DEF). |
| Needs synthesis + place & route. | Ready to place into your floorplan directly. |
| Can be resized, customized. | Fixed size, fixed performance (but verified). |
| Example: Open-source UART IP core. | Example: ARM Cortex-A53 core from ARM as Hard IP. |

Same logic for **eFPGA**:  
- **Soft eFPGA IP**: you *synthesize* an RTL of programmable logic.
- **Hard eFPGA IP**: you *get a block* that has routing, LUTs, configuration circuits, timing models already optimized.

---

## ⚡ Why eFPGA Hard IP matters
- It **saves you months** of work (no need to verify timing, DRC/LVS).
- It guarantees **known performance and area** at specific process nodes (like TSMC 7nm, 16nm, GF22FDX, etc).
- You can **program it after chip fabrication**, inside your ASIC, similar to how you program a normal FPGA.
- You **don't** need a separate FPGA chip → saves cost, power, board space.

---

## 🔥 Real-world eFPGA Hard IP providers:
| Company | eFPGA Hard IP Product | Notes |
|:---|:---|:---|
| **Flex Logix** | EFLX | Big player. Hard IP for TSMC 40nm, 28nm, 16nm, 7nm. |
| **QuickLogic** | ArcticPro | Open-source toolchain ("QuickLogic Symbiflow") + Hard IP. |
| **Achronix** | Speedcore | High-end hardened eFPGA blocks for accelerators. |
| **Menta** | eFPGA IP | Fully customizable, can provide Hard IP versions too. |

---

## 🛠️ So in practice:

**You are taping out an SoC**, and you tell the fab:

- "I want to insert an eFPGA Hard IP here: 1,000 LUTs, 4 DSPs, 32 IOs, timing closure guaranteed at 500MHz."
- They put the pre-verified physical design block inside your chip layout.
- After your ASIC is manufactured, you can **reprogram** that eFPGA at runtime!

---

# ✍ Final Summary
> **eFPGA Hard IP** = A ready-made, silicon-verified, embedded FPGA block that you can physically drop into your ASIC layout, saving time, cost, and enabling post-silicon programmability.

---


## Research

- [ ] [Which are the best universities for FPGA related research](https://www.quora.com/Which-are-the-best-universities-for-FPGA-related-research)

The University of Toronto has engaged in collaborations with EURECOM, a research and higher education institution based in France, particularly in areas related to telecommunications, signal processing, and network systems. While specific details on FPGA-related projects may vary, here are some general aspects of the collaboration:

### Areas of Collaboration
- **Telecommunications**: Joint research on optimizing FPGA implementations for communication protocols and network systems.
- **Signal Processing**: Development of advanced algorithms for signal processing tasks that can be accelerated using FPGAs.
- **Embedded Systems**: Collaborative projects focusing on the integration of FPGA technology in embedded system designs for various applications.

### Research Outcomes
- Collaborative publications in conferences and journals, showcasing advancements in FPGA architectures and applications.
- Sharing of resources and expertise between the two institutions to enhance research quality and innovation.

For more specific details or updates on ongoing projects, it is advisable to refer to the respective institutions' publications or announcements.

While I can't provide real-time updates, here are some professors from the University of Toronto and EURECOM known for their work in areas likely to involve FPGA research and collaboration:

### University of Toronto
1. **Prof. Edward Yang**
   - Focus: Computer architecture, including FPGA design and applications.
   
2. **Prof. J. Zico Kolter**
   - Focus: Machine learning and optimization, often applying FPGAs for efficient computation.

3. **Prof. Ali Farhadi**
   - Focus: Computer vision and machine learning, with potential FPGA applications.

### EURECOM
1. **Prof. Hervé Sizun**
   - Focus: Wireless communications and signal processing, often utilizing FPGAs.

2. **Prof. Philippe Godlewski**
   - Focus: Networking and communication systems, including hardware implementations.

### Collaboration
These professors might collaborate on projects involving FPGA technologies in telecommunications, embedded systems, and signal processing. For the most accurate and current information, checking their individual web pages or recent publications is recommended.

- [ ] [[Pico ICE]](pico-ice) by :shark: [Pico ICE Tiny Vision](https://pico-ice.tinyvision.ai)

## Hardware Related Stuff

- [ ] [Ettus Research USRP FPGA HDL Source](https://github.com/EttusResearch/fpga)
- [ ] [myriadrf](https://myriadrf.org)
- [ ] [Welcome to the SoapySDR project](https://github.com/pothosware/SoapySDR/wiki)

## OpenCL

- [ ] [Efficient SIMD Vectorization for Hashing in OpenCL](https://openproceedings.org/2018/conf/edbt/paper-330.pdf)
- [ ] [OpenCL RISC-V](https://carrv.github.io/2021/papers/CARRV2021_paper_36_Blaise.pdf)

FPGA

* [FPGA engineer salaries](https://www.reddit.com/r/FPGA/comments/vf9pmh/fpga_engineer_salaries/)

* Lattice [Curated List](https://github.com/kelu124/awesome-latticeFPGAs)
* [FPGA4Fun](https://www.fpga4fun.com/) 

* LimeSDR - An open, full-duplex, USB stick software defined radio
  - [ ] [LimeSDR](https://www.crowdsupply.com/lime-micro/limesdr)
  - [ ] [LimeSDR Mini 2.0](https://www.crowdsupply.com/lime-micro/limesdr-mini-2)

- [ ] [Intro to Digital Electronics and FPGAs](https://www.youtube.com/watch?v=-qpfv8KLXOk)
  - [ ] [Programming an FPGA](https://learn.sparkfun.com/tutorials/programming-an-fpga)

- [ ] [Exploring FPGA - The Retro Desk :tv: (Youtube Playlist)](https://www.youtube.com/playlist?list=PLPSrOWYluVLJxqlrWqjZWQ1B4bBgrQ42G)
  - [ ] [Documentation for Chinese ALTERA Cyclone IV EP4CE6 FPGA Development Board](https://github.com/SlithyMatt/Altera-Cyclone-IV-board-V3.0)

- [ ] [Elektor TV : Hello FPGA – Getting Started with Microchip FPGAs](https://youtu.be/zcaZxu010cg)

HDL - Languages

- [ ] [Innovate by reaching for the open source FPGA tooling](https://f4pga.org)
- [ ] ["FPGA Design with Chisel" - Josh Bassett (LCA 2021 Online)](https://www.youtube.com/watch?v=Wst8IoYRWKo)
  - [ ] [DodonPachi board reverse engineerin](https://en.wikipedia.org/wiki/DoDonPachi)
- [ ] [Chisel/FIRRTL Hardware Compiler Framework](https://www.chisel-lang.org/)
- [ ] [Digital Design with Chisel by Martin Schoeberl](https://github.com/schoeberl/chisel-book)
- [ ] [Chisel Lab](https://github.com/schoeberl/chisel-lab)
- [ ] [:octocat: Raspberry Pi PICO board + Lattice iCE40 FPGA's](https://github.com/tinyvision-ai-inc/pico-ice)
- [ ] [Clash: A modern, functional, hardware description language](https://clash-lang.org/)

Testing 

- [ ] [osvvm](https://osvvm.org/) Open Source VHDL Verification Methodology™ (OSVVM™) is VHDL’s answer to SystemVerilog’s UVM.

:tv: Digi-Key

- [ ] [Introduction to FPGA Part 1 - What is an FPGA? | Digi-Key Electronics](https://www.youtube.com/watch?v=lLg1AgA2Xoo&list=PLEBQazB0HUyT1WmMONxRZn9NmQ_9CIKhb)

:electric_plug: Hardware

## :star: Development Boards (Kits)

- [ ] [MPFS-ICICLE-KIT-ES DEVELOPMENT KIT, POLARFIRE S](https://canada.newark.com/microchip/mpfs-icicle-kit-es/development-kit-polarfire-soc/dp/45AJ6163) $1,065.66
- [ ] [Cheap FPGA Development Boards](https://joelw.id.au/FPGA/CheapFPGADevelopmentBoards)
- [ ] [An FPGA Developer's Guide to Cheap Development Boards](https://hackster.io/news/an-fpga-developer-s-guide-to-cheap-development-boards-8f1782bb271a)


## 🥇 [Future prospects of the industry](https://www.reddit.com/r/FPGA/comments/1191ec0/future_prospects_of_the_industry)


You are asking a question about economics, not technology. For traditional FPGAs, the trends are:

1. High-end competition (ASICs) gets more expensive over time, and

1. The capabilities of "midrange" or "low cost" FPGAs improve generation over generation, but

1. Low-end competition (ARM SoCs) also get more capable over time.

As long as (1) and (2) occur faster than (3), the ecosystem niche occupied by FPGAs keeps growing. As usual, this is a great read: [https://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=7086413]

That's the view on traditional FPGAs - but all of the really interesting high-end action is heterogenous, i.e. SoC FPGAs, RFSoCs, datacentre accelerators, etc. We're seeing a Cambrian explosion of diversity in silicon, which means Intel/AMD have to make huge technological bets. For those of us who use the silicon that results, it's an exciting time to work in the sector.


# References
- [ ] [	LTESniffer – An Open-Source LTE Downlink/Uplink Eavesdropper (github.com/syssec-kaist)](https://news.ycombinator.com/item?id=35952206)
- [ ] [USRP](https://www.ettus.com/sdr-software/uhd-usrp-hardware-driver)
- [ ] [GnuRadio](https://www.ettus.com/sdr-software/gnu-radio/)
- [ ] [Next Generation FPGAs for Electronic Warfare Systems - April 1, 2016](https://www.mobilityengineeringtech.com/component/content/article/adt/pub/features/articles/24386)
- [ ] [Safran: HIGH ACCURACY TIMING IP CORE (HATI) FPGA CORE ENABLING SUB-NANOSECOND SYNCHRONIZATION](https://safran-navigation-timing.com/product/high-accuracy-timing-ip-core-hati)
- [ ] [What Is the Difference between NI and Ettus Research USRP Devices?](https://www.ni.com/en-ca/shop/wireless-design-test/what-is-a-usrp-software-defined-radio/what-is-the-difference-between-ni-and-ettus-usrps.html)
- [ ] [Next Generation FPGAs for Electronic Warfare Systems](https://www.mobilityengineeringtech.com/component/content/article/adt/pub/features/articles/24386)
- [ ] [Wikipedia : RISC-V](https://en.wikipedia.org/wiki/RISC-V)
- [ ] [Getting Started in Kicad](https://docs.kicad.org/7.0/en/getting_started_in_kicad/getting_started_in_kicad.html)
- [ ] [First RISC-V-Based System-on-Chip (SoC) FPGA Enters Mass Production](https://www.microchip.com/en-us/about/news-releases/products/first-risc-v-based-system-on-chip-fpga-enters-mass-production)
- [ ] [IceStick FPGA Tutorial #FPGA #RISCV @BrunoLevy0](https://blog.adafruit.com/2021/01/28/icestick-fpga-tutorial-fpga-riscv-brunolevy01/)
- [ ] [BrunoLevy/learn-fpga IceStick Tutorial](https://github.com/BrunoLevy/learn-fpga/blob/master/FemtoRV/TUTORIALS/IceStick.md)
- [ ] [So what's the deal with CHISEL, and why is it so great?](https://www.reddit.com/r/FPGA/comments/wnnhb8/so_whats_the_deal_with_chisel_and_why_is_it_so/)
- [ ] In computer science, [register transfer language (RTL)](https://en.wikipedia.org/wiki/Register_transfer_language)  is a kind of  [Intermediate Representation (IR)](https://en.wikipedia.org/wiki/Intermediate_representation) that is very close to assembly language, such as that which is used in a compiler.
- [ ] [How Do I Get a Job in FPGA?](https://digilent.com/blog/how-do-i-get-a-job-in-fpga/)
- [ ] [MEE10203 - Programmable Electronics](https://www.youtube.com/playlist?list=PL_N6Mn2-rIULhuVNHMpjmmKMYafQjaCZX)
- [ ] [Three Ages of FPGAs: A Retrospective on the First Thirty Years of FPGA Technology](https://ieeexplore.ieee.org/document/7086413)
- [ ] [Future of FPGA](https://www.maven-silicon.com/blog/future-of-fpga/)
- [ ] [The nextpnr FOSS FPGA place-and-route tool](https://media.ccc.de/v/35c3-9612-the_nextpnr_foss_fpga_place-and-route_tool)

- [ ] [1978: PAL User-Programmable Logic Devices Introduced](https://www.computerhistory.org/siliconengine/pal-user-programmable-logic-devices-introduced/)
- [ ] [Vaughn Betz: Crossroads FPGA Seminar: Verilog to Routing (VTR) A Flexible CAD Flow to Explore FPGA Architectures](https://www.youtube.com/watch?v=lQ1RKbEJZmE)

