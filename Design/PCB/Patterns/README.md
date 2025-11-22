# Design Patterns

## What does this diagram represent?

<img src=images/voltage-divider.png width='50%' height='50%' > </img>

This schematic is a **high-impedance RC low-pass filter / bias network**.

### ✅ What the circuit is doing

It combines **two resistors (R7 = 649 kΩ and R8 = 200 kΩ)** and **a capacitor (C3 = 47 nF)** to create a node (OUT) that has:

1. **A fixed DC bias**
   The two resistors form a voltage divider from VCC to GND.

   $V_\text{OUT, DC} = V_{CC}\cdot \frac{R8}{R7 + R8}$

   This is often used to **bias the input of an amplifier**, comparator, or ADC around some midpoint.

2. **Low-pass filtering / noise smoothing**
   The capacitor C3 shunts AC signals to ground, so only slow changes or DC remain.

   The cutoff frequency is:

   $f_c = \frac{1}{2\pi (R_\text{eq}) C}$

   Here $( R_\text{eq} )$ is the parallel combination of R7 and R8:

   $R_\text{eq} = \frac{R7 \cdot R8}{R7 + R8} \approx 150 \text{ kΩ}$

   So:

   $f_c \approx \frac{1}{2\pi(150,\text{kΩ})(47,\text{nF})} \approx 23 \text{ Hz}$

   → This means only very slow signals pass; everything faster is filtered.

### ❓ Common places you see this

* Biasing the input of an op-amp into mid-rail
* Adding a stable reference point to a high-Z analog input
* Smoothing sensor outputs
* AC-coupled audio/DC-restore circuits
* Reset/RC timing circuits (depending on what OUT connects to)

### 🧠 In one sentence

**This is a voltage divider that generates a DC reference (bias) voltage and filters it using an RC network to make it clean and noise-free.**
