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

```
mkdir .cargo && curl -o .cargo/config https://raw.githubusercontent.com/rp-rs/rp-hal-boards/main/.cargo/config
```

```
curl -o memory.x https://raw.githubusercontent.com/rp-rs/rp-hal-boards/main/memory.x
```

src/main.rs

```rust
#![no_std]
#![no_main]
use rp_pico::entry;
use panic_halt as _;
#[entry]
fn see_doesnt_have_to_be_called_main() -> ! {
  loop {}
}
```

```
cargo run
```
> Response:
```rust
  Downloaded arrayvec v0.7.4
  Downloaded nb v0.1.3
  Downloaded proc-macro2 v1.0.66
  Downloaded unicode-ident v1.0.11
  Downloaded stable_deref_trait v1.2.0
  Downloaded rand_core v0.6.4
  Downloaded quote v1.0.31
  Downloaded void v1.0.2
  Downloaded nb v1.1.0
  Downloaded embedded-hal v0.2.7
  Downloaded debug-helper v0.3.13
  Downloaded paste v1.0.14
  Downloaded rp2040-boot2 v0.2.1
  Downloaded rp-pico v0.7.0
  Downloaded pio v0.2.1
  Downloaded rp2040-hal v0.8.2
  Downloaded num_enum_derive v0.5.11
  Downloaded rp2040-hal-macros v0.1.0
  Downloaded vcell v0.1.3
  Downloaded volatile-register v0.2.1
  Downloaded gcd v2.3.0
  Downloaded rustc_version v0.2.3
  Downloaded bitfield v0.13.2
  Downloaded semver v0.9.0
  Downloaded usb-device v0.2.9
  Downloaded cortex-m-rt-macros v0.7.0
  Downloaded panic-halt v0.2.0
  Downloaded embedded-dma v0.2.0
  Downloaded cortex-m-rt v0.7.3
  Downloaded semver-parser v0.7.0
  Downloaded bare-metal v0.2.5
  Downloaded num_enum v0.5.11
  Downloaded rp2040-pac v0.4.0
  Downloaded critical-section v1.1.1
  Downloaded cortex-m v0.7.7
  Downloaded either v1.8.1
  Downloaded itertools v0.10.5
  Downloaded fugit v0.3.7
  Downloaded syn v1.0.109
  Downloaded crc-any v2.4.3
  Downloaded 40 crates (1.9 MB) in 6.19s
   Compiling proc-macro2 v1.0.66
   Compiling unicode-ident v1.0.11
   Compiling syn v1.0.109
   Compiling semver-parser v0.7.0
   Compiling cortex-m-rt v0.7.3
   Compiling semver v0.9.0
   Compiling cortex-m v0.7.7
   Compiling nb v1.1.0
error[E0463]: can't find crate for `core`
  |
  = note: the `thumbv6m-none-eabi` target may not be installed
  = help: consider downloading the target with `rustup target add thumbv6m-none-eabi`

error[E0463]: can't find crate for `compiler_builtins`

error[E0463]: can't find crate for `core`
   --> /home/pi/.cargo/registry/src/index.crates.io-6f17d22bba15001f/nb-1.1.0/src/lib.rs:192:5
    |
192 | use core::fmt;
    |     ^^^^ can't find crate
    |
    = note: the `thumbv6m-none-eabi` target may not be installed
    = help: consider downloading the target with `rustup target add thumbv6m-none-eabi`

error: cannot find attribute `derive` in this scope
   --> /home/pi/.cargo/registry/src/index.crates.io-6f17d22bba15001f/nb-1.1.0/src/lib.rs:201:3
    |
201 | #[derive(Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
    |   ^^^^^^

error[E0463]: can't find crate for `core`
   --> /home/pi/.cargo/registry/src/index.crates.io-6f17d22bba15001f/nb-1.1.0/src/lib.rs:195:27
    |
195 | pub type Result<T, E> = ::core::result::Result<T, Error<E>>;
    |                           ^^^^ can't find crate
    |
    = note: the `thumbv6m-none-eabi` target may not be installed
    = help: consider downloading the target with `rustup target add thumbv6m-none-eabi`

error[E0405]: cannot find trait `FnOnce` in this scope
   --> /home/pi/.cargo/registry/src/index.crates.io-6f17d22bba15001f/nb-1.1.0/src/lib.rs:239:12
    |
239 |         F: FnOnce(E) -> T,
    |            ^^^^^^ not found in this scope

error[E0405]: cannot find trait `From` in this scope
   --> /home/pi/.cargo/registry/src/index.crates.io-6f17d22bba15001f/nb-1.1.0/src/lib.rs:248:9
    |
248 | impl<E> From<E> for Error<E> {
    |         ^^^^ not found in this scope

Some errors have detailed explanations: E0405, E0463.
For more information about an error, try `rustc --explain E0405`.
error: could not compile `nb` (lib) due to 7 previous errors
warning: build failed, waiting for other jobs to finish...
```

# References

- [ ] [rustup is an installer for the systems programming language Rust](https://rustup.rs/)
- [ ] [rp-pico - Board Support for the Raspberry Pi Pico](https://crates.io/crates/rp-pico)
- [ ] [.cargo/config.toml in your project](https://doc.rust-lang.org/cargo/reference/config.html#:~:text=level%20of%20discovered%20.-,cargo%2Fconfig.,as%20%2Fmy%2Fproject%2F.)
