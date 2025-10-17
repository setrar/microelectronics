onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label Data -radix hexadecimal /testbench/Data
add wave -noupdate -label Resetn /testbench/Resetn
add wave -noupdate -label w /testbench/w
add wave -noupdate -label Clock /testbench/Clock
add wave -noupdate -label RinExt /testbench/RinExt
add wave -noupdate -divider swap
add wave -noupdate -label BusWires -radix hexadecimal /testbench/U1/BusWires
add wave -noupdate -label RRin /testbench/U1/RRin
add wave -noupdate -label Rin /testbench/U1/Rin
add wave -noupdate -label Rout /testbench/U1/Rout
add wave -noupdate -label R1 -radix hexadecimal /testbench/U1/R1
add wave -noupdate -label R2 -radix hexadecimal /testbench/U1/R2
add wave -noupdate -label R3 -radix hexadecimal /testbench/U1/R3
add wave -noupdate -label y /testbench/U1/y
add wave -noupdate -label Done /testbench/U1/Done
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {20000 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 73
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
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ps} {112134 ps}
