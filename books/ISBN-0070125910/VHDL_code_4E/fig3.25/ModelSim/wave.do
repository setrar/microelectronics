onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label Cin /testbench/Cin
add wave -noupdate -label X -radix hexadecimal /testbench/X
add wave -noupdate -label Y -radix hexadecimal /testbench/Y
add wave -noupdate -divider adder16
add wave -noupdate -label S -radix hexadecimal -childformat {{/testbench/S(15) -radix hexadecimal} {/testbench/S(14) -radix hexadecimal} {/testbench/S(13) -radix hexadecimal} {/testbench/S(12) -radix hexadecimal} {/testbench/S(11) -radix hexadecimal} {/testbench/S(10) -radix hexadecimal} {/testbench/S(9) -radix hexadecimal} {/testbench/S(8) -radix hexadecimal} {/testbench/S(7) -radix hexadecimal} {/testbench/S(6) -radix hexadecimal} {/testbench/S(5) -radix hexadecimal} {/testbench/S(4) -radix hexadecimal} {/testbench/S(3) -radix hexadecimal} {/testbench/S(2) -radix hexadecimal} {/testbench/S(1) -radix hexadecimal} {/testbench/S(0) -radix hexadecimal}} -subitemconfig {/testbench/S(15) {-height 15 -radix hexadecimal} /testbench/S(14) {-height 15 -radix hexadecimal} /testbench/S(13) {-height 15 -radix hexadecimal} /testbench/S(12) {-height 15 -radix hexadecimal} /testbench/S(11) {-height 15 -radix hexadecimal} /testbench/S(10) {-height 15 -radix hexadecimal} /testbench/S(9) {-height 15 -radix hexadecimal} /testbench/S(8) {-height 15 -radix hexadecimal} /testbench/S(7) {-height 15 -radix hexadecimal} /testbench/S(6) {-height 15 -radix hexadecimal} /testbench/S(5) {-height 15 -radix hexadecimal} /testbench/S(4) {-height 15 -radix hexadecimal} /testbench/S(3) {-height 15 -radix hexadecimal} /testbench/S(2) {-height 15 -radix hexadecimal} /testbench/S(1) {-height 15 -radix hexadecimal} /testbench/S(0) {-height 15 -radix hexadecimal}} /testbench/S
add wave -noupdate -label Cout /testbench/Cout
add wave -noupdate -label Overflow /testbench/Overflow
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {20000 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 97
configure wave -valuecolwidth 64
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ps} {113175 ps}
