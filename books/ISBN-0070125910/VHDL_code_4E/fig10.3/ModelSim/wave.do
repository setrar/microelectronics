onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label Clock /testbench/Clock
add wave -noupdate -label Reset /testbench/Reset
add wave -noupdate -label A -radix hexadecimal /testbench/A
add wave -noupdate -label B -radix hexadecimal /testbench/B
add wave -noupdate -label Sel /testbench/Sel
add wave -noupdate -label AddSub /testbench/AddSub
add wave -noupdate -divider addersubtractor
add wave -noupdate -label Z -radix hexadecimal /testbench/U1/Z
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
WaveRestoreZoom {0 ps} {200 ns}
