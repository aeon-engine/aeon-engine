#!/bin/bash

rm -rf build
mkdir build
cd build
cmake ../ -G "Xcode"
open .
cd ..

