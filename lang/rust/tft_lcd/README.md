

```rust
cargo install hal
```

```
cargo add embedded-graphics ; cargo add display-interface-spi ; cargo add mipidsi ; cargo add fugit
```
> Response:
```rust
    Updating crates.io index
      Adding embedded-graphics v0.8.0 to dependencies.
             Features:
             - defmt
             - fixed
             - fixed_point
             - nalgebra_support
    Updating crates.io index
    Updating crates.io index
      Adding display-interface-spi v0.4.1 to dependencies.
    Updating crates.io index
    Updating crates.io index
      Adding mipidsi v0.7.1 to dependencies.
             Features:
             + batch
             + heapless
    Updating crates.io index
    Updating crates.io index
      Adding fugit v0.3.7 to dependencies.
             Features:
             - defmt
```


```
hal = { package = "esp32c3-hal", version = "0.10.0" }
esp-backtrace = { version = "0.7.0", features = ["esp32c3", "panic-handler", "exception-handler", "print-uart"] }
esp-println       = { version = "0.5.0", features = ["esp32c3"] }
embedded-graphics = "0.8.0"
display-interface-spi = "0.4.1"
mipidsi = "0.7.1"
fugit = "0.3.7"
```

```rust
error[E0433]: failed to resolve: use of undeclared crate or module `hal`
 --> src/main.rs:6:5
  |
6 | use hal::{
  |     ^^^ use of undeclared crate or module `hal`

error[E0432]: unresolved imports `esp_backtrace`, `hal::clock::ClockControl`, `hal::peripherals::Peripherals`, `hal::prelude::*`, `hal::spi::Spi`, `hal::spi::SpiMode`, `hal::timer::TimerGroup`
  --> src/main.rs:5:5
   |
5  | use esp_backtrace as _;
   |     ^^^^^^^^^^^^^^^^^^ no external crate `esp_backtrace`
6  | use hal::{
7  |     clock::ClockControl,
   |     ^^^^^^^^^^^^^^^^^^^
8  |     peripherals::Peripherals,
   |     ^^^^^^^^^^^^^^^^^^^^^^^^
9  |     prelude::*,
   |     ^^^^^^^^^^
10 |     spi::{Spi, SpiMode},
   |           ^^^  ^^^^^^^
11 |     timer::TimerGroup,
   |     ^^^^^^^^^^^^^^^^^

error[E0433]: failed to resolve: use of undeclared crate or module `embedded_graphics`
  --> src/main.rs:16:5
   |
16 | use embedded_graphics::{
   |     ^^^^^^^^^^^^^^^^^ use of undeclared crate or module `embedded_graphics`

error[E0432]: unresolved imports `hal`, `embedded_graphics::pixelcolor::Rgb565`, `embedded_graphics::prelude::*`, `embedded_graphics::primitives::Circle`, `embedded_graphics::primitives::Primitive`, `embedded_graphics::primitives::PrimitiveStyle`, `embedded_graphics::primitives::Rectangle`, `embedded_graphics::primitives::Triangle`
  --> src/main.rs:6:5
   |
6  | use hal::{
   |     ^^^ help: a similar path exists: `rp_pico::hal`
...
17 |     pixelcolor::Rgb565,
   |     ^^^^^^^^^^^^^^^^^^
18 |     prelude::*,
   |     ^^^^^^^^^^
19 |     primitives::{Circle, Primitive, PrimitiveStyle, Rectangle, Triangle},
   |                  ^^^^^^  ^^^^^^^^^  ^^^^^^^^^^^^^^  ^^^^^^^^^  ^^^^^^^^

error[E0432]: unresolved import `display_interface_spi`
  --> src/main.rs:23:5
   |
23 | use display_interface_spi::SPIInterfaceNoCS;
   |     ^^^^^^^^^^^^^^^^^^^^^ use of undeclared crate or module `display_interface_spi`

error[E0432]: unresolved import `mipidsi`
  --> src/main.rs:26:5
   |
26 | use mipidsi::Builder;
   |     ^^^^^^^ use of undeclared crate or module `mipidsi`

error[E0432]: unresolved import `fugit`
  --> src/main.rs:28:5
   |
28 | use fugit::RateExtU32;
   |     ^^^^^ use of undeclared crate or module `fugit`

error: cannot find attribute `entry` in this scope
  --> src/main.rs:30:3
   |
30 | #[entry]
   |   ^^^^^
   |
   = help: consider importing one of these items:
           cortex_m_rt::entry
           rp_pico::entry

error[E0405]: cannot find trait `DrawTarget` in this scope
   --> src/main.rs:101:19
    |
101 | fn draw_smiley<T: DrawTarget<Color = Rgb565>>(display: &mut T) -> Resul...
    |                   ^^^^^^^^^^ not found in this scope

error[E0433]: failed to resolve: use of undeclared type `Point`
   --> src/main.rs:103:17
    |
103 |     Circle::new(Point::new(50, 100), 40)
    |                 ^^^^^ use of undeclared type `Point`

error[E0433]: failed to resolve: use of undeclared type `Point`
   --> src/main.rs:108:17
    |
108 |     Circle::new(Point::new(50, 200), 40)
    |                 ^^^^^ use of undeclared type `Point`

error[E0433]: failed to resolve: use of undeclared type `Point`
   --> src/main.rs:114:9
    |
114 |         Point::new(130, 140),
    |         ^^^^^ use of undeclared type `Point`

error[E0433]: failed to resolve: use of undeclared type `Point`
   --> src/main.rs:115:9
    |
115 |         Point::new(130, 200),
    |         ^^^^^ use of undeclared type `Point`

error[E0433]: failed to resolve: use of undeclared type `Point`
   --> src/main.rs:116:9
    |
116 |         Point::new(160, 170),
    |         ^^^^^ use of undeclared type `Point`

error[E0433]: failed to resolve: use of undeclared type `Point`
   --> src/main.rs:123:9
    |
123 |         Point::new(130, 150),
    |         ^^^^^ use of undeclared type `Point`

error[E0433]: failed to resolve: use of undeclared type `Point`
   --> src/main.rs:124:9
    |
124 |         Point::new(130, 190),
    |         ^^^^^ use of undeclared type `Point`

error[E0433]: failed to resolve: use of undeclared type `Point`
   --> src/main.rs:125:9
    |
125 |         Point::new(150, 170),
    |         ^^^^^ use of undeclared type `Point`

Some errors have detailed explanations: E0405, E0432, E0433.
For more information about an error, try `rustc --explain E0405`.
error: could not compile `tft_lcd` (bin "tft_lcd") due to 17 previous errors

```
