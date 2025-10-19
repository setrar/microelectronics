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
graph TD
    A[FPGA Device 7-Series] --> B[Configuration & Control]
    A --> C[Logic Fabric (CLBs)]
    A --> D[Block RAM Columns]
    A --> E[DSP Columns]
    A --> F[IO Columns]
    A --> G[Clocking Network]
    A --> H[Transceiver Columns]
    A --> I[Analog Block]
    A --> J[Embedded Processor - Zynq only]

    B --> B1[ICAP / FRAME_ECC / DNA_PORT]
    B --> B2[STARTUPE2 / BSCAN]
    B --> B3[MMCM / PLL / BUFG / BUFR]

    C --> C1[LUT6 / LUT5]
    C --> C2[FDRE / FDCE - Flip-Flops]
    C --> C3[CARRY4 / MUXF7 / MUXF8]
    C --> C4[SRL16E / SRLC32E]
    C --> C5[PIPs & Routing Switches]

    D --> D1[RAMB18E1 / RAMB36E1]
    D --> D2[FIFO36E1]

    E --> E1[DSP48E1 Blocks]

    F --> F1[IOB33S / IOB33M]
    F --> F2[IBUF / OBUF / IOBUF / OBUFDS]
    F --> F3[ISERDESE2 / OSERDESE2]
    F --> F4[IDDR / ODDR / IDELAYE2 / ODELAYE2]

    G --> G1[BUFG (Global)]
    G --> G2[BUFH / BUFR / BUFIO (Regional)]

    H --> H1[GTXE2 / GTHE2 Channels]
    H --> H2[IBUFDS_GTE2 / OBUFDS_GTE2]

    I --> I1[XADC Sensors]

    J --> J1[PS7 ARM Cortex-A9]
    J --> J2[AXI Interconnect]
```

---

## 💡 Summary

Think of the **7-series architecture** as a **columnar grid**:

* **CLBs** (logic) form most of the fabric.
* **BRAMs**, **DSPs**, **IOBs**, and **GTXs** form vertical **columns** interleaved with CLBs.
* The **clocking network** and **routing matrices** interconnect everything.
* On **Zynq**, a **Processing System (PS7)** block connects via **AXI** to the programmable logic (PL).

---

Would you like me to extend this diagram to show **dataflow paths** (e.g., fabric → IOB → pad, or fabric → DSP → BRAM)? It helps when you’re designing a SoC-like subsystem (e.g., MicroBlaze + AXI + DDR).

