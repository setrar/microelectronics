onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label Resetn /testbench/Resetn
add wave -noupdate -label Clock /testbench/Clock
add wave -noupdate -label LA /testbench/LA
add wave -noupdate -label DataA -radix hexadecimal /testbench/DataA
add wave -noupdate -label EB /testbench/EB
add wave -noupdate -label DataB -radix hexadecimal /testbench/DataB
add wave -noupdate -label s /testbench/s
add wave -noupdate -divider multiply
add wave -noupdate -label Done /testbench/U1/Done
add wave -noupdate -label Q -radix hexadecimal /testbench/Q
add wave -noupdate -label R -radix hexadecimal /testbench/U1/R
add wave -noupdate -label R0 /testbench/U1/R0
add wave -noupdate -label y /testbench/U1/y
add wave -noupdate -label Count -radix hexadecimal /testbench/U1/Count
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
