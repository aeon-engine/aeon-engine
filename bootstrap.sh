#!/bin/bash

export BOOST_ROOT=/Users/robindegen/Development/libraries/boost/current
export GLFW_ROOT=/Users/robindegen/Development/libraries/glfw/3.1.1
export GLEW_ROOT=/Users/robindegen/Development/libraries/glew/1.12.0
export GLM_ROOT=/Users/robindegen/Development/libraries/glm/0.9.6.3
export ASSIMP_ROOT=/Users/robindegen/Development/libraries/assimp/3.1.1
export PNG_ROOT=/Users/robindegen/Development/libraries/png/1.6.17
export ZLIB_ROOT=/Users/robindegen/Development/libraries/zlib/1.2.8
rm -rf build
mkdir build
cd build
cmake ../
cd ..

