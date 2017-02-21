cmake_minimum_required(VERSION 3.2)
project(json11 VERSION 1.0.0 LANGUAGES CXX)

#enable_testing()

option(JSON11_BUILD_TESTS "Build unit tests" OFF)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(json11 json11.cpp json11.hpp)
target_include_directories(json11 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_compile_options(json11
#  PRIVATE -fno-rtti -fno-exceptions -Wall -Wextra -Werror)
configure_file("json11.pc.in" "json11.pc" @ONLY)

set_target_properties(json11 PROPERTIES
                      FOLDER "External/json11")

if (JSON11_BUILD_TESTS)
  add_executable(json11_test test.cpp)
  target_link_libraries(json11_test json11)
endif()

install(TARGETS json11 DESTINATION lib)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/json11.hpp" DESTINATION include)
install(FILES "${CMAKE_BINARY_DIR}/json11.pc" DESTINATION lib/pkgconfig)
