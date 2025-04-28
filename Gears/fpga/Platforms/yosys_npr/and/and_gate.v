module and_gate (
    input wire btn1,
    input wire btn2,
    output led_red
);

assign led_red = ~(btn1 & btn2);

endmodule
