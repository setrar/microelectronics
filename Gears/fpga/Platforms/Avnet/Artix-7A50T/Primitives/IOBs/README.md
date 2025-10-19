# IOBs

A subtle but *important* distinction when dealing with **7-series FPGA I/O primitives**.

Let’s unpack it clearly:

---

## ⚙️ Overview: What an IOB33 Is

In Xilinx **7-series FPGAs**, every physical I/O pad is implemented using an **IOB33** tile (I/O Block for 3.3 V standards).
It can handle **single-ended** (LVCMOS, LVTTL, etc.) or **differential** (LVDS, TMDS, etc.) signaling.

Each IOB tile contains:

* An **input buffer** (IBUF path)
* An **output driver** (OBUF path)
* A **tri-state control** (T signal)
* Optional **termination and bias circuits**
* Configurable **IO standards, slew rate, drive strength, and pull resistors**

---

## 🧩 The Two Variants

| Variant    | Full Name                  | Role                                       | Used For                                                  | Connection                                                          |
| ---------- | -------------------------- | ------------------------------------------ | --------------------------------------------------------- | ------------------------------------------------------------------- |
| [**IOB33S**](IOB33S) | *I/O Block 3.3 V — Single* | **Single-ended** I/O block                 | LVCMOS, LVTTL, or as the **slave** in a differential pair | Directly to a single package pin (PAD)                              |
| **IOB33M** | *I/O Block 3.3 V — Master* | **Master** half of a **differential pair** | LVDS, TMDS, or other differential standards               | Provides shared differential biasing & control to the paired IOB33S |

---

## 🔄 How They Work Together (Differential Pair)

When you use a differential standard like **LVDS_25**, two adjacent IOBs form a pair:

```
+---------------------+        +---------------------+
|  IOB33M (Master)    | <===>  |  IOB33S (Slave)     |
|  PAD_P (positive)   |        |  PAD_N (negative)   |
|  Controls DIFFI/O   |        |  Mirrors settings   |
+---------------------+        +---------------------+
```

* **IOB33M** handles the **shared differential circuitry** (termination, reference voltage, differential buffer enable).
* **IOB33S** acts as the complementary side of that pair (its configuration links to the M tile).
* The *M* tile’s DIFFIN and DIFFOUT ports connect internally to the *S* tile.

---

## ⚡ In Single-Ended Mode

If you’re not using a differential pair, Vivado instantiates **only IOB33S** (for single LVCMOS pads).
In that case:

* The **DIFFI/O ports** are unused.
* The IOB behaves purely as a single input/output/tri-state driver.

---

## 🧠 Quick Summary Table

| Feature                       | **IOB33S**                                  | **IOB33M**                       |
| ----------------------------- | ------------------------------------------- | -------------------------------- |
| Mode                          | Single-ended, or Slave in differential pair | Master in differential pair      |
| Shared differential resources | No                                          | Yes                              |
| Typical usage                 | LVCMOS, LVTTL                               | LVDS, TMDS, LVPECL               |
| Controls DIFFI/O routing      | No                                          | Yes (drives DIFFIN/DIFFOUT nets) |
| Physical placement            | Adjacent to M tile                          | Adjacent to S tile               |
| Example                       | `IOB33S_X0Y127`                             | `IOB33M_X0Y126`                  |

---

### 🧭 Visualization

```
Fabric Signal → IOB33M (P) → PAD_P (pin)
             ↘→ IOB33S (N) → PAD_N (pin)
```

Both are physically adjacent in the I/O bank, forming a **matched differential pair** (with proper impedance and skew control).

---

### ✅ Practical Tip in Vivado

When you assign an **LVDS** I/O standard, Vivado:

* Automatically selects a **pair of IOBs**,
* Marks one as **M (master)** and the other as **S (slave)**,
* And manages the pairing constraints (you’ll see them in the `.xdc` as `DIFF_PAIR`).

You normally don’t need to instantiate these primitives manually — but understanding them helps when reading netlists, floorplans, or FPGA editor schematics (like the one you sent earlier).

