#!/bin/bash

yosys -p "synth_ice40 -top button_input -json button_input.json" button_input.v
nextpnr-ice40 --up5k --package sg48 --json button_input.json --pcf button_input.pcf --asc button_input.asc
icepack button_input.asc hardware.bin
tinyprog -p hardware.bin

