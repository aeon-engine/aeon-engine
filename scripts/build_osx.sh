#!/bin/bash
git submodule update --init
export WORKSPACE=$PWD
cd $AEON_LIBRARIES_PATH
git fetch --prune
git checkout origin/master
cd $WORKSPACE
export GIT_COMMIT_HASH=`git rev-parse --short HEAD`
export BUILD_DIR=ci_build
mkdir $BUILD_DIR
cd $BUILD_DIR
cmake -DCMAKE_INSTALL_PREFIX=install -DAEON_ENABLE_CLANG_COVERAGE=1 ../
cmake --build . --config Debug -- -j4
ctest -C Debug --verbose
