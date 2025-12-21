onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label Resetn /testbench/Resetn
add wave -noupdate -label N /testbench/N
add wave -noupdate -label D /testbench/D
add wave -noupdate -label Q /testbench/Q
add wave -noupdate -label Coin /testbench/Coin
add wave -noupdate -divider vend
add wave -noupdate -label Z /testbench/U1/Z
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 81
configure wave -valuecolwidth 40
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
WaveRestoreZoom {0 ps} {124550 ps}
