```
--chip auto --port /dev/tty.usbmodem101 --baud 1500000 --before default_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0x000 /Applications/M5Burner.app/Contents/Resources/packages/tmp/uiflow2-mixin.bin
esptool.py v4.7-dev
Serial port /dev/tty.usbmodem101
Connecting...

Detecting chip type... ESP32-S3
Chip is ESP32-S3 (revision v0.2)
Features: WiFi, BLE
Crystal is 40MHz
MAC: 48:27:e2:66:a5:88
Uploading stub...
Running stub...
Stub running...
Changing baud rate to 1500000
Changed.
Configuring flash size...
Auto-detected Flash size: 16MB
Flash will be erased from 0x00000000 to 0x00ffefff...
Compressed 16773120 bytes to 3218797...
Writing at 0x00000000... (0 %)
Writing at 0x000127f8... (1 %)
...
...
Writing at 0x00605a8f... (99 %)
Writing at 0x00de1969... (100 %)
Wrote 16773120 bytes (3218797 compressed) at 0x00000000 in 102.1 seconds (effective 1314.9 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
```
