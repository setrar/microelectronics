# simple

This is an attempt to compile the Pico Pi with Rust.


- [ ] Prequisite: Install [Rust](../install)


- [ ] [rp-pico - Board Support for the Raspberry Pi Pico - From Scratch](https://crates.io/crates/rp-pico/#:~:text=From,Scratch)

```
cargo new simple && cd simple
```

- [ ] Add the libraries

```
cargo add rp-pico ; \
cargo add cortex-m-rt ; \
cargo add panic-halt
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
      Adding cortex-m-rt v0.7.3 to dependencies.
             Features:
             - device
             - set-sp
             - set-vtor
    Updating crates.io index
      Adding panic-halt v0.2.0 to dependencies.
    Updating crates.io index
```

- [ ] Downloading the config files

```
mkdir .cargo && curl -o .cargo/config https://raw.githubusercontent.com/rp-rs/rp-hal-boards/main/.cargo/config &&
curl -o memory.x https://raw.githubusercontent.com/rp-rs/rp-hal-boards/main/memory.x
```

- [ ] Add the targeted platform [`thumbv6m-none-eabi`](https://mynewt.apache.org/v1_9_0/tutorials/other/rust.html#:~:text=targets,syscfg)  - use this for Cortex-M0 and Cortex-M0+.

```
rustup target add thumbv6m-none-eabi
```
> Response:
```rust
info: downloading component 'rust-std' for 'thumbv6m-none-eabi'
info: installing component 'rust-std' for 'thumbv6m-none-eabi'
  8.0 MiB /   8.0 MiB (100 %)   5.0 MiB/s in  1s ETA:  0s
```

- [ ] Write the code `src/main.rs`

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


- [ ] run the app

```
cargo run
```
> Response:
```rust
   Compiling quote v1.0.31
   Compiling rustc_version v0.2.3
   Compiling cortex-m v0.7.7
   Compiling nb v1.1.0
   Compiling void v1.0.2
   Compiling nb v0.1.3
   Compiling debug-helper v0.3.13
   Compiling vcell v0.1.3
   Compiling paste v1.0.14
   Compiling cortex-m-rt v0.7.3
   Compiling syn v1.0.109
   Compiling bare-metal v0.2.5
   Compiling crc-any v2.4.3
   Compiling volatile-register v0.2.1
   Compiling embedded-hal v0.2.7
   Compiling rp2040-pac v0.4.0
   Compiling bitfield v0.13.2
   Compiling rp2040-boot2 v0.2.1
   Compiling arrayvec v0.7.4
   Compiling either v1.8.1
   Compiling gcd v2.3.0
   Compiling stable_deref_trait v1.2.0
   Compiling embedded-dma v0.2.0
   Compiling fugit v0.3.7
   Compiling itertools v0.10.5
   Compiling usb-device v0.2.9
   Compiling rp-pico v0.7.0
   Compiling critical-section v1.1.1
   Compiling rand_core v0.6.4
   Compiling panic-halt v0.2.0
   Compiling cortex-m-rt-macros v0.7.0
   Compiling num_enum_derive v0.5.11
   Compiling rp2040-hal-macros v0.1.0
   Compiling num_enum v0.5.11
   Compiling pio v0.2.1
   Compiling rp2040-hal v0.8.2
   Compiling blink v0.1.0 (/home/pi/Developer/microelectronics/lang/blink)
    Finished dev [unoptimized + debuginfo] target(s) in 1m 37s
     Running `elf2uf2-rs -d target/thumbv6m-none-eabi/debug/blink`
Found pico uf2 disk /media/pi/RPI-RP2
Transfering program to pico
1.50 KB / 1.50 KB [========================================================================] 100.00 % 10.70 KB/s 
```


# References

- [ ] [rp-pico - Board Support for the Raspberry Pi Pico](https://crates.io/crates/rp-pico)
- [ ] [.cargo/config.toml in your project](https://doc.rust-lang.org/cargo/reference/config.html#:~:text=level%20of%20discovered%20.-,cargo%2Fconfig.,as%20%2Fmy%2Fproject%2F.)
- [ ] [Error: "Unable to find mounted pico" in Raspberry Pico](https://kresna.dev/raspberry-pico-unable-to-find-mounted-pico/)
