#!/bin/bash

CMAKE_GENERATOR=${GENERATOR:-Unix Makefiles}

rm -rf build
mkdir build
cd build
cmake ../ -G "${CMAKE_GENERATOR}"
cd ..

