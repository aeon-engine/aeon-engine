#!/bin/bash

export RASPBERRY_PI_SDK_ROOT=/opt/vc

export CC=gcc-6
export CXX=g++-6

rm -rf build
mkdir build
cd build
cmake ../ -DAEON_GFX_RENDERER=GLES2 -DAEON_PLATFORM=RPI -DAEON_SKIP_COPY_ASSETS_TO_RUNTIME_PATH=1 -DASSIMP_BUILD_IFC_IMPORTER=0
cd ..
