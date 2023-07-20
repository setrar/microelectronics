# Blinky

- [ ] Create the `Blinky` project

```
cargo new blinky && cd blinky
```
>    Created binary (application) `blinky` package

- [ ] Add the libraries

```
cargo add rp-pico ; \
cargo add cortex-m ; \
cargo add cortex-m-rt ; \
cargo add embedded-hal ; \
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
      Adding cortex-m v0.7.7 to dependencies.
             Features:
             - cm7
             - cm7-r0p1
             - critical-section
             - critical-section-single-core
             - inline-asm
             - linker-plugin-lto
             - serde
             - std
    Updating crates.io index
      Adding cortex-m-rt v0.7.3 to dependencies.
             Features:
             - device
             - set-sp
             - set-vtor
    Updating crates.io index
      Adding embedded-hal v0.2.7 to dependencies.
             Features:
             - unproven
    Updating crates.io index
      Adding panic-halt v0.2.0 to dependencies.
```

- [ ] Download the config files

```
mkdir .cargo && curl -o .cargo/config https://raw.githubusercontent.com/rp-rs/rp-hal-boards/main/.cargo/config ; \
curl -o memory.x https://raw.githubusercontent.com/rp-rs/rp-hal-boards/main/memory.x
```
> Response:
```rust
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100  1528  100  1528    0     0  11175      0 --:--:-- --:--:-- --:--:-- 11664
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100   319  100   319    0     0   2769      0 --:--:-- --:--:-- --:--:--  2900
```

- [ ] Assign the targetted platform

```
rustup target add thumbv6m-none-eabi
```
> Response:
```rust
info: downloading component 'rust-std' for 'thumbv6m-none-eabi'
info: installing component 'rust-std' for 'thumbv6m-none-eabi'
```

- [ ] Write the Code `src/main.rs`

```rust
//! # Pico Blinky Example
//!
//! Blinks the LED on a Pico board.
//!
//! This will blink an LED attached to GP25, which is the pin the Pico uses for
//! the on-board LED.
//!
//! See the `Cargo.toml` file for Copyright and license details.

#![no_std]
#![no_main]

// The macro for our start-up function
use rp_pico::entry;

// GPIO traits
use embedded_hal::digital::v2::OutputPin;

// Ensure we halt the program on panic (if we don't mention this crate it won't
// be linked)
use panic_halt as _;

// Pull in any important traits
use rp_pico::hal::prelude::*;

// A shorter alias for the Peripheral Access Crate, which provides low-level
// register access
use rp_pico::hal::pac;

// A shorter alias for the Hardware Abstraction Layer, which provides
// higher-level drivers.
use rp_pico::hal;

/// Entry point to our bare-metal application.
///
/// The `#[entry]` macro ensures the Cortex-M start-up code calls this function
/// as soon as all global variables are initialised.
///
/// The function configures the RP2040 peripherals, then blinks the LED in an
/// infinite loop.
#[entry]
fn main() -> ! {
    // Grab our singleton objects
    let mut pac = pac::Peripherals::take().unwrap();
    let core = pac::CorePeripherals::take().unwrap();

    // Set up the watchdog driver - needed by the clock setup code
    let mut watchdog = hal::Watchdog::new(pac.WATCHDOG);

    // Configure the clocks
    //
    // The default is to generate a 125 MHz system clock
    let clocks = hal::clocks::init_clocks_and_plls(
        rp_pico::XOSC_CRYSTAL_FREQ,
        pac.XOSC,
        pac.CLOCKS,
        pac.PLL_SYS,
        pac.PLL_USB,
        &mut pac.RESETS,
        &mut watchdog,
    )
    .ok()
    .unwrap();

    // The delay object lets us wait for specified amounts of time (in
    // milliseconds)
    let mut delay = cortex_m::delay::Delay::new(core.SYST, clocks.system_clock.freq().to_Hz());

    // The single-cycle I/O block controls our GPIO pins
    let sio = hal::Sio::new(pac.SIO);

    // Set the pins up according to their function on this particular board
    let pins = rp_pico::Pins::new(
        pac.IO_BANK0,
        pac.PADS_BANK0,
        sio.gpio_bank0,
        &mut pac.RESETS,
    );

    // Set the LED to be an output
    let mut led_pin = pins.led.into_push_pull_output();

    // Blink the LED at 1 Hz
    loop {
        led_pin.set_high().unwrap();
        delay.delay_ms(500);
        led_pin.set_low().unwrap();
        delay.delay_ms(500);
    }
}

// End of file
```


- [ ]  run the app (make sure the BOOTLOADER folder is available)

```
cargo run
```

# References

- [ ] [pico_blinky.rs](https://github.com/rp-rs/rp-hal-boards/blob/main/boards/rp-pico/examples/pico_blinky.rs)
