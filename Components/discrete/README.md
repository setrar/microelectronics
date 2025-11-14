


CD4001 → NOR

CD4011 → NAND

CD4069 → inverter

CD4070 → XOR

---

A compact, ready-to-buy **combined BOM + roles + notes** to build a full *DIY FPGA macrocell / small array* using **74HC (fast CMOS)** for speed and control, and **CD40xx** where you want the “old CMOS” behavior or extra voltage headroom. I’ll also include a quick wiring summary for how the parts map to the macrocell (LUT → FF → output) so you can start wiring on a breadboard.

# ✅ Goal

Build reusable macrocell(s) that implement a 4-input LUT (configurable by hardwired switches), optional combinational-vs-registered output, a D flip-flop, and tri-state output / bus connection.

---

# 📦 Combined BOM (DIP-friendly parts)

Buy 2–4 of each core part to prototype several macrocells.

| Qty | Part (DIP)                | Family | Role in DIY FPGA cell                                         | Notes                                                |
| :-- | ------------------------- | ------ | ------------------------------------------------------------- | ---------------------------------------------------- |
| 2–4 | **74HC153** (DIP)         | 74HC   | Dual 4:1 MUX — used as two halves of a 4-input LUT            | Each IC has 2 × 4:1 muxes.                           |
| 2–4 | **74HC157** (DIP)         | 74HC   | Quad 2:1 MUX — final selection (D) + reg/combinational select | Use to choose between halves or between LUT_OUT/Q.   |
| 4–6 | **74HC74** (DIP)          | 74HC   | Dual D flip-flop — macrocell registers                        | Tie PRE/CLR inactive unless used.                    |
| 2–4 | **74HC125** (DIP)         | 74HC   | Quad tri-state buffer — programmable output enable            | OE logic: tie appropriately (check active polarity). |
|   2 | **74HC04** (DIP)          | 74HC   | Hex inverter — input conditioning / level invert              | Useful for REG_SEL inversion or OE polarity.         |
|   1 | **74HC245** (DIP)         | 74HC   | Octal bus transceiver — shared bus / I/O buffering            | Optional but handy for multi-macrocell bus.          |
| 1–2 | **CD4051 / CD4052** (DIP) | CD40xx | Analog MUX alternatives (if you prefer CD family LUTs)        | CD4052 = dual 4-channel analog mux; works at 5 V.    |
| 1–2 | **CD4069** (DIP)          | CD40xx | Hex inverter (old CMOS flavor)                                | Use where you want classic CMOS timing/thresholds.   |
| 1–2 | **CD4013** (DIP)          | CD40xx | Dual D flip-flop (CD4000 variant)                             | If you want CD40xx register behavior.                |
|   — | **74HC14** (DIP)          | 74HC   | Schmitt inputs for noisy signals (optional)                   | Use for debouncing or noisy external inputs.         |

---

# 🧰 Configuration & support parts

| Item                                                 | Purpose                                                   |
| ---------------------------------------------------- | --------------------------------------------------------- |
| DIP switch pack (8 or 12 positions)                  | Hardwire LUT truth table bits C00..C07 (or use jumpers)   |
| 8 × 10 kΩ resistors                                  | Pull-downs/pull-ups for DIP switch lines (avoid floating) |
| 0.1 µF ceramic caps (x6)                             | Decoupling — one per IC group (close to VCC pins)         |
| 5 V regulated supply (1 A)                           | VCC for 74HC; runs CD40xx at 5 V (common rail)            |
| Breadboard, IC sockets                               | Makes swapping parts easy                                 |
| Logic probe / cheap oscilloscope                     | Debug timing and logic levels                             |
| Optional: rotary encoder or shift register (74HC595) | Reprogram LUTs via serial if you want reconfigurability   |

---

# ⚡ Voltage & mixing notes

* **Run everything at 5.0 V** for easiest compatibility between 74HC and CD40xx.
* 74HC parts like 74HCxx are fastest at 5 V; CD40xx are slower but work at 5 V.
* Tie unused inputs to defined levels (use the 10 kΩ pulls).
* Decouple VCC–GND at each IC (0.1 µF).

---

# 🧭 Minimal parts per single macrocell (concrete)

* 1 × 74HC153 (both halves used)
* 1 × 74HC157 (use 1 channel; leads left for extra choices)
* 1 × 74HC74 (1 FF used; extra FF available)
* 1 × 74HC125 (1 channel used)
* 1 × 74HC04 (optional)
* DIP switches + resistors + decoupling caps

This is exactly the set you used earlier in textual wiring.

---

# 🔗 Quick wiring summary (macrocell mapping)

(You already have a textual wiring diagram earlier — here’s the BOM→signal quick map.)

1. **Inputs**: I0..I3 → feed 74HC153 select pins (A,B) and final 74HC157 select (D).
2. **Config bits**: C00..C07 wired to 153 data inputs via DIP switches (to VCC/GND) with 10 k pull resistors.
3. **153 outputs** → 157 inputs → **LUT_OUT** (final 2:1 selection by D).
4. **LUT_OUT** → D of **74HC74** (FF). CLK → 74HC74 clock pin. PRE/CLR tied inactive. Q is registered output.
5. **REG_SEL (via 74HC157)** chooses between LUT_OUT (combinational) and Q (registered) and feeds the **74HC125** data input.
6. **OE** controls 74HC125 enabling to drive **OUT_PIN** (or put 74HC245 after it for bus).
7. Use 74HC04 for any required polarity inversion (OE inversion, REG_SEL inversion, etc.).

---

# 🧪 Suggested prototyping plan

1. Build a single macrocell following your earlier textual wiring — get LUT→FF→OE working using hardwired config bits.
2. Verify combinational outputs (LUT_OUT) with logic probe; then clock the FF and verify Q behavior.
3. Add REG_SEL and OE options.
4. Replicate N macrocells (2–4) and connect through 74HC245 for bus experiments.
5. If you want reprogrammable LUTs, replace DIP switches with a small shift register (74HC595) or an 8-bit SRAM/EEPROM and a small driver.

---

# 🛒 Where to buy (quick)

Common vendors: **DigiKey, Mouser, Newark, LCSC, Amazon**. For hobby quantities, Amazon / eBay / AliExpress kit sellers are often cheaper (but QC/time varies). No links here unless you want them.

---

# Final — want me to do next?

* I can produce a **pin-by-pin DIP netlist** (exact pin numbers for TI/NXP/ON Semiconductor pinouts) you can paste into a breadboard plan — say “Pin numbers — TI pinout” and I’ll list them.
* Or I can convert the wiring into a **Logisim netlist** or a **SPICE / NGSpice** netlist for simulation.

Which one should I generate now?
