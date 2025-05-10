module blinky (
    input wire clk,      // Input clock
    output reg led       // Output to an LED
);
    reg [23:0] counter = 0;

    always @(posedge clk) begin
        counter <= counter + 1;
        led <= counter[23]; // Blink every ~0.5s with 100MHz clock
    end
endmodule

