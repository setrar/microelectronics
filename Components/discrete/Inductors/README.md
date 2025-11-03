# Inductors

### ⚙️ 1️⃣ Inductor in general electronics

An **inductor** is a **discrete passive component**, not an IC by itself.

* It’s usually a **coil of wire** (air-core or ferrite-core) with two terminals.
* It can be **mounted on a PCB** or **wound by hand**.

So in the classic sense, **an inductor is not an integrated circuit (IC)**.

---

### ⚙️ 2️⃣ Inductor in RF / CMOS chips

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

Let’s break it down carefully 👇

---

## ⚙️ 1️⃣ What an Inductor Is

An **inductor** is simply a **coil of wire** that stores energy in a **magnetic field** when current flows through it.

The **more turns**, **larger area**, or **more magnetic material**, the **higher the inductance**.

---

## 🧰 2️⃣ What You Need

You can make one from:

| Part                                   | Purpose                     | Example                                                       |
| -------------------------------------- | --------------------------- | ------------------------------------------------------------- |
| **Copper wire (enameled magnet wire)** | Conducts current            | 24–30 AWG magnet wire                                         |
| **Core (optional)**                    | Concentrates magnetic field | Ferrite rod, iron powder core, toroid, or even air (air-core) |
| **Form**                               | Shape to wind wire          | Pen, straw, 3D-printed cylinder, etc.                         |

---

## 🧮 3️⃣ Inductance Formula (for a simple air-core coil)

If you make an **air-core inductor**, you can estimate its inductance as:

$L = \frac{(r^2 N^2)}{9r + 10l} ; [\mu H]$

Where:

* ( L ) = inductance (µH)
* ( r ) = coil radius (cm)
* ( l ) = coil length (cm)
* ( N ) = number of turns

👉 This is called **Wheeler’s formula** — great for hand-wound inductors.

---

### Example

If you wind **10 turns** of wire on a **1 cm radius** form that’s **2 cm long**:
$L ≈ \frac{(1^2 × 10^2)}{9×1 + 10×2} = \frac{100}{29} ≈ 3.4 µH$

That’s a perfectly usable inductor for many analog and low-RF circuits!

---

## ⚡ 4️⃣ How to Build One

1. **Choose your target inductance** (say 1 µH or 10 µH).
2. **Pick your wire gauge** (thicker = lower resistance).
3. **Wind wire on your form** — count turns carefully.
4. **Secure it** with tape, epoxy, or glue.
5. **Measure it** using an **LCR meter** or an **LC resonance test** (e.g., with an oscilloscope + known capacitor).

---

## 🧲 5️⃣ Optional: Use a Core

If you use a **ferrite or iron powder core**, inductance increases dramatically because the magnetic permeability is higher.
You can buy toroidal ferrite cores (e.g., FT-37-43) and wind your coil around them — perfect for **RF chokes** or **filters**.

---

## 🧩 6️⃣ Limits

| Limitation                | Why it matters                                                        |
| ------------------------- | --------------------------------------------------------------------- |
| **Parasitic capacitance** | At high frequencies (GHz), the coil self-resonates.                   |
| **Resistance**            | Fine wire = higher series resistance → lower Q.                       |
| **Core saturation**       | Magnetic cores can saturate at high currents.                         |
| **Precision**             | Hand-wound inductors are approximate (good for hobby and prototypes). |

---

## 🧠 For RF-CMOS chips (on silicon)

You **can’t physically hand-make** the *on-chip* spiral inductors — those are fabricated in top metal layers of silicon (e.g., using thick Al/Cu).
But conceptually, they’re doing the **same thing** you do with wire — just miniaturized and precisely modeled.

---

## 🧰 Summary

| Setting                  | Can you make it?         | Method                        |
| ------------------------ | ------------------------ | ----------------------------- |
| **Discrete / PCB-level** | ✅ Yes                    | Wire + core or air-core coil  |
| **RFIC (on-chip)**       | ❌ No (needs fab process) | Made lithographically         |
| **Simulation / design**  | ✅ Yes                    | Model with L and Q parameters |

Yes — exactly ✅

$\mu H = \text{microhenry}$

It’s the **unit of inductance**, where:

$1,\mu H = 10^{-6},H$

---

### ⚙️ Unit hierarchy

| Unit       | Symbol | Relation             |
| ---------- | ------ | -------------------- |
| Henry      | **H**  | Base SI unit         |
| Millihenry | **mH** | ( 1,mH = 10^{-3},H ) |
| Microhenry | **µH** | ( 1,µH = 10^{-6},H ) |
| Nanohenry  | **nH** | ( 1,nH = 10^{-9},H ) |

---

### 🧭 Example

If you wind a small coil of wire and measure:
$L = 2.2,\mu H$
that means it has an inductance of $( 2.2 \times 10^{-6} )$ henries.

