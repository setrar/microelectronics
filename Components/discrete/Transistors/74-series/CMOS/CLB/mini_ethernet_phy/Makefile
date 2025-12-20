# ============================
# GHDL Makefile (VHDL-2008)
# ============================

GHDL      := ghdl
STD       := --std=08
TOP       := tb_mini_ethernet_phy
VCD       := wave.vcd

SRC       := mini_ethernet_phy.vhd \
             tb_mini_ethernet_phy.vhd

# Default target
all: run

# Analyze (compile)
analyze:
	$(GHDL) -a $(STD) $(SRC)

# Elaborate
elab: analyze
	$(GHDL) -e $(STD) $(TOP)

# Run simulation
run: elab
	$(GHDL) -r $(TOP) --vcd=$(VCD)

# View waveform (requires GTKWave)
view: $(VCD)
	gtkwave $(VCD)

# Clean build artifacts
clean:
	rm -f *.o *.cf $(TOP) $(VCD)

.PHONY: all analyze elab run view clean

