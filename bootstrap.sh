#!/bin/bash

export BOOST_ROOT=/Development/Libraries/Binary/boost/current
export GLFW_ROOT=/Development/Libraries/Binary/glfw/current
export GLEW_ROOT=/Development/Libraries/Binary/glew/current
export GLM_ROOT=/Development/Libraries/Binary/glm/current
export ASSIMP_ROOT=/Development/Libraries/Binary/assimp/current
export PNG_ROOT=/Development/Libraries/Binary/png/current
export ZLIB_ROOT=/Development/Libraries/Binary/zlib/current
rm -rf xcode_build
mkdir xcode_build
cd xcode_build
cmake ../ -G "Xcode"
cd ..

