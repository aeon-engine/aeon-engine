#!/bin/bash

rm -rf build
mkdir build
cd build
cmake ../ -G "Xcode" -DAEON_GFX_RENDERER=GLES2 -DAEON_PLATFORM=iOS_Qt
open .
cd ..
