# Install `rust` on a Raspberry Pi Pico

This is an attempt to compile the Pico Pi with Rust.

- [ ] Install Rustup

```
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```
> Response:
```rust
info: downloading installer

Welcome to Rust!

This will download and install the official compiler for the Rust
programming language, and its package manager, Cargo.

Rustup metadata and toolchains will be installed into the Rustup
home directory, located at:

 /home/pi/.cargo

This can be modified with the CARGO_HOME environment variable.

The cargo, rustc, rustup and other commands will be added to
Cargo's bin directory, located at:

  /home/pi/.cargo/bin

This path will then be added to your PATH environment variable by
modifying the profile files located at:

  /home/pi/.profile
  /home/pi/.bashrc

You can uninstall at any time with rustup self uninstall and
these changes will be reverted.

Current installation options:


   default host triple: aarch64-unknown-linux-gnu
     default toolchain: stable (default)
               profile: default
  modify PATH variable: yes

1) Proceed with installation (default)
2) Customize installation
3) Cancel installation
```

- [ ] 1) Proceed with installation (default)

```
> 1
```
> Response :
```rust

info: profile set to 'default'
info: default host triple is aarch64-unknown-linux-gnu
info: syncing channel updates for 'stable-aarch64-unknown-linux-gnu'
info: latest update on 2023-07-13, rust version 1.71.0 (8ede3aae2 2023-07-12)
info: downloading component 'cargo'
info: downloading component 'clippy'
info: downloading component 'rust-docs'
 13.6 MiB /  13.6 MiB (100 %)  11.3 MiB/s in  1s ETA:  0s
info: downloading component 'rust-std'
 30.9 MiB /  30.9 MiB (100 %)  11.2 MiB/s in  4s ETA:  0s
info: downloading component 'rustc'
 74.8 MiB /  74.8 MiB (100 %)  11.1 MiB/s in 14s ETA:  0s
info: downloading component 'rustfmt'
info: installing component 'cargo'
  6.7 MiB /   6.7 MiB (100 %)   5.7 MiB/s in  1s ETA:  0s
info: installing component 'clippy'
info: installing component 'rust-docs'
 13.6 MiB /  13.6 MiB (100 %)   1.0 MiB/s in 20s ETA:  0s
info: installing component 'rust-std'
 30.9 MiB /  30.9 MiB (100 %)   4.0 MiB/s in  9s ETA:  0s
  6 IO-ops /   6 IO-ops (100 %)   0 IOPS in 14s ETA: Unknown
info: installing component 'rustc'
 74.8 MiB /  74.8 MiB (100 %)   5.4 MiB/s in 27s ETA:  0s
  9 IO-ops /   9 IO-ops (100 %)   0 IOPS in 19s ETA: Unknown
info: installing component 'rustfmt'
info: default toolchain set to 'stable-aarch64-unknown-linux-gnu'

  stable-aarch64-unknown-linux-gnu installed - rustc 1.71.0 (8ede3aae2 2023-07-12)


Rust is installed now. Great!

To get started you may need to restart your current shell.
This would reload your PATH environment variable to include
Cargo's bin directory ($HOME/.cargo/bin).

To configure your current shell, run:
source "$HOME/.cargo/env"
```

- [ ] Prerequisites

* compiling `elf2uf2-rs` Pico flasher

```
sudo apt-get install libudev-dev
```
> Response:
```bash
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
The following package was automatically installed and is no longer required:
  libfuse2
Use 'sudo apt autoremove' to remove it.
The following NEW packages will be installed:
  libudev-dev
0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded.
Need to get 123 kB of archives.
After this operation, 213 kB of additional disk space will be used.
Get:1 http://deb.debian.org/debian bullseye/main arm64 libudev-dev arm64 247.3-7+deb11u2 [123 kB]
Fetched 123 kB in 0s (912 kB/s) 
Selecting previously unselected package libudev-dev:arm64.
(Reading database ... 96913 files and directories currently installed.)
Preparing to unpack .../libudev-dev_247.3-7+deb11u2_arm64.deb ...
Unpacking libudev-dev:arm64 (247.3-7+deb11u2) ...
Setting up libudev-dev:arm64 (247.3-7+deb11u2) ...
Processing triggers for man-db (2.9.4-2) ...
```

```
sudo apt autoremove
```
> Response:
```bash
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
The following packages will be REMOVED:
  libfuse2
0 upgraded, 0 newly installed, 1 to remove and 0 not upgraded.
After this operation, 354 kB disk space will be freed.
Do you want to continue? [Y/n] Y
(Reading database ... 96988 files and directories currently installed.)
Removing libfuse2:arm64 (2.9.9-5) ...
Processing triggers for libc-bin (2.31-13+rpt2+rpi1+deb11u5) ...
```

```
cargo install elf2uf2-rs
```
> Response
```rust
    Updating crates.io index
  Installing elf2uf2-rs v1.3.8
    Updating crates.io index
   Compiling autocfg v1.1.0
   Compiling libc v0.2.147
   Compiling proc-macro2 v1.0.66
   Compiling cfg-if v1.0.0
   Compiling unicode-ident v1.0.11
   Compiling crossbeam-utils v0.8.16
   Compiling version_check v0.9.4
   Compiling memoffset v0.9.0
   Compiling syn v1.0.109
   Compiling quote v1.0.31
   Compiling crossbeam-epoch v0.9.15
   Compiling scopeguard v1.2.0
   Compiling proc-macro-error-attr v1.0.4
   Compiling pkg-config v0.3.27
   Compiling libudev-sys v0.1.4
   Compiling crossbeam-channel v0.5.8
   Compiling proc-macro-error v1.0.4
   Compiling rayon-core v1.11.0
   Compiling num_cpus v1.16.0
   Compiling crossbeam-deque v0.8.3
   Compiling indexmap v1.9.3
   Compiling bitflags v1.3.2
   Compiling hashbrown v0.12.3
   Compiling either v1.8.1
   Compiling once_cell v1.18.0
   Compiling os_str_bytes v6.5.1
   Compiling heck v0.4.1
   Compiling static_assertions v1.1.0
   Compiling nix v0.26.2
   Compiling clap_lex v0.2.4
   Compiling rayon v1.7.0
   Compiling libudev v0.3.0
   Compiling zerocopy-derive v0.3.2
   Compiling clap_derive v3.2.25
   Compiling atty v0.2.14
   Compiling bitflags v2.0.2
   Compiling strsim v0.10.0
   Compiling textwrap v0.16.0
   Compiling termcolor v1.2.0
   Compiling byteorder v1.4.3
   Compiling zerocopy v0.6.1
   Compiling sysinfo v0.28.4
   Compiling clap v3.2.25
   Compiling serialport v4.2.1
   Compiling pbr v1.1.1
   Compiling assert_into v1.1.0
   Compiling elf2uf2-rs v1.3.8
    Finished release [optimized] target(s) in 2m 17s
  Installing /home/pi/.cargo/bin/elf2uf2-rs
   Installed package `elf2uf2-rs v1.3.8` (executable `elf2uf2-rs`)
```

# References

- [ ] [rustup is an installer for the systems programming language Rust](https://rustup.rs/)
- [ ] [rp-pico - Board Support for the Raspberry Pi Pico](https://crates.io/crates/rp-pico)
- [ ] [libudev development package not found](https://stackoverflow.com/questions/55945023/libudev-development-package-not-found)
- [ ] [Error: "Unable to find mounted pico" in Raspberry Pico](https://kresna.dev/raspberry-pico-unable-to-find-mounted-pico/)

- [ ] [.cargo/config.toml in your project](https://doc.rust-lang.org/cargo/reference/config.html#:~:text=level%20of%20discovered%20.-,cargo%2Fconfig.,as%20%2Fmy%2Fproject%2F.)
