include(PrecompiledHeader)

include_directories(
    ${CMAKE_SOURCE_DIR}/dep/libaeon/include
    ${Boost_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
    src
)

set(AEON_ENGINE_MAIN_SOURCE
    src/application.cpp
    src/application.h
    src/buffer.cpp
    src/buffer.h
    src/buildconfig.h
    src/iostream.cpp
    src/iostream.h
    src/main.cpp
    src/root.cpp
    src/root.h
    src/stdafx.cpp
    src/stdafx.h
    src/streamlistener.cpp
    src/streamlistener.h
    src/stringutils.cpp
    src/stringutils.h
)

source_group("main" FILES ${AEON_ENGINE_MAIN_SOURCE})

################################################################################

set(AEON_ENGINE_RESOURCES_SOURCE
    src/image.cpp
    src/image.h
    src/imagecodec.h
    src/imagecodecmanager.cpp
    src/imagecodecmanager.h
    src/imagecodecpng.cpp
    src/imagecodecpng.h
    src/material.cpp
    src/material.h
    src/materialmanager.cpp
    src/materialmanager.h
    src/mesh.cpp
    src/mesh.h
    src/meshmanager.cpp
    src/meshmanager.h
    src/resource.cpp
    src/resource.h
    src/resourcemanager.cpp
    src/resourcemanager.h
    src/scene.cpp
    src/scene.h
    src/scenecodec.h
    src/scenecodecassimp.cpp
    src/scenecodecassimp.h
    src/scenecodecmanager.cpp
    src/scenecodecmanager.h
    src/shader.cpp
    src/shader.h
    src/shadermanager.cpp
    src/shadermanager.h
    src/submesh.h
    src/texture.cpp
    src/texture.h
    src/texturemanager.cpp
    src/texturemanager.h
)

source_group("resources" FILES ${AEON_ENGINE_RESOURCES_SOURCE})

################################################################################

set(AEON_ENGINE_CONSOLE_SOURCE
    src/console.cpp
    src/console.h
    src/consolelistener.h
    src/framelistener.h
)

source_group("console" FILES ${AEON_ENGINE_CONSOLE_SOURCE})

################################################################################

set(AEON_ENGINE_PLATFORM_SOURCE
    src/baseplatform.h
    src/glfwplatform.cpp
    src/glfwplatform.h
)

source_group("platform" FILES ${AEON_ENGINE_PLATFORM_SOURCE})

################################################################################

set(AEON_ENGINE_GAME_SOURCE
    src/game.cpp
    src/game.h
    src/gamestate.h
    src/gamestate_game.cpp
    src/gamestate_game.h
    src/rpggame.cpp
    src/rpggame.h
)

source_group("game" FILES ${AEON_ENGINE_GAME_SOURCE})

################################################################################

set(AEON_ENGINE_SOURCE
    ${AEON_ENGINE_MAIN_SOURCE}
    ${AEON_ENGINE_PLATFORM_SOURCE}
    ${AEON_ENGINE_RESOURCES_SOURCE}
    ${AEON_ENGINE_CONSOLE_SOURCE}
    ${AEON_ENGINE_GAME_SOURCE}
)

################################################################################

use_precompiled_header(aeon_engine
    src/stdafx.h
    src/stdafx.cpp
)

add_executable(aeon_engine ${AEON_ENGINE_SOURCE})

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

set_target_properties(aeon_engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
