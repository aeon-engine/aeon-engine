#!/bin/bash
git submodule update --init
export GIT_COMMIT_HASH=`git rev-parse --short HEAD`
export BUILD_DIR=ci_build
mkdir $BUILD_DIR
cd $BUILD_DIR
cmake -DCMAKE_INSTALL_PREFIX=install ../
cmake --build . --config Debug -- -j4
ctest -C Debug --verbose
