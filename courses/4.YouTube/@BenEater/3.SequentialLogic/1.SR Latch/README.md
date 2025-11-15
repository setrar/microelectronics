# [SR latch](https://www.youtube.com/watch?v=KM0DdEaY5sY)


# :books: References

The **74HC** family is the CMOS, low-power, high-speed successor to the older bipolar **74LS** family.

So you are looking for the **HC equivalent** of **74LS32** (a **quad 2-input OR gate**).

# ✅ **Direct Equivalent**

### ✔ **74HC32**

This is the CMOS-based drop-in replacement for the 74LS32.

It has the same:

* Pinout
* Logic function (quad 2-input OR)
* Operating voltage range (typically 2–6 V, best at 5 V)

### Common variants:

* **74HC32** → standard CMOS
* **74HCT32** → CMOS that is TTL-input compatible

  * *Use HCT if you’re mixing with LS-family signals*

---

# ✔ Summary

| LS Part    | CMOS Replacement | TTL-compatible CMOS |
| ---------- | ---------------- | ------------------- |
| **74LS32** | **74HC32**       | **74HCT32**         |

---

# When to choose HCT instead of HC?

Use **74HCT32** if:

* You are driving it with **74LS**, **74ALS**, or **TTL-output** chips
* You need **same input thresholds** as LS (TTL-level)

Use **74HC32** if:

* Everything in the circuit is CMOS (74HC, CD4000, etc.)

---

If you want, I can generate a complete table mapping **all 74LS → 74HC/HCT equivalents** for your DIY FPGA logic-cell project.
