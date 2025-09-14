cmake_minimum_required(VERSION 3.10)
project(libretro_test C)

# Enable shared library output for libretro core
set(BUILD_SHARED_LIBS ON)

# Use FetchContent to download libretro-common for glsym.h
include(FetchContent)
FetchContent_Declare(
    libretro_common
    GIT_REPOSITORY https://github.com/libretro/libretro-common.git
    GIT_TAG master
)
FetchContent_MakeAvailable(libretro_common)

# Define the source file
set(SOURCES libretro.c)

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

# Find and link OpenGL ES (GLESv2) for Android
find_library(GLESv2_LIBRARY NAMES GLESv2)
find_library(LOG_LIBRARY NAMES log)
target_link_libraries(test_lib PRIVATE
    ${GLESv2_LIBRARY}
    ${LOG_LIBRARY}
)

# Optimize for ARM (e.g., NEON)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm" OR CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    target_compile_options(test_lib PRIVATE -mfpu=neon)
endif()

# Define OpenGL ES version for glsym
target_compile_definitions(test_lib PRIVATE
    GL_GLEXT_PROTOTYPES
    EGL_EGLEXT_PROTOTYPES
)