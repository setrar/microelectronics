# pico-ice-blinky


- [ ]  Build a new directory with a "blinky" example project inside

```
mkdir pico-ice-blinky; cd pico-ice-blinky
```

```
apio examples -f iCE40-UP5K/blink
```

This will generate a verilog source file:


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

- [ ] Set the board to "pico-ice" with `rgb_test` as top module


```
apio init --sayyes --board pico-ice --top-module rgb_test 
```
> Returns
```powershell
Creating apio.ini file ...
File 'apio.ini' has been successfully created!
```



- [ ] Build the project using yosys/nextpnr

```
apio build
```
> Returns
```powershell
[Tue Apr 16 22:00:17 2024] Processing pico-ice
───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
yosys -p "synth_ice40 -top rgb_test -json hardware.json" -q blink.v
nextpnr-ice40 --up5k --package sg48 --json hardware.json --asc hardware.asc --pcf up5k.pcf -q
icepack hardware.asc hardware.bin
═════════════════════════════════════════════════════════════ [SUCCESS] Took 1.08 seconds ═════════════════════════════════════════════════════════════
```


- [ ] Plug your pico-ice board and upload the blinky project to it

*** Synthesize *** Fail


```
apio upload
```
> Returns
```powershell
[Tue Apr 16 21:49:47 2024] Processing pico-ice
───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
dfu-util -d 1209:b1c0 -a 0 -D --reset hardware.bin
Error: Unexpected argument: hardware.bin
...
```

- Manually run (put the `--reset` parameter at the end)

```
dfu-util -d 1209:b1c0 -a 0 -D hardware.bin --reset
```

as of

```
apio --version
```
> apio, version 0.9.3

```
dfu-util --version
```
> dfu-util 0.11

<img src=images/picoice-apio-upload.png width='' height='' > </img>

---

### using [`apio raw`](https://apiodoc.readthedocs.io/en/stable/source/user_guide/util_commands/cmd_raw.html)

```
bash raw.sh
```

```bash
#!/bin/bash

rm hardware.*
apio raw 'yosys -p "synth_ice40 -top rgb_test -json hardware.json" -q blink.v' &&
apio raw 'nextpnr-ice40 --up5k --package sg48 --json hardware.json --asc hardware.asc --pcf up5k.pcf -q' &&
apio raw 'icepack hardware.asc hardware.bin'  &&
dfu-util -d 1209:b1c0 -a 0 -D hardware.bin --reset
```

This Bash script is for building and deploying a hardware design for an FPGA, specifically targeting an iCE40 UP5K FPGA device. Here's a breakdown of what each line does:

1. **`rm hardware.*`**:
   - This command deletes any existing files with the name `hardware.*` (e.g., `hardware.json`, `hardware.asc`, `hardware.bin`) to ensure a clean start.

2. **`apio raw 'yosys -p "synth_ice40 -top rgb_test -json hardware.json" -q blink.v'`**:
   - Runs the `yosys` synthesis tool using `apio`, which synthesizes the `blink.v` Verilog design.
   - The `-p` option passes a command to `yosys`, specifying that it should synthesize the design for an iCE40 FPGA, using `rgb_test` as the top module, and output the result in `hardware.json`.
   - The `-q` option ensures that `yosys` runs quietly, suppressing most log output.

3. **`apio raw 'nextpnr-ice40 --up5k --package sg48 --json hardware.json --asc hardware.asc --pcf up5k.pcf -q'`**:
   - Runs the `nextpnr-ice40` place-and-route tool using `apio`.
   - `--up5k` specifies the target FPGA is an iCE40 UP5K.
   - `--package sg48` indicates the specific package type of the FPGA (48-pin SG package).
   - `--json hardware.json` is the input JSON netlist from the previous synthesis step.
   - `--asc hardware.asc` specifies the output ASCII file for the FPGA bitstream.
   - `--pcf up5k.pcf` points to the pin constraint file, which maps logical pins to physical pins on the FPGA.
   - The `-q` option runs `nextpnr-ice40` in quiet mode.

4. **`apio raw 'icepack hardware.asc hardware.bin'`**:
   - Runs the `icepack` tool using `apio` to convert the `hardware.asc` ASCII bitstream file into a binary bitstream file (`hardware.bin`) that can be programmed onto the FPGA.

5. **`dfu-util -d 1209:b1c0 -a 0 -D hardware.bin --reset`**:
   - Uses `dfu-util` to upload the `hardware.bin` binary to the FPGA.
   - `-d 1209:b1c0` specifies the USB device ID of the target FPGA.
   - `-a 0` selects the first DFU (Device Firmware Upgrade) interface.
   - `-D hardware.bin` indicates the file to be downloaded.
   - `--reset` resets the FPGA after programming, initiating the programmed bitstream.

### Summary
This script synthesizes a Verilog design (`blink.v`), places and routes it for an iCE40 UP5K FPGA, creates a bitstream file, and uploads it to the FPGA using `dfu-util`. The script ensures that the design is cleaned, synthesized, placed, routed, and flashed onto the FPGA in an automated process.


# References


- [ ] [programming_the_fpga.md#using-apio](https://github.com/tinyvision-ai-inc/pico-ice/blob/main/Docs/programming_the_fpga.md#using-apio)
- [ ] [pico_ice.pcf file](https://github.com/tinyvision-ai-inc/pico-ice-sdk/blob/main/rtl/pico_ice.pcf)
- [ ] [pinout diagram](https://pico-ice.tinyvision.ai/md_pinout.html)
- [ ] [Convertir du VHDL en Verilog librement avec Yosys et GHDL](https://www.fabienm.eu/flf/convertir-du-vhdl-en-verilog-librement-avec-yosys-et-ghdl/)
- [ ] [dfu-util - Device Firmware Upgrade Utilities](https://dfu-util.sourceforge.net/)
