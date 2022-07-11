#!/bin/bash

cd openocd/tcl
../src/openocd -f interface/picoprobe.cfg -f target/rp2040.cfg -s tcl
