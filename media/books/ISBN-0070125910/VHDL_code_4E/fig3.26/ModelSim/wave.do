onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label X -radix decimal /testbench/X
add wave -noupdate -label Y -radix decimal /testbench/Y
add wave -noupdate -divider adder16
add wave -noupdate -label S -radix decimal /testbench/S
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
