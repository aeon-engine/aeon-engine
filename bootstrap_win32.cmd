rd /s /q vs_build
mkdir vs_build
pushd vs_build
cmake -G "Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX=install ../
popd
