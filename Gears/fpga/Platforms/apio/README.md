# APIO

APIO is an open-source command-line tool designed to simplify the development workflow for FPGA and embedded system projects. It acts as a high-level interface for managing the FPGA toolchain, automating tasks like synthesis, place-and-route, and programming the FPGA without requiring users to manually execute individual tools and commands.

Key Features of APIO

1.	Toolchain Integration:
-	APIO integrates various FPGA development tools, including open-source tools like Yosys (for synthesis), nextpnr (for place-and-route), icepack (for bitstream conversion), and openFPGALoader (for FPGA programming).
-	It provides a unified command structure, allowing developers to interact with these tools more easily.
2.	Simplified Workflow:
-	APIO abstracts the complexities of managing individual tools and commands. Instead of running each step manually, users can perform tasks like synthesis and programming with simple APIO commands.
-	This makes it particularly useful for beginners or those who want a streamlined, consistent workflow for various FPGA platforms.
3.	FPGA and Embedded System Support:
-	Although often associated with Lattice iCE40 FPGAs (e.g., UP5K), APIO also supports other FPGA families and platforms with compatible toolchains.
-	For embedded development, APIO can manage build and programming workflows for microcontrollers.
4.	Cross-Platform Compatibility:
-	APIO is compatible with major operating systems, including Linux, Windows, and macOS.

Common Commands

Some basic APIO commands include:

-	apio init: Initializes a new APIO project.
-	apio build: Runs synthesis and place-and-route for the project.
-	apio upload: Programs the FPGA with the generated bitstream.
-	apio raw: Allows running raw commands for specific tools, such as yosys or nextpnr.

Example Workflow with APIO

Here’s an example workflow for developing an FPGA project with APIO:

1.	Initialize Project: apio init
2.	Build the Project (synthesis + place-and-route): apio build
3.	Upload to FPGA: apio upload

Advantages of Using APIO

-	Ease of Use: APIO reduces the need to understand or manage the intricate commands and options of each tool in the FPGA toolchain.
-	Modularity: Since it supports multiple FPGA toolchains, APIO is versatile and can be used across different devices.
-	Community-Friendly: As an open-source tool, APIO is continually improved by the open hardware community.

In summary, APIO acts as a high-level interface for FPGA and embedded system development, simplifying workflows by integrating key tools and making FPGA programming more accessible.



### :o: [Install](install) APIO

### :a: Examples using the `pico-ice` device

| Examples |
|-|
| [compare4sbits](compare4sbits) |
| [leds](leds) |
| [pico-ice-blinky](pico-ice-blinky) |


# References

- [ ] [APIO Wiki](https://github.com/FPGAwars/apio/wiki)
- [ ] [introduction to FPGA DigiKey](https://www.youtube.com/playlist?list=PLEBQazB0HUyT1WmMONxRZn9NmQ_9CIKhb)

- [ ] [Example project for APIO that has initial support for both VHDL and Verilog toolchains](https://github.com/FPGAwars/apio-examples/tree/master/TinyFPGA-BX/clock_divider)

---

- [ ] GTKWave issue

```
apio sim
```
> Returns
```powershell
iverilog -B "/Users/valiha/.apio/packages/tools-oss-cad-suite/lib/ivl" -o leds_tb.out -D VCD_OUTPUT=leds_tb -D INTERACTIVE_SIM -D NO_ICE40_DEFAULT_ASSIGNMENTS "/Users/valiha/.apio/packages/tools-oss-cad-suite/share/yosys/ice40/cells_sim.v" leds.v leds_tb.v
vvp -M "/Users/valiha/.apio/packages/tools-oss-cad-suite/lib/ivl" leds_tb.out
VCD info: dumpfile leds_tb.vcd opened for output.
End of simulation
leds_tb.v:41: $finish called at 1000000 (1ps)
gtkwave --rcvar "splash_disable on" --rcvar "do_initial_zoom_fit 1" leds_tb.vcd leds_tb.gtkw
Can't locate Switch.pm in @INC (you may need to install the Switch module) (@INC contains: /Library/Perl/5.34/darwin-thread-multi-2level /Library/Perl/5.34 /Network/Library/Perl/5.34/darwin-thread-multi-2level /Network/Library/Perl/5.34 /Library/Perl/Updates/5.34.1 /System/Library/Perl/5.34/darwin-thread-multi-2level /System/Library/Perl/5.34 /System/Library/Perl/Extras/5.34/darwin-thread-multi-2level /System/Library/Perl/Extras/5.34) at /opt/homebrew/bin/gtkwave line 2.
BEGIN failed--compilation aborted at /opt/homebrew/bin/gtkwave line 2.
scons: *** [sim] Error 2
═════════════════════════════════════════════════════════════ [ ERROR ] Took 0.45 seconds ═════════════════════════════════════════════════════════════
```

```
brew uninstall gtkwave
```
> Returns
```powershell
==> Uninstalling Cask gtkwave
==> Backing App 'gtkwave.app' up to '/opt/homebrew/Caskroom/gtkwave/3.3.107/gtkwave.app'
==> Removing App '/Applications/gtkwave.app'
==> Unlinking Binary '/opt/homebrew/bin/gtkwave'
==> Purging files for version 3.3.107 of Cask gtkwave
```

```
brew untap randomplum/gtkwave
```
> Returns
```powershell
Error: No available tap randomplum/gtkwave.
Run brew tap-new randomplum/gtkwave to create a new randomplum/gtkwave tap!
```


```
brew install --HEAD randomplum/gtkwave/gtkwave
```


