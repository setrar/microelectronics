# 

```
mkdir compare4sbits && cd compare4sbits
```

- [ ] Init

```
apio init --board pico-ice --project-dir .
```

generates 

```yaml
[env]
board = pico-ice
top-module = main
```

- [ ] The following is a possible design for a comparator. It is stored in a file named `compare4sbits.v`

```verilog
// 4 Bit comparator for signed numbers
//
module comparator_4bit(i_a, i_b, o_less, o_equal, o_greater);
    input [3:0] i_a, i_b;
    output o_less;
    output o_equal;
    output o_greater;
    wire [3:0] w_diff;
    wire w_bits_set;
    assign w_diff = i_a - i_b;
    assign w_bits_set = w_diff[3] | w_diff[2] | w_diff[1] | w_diff[0];
    assign o_greater = (w_diff[3]) ? 1'b0 : (1'b1 & w_bits_set);
    assign o_less = (w_diff[3]) ? 1'b1 : 1'b0;
    assign o_equal = ~w_bits_set;
endmodule
```

- [ ] To test it we create a test bench in a file named `compare4sbits_tb.v` with

```verilog
// Test bench for the 4bit signed comparator
//
module comparator_4bit_tb();
    reg r_clk;
    reg [3:0] r_ta;
    reg [3:0] r_tb;
    wire w_gt;
    wire w_eq;
    wire w_lt;

    // Unit Under Test
    comparator_4bit uut(
        .i_a (r_ta),
        .i_b (r_tb),
        .o_less (w_lt),
        .o_equal (w_eq),
        .o_greater (w_gt)
    );

    initial begin
        // Specify the name where to dump the trace data
        $dumpfile("compare4sbits_tb.vcd");
        // Specify what variables to trace, 0 == all of them,
        // and from which module
        $dumpvars(0, comparator_4bit_tb);
        // Add a clock signal, not really needed but nice as
        // a reference.
        r_clk = 1'b0;
        forever #5 r_clk = ~r_clk; // generate a clock
    end

    // Fill r_ta and r_tb with different values
    // to see how the comparator behaves.
    initial begin
        // r_ta and r_tb are still undefined at this
        // point.
        #5 // Wait 5ps before executing the next step
        r_ta = 4'b0111; //  7
        r_tb = 4'b0000; //  0
        #10 // Wait 10ps
        r_ta = 4'b0000; //  0
        r_tb = 4'b0111; //  7
        #10
        r_ta = 4'b0000; //  0
        r_tb = 4'b1111; // -1
        #20
        r_ta = 4'b1111; // -1
        r_tb = 4'b1111; // -1
        #30
        r_ta = 4'b0001; //  1
        r_tb = 4'b1111; // -1
        #40
        r_ta = 4'b0000; //  0
        r_tb = 4'b0000; //  0
        #5
        $finish;
    end

endmodule
```

- [ ] To simulate 

```
apio sim
```

- [ ] Viewing

<img src=images/gtkwave_compare4sbits.png width='' height='' > <img>


# References

- [ ] [FPGA Development hello world](https://timesink.nl/2023-12-26-apio.html)
