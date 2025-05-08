# Artix-7A50T



## **Project X-Ray**:

Yes, **Project X-Ray *can* be used with the Artix-7 50T**, specifically for certain variants—**but with some caveats**:

---

### ✅ Supported Devices

Project X-Ray officially targets **Xilinx 7-series FPGAs**, and within that family, the **Artix-7 XC7A50T** is **partially supported**, especially the:

* **xc7a50ticsg324-1L** and similar packages/speeds.

You can check the specific device support list in the [Project X-Ray database](https://github.com/SymbiFlow/prjxray-db) or their [status page](https://github.com/SymbiFlow/prjxray#supported-devices).

---

### ❗ Caveats

* **Not all speed grades and packages** are covered. If you have a less-common package, the bitstream mapping may not be complete.
* Full bitstream support depends on how far the reverse engineering effort has gone for your **exact** device.
* Even if partially unsupported, **you may be able to help contribute fuzzing results** to expand support.

---

### 🔍 How to Check

Run:

```bash
prjxray-db-util xc7a50t
```

Or look in:

```
prjxray-db/artix7/
```

If your exact part number is listed under `xc7a50t`, it’s supported. If not, you might need to do some fuzzing yourself using Project X-Ray’s tooling.

---

Would you like help checking support for your board's exact part number?



# References

- [ ] [Artix 7A50T - Hardware User Guide ](https://www.avnet.com/apac/products/product-highlights/xilinx-artix7)
