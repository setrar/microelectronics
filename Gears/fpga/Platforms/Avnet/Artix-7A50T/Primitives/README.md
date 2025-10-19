# FPGA Primitives

How the major **7-series FPGA primitives** are structured and connected inside the device fabric.

---

## 🧱 **Text Hierarchy Overview**

```
FPGA (7-Series)
│
├── Configuration & Control
│   ├── ICAP, FRAME_ECC, STARTUPE2, BSCAN, DNA_PORT
│   └── Clock Managers: MMCM, PLL, BUFG/BUFH/BUFR/BUFIO
│
├── Logic Fabric (CLB Columns)
│   ├── Slice (LUTs + FFs + Carry + MUXes)
│   │   ├── LUT6, LUT5, LUT3
│   │   ├── FDRE / FDCE (Flip-Flops)
│   │   ├── CARRY4
│   │   ├── MUXF7 / MUXF8
│   │   └── SRL16E / SRLC32E (Distributed RAM / Shift Reg)
│   └── Connected by Routing Switch Matrices (PIPs)
│
├── Memory Columns
│   ├── Block RAM Tiles
│   │   ├── RAMB18E1 / RAMB36E1
│   │   └── FIFO36E1
│   └── Optional BRAM controllers (soft AXI or native)
│
├── DSP Columns
│   └── DSP48E1 (MAC, multiplier, ALU, preadder)
│
├── I/O Columns
│   ├── IOB33S / IOB33M (Single-ended/Differential I/O)
│   ├── IBUF / OBUF / IOBUF / OBUFDS / IBUFDS
│   ├── ISERDESE2 / OSERDESE2 / IDDR / ODDR
│   └── IDELAYE2 / ODELAYE2
│
├── Clocking Network
│   ├── BUFGs (Global clock buffers)
│   ├── BUFH / BUFR / BUFIO (Regional / local)
│   └── Clock routing spine connects to every tile column
│
├── Transceiver Columns (optional, on high-end devices)
│   ├── GTXE2_CHANNEL / GTXE2_COMMON
│   ├── GTHE2_CHANNEL / GTHE2_COMMON
│   └── IBUFDS_GTE2 / OBUFDS_GTE2 (refclk interfaces)
│
├── Analog Block
│   └── XADC (on-chip ADC and sensors)
│
└── Embedded Processor (Zynq-7000 only)
    ├── PS7 (ARM Cortex-A9 dual-core)
    └── AXI interconnect bridges (PS↔PL)
```

---

## 🧭 **Mermaid Flowchart Representation**

```mermaid
graph LR
    A@{ shape: procs, label: "FPGA Device (7-Series)" }
    B@{ shape: procs, label: "Configuration & Control" }
    C@{ shape: procs, label: "Logic Fabric (CLBs)" }
    D@{ shape: procs, label: "Block RAM Columns" }
    E@{ shape: procs, label: "DSP Columns" }
    F@{ shape: procs, label: "I/O Columns" }
    G@{ shape: procs, label: "Clocking Network" }
    H@{ shape: procs, label: "Transceiver Columns" }
    I@{ shape: procs, label: "Analog Block" }
    J@{ shape: procs, label: "Embedded Processor (Zynq only)" }

    %% Top-level structure
    A --> B
    A --> C
    A --> D
    A --> E
    A --> F
    A --> G
    A --> H
    A --> I
    A --> J

    %% Subnodes for Configuration & Control
    B1@{ shape: rect, label: "ICAP / FRAME_ECC / DNA_PORT" }
    B2@{ shape: rect, label: "STARTUPE2 / BSCAN" }
    B3@{ shape: rect, label: "MMCM / PLL / BUFG / BUFR" }
    B --> B1 --> B2 --> B3

    %% Subnodes for Logic Fabric
    C1@{ shape: rect, label: "LUT6 / LUT5" }
    C2@{ shape: rect, label: "FDRE / FDCE (Flip-Flops)" }
    C3@{ shape: rect, label: "CARRY4 / MUXF7 / MUXF8" }
    C4@{ shape: rect, label: "SRL16E / SRLC32E" }
    C5@{ shape: rect, label: "PIPs & Routing Switches" }
    C --> C1 --> C2 --> C3 --> C4 --> C5

    %% Subnodes for BRAM
    D1@{ shape: rect, label: "RAMB18E1 / RAMB36E1" }
    D2@{ shape: rect, label: "FIFO36E1" }
    D --> D1 --> D2

    %% Subnodes for DSP
    E1@{ shape: rect, label: "DSP48E1 Blocks" }
    E --> E1

    %% Subnodes for IO
    F1@{ shape: rect, label: "IOB33S / IOB33M" }
    F2@{ shape: rect, label: "IBUF / OBUF / IOBUF / OBUFDS" }
    F3@{ shape: rect, label: "ISERDESE2 / OSERDESE2" }
    F4@{ shape: rect, label: "IDDR / ODDR / IDELAYE2 / ODELAYE2" }
    F --> F1 --> F2 --> F3 --> F4

    %% Subnodes for Clocking
    G1@{ shape: rect, label: "BUFG (Global)" }
    G2@{ shape: rect, label: "BUFH / BUFR / BUFIO (Regional)" }
    G --> G1 --> G2

    %% Subnodes for Transceivers
    H1@{ shape: rect, label: "GTXE2 / GTHE2 Channels" }
    H2@{ shape: rect, label: "IBUFDS_GTE2 / OBUFDS_GTE2" }
    H --> H1 --> H2

    %% Analog
    I1@{ shape: rect, label: "XADC Sensors" }
    I --> I1

    %% Processor
    J1@{ shape: rect, label: "PS7 ARM Cortex-A9" }
    J2@{ shape: rect, label: "AXI Interconnect" }
    J --> J1 --> J2
```

---

## 💡 Summary

Think of the **7-series architecture** as a **columnar grid**:

* [**CLBs**](CLBs) (logic) form most of the fabric.
* **BRAMs**, **DSPs**, [**IOBs**](IOBs), and **GTXs** form vertical **columns** interleaved with CLBs.
* The **clocking network** and **routing matrices** interconnect everything.
* On **Zynq**, a **Processing System (PS7)** block connects via **AXI** to the programmable logic (PL).

