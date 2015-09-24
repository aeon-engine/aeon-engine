#!/bin/bash
pushd $BUILD_DIR
ctest -C Debug --verbose
popd
