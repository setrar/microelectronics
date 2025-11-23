# **Japanese transistor numbering system (JIS standard)**

### 🧩 The “2S” Prefix

In Japanese transistor part numbers like **2SA**, **2SB**, **2SC**, etc.,
the **“2S”** means it’s a **semiconductor device** — specifically a **three-terminal transistor** (two for a diode would be “1S”).

<img src=images/signal-2025-11-02-160805_005.jpeg  width='50%' height='50%' > </img>


---

### ⚙️ Breakdown of the Code

| Example    | Type       | Polarity / Usage                           | Typical Package     |
| ---------- | ---------- | ------------------------------------------ | ------------------- |
| **2SAxxx** | Transistor | **PNP** (low-frequency or general-purpose) | TO-92, TO-126, etc. |
| **2SBxxx** | Transistor | **PNP** (power type)                       | TO-220, TO-3P, etc. |
| **2SCxxx** | Transistor | **NPN** (low-frequency or general-purpose) | TO-92, TO-126, etc. |
| **2SDxxx** | Transistor | **NPN** (power type)                       | TO-220, TO-3P, etc. |

---

### 🧠 Meaning of Each Part

* **2S** → Indicates a transistor device.
* **A/B/C/D** → Letter group that identifies **polarity** and **frequency/power class**.
* **xxx** → Number assigned by manufacturer.

So:

* **2SA → PNP small-signal transistor**
* **2SB → PNP power transistor**
* **2SC → NPN small-signal transistor**
* **2SD → NPN power transistor**

---

### 🧰 Example Parts

| Part    | Type | Description                          |
| ------- | ---- | ------------------------------------ |
| 2SA1015 | PNP  | Low-noise amplifier transistor       |
| 2SC1815 | NPN  | General-purpose amplifier transistor |
| 2SB688  | PNP  | Audio power transistor               |
| 2SD718  | NPN  | Audio power transistor               |

---

So at your electronics store:

* **2SA shelf** = PNP transistors (signal type)
* **2SB Resistors** (probably a labeling mistake — should be “2SB Transistors”) = PNP power transistors
* **2SC shelf** = NPN transistors (signal type)

Here’s a clear visual chart showing how the **Japanese transistor classification (2SA–2SD)** system works 👇

```mermaid
graph TD
    A["2S (Three-terminal semiconductor device)"] --> B["2SAxxx\nPNP – Low Frequency / Small Signal\n(e.g. 2SA1015)\nUse: Audio amp, switch"]
    A --> C["2SBxxx\nPNP – Low Frequency / Power Type\n(e.g. 2SB688)\nUse: Power amplifier, driver"]
    A --> D["2SCxxx\nNPN – Low Frequency / Small Signal\n(e.g. 2SC1815)\nUse: Amplifier, RF, logic"]
    A --> E["2SDxxx\nNPN – Low Frequency / Power Type\n(e.g. 2SD718)\nUse: Power output stage"]
    
    style A fill:#444,color:#fff,stroke:#888,stroke-width:1px
    style B fill:#fcbaba,stroke:#e57373
    style C fill:#f88379,stroke:#e53935
    style D fill:#b5d3ff,stroke:#64b5f6
    style E fill:#82b1ff,stroke:#1e88e5
```

🧠 **Quick memory tip:**

* **A/B = PNP**
* **C/D = NPN**
* **Odd (A, C)** = small-signal
* **Even (B, D)** = power

---

The kind of comparison that helps you “read” transistor part numbers across standards. Let’s go step-by-step 👇

---

## 🧩 1️⃣ Naming Systems Overview

| Origin                            | Typical Prefix        | Example      | Description                                   |
| --------------------------------- | --------------------- | ------------ | --------------------------------------------- |
| 🇯🇵 **Japanese (JIS)**           | 2SA / 2SB / 2SC / 2SD | 2SC1815      | 2S = 3-terminal device, A/B = PNP, C/D = NPN  |
| 🇺🇸 **American (JEDEC)**         | 2Nxxxx                | 2N3904       | 2N = 2-junction transistor                    |
| 🇪🇺 **European (Pro Electron)**  | BCxxx / BDxxx         | BC547        | B = Silicon, C = Low power, D = Power         |
| 🇨🇳 **Chinese (local industry)** | Sxxxx                 | S8050, S8550 | Derived from older JEITA logic but simplified |

---

## 🧭 2️⃣ Where S8050 / S8550 Fit

| Part      | Origin                        | Polarity | Category                           | Typical Equivalent                               |
| --------- | ----------------------------- | -------- | ---------------------------------- | ------------------------------------------------ |
| **S8050** | 🇨🇳 Chinese (local standard) | **NPN**  | Small-signal, low-power transistor | ~ **2SC1815**, **BC337**, **2N2222**, **2N3904** |
| **S8550** | 🇨🇳 Chinese (local standard) | **PNP**  | Small-signal, low-power transistor | ~ **2SA1015**, **BC327**, **2N3906**             |

So — **S8050 ↔ 2SC1815** (NPN equivalents), and **S8550 ↔ 2SA1015** (PNP equivalents).
They have almost the same electrical class: small-signal, general-purpose, TO-92 package, 25–50 V, ~500 mA–1 A current.

---

## ⚙️ 3️⃣ Comparison Table

| Parameter       | **S8050**         | **S8550**         | **2SC1815**      | **2SA1015**      |
| --------------- | ----------------- | ----------------- | ---------------- | ---------------- |
| Origin          | China             | China             | Japan            | Japan            |
| Type            | NPN               | PNP               | NPN              | PNP              |
| V<sub>CEO</sub> | 25 V              | 25 V              | 50 V             | 50 V             |
| I<sub>C</sub>   | 1.5 A             | 1.5 A             | 150 mA           | 150 mA           |
| h<sub>FE</sub>  | 40–400            | 40–400            | 70–700           | 70–700           |
| Package         | TO-92             | TO-92             | TO-92            | TO-92            |
| Use             | Switching, Driver | Switching, Driver | Amplifier, Audio | Amplifier, Audio |

---

## 🧠 4️⃣ Summary Insight

| Family                | Polarity  | Origin              | General Use                 | Common Substitutes                 |
| --------------------- | --------- | ------------------- | --------------------------- | ---------------------------------- |
| **S8050 / S8550**     | NPN / PNP | **Chinese (local)** | Switching, LED/relay driver | 2N3904 / 2N3906, 2SC1815 / 2SA1015 |
| **2SC1815 / 2SA1015** | NPN / PNP | **Japanese (JIS)**  | Audio / signal amplifier    | BC547 / BC557, 2N2222 / 2N2907     |

---

✅ **In short:**

* S8050/S8550 = **Chinese general-purpose** NPN/PNP pair
* 2SC1815/2SA1015 = **Japanese low-noise amplifier** NPN/PNP pair
* They’re roughly **same class**, but 2SC/2SA parts are a bit **more precise (audio-grade)** while S8050/S8550 handle **more current (switching-grade)**.

---

There are actually **several transistor numbering and naming standards** in use worldwide — each developed by a regional body or semiconductor industry association.
Here’s a complete overview so you can see where **2SA/2SC**, **2N**, **BC/BD**, and **S** all fit in the bigger picture 👇

---

## 🌍 **Major Transistor Numbering Systems**

| **System**                                                 | **Origin / Body**          | **Prefix Example**                           | **Typical Use**                   | **Notes**                                                    |
| ---------------------------------------------------------- | -------------------------- | -------------------------------------------- | --------------------------------- | ------------------------------------------------------------ |
| 🇯🇵 **JIS (Japanese Industrial Standard)**                | Japan (JEITA / JIS-C-7012) | **2SA**, **2SB**, **2SC**, **2SD**           | Small-signal & power transistors  | 2S = 3-terminal device; A/B = PNP, C/D = NPN                 |
| 🇺🇸 **JEDEC (Joint Electron Device Engineering Council)** | USA                        | **2N3904**, **2N3055**                       | General-purpose, RF, power        | “2N” = transistor, “1N” = diode; globally common             |
| 🇪🇺 **Pro Electron / EECA**                               | Europe (Belgium-based)     | **BC**, **BD**, **BF**, **BU**, etc.         | Audio, RF, power                  | Prefix letter = material (B = silicon), second = application |
| 🇨🇳 **Chinese National Standard**                         | China                      | **S8050**, **S8550**, **C945**               | General-purpose transistors       | Derived from older JEITA and JEDEC conventions               |
| 🇷🇺 **GOST / Soviet System**                              | USSR / Russia              | **КТ315**, **КТ805**, **ГТ308**              | General-purpose, power, HF        | Cyrillic letters: КТ = transistor, ГТ = germanium transistor |
| 🇩🇪 **Telefunken / Siemens Legacy**                       | Germany (Pre-Pro Electron) | **OC**, **AF**, **AC**, **AD**               | Germanium transistors (1950s–60s) | Used before silicon era; now obsolete                        |
| 🇬🇧 **Mullard / Philips Legacy**                          | UK / Netherlands           | **OC**, **BF**, **BD**, etc.                 | Early European devices            | Merged into Pro Electron system in 1966                      |
| 🇰🇷 **Korean Local Codes**                                | South Korea                | **KTC3875**, **KTA1268**                     | Modern discrete devices           | Similar to Japanese: “KTC” = NPN, “KTA” = PNP                |
| 🇹🇼 **Taiwanese / Hong Kong Industry**                    | Taiwan                     | **2SCxxxx**, **2SAxxxx**, **A733**, **C945** | Cross-over naming                 | Often reuse Japanese codes, sometimes drop “2S”              |

---

## 🧠 **Summary by Era & Style**

| **Era**               | **Common Prefixes**             | **Notes**                        |
| --------------------- | ------------------------------- | -------------------------------- |
| 1950s–60s (Germanium) | OC, AC, AD                      | Early European parts             |
| 1960s–70s             | 2N, BC, BD                      | American & European silicon      |
| 1970s–80s             | 2SA, 2SC                        | Japanese system becomes dominant |
| 1980s–2000s           | S8050, C945, KTC, etc.          | Asian regional derivatives       |
| Modern                | Still 2N, BC, 2SA/2SC, S-series | Many overlap and coexist         |

---

## 🧩 **How They Interrelate**

```
    ┌────────────┐
    │   JEDEC    │ → 2Nxxxx (USA)
    └────────────┘
           │
           ▼
    ┌────────────┐
    │ Pro Electron│ → BC/BD/BF... (Europe)
    └────────────┘
           │
           ▼
    ┌────────────┐
    │    JIS     │ → 2SA/2SC/2SD (Japan)
    └────────────┘
           │
           ▼
    ┌────────────┐
    │   Chinese  │ → S8050, S8550 (China)
    └────────────┘
```

---

### 🧩 **Fun fact:**

Many “local” transistor codes like **C945**, **A733**, or **KTC3875** you see on small boards are **abbreviated JIS parts** —
for example:

* **C945** = **2SC945**
* **A733** = **2SA733**
* **KTC3875** = Korean version of **2SC1815**

---

## Other components

<img src=images/signal-2025-11-02-160805_002.jpeg width='50%' height='50%' > </img>
<img src=images/signal-2025-11-02-160805_003.jpeg width='50%' height='50%' > </img>
<img src=images/signal-2025-11-02-160805_004.jpeg width='50%' height='50%' > </img>

# Others

<img src=images/signal-2025-04-23-152007_002.jpeg width='50%' height='50%' > </img>

<img src=images/signal-2025-10-05-094147_002.jpeg width='50%' height='50%' > </img>
<img src=images/signal-2025-10-05-095120.jpeg width='50%' height='50%' > </img>

