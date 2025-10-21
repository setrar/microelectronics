

```sh
lsusb | grep UART
```
> Bus 002 Device 002: ID 0403:6014 Future Technology Devices International, Ltd FT232H Single HS USB-UART/FIFO IC


```sh
sudo /tools/Xilinx/2025.1/Vivado/data/xicom/cable_drivers/lin64/install_script/install_drivers/install_drivers
```
<details>

```lua
INFO: Installing cable drivers.
INFO: Script name = /tools/Xilinx/2025.1/Vivado/data/xicom/cable_drivers/lin64/install_script/install_drivers/install_drivers
INFO: HostName = distillery
INFO: RDI_BINROOT= /tools/Xilinx/2025.1/Vivado/data/xicom/cable_drivers/lin64/install_script/install_drivers
INFO: Current working dir = /home/b300098957
INFO: Kernel version = 6.8.0-85-generic.
INFO: Arch = x86_64.
Successfully installed Digilent Cable Drivers
--File /etc/udev/rules.d/52-xilinx-ftdi-usb.rules does not exist.
--File version of /etc/udev/rules.d/52-xilinx-ftdi-usb.rules = 0000.
--Updating rules file.
--File /etc/udev/rules.d/52-xilinx-pcusb.rules does not exist.
--File version of /etc/udev/rules.d/52-xilinx-pcusb.rules = 0000.
--Updating rules file.

INFO: Digilent Return code = 0
INFO: Xilinx Return code = 0
INFO: Xilinx FTDI Return code = 0
INFO: Return code = 0
INFO: Driver installation successful.
CRITICAL WARNING: Cable(s) on the system must be unplugged then plugged back in order for the driver scripts to update the cables.
```

</details>
