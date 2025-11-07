


<img src=images/NMOS-inverter.png width='30%' height='30%' > </img>

A **common-source NMOS amplifier** (or **inverter**, depending on biasing).

Here’s how to classify it:

---

### ⚙️ Circuit Type

**→ Common-Source NMOS Configuration**

---

### 🔋 Structure

* **Drain** connected to **V<sub>DD</sub>** through a **resistor** → provides the load.
* **Source** connected to **ground (V<sub>SS</sub>)** → reference node.
* **Gate** receives the **input voltage (V<sub>G</sub>)** → controls current through the channel.

---

### 🔄 Function

Depending on how it’s biased:

1. **As a digital logic inverter (switching region):**

   * If **V<sub>G</sub> < V<sub>th</sub>**, the NMOS is **OFF**, so **V<sub>D</sub> ≈ V<sub>DD</sub>** → logic ‘1’.
   * If **V<sub>G</sub> > V<sub>th</sub>**, the NMOS is **ON**, pulling **V<sub>D</sub> ≈ 0 V (V<sub>SS</sub>)** → logic ‘0’.
   * ➜ Acts as a **NOT gate**.

2. **As an analog amplifier (active region):**

   * For small signals, the NMOS operates in the **saturation region**.
   * **V<sub>D</sub>** varies inversely with **V<sub>G</sub>**, giving voltage amplification.
   * ➜ Acts as a **common-source amplifier**.

---

### 🧩 Summary Table

| Node     | Symbol         | Function           |
| -------- | -------------- | ------------------ |
| Drain    | D              | Output             |
| Gate     | G              | Input              |
| Source   | S              | Reference (ground) |
| Resistor | R<sub>D</sub>  | Load               |
| Supply   | V<sub>DD</sub> | Positive rail      |

---

So:
- ✅ **Digital View:** NMOS inverter (logic NOT gate)
- ✅ **Analog View:** Common-source amplifier

<img src=images/VTC.png width='50%' height='50%' > </img>

Nice — perfect plot. Here's a short explanation to go with the voltage-transfer characteristic (VTC) you just saw.

# What the plot shows

* The **horizontal axis** is the input gate voltage (V_{in}).
* The **vertical axis** is the output/drain voltage (V_{out}=V_D) (node pulled up by (R_D) to (V_{DD}) when the NMOS is off).
* The dashed diagonal line (y=x) is shown for reference.

# Regions and behavior

1. **Left region (Vin < Vth ≈ 1.5 V)**

   * NMOS is **off** (no channel).
   * No drain current, so the pull-up resistor pulls the drain to (V_{DD}) (here ≈ 5 V).
   * Output is HIGH.

2. **Transition region (around Vin ≈ Vth → a bit above)**

   * The transistor begins to conduct; the drain starts to fall from (V_{DD}).
   * The device may operate first in **saturation** (current limited by gate overdrive) and then in **triode**, depending on Vds vs Vov.
   * This region produces the sharp fall (gain) — the inverter switching threshold lies somewhere here.

3. **Right region (Vin large)**

   * NMOS is strongly on; it pulls the drain near ground (small Vout).
   * Output is LOW (but not exactly 0 V because of voltage drop across the on-resistance and the finite Rd).

# Design knobs that change the curve

* **Rd (pull-up resistor)**: larger Rd → weaker pull-up → steeper transition and lower static HIGH→LOW current (slower switching). Smaller Rd → stronger pull-up → Vout HIGH closer to VDD when off but larger static power when ON.
* **Vth (threshold)** and **k (device strength)**: change where the transistor turns on and how strongly it pulls the output down — shifts and steepness of the transition.
* **Vdd**: scales the HIGH and influences where regions fall.

# Practical notes

* This Rd-loaded NMOS inverter is simple but **inefficient** (static power drawn when input is HIGH because current flows through Rd and NMOS). CMOS inverters avoid that by using complementary devices.
* The VTC is useful for finding the **switching threshold (Vm)** where (V_{in}=V_{out}) and for calculating gain (slope) at that point.

---

Perfect ✅ — here’s a **Mermaid schematic** comparing **BJT vs MOSFET** rail conventions side-by-side:

```mermaid
graph LR
  subgraph BJT_Circuit["BJT Circuit (VCC / VEE)"]
    VCC["+VCC (Collector Rail)"]
    Q1["NPN Transistor"]
    VEE["0V / -VEE (Emitter Rail)"]
    VCC --> Q1
    Q1 --> VEE
    Q1 -->|Base Input| Vin1["V_in (Base)"]
  end

  subgraph MOSFET_Circuit["MOSFET Circuit (VDD / VSS)"]
    VDD["+VDD (Drain Rail)"]
    M1["nMOS Transistor"]
    VSS["0V / -VSS (Source Rail)"]
    VDD --> M1
    M1 --> VSS
    M1 -->|Gate Input| Vin2["V_in (Gate)"]
  end

  style BJT_Circuit fill:#ffe9d6,stroke:#f68b1f,stroke-width:2px
  style MOSFET_Circuit fill:#d6f5ff,stroke:#007acc,stroke-width:2px
```

---

### 🧠 Explanation

| Type       | Positive Rail | Negative / Ground Rail | Controlled by | Typical Symbol |
| ---------- | ------------- | ---------------------- | ------------- | -------------- |
| **BJT**    | **$V_{CC}$**  | **$V_{EE}$**           | Base current  | NPN or PNP     |
| **MOSFET** | **$V_{DD}$**  | **$V_{SS}$**           | Gate voltage  | nMOS or pMOS   |

So:

* BJTs → **Collector/E**mitter rails → ($V_{CC}$), ($V_{EE}$)
* MOSFETs → **Drain/S**ource rails → ($V_{DD}$), ($V_{SS}$)



```mermaid
graph TD
  VDD["VDD (+)"]
  R["Pull-up Resistor"]
  Vf["Vf (Output Node)"]
  Q["NPN Transistor"]
  VSS["VSS (Ground)"]
  Vx["Vx (Base Input)"]

  VDD --> R --> Vf --> Q
  Q --> VSS
  Vx -->|Base| Q
```

The “**DD**” in **($V_{DD}$)** actually comes from **old MOSFET terminology**:

### 🧩 Origin of the notation

| Symbol         | Meaning                                          | Common Use                                    |
| -------------- | ------------------------------------------------ | --------------------------------------------- |
| **($V_{DD}$)** | Voltage at the **drain** of an n-channel MOSFET  | Used as the **positive supply**               |
| **($V_{SS}$)** | Voltage at the **source** of an n-channel MOSFET | Used as **ground** or the **negative supply** |

---

### 🧠 Why it’s used even for BJTs

Even though BJTs have **collector/emitter** instead of **drain/source**, engineers kept using ($V_{DD}$) and ($V_{SS}$) for consistency in digital circuits, especially CMOS logic.
In BJT-based circuits you might see:

| BJT notation                  | Equivalent MOSFET notation |
| ----------------------------- | -------------------------- |
| ($V_{CC}$) (collector supply) | ($V_{DD}$)                 |
| ($V_{EE}$) (emitter supply)   | ($V_{SS}$)                 |

---

### ⚡ Summary

* **($V_{DD}$)** → “Drain-to-Drain voltage” → positive rail.
* **($V_{SS}$)** → “Source-to-Source voltage” → ground/negative rail.
* Historical artifact:

  * **D** = Drain
  * **S** = Source
  * **C** = Collector
  * **E** = Emitter

So in short:

> 🔹 **($V_{DD}$)** = positive supply voltage
> 
> 🔹 **($V_{SS}$)** = ground or 0 V (negative supply)



Here’s a **comparison chart** showing the different supply-voltage notations used across common electronic device families:

---

### ⚙️ Supply Voltage Notation Reference

| **Device Type**                            | **Positive Supply**                              | **Negative / Ground Supply**  | **Notes / Meaning**                                                                 |
| ------------------------------------------ | ------------------------------------------------ | ----------------------------- | ----------------------------------------------------------------------------------- |
| **BJT (Bipolar Junction Transistor)**      | **V<sub>CC</sub>**                               | **V<sub>EE</sub>**            | C = Collector, E = Emitter. Used in logic built with BJTs (e.g., TTL).              |
| **MOSFET (CMOS logic, ICs)**               | **V<sub>DD</sub>**                               | **V<sub>SS</sub>**            | D = Drain, S = Source. Origin of modern digital supply naming (V<sub>DD</sub> = +, V<sub>SS</sub> = GND). |
| **Op-Amp (Analog Circuits)**               | **V<sub>+</sub>**                                | **V<sub>–</sub>**             | Some op-amps use ± supplies (e.g., +15 V / –15 V).                                  |
| **General Digital ICs (TTL/CMOS)**         | **V<sub>CC</sub>** or **V<sub>DD</sub>**         | **GND** or **V<sub>SS</sub>** | Depending on internal transistor type (BJT → CC, MOS → DD).                         |
| **FET Amplifiers (Discrete)**              | **V<sub>DD</sub>**                               | **V<sub>SS</sub>**            | Drain connected to positive rail, Source to ground.                                 |
| **Bipolar Differential / Analog Circuits** | **V<sub>CC</sub>**                               | **V<sub>EE</sub>**            | Common in analog amplifiers using NPN+PNP stages.                                   |
| **Microcontrollers / CPUs (CMOS)**         | **V<sub>DD</sub>**                               | **V<sub>SS</sub>**            | Standard across all CMOS devices. E.g. VDD = 3.3 V or 5 V.                          |
| **Dual-Supply Systems**                    | **V<sub>CC</sub> = +V**, **V<sub>EE</sub> = –V** | —                             | Used for analog designs needing positive and negative rails.                        |

---

### 🧠 Quick Summary

| Context                       | You’ll usually see               |
| ----------------------------- | -------------------------------- |
| **Digital CMOS**              | ($V_{DD}$), ($V_{SS}$)           |
| **Digital TTL / BJT**         | ($V_{CC}$), ($V_{EE}$)           |
| **Analog / Op-Amp**           | ($V_{+}$), ($V_{-}$)             |
| **Ground (common reference)** | ($V_{SS}$), ($V_{EE}$), or (GND) |
