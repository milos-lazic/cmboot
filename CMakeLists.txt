cmake_minimum_required(VERSION 3.20)
project(DummyProject C CXX ASM)

set(CMAKE_C_LINKER_WRAPPER_FLAG       "-Wl,")
set(CMAKE_C_LINKER_WRAPPER_FLAG_SEP   ",")
set(CMAKE_CXX_LINKER_WRAPPER_FLAG     "-Wl,")
set(CMAKE_CXX_LINKER_WRAPPER_FLAG_SEP ",")

# Current directory scope variables.
set(_target app_dummy)

add_executable(${_target}.elf)

target_sources(${_target}.elf
    PRIVATE
        # src/minimum.c
        src/main.cpp
        src/startup_ARMCM0.S
)

target_compile_options(${_target}.elf
    PRIVATE
        # -std=c99
        -Wall
        --specs=nosys.specs
)

target_link_options(${_target}.elf
    PRIVATE
        --specs=nosys.specs
        LINKER:-Map=${_target}.map
        LINKER:-T,${CMAKE_CURRENT_SOURCE_DIR}/gcc.ld
)