# **IOB33S**

<img src=images/IOB33S.png width='50%' height='50%' > </img>

This schematic represents a **Xilinx I/O Block (IOB)** — specifically an **IOB33S** (Single-ended I/O Block for 3.3 V standards) tile from a **7-series FPGA** (Artix-7, Kintex-7, or Virtex-7).

Let’s decode what you’re seeing:

---

### 🧩 Block Name

**`IOB33S (X0Y127)`**

* `IOB` → I/O Block (used to connect FPGA fabric signals to physical package pins).
* `33` → Supports 3.3 V I/O standards (e.g., LVCMOS33, LVTTL, etc.).
* `S` → “Single-ended” I/O (there’s also an `IOB33M` for the master side of a differential pair).
* `(X0Y127)` → Tile coordinates in the FPGA fabric.

---

### 🔌 Major Components and Signals

| Symbol / Label                 | Meaning                                                                 |
| ------------------------------ | ----------------------------------------------------------------------- |
| **PAD**                        | The actual **bond pad** connecting to a package pin.                    |
| **TRI** block                  | The **3-state output buffer** (drives pad or sets it to high-Z).        |
| **OUT**                        | Output from FPGA fabric to pad (goes through output driver).            |
| **IN**                         | Input from pad to FPGA logic.                                           |
| **T (Tri-state control)**      | Enables or disables output driver (drives pad or releases it).          |
| **DIFFI/DIFFO**                | Differential input/output paths (used when paired with an `IOB33M`).    |
| **INTERMDISABLE**              | Disables on-chip input termination (useful for differential signaling). |
| **BUFIO/BUFR path**            | Path to internal high-speed I/O clocking buffers.                       |
| **KEEPER / PULLUP / PULLDOWN** | Optional weak bias resistors.                                           |

---

### ⚙️ Functionally

This circuit implements both:

* **Input buffer path**: PAD → buffer → fabric (`Q_OUT_`).
* **Output driver path**: fabric signal → tri-state driver → PAD (`PADOUT_`).
* **Control logic**: optional pull-ups, differential termination, and tri-state control.

So, it’s the **hardware primitive for a single I/O pin** in a 7-series FPGA.
When you instantiate `IOBUF`, `OBUF`, or `IBUF` in Vivado or connect top-level ports, this is the actual silicon-level cell that gets mapped under the hood.


