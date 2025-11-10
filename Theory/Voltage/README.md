# 🌩️ **Voltage**


**Voltage** (often denoted (V)) is the **electrical potential difference** between two points in a circuit. It’s a measure of how much energy per unit charge is available to move electrons from one point to another. In simpler terms, it’s like the “push” that drives electric current through a circuit.

### Key Points:

1. **Potential Difference**

   * If you have two points, say **A** and **B**, the voltage $(V_{AB})$ is the difference in electric potential energy per unit charge between these points.
   * Formula:
     $V_{AB} = V_A - V_B$
     Where $(V_A)$ and $(V_B)$ are the electric potentials at points A and B.

2. **Analogy**: Water in a tank

   * Think of electric potential like water pressure in a tank.
   * Voltage is like the difference in water pressure between two points — water flows from high pressure to low pressure.
   * Similarly, electrons “flow” from a lower potential (more negative) to a higher potential (more positive for conventional current).

3. **Units**

   * Voltage is measured in **volts (V)**.
   * 1 Volt = 1 Joule of energy per 1 Coulomb of charge:
     $1,\text{V} = 1,\text{J/C}$

4. **Why it matters**

   * The higher the voltage difference between two points, the more “force” there is to move electrons.
   * Devices like resistors, LEDs, and transistors respond to the voltage difference applied across them.

5. **In a circuit**

   * $(V_{DD})$ or $(V_{CC})$ often represents the positive rail.
   * $(V_{SS})$ or $(V_{EE})$ is often the ground or negative rail.
   * The difference between these rails is the supply voltage (e.g., 5 V, 3.3 V).


### 1️⃣ Voltage is always relative

* Voltage is **a potential difference between two points**.
* Saying “this point is 5 V” **doesn’t mean anything** unless you know **relative to what**.

Example:

| Point | Potential |
| ----- | --------- |
| A     | 5 V       |
| B     | ?         |

* The voltage **only makes sense** if we define a reference, like B = 0 V (ground). Then $(V_{AB} = 5 - 0 = 5 V)$.

---

### 2️⃣ Ground as a common reference

* In almost all circuits, **GND is assigned 0 V**.
* All other voltages are measured **relative to GND**.
* Think of it like a “sea level” in geography. Mountains (positive voltage) and valleys (negative voltage) are measured relative to sea level.

---

### 3️⃣ Why it’s called a reference

* Because it **gives a fixed point from which all other voltages are defined**.
* Without it:

  * You can have floating voltages that are undefined.
  * Measuring a voltage with a multimeter becomes meaningless, because it always measures **difference between two points**.

---

### 4️⃣ Extra insight

* In complex circuits, you can have **multiple “grounds”** or reference points (digital GND, analog GND, chassis GND), but usually they are connected at some point to **establish a common reference**.
* Even in batteries, one terminal is “negative” (GND) so the other terminal’s voltage is meaningful.

---

💡 **Analogy:**

* GND is like the zero mark on a ruler. A measurement of 5 cm only makes sense because there’s a 0 cm reference.

