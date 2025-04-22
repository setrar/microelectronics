# YouTube Courses

| Topic | Description |
|-|-|
| [Making logic gates from transistors](https://www.youtube.com/watch?v=sTu3LwpF6XI) [:books:](1.logic_gates) - logic_gates | This video demonstrates how to build logic gates using transistors. The presenter explains the basic operation of a transistor as a current switch and then builds several circuits, including an inverter, a NAND gate, an OR gate, and an XOR gate. The video concludes with a list of other logic gates that can be built using transistors. |
| [SR latch](https://www.youtube.com/watch?v=KM0DdEaY5sY) | Digital logic gets really interesting when we connect the output of gates back to an input. The SR latch is one of the most basic memory circuits that we can build on to make counters, registers, and all sorts of other interesting things. | 
| [D latch](https://www.youtube.com/watch?v=peCh_859q7Q) | Building on the SR latch from the previous video (   • SR latch  ), the D latch  makes it easier to store a single bit of data. |
| [D flip-flop](https://www.youtube.com/watch?v=YW-_GkUguMM) | Building on the D latch from the previous video (   • D latch  ), the D flip-flop has a "clock" input instead of an "enable" input and stores data just on the rising edge of the clock. |

## 📚 Learning Strategy

1. **Digital Logic Design** – Learn through simulation (Logisim, Quartus, Vivado).
2. **HDL Mastery** – Verilog or VHDL. Write testbenches, synthesize, simulate.
3. **FPGA Toolchain** – Vivado, Quartus, Yosys, etc. Get used to constraint files, clocking wizard, timing reports.
4. **Hands-on Projects** – Blink LED → UART interface → SPI peripheral → Soft CPU → Custom DSP core.
5. **Advanced Topics** – AXI interconnects, DMA, PCIe, HLS, partial reconfiguration.

Mastering FPGA development requires a strong foundation in several microelectronic and digital logic concepts. Here’s a breakdown of **what you need to know and why it matters**, especially when working with FPGAs:

---

### 🔧 **Core Microelectronic Concepts to Master for FPGA Development**

#### 1. **Logic Gates (AND, OR, NOT, NAND, NOR, XOR, XNOR)**
- **Why**: They’re the building blocks of all digital circuits. FPGAs synthesize HDL into a sea of logic gates.
- **Mastery**: Know truth tables, timing behavior, and how to build complex logic from simpler gates.

#### 2. **Combinational Logic**
- Includes **multiplexers**, **demultiplexers**, **encoders**, **decoders**, **adders**, etc.
- **Why**: FPGAs implement custom data paths, control logic, and arithmetic using these.
- **Example**: Designing a 4-bit ALU or priority encoder in VHDL/Verilog.

#### 3. **Sequential Logic**
- Covers **SR latches**, **D latches**, **D flip-flops**, **JK flip-flops**, **T flip-flops**.
- **Why**: FPGAs are inherently synchronous. State machines and pipelines depend on these.
- **Skills**: Understand setup/hold time, clock skew, metastability.

#### 4. **Finite State Machines (FSMs)**
- **Why**: Used for control logic, protocol handling, and decision-making blocks.
- **Know both**: Mealy and Moore machine styles.

#### 5. **Clocking and Timing Concepts**
- **Clock trees**, **clock domains**, **synchronous vs. asynchronous design**, **multicycle paths**, **metastability**, **PLL**, **MMCM**.
- **Why**: Errors here cause real-world system failures. Especially important in high-speed FPGA designs.

#### 6. **Registers, Counters, Shift Registers**
- **Why**: Used extensively in control and data pipelines.
- Know how to build synchronous/asynchronous counters, linear feedback shift registers (LFSRs), etc.

#### 7. **Memory Elements**
- **SRAM**, **ROM**, **BRAM**, **FIFO**, **Dual-Port RAM**.
- **Why**: FPGAs embed block RAMs and LUT-RAMs. Efficient memory usage = better performance.

#### 8. **Propagation Delay & Timing Diagrams**
- Understand **combinational delay**, **clock-to-Q delay**, **setup/hold margins**.
- Essential for **timing closure** and static timing analysis (STA).

#### 9. **Digital Arithmetic**
- **Binary**, **signed/unsigned**, **fixed-point**, **floating-point (optional)**, **overflow**, **carry chains**.
- **Why**: Signal processing, filters, and DSP cores use these heavily.

#### 10. **Bus Protocols and Interfacing**
- SPI, I2C, UART, AXI, AMBA, Wishbone.
- **Why**: Most FPGA projects interface with CPUs, memory, or peripherals.

---

### 🧠 Optional but Useful Microelectronic Concepts

#### 11. **CMOS Circuit Design Basics**
- Understand how logic gates are physically implemented (pull-up/pull-down, inverter chains).
- **Why**: Not directly needed for FPGA design, but helps in timing/power optimization and ASIC transition.

#### 12. **VLSI Concepts**
- Especially if planning to transition from FPGA prototyping to ASICs or want to understand synthesis/P&R deeply.

# References

- [ ] [Build an 8-bit computer from scratch](https://eater.net/8bit)

