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
