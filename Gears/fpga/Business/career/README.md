

# :cat:GPT [How realistic is a change of career to FPGA engineering?](https://www.reddit.com/r/FPGA/comments/smt7fm/how_realistic_is_a_change_of_career_to_fpga)

A **career switch to FPGA engineering** is *absolutely realistic* — and in 2025, it's arguably a **strategic** move, especially with your background in **SDR, embedded systems, C, and VHDL**. You’ve already got a solid foundation, and with some focused upskilling and positioning, you can absolutely pivot into the FPGA space.

Let’s break it down:

---

## 🧭 Is It Realistic? Yes — Here’s Why:

### ✅ **High Demand, Niche Skillset**
- FPGA engineers are in **short supply** compared to embedded/Linux kernel or Python devs.
- Skills like **RTL design, synthesis, timing closure**, and **hardware/software codesign** are rare and valued.

### ✅ **Low Competition**
- It’s not flooded like web/dev jobs. If you show up with *real projects* and *practical experience*, you stand out quickly.

### ✅ **Transferable Skills from Embedded/Systems**
You already likely have:
- 🧠 Embedded C/system thinking
- 🧰 Familiarity with toolchains, Linux, device trees
- ⚡ Interest in real-time systems like SDR, MIDI, O-RAN

That gives you a **huge leg up** compared to someone starting from scratch.

---

## 🧗 How Hard Is It?

| Area | Difficulty | Notes |
|------|------------|-------|
| RTL Design (VHDL/Verilog) | 🟨 Moderate | Needs practice, but similar to writing clean embedded C logic |
| Timing Closure | 🟥 Hard | Comes with experience; start with simple clock domains |
| Toolchains (Vivado, Quartus) | 🟨 Moderate | GUI-driven at first, but automation takes time |
| High-Level Synthesis (HLS) | 🟩 Easier entry | If you're strong in C/C++, this can be a fast entry point |
| Open Source FPGA tools | 🟩 Easy to get started | No license headaches, great community |

---

## 🎓 What You’d Need to Learn (or Refine)

| Skill | How to Learn It |
|-------|-----------------|
| VHDL/Verilog for synthesis | Pong Chu’s books, open projects (LiteX, TinyTapeout) |
| Timing (setup/hold, constraints) | Xilinx Timing Constraints Guide + small projects |
| FPGA tools (Vivado, Quartus, LiteX) | Use with real boards: Digilent Arty, Lattice iCEstick |
| Interface protocols (AXI, SPI, UART, I2S) | Build peripherals in simulation and hardware |
| SoC integration (soft-core CPUs) | RISC-V + LiteX or Zynq/ZynqMP + PetaLinux |
| Simulation/testbenches | GHDL, ModelSim, or Vivado Simulator |

---

## 🧪 Proof-of-Skill Projects You Could Build

These **small but powerful projects** show up great on a portfolio:

- ✅ Custom **UART or I2S peripheral** in VHDL with testbench + hardware test
- ✅ Mini SoC with **VexRiscv + SPI + Timer** (LiteX)
- ✅ SDR or DSP block: FIR filter / AM demodulator / FFT in Verilog/VHDL
- ✅ Basic VGA output controller with framebuffer
- ✅ MIDI over BLE or wireless using FPGA + soft-core

Host your projects on GitHub, demo on YouTube or LinkedIn — even a few **solid repo READMEs** go a long way.

---

## 💼 Career Entry Points

| Path | Strategy |
|------|----------|
| 👷‍♂️ **FPGA Design Engineer (Junior)** | Focus on testbenches, simulation, peripheral design |
| 🧠 **SoC/Embedded + FPGA** | Zynq or RISC-V SoC work — your embedded C + FPGA combo shines |
| 🚀 **Startup / Indie Hardware** | Build and sell FPGA-based devices (CrowdSupply, GitHub sponsorware) |
| 🧪 **Research / PhD / Labs** | Use FPGA for 5G, DSP, robotics — often open to career-changers |
| 📡 **SDR / Telecom** | Your past in OAI, SDR, and PHY layer makes this **extremely viable** |

---

## ✊ Final Thoughts

You’re not starting from zero — you’re probably already 60–70% there.

If you:
- 🔨 Build 1–2 solid FPGA projects,
- 📂 Open-source them or use them in a job app,
- 🎯 Target embedded/DSP/SDR companies…

You could **land your first FPGA job in 6–12 months**, even faster if you focus.

---

Want help picking a first "portfolio-grade" FPGA project tailored to your background?
