onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label c9 /testbench/c9
add wave -noupdate -label Reset /testbench/Reset
add wave -noupdate -label w /testbench/w
add wave -noupdate -label Pushn /testbench/Pushn
add wave -noupdate -divider reaction
add wave -noupdate -label LEDn /testbench/U1/LEDn
add wave -noupdate -label BCD1 -radix hexadecimal /testbench/U1/counter/BCD1
add wave -noupdate -label BCD0 -radix hexadecimal /testbench/U1/counter/BCD0
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 82
configure wave -valuecolwidth 39
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
configure wave -timelineunits ms
update
WaveRestoreZoom {0 ps} {200 ms}
