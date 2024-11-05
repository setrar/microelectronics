# [OSS CAD Suite](https://github.com/YosysHQ/oss-cad-suite-build)

The OSS CAD Suite is a comprehensive collection of open-source tools designed for digital logic design and verification. It encompasses a range of utilities for tasks such as RTL synthesis, formal hardware verification, place and route, FPGA programming, and testing. The suite supports various hardware description languages, including Verilog, Migen, and Amaranth. (GitHub)

Key Components of the OSS CAD Suite:

-	RTL Synthesis:
-	Yosys: A versatile RTL synthesis tool with extensive Verilog 2005 support.
-	Amaranth: A refreshed Python toolbox for building complex digital hardware.
-	Migen: A Python-based tool for creating complex digital hardware designs.
-	ABC: A system for sequential synthesis and verification.
-	GHDL: A VHDL simulator supporting VHDL 2008/93/87 standards (available on Linux-x64, Darwin-x64, and Darwin-arm64 platforms).
-	Formal Verification Tools:
-	sby (SymbiYosys): A front-end driver for Yosys-based formal hardware verification flows.
-	mcy: Mutation coverage with Yosys.
-	eqy: Equivalence checking with Yosys.
-	sby-gui: A graphical user interface for sby.
-	Various SMT Solvers: Including Boolector, Yices 2, Z3, and Bitwuzla.
-	Place and Route Tools:
-	nextpnr: A portable FPGA place and route tool supporting architectures like iCE40, ECP5, MachXO2, Nexus, and Gowin.
-	Project IceStorm: Tools for working with Lattice ICE40 bitstreams.
-	Project Trellis: Tools for Lattice ECP5 bitstreams.
-	Project Oxide: Tools for Lattice Nexus bitstreams.
-	Project Apicula: Tools for Gowin bitstreams.
-	FPGA Programming Tools:
-	openFPGALoader: A universal utility for programming FPGAs.
-	dfu-util: Device Firmware Upgrade utilities.
-	ecpprog: A driver for FTDI-based JTAG probes to program ECP5 FPGAs.
-	openocd: Open On-Chip Debugger.
-	Simulation and Testing:
-	GTKWave: A fully featured GTK+ based wave viewer.
-	Verilator: A Verilog/SystemVerilog simulator.
-	Icarus Verilog (iverilog): A Verilog compilation system.
-	cocotb: A coroutine-based cosimulation library for writing VHDL and Verilog testbenches in Python.

The OSS CAD Suite is part of YosysHQ’s Tabby CAD Suite, which offers additional features such as industry-grade SystemVerilog and VHDL support, formal verification with SystemVerilog Assertions (SVA), and formal applications. For more details on the Tabby CAD Suite, refer to the Tabby CAD Datasheet.

To install the OSS CAD Suite, download the appropriate archive for your operating system from the releases page. After extraction, set up the environment as described in the installation instructions. The suite supports multiple platforms, including Linux (x64, ARM64), macOS (x64, ARM64), and Windows (x64). (GitHub)

---

## APIO

APIO and the OSS CAD Suite are related in that both are used for developing and programming FPGAs, but they serve slightly different purposes and have different scopes:

APIO:

	-	APIO is a command-line tool designed to simplify the development workflow for FPGA and embedded development projects. It acts as an interface or frontend that automates and integrates various FPGA tools, making it easier to run synthesis, place-and-route, and bitstream generation commands without dealing with the complexity of each tool individually.
	-	APIO is particularly focused on being user-friendly and accessible to beginners or developers who want a streamlined workflow for their projects.
	-	It can integrate with tools from the OSS CAD Suite (e.g., Yosys, nextpnr, icepack, etc.) to run synthesis and place-and-route processes.

OSS CAD Suite:

	-	OSS CAD Suite is a comprehensive collection of open-source tools for digital design and verification, including Yosys (for synthesis), nextpnr (for place-and-route), icepack (for bitstream packaging), and others.
	-	This suite is designed for developers looking for an end-to-end set of tools to design, verify, and program FPGAs. It supports multiple FPGA families (e.g., Lattice iCE40, ECP5, etc.).
	-	While APIO can call individual tools from the OSS CAD Suite to run specific tasks, the suite itself is a complete toolchain providing more granular control and capabilities for FPGA design and testing.

Relationship:

	-	Integration: APIO can use the OSS CAD Suite as part of its backend tools for handling synthesis, place-and-route, and bitstream generation. When you run commands in APIO, such as those in your Bash script (e.g., using apio raw to call yosys and nextpnr), APIO is acting as a higher-level interface to orchestrate the operations performed by the individual OSS CAD Suite tools.
	-	Ease of Use: APIO simplifies the interaction with the OSS CAD Suite by providing a unified, easy-to-use command structure that abstracts the more complex commands of the suite’s tools.

In essence, APIO acts as a convenient frontend for using tools in the OSS CAD Suite to help streamline the FPGA development workflow.


### :apple: MacOS

#### Installation

Download an archive matching your OS from the releases page.

```
cd ~/bin
```

```
wget https://github.com/YosysHQ/oss-cad-suite-build/releases/download/2024-03-30/oss-cad-suite-darwin-arm64-20240330.tgz -o ~/bin/oss-cad-suite-darwin-arm64-20240330.tgz
```

Extract the archive to a location of your choice (for Windows it is recommended that path does not contain spaces)


On macOS to allow execution of quarantined files 
```
xattr -d com.apple.quarantine oss-cad-suite-darwin-x64-yyymmdd.tgz
```
 on downloaded file, or run: `./activate` in extracted location once.

```
tar zxvf ~/bin/oss-cad-suite-darwin-arm64-20240330.tgz
```

Set the environment as described below.
Linux and macOS

extracted_location=~/bin/oss-cad-suite

```
export PATH="$extracted_location/oss-cad-suite/bin:$PATH"
```

# or

source $extracted_location/oss-cad-suite/environment

# References

- [ ] [Yosys+nextpnr: an Open Source Framework from Verilog to Bitstream for Commercial FPGAs](https://arxiv.org/pdf/1903.10407)
