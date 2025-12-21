onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label s1 /testbench/s1
add wave -noupdate -label s0 /testbench/s0
add wave -noupdate -divider display
add wave -noupdate -label a /testbench/U1/a
add wave -noupdate -label b /testbench/U1/b
add wave -noupdate -label c /testbench/U1/c
add wave -noupdate -label d /testbench/U1/d
add wave -noupdate -label e /testbench/U1/e
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
