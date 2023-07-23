# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C   standards
project(TftGuiSimple C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

include_directories(../Lib)

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME} 
    TftGuiSimple.c
    gui.c
    ../Lib/Tft320x240.c
    ../Lib/Veeprom.c
    ../lib/TftTouch.c
)

# Configure VEEPROM to use 4 bytes per word and set valid key
target_compile_definitions(${PROJECT_NAME}  PRIVATE
    VEE_PAYLOAD_SIZE=4 # Can be 4,3,2 or 1 byte per word
    VEE_VALID_BUFFER_MARKER=0x1861
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    hardware_adc
    hardware_flash
)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 0)   # turn off serial out on USB
pico_enable_stdio_uart(${PROJECT_NAME} 0)  # turn off serial out on uart 0
