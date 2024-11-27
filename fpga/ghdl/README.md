
### :o: Install GHDL Manually on Mac Mx using `homebrew`

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
