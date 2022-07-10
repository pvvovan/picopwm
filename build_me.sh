#!/bin/bash

mkdir build
cd build

cmake .. -DPICO_SDK_PATH=/mnt/sda1/pvv/github/picopwm/pico-sdk -DCMAKE_BUILD_TYPE=Debug

make all
