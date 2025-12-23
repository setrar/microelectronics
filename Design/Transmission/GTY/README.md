```mermaid
flowchart LR
    A[FPGA Fabric Logic<br/>(Digital)] -->|Parallel bits| B[GTY Transceiver Block]

    subgraph FPGA["FPGA Silicon"]
        A
        subgraph GTY["GTY (Mixed-Signal / Analog)"]
            B1[Serializer]
            B2[PLL / CDR]
            B3[Pre-emphasis]
            B4[TX/RX Equalization]
            B5[CML Drivers & Receivers]

            B1 --> B2 --> B3 --> B4 --> B5
        end
    end

    B5 -->|High-speed differential<br/>analog waveform| C[PCB Differential Pair<br/>(100Ω)]

    C --> D[SFP+ Module]

    subgraph SFP["SFP+ Transceiver"]
        D1[Electrical Front-End (SFI)]
        D2[Optical / DAC Conversion]
        D3[Laser or Copper Driver]

        D1 --> D2 --> D3
    end

    D --> D1
```
