# EZGrabber

### Can I revert engineer the EZGrabber video capture device from Hi8 PAL to USB with the Artix-7A50T?

That’s an ambitious but *fascinating* idea — and yes, to a limited extent, you **can reverse engineer and reimplement** the core function of an EZGrabber video capture device (Hi8 PAL → USB) using an **Artix-7A50T**, but there are **practical constraints** you need to understand before diving in.

Let’s unpack it carefully 👇

---

## 🧩 1. What the EZGrabber device actually does

A typical **EZGrabber analog video capture dongle** (like the “Video Capture USB” or “EyeTV” line) does:

1. **Analog front-end (AFE):**

   * Accepts composite (CVBS) or S-Video (Y/C) PAL/NTSC input.
   * Uses a **video decoder IC** (e.g., ADV7180 / CX23102 / SAA7113) to:

     * Perform ADC (sampling analog Y/C)
     * Apply color demodulation
     * Output **digital YCbCr 4:2:2** video over an 8- or 16-bit bus at ~27 MHz.
2. **Video compression:**

   * A small ASIC or DSP compresses to **MPEG-2/MJPEG/H.264**.
3. **USB bridge:**

   * Transfers compressed data to the host PC over **USB 2.0 (480 Mbps)**.

---

## 🧠 2. What the Artix-7A50T can handle

The Artix-7A50T *can* handle the **digital video domain**, but **not the analog** or **USB host/device** parts *alone*.
Here’s what’s possible:

| Function                                 | Can Artix-7A50T handle it?          | Notes                                                                              |
| ---------------------------------------- | ----------------------------------- | ---------------------------------------------------------------------------------- |
| **ADC + PAL decoding**                   | ❌ Not directly                      | Needs an external video decoder IC (e.g. ADV7181B)                                 |
| **Digital video buffering / processing** | ✅ Yes                               | Use FPGA fabric for scaling, color conversion, sync, etc.                          |
| **Video compression**                    | ⚠️ Possible but expensive in LUTs   | You can do raw YCbCr or lightweight RLE/DPCM, but not real-time H.264 in this FPGA |
| **USB streaming**                        | ⚠️ Only with external PHY + soft IP | Use ULPI PHY + open USB core or route video via UART/Ethernet instead              |

---

## ⚙️ 3. Feasible reverse-engineered pipeline

Here’s a **practical open-source flow** you could build on the Artix-7A50T:

```mermaid
graph LR
A[Hi8 PAL analog] -->|Composite/S-Video| B[ADV7181B@{shape: rect, label: "Analog Decoder\n(ADC + PAL to YCbCr 4:2:2)"}]
B -->|8/16-bit BT.656| C[Artix-7@{shape: rect, label: "Video Buffer + Simple Preproc\n(Deinterlace, Resize, YUV→RGB)"}]
C -->|Parallel| D[FT601Q@{shape: rect, label: "USB3 FIFO Bridge"}]
D -->|USB3| E[PC@{shape: rect, label: "OBS / ffmpeg"}]
```

**Hardware:**

* **ADV7181B** or **TVP5150** for analog video decode.
* **FT601** or **CYUSB3014** for USB 3.0 bridge.
* **Artix-7A50T** handles the middle (video processing).

**Software:**

* Host captures raw YUV frames via libusb or OBS plugin.
* Compression and encoding happen in software (e.g. ffmpeg on host).

---

## ⚡ 4. Challenges

| Area                                | Difficulty   | Comment                                                           |
| ----------------------------------- | ------------ | ----------------------------------------------------------------- |
| Reverse-engineering EZGrabber firmware | 🔥 Hard      | Proprietary; encrypted USB traffic; not worth replicating exactly |
| Real-time H.264 in FPGA             | 🔥 Very hard | Needs dedicated encoder or large FPGA                             |
| USB device stack in HDL             | 🧠 Moderate  | Doable with open cores, but USB3 requires a PHY                   |
| Analog input quality                | 🧠 Moderate  | PAL has interlacing and colorburst sync issues; use decoder IC    |

---

## 🧩 5. Recommended approach

If your goal is **learning and open video capture**, I’d recommend:

1. **Use a known decoder IC** → ADV7181B or TVP5150.
2. **Use your Artix-7A50T board** to process BT.656 digital video.
3. **Stream via FT601 (USB3) or Ethernet**.
4. Use **OBS or ffmpeg** to capture on the host.

This gives you an open, FPGA-based equivalent of an EZGrabber — but with modular, documented hardware.
