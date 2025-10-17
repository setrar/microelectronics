# usb-uart connection



## :penguin: Linux

- [ ] Look for UART Bridge

```sh
lsusb | grep CP2104
```
>
```powershell
Bus 003 Device 003: ID 10c4:ea60 Silicon Labs CP210x UART Bridge
```

- [ ] Connect

```sh
screen /dev/ttyUSB0 115200
```
>
```powershell
Press any key to return to main menu

********************************************************
********************************************************
**           Avnet Artix-7 50T Evaluation Kit         **
********************************************************
********************************************************

Choose Feature to Test:
1: IIC Test
2: DDR3 Memory Test
3: LED Test
4: DIP Switch Test
5: Push Button Test
A: Run all tests
0: Exit
```

## :apple: MacOS

### Detection

Your Mac **detects the CP2104 USB-to-UART bridge** from your Artix-7A50T board:

```zsh
system_profiler SPUSBDataType | grep -A 5 "CP210"
```
<details>

```
            CP2104 USB to UART Bridge Controller:

              Product ID: 0xea60
              Vendor ID: 0x10c4  (Silicon Laboratories, Inc.)
              Version: 1.00
              Serial Number: 008FCD8C
              Speed: Up to 12 Mb/s
```

</details>

✅ This confirms that the USB-UART hardware is correctly recognized by macOS.

---

### Next Steps

1. **Check the serial port**:

```bash
ls /dev/cu.*
```

You already saw `/dev/cu.usbserial-008FCD8C` — that’s your device.

2. **Test UART communication**:

```bash
screen /dev/cu.usbserial-008FCD8C 115200
```

* Replace `115200` with the FPGA UART baud rate.
* To exit `screen`: `Ctrl-A` → `K` → `Y`.

# :books: References

Classic **`screen` confusion on macOS**! The `Ctrl-A → \` doesn’t work to exit is **because `\` is not the default quit command in `screen`**, and macOS Terminal may also interpret certain key sequences differently.

---

### 1️⃣ Default `screen` key bindings

* **`Ctrl-A`** is the **command prefix** in `screen`.
* After pressing `Ctrl-A`, you issue a **command key**:

| Command | Action                                                               |
| ------- | -------------------------------------------------------------------- |
| `K`     | Kill the current window (you’ll be asked to confirm)                 |
| `D`     | Detach from the screen session (leaves it running in the background) |
| `\`     | **Quit all screen sessions** (asks for confirmation)                 |

So normally, `Ctrl-A \` **should quit all sessions**, but there are some quirks on macOS:

---

### 2️⃣ Why `Ctrl-A \` may not work

1. **Terminal key interpretation**

   * macOS Terminal, iTerm2, or other terminal apps sometimes intercept `\` differently (especially with Option/Alt keys).
   * If your keyboard layout or Terminal settings remap `\`, `screen` never sees it.

2. **Screen configuration**

   * If you have a `.screenrc` file, the quit binding may be overridden.
   * Some default macOS `screen` builds disable `\` as a global quit.

---

### 3️⃣ Recommended ways to exit `screen` on macOS

#### Option A — Kill current window

```text
Ctrl-A K
```

* `screen` will ask: `Really kill this window [y/n] ?`
* Press `y` to close.

#### Option B — Detach and kill from terminal

1. Detach the session:

```text
Ctrl-A D
```

* You’re returned to your shell.

2. List sessions:

```bash
screen -ls
```

* Example output: `12345.pts-0.MacBook (Detached)`

3. Kill the session:

```bash
screen -X -S 12345 quit
```

---

#### Option C — Quit all windows (works in most cases)

```text
Ctrl-A \
```

* If it doesn’t respond, try pressing `Ctrl-A` **then hold Shift** and type `\` (i.e., `Ctrl-A Shift-\`).
* This ensures Terminal sends the literal backslash.


Great! Here's a **simple macOS CLI setup using `picocom`** (recommended over `screen`) that continuously logs UART output from your Digilent device and reconnects if it resets.

---

### **1️⃣ Install picocom**

```bash
brew install picocom
```

---

### **2️⃣ Create a small reconnect script**

You can make a script called `digilent-uart.sh`:

```bash
#!/bin/bash

DEVICE="/dev/cu.usbserial-210251946724"  # Digilent USB-UART device
BAUD=115200                               # FPGA UART baud rate

while true; do
    echo "Connecting to $DEVICE at $BAUD baud..."
    picocom --baud $BAUD --flow n $DEVICE
    echo "Disconnected. Reconnecting in 2s..."
    sleep 2
done
```

* Make it executable:

```bash
chmod +x digilent-uart.sh
```

---

### **3️⃣ Run the script**

```bash
./digilent-uart.sh
```

* It will automatically reconnect if the FPGA resets or USB disconnects.
* Displays all UART output in real-time.
* Press `Ctrl-A` then `Ctrl-X` inside picocom to exit safely.

---

### ✅ Advantages

* Automatically reconnects — no need to manually restart `screen`.
* Handles line endings and baud rate consistently.
* Works well for long FPGA debug sessions.

