#!/bin/bash
NUM_JOBS=10
DEPLOY_DIR=build_deploy
BUILD_CONFIGURATION=Debug

ROOT_DIR=$(PWD)

echo ==============================================================
echo Creating deployment folder
echo ==============================================================

rm -rf $DEPLOY_DIR
mkdir $DEPLOY_DIR
cd $DEPLOY_DIR

echo ==============================================================
echo Bootstrapping $BUILD_CONFIGURATION
echo ==============================================================

mkdir src
cd src
mkdir $BUILD_CONFIGURATION
cd $BUILD_CONFIGURATION
cmake ../../../ -DCMAKE_BUILD_TYPE=$BUILD_CONFIGURATION -DCMAKE_INSTALL_PREFIX=$ROOT_DIR/$DEPLOY_DIR/$BUILD_CONFIGURATION

echo ==============================================================
echo Building $BUILD_CONFIGURATION
echo ==============================================================

cmake --build . --config $BUILD_CONFIGURATION --target install -- -j$NUM_JOBS
cd ..
cd ..

