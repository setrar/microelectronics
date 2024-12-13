`timescale 1ns/1ps

module blink_tb;

    // Testbench signals
    reg clk;                   // Clock signal
    wire led_blue, led_green, led_red; // Outputs from the DUT

    // Instantiate the Design Under Test (DUT)
    rgb_test dut (
        .clk(clk),
        .led_blue(led_blue),
        .led_green(led_green),
        .led_red(led_red)
    );

    // Clock generation
    initial begin
        clk = 0;
        forever #5 clk = ~clk;  // 100 MHz clock (10 ns period)
    end

    // Simulation time control
    initial begin
        $dumpfile("blink_tb.vcd"); // Generates a VCD file for waveform analysis
        $dumpvars(0, blink_tb);    // Dumps all variables in this testbench
        #100000; // Run the simulation for 100,000 time units
        $finish; // End the simulation
    end

endmodule
