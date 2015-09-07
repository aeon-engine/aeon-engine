include(Common)

################################################################################

add_source_path(AEON_ENGINE_SOURCES common)
add_source_path(AEON_ENGINE_SOURCES console)
add_source_path(AEON_ENGINE_SOURCES resources)
add_source_path(AEON_ENGINE_SOURCES resources/codec)

################################################################################

add_source_path(AEON_ENGINE_SOURCES gfx)

if (AEON_GFX_GL)
    add_source_path(AEON_ENGINE_SOURCES gfx/gl)
endif ()

################################################################################

add_source_path(AEON_ENGINE_SOURCES platform)

if (AEON_PLATFORM_GLFW)
    add_source_path(AEON_ENGINE_SOURCES platform/glfw)
endif ()

################################################################################

generate_source_groups("${AEON_ENGINE_SOURCES}")

add_executable(aeon_engine ${AEON_ENGINE_SOURCES})

target_include_directories(aeon_engine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${Boost_INCLUDE_DIRS}
    PUBLIC ${GLEW_INCLUDE_DIRS}
    PUBLIC ${GLFW_INCLUDE_DIRS}
    PUBLIC ${ASSIMP_INCLUDE_DIRS}
    PUBLIC ${GLM_INCLUDE_DIRS}
    PUBLIC ${ZLIB_INCLUDE_DIRS}
    PUBLIC ${PNG_INCLUDE_DIRS}
)

target_link_libraries(aeon_engine
    aeon
    ${Boost_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${ASSIMP_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${PNG_LIBRARIES}
    ${ZLIB_LIBRARIES}
)

if (APPLE)
    target_link_libraries(aeon_engine ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif ()

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE -D_WIN32_WINNT=0x0601")
endif (MSVC)

set_target_properties(
    aeon_engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)
