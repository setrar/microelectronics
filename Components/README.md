# Components

Discrete and IC components: a fundamental distinction in electronics. Let’s go step by step:

---

## ⚙️ 1️⃣ Discrete Components

**Definition:**
A **discrete component** is a **single, individual electronic element** with **one basic electrical function**.

### ✅ Examples

| Type                 | Function                        | Notes                                       |
| -------------------- | ------------------------------- | ------------------------------------------- |
| Resistor (R)         | Limits current                  | Can be carbon, metal-film, or chip resistor |
| Capacitor (C)        | Stores electric energy          | Ceramic, [electrolytic](https://en.wikipedia.org/wiki/Electrolytic_capacitor), tantalum             |
| Inductor (L)         | Stores magnetic energy          | Air-core or ferrite coil                    |
| Diode                | Allows current in one direction | Includes LEDs, Schottky, Zener              |
| Transistor           | Amplification or switching      | BJT, MOSFET, JFET                           |
| Crystal / Oscillator | Precise frequency reference     | Quartz crystal                              |

### ⚡ Characteristics

* **Single function** per component
* Can be **mounted on a PCB individually**
* Often used in **prototyping, discrete circuits, or power electronics**

---

## ⚙️ 2️⃣ Integrated Circuit (IC) Components

**Definition:**
An **IC (Integrated Circuit)** is a **miniature electronic circuit** where **multiple components** are fabricated **together on a single semiconductor chip**.

### ✅ Examples

| Type                 | Function                             | Notes               |
| -------------------- | ------------------------------------ | ------------------- |
| Op-amp IC            | Amplifier with multiple transistors  | LM358, TL072        |
| Voltage regulator IC | Provides fixed or adjustable voltage | 7805, LM317         |
| Microcontroller      | Contains CPU + memory + peripherals  | Arduino chip, STM32 |
| RFIC                 | Contains amplifiers, mixers, filters | LNA, VCO on-chip    |
| ADC/DAC              | Converts analog ↔ digital            | MCP3008, AD5693     |

### ⚡ Characteristics

* **Multiple functions/components integrated on one chip**
* **Much smaller size** than discrete equivalents
* Can include **transistors, resistors, capacitors, inductors (sometimes)**
* Mass-produced and cost-effective for complex circuits

---

## ⚙️ 3️⃣ Comparison Table

| Feature             | Discrete Component          | IC Component                      |
| ------------------- | --------------------------- | --------------------------------- |
| Functionality       | Single basic function       | Multiple components/functions     |
| Fabrication         | Individual                  | All on a single semiconductor die |
| Size                | Larger                      | Much smaller                      |
| Cost (per function) | Higher for complex circuits | Lower for complex circuits        |
| Examples            | R, C, L, Diode, BJT         | Op-amp IC, MCU, RFIC              |

---

### ⚡ Key Intuition

* **Discrete:** Think **one thing, one function** — like a single resistor or transistor.
* **IC:** Think **many things together on one chip** — like an op-amp that already contains dozens of transistors and resistors.

---

## An example: The Inductor

### ⚙️ 1️⃣ Inductor in general electronics (i.e. [Discrete](discrete) )

An **inductor** is a **discrete passive component**, not an IC by itself.

* It’s usually a **coil of wire** (air-core or ferrite-core) with two terminals.
* It can be **mounted on a PCB** or **wound by hand**.

So in the classic sense, **an inductor is not an integrated circuit (IC)**.

---

### ⚙️ 2️⃣ Inductor in RF / CMOS chips (i.e. [IC - Integrated Circuit](ic) )

In **RFIC / CMOS design**, inductors **can be fabricated on-chip**, typically as:

* **Spiral inductors** in the top metal layers
* **Planar inductors** embedded in silicon
* **Bonded wire or stacked metal** to increase Q

These are **part of an IC** — so in that sense, the inductor is **on-chip, but not a standalone IC**.

---

### ⚡ Key distinction

| Type                               | Form                                    | IC?                                 |
| ---------------------------------- | --------------------------------------- | ----------------------------------- |
| Discrete inductor                  | Wire coil or ferrite/air core           | ❌ Not an IC                         |
| On-chip spiral inductor            | Lithographically patterned metal layers | ✅ Part of an IC, but not standalone |
| Integrated passive component block | Includes multiple L, C, R on-chip       | ✅ Part of IC                        |

---

### 🧠 Takeaway

> Inductors themselves are **passive components**, not ICs. But in **RF CMOS or BiCMOS chips**, inductors can be **fabricated on-chip as part of an IC**.

Yes — absolutely ✅ you *can* create your own inductor!
In fact, **inductors are one of the few electronic components you can physically make yourself** using just wire, a core (or even air), and a bit of math.

---

