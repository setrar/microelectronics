onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label X -radix hexadecimal /testbench/X
add wave -noupdate -label Y -radix hexadecimal /testbench/Y
add wave -noupdate -divider BCD
add wave -noupdate -label Z /testbench/U1/Z
add wave -noupdate -label Adjust /testbench/U1/Adjust
add wave -noupdate -label S -radix hexadecimal /testbench/S
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
