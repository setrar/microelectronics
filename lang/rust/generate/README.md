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


- [ ] [Troubleshooting - "Error: no probe was found."](https://github.com/knurling-rs/probe-run#troubleshooting)

- [ ] [Linux only: USB](https://embedded-trainings.ferrous-systems.com/installation.html?highlight=udev#linux-only-usb) :grey_question::grey_question:

```
sudo apt-get install libudev-dev libusb-1.0-0-dev
```
> Response:
```
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
libudev-dev is already the newest version (247.3-7+deb11u2).
The following NEW packages will be installed:
  libusb-1.0-0-dev libusb-1.0-doc
0 upgraded, 2 newly installed, 0 to remove and 0 not upgraded.
Need to get 272 kB of archives.
After this operation, 1,948 kB of additional disk space will be used.
Get:1 http://deb.debian.org/debian bullseye/main arm64 libusb-1.0-0-dev arm64 2:1.0.24-3 [80.6 kB]
Get:2 http://deb.debian.org/debian bullseye/main arm64 libusb-1.0-doc all 2:1.0.24-3 [192 kB]
Fetched 272 kB in 0s (1,182 kB/s)   
Selecting previously unselected package libusb-1.0-0-dev:arm64.
(Reading database ... 98405 files and directories currently installed.)
Preparing to unpack .../libusb-1.0-0-dev_2%3a1.0.24-3_arm64.deb ...
Unpacking libusb-1.0-0-dev:arm64 (2:1.0.24-3) ...
Selecting previously unselected package libusb-1.0-doc.
Preparing to unpack .../libusb-1.0-doc_2%3a1.0.24-3_all.deb ...
Unpacking libusb-1.0-doc (2:1.0.24-3) ...
Setting up libusb-1.0-doc (2:1.0.24-3) ...
Setting up libusb-1.0-0-dev:arm64 (2:1.0.24-3) ...
```


# References

- [ ] [rp-rs/rp2040-project-template](https://github.com/rp-rs/rp2040-project-template)
- [ ] [cargo-generate](https://crates.io/crates/cargo-generate)
- [ ] [Debugging embedded software with Raspberry Pi Pico](https://www.raspberrypi.com/news/debugging-embedded-software-with-raspberry-pi-pico/)
- [ ] [Debugging Raspberry Pi Pico via SWD](https://visualgdb.com/documentation/embedded/raspberry/pico/swd/)
- [ ] [JTAG/SWD Interface](https://developer.arm.com/documentation/101636/0100/Debug-and-Trace/JTAG-SWD-Interface)
