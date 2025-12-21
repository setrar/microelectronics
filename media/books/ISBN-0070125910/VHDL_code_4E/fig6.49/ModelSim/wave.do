onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label Reset /testbench/Reset
add wave -noupdate -label Clock /testbench/Clock
add wave -noupdate -label A -radix hexadecimal /testbench/A
add wave -noupdate -label B -radix hexadecimal /testbench/B
add wave -noupdate -divider serial
add wave -noupdate -label y /testbench/U1/y
add wave -noupdate -label Run /testbench/U1/Run
add wave -noupdate -label Count -radix hexadecimal /testbench/U1/Count
add wave -noupdate -label Sum -radix hexadecimal /testbench/U1/Sum
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {20000 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 73
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
WaveRestoreZoom {0 ps} {120 ns}
