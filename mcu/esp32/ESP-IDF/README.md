# ESP-IDF 

* `ESP`ressif `I`oT `D`evelopment `F`ramework

- [ ] [Standard Toolchain Setup for Linux and macOS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html)

```
brew install cmake ninja dfu-util
```
> Returns
```powershell
Running `brew update --auto-update`...
==> Auto-updated Homebrew!
Updated 2 taps (homebrew/core and homebrew/cask).
==> New Formulae
apkleaks                   bao                        libsail                    python-mako
authz0                     libjuice                   python-docopt              scikit-image

You have 11 outdated formulae and 5 outdated casks installed.

Warning: Treating cmake as a formula. For the cask, use homebrew/cask/cmake
==> Downloading https://ghcr.io/v2/homebrew/core/cmake/manifests/3.27.7
################################################################################################### 100.0%
==> Fetching cmake
==> Downloading https://ghcr.io/v2/homebrew/core/cmake/blobs/sha256:e829c02f42d2e537e53afd0dddc71b8c6c273e
################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/ninja/manifests/1.11.1-1
################################################################################################### 100.0%
==> Fetching ninja
==> Downloading https://ghcr.io/v2/homebrew/core/ninja/blobs/sha256:f973424d56f32c88d2de08e26d2ab37c9966ab
################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/dfu-util/manifests/0.11
################################################################################################### 100.0%
==> Fetching dependencies for dfu-util: libusb
==> Downloading https://ghcr.io/v2/homebrew/core/libusb/manifests/1.0.26
################################################################################################### 100.0%
==> Fetching libusb
==> Downloading https://ghcr.io/v2/homebrew/core/libusb/blobs/sha256:ea8a4a04b5cc81eff38d0c5cdfe2fbac519ca
################################################################################################### 100.0%
==> Fetching dfu-util
==> Downloading https://ghcr.io/v2/homebrew/core/dfu-util/blobs/sha256:03e81fc129ada62759e3cd8d892131ca326
################################################################################################### 100.0%
==> Pouring cmake--3.27.7.arm64_ventura.bottle.tar.gz
==> Caveats
To install the CMake documentation, run:
  brew install cmake-docs

Emacs Lisp files have been installed to:
  /opt/homebrew/share/emacs/site-lisp/cmake
==> Summary
🍺  /opt/homebrew/Cellar/cmake/3.27.7: 3,285 files, 55.3MB
==> Running `brew cleanup cmake`...
Disable this behaviour by setting HOMEBREW_NO_INSTALL_CLEANUP.
Hide these hints with HOMEBREW_NO_ENV_HINTS (see `man brew`).
==> Pouring ninja--1.11.1.arm64_ventura.bottle.1.tar.gz
==> Caveats
zsh completions have been installed to:
  /opt/homebrew/share/zsh/site-functions

Emacs Lisp files have been installed to:
  /opt/homebrew/share/emacs/site-lisp/ninja
==> Summary
🍺  /opt/homebrew/Cellar/ninja/1.11.1: 10 files, 431KB
==> Running `brew cleanup ninja`...
==> Installing dependencies for dfu-util: libusb
==> Installing dfu-util dependency: libusb
==> Downloading https://ghcr.io/v2/homebrew/core/libusb/manifests/1.0.26
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/ce7ffd7c94deb7060c2cac56f1d68a97b9d4bdc039f9548c3df327bee3d20ae4--libusb-1.0.26.bottle_manifest.json
==> Pouring libusb--1.0.26.arm64_ventura.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libusb/1.0.26: 22 files, 595.0KB
==> Installing dfu-util
==> Pouring dfu-util--0.11.arm64_ventura.bottle.tar.gz
🍺  /opt/homebrew/Cellar/dfu-util/0.11: 13 files, 285.9KB
==> Running `brew cleanup dfu-util`...
==> Caveats
==> cmake
To install the CMake documentation, run:
  brew install cmake-docs

Emacs Lisp files have been installed to:
  /opt/homebrew/share/emacs/site-lisp/cmake
==> ninja
zsh completions have been installed to:
  /opt/homebrew/share/zsh/site-functions

Emacs Lisp files have been installed to:
  /opt/homebrew/share/emacs/site-lisp/ninja
```

- [ ] ccache

```
brew install ccache
```
> Returns
```powershell
==> Downloading https://ghcr.io/v2/homebrew/core/ccache/manifests/4.8.3
################################################################################################### 100.0%
==> Fetching dependencies for ccache: hiredis
==> Downloading https://ghcr.io/v2/homebrew/core/hiredis/manifests/1.2.0-1
################################################################################################### 100.0%
==> Fetching hiredis
==> Downloading https://ghcr.io/v2/homebrew/core/hiredis/blobs/sha256:9970a5ff45d25be488b5f3e843fb777624b4
################################################################################################### 100.0%
==> Fetching ccache
==> Downloading https://ghcr.io/v2/homebrew/core/ccache/blobs/sha256:371bd659fedf0bceefc9ef96c603dbd97b869
################################################################################################### 100.0%
==> Installing dependencies for ccache: hiredis
==> Installing ccache dependency: hiredis
==> Downloading https://ghcr.io/v2/homebrew/core/hiredis/manifests/1.2.0-1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/127a05c6ea8bbe081851bc3c059b6aa5fce19f2b7e9e467d50b914487eda7a4e--hiredis-1.2.0-1.bottle_manifest.json
==> Pouring hiredis--1.2.0.arm64_ventura.bottle.1.tar.gz
🍺  /opt/homebrew/Cellar/hiredis/1.2.0: 52 files, 490.2KB
==> Installing ccache
==> Pouring ccache--4.8.3.arm64_ventura.bottle.tar.gz
==> Caveats
To install symlinks for compilers that will automatically use
ccache, prepend this directory to your PATH:
  /opt/homebrew/opt/ccache/libexec

If this is an upgrade and you have previously added the symlinks to
your PATH, you may need to modify it to the path specified above so
it points to the current version.

NOTE: ccache can prevent some software from compiling.
ALSO NOTE: The brew command, by design, will never use ccache.
==> Summary
🍺  /opt/homebrew/Cellar/ccache/4.8.3: 78 files, 1.3MB
==> Running `brew cleanup ccache`...
Disable this behaviour by setting HOMEBREW_NO_INSTALL_CLEANUP.
Hide these hints with HOMEBREW_NO_ENV_HINTS (see `man brew`).
==> Caveats
==> ccache
To install symlinks for compilers that will automatically use
ccache, prepend this directory to your PATH:
  /opt/homebrew/opt/ccache/libexec

If this is an upgrade and you have previously added the symlinks to
your PATH, you may need to modify it to the path specified above so
it points to the current version.

NOTE: ccache can prevent some software from compiling.
ALSO NOTE: The brew command, by design, will never use ccache.
```

- [ ] [Step :two:. Get esp-idf](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html#step-2-get-esp-idf)

```
mkdir -p ~/Developer/esp
cd ~/Developer/esp
git clone --recursive https://github.com/espressif/esp-idf.git
```

- [ ] [Step :three:. Set up the Tools](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/linux-macos-setup.html#step-3-set-up-the-tools)

```
cd ~/Developer/esp/esp-idf
./install.sh esp32s3
```
> Returns
```powershell
Detecting the Python interpreter
Checking "python3" ...
Python 3.11.6
"python3" has been detected
Checking Python compatibility
Installing ESP-IDF tools
Updating /Users/valiha/.espressif/idf-env.json
Selected targets are: esp32s3
Current system platform: macos-arm64
Installing tools: xtensa-esp-elf-gdb, xtensa-esp-elf, riscv32-esp-elf, esp32ulp-elf, openocd-esp32, esp-rom-elfs
Installing xtensa-esp-elf-gdb@12.1_20221002
...
Installing riscv32-esp-elf@esp-13.2.0_20230928
...
```

# References

- [ ] [:octocat: ESP-IDF](https://github.com/espressif/esp-idf)
