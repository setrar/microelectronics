
### RTL Synthesis: `Yosys`

```
apio raw 'yosys -h'
```
> Returns
```powershell
Usage: /Users/valiha/.apio/packages/tools-oss-cad-suite/libexec/yosys [options] [<infile> [..]]

    -Q
        suppress printing of banner (copyright, disclaimer, version)

    -T
        suppress printing of footer (log hash, version, timing statistics)

    -q
        quiet operation. only write warnings and error messages to console
        use this option twice to also quiet warning messages

    -v <level>
        print log headers up to level <level> to the console. (this
        implies -q for everything except the 'End of script.' message.)

    -t
        annotate all log messages with a time stamp

    -d
        print more detailed timing stats at exit

    -l logfile
        write log messages to the specified file

    -L logfile
        like -l but open log file in line buffered mode

    -o outfile
        write the design to the specified file on exit

    -b backend
        use this backend for the output file specified on the command line

    -f frontend
        use the specified frontend for the input files on the command line

    -H
        print the command list

    -h command
        print the help message for the specified command

    -s scriptfile
        execute the commands in the script file

    -c tcl_scriptfile
        execute the commands in the tcl script file (see 'help tcl' for details)

    -C
        enters TCL interatcive shell mode

    -p command
        execute the commands (to chain commands, separate them with semicolon + whitespace: 'cmd1; cmd2')

    -m module_file
        load the specified module (aka plugin)

    -X
        enable tracing of core data structure changes. for debugging

    -M
        will slightly randomize allocated pointer addresses. for debugging

    -A
        will call abort() at the end of the script. for debugging

    -r <module_name>
        elaborate command line arguments using the specified top module

    -D <macro>[=<value>]
        set the specified Verilog define (via "read -define")

    -P <header_id>[:<filename>]
        dump the design when printing the specified log header to a file.
        yosys_dump_<header_id>.il is used as filename if none is specified.
        Use 'ALL' as <header_id> to dump at every header.

    -W regex
        print a warning for all log messages matching the regex.

    -w regex
        if a warning message matches the regex, it is printed as regular
        message instead.

    -e regex
        if a warning message matches the regex, it is printed as error
        message instead and the tool terminates with a nonzero return code.

    -E <depsfile>
        write a Makefile dependencies file with in- and output file names

    -x <feature>
        do not print warnings for the specified experimental feature

    -g
        globally enable debug log messages

    -V
        print version information and exit

The option -S is an shortcut for calling the "synth" command, a default
script for transforming the Verilog input to a gate-level netlist. For example:

    yosys -o output.blif -S input.v

For more complex synthesis jobs it is recommended to use the read_* and write_*
commands in a script file instead of specifying input and output files on the
command line.

When no commands, script files or input files are specified on the command
line, yosys automatically enters the interactive command mode. Use the 'help'
command to get information on the individual commands.
```

### Place and Route Tools: `nextpnr`

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



```
apio raw 'icepack -h'
```
> Returns
```powershell
Usage: /Users/valiha/.apio/packages/tools-oss-cad-suite/libexec/icepack [options] [input-file [output-file]]

    -u
        unpack mode (implied when called as 'iceunpack')

    -v
        verbose (repeat to increase verbosity)

    -s
        disable final deep-sleep SPI flash command after bitstream is loaded

    -b
        write cram bitmap as netpbm file

    -f
        write cram bitmap (fill tiles) as netpbm file

    -c
        write cram bitmap (checkerboard) as netpbm file
        repeat to flip the selection of tiles

    -r
        write bram data, not cram, to the netpbm file

    -B0, -B1, -B2, -B3
        only include the specified bank in the netpbm file

    -n
        skip initializing BRAM
```

### Bitstream Conversion: `icepack`

```
apio raw 'icepack -h'
```
> Returns
```powershell
Usage: /Users/valiha/.apio/packages/tools-oss-cad-suite/libexec/icepack [options] [input-file [output-file]]

    -u
        unpack mode (implied when called as 'iceunpack')

    -v
        verbose (repeat to increase verbosity)

    -s
        disable final deep-sleep SPI flash command after bitstream is loaded

    -b
        write cram bitmap as netpbm file

    -f
        write cram bitmap (fill tiles) as netpbm file

    -c
        write cram bitmap (checkerboard) as netpbm file
        repeat to flip the selection of tiles

    -r
        write bram data, not cram, to the netpbm file

    -B0, -B1, -B2, -B3
        only include the specified bank in the netpbm file

    -n
        skip initializing BRAM
```