

```
cargo new blinky && cd blinky
```
>    Created binary (application) `blinky` package

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
```



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

```
rustup target add thumbv6m-none-eabi
```
> Response:
```rust
info: downloading component 'rust-std' for 'thumbv6m-none-eabi'
info: installing component 'rust-std' for 'thumbv6m-none-eabi'
```

- [ ]  run the app

```
cargo run
```
