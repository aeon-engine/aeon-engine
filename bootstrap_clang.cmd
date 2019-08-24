rd /s /q vs_build
mkdir vs_build
cd vs_build
cmake ../ -G "Visual Studio 16 2019" -T ClangCL -A x64 -DCMAKE_SYSTEM_VERSION=10.0 -DCMAKE_INSTALL_PREFIX=install
cd ..
