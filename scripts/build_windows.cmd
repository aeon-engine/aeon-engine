@rem Cleanup
git clean -dfx || exit /b 1
git submodule foreach git clean -dfx || exit /b 1
git reset --hard || exit /b 1
git submodule foreach git reset --hard || exit /b 1

@rem Update
git submodule sync || exit /b 1
git submodule update --init || exit /b 1

@rem Build
mkdir ci_build || exit /b 1
cd ci_build || exit /b 1

cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX=install ../  || exit /b 1
cmake --build . --config Debug -- /m || exit /b 1

ctest -C Debug --verbose || exit /b 1
