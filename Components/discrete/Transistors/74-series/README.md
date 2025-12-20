# 74-series

**The 74-series includes *both* TTL and CMOS families.**
“74-series” is a **naming umbrella**, not a technology. The **suffix** tells you whether the logic family is TTL or CMOS.

---

## Big picture (one sentence)

* **TTL families** → bipolar transistors (BJT)
* **CMOS families** → MOSFETs
* **HCT** → CMOS internally, **TTL-compatible at the inputs**

---

## Clean, practical comparison table (engineer-friendly)

### 74-Series Logic Families Overview

| Family    | Technology | V<sub>CC</sub> | Input Levels | Speed     | Power     | Notes / Typical Use       |
| --------- | ---------- | -------------- | ------------ | --------- | --------- | ------------------------- |
| **74**    | TTL (BJT)  | 5 V            | TTL          | Slow      | High      | Original TTL (obsolete)   |
| **74L**   | TTL (BJT)  | 5 V            | TTL          | Very slow | Lower     | Rare/obsolete             |
| **74H**   | TTL (BJT)  | 5 V            | TTL          | Faster    | High      | Rare                      |
| **74S**   | TTL (BJT)  | 5 V            | TTL          | Fast      | Very high | Obsolete, hot             |
| **74LS**  | TTL (BJT)  | 5 V            | TTL          | Medium    | Lower     | Classic TTL (school labs) |
| **74AS**  | TTL (BJT)  | 5 V            | TTL          | Very fast | High      | Rare                      |
| **74ALS** | TTL (BJT)  | 5 V            | TTL          | Fast      | Medium    | Late-generation TTL       |

---

### CMOS 74-Series (Most modern designs)

| Family                 | Technology | V<sub>CC</sub> | Input Levels       | Speed     | Power     | Notes                       |
| ---------------------- | ---------- | -------------- | ------------------ | --------- | --------- | --------------------------- |
| **74C**                | CMOS       | 3–15 V         | CMOS               | Slow      | Very low  | Obsolete                    |
| **74HC**               | CMOS       | 2–6 V          | CMOS               | Fast      | Very low  | **Most common CMOS logic**  |
| **74HCT**              | CMOS       | 4.5–5.5 V      | **TTL-compatible** | Fast      | Very low  | Drop-in replacement for TTL |
| **74AC**               | CMOS       | 2–6 V          | CMOS               | Very fast | Low       | High-speed CMOS             |
| **74ACT**              | CMOS       | 4.5–5.5 V      | **TTL-compatible** | Very fast | Low       | Fast TTL replacement        |
| **74LVC**              | CMOS       | 1.65–3.6 V     | CMOS               | Very fast | Ultra-low | Modern low-voltage logic    |
| **74LVX / AHC / AHCT** | CMOS       | 2–5 V          | CMOS / TTL         | Very fast | Low       | FPGA-friendly glue logic    |

---

## Key distinctions (this matters in real designs)

### TTL (BJT-based)

* Fixed **5 V**
* **Consumes power even when idle**
* Strong output drive
* Limited voltage flexibility
* Mostly obsolete except legacy systems

### CMOS (MOSFET-based)

* **Very low static power**
* Wide voltage range
* Higher noise margin
* Scales to modern processes
* Dominates **all modern digital ICs**

---

## HC vs HCT (the most common confusion)

| Feature          | 74HC            | 74HCT                |
| ---------------- | --------------- | -------------------- |
| Internal tech    | CMOS            | CMOS                 |
| Supply           | 2–6 V           | 4.5–5.5 V            |
| Input thresholds | CMOS            | **TTL-compatible**   |
| Use when         | All-CMOS system | Interfacing with TTL |

> **HCT is CMOS pretending to be TTL at the inputs.**

---

## Final classification (clear answer)

| Family           | TTL?  | CMOS? |
| ---------------- | ----- | ----- |
| 74, LS, ALS, S   | ✅ Yes | ❌ No  |
| HC, HCT, AC, LVC | ❌ No  | ✅ Yes |

