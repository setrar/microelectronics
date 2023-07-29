/* --- Needed by RPI Pico --- */
#![no_std]
#![no_main]
use bsp::entry;
use bsp::hal::{
    clocks::{init_clocks_and_plls, Clock},
    gpio, pac,
    sio::Sio,
    spi::Spi,
    watchdog::Watchdog,
};
use defmt_rtt as _;
use panic_probe as _;
use rp_pico as bsp;
/* -------------------------- */

// GPIO traits
use embedded_hal::digital::v2::OutputPin;

use embedded_graphics::{
    pixelcolor::Rgb666,
    prelude::*,
    primitives::{Circle, Primitive, PrimitiveStyle, Triangle},
};

// Provides the parallel port and display interface builders
use display_interface_spi::SPIInterfaceNoCS;

// Provides the Display builder
use mipidsi::Builder as mipidsi;

use fugit::RateExtU32;

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
    let mut watchdog = Watchdog::new(pac.WATCHDOG);

    // Configure the clocks
    //
    // The default is to generate a 125 MHz system clock
    let clocks = init_clocks_and_plls(
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
    let sio = Sio::new(pac.SIO);

    // Set the pins up according to their function on this particular board
    let pins = rp_pico::Pins::new(
        pac.IO_BANK0,
        pac.PADS_BANK0,
        sio.gpio_bank0,
        &mut pac.RESETS,
    );

    // Set the LED to be an output
    let mut led_pin = pins.led.into_push_pull_output();
    
    // Define the reset and write enable pins as digital outputs and make them high
    let reset = pins
        .gpio21
        .into_push_pull_output_in_state(gpio::PinState::High);

    // Define the Data/Command select pin as a digital output
    let dc = pins
            .gpio20
            .into_push_pull_output();
    
    // Define the SPI pins and create the SPI interface
    let _miso = pins.gpio16.into_mode::<gpio::FunctionSpi>();
    let _cs   = pins.gpio17.into_push_pull_output();
    let _sck  = pins.gpio18.into_mode::<gpio::FunctionSpi>();
    let _mosi = pins.gpio19.into_mode::<gpio::FunctionSpi>();
 
    let spi = Spi::<_, _, 8>::new(pac.SPI0);
    
    let spi = spi.init(
        &mut pac.RESETS,
        clocks.peripheral_clock.freq(),
        10.MHz(),
        &embedded_hal::spi::MODE_0,
        );
        
    // Define the display interface with no chip select
    let di = SPIInterfaceNoCS::new(spi, dc);
    
    // Define the display from the display interface and initialize it
    let mut display = mipidsi::ili9486_rgb666(di)
        .init(&mut delay, Some(reset))
        .unwrap();

    // Make the display all black
    display.clear(Rgb666::BLACK).unwrap();
    
    // Draw a smiley face with white eyes and a red mouth
    draw_smiley(&mut display).unwrap();
    
    // Blink the LED at 1 Hz
    loop {
        led_pin.set_high().unwrap();
        delay.delay_ms(500);
        led_pin.set_low().unwrap();
        delay.delay_ms(500);
    }
}

fn draw_smiley<T: DrawTarget<Color = Rgb666>>(display: &mut T) -> Result<(), T::Error> {
    // Draw the left eye as a circle located at (50, 100), with a diameter of 40, filled with white
    Circle::new(Point::new(50, 100), 40)
        .into_styled(PrimitiveStyle::with_fill(Rgb666::WHITE))
        .draw(display)?;

    // Draw the right eye as a circle located at (50, 200), with a diameter of 40, filled with white
    Circle::new(Point::new(50, 200), 40)
        .into_styled(PrimitiveStyle::with_fill(Rgb666::WHITE))
        .draw(display)?;

    // Draw an upside down red triangle to represent a smiling mouth
    Triangle::new(
        Point::new(130, 140),
        Point::new(130, 200),
        Point::new(160, 170),
    )
    .into_styled(PrimitiveStyle::with_fill(Rgb666::RED))
    .draw(display)?;

    // Cover the top part of the mouth with a black triangle so it looks closed instead of open
    Triangle::new(
        Point::new(130, 150),
        Point::new(130, 190),
        Point::new(150, 170),
    )
    .into_styled(PrimitiveStyle::with_fill(Rgb666::BLACK))
    .draw(display)?;

    Ok(())
}

// End of file
