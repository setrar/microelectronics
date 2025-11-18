# **74HC153N**

The **74HC153N** is *not* an **8:1 multiplexer** — it’s a **dual 4:1 multiplexer (2× 4:1 MUX)** in one DIP-16 package.

Here’s the correct breakdown:

---

# ✅ **74HC153N — Dual 4-to-1 Multiplexer (High-Speed CMOS)**

### **What it really contains**

* **Two independent 4-input multiplexers**
* **Shared select lines** (`S0`, `S1`)
* Each multiplexer has:

  * 4 data inputs (`I0x`, `I1x`, `I2x`, `I3x`)
  * One output (`Yx`)
  * One enable (`E̅x`) — active *low*

---

# 📘 **Pin Functions**

### **Shared**

* `S0`, `S1` — select inputs
  → Choose one of the four inputs (00/01/10/11)

### **Channel A**

* `I0a`, `I1a`, `I2a`, `I3a` — data inputs
* `Ea̅` — enable (active LOW)
* `Ya` — output

### **Channel B**

* `I0b`, `I1b`, `I2b`, `I3b` — data inputs
* `Eb̅` — enable (active LOW)
* `Yb` — output

---

# 🧠 **Truth Table**

| E̅ | S1 | S0 | Output                                    |
| -- | -- | -- | ----------------------------------------- |
| 1  | X  | X  | High-Z or forced HIGH (depends on family) |
| 0  | 0  | 0  | I0                                        |
| 0  | 0  | 1  | I1                                        |
| 0  | 1  | 0  | I2                                        |
| 0  | 1  | 1  | I3                                        |

---

# ⚡ **Electrical Characteristics (74HC family)**

* **Vcc = 2–6V** (common use: 5V or 3.3V)
* CMOS → very low static power, fast edges
* Logic-level inputs compatible with other HC/HCT parts

---

# 🛠️ **Typical Uses**

✔ **MUX for digital signals**
✔ **Building small CPUs**
✔ **ROM decoding / microcoded control**
✔ **Selecting between registers**
✔ **Replacing 2× 74HC153 = simple ALU select logic**
✔ **Glitch-free digital selection**

---

# 🧩 How to turn it into an 8:1 MUX

If you *really* want an 8:1 multiplexer:

### Use both channels together:

* First stage: two 4:1 muxes (the 74HC153 is already this)
* Second stage: a 2:1 mux (use a **74HC157** or a single gate)

Then your selects become:

* `S0`, `S1` to pick within the 4:1 groups
* `S2` to choose which half (top 4 or bottom 4)

---

# 🎯 Summary

The **74HC153N ≠ 8:1 mux**.
It is **2 × 4:1 multiplexers**, very useful in digital designs, especially glue logic, CPU building, and microcode machines.




# References

- [ ] [SNx4HC153 Dual 4-Line To 1-Line Data Selectors/Multiplexers](https://www.ti.com/lit/ds/symlink/sn74hc153.pdf)
- [ ] [8:1 MUX/ 3 variable function using IC74153](https://www.youtube.com/watch?v=gqp-PyrCXCI)
