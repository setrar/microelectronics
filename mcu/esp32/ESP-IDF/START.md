- [ ] [Start a Project](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html#start-a-project)

```
get_idf
```

```
cp -r $IDF_PATH/examples/get-started/hello_world .
```


- [ ] [Configure your project](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html#configure-your-project)

```
idf.py set-target esp32s3
idf.py menuconfig
```

- [ ] [Build the project](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html#build-the-project)

```
idf.py build
```
> Returns
```powershell
Executing action: all (aliases: build)
Running ninja in directory /Users/valiha/Developer/esp/hello_world/build
Executing "ninja all"...
[0/1] Re-running CMake...
-- git rev-parse returned 'fatal: not a git repository (or any of the parent directories): .git'
-- Could not use 'git describe' to determine PROJECT_VER.
-- Building ESP-IDF components for target esp32s3
-- Project sdkconfig file /Users/valiha/Developer/esp/hello_world/sdkconfig
-- Compiler supported targets: xtensa-esp-elf
-- App "hello_world" version: 1
-- Adding linker script /Users/valiha/Developer/esp/hello_world/build/esp-idf/esp_system/ld/memory.ld
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/esp_system/ld/esp32s3/sections.ld.in
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/esp_rom/esp32s3/ld/esp32s3.rom.ld
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/esp_rom/esp32s3/ld/esp32s3.rom.api.ld
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/esp_rom/esp32s3/ld/esp32s3.rom.libgcc.ld
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/esp_rom/esp32s3/ld/esp32s3.rom.newlib.ld
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/esp_rom/esp32s3/ld/esp32s3.rom.version.ld
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/soc/esp32s3/ld/esp32s3.peripherals.ld
-- Components: app_trace app_update bootloader bootloader_support bt cmock console cxx driver efuse esp-tls esp_adc esp_app_format esp_bootloader_format esp_coex esp_common esp_eth esp_event esp_gdbstub esp_hid esp_http_client esp_http_server esp_https_ota esp_https_server esp_hw_support esp_lcd esp_local_ctrl esp_mm esp_netif esp_netif_stack esp_partition esp_phy esp_pm esp_psram esp_ringbuf esp_rom esp_system esp_timer esp_wifi espcoredump esptool_py fatfs freertos hal heap http_parser idf_test ieee802154 json log lwip main mbedtls mqtt newlib nvs_flash nvs_sec_provider openthread partition_table perfmon protobuf-c protocomm pthread sdmmc soc spi_flash spiffs tcp_transport touch_element ulp unity usb vfs wear_levelling wifi_provisioning wpa_supplicant xtensa
-- Component paths: /Users/valiha/Developer/esp/esp-idf/components/app_trace /Users/valiha/Developer/esp/esp-idf/components/app_update /Users/valiha/Developer/esp/esp-idf/components/bootloader /Users/valiha/Developer/esp/esp-idf/components/bootloader_support /Users/valiha/Developer/esp/esp-idf/components/bt /Users/valiha/Developer/esp/esp-idf/components/cmock /Users/valiha/Developer/esp/esp-idf/components/console /Users/valiha/Developer/esp/esp-idf/components/cxx /Users/valiha/Developer/esp/esp-idf/components/driver /Users/valiha/Developer/esp/esp-idf/components/efuse /Users/valiha/Developer/esp/esp-idf/components/esp-tls /Users/valiha/Developer/esp/esp-idf/components/esp_adc /Users/valiha/Developer/esp/esp-idf/components/esp_app_format /Users/valiha/Developer/esp/esp-idf/components/esp_bootloader_format /Users/valiha/Developer/esp/esp-idf/components/esp_coex /Users/valiha/Developer/esp/esp-idf/components/esp_common /Users/valiha/Developer/esp/esp-idf/components/esp_eth /Users/valiha/Developer/esp/esp-idf/components/esp_event /Users/valiha/Developer/esp/esp-idf/components/esp_gdbstub /Users/valiha/Developer/esp/esp-idf/components/esp_hid /Users/valiha/Developer/esp/esp-idf/components/esp_http_client /Users/valiha/Developer/esp/esp-idf/components/esp_http_server /Users/valiha/Developer/esp/esp-idf/components/esp_https_ota /Users/valiha/Developer/esp/esp-idf/components/esp_https_server /Users/valiha/Developer/esp/esp-idf/components/esp_hw_support /Users/valiha/Developer/esp/esp-idf/components/esp_lcd /Users/valiha/Developer/esp/esp-idf/components/esp_local_ctrl /Users/valiha/Developer/esp/esp-idf/components/esp_mm /Users/valiha/Developer/esp/esp-idf/components/esp_netif /Users/valiha/Developer/esp/esp-idf/components/esp_netif_stack /Users/valiha/Developer/esp/esp-idf/components/esp_partition /Users/valiha/Developer/esp/esp-idf/components/esp_phy /Users/valiha/Developer/esp/esp-idf/components/esp_pm /Users/valiha/Developer/esp/esp-idf/components/esp_psram /Users/valiha/Developer/esp/esp-idf/components/esp_ringbuf /Users/valiha/Developer/esp/esp-idf/components/esp_rom /Users/valiha/Developer/esp/esp-idf/components/esp_system /Users/valiha/Developer/esp/esp-idf/components/esp_timer /Users/valiha/Developer/esp/esp-idf/components/esp_wifi /Users/valiha/Developer/esp/esp-idf/components/espcoredump /Users/valiha/Developer/esp/esp-idf/components/esptool_py /Users/valiha/Developer/esp/esp-idf/components/fatfs /Users/valiha/Developer/esp/esp-idf/components/freertos /Users/valiha/Developer/esp/esp-idf/components/hal /Users/valiha/Developer/esp/esp-idf/components/heap /Users/valiha/Developer/esp/esp-idf/components/http_parser /Users/valiha/Developer/esp/esp-idf/components/idf_test /Users/valiha/Developer/esp/esp-idf/components/ieee802154 /Users/valiha/Developer/esp/esp-idf/components/json /Users/valiha/Developer/esp/esp-idf/components/log /Users/valiha/Developer/esp/esp-idf/components/lwip /Users/valiha/Developer/esp/hello_world/main /Users/valiha/Developer/esp/esp-idf/components/mbedtls /Users/valiha/Developer/esp/esp-idf/components/mqtt /Users/valiha/Developer/esp/esp-idf/components/newlib /Users/valiha/Developer/esp/esp-idf/components/nvs_flash /Users/valiha/Developer/esp/esp-idf/components/nvs_sec_provider /Users/valiha/Developer/esp/esp-idf/components/openthread /Users/valiha/Developer/esp/esp-idf/components/partition_table /Users/valiha/Developer/esp/esp-idf/components/perfmon /Users/valiha/Developer/esp/esp-idf/components/protobuf-c /Users/valiha/Developer/esp/esp-idf/components/protocomm /Users/valiha/Developer/esp/esp-idf/components/pthread /Users/valiha/Developer/esp/esp-idf/components/sdmmc /Users/valiha/Developer/esp/esp-idf/components/soc /Users/valiha/Developer/esp/esp-idf/components/spi_flash /Users/valiha/Developer/esp/esp-idf/components/spiffs /Users/valiha/Developer/esp/esp-idf/components/tcp_transport /Users/valiha/Developer/esp/esp-idf/components/touch_element /Users/valiha/Developer/esp/esp-idf/components/ulp /Users/valiha/Developer/esp/esp-idf/components/unity /Users/valiha/Developer/esp/esp-idf/components/usb /Users/valiha/Developer/esp/esp-idf/components/vfs /Users/valiha/Developer/esp/esp-idf/components/wear_levelling /Users/valiha/Developer/esp/esp-idf/components/wifi_provisioning /Users/valiha/Developer/esp/esp-idf/components/wpa_supplicant /Users/valiha/Developer/esp/esp-idf/components/xtensa
-- Configuring done (1.8s)
-- Generating done (0.2s)
-- Build files have been written to: /Users/valiha/Developer/esp/hello_world/build
[10/956] Generating ../../partition_table/partition-table.bin
Partition table binary generated. Contents:
*******************************************************************************
# ESP-IDF Partition Table
# Name, Type, SubType, Offset, Size, Flags
nvs,data,nvs,0x9000,24K,
phy_init,data,phy,0xf000,4K,
factory,app,factory,0x10000,1M,
*******************************************************************************
[522/956] Performing configure step for 'bootloader'
-- Found Git: /usr/bin/git (found version "2.39.3 (Apple Git-145)") 
-- The C compiler identification is GNU 13.2.0
-- The CXX compiler identification is GNU 13.2.0
-- The ASM compiler identification is GNU
-- Found assembler: /Users/valiha/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20230928/xtensa-esp-elf/bin/xtensa-esp32s3-elf-gcc
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /Users/valiha/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20230928/xtensa-esp-elf/bin/xtensa-esp32s3-elf-gcc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /Users/valiha/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20230928/xtensa-esp-elf/bin/xtensa-esp32s3-elf-g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Building ESP-IDF components for target esp32s3
-- Project sdkconfig file /Users/valiha/Developer/esp/hello_world/sdkconfig
-- Compiler supported targets: xtensa-esp-elf
-- Looking for sys/types.h
-- Looking for sys/types.h - found
-- Looking for stdint.h
-- Looking for stdint.h - found
-- Looking for stddef.h
-- Looking for stddef.h - found
-- Check size of time_t
-- Check size of time_t - done
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/soc/esp32s3/ld/esp32s3.peripherals.ld
-- Bootloader project name: "bootloader" version: 1
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/esp_rom/esp32s3/ld/esp32s3.rom.ld
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/esp_rom/esp32s3/ld/esp32s3.rom.api.ld
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/esp_rom/esp32s3/ld/esp32s3.rom.libgcc.ld
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/esp_rom/esp32s3/ld/esp32s3.rom.newlib.ld
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/bootloader/subproject/main/ld/esp32s3/bootloader.ld
-- Adding linker script /Users/valiha/Developer/esp/esp-idf/components/bootloader/subproject/main/ld/esp32s3/bootloader.rom.ld
-- Components: bootloader bootloader_support efuse esp_app_format esp_bootloader_format esp_common esp_hw_support esp_rom esp_system esptool_py freertos hal log main micro-ecc newlib partition_table soc spi_flash xtensa
-- Component paths: /Users/valiha/Developer/esp/esp-idf/components/bootloader /Users/valiha/Developer/esp/esp-idf/components/bootloader_support /Users/valiha/Developer/esp/esp-idf/components/efuse /Users/valiha/Developer/esp/esp-idf/components/esp_app_format /Users/valiha/Developer/esp/esp-idf/components/esp_bootloader_format /Users/valiha/Developer/esp/esp-idf/components/esp_common /Users/valiha/Developer/esp/esp-idf/components/esp_hw_support /Users/valiha/Developer/esp/esp-idf/components/esp_rom /Users/valiha/Developer/esp/esp-idf/components/esp_system /Users/valiha/Developer/esp/esp-idf/components/esptool_py /Users/valiha/Developer/esp/esp-idf/components/freertos /Users/valiha/Developer/esp/esp-idf/components/hal /Users/valiha/Developer/esp/esp-idf/components/log /Users/valiha/Developer/esp/esp-idf/components/bootloader/subproject/main /Users/valiha/Developer/esp/esp-idf/components/bootloader/subproject/components/micro-ecc /Users/valiha/Developer/esp/esp-idf/components/newlib /Users/valiha/Developer/esp/esp-idf/components/partition_table /Users/valiha/Developer/esp/esp-idf/components/soc /Users/valiha/Developer/esp/esp-idf/components/spi_flash /Users/valiha/Developer/esp/esp-idf/components/xtensa
-- Configuring done (4.9s)
-- Generating done (0.1s)
-- Build files have been written to: /Users/valiha/Developer/esp/hello_world/build/bootloader
[111/112] Generating binary image from built executable
esptool.py v4.7.dev2
Creating esp32s3 image...
Merged 2 ELF sections
Successfully created esp32s3 image.
Generated /Users/valiha/Developer/esp/hello_world/build/bootloader/bootloader.bin
[112/112] cd /Users/valiha/Developer/esp/hello_worl...per/esp/hello_world/build/bootloader/bootloader.bin
Bootloader binary size 0x5240 bytes. 0x2dc0 bytes (36%) free.
[955/956] Generating binary image from built executable
esptool.py v4.7.dev2
Creating esp32s3 image...
Merged 2 ELF sections
Successfully created esp32s3 image.
Generated /Users/valiha/Developer/esp/hello_world/build/hello_world.bin
[956/956] cd /Users/valiha/Developer/esp/hello_worl...iha/Developer/esp/hello_world/build/hello_world.bin
hello_world.bin binary size 0x35410 bytes. Smallest app partition is 0x100000 bytes. 0xcabf0 bytes (79%) free.

Project build complete. To flash, run:
 idf.py flash
or
 idf.py -p PORT flash
or
 python -m esptool --chip esp32s3 -b 460800 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_size 2MB --flash_freq 80m 0x0 build/bootloader/bootloader.bin 0x8000 build/partition_table/partition-table.bin 0x10000 build/hello_world.bin
or from the "/Users/valiha/Developer/esp/hello_world/build" directory
 python -m esptool --chip esp32s3 -b 460800 --before default_reset --after hard_reset write_flash "@flash_args"
```

- [ ] Check ports

* you may need to reset the board to see the correct PORT name

```
ls -l /dev/cu.*
```
> returns
```
crw-rw-rw-  1 root  wheel  0x9000001  6 Nov 21:56 /dev/cu.Bluetooth-Incoming-Port
crw-rw-rw-  1 root  wheel  0x9000003  6 Nov 22:01 /dev/cu.usbmodem1101
```

- [ ] [Flash onto the device](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html#flash-onto-the-device)

```
idf.py -p /dev/cu.usbmodem1101 flash
```
> Returns
```powershell
Executing action: flash
Running ninja in directory /Users/valiha/Developer/esp/hello_world/build
Executing "ninja flash"...
[1/5] cd /Users/valiha/Developer/esp/hello_world/bu...iha/Developer/esp/hello_world/build/hello_world.bin
hello_world.bin binary size 0x35410 bytes. Smallest app partition is 0x100000 bytes. 0xcabf0 bytes (79%) free.
[1/1] cd /Users/valiha/Developer/esp/hello_world/bu...per/esp/hello_world/build/bootloader/bootloader.bin
Bootloader binary size 0x5240 bytes. 0x2dc0 bytes (36%) free.
[4/5] cd /Users/valiha/Developer/esp/esp-idf/compon...esp-idf/components/esptool_py/run_serial_tool.cmake
esptool.py --chip esp32s3 -p /dev/cu.usbmodem1101 -b 460800 --before=default_reset --after=hard_reset write_flash --flash_mode dio --flash_freq 80m --flash_size 2MB 0x0 bootloader/bootloader.bin 0x10000 hello_world.bin 0x8000 partition_table/partition-table.bin
esptool.py v4.7.dev2
Serial port /dev/cu.usbmodem1101
Connecting...
Chip is ESP32-S3 (QFN56) (revision v0.2)
Features: WiFi, BLE
Crystal is 40MHz
MAC: 48:27:e2:66:a5:88
Uploading stub...
Running stub...
Stub running...
Changing baud rate to 460800
Changed.
Configuring flash size...
Flash will be erased from 0x00000000 to 0x00005fff...
Flash will be erased from 0x00010000 to 0x00045fff...
Flash will be erased from 0x00008000 to 0x00008fff...
Compressed 21056 bytes to 13076...
Writing at 0x00000000... (100 %)
Wrote 21056 bytes (13076 compressed) at 0x00000000 in 0.4 seconds (effective 464.0 kbit/s)...
Hash of data verified.
Compressed 218128 bytes to 110750...
Writing at 0x00040291... (100 %)
Wrote 218128 bytes (110750 compressed) at 0x00010000 in 1.8 seconds (effective 958.8 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 103...
Writing at 0x00008000... (100 %)
Wrote 3072 bytes (103 compressed) at 0x00008000 in 0.1 seconds (effective 390.1 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
Done
```

- [ ] [Monitor the output](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html#monitor-the-output)

```
idf.py -p /dev/cu.usbmodem1101 monitor
```
> Returns
```powershell
Executing action: monitor
Running idf_monitor in directory /Users/valiha/Developer/esp/hello_world
Executing "/Users/valiha/.espressif/python_env/idf5.2_py3.11_env/bin/python /Users/valiha/Developer/esp/esp-idf/tools/idf_monitor.py -p /dev/cu.usbmodem1101 -b 115200 --toolchain-prefix xtensa-esp32s3-elf- --target esp32s3 --revision 0 /Users/valiha/Developer/esp/hello_world/build/hello_world.elf -m '/Users/valiha/.espressif/python_env/idf5.2_py3.11_env/bin/python' '/Users/valiha/Developer/esp/esp-idf/tools/idf.py' '-p' '/dev/cu.usbmodem1101'"...
--- esp-idf-monitor 1.3.3 on /dev/cu.usbmodem1101 115200 ---
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x15 (USB_UART_CHIP_RESET),boot:0x2b (SPI_FAST_FLASH_BOOT)
Saved PC:0x40378282
0x40378282: esp_cpu_wait_for_intr at /Users/valiha/Developer/esp/esp-idf/components/esp_hw_support/cpu.c:145

SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce3810,len:0x178c
load:0x403c9700,len:0x4
load:0x403c9704,len:0xcbc
load:0x403cc700,len:0x2d94
entry 0x403c9914
I (26) boot: ESP-IDF v5.2-dev-3775-gb4268c874a 2nd stage bootloader
I (27) boot: compile time Nov  6 2023 21:48:00
I (27) boot: Multicore bootloader
I (31) boot: chip revision: v0.2
I (35) boot.esp32s3: Boot SPI Speed : 80MHz
I (40) boot.esp32s3: SPI Mode       : DIO
I (45) boot.esp32s3: SPI Flash Size : 2MB
I (49) boot: Enabling RNG early entropy source...
I (55) boot: Partition Table:
I (58) boot: ## Label            Usage          Type ST Offset   Length
I (66) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (73) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (81) boot:  2 factory          factory app      00 00 00010000 00100000
I (88) boot: End of partition table
I (92) esp_image: segment 0: paddr=00010020 vaddr=3c020020 size=0cccch ( 52428) map
I (110) esp_image: segment 1: paddr=0001ccf4 vaddr=3fc91800 size=028a8h ( 10408) load
I (113) esp_image: segment 2: paddr=0001f5a4 vaddr=40374000 size=00a74h (  2676) load
I (118) esp_image: segment 3: paddr=00020020 vaddr=42000020 size=18660h ( 99936) map
I (144) esp_image: segment 4: paddr=00038688 vaddr=40374a74 size=0cd58h ( 52568) load
I (162) boot: Loaded app from partition at offset 0x10000
I (162) boot: Disabling RNG early entropy source...
I (173) cpu_start: Multicore app
I (183) cpu_start: Pro cpu start user code
I (183) cpu_start: cpu freq: 160000000 Hz
I (184) cpu_start: Application information:
I (186) cpu_start: Project name:     hello_world
I (192) cpu_start: App version:      1
I (196) cpu_start: Compile time:     Nov  6 2023 21:47:54
I (202) cpu_start: ELF file SHA256:  a6392b013...
I (208) cpu_start: ESP-IDF:          v5.2-dev-3775-gb4268c874a
I (214) cpu_start: Min chip rev:     v0.0
I (219) cpu_start: Max chip rev:     v0.99 
I (224) cpu_start: Chip rev:         v0.2
I (228) heap_init: Initializing. RAM available for dynamic allocation:
I (236) heap_init: At 3FC94978 len 00054D98 (339 KiB): RAM
I (242) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (248) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (254) heap_init: At 600FE010 len 00001FD8 (7 KiB): RTCRAM
I (261) spi_flash: detected chip: generic
I (265) spi_flash: flash io: dio
W (269) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (282) sleep: Configure to isolate all GPIO pins in sleep state
I (289) sleep: Enable automatic switching of GPIO sleep configuration
I (296) main_task: Started on CPU0
I (306) main_task: Calling app_main()
...
```

After startup and diagnostic logs scroll up, you should see “Hello world!” printed out by the application.

```powershell
...
Hello world!
This is esp32s3 chip with 2 CPU core(s), WiFi/BLE, silicon revision v0.2, 2MB external flash
Minimum free heap size: 388440 bytes
Restarting in 10 seconds...
Restarting in 9 seconds...
```



To exit IDF monitor use the shortcut `Ctrl+]`.
