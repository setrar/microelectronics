# One Unifying Mental Model

> **Everything is just:**
>
> **Combinational logic + optional flip-flop + routing**

All the terms you listed are **packaging differences**, not fundamentally different ideas.

---

## Level 0 — Raw Digital Logic (Ground Truth)

This is the base reality.

### Primitives

* AND / OR / XOR / NOT
* Multiplexer
* Flip-flop ([D-FF](https://www.youtube.com/watch?v=YW-_GkUguMM))
* Wires
* Clock

Everything else is **bundling**.

---

## Level 1 — 74HC Logic (Discrete Era)

**What it is:**
Pre-packaged chunks of Level-0 logic.

| Chip    | What it *really* is |
| ------- | ------------------- |
| 74HC08  | 4 × AND gates       |
| 74HC32  | 4 × OR gates        |
| 74HC74  | 2 × D flip-flops    |
| 74HC157 | 4 × 2:1 mux         |
| 74HC283 | 4-bit adder         |

👉 You manually wire them together.

**Mental model:**

> *Hard-wired fixed logic blocks*

---

## Level 2 — Macrocell (Programmable 74HC-on-a-chip)

**What it is:**
A **configurable 1-bit logic slice**.

Typical macrocell:

```
Inputs → AND/OR (programmable) → D-FF → Output enable
```

This is:

* 74HC08 + 74HC32 (logic)
* 74HC74 (FF)
* 74HC125 (OE)

**Key point:**
A macrocell ≈ **one bit of stateful logic**.

---

## Level 3 — CPLD (Array of Macrocells)

**What it is:**
Hundreds to thousands of macrocells + predictable routing.

| Property    | CPLD                |
| ----------- | ------------------- |
| Logic style | Sum-of-products     |
| Timing      | Very predictable    |
| Flip-flops  | Everywhere          |
| Best for    | Control logic, glue |

**Mental model:**

> *A big pile of identical macrocells*

This is why CPLDs feel like **giant 74HC schematics**.

---

## Level 4 — CLB (FPGA Logic Block)

**What it is:**
A **more flexible macrocell**.

Typical CLB contains:

* Several LUTs (e.g. 6-input)
* Several flip-flops
* Fast carry chains
* Local routing

A LUT is just:

> a **truth table in SRAM**

So a CLB is:

> *“store any Boolean function you want”*

---

## Level 5 — FPGA (Sea of CLBs)

**What it is:**
Thousands to millions of CLBs + routing + hard IP.

| Feature     | FPGA           |
| ----------- | -------------- |
| Logic style | LUT-based      |
| Datapaths   | Very wide      |
| Timing      | Tool-dependent |
| Best for    | Datapaths, DSP |

**Mental model:**

> *A reconfigurable digital fabric*

---

# One Table to Rule Them All

| Term      | What it really is        | Scale  |
| --------- | ------------------------ | ------ |
| 74HC      | Fixed logic blocks       | Chip   |
| Macrocell | Programmable 1-bit logic | Cell   |
| CPLD      | Many macrocells          | Device |
| LUT       | Truth-table logic        | Cell   |
| CLB       | Group of LUTs + FFs      | Block  |
| FPGA      | Many CLBs                | Device |

---

## Why This Feels Confusing (But Isn’t)

Because **vendors renamed the same idea**:

* Macrocell → LUT + FF
* AND/OR plane → SRAM truth table
* Product term → LUT input
* Carry logic → fast chain

But **physics didn’t change**.

---

## The One Sentence You Should Remember

> **74HC, macrocells, CPLDs, CLBs, and FPGAs are all just different ways of packaging combinational logic + flip-flops + routing.**

Everything else is marketing and scale.

---

## How This Ties Back to *You*

Your instincts are correct because:

* You think in **bit-slices**
* You reason in **datapaths**
* You notice pipelines everywhere (Ethernet, MIPS, SDR)

That means you’re already thinking like:

* a CPLD designer
* an FPGA architect
* an ASIC floorplanner

