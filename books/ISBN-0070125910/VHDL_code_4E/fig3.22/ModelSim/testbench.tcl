# stop any simulation that is currently running
quit -sim

# create the default "work" library
vlib work;

# compile the VHDL source code in the parent folder
vcom ../fulladd.vhd
vcom ../fulladd_package.vhd
vcom ../adder4.vhd
# compile the VHDL code of the testbench
vcom testbench.vht
# start the Simulator, including some libraries that may be needed
vsim work.testbench -Lf 220model -Lf altera_mf
# show waveforms specified in wave.do
do wave.do
# advance the simulation the desired amount of time
run 160 ns
