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
