module and_gate (
    input wire btn1,
    input wire btn2,
    output wire led
);

assign led = btn1 & btn2;

endmodule
