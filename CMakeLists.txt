project(AEON3D)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake/modules)

find_package(OpenGL REQUIRED)
find_package(GLFW3)
find_package(GLEW REQUIRED)

set(CMAKE_CXX_FLAGS "-c -Wall -Wfatal-errors -std=c++11 -O2")

