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

Nice — that part number matches what other people have found on those cheap USB “EZGrabber” / EZGrabber-style capture sticks.  The **CX78921-11Z** (often shown as `CX78921-11z`) appears to be a Conexant / Conexant-family single-chip video capture SoC used on many low-cost USB video capture dongles. Multiple community posts and driver threads identify that exact marking and describe it as the single chip that does the video/audio capture + USB on those sticks. ([LinuxTV][1])

### What that implies (short)

* **The chip already contains the analogue decoder + ADC + USB interface (and sometimes a compressor).** In other words the CX78921 is doing the *exact* conversion you wanted to reimplement (Hi8/PAL → USB) on one package. That’s why many of those dongles are so small. ([Patrolfull][2])
* **Reverse-engineering the EZGrabber becomes a firmware/driver and protocol task, not a pure-hardware FPGA task.** If the chip exposes standard USB video class or uses a driver compatible with `cx231xx` family, you can capture frames on a PC without rebuilding the analog/USB chain. The Linux cx231xx driver tree and related mailing-list threads discuss support for these OTG/EZGrabber devices. ([Linux Media][3])
* **If you still want to use the Artix-7**, you have two practical options:

  1. **Use the CX78921 on the EZGrabber PCB as the AFE + USB interface** and let the host do encoding — i.e., *don’t* replace that chip; instead intercept/inspect USB traffic or adapt the board to feed the Artix only for additional processing (hard to do because CX78921 combines everything). ([Patrolfull][2])
  2. **Replace the CX78921 with discrete parts**: an analog video decoder (e.g., ADV7181 / TVP5150), route parallel BT.656/BT.1120 into the Artix-7 for buffering/preproc, then use an FTDI/Cypress USB FIFO (or external USB3 bridge) to get frames to the PC. That’s the approach you mentioned before and is fully feasible but requires more PCB work and extra components. (This is the route if you *must* have FPGA processing/encoding.) ([The Digital FAQ][4])

### Practical next steps I can do for you right now

* I can **pull together the community notes and kernel driver references** about CX78921 / OTG102 / EZGrabber so you can see how Linux/Windows drivers talk to it (helpful if you want to reuse the existing chip). ([Linux Media][3])
* Or I can **draw the RTL/block diagram** for the discrete approach (ADV7181 → Artix-7 → FT601) you mentioned earlier — showing clocks, data widths, and the logic blocks you’d need in the FPGA (capture FIFO, sync detector, optional scaler/deinterlacer, USB FIFO interface).
* If you have **clear photos of the EZGrabber PCB / the chip marking / any silkscreen IDs**, share them and I’ll point out the pins and likely interfaces to confirm whether that chip is acting as a full USB SoC on your board.

Which would you like me to do next — gather the driver/firmware references for the CX78921, or create the discrete-part Artix-7 block diagram (ADV7181 + FT601) so you can plan a replacement design?

[1]: https://www.linuxtv.org/wiki/index.php/OTG102?utm_source=chatgpt.com "OTG102 - LinuxTVWiki"
[2]: https://patrolfull.blogg.se/2022/june/ez-grabber-2-windows-8.html?utm_source=chatgpt.com "Ez grabber 2 windows 8"
[3]: https://linux-media.vger.kernel.narkive.com/xbsm0L6h/cx231xx-add-support-for-otg102-aka-ezgrabber2?utm_source=chatgpt.com "cx231xx : Add support for OTG102 aka EZGrabber2"
[4]: https://www.digitalfaq.com/forum/video-capture/9190-comparing-capture-cards.html?utm_source=chatgpt.com "Comparing capture cards handling lousy tapes?"
