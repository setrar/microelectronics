onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label Cin /testbench/Cin
add wave -noupdate -label x3 /testbench/x3
add wave -noupdate -label x2 /testbench/x2
add wave -noupdate -label x1 /testbench/x1
add wave -noupdate -label x0 /testbench/x0
add wave -noupdate -label y3 /testbench/x3
add wave -noupdate -label y2 /testbench/x2
add wave -noupdate -label y1 /testbench/x1
add wave -noupdate -label y0 /testbench/x0
add wave -noupdate -divider adder4
add wave -noupdate -label s3 /testbench/s3
add wave -noupdate -label s2 /testbench/s2
add wave -noupdate -label s1 /testbench/s1
add wave -noupdate -label s0 /testbench/s0
add wave -noupdate -label Cout /testbench/Cout
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
