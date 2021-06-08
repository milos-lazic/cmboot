set(_toolchain_install_dir /home/mlazic/Development/embedded/toolchain/gcc-arm-none-eabi-10-2020-q4-major)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Defines the target system.
set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Defines the compiler drivers to use.
set(CMAKE_C_COMPILER   ${_toolchain_install_dir}/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${_toolchain_install_dir}/bin/arm-none-eabi-g++)

# Tell CMake where to locate binaries, headers, and packages.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Set the required GCC/G++ architecture options.
set(CMAKE_C_FLAGS   "-mthumb -mcpu=cortex-m0 -mfloat-abi=soft")
set(CMAKE_CXX_FLAGS "-mthumb -mcpu=cortex-m0 -mfloat-abi=soft")