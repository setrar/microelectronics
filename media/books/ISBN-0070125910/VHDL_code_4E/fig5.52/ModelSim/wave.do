onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label Clock /testbench/Clock
add wave -noupdate -label Resetn /testbench/Resetn
add wave -noupdate -label E /testbench/E
add wave -noupdate -label R /testbench/R
add wave -noupdate -divider rege
add wave -noupdate -label Q /testbench/U1/Q
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
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
WaveRestoreZoom {0 ps} {236208 ps}
