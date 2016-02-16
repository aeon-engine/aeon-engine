git submodule update --init
mkdir ci_build
cd ci_build
cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX=install ../
cmake --build . --config Debug -- /m
ctest -C Debug --verbose
