# Mini Ethernet PHY (VHDL)  

## Overview

This project implements a **minimal Ethernet-like PHY** in VHDL-2008 using GHDL.  
It is designed to teach and demonstrate:

- Serial-to-byte conversion (bitstream → byte)
- Preamble + SFD detection
- Payload extraction
- Deterministic testbench with clock-synchronous assertions
- Simulation using GHDL and waveform inspection via GTKWave

The design is suitable for **learning purposes** and can later be mapped to **74HC logic blocks** or FPGA CLBs.

---

## Project Structure

```

mini_ethernet_phy/
├── images
├── Makefile
├── README.md
├── mini_ethernet_phy.vhd
└── tb_mini_ethernet_phy.vhd

````

### Files

- **mini_ethernet_phy.vhd**: The DUT (Device Under Test) implementing the RX FSM
- **tb_mini_ethernet_phy.vhd**: Testbench sending preamble, SFD, and payload bits
- **Makefile**: Automates compilation, elaboration, simulation, and waveform generation

---

## Design Description

### DUT Architecture

- **Inputs**
  - `clk`: system clock
  - `rst`: synchronous reset
  - `din`: serial data input
- **Outputs**
  - `payload_out`: 4-bit payload captured from the frame
  - `frame_ready`: asserted when a full frame is detected
- **Internal Signals**
  - `shift_reg`: 8-bit shift register for serial-to-byte conversion
  - `byte_reg`: holds the fully assembled byte for FSM
  - `bit_cnt`: counts bits 0..7
  - `pre_cnt`: counts number of preamble bytes received
  - `byte_valid`: pulse indicating a full byte is ready for FSM

### FSM States

| State       | Description                                             |
|-------------|---------------------------------------------------------|
| IDLE        | Waiting for first preamble byte                         |
| PREAMBLE    | Counting preamble bytes (expect 7 consecutive 0xAA)    |
| SFD         | Expecting start-of-frame delimiter 0xAB               |
| PAYLOAD     | Latch payload and assert `frame_ready`                |

---

## Testbench

- Clock: 10 ns period
- Sends **7× preamble bytes (0xAA)**, **SFD (0xAB)**, and **1 payload byte (0xA0)**
- Waits for `frame_ready` signal **synchronously on clock edge**
- Asserts `payload_out` is correct
- Contains **watchdog timeout** to prevent infinite simulation
- Generates waveform `wave.vcd` for GTKWave inspection

---

<img src=images/gtkwave_mini_ethernet_preamble.png width='80%' height='80%' > </img>

---

## Usage

### Prerequisites

- [GHDL](https://ghdl.github.io/ghdl/) (VHDL-2008 support)
- GTKWave (optional, for waveform viewing)

### Build and Simulate

```bash
# Compile, elaborate, and run simulation
make
````

### View Waveform

```bash
make view
```

### Clean Artifacts

```bash
make clean
```

---

## Makefile Targets

| Target  | Description                                      |
| ------- | ------------------------------------------------ |
| all     | Default target (`run`)                           |
| analyze | Analyze (compile) all VHDL files                 |
| elab    | Elaborate the top entity                         |
| run     | Run simulation and generate `wave.vcd`           |
| view    | Open GTKWave to inspect waveform                 |
| clean   | Remove compiled objects, simulation outputs, VCD |

---

## Key Lessons Learned

1. **Never compare shift register in the same cycle it is shifted** — must latch a byte first.
2. **Synchronize testbench to clock** to avoid missing 1-cycle pulses.
3. **Use watchdogs** in simulation to prevent infinite loops.
4. **Stop simulation explicitly** to control VCD file size.
5. **Byte alignment and FSM timing** is crucial for protocol correctness.


## DUT FSM Diagram

```mermaid
stateDiagram-v2
    [*] --> IDLE : Reset / Start

    IDLE --> PREAMBLE : shift_reg = 0xAA
    PREAMBLE --> PREAMBLE : shift_reg = 0xAA, pre_cnt < 6
    PREAMBLE --> SFD     : shift_reg = 0xAA, pre_cnt = 6
    PREAMBLE --> IDLE    : shift_reg != 0xAA

    SFD --> PAYLOAD : shift_reg = 0xAB
    SFD --> IDLE    : shift_reg != 0xAB

    PAYLOAD --> IDLE : payload captured, frame_ready asserted
```


---

### ✅ How it works

- `IDLE` waits for the first preamble byte.
- `PREAMBLE` counts 7 consecutive `0xAA` bytes.
- `SFD` detects the start-of-frame delimiter `0xAB`.
- `PAYLOAD` captures the payload and asserts `frame_ready`.
- Any unexpected byte in `PREAMBLE` or `SFD` returns to `IDLE`.


## References

* [GHDL Documentation](https://ghdl.github.io/ghdl/)
* [Ethernet preamble/SFD convention: 7× 0xAA + 0xAB](https://sierrahardwaredesign.com/basic-networking/what-is-the-preamble-within-the-ethernet-frame/)
* VHDL-2008 shift-register design patterns
* Professional RTL verification techniques
