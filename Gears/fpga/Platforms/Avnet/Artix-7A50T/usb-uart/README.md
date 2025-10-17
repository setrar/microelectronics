# usb-uart connection



## :penguin: Linux

```sh
lsusb
```
>
```powershell
Bus 004 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
Bus 003 Device 003: ID 10c4:ea60 Silicon Labs CP210x UART Bridge
Bus 003 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
```

- [ ] Look for UART Bridge

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

```zsh
system_profiler SPUSBDataType
```
<details>

```powershell
USB:

    USB 3.1 Bus:

      Host Controller Driver: AppleT8112USBXHCI

        USB3.0 Hub             :

          Product ID: 0x0031
          Vendor ID: 0x291a
          Version: 3.e3
          Speed: Up to 5 Gb/s
          Manufacturer: Anker                  
          Location ID: 0x01200000 / 1
          Current Available (mA): 900
          Current Required (mA): 0
          Extra Operating Current (mA): 0

            USB3.0 Card Reader:

              Product ID: 0x0749
              Vendor ID: 0x05e3  (Genesys Logic, Inc.)
              Version: 15.39
              Serial Number: 000000001539
              Speed: Up to 5 Gb/s
              Manufacturer: Generic
              Location ID: 0x01210000 / 2
              Current Available (mA): 900
              Current Required (mA): 896
              Extra Operating Current (mA): 0

        USB2.0 Hub             :

          Product ID: 0x0020
          Vendor ID: 0x291a
          Version: 3.e3
          Speed: Up to 480 Mb/s
          Manufacturer: Anker                  
          Location ID: 0x01100000 / 3
          Current Available (mA): 500
          Current Required (mA): 0
          Extra Operating Current (mA): 0

            CP2104 USB to UART Bridge Controller:

              Product ID: 0xea60
              Vendor ID: 0x10c4  (Silicon Laboratories, Inc.)
              Version: 1.00
              Serial Number: 008FCD8C
              Speed: Up to 12 Mb/s
              Manufacturer: Silicon Labs
              Location ID: 0x01120000 / 5
              Current Available (mA): 500
              Current Required (mA): 100
              Extra Operating Current (mA): 0

            Anker USB-C Hub Device :

              Product ID: 0x8371
              Vendor ID: 0x291a
              Version: 0.01
              Serial Number: 0000000000000001
              Speed: Up to 480 Mb/s
              Manufacturer: Anker Innovations Limited
              Location ID: 0x01150000 / 4
              Current Available (mA): 500
              Current Required (mA): 100
              Extra Operating Current (mA): 0

    USB 3.1 Bus:

      Host Controller Driver: AppleT8112USBXHCI
```

- [ ] Look for UART Bridge


</details>
