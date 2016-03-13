git submodule update --init

if errorlevel 1 (
    exit /b 1
)

mkdir ci_build

if errorlevel 1 (
    exit /b 1
)

cd ci_build

if errorlevel 1 (
    exit /b 1
)

cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX=install ../

if errorlevel 1 (
    exit /b 1
)

cmake --build . --config Debug -- /m

if errorlevel 1 (
    exit /b 1
)

ctest -C Debug --verbose

if errorlevel 1 (
    exit /b 1
)

