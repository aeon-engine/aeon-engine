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
    src/configfile.cpp
    src/configfile.h
    src/console.cpp
    src/console.h
    src/consolelistener.h
    src/filestream.cpp
    src/filestream.h
    src/framelistener.h
    src/game.cpp
    src/game.h
    src/gamestate.h
    src/gamestate_game.cpp
    src/gamestate_game.h
    src/glfwplatform.cpp
    src/glfwplatform.h
    src/image.cpp
    src/image.h
    src/imagecodec.h
    src/imagecodecmanager.cpp
    src/imagecodecmanager.h
    src/imagecodecpng.cpp
    src/imagecodecpng.h
    src/iostream.cpp
    src/iostream.h
    src/main.cpp
    src/material.cpp
    src/material.h
    src/materialmanager.cpp
    src/materialmanager.h
    src/memorystream.cpp
    src/memorystream.h
    src/mesh.cpp
    src/mesh.h
    src/meshmanager.cpp
    src/meshmanager.h
    src/resource.cpp
    src/resource.h
    src/resourcemanager.cpp
    src/resourcemanager.h
    src/root.cpp
    src/root.h
    src/rpggame.cpp
    src/rpggame.h
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
    src/stdafx.cpp
    src/stdafx.h
    src/stream.cpp
    src/stream.h
    src/streamlistener.cpp
    src/streamlistener.h
    src/stringutils.cpp
    src/stringutils.h
    src/submesh.h
    src/texture.cpp
    src/texture.h
    src/texturemanager.cpp
    src/texturemanager.h
)

source_group(main FILES ${AEON_ENGINE_MAIN_SOURCE})

set(AEON_ENGINE_SOURCE
    ${AEON_ENGINE_MAIN_SOURCE}
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
