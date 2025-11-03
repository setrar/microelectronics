# Components

# What are they?

Say for example: (Inductor)

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

Let’s break it down carefully 👇

---

