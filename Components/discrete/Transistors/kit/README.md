# Kit

A **ready-to-go MOSFET shopping list** for discrete DIY CMOS FPGA experiments. I’ve included **multiple options** so you can grab whatever is in stock at an old electronics store. These are **breadboard-friendly, logic-level, low-current small-signal MOSFETs**.


---

## **1. N-Channel MOSFETs (for pull-down networks and pass transistors)**

| Part Number   | Package   | $V_{DS}$ | $V_{GS}(th)$ | Notes                                                             |
| ------------- | --------- | ---- | -------- | ----------------------------------------------------------------- |
| **2N7000**    | TO-92     | 60V  | 2–3V     | Classic, widely available, easy to breadboard   2N**7**000                  |
| **BS170**     | TO-92     | 60V  | 2–3V     | Very similar to 2N7000                                            |
| **VN2222**    | TO-92     | 60V  | 2–3V     | Small-signal, you mentioned this one                              |
| **IRLML6344** | SOT-23    | 30V  | 1–2V     | Tiny, very low $R_{DS}(on)$, optional if you have breadboard adapters |
| **2N7002**    | SMD/TO-92 | 60V  | 1–3V     | Surface-mount, optional with adapters                             |

---

## **2. P-Channel MOSFETs (for pull-up networks and pass transistors / transmission gates)**

| Part Number  | Package | $V_{DS}$ | $V_{GS}$    | Notes                                            |
| ------------ | ------- | ---- | ----------- | ------------------------------------------------ |
| **BSS84**    | TO-92   | 50V  | –2 to –4V   | Classic, breadboard-friendly, logic-level        |
| **IRF9540N** | TO-220  | 100V | –2 to –4V   | Larger, optional if TO-92 not available          |
| **PMV20EN**  | TO-92   | 20V  | –1.5 to –3V | Logic-level, small currents, breadboard-friendly |
| **FQP27P06** | TO-220  | 60V  | –2 to –4V   | Higher current than needed, still usable         |
| **IRF5210**  | TO-220  | 100V | –2 to –4V   | Optional, overkill but works for low-speed logic |

---

## **3. Stocking Quantities Recommendation (for multiple tiles)**

* **2-LUT tile:** N-MOS ≈ 20, P-MOS ≈ 20
* **4-LUT tile:** N-MOS ≈ 40, P-MOS ≈ 40
* Buy **extra** in case of faulty transistors or mistakes during breadboarding.

---

✅ **Tips for old stores:**

1. Prefer **TO-92 packages** for easy breadboarding.
2. Make sure **$V_{GS}(th)$ < 3V** for 5V logic.
3. Any logic-level small-signal N-MOS / P-MOS in that list works; you can mix and match.
4. Avoid power MOSFETs with high $V_{GS}(th)$ — they may not fully turn on at 5V.

