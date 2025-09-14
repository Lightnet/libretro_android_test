cmake_minimum_required(VERSION 3.10)
project(libretro_test C)

# Enable shared library output for libretro core
set(BUILD_SHARED_LIBS ON)

# Use FetchContent to download libretro-common
include(FetchContent)
FetchContent_Declare(
    libretro_common
    GIT_REPOSITORY https://github.com/libretro/libretro-common.git
    GIT_TAG master
)
FetchContent_MakeAvailable(libretro_common)

# Define the test core source files (adjust based on actual files in libretro-common)
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/libretro.c
)

# Create the shared library (test_lib.so)
add_library(test_lib SHARED ${SOURCES})

# Include directories for libretro headers
target_include_directories(test_lib PRIVATE
    ${libretro_common_SOURCE_DIR}/include
)

# Set Android-specific properties
set_target_properties(test_lib PROPERTIES
    PREFIX ""  # Remove "lib" prefix for libretro cores
    OUTPUT_NAME "test_lib"  # Name the output test_lib.so
)

# Link any required Android libraries
target_link_libraries(test_lib PRIVATE log)

# Optional: Optimize for ARM (e.g., NEON)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm" OR CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    target_compile_options(test_lib PRIVATE -mfpu=neon)
endif()