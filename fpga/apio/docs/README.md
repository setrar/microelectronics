
```
apio raw 'nextpnr-ice40 -h'
```
> Returns:
```powershell
"nextpnr-ice40" -- Next Generation Place and Route (Version nextpnr-0.7-5-gb05cb862)

General options:
  -h [ --help ]                         show help
  -v [ --verbose ]                      verbose output
  -q [ --quiet ]                        quiet mode, only errors and warnings 
                                        displayed
  --Werror                              Turn warnings into errors
  -l [ --log ] arg                      log file, all log messages are written 
                                        to this file regardless of -q
  --debug                               debug output
  --debug-placer                        debug output from placer only
  --debug-router                        debug output from router only
  --threads arg                         number of threads for passes where this
                                        is configurable
  -f [ --force ]                        keep running after errors
  --gui                                 start gui
  --gui-no-aa                           disable anti aliasing (use together 
                                        with --gui option)
  --run arg                             python file to execute instead of 
                                        default flow
  --pre-pack arg                        python file to run before packing
  --pre-place arg                       python file to run before placement
  --pre-route arg                       python file to run before routing
  --post-route arg                      python file to run after routing
  --on-failure arg                      python file to run in event of crash 
                                        for design introspection
  --json arg                            JSON design file to ingest
  --write arg                           JSON design file to write
  --top arg                             name of top module
  --seed arg                            seed value for random number generator
  -r [ --randomize-seed ]               randomize seed value for random number 
                                        generator
  --placer arg                          placer algorithm to use; available: sa,
                                        heap, static; default: heap
  --router arg                          router algorithm to use; available: 
                                        router1, router2; default: router1
  --slack_redist_iter arg               number of iterations between slack 
                                        redistribution
  --cstrweight arg                      placer weighting for relative 
                                        constraint satisfaction
  --starttemp arg                       placer SA start temperature
  --pack-only                           pack design only without placement or 
                                        routing
  --no-route                            process design without routing
  --no-place                            process design without placement
  --no-pack                             process design without packing
  --ignore-loops                        ignore combinational loops in timing 
                                        analysis
  --ignore-rel-clk                      ignore clock-to-clock relations in 
                                        timing checks
  -V [ --version ]                      show version
  --test                                check architecture database integrity
  --freq arg                            set target frequency for design in MHz
  --timing-allow-fail                   allow timing to fail in design
  --no-tmdriv                           disable timing-driven placement
  --sdf arg                             SDF delay back-annotation file to write
  --sdf-cvc                             enable tweaks for SDF file 
                                        compatibility with the CVC simulator
  --no-print-critical-path-source       disable printing of the line numbers 
                                        associated with each net in the 
                                        critical path
  --placer-heap-alpha arg               placer heap alpha value (float, 
                                        default: 0.1)
  --placer-heap-beta arg                placer heap beta value (float, default:
                                        0.9)
  --placer-heap-critexp arg             placer heap criticality exponent (int, 
                                        default: 2)
  --placer-heap-timingweight arg        placer heap timing weight (int, 
                                        default: 10)
  --placer-heap-cell-placement-timeout arg
                                        allow placer to attempt up to 
                                        max(10000, total cells^2 / N) 
                                        iterations to place a cell (int N, 
                                        default: 8, 0 for no timeout)
  --parallel-refine                     use new experimental parallelised 
                                        engine for placement refinement
  --router2-heatmap arg                 prefix for router2 resource congestion 
                                        heatmaps
  --tmg-ripup                           enable experimental timing-driven ripup
                                        in router
  --router2-tmg-ripup                   enable experimental timing-driven ripup
                                        in router (deprecated; use --tmg-ripup 
                                        instead)
  --router2-alt-weights                 use alternate router2 weights
  --report arg                          write timing and utilization report in 
                                        JSON format to file
  --detailed-timing-report              Append detailed net timing data to the 
                                        JSON report
  --placed-svg arg                      write render of placement to SVG file
  --routed-svg arg                      write render of routing to SVG file

Architecture specific options:
  --lp384                               set device type to iCE40LP384
  --lp1k                                set device type to iCE40LP1K
  --lp4k                                set device type to iCE40LP4K
  --lp8k                                set device type to iCE40LP8K
  --hx1k                                set device type to iCE40HX1K
  --hx4k                                set device type to iCE40HX4K
  --hx8k                                set device type to iCE40HX8K
  --up3k                                set device type to iCE40UP3K
  --up5k                                set device type to iCE40UP5K
  --u1k                                 set device type to iCE5LP1K
  --u2k                                 set device type to iCE5LP2K
  --u4k                                 set device type to iCE5LP4K
  --package arg                         set device package
  --pcf arg                             PCF constraints file to ingest
  --asc arg                             asc bitstream file to write
  --read arg                            asc bitstream file to read
  --promote-logic                       enable promotion of 'logic' globals (in
                                        addition to clk/ce/sr by default)
  --no-promote-globals                  disable all global promotion
  --opt-timing                          run post-placement timing optimisation 
                                        pass (experimental)
  --tmfuzz                              run path delay estimate fuzzer
  --pcf-allow-unconstrained             don't require PCF to constrain all IO
```
