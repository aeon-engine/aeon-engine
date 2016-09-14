#!/bin/bash
git submodule update --init
export GIT_COMMIT_HASH=`git rev-parse --short HEAD`
export BUILD_DIR=ci_build
rm -rf $BUILD_DIR
mkdir $BUILD_DIR
cd $BUILD_DIR
cmake -G "Xcode" -DCMAKE_INSTALL_PREFIX=install ../
xcodebuild -parallelizeTargets -project AeonEngine.xcodeproj -configuration Debug clean build
ctest -C Debug --verbose
