# pico-ice-blinky


```
# Build a new directory with a "blinky" example project inside
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

# Set the board to "pico-ice" with `rgb_test` as top module


```
apio init --sayyes --board pico-ice --top-module rgb_test 
```

- [ ] Build the project using yosys/nextpnr

```
apio build
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


# References


- [ ] [programming_the_fpga.md#using-apio](https://github.com/tinyvision-ai-inc/pico-ice/blob/main/Docs/programming_the_fpga.md#using-apio)
