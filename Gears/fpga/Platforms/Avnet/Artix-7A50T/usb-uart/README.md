# usb-uart connection

- [ ] Linux

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
