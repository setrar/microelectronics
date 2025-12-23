# Transmission Lines


Here’s a **clean, no-fluff comparison** of **LVDS vs LVCMOS33**, focusing on *what they really are*, *why they exist*, and *when you should use each*—especially relevant to FPGA/board design.

---

## 1️⃣ What they are (one-line definition)

| Standard     | What it is                                                  |
| ------------ | ----------------------------------------------------------- |
| **LVCMOS33** | **Single-ended** 3.3 V CMOS digital I/O standard            |
| **LVDS**     | **Differential** low-voltage, high-speed signaling standard |

---

## 2️⃣ Electrical signaling (core difference)

### 🔹 LVCMOS33

* **Single wire per signal**
* Voltage swing: **0 V ↔ 3.3 V**
* Receiver compares signal to **ground**
* High noise sensitivity

```
Signal ──────────▶
GND    ──────────▶
```

### 🔹 LVDS

* **Two wires per signal (P / N)**
* Voltage swing: **~350 mV**
* Receiver measures **difference** between the two
* Excellent noise immunity

```
Signal+ ─────▶
Signal- ─────▶   (difference is what matters)
```

---

## 3️⃣ Speed capability

| Feature          | LVCMOS33    | LVDS        |
| ---------------- | ----------- | ----------- |
| Practical speed  | ~50–150 MHz | **>1 Gb/s** |
| Edge quality     | Slow        | Fast        |
| Jitter tolerance | Poor        | Excellent   |
| Clock quality    | Weak        | Strong      |

👉 If it’s **above ~200 MHz** or off-board → **LVDS wins**

---

## 4️⃣ Power & EMI

| Aspect           | LVCMOS33 | LVDS         |
| ---------------- | -------- | ------------ |
| Power per toggle | High     | **Low**      |
| EMI radiation    | High     | **Very low** |
| Ground bounce    | Yes      | Almost none  |

Why?

* LVCMOS charges/discharges **big capacitance at 3.3 V**
* LVDS switches **tiny current at constant bias**

---

## 5️⃣ PCB & routing impact

| Aspect           | LVCMOS33 | LVDS                   |
| ---------------- | -------- | ---------------------- |
| Routing          | Simple   | Requires pair matching |
| Length tolerance | Short    | Long cables OK         |
| Termination      | None     | **100 Ω differential** |
| Crosstalk        | High     | Low                    |

---

## 6️⃣ Typical use cases

### 🟢 LVCMOS33 is used for:

* Buttons, LEDs
* SPI / I²C
* GPIO
* Configuration pins
* Low-speed control signals

### 🔵 LVDS is used for:

* High-speed clocks
* ADC/DAC data buses
* JESD / Camera / Display links
* FPGA-to-FPGA links
* SerDes *before* real SerDes

---

## 7️⃣ FPGA perspective (important)

| FPGA I/O             | LVCMOS33  | LVDS          |
| -------------------- | --------- | ------------- |
| I/O pins             | 1 per bit | **2 per bit** |
| Bank voltage         | 3.3 V     | ~1.8 V        |
| Clocking             | Poor      | **Excellent** |
| High-speed viability | ❌         | ✅             |

⚠️ **Modern FPGAs often LIMIT or REMOVE 3.3 V I/O**
LVDS survives longer in advanced nodes.

---

## 8️⃣ When people get confused (very common)

> ❌ “LVDS is like CMOS but faster”

No.

* **CMOS = voltage-mode**
* **LVDS = current-mode**

They are **fundamentally different physics**

---

## 9️⃣ Rule-of-thumb decision table

| Question                | Answer       |
| ----------------------- | ------------ |
| On-board, slow, cheap?  | **LVCMOS33** |
| Off-board, long traces? | **LVDS**     |
| High-speed clock?       | **LVDS**     |
| EMI-sensitive design?   | **LVDS**     |
| Simple GPIO?            | **LVCMOS33** |

---

## 🔟 In your context (FPGA + O-RAN / SerDes path)

* **Control & config** → LVCMOS
* **High-rate data** → LVDS
* **25G / GTY** → **Neither** (CML / SerDes)

LVDS is the **bridge** between CMOS GPIO and full SerDes.


<img src=images/Transmission-Lines.png width='50%' height='50%' > </img>
