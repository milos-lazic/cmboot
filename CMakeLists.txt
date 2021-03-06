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
        # src/startup_ARMCM0.c
        # src/NRF51/systemNrf51.c
        src/startup_nrf51.c
        src/arch_ARMCM0.S
)

target_compile_options(${_target}.elf
    PRIVATE
        -Wall
        --specs=nosys.specs
        -ffunction-sections
        -fdata-sections
)

target_include_directories(${_target}.elf
    PRIVATE
        src
        inc
)

target_link_options(${_target}.elf
    PRIVATE
        --specs=nosys.specs
        LINKER:-gc-sections
        LINKER:-Map=${_target}.map
        LINKER:-T,${CMAKE_CURRENT_SOURCE_DIR}/nrf51_boot_gcc.ld
)

add_custom_command(TARGET ${_target}.elf
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex ${_target}.elf ${_target}.hex
    COMMENT "Generating hex file..."
    VERBATIM
)

add_custom_command(TARGET ${_target}.elf
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${_target}.elf ${_target}.bin
    COMMENT "Generating bin file..."
    VERBATIM
)