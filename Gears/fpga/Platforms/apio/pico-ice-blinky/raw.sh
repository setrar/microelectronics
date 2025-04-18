#!/bin/bash

rm hardware.*
apio raw 'yosys -p "synth_ice40 -top rgb_test -json hardware.json" -q blink.v' &&
apio raw 'nextpnr-ice40 --up5k --package sg48 --json hardware.json --asc hardware.asc --pcf up5k.pcf -q' &&
apio raw 'icepack hardware.asc hardware.bin'  &&
dfu-util -d 1209:b1c0 -a 0 -D hardware.bin --reset

