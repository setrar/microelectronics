

```sh
# Step 1: Clean old crap (optional but recommended)
brew uninstall yosys ghdl
sudo rm -rf /usr/local/bin/yosys /usr/local/bin/ghdl
sudo rm -rf /usr/local/lib/libghdl* /usr/local/share/yosys

# Step 2: Install prerequisites
brew install gnat llvm bison flex cmake

# Step 3: Add LLVM path
export LIBRARY_PATH=/opt/homebrew/opt/llvm@15/lib/clang/15.0.7/lib/darwin:$LIBRARY_PATH
export CPATH=/opt/homebrew/opt/llvm@15/include:$CPATH

# Step 4: Build GHDL from source
git clone https://github.com/ghdl/ghdl.git
cd ghdl
./configure --prefix=/usr/local --enable-synth --enable-libghdl
make -j$(sysctl -n hw.logicalcpu)
sudo make install

# Step 5: Build Yosys from source
cd ..
git clone https://github.com/YosysHQ/yosys.git
cd yosys
make ENABLE_GHDL=1 -j$(sysctl -n hw.logicalcpu)
sudo make install

# Step 6: Verify
which yosys
yosys -m ghdl
```
