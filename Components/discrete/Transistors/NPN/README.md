

```mermaid
graph TD
  VDD[$V_{DD}$ "(+)"]
  R["Pull-up Resistor"]
  Vf["Vf (Output Node)"]
  Q["NPN Transistor"]
  VSS["VSS (Ground)"]
  Vx["Vx (Base Input)"]

  VDD --> R --> Vf --> Q
  Q --> VSS
  Vx -->|Base| Q
```


Excellent — here’s a **comparison chart** showing the different supply-voltage notations used across common electronic device families:

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
