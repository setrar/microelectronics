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

