# 🔷 **Logic Function Block Diagrams**

---

## **1. 74HC00 — Quad 2-Input NAND Gate**

```mermaid
graph LR
    subgraph NAND1 [ ]
        direction LR
        A1[A] --> N1[NAND]
        B1[B] --> N1
        N1 -- "≥1" --> Y1[Y]
    end

    subgraph NAND2 [ ]
        direction LR
        A2[A] --> N2[NAND]
        B2[B] --> N2
        N2 -- "≥1" --> Y2[Y]
    end

    subgraph NAND3 [ ]
        direction LR
        A3[A] --> N3[NAND]
        B3[B] --> N3
        N3 -- "≥1" --> Y3[Y]
    end

    subgraph NAND4 [ ]
        direction LR
        A4[A] --> N4[NAND]
        B4[B] --> N4
        N4 -- "≥1" --> Y4[Y]
    end

    %% Arrange subgraphs horizontally
    NAND1 --- NAND2 --- NAND3 --- NAND4
```


---

## **2. 74HC02 / 74HCT02 — Quad 2-Input NOR Gate**

```mermaid
graph LR
    subgraph NOR1 [ ]
        direction LR
        A1[A] --> N1[NOR]
        B1[B] --> N1
        N1 -- "=1" --> Y1[Y]
    end

    subgraph NOR2 [ ]
        direction LR
        A2[A] --> N2[NOR]
        B2[B] --> N2
        N2 -- "=1" --> Y2[Y]
    end

    subgraph NOR3 [ ]
        direction LR
        A3[A] --> N3[NOR]
        B3[B] --> N3
        N3 -- "=1" --> Y3[Y]
    end

    subgraph NOR4 [ ]
        direction LR
        A4[A] --> N4[NOR]
        B4[B] --> N4
        N4 -- "=1" --> Y4[Y]
    end

    %% Arrange subgraphs horizontally
    NOR1 --- NOR2 --- NOR3 --- NOR4
```

---

## **3. 74HCT04 — Hex Inverter**

```mermaid
graph LR
    subgraph NOT1 [ ]
        direction LR
        A1[A] --> N1[NOT]
        N1 --> Y1[Y]
    end

    subgraph NOT2 [ ]
        direction LR
        A2[A] --> N2[NOT]
        N2 --> Y2[Y]
    end

    subgraph NOT3 [ ]
        direction LR
        A3[A] --> N3[NOT]
        N3 --> Y3[Y]
    end

    subgraph NOT4 [ ]
        direction LR
        A4[A] --> N4[NOT]
        N4 --> Y4[Y]
    end

    subgraph NOT5 [ ]
        direction LR
        A5[A] --> N5[NOT]
        N5 --> Y5[Y]
    end

    subgraph NOT6 [ ]
        direction LR
        A6[A] --> N6[NOT]
        N6 --> Y6[Y]
    end

    %% Arrange subgraphs horizontally
    NOT1 --- NOT2 --- NOT3 --- NOT4 --- NOT5 --- NOT6
```

---

## **4. 74HC40 — Dual 4-Input NAND Gate**

```mermaid
graph LR
    subgraph NAND1 [ ]
        direction LR
        A1[A] --> N1[4-INPUT NAND ]
        B1[B] --> N1
        C1[C] --> N1
        D1[D] --> N1
        N1 --> Y1[Y]
    end

    subgraph NAND2 [ ]
        direction LR
        A2[A] --> N2[4-INPUT NAND ]
        B2[B] --> N2
        C2[C] --> N2
        D2[D] --> N2
        N2 --> Y2[Y]
    end

    %% Arrange subgraphs horizontally
    NAND1 --- NAND2
```

---

## **5. 74HC86 — Quad 2-Input XOR Gate**

```mermaid
graph LR
    subgraph XOR1 [ ]
        direction LR
        A1[A] --> X1[XOR]
        B1[B] --> X1
        X1 -- "⊕" --> Y1[Y]
    end

    subgraph XOR2 [ ]
        direction LR
        A2[A] --> X2[XOR]
        B2[B] --> X2
        X2 -- "⊕" --> Y2[Y]
    end

    subgraph XOR3 [ ]
        direction LR
        A3[A] --> X3[XOR]
        B3[B] --> X3
        X3 -- "⊕" --> Y3[Y]
    end

    subgraph XOR4 [ ]
        direction LR
        A4[A] --> X4[XOR]
        B4[B] --> X4
        X4 -- "⊕" --> Y4[Y]
    end

    %% Arrange subgraphs horizontally
    XOR1 --- XOR2 --- XOR3 --- XOR4
```

---

## **6. 74HC21 — Dual 4-Input AND Gate**

```mermaid
graph LR
    subgraph NAND1 [ ]
        direction LR
        A1[A] --> N1[4-INPUT AND ]
        B1[B] --> N1
        C1[C] --> N1
        D1[D] --> N1
        N1 --> Y1[Y]
    end

    subgraph NAND2 [ ]
        direction LR
        A2[A] --> N2[4-INPUT AND ]
        B2[B] --> N2
        C2[C] --> N2
        D2[D] --> N2
        N2 --> Y2[Y]
    end

    %% Arrange subgraphs horizontally
    NAND1 --- NAND2
```

---

# 🔷 **Buffers, MUXes, and Transceivers**

---

## **7. 74HC125 — Quad Tri-State Buffer (Active-LOW Enable)**

```mermaid
graph LR
    subgraph BUF1 [ ]
        direction LR
        EN1[EN¯] --> B1[BUF]
        A1[A] --> B1
        B1 --> Y1[Y]
    end

    subgraph BUF2 [ ]
        direction LR
        EN2[EN¯] --> B2[BUF]
        A2[A] --> B2
        B2 --> Y2[Y]
    end

    subgraph BUF3 [ ]
        direction LR
        EN3[EN¯] --> B3[BUF]
        A3[A] --> B3
        B3 --> Y3[Y]
    end

    subgraph BUF4 [ ]
        direction LR
        EN4[EN¯] --> B4[BUF]
        A4[A] --> B4
        B4 --> Y4[Y]
    end

    %% Arrange subgraphs horizontally
    BUF1 --- BUF2 --- BUF3 --- BUF4
```

```
      EN¯   A          Y
      ───►┌─────┐──►────
          │BUF  │
          └─────┘

(Each of the 4 sections is identical)
```

---

## **8. 74HC153 — Dual 4-Input Multiplexer**

```mermaid
flowchart TD
    %% MUX 2 (Channel 2)
    subgraph MUX2[" "]
        S1_2[S1] --> M2["4-TO-1 MUX<br>(Channel 2)"]
        S0_2[S0] --> M2
        I4 --> M2
        I5 --> M2
        I6 --> M2
        I7 --> M2
        M2 --> Y2[Y2]
    end

    %% MUX 1 (Channel 1)
    subgraph MUX1[" "]
        S1_1[S1] --> M1["4-TO-1 MUX<br>(Channel 1)"]
        S0_1[S0] --> M1
        I0 --> M1
        I1 --> M1
        I2 --> M1
        I3 --> M1
        M1 --> Y1[Y1]
    end
```

---

## **9. 74HC157 — Quad 2-Input Multiplexer**

```mermaid
graph LR
    %% MUX 0
    subgraph MUX0 [ ]
        direction LR
        SEL0[Select0] --> M0[MUX]
        A0[A0] --> M0
        B0[B0] --> M0
        M0 --> Y0[Y0]
    end

    %% MUX 1
    subgraph MUX1 [ ]
        direction LR
        SEL1[Select1] --> M1[MUX]
        A1[A1] --> M1
        B1[B1] --> M1
        M1 --> Y1[Y1]
    end

    %% MUX 2
    subgraph MUX2 [ ]
        direction LR
        SEL2[Select2] --> M2[MUX]
        A2[A2] --> M2
        B2[B2] --> M2
        M2 --> Y2[Y2]
    end

    %% MUX 3
    subgraph MUX3 [ ]
        direction LR
        SEL3[Select3] --> M3[MUX]
        A3[A3] --> M3
        B3[B3] --> M3
        M3 --> Y3[Y3]
    end

    %% Arrange MUX subgraphs horizontally
    MUX0 --- MUX1 --- MUX2 --- MUX3
```

```
         Select
           │
           ▼
        ┌─────────┐
 A0 ───►│         │──► Y0
 B0 ───►│  MUX    │
        └─────────┘
            ×4    (A1/B1 → Y1, etc.)
```

---

## **10. 74HC243 — Quad Bus Transceiver (3-State)**

```mermaid
graph LR
    %% Bi-directional Transceiver

    %% Control signals
    DIR[DIR] --> TR[TRANSCEIVER]
    G1[G¯] --> TR
    G2[G¯] --> TR

    %% Data paths
    A[A] -->|A→B| TR
    B[B] -->|B→A| TR
    TR --> A
    TR --> B
```

```
         DIR
     A ◄────► B
      ▲      ▲
      │      │
      │      │
     G¯      G¯  (Enable LOW)
```

Expanded single-channel view:

```
             DIR
 A ────┬─────────────► B
       │
       │  ┌────────┐
       └──│ TRANSCE │──┐  
          │        │   │
 B ───────│        │◄──┘
          └────────┘
               ▲
               │
              G¯ (ENABLE LOW)
```



---

