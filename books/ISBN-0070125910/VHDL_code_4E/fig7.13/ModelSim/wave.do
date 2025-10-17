onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label Clock /testbench/Clock
add wave -noupdate -label Reset /testbench/Reset
add wave -noupdate -label w /testbench/w
add wave -noupdate -label Data -radix hexadecimal /testbench/Data
add wave -noupdate -label F /testbench/F
add wave -noupdate -label Rx /testbench/Rx
add wave -noupdate -label Ry /testbench/Ry
add wave -noupdate -divider proc
add wave -noupdate -label Done /testbench/U1/Done
add wave -noupdate -label Count /testbench/U1/Count
add wave -noupdate -label BusWires -radix hexadecimal /testbench/U1/BusWires
add wave -noupdate -label R0 -radix hexadecimal /testbench/U1/R0
add wave -noupdate -label R1 -radix hexadecimal /testbench/U1/R1
add wave -noupdate -label R2 -radix hexadecimal /testbench/U1/R2
add wave -noupdate -label R3 -radix hexadecimal /testbench/U1/R3
add wave -noupdate -label A -radix hexadecimal /testbench/U1/A
add wave -noupdate -label G -radix hexadecimal /testbench/U1/G
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {31000 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 82
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
WaveRestoreZoom {20 ns} {420 ns}
