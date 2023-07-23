#![no_std]
#![no_main]

/* --- Needed by RPI Pico --- */
use bsp::entry;
use bsp::hal::{
    clocks::{init_clocks_and_plls, Clock},
    gpio, pac,
    sio::Sio,
    spi::{Spi, SpiMode},
    watchdog::Watchdog,
};
use defmt_rtt as _;
use panic_probe as _;
use rp_pico as bsp;
/* -------------------------- */

use embedded_graphics::{
    pixelcolor::Rgb565,
    prelude::*,
    primitives::{Circle, Primitive, PrimitiveStyle, Rectangle, Triangle},
};

// Provides the parallel port and display interface builders
use display_interface_spi::SPIInterfaceNoCS;

// Provides the Display builder
use mipidsi::Builder;

use fugit::RateExtU32;

#[entry]
fn main() -> ! {
    let peripherals = Peripherals::take();
    let mut system = peripherals.SYSTEM.split();
    let clocks = ClockControl::boot_defaults(system.clock_control).freeze();
    let io = IO::new(peripherals.GPIO, peripherals.IO_MUX);

    // Disable the RTC and TIMG watchdog timers
    let mut rtc = Rtc::new(peripherals.RTC_CNTL);
    let timer_group0 = TimerGroup::new(
        peripherals.TIMG0,
        &clocks,
        &mut system.peripheral_clock_control,
    );
    let mut wdt0 = timer_group0.wdt;
    let timer_group1 = TimerGroup::new(
        peripherals.TIMG1,
        &clocks,
        &mut system.peripheral_clock_control,
    );
    let mut wdt1 = timer_group1.wdt;
    rtc.swd.disable();
    rtc.rwdt.disable();
    wdt0.disable();
    wdt1.disable();

    // Define the delay struct, needed for the display driver
    let mut delay = Delay::new(&clocks);

    // Define the Data/Command select pin as a digital output
    let dc = io.pins.gpio7.into_push_pull_output();
    // Define the reset pin as digital outputs and make it high
    let mut rst = io.pins.gpio8.into_push_pull_output();
    rst.set_high().unwrap();

    // Define the SPI pins and create the SPI interface
    let sck = io.pins.gpio12;
    let miso = io.pins.gpio11;
    let mosi = io.pins.gpio13;
    let cs = io.pins.gpio10;
    let spi = Spi::new(
        peripherals.SPI2,
        sck,
        mosi,
        miso,
        cs,
        100_u32.kHz(),
        SpiMode::Mode0,
        &mut system.peripheral_clock_control,
        &clocks,
    );

    // Define the display interface with no chip select
    let di = SPIInterfaceNoCS::new(spi, dc);

    // Define the display from the display interface and initialize it
    let mut display = Builder::ili9486_rgb565(di)
        .init(&mut delay, Some(rst))
        .unwrap();

    // Make the display all black
    display.clear(Rgb565::BLACK).unwrap();

    loop {
        // Do nothing
    }
}
