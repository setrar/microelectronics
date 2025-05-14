module button_input (
    input wire button,
    output wire led
);
    // Light the LED when button is pressed (logic low)
    assign led = ~button;
endmodule

