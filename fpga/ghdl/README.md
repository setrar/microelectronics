

### [GCC 14.2.0-3 (aarch64)](https://github.com/simonjwright/distributing-gcc/releases)

For notes on installation, paths etc see the [Wiki](https://github.com/simonjwright/distributing-gcc/wiki).

- [ ] Download the latest release

- [ ] run

```
cd ~/Downloads
```

```
xattr -d com.apple.quarantine gcc-14.2.0-3-aarch64-apple-darwin23.pkg
```

| | |
|-|-|
| <img src=images/gcc-installer.png width='' height='' > </img> | <img src=images/gcc-installer.png width='' height='' > </img> | 

### :o: Install GHDL Manually on Mac M[?] using `homebrew`

- [ ] [GHDL not properly compiling on MacOS 14.6 with command ghdl -a --ieee=synopsy command](https://github.com/ghdl/ghdl/issues/2711)

```
brew tap --force homebrew/cask
```
> Returns
```powershell
==> Auto-updating Homebrew...
Adjust how often this is run with HOMEBREW_AUTO_UPDATE_SECS or disable with
HOMEBREW_NO_AUTO_UPDATE. Hide these hints with HOMEBREW_NO_ENV_HINTS (see `man brew`).
==> Tapping homebrew/cask
Cloning into '/opt/homebrew/Library/Taps/homebrew/homebrew-cask'...
remote: Enumerating objects: 1123917, done.
remote: Counting objects: 100% (2910/2910), done.
remote: Compressing objects: 100% (1062/1062), done.
remote: Total 1123917 (delta 2093), reused 2635 (delta 1847), pack-reused 1121007 (from 1)
Receiving objects: 100% (1123917/1123917), 407.84 MiB | 1.50 MiB/s, done.
Resolving deltas: 100% (829897/829897), done.
Tapped 2 commands and 7188 casks (7,260 files, 444.4MB).
```

```ruby
cask "ghdl" do
  version "4.2.0"

  arch arm: "ARM64"
  sha256 "3cd01ca86bcd6bb9ec0bdb086af1468c3c4f7a170fd003a879ffcbd567036c6b"
  url "https://github.com/ghdl/ghdl/releases/download/nightly/ghdl-macos14-#{arch}-llvm.tgz"
  name "ghdl"
  desc "VHDL 2019/2008/93/87 simulator"
  homepage "https://github.com/ghdl/ghdl/"

  livecheck do
    url :url
    strategy :github_latest
  end

  depends_on formula: "llvm@18"
  ghdlbins = ["ghdl", "ghwdump", "ghdl1-llvm"]

  ghdlbins.each { |_bin|
    binary "bin/#{_bin}"
  }

  postflight do
    puts "Creating symlink to libgcc_s.1.1.dylib"
    File.symlink("#{HOMEBREW_PREFIX}/lib/gcc/current/libgcc_s.1.1.dylib", "#{staged_path}/bin/libgcc_s.1.1.dylib")
    puts "Creating library symlinks in #{HOMEBREW_PREFIX}/include and #{HOMEBREW_PREFIX}/lib"
    File.symlink("#{staged_path}/include/ghdl", "#{HOMEBREW_PREFIX}/include/ghdl")
    File.symlink("#{staged_path}/lib/ghdl", "#{HOMEBREW_PREFIX}/lib/ghdl")
    puts "⚠️  Relinking ghdl1-llvm to LLVM@18"
    `install_name_tool -change \
      #{HOMEBREW_PREFIX}/opt/llvm/lib/libLLVM.dylib \
      #{HOMEBREW_PREFIX}/opt/llvm@18/lib/libLLVM.dylib \
      #{HOMEBREW_PREFIX}/Caskroom/ghdl/4.2.0/bin/ghdl1-llvm`
    puts "Setting files as being from a nice developer"
    ghdlbins.each { |_bin|
      `xattr -dr com.apple.quarantine #{HOMEBREW_PREFIX}/bin/#{_bin}`
    }
  end

  uninstall_postflight do
    puts "Removing symlink to libgcc_s.1.1.dylib"
    File.unlink("#{staged_path}/bin/libgcc_s.1.1.dylib")
    puts "Removing library symlinks in #{HOMEBREW_PREFIX}/include and #{HOMEBREW_PREFIX}/lib"
    File.unlink("#{HOMEBREW_PREFIX}/include/ghdl", "#{HOMEBREW_PREFIX}/lib/ghdl")
  end

  # No zap stanza required
end
```

```
export HOMEBREW_EDITOR=vi
```

```
brew edit --cask ghdl
```
> Returns
```powershell
Editing /opt/homebrew/Library/Taps/homebrew/homebrew-cask/Casks/g/ghdl.rb
```

```
brew install ghdl
```
> Returns
```
==> Auto-updating Homebrew...
Adjust how often this is run with HOMEBREW_AUTO_UPDATE_SECS or disable with
HOMEBREW_NO_AUTO_UPDATE. Hide these hints with HOMEBREW_NO_ENV_HINTS (see `man brew`).
==> Tapping homebrew/core
Cloning into '/opt/homebrew/Library/Taps/homebrew/homebrew-core'...
remote: Enumerating objects: 2339275, done.
remote: Counting objects: 100% (4464/4464), done.
remote: Compressing objects: 100% (1592/1592), done.
remote: Total 2339275 (delta 3168), reused 4059 (delta 2872), pack-reused 2334811 (from 1)
Receiving objects: 100% (2339275/2339275), 838.89 MiB | 1.79 MiB/s, done.
Resolving deltas: 100% (1702265/1702265), done.
Updating files: 100% (7543/7543), done.
Tapped 4 commands and 7217 formulae (7,554 files, 921MB).
==> Downloading https://github.com/ghdl/ghdl/releases/download/nightly/ghdl-macos14-ARM64-llvm.tgz
==> Downloading from https://objects.githubusercontent.com/github-production-release-asset-2e65be/46439446/32515a05-9e
############################################################################################################### 100.0%
==> Installing dependencies: llvm@18
==> Downloading https://ghcr.io/v2/homebrew/core/llvm/18/manifests/18.1.8
############################################################################################################### 100.0%
==> Fetching llvm@18
==> Downloading https://ghcr.io/v2/homebrew/core/llvm/18/blobs/sha256:c7bb3e7186411468c2b7af59fb5abd5108805078280f8144
############################################################################################################### 100.0%
==> Installing llvm@18
==> Pouring llvm@18--18.1.8.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/llvm@18/18.1.8: 7,140 files, 1.7GB
==> Installing Cask ghdl
==> Linking Binary 'ghdl' to '/opt/homebrew/bin/ghdl'
==> Linking Binary 'ghwdump' to '/opt/homebrew/bin/ghwdump'
==> Linking Binary 'ghdl1-llvm' to '/opt/homebrew/bin/ghdl1-llvm'
Creating symlink to libgcc_s.1.1.dylib
Creating library symlinks in /opt/homebrew/include and /opt/homebrew/lib
⚠️  Relinking ghdl1-llvm to LLVM@18
Setting files as being from a nice developer
🍺  ghdl was successfully installed!
```

- [ ] Testing

```vhdl
--  Hello world program
use std.textio.all; -- Imports the standard textio package.

--  Defines a design entity, without any ports.
entity hello_world is
end hello_world;

architecture behaviour of hello_world is
begin
  process
    variable l : line;
  begin
    write (l, String'("Hello world!"));
    writeline (output, l);
    wait;
  end process;
end behaviour;
```

```
ghdl analyse  hello.vhd
```

```
ghdl elaborate  hello_world
```

```
ghdl run  hello_world
```
> Hello world!