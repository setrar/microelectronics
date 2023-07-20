# Languages

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

- [ ] [rp-pico - Board Support for the Raspberry Pi Pico - From Scratch](https://crates.io/crates/rp-pico/#:~:text=From,Scratch)

```
cargo new blink
```

```
cd blink
```


```
cargo add rp-pico
```
> Response:
```rust
    Updating crates.io index
      Adding rp-pico v0.7.0 to dependencies.
             Features:
             + boot2
             + cortex-m-rt
             + critical-section-impl
             + rom-func-cache
             + rp2040-boot2
             + rt
             - disable-intrinsics
             - rom-v2-intrinsics
             - rp2040-e5
    Updating crates.io index
```

```
cargo add cortex-m-rt
```
> Response:
```rust
    Updating crates.io index
      Adding cortex-m-rt v0.7.3 to dependencies.
             Features:
             - device
             - set-sp
             - set-vtor
```

```
cargo add panic-halt
```
> Response:
```rust
    Updating crates.io index
      Adding panic-halt v0.2.0 to dependencies.
    Updating crates.io index
```


# References

- [ ] [rustup is an installer for the systems programming language Rust](https://rustup.rs/)
- [ ] [rp-pico - Board Support for the Raspberry Pi Pico](https://crates.io/crates/rp-pico)
