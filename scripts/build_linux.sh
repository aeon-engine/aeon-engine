#!/bin/bash
# Cleanup
git clean -dfx
git submodule foreach git clean -dfx
git reset --hard
git submodule foreach git reset --hard

# Update
git submodule sync
git submodule update --init

# Build
export GIT_COMMIT_HASH=`git rev-parse --short HEAD`
export BUILD_DIR=ci_build
rm -rf $BUILD_DIR
mkdir $BUILD_DIR
cd $BUILD_DIR
cmake -DCMAKE_INSTALL_PREFIX=install ../
cmake --build . --config Debug -- -j2
ctest -C Debug --verbose
