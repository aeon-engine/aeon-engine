@echo off

rem Set up common variables
set COMPILER_NAME=Visual Studio 14 2015 Win64
set DEPLOY_FOLDER=build_deploy
set INSTALL_FOLDER=../output

echo ==============================================================
echo Creating deployment folder
echo ==============================================================

rd /s /q %DEPLOY_FOLDER%
mkdir %DEPLOY_FOLDER%
cd %DEPLOY_FOLDER%

echo ==============================================================
echo Bootstrapping Debug
echo ==============================================================
mkdir Debug
cd Debug
cmake ../../ -G "%COMPILER_NAME%" -DCMAKE_INSTALL_PREFIX=%INSTALL_FOLDER%
cd ..

echo ==============================================================
echo Bootstrapping Release
echo ==============================================================
mkdir Release
cd Release
cmake ../../ -G "%COMPILER_NAME%" -DCMAKE_INSTALL_PREFIX=%INSTALL_FOLDER%
cd ..

echo ==============================================================
echo Building Debug
echo ==============================================================
mkdir Debug
cd Debug
cmake --build . --config Debug --target INSTALL -- /m
cd ..

echo ==============================================================
echo Building Release
echo ==============================================================
mkdir Release
cd Release
cmake --build . --config Release --target INSTALL -- /m
cd ..
