#!/bin/bash

export ROOT=~/.icestudio/venv/bin/

rm hardware.*
${ROOT}apio raw 'yosys -p "synth_ice40 -top leds -json hardware.json" -q leds.v' &&
${ROOT}apio raw 'nextpnr-ice40 --up5k --package sg48 --json hardware.json --asc hardware.asc --pcf leds.pcf -q' &&
${ROOT}apio raw 'icepack hardware.asc hardware.bin'  &&
dfu-util -d 1209:b1c0 -a 0 -D hardware.bin
