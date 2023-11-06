- [ ] [Start a Project](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html#start-a-project)

```
get_idf
```

```
cd ~/Developer/esp
cp -r $IDF_PATH/examples/get-started/hello_world .
```


- [ ] [Configure your project](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html#configure-your-project)

```
cd ~/Developer/esp/hello_world
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
