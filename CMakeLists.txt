cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_PATH /mnt/sda1/pvv/github/picopwm/pico-sdk)
set(CMAKE_C_COMPILER /mnt/sda1/pvv/gcc/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER /mnt/sda1/pvv/gcc/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER /mnt/sda1/pvv/gcc/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin/arm-none-eabi-asm)

set(PICO_BOARD pico_w)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_blink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra)

pico_sdk_init()

add_executable(hey_pwm
	hello_pwm.cpp
)

target_include_directories(hey_pwm PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
)

# pull in common dependencies
target_link_libraries(hey_pwm
	pico_stdlib
	hardware_pwm
	pico_cyw43_arch_lwip_poll
)

# create map/bin/hex file etc.
pico_add_extra_outputs(hey_pwm)

