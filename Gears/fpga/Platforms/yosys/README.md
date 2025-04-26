

```sh
# Step 1: Clean old crap (optional but recommended)
brew uninstall yosys ghdl
sudo rm -rf /usr/local/bin/yosys /usr/local/bin/ghdl
sudo rm -rf /usr/local/lib/libghdl* /usr/local/share/yosys

# Step 2: Install prerequisites
brew install gnat llvm bison flex cmake

# Step 3: Build GHDL from source
git clone https://github.com/ghdl/ghdl.git
cd ghdl
./configure --prefix=/usr/local --enable-synth --enable-libghdl
make -j$(sysctl -n hw.logicalcpu)
sudo make install

# Step 4: Build Yosys from source
cd ..
git clone https://github.com/YosysHQ/yosys.git
cd yosys
make ENABLE_GHDL=1 -j$(sysctl -n hw.logicalcpu)
sudo make install

# Step 5: Verify
which yosys
yosys -m ghdl
```
