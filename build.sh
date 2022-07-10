#!/bin/bash

rm -rf ./build

mkdir build
cd build

cmake .. -D CMAKE_BUILD_TYPE=Debug \
-D PICO_SDK_PATH=/mnt/sda1/pvv/github/picopwm/pico-sdk \
-D CMAKE_C_COMPILER=/mnt/sda1/pvv/gcc/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc \
-D CMAKE_CXX_COMPILER=/mnt/sda1/pvv/gcc/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin/arm-none-eabi-g++

make all -j8
