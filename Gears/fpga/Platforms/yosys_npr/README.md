# Plain without apio

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

rm hardware.*

yosys -p "synth_ice40 -top rgb_test -json hardware.json" -q blink.v

nextpnr-ice40 --up5k --package sg48 --json hardware.json --asc hardware.asc --pcf up5k.pcf -q

icepack hardware.asc hardware.bin


dfu-util -d 1209:b1c0 -a 0 -D hardware.bin --reset
