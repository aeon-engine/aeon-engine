
#!/bin/bash

export CC=${RASPBERRY_PI_GCC_PATH}/bin/arm-unknown-linux-gnueabi-gcc
export CXX=${RASPBERRY_PI_GCC_PATH}/bin/arm-unknown-linux-gnueabi-g++

rm -rf build
mkdir build
cd build
cmake ../ -DAEON_GFX_GL=0 -DAEON_GFX_GLES2=1 -DAEON_PLATFORM_GLFW=0 -DAEON_PLATFORM_RPI=1 -DCMAKE_FIND_ROOT_PATH=${RASPBERRY_PI_GCC_PATH}/arm-unknown-linux-gnueabi -DCMAKE_SYSTEM_NAME=Linux -DCMAKE_SYSTEM_VERSION=1
cd ..
