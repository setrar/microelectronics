# ghdl 

- [ ] Install ghdl

```sh
brew install --cask ghdl
```
>
```powershell
==> Auto-updating Homebrew...
Adjust how often this is run with HOMEBREW_AUTO_UPDATE_SECS or disable with
HOMEBREW_NO_AUTO_UPDATE. Hide these hints with HOMEBREW_NO_ENV_HINTS (see `man brew`).
==> Auto-updated Homebrew!
==> Updated Homebrew from 3d2ab610c9 to 94c91ed052.
No changes to formulae or casks.

==> Downloading https://github.com/ghdl/ghdl/releases/download/v5.0.1/ghdl-llvm-5.0.1-macos15-aarch64.tar.gz
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/087465da8a186192e2cdf28323aff023d313a18dbbda905c7cdad26502662e8e--ghdl-llvm-5.0.1-macos15-aarch64.tar.gz
==> Installing Cask ghdl
==> Linking Binary 'ghdl' to '/opt/homebrew/bin/ghdl'
==> Linking Binary 'ghwdump' to '/opt/homebrew/bin/ghwdump'
==> Linking Binary 'ghdl1-llvm' to '/opt/homebrew/bin/ghdl1-llvm'
==> Linking Binary 'ghdl' to '/opt/homebrew/include/ghdl'
==> Linking Binary 'ghdl' to '/opt/homebrew/lib/ghdl'
🍺  ghdl was successfully installed!
```



```sh
xattr -d com.apple.quarantine `which ghdl`
```



```
ghdl
```
>
```powershell
dyld[28497]: Library not loaded: @rpath/libgcc_s.1.1.dylib
  Referenced from: <DB204FFD-E941-3163-960B-85FA738A7247> /opt/homebrew/Caskroom/ghdl/5.0.1/ghdl-llvm-5.0.1-macos15-aarch64/bin/ghdl
  Reason: tried: '/opt/homebrew/Caskroom/ghdl/5.0.1/ghdl-llvm-5.0.1-macos15-aarch64/bin/libgcc_s.1.1.dylib' (code signature in <064AC5A4-9EF3-37A9-AA5A-5057530C058E> '/opt/homebrew/Caskroom/ghdl/5.0.1/ghdl-llvm-5.0.1-macos15-aarch64/bin/libgcc_s.1.1.dylib' not valid for use in process: library load disallowed by system policy), '/Users/runner/work/ghdl/ghdl/gnat/lib/gcc/aarch64-apple-darwin23.6.0/14.2.0/libgcc_s.1.1.dylib' (no such file), '/System/Volumes/Preboot/Cryptexes/OS/Users/runner/work/ghdl/ghdl/gnat/lib/gcc/aarch64-apple-darwin23.6.0/14.2.0/libgcc_s.1.1.dylib' (no such file), '/Users/runner/work/ghdl/ghdl/gnat/lib/gcc/libgcc_s.1.1.dylib' (no such file), '/System/Volumes/Preboot/Cryptexes/OS/Users/runner/work/ghdl/ghdl/gnat/lib/gcc/libgcc_s.1.1.dylib' (no such file), '/Users/runner/work/ghdl/ghdl/gnat/lib/libgcc_s.1.1.dylib' (no such file), '/System/Volumes/Preboot/Cryptexes/OS/Users/runner/work/ghdl/ghdl/gnat/lib/libgcc_s.1.1.dylib' (no such file), '/opt/homebrew/Caskroom/ghdl/5.0.1/ghdl-llvm-5.0.1-macos15-aarch64/bin/libgcc_s.1.1.dylib' (code signature in <064AC5A4-9EF3-37A9-AA5A-5057530C058E> '/opt/homebrew/Caskroom/ghdl/5.0.1/ghdl-llvm-5.0.1-macos15-aarch64/bin/libgcc_s.1.1.dylib' not valid for use in process: library load disallowed by system policy), '/Users/runner/work/ghdl/ghdl/gnat/lib/gcc/aarch64-apple-darwin23.6.0/14.2.0/libgcc_s.1.1.dylib' (no such file), '/System/Volumes/Preboot/Cryptexes/OS/Users/runner/work/ghdl/ghdl/gnat/lib/gcc/aarch64-apple-darwin23.6.0/14.2.0/libgcc_s.1.1.dylib' (no such file), '/Users/runner/work/ghdl/ghdl/gnat/lib/gcc/libgcc_s.1.1.dylib' (no such file), '/System/Volumes/Preboot/Cryptexes/OS/Users/runner/work/ghdl/ghdl/gnat/lib/gcc/libgcc_s.1.1.dylib' (no such file), '/Users/runner/work/ghdl/ghdl/gnat/lib/libgcc_s.1.1.dylib' (no such file), '/System/Volumes/Preboot/Cryptexes/OS/Users/runner/work/ghdl/ghdl/gnat/lib/libgcc_s.1.1.dylib' (no such file), '/usr/local/lib/libgcc_s.1.1.dylib' (no such file), '/usr/lib/libgcc_s.1.1.dylib' (no such file, not in dyld cache)
```

Ah, now it's warning you about **`libgcc_s.1.1.dylib`**, which is part of the **GCC runtime libraries** — often pulled in when using tools like GHDL (especially if built with GCC backend). This is another classic **Gatekeeper issue**, and again, it doesn’t mean the library is malicious.

### 🔓 **Alternative Fix: Remove Quarantine**

```sh
xattr -d com.apple.quarantine /opt/homebrew/Caskroom/ghdl/5.0.1/ghdl-llvm-5.0.1-macos15-aarch64/bin/libgcc_s.1.1.dylib
```

```
ghdl -h
```
>
```powershell
usage: ghdl COMMAND [OPTIONS] ...
COMMAND is one of:
analyze [OPTS] FILEs
  Analyze one or multiple VHDL files
  aliases: -a, analyse
elaborate [OPTS] UNIT [ARCH]
  Elaborate design UNIT
  alias: -e
run UNIT [ARCH] [RUNOPTS]
  Run design UNIT
  alias: -r
elab-run [OPTS] UNIT [ARCH] [RUNOPTS]
  Elaborate and run design UNIT
  alias: --elab-run
bind [OPTS] UNIT [ARCH]
  Bind design UNIT
  alias: --bind
link [OPTS] UNIT [ARCH]
  Link design UNIT
  alias: --link
list-link [OPTS] UNIT [ARCH]
  List objects file to link UNIT
  alias: --list-link
compile [OPTS] FILEs -e UNIT [ARCH]
  Generate whole sequence to elaborate design UNIT from FILEs
  alias: -c
make [OPTS] UNIT [ARCH]
  Make design UNIT
  alias: -m
gen-makefile [OPTS] UNIT [ARCH]
  Generate a Makefile for design UNIT
  alias: --gen-makefile
gen-depends [OPTS] UNIT [ARCH]
  Generate dependencies of design UNIT
  alias: --gen-depends
disp-config
  Display tools path
  aliases: --disp-config, dispconfig, --dispconfig
bootstrap-std
  (internal) Compile std.standard
  alias: --bootstrap-standard
synth [FILES... -e] UNIT [ARCH]
  Synthesis from UNIT
  alias: --synth
import [OPTS] FILEs
  Import units of FILEs
  alias: -i
syntax [OPTS] FILEs
  Check syntax of FILEs
  alias: -s
dir [LIBs]
  Display contents of the libraries
  alias: --dir
files FILEs
  Display units in FILES
  alias: -f
clean
  Remove generated files
  alias: --clean
remove
  Remove generated files and library file
  alias: --remove
disp-standard
  Disp std.standard in pseudo-vhdl
  alias: --disp-standard
elab-order [--libraries] [OPTS] UNIT [ARCH]
  Display ordered source files
  alias: --elab-order
find-top
  Display possible top entity in work library
  alias: --find-top
chop [OPTS] FILEs
  Chop FILEs
  alias: --chop
lines FILEs
  Precede line with its number
  alias: --lines
reprint [OPTS] FILEs
  Redisplay FILEs
  alias: --reprint
fmt [OPTS] FILEs
  Format FILEs
  alias: --format
compare-tokens [OPTS] REF FILEs
  Compare FILEs with REF
  alias: --compare-tokens
pp-html FILEs
  Pretty-print FILEs in HTML
  alias: --pp-html
xref-html FILEs
  Display FILEs in HTML with xrefs
  alias: --xref-html
xref FILEs
  Generate xrefs
  alias: --xref
--vpi-compile CMD ARGS
  Compile with VPI/VHPI include path
--vpi-link CMD ARGS
  Link with VPI/VHPI library
--vpi-cflags
  Display VPI/VHPI compile flags
--vpi-ldflags
  Display VPI/VHPI link flags
--vpi-include-dir
  Display VPI/VHPI include directory
--vpi-library-dir
  Display VPI/VHPI library directory
--vpi-library-dir-unix
  Display VPI/VHPI library directory (unix form)
file-to-xml FILEs
  Dump AST in XML
  alias: --file-to-xml
--libghdl-name
  Display libghdl name
--libghdl-library-path
  Display libghdl library path
--libghdl-include-dir
  Display libghdl include directory
help [CMD]
  Display this help or [help on CMD]
  aliases: -h, --help
version
  Display ghdl version
  aliases: -v, --version
help-options
  Display help for analyzer options
  alias: --help-options, opts-help, --options-help
help-warnings
  Display help about all the warnings
  alias: --help-warnings

To display the options of a GHDL program,
  run your program with the 'help' option.
Also see 'opts-help' for analyzer options.

Please, refer to the GHDL manual for more information.
Report issues on https://github.com/ghdl/ghdl
```

## Yosys GHDL Plugin

- [ ] Add to libs

```sh
ln -s /opt/homebrew/Caskroom/ghdl/5.0.1/ghdl-llvm-5.0.1-macos15-aarch64/lib/libghdl-5_0_1.dylib /opt/homebrew/lib/libghdl-5_0_1.dylib
```

- [ ] Remove from Quarantine

```
xattr -d com.apple.quarantine /opt/homebrew/lib/libghdl-5_0_1.dylib
xattr -d com.apple.quarantine /opt/homebrew/Caskroom/ghdl/5.0.1/ghdl-llvm-5.0.1-macos15-aarch64/lib/libgnat-14.dylib
xattr -d com.apple.quarantine /opt/homebrew/Caskroom/ghdl/5.0.1/ghdl-llvm-5.0.1-macos15-aarch64/lib/libgcc_s.1.1.dylib
```

- [ ] Test plugin

```sh
export GHDL_YOSYS_PLUGIN=/opt/homebrew/lib/libghdl-5_0_1.dylib    
```

```sh
yosys -m $GHDL_YOSYS_PLUGIN
```
>
```powershell
 /----------------------------------------------------------------------------\
 |  yosys -- Yosys Open SYnthesis Suite                                       |
 |  Copyright (C) 2012 - 2025  Claire Xenia Wolf <claire@yosyshq.com>         |
 |  Distributed under an ISC-like license, type "license" to see terms        |
 \----------------------------------------------------------------------------/
 Yosys 0.52 (git sha1 fee39a3284c90249e1d9684cf6944ffbbcbb8f90, clang++ 16.0.0 -fPIC -O3)

yosys>
```
