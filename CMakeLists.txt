cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_blink C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# include(example_auto_set_url.cmake)

add_executable(pico_pwm
	hello_pwm.cpp
)

# pull in common dependencies
target_link_libraries(pico_pwm pico_stdlib hardware_pwm)

# create map/bin/hex file etc.
pico_add_extra_outputs(pico_pwm)
