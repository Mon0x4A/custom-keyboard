# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/tggh/gitRepos/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(vamk C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(vamk vamk.c )

# Add any subdirectories
target_include_directories(vamk PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/display
        ${CMAKE_CURRENT_LIST_DIR}/key-handling
        ${CMAKE_CURRENT_LIST_DIR}/keymaps
        ${CMAKE_CURRENT_LIST_DIR}/macros
        ${CMAKE_CURRENT_LIST_DIR}/mouse_handling
        ${CMAKE_CURRENT_LIST_DIR}/tinyusb-config
        )

target_sources(vamk PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/display/ssd1306_buffer_helper.c
        ${CMAKE_CURRENT_LIST_DIR}/display/ssd1306_i2c_api.c
        ${CMAKE_CURRENT_LIST_DIR}/display/vamk_display_state.c
        ${CMAKE_CURRENT_LIST_DIR}/vamk.c
        ${CMAKE_CURRENT_LIST_DIR}/key-handling/vamk_hold_delay_handler.c
        ${CMAKE_CURRENT_LIST_DIR}/key-handling/vamk_key_helper.c
        ${CMAKE_CURRENT_LIST_DIR}/key-handling/vamk_key_state.c
        ${CMAKE_CURRENT_LIST_DIR}/key-handling/vamk_keyboard_state.c
        ${CMAKE_CURRENT_LIST_DIR}/vamk_layer_info.c
        ${CMAKE_CURRENT_LIST_DIR}/key-handling/vamk_peripheral_switch_state.c
        ${CMAKE_CURRENT_LIST_DIR}/key-handling/vamk_press_handler.c
        ${CMAKE_CURRENT_LIST_DIR}/key-handling/vamk_press_helper.c
        ${CMAKE_CURRENT_LIST_DIR}/key-handling/vamk_release_handler.c
        ${CMAKE_CURRENT_LIST_DIR}/key-handling/vamk_switch_state.c
        ${CMAKE_CURRENT_LIST_DIR}/key-handling/vamk_tap_handler.c
        ${CMAKE_CURRENT_LIST_DIR}/mouse-handling/pmw3360_spi_api.c
        ${CMAKE_CURRENT_LIST_DIR}/tinyusb-config/usb_descriptors.c
        ${CMAKE_CURRENT_LIST_DIR}/tinyusb-config/tusb_implementation.c
        )

pico_set_program_name(vamk "vamk")
pico_set_program_version(vamk "0.1")

pico_enable_stdio_uart(vamk 1)
pico_enable_stdio_usb(vamk 0)

# Add the standard library to the build
target_link_libraries(
        vamk
        pico_stdlib
        )

# Add the standard include files to the build
target_include_directories(vamk PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(
        vamk
        hardware_i2c
        hardware_spi
        hardware_timer
        pico_i2c_slave
        tinyusb_device
        tinyusb_board
        )

pico_add_extra_outputs(vamk)

