# APIO






# References

- [ ] [APIO Wiki](https://github.com/FPGAwars/apio/wiki)
- [ ] [introduction to FPGA DigiKey](https://www.youtube.com/playlist?list=PLEBQazB0HUyT1WmMONxRZn9NmQ_9CIKhb)

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


