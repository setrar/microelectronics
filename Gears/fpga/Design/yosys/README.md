

```sh
# Step 1: Clean old crap (optional but recommended)
brew uninstall yosys
sudo rm -rf /usr/local/lib/libghdl* /usr/local/share/yosys

# Step 2: Build GHDL from source
git clone https://github.com/ghdl/ghdl.git
cd ghdl
./configure --prefix=/usr/local --enable-synth --enable-libghdl --with-llvm-config=/opt/homebrew/opt/llvm@15/bin/llvm-config
make -j$(sysctl -n hw.logicalcpu)
sudo make install

# Step 3: Build Yosys from source
cd ..
git clone https://github.com/YosysHQ/yosys.git
cd yosys
git submodule update --init --recursive
# explicitly use clang and clang++ instead of gcc/g++ as the C and C++ compilers.
make CC=clang CXX=clang++ -j$(sysctl -n hw.logicalcpu)
sudo make install

# Step 5: Verify
which yosys
yosys -m ghdl
```

