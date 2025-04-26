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
GHDL 5.0.1 (4.1.0.r602.g37ad91899) [Dunoon edition]
 Compiled with GNAT Version: 14.2.0
 llvm 19.1.7 code generator
Written by Tristan Gingold.

Copyright (C) 2003 - 2025 Tristan Gingold.
GHDL is free software, covered by the GNU General Public License.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

## Yosys GHDL Plugin

- [ ] Remove from Quarantine

```
xattr -d com.apple.quarantine /opt/homebrew/Caskroom/ghdl/5.0.1/ghdl-llvm-5.0.1-macos15-aarch64/lib/libghdl-5_0_1.dylib
xattr -d com.apple.quarantine /opt/homebrew/Caskroom/ghdl/5.0.1/ghdl-llvm-5.0.1-macos15-aarch64/lib/libgnat-14.dylib
xattr -d com.apple.quarantine /opt/homebrew/Caskroom/ghdl/5.0.1/ghdl-llvm-5.0.1-macos15-aarch64/lib/libgcc_s.1.1.dylib
```

- [ ] Add a more friendly name to libs

```sh
ln -s /opt/homebrew/Caskroom/ghdl/5.0.1/ghdl-llvm-5.0.1-macos15-aarch64/lib/libghdl-5_0_1.dylib /opt/homebrew/lib/libghdl-5_0_1.dylib
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

# References

- [ ] Manually install ghdl

Note: the homebrew oackage comes with gnat and other shared libraries (homebrew has better approach)

```sh
# Step 1: Clean old crap (optional but recommended)
brew uninstall ghdl
sudo rm -rf /usr/local/bin/yosys /usr/local/bin/ghdl

# Step 2: Install prerequisites
brew install gnat llvm bison flex cmake

# Step 3: Build GHDL from source
git clone https://github.com/ghdl/ghdl.git
cd ghdl
./configure --prefix=/usr/local --enable-synth --enable-libghdl --with-llvm-config=/opt/homebrew/opt/llvm@15/bin/llvm-config
make -j$(sysctl -n hw.logicalcpu)
sudo make install
```
