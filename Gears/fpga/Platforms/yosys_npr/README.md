# Plain 

**0.**  Blinks the device led in 3 different colors.

- [ ] pin file `up5k.pcf`

```pcf
set_io -nowarn led_blue 39
set_io -nowarn led_green 40
set_io -nowarn led_red 41
set_io -nowarn clk 35
```

- [ ] HDL file `blink.v`

```
cat blink.v
```
>
```verilog
module rgb_test (input clk,
                 output led_blue,
                 output led_green,
                 output led_red);


//-- Modify this value for changing the blink frequency
localparam N = 24;  //-- N<=21 Fast, N>=23 Slow

reg [N:0] counter;
always @(posedge clk)
  counter <= counter + 1;

assign led_green = counter[N];
assign led_blue = counter[N-1];
assign led_red = counter[N-2];

endmodule
```


**1.**  Outputs the synthesized netlist into `hardware.json`.
```bash
yosys -p "synth_ice40 -top rgb_test -json hardware.json" -q blink.v
```
- **yosys**: Synthesizes the Verilog file `blink.v`.
- **synth_ice40**: Target a Lattice iCE40 FPGA.
- **-top rgb_test**: Set the top module name to `rgb_test`.
- **-json hardware.json**: Output the synthesized netlist into `hardware.json`.
- **-q**: Quiet mode (less verbose).

---

**2.**  Outputs placement and routing info in ASCII format `hardware.asc`.
```bash
nextpnr-ice40 --up5k --package sg48 --json hardware.json --asc hardware.asc --pcf up5k.pcf -q
```
- **nextpnr-ice40**: Place-and-route tool for iCE40 FPGAs.
- **--up5k**: Target the iCE40 UltraPlus 5K FPGA.
- **--package sg48**: FPGA package type (48-pin SG48).
- **--json hardware.json**: Input netlist from Yosys output.
- **--asc hardware.asc**: Output placement and routing info in ASCII format.
- **--pcf up5k.pcf**: Pin constraint file (defines pin assignments).
- **-q**: Quiet mode.

---

**3.**  Converts the `.asc` text file into a binary bitstream `.bin` file
```bash
icepack hardware.asc hardware.bin
```
- **icepack**: Converts the `.asc` text file into a binary bitstream `.bin` file.
- **hardware.asc -> hardware.bin**: Now you have a bitstream ready to flash onto the FPGA.

---

**4.**  Downloads `hardware.bin` to the device.
```bash
dfu-util -d 1209:b1c0 -a 0 -D hardware.bin --reset
```
- **dfu-util**: Uploads firmware over USB using DFU (Device Firmware Update).
- **-d 1209:b1c0**: USB device ID (specific to your FPGA dev board).
- **-a 0**: Alternate setting 0 (usually the FPGA flash or SRAM).
- **-D hardware.bin**: Download `hardware.bin` to the device.
- **--reset**: Reset the FPGA after programming.

---

⚡ **Summary**:  
You're doing a full FPGA toolchain flow:  
**(Verilog ➔ Synth ➔ Place & Route ➔ Bitstream ➔ Flash to FPGA)**  
**completely with open-source tools**!

