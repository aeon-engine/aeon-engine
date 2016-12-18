set DEPLOY_FOLDER=build_deploy

cd %DEPLOY_FOLDER%

echo ==============================================================
echo Building Debug
echo ==============================================================
cd Debug
cmake --build . --config Debug --target INSTALL -- /m
cd ..

echo ==============================================================
echo Building Release
echo ==============================================================
cd Release
cmake --build . --config Release --target INSTALL -- /m
cd ..

cd ..
