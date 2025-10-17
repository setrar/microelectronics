onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label x /testbench/x
add wave -noupdate -label y /testbench/y
add wave -noupdate -label z /testbench/z
add wave -noupdate -divider f_g
add wave -noupdate -label f /testbench/U1/f
add wave -noupdate -label g /testbench/U1/g
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
