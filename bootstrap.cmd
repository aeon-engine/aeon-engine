set BOOST_ROOT=%AEON_LIBRARY_PATH%boost\current
set GLFW_ROOT=%AEON_LIBRARY_PATH%glfw\current
set GLEW_ROOT=%AEON_LIBRARY_PATH%glew\current
set GLM_ROOT=%AEON_LIBRARY_PATH%glm\current
set ASSIMP_ROOT=%AEON_LIBRARY_PATH%assimp\current
set PNG_ROOT=%AEON_LIBRARY_PATH%png\current
set ZLIB_ROOT=%AEON_LIBRARY_PATH%zlib\current
rd /s /q vs_build
mkdir vs_build
cd vs_build
cmake ../ -G "Visual Studio 12 2013 Win64"
cd ..
