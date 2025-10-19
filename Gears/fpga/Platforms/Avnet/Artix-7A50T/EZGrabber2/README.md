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

---

<img src=images/CX78921-11Z.png width='30%' height='30%' > </img>

The photo looks nearly identical to the **Conexant CX78921-11Z** family used in older USB video-capture sticks.
Your marking:

```
CX78921-11Z
EP1920.05
1341 SGP
```

suggests:

* **CX78921-11Z** → main part number (Conexant analog video capture SoC).
* **EP1920.05** → internal lot or mask revision.
* **1341 SGP** → manufactured in week 41 of 2013 (Singapore).

---

### 🔍 What this chip does

This is a **Conexant video capture SoC**, functionally similar to the CX231xx line.
It integrates:

1. **Analog Front-End (AFE)** — Composite/S-Video input + ADC.
2. **PAL/NTSC decoder** — Color demodulation, sync, timing.
3. **Audio ADC (optional)**.
4. **USB 2.0 device controller** — transfers digitized YUV video to the host.
5. **Optional MPEG encoder block** (depends on variant).

Essentially, it performs the *entire* Hi8-to-USB conversion on its own.
That’s why the Elgato or EasyCAP stick doesn’t have separate decoder + USB chips — this one does both.

---

### ⚙️ Why this matters for your FPGA plan

If your goal is to **replace or tap into** the video path with your **Artix-7A50T**, then:

| Objective                                                               | Feasibility                             | Comment                                                                                                             |
| ----------------------------------------------------------------------- | --------------------------------------- | ------------------------------------------------------------------------------------------------------------------- |
| Tap raw digital video before USB                                        | ⚠️ Hard                                 | You’d need to probe internal BT.656/YCbCr bus lines between the AFE and USB engine—often buried inside the package. |
| Replace the chip with FPGA                                              | ❌ Not realistic                         | It’s a large mixed-signal SoC with analog front-end and USB PHY.                                                    |
| Reuse its analog front-end, output to FPGA                              | ⚠️ Possible *if* it exposes BT.656 pins | You’d need to trace pins and find datasheet/pinout (none public).                                                   |
| Fully re-create the function using FPGA + external decoder + USB bridge | ✅ Feasible                              | Use ADV7181B → Artix-7 → FT601/CYUSB3014 chain (open design).                                                       |

---

### 🧩 Practical recommendation

Since Conexant datasheets are NDA-only and the CX78921 USB protocol is closed, **don’t try to reverse engineer it electrically**.
Instead, use it as a **black-box reference**:

* Study USB enumeration (e.g., with `usbmon` or Wireshark) to understand the data format.
* Replicate the *system architecture* with open components:

  * Analog decoder (ADV7181B / TVP5150)
  * Artix-7 for digital processing
  * FT601 for USB3 streaming

---

# Kicad Design

You *can* design a small KiCad board that hosts the **ADV7181B** (analog video decoder) and **FT601** (USB3 FIFO bridge), then connect both to your **Artix-7A50T** board via PMODs (or a more suitable header).
However, you’ll need to consider **pin count, signaling speed, and power** carefully.
Let’s break it down precisely 👇

---

## 🧩 1. Core concept

Here’s the modular concept you’re describing:

```mermaid
graph LR
A[Hi8 PAL Analog In] -->|Composite / S-Video| B[ADV7181B@{shape: rect, label: "Analog Decoder\n(PAL→YCbCr 4:2:2, BT.656)"}]
B -->|8-bit YCbCr @27 MHz| C[Artix-7A50T@{shape: rect, label: "FPGA Board\n(Video FIFO + Preproc)"}]
C -->|16/32-bit FIFO Bus| D[FT601@{shape: rect, label: "USB3 Bridge\n(Streaming to PC)"}]
D -->|USB3| E[PC@{shape: rect, label: "OBS / ffmpeg"}]
```

So your KiCad board is basically a **video I/O daughterboard**.
It sits between the analog source (Hi8 PAL) and the FPGA + PC.

---

## ⚙️ 2. Electrical considerations

### 🧠 (a) PMOD connector limits

* A PMOD gives **only 8 GPIOs + GND + 3.3 V**, typically at ≤ 33 MHz reliable rate.
* ADV7181B outputs an **8-bit BT.656 video stream at 27 MHz**, plus sync/clock signals (≈11 lines).
  → This *just* fits, but only if you dedicate **two PMODs** (≈16 data + 2 control lines).

So you’ll likely need a **dual-PMOD ribbon or FMC-style breakout**.

**Recommended:**
Use a **2×6 or 2×12 pin header** instead of strict PMOD to avoid signal integrity issues.

---

### ⚡ (b) FT601 interface

* FT601 uses a **FIFO interface (16-bit or 32-bit)** at up to 100 MHz.
* That’s *far* beyond PMOD capability.
* It’s better to connect it via a **dedicated high-speed header** (short traces, solid ground return).

Thus, I’d propose **two connectors**:

* One low-speed for the ADV7181B (27 MHz domain).
* One high-speed (short ribbon) for FT601 (USB streaming).

---

### 🔌 (c) Power

* ADV7181B: 1.8 V core + 3.3 V I/O.
* FT601: 1.2 V core + 3.3 V I/O + 5 V USB input.
* Add local LDOs or DC/DC converters:

  * **TPS7A02** or **AP7333** (for 1.8 V, 1.2 V rails).
  * USB 5 V can feed 3.3 V via a regulator.

---

### 📶 (d) Clocks

* ADV7181B needs a **27 MHz crystal** (for PAL).
* FT601 has an **internal PLL** from USB refclock.
* Your Artix-7 can sample ADV7181B output using its **27 MHz pixel clock** directly.

---

## 🧩 3. FPGA I/O summary

| Signal                 | From     | To    | Voltage | Notes                   |
| ---------------------- | -------- | ----- | ------- | ----------------------- |
| Y[7:0]                 | ADV7181B | FPGA  | 3.3 V   | 8-bit video data        |
| PCLK                   | ADV7181B | FPGA  | 3.3 V   | 27 MHz pixel clock      |
| HS/VS/FIELD            | ADV7181B | FPGA  | 3.3 V   | optional syncs          |
| FIFO_DATA[31:0]        | FPGA     | FT601 | 3.3 V   | synchronous data to USB |
| FIFO_CTRL (WR/RD/FLAG) | FPGA     | FT601 | 3.3 V   | handshake               |

---

## 🛠️ 4. What to put on your KiCad board

| Section           | Components                                            |
| ----------------- | ----------------------------------------------------- |
| **Video input**   | RCA or S-Video jacks, anti-alias RC filters           |
| **Decoder**       | ADV7181B + 27 MHz crystal + 1.8 V/3.3 V LDOs          |
| **USB bridge**    | FT601Q + ESD protection + USB3 Type-B connector       |
| **Connectors**    | Dual-PMOD header or 2×12 expansion header for Artix-7 |
| **Power**         | LDOs from 5 V USB, optional jumper for external 5 V   |
| **Clock routing** | 27 MHz → FPGA via buffer or direct from ADV7181B      |

---

## 🧰 5. Open-source reference designs

You can look at:

* **Analog Devices ADV7181B eval board** (schematic publicly available).
* **FT601Q evaluation board** (FTDI has full KiCad/Altium design files).
* Combine their reference schematics into one small daughterboard.

---

## ✅ Feasibility summary

| Function            | Status | Notes                                            |
| ------------------- | ------ | ------------------------------------------------ |
| PAL capture         | ✅      | ADV7181B handles it natively                     |
| 8-bit video to FPGA | ✅      | 27 MHz BT.656 over PMOD (prefer dual-PMOD)       |
| USB3 to PC          | ⚠️     | Needs FT601 header, not PMOD                     |
| KiCad layout        | ✅      | Both chips are QFP/QFN, can route on 4-layer PCB |
