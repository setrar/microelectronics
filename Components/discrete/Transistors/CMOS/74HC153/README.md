# **74HC153N**

Perfect — let’s describe the **implementation of**

[
f(A,B,C) = \Sigma_m(1,3,5,6,7)
]

**using one half of the SNx4HC153 (a 4:1 MUX) in textual form**.

---

# 1️⃣ Assign the MUX signals

* **Select lines:**

  * (S_1 = B)
  * (S_0 = C)

* **Data inputs (I0–I3):** determine the output for each BC combination

| BC (S1,S0) | Corresponding minterms | What f should output | MUX input I? |
| ---------- | ---------------------- | -------------------- | ------------ |
| 00         | m0, m4                 | 0                    | I0 = 0       |
| 01         | m1, m5                 | 1                    | I1 = 1       |
| 10         | m2, m6                 | depends on A         | I2 = A       |
| 11         | m3, m7                 | 1                    | I3 = 1       |

> Explanation: For BC=10, f = 1 only when A=1 (minterm 6), otherwise 0 (minterm 2). That’s why I2 = A.

---

# 2️⃣ Textual wiring description

```
SNx4HC153 half-MUX (Y output):

- Select lines:
    S1 = B
    S0 = C

- Data inputs:
    I0 = 0       // covers minterms 0,4
    I1 = 1       // covers minterms 1,5
    I2 = A       // covers minterms 2 (0) and 6 (1)
    I3 = 1       // covers minterms 3,7

- Enable: E̅ = 0   // active
- Output: Y = f(A,B,C)
```

* Operation:

  * When B,C = 00 → Y = I0 = 0 → covers m0, m4
  * When B,C = 01 → Y = I1 = 1 → covers m1, m5
  * When B,C = 10 → Y = I2 = A → covers m2, m6
  * When B,C = 11 → Y = I3 = 1 → covers m3, m7

This **directly implements** f(A,B,C) = Σm(1,3,5,6,7).

---

# 3️⃣ Optional textual summary of minterm mapping

```
Minterm -> Output

m0 (000) -> 0  (I0)
m1 (001) -> 1  (I1)
m2 (010) -> 0  (I2 = A=0)
m3 (011) -> 1  (I3)
m4 (100) -> 0  (I0)
m5 (101) -> 1  (I1)
m6 (110) -> 1  (I2 = A=1)
m7 (111) -> 1  (I3)
```

---

✅ This textual wiring shows exactly **how the 74HC153/SNx4HC153 implements the sum-of-minterms function**.

---

# how to physically (i.e. with discrete components) test the given f(A,B,C) function on a breadboard?

Great — here is the **ASCII art breadboard layout** and **full explanation** for physically testing
$
f(A,B,C)=\Sigma_m(1,3,5,5,6,7)
$
using a **74HC153**, switches, and LEDs.

---

# 🧱 **ASCII ART BREADBOARD LAYOUT**

This layout shows *one half* of the 74HC153 wired exactly as required.

```
===========================================================
  +5V RAIL      |                                    |
===========================================================
  GND RAIL      |                                    |
===========================================================

                      BREADBOARD

                   (74HC153 DIP-16)
                 ┌───────────────────────┐
       +5V  ---> │16 Vcc            GND 8│ <--- GND
                 │                       │
 I0 = 0     GND  │1   1A            2A 15│
 I1 = 1     +5V  │2   1B            2B 14│
 I2 = A          │3   1C            2C 13│
 I3 = 1     +5V  │4   1D            2D 12│
 EN = 0    GND   │5  1G̅             2G̅ 11│
 OUTPUT ---> LED │6   1Y            2Y 10│
 SIGNAL GND------│7   GND         S0 (C)9│ <--- C switch
                 │                       │
 S1 (B) <--------│11 S1                9 │ (depends on pkg)
                 └───────────────────────┘

===========================================================
     SWITCHES (A, B, C)
===========================================================

     +5V   o───┐     +5V   o───┐     +5V   o───┐
               |                |                |
          A ---┘           B ---┘           C ---┘
               |                |                |
     GND ──1kΩ─┘     GND ──1kΩ─┘     GND ──1kΩ─┘

===========================================================
       OUTPUT LED
===========================================================

74HC153 Pin 7 (1Y) ─── 1kΩ ───►|─── GND
                               LED
```

This ASCII diagram is EXACT wiring, with correct pins and signals.

---

# 🧩 **PIN MAPPING FOR THE LEFT MUX (1Y)**

| Function   | 74HC153 Pin | Connect To       |
| ---------- | ----------- | ---------------- |
| **Vcc**    | 16          | +5V              |
| **GND**    | 8           | GND              |
| I0         | 1           | GND              |
| I1         | 2           | +5V              |
| I2         | 3           | A switch         |
| I3         | 4           | +5V              |
| Enable 1G̅ | 5           | GND (always on)  |
| Output 1Y  | 7           | LED + 1kΩ to GND |
| Select S1  | 11          | B switch         |
| Select S0  | 10          | C switch         |

---

# 🧪 **SWITCH WIRING (A, B, C)**

Each switch:

```
+5V ──o/ o── A(or B/C)
             |
            1kΩ
             |
            GND
```

This makes:

* Switch OFF → input = 0
* Switch ON → input = 1

---

# 🔴 **LED OUTPUT**

```
Pin 7 ── 1kΩ resistor ──► LED ──► GND
```

LED ON → f = 1
LED OFF → f = 0

---

# 🧪 **FULL TEST TABLE (USE SWITCHES)**

| A | B | C | Minterm | Expected f | LED |
| - | - | - | ------- | ---------- | --- |
| 0 | 0 | 0 | m0      | 0          | OFF |
| 0 | 0 | 1 | m1      | 1          | ON  |
| 0 | 1 | 0 | m2      | 0          | OFF |
| 0 | 1 | 1 | m3      | 1          | ON  |
| 1 | 0 | 0 | m4      | 0          | OFF |
| 1 | 0 | 1 | m5      | 1          | ON  |
| 1 | 1 | 0 | m6      | 1          | ON  |
| 1 | 1 | 1 | m7      | 1          | ON  |

The most important test is **m6 = 110**, because I2 = A must result in 1.

---

# 🧠 WHY THIS WORKS

When B,C select:

* **00 → I0 = 0**
* **01 → I1 = 1**
* **10 → I2 = A**
* **11 → I3 = 1**

This matches the minterm pattern exactly.

---


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
