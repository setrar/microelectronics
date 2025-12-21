onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label Resetn /testbench/Resetn
add wave -noupdate -label Clock /testbench/Clock
add wave -noupdate -label s /testbench/s
add wave -noupdate -label LA /testbench/LA
add wave -noupdate -label DataA -radix hexadecimal /testbench/DataA
add wave -noupdate -label LB /testbench/LB
add wave -noupdate -label DataB -radix hexadecimal /testbench/DataB
add wave -noupdate -divider multiply
add wave -noupdate -label Done /testbench/U1/Done
add wave -noupdate -label P -radix hexadecimal /testbench/P
add wave -noupdate -label A -radix hexadecimal /testbench/U1/A
add wave -noupdate -label B -radix hexadecimal /testbench/U1/B
add wave -noupdate -label y /testbench/U1/y
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {11000 ps} 0}
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
WaveRestoreZoom {0 ps} {280 ns}
