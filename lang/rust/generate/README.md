# Trying Cargo Generate


```
cargo install cargo-generate
```
> Response:
```rust
    Updating crates.io index
  Downloaded cargo-generate v0.18.3
  Downloaded 1 crate (94.7 KB) in 0.19s
  Installing cargo-generate v0.18.3
  Downloaded btoi v0.4.3
  Downloaded anstyle v1.0.1
...
   Compiling home v0.5.5
   Compiling git2 v0.17.2
   Compiling cargo-generate v0.18.3
    Finished release [optimized] target(s) in 3m 51s
  Installing /Users/myself/.cargo/bin/cargo-generate
   Installed package `cargo-generate v0.18.3` (executable `cargo-generate`)
```

```
cargo generate rp-rs/rp2040-project-template 
```
> Response:
```rust
⚠️   Favorite `rp-rs/rp2040-project-template` not found in config, using it as a git repository: https://github.com/rp-rs/rp2040-project-template.git
🤷   Project Name: blinky-from-template
🔧   Destination: /Users/myself/Developer/microelectronics/lang/rust/generate/blinky-from-template ...
🔧   project-name: blinky-from-template ...
🔧   Generating template ...
🔧   Moving generated files into: `/Users/myself/Developer/microelectronics/lang/rust/generate/blinky-from-template`...
Initializing a fresh Git repository
✨   Done! New project created /Users/myself/Developer/microelectronics/lang/rust/generate/blinky-from-template
```

# References

- [ ] [rp-rs/rp2040-project-template](https://github.com/rp-rs/rp2040-project-template)
- [ ] [cargo-generate](https://crates.io/crates/cargo-generate)
