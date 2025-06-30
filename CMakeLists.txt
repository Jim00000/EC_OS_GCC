cmake_minimum_required (VERSION 3.20)

# Fixed parameters
set(TOOL_DIR ${CMAKE_SOURCE_DIR}/util)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/RTKToolChain.cmake)
set(RAW_BINFILE_NAME ec_firmware.bin)

# User-defined parameters
set(EC_PROJECT RTS5911 CACHE STRING "EC Project Version")
set_property(CACHE EC_PROJECT PROPERTY STRINGS RTS5911 RTS5913)

project(EC-GCC-Firmware LANGUAGES C ASM)

# Use Git
find_package(Git)

include(${CMAKE_TOOLCHAIN_FILE})
include(${CMAKE_SOURCE_DIR}/cmake/SignTool.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/${EC_PROJECT}.cmake)