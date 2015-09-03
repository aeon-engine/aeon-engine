include(Common)

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

set(AEON_ENGINE_MAIN_SOURCE
    application.cpp
    application.h
    buffer.cpp
    buffer.h
    buildconfig.h
    main.cpp
    root.cpp
    root.h
    stdafx.cpp
    stdafx.h
    streamlistener.cpp
    streamlistener.h
    stringutils.cpp
    stringutils.h
)

source_group("main" FILES ${AEON_ENGINE_MAIN_SOURCE})

################################################################################

set(AEON_ENGINE_RESOURCES_SOURCE
    image.cpp
    image.h
    imagecodec.h
    imagecodecmanager.cpp
    imagecodecmanager.h
    imagecodecpng.cpp
    imagecodecpng.h
    material.cpp
    material.h
    materialmanager.cpp
    materialmanager.h
    mesh.cpp
    mesh.h
    meshmanager.cpp
    meshmanager.h
    resource.cpp
    resource.h
    resourcemanager.cpp
    resourcemanager.h
    scene.cpp
    scene.h
    scenecodec.h
    scenecodecassimp.cpp
    scenecodecassimp.h
    scenecodecmanager.cpp
    scenecodecmanager.h
    shader.cpp
    shader.h
    shadermanager.cpp
    shadermanager.h
    submesh.h
    texture.cpp
    texture.h
    texturemanager.cpp
    texturemanager.h
)

source_group("resources" FILES ${AEON_ENGINE_RESOURCES_SOURCE})

################################################################################

set(AEON_ENGINE_CONSOLE_SOURCE
    console.cpp
    console.h
    consolelistener.h
    framelistener.h
)

source_group("console" FILES ${AEON_ENGINE_CONSOLE_SOURCE})

################################################################################

set(AEON_ENGINE_PLATFORM_SOURCE
    baseplatform.h
    glfwplatform.cpp
    glfwplatform.h
)

source_group("platform" FILES ${AEON_ENGINE_PLATFORM_SOURCE})

################################################################################

set(AEON_ENGINE_GAME_SOURCE
    game.cpp
    game.h
    gamestate.h
    gamestate_game.cpp
    gamestate_game.h
    rpggame.cpp
    rpggame.h
)

source_group("game" FILES ${AEON_ENGINE_GAME_SOURCE})

################################################################################

generate_source_groups("${AEON_ENGINE_SOURCES}")

set(AEON_ENGINE_SOURCE
    ${AEON_ENGINE_SOURCES} # temporary workaround
    ${AEON_ENGINE_MAIN_SOURCE}
    ${AEON_ENGINE_PLATFORM_SOURCE}
    ${AEON_ENGINE_RESOURCES_SOURCE}
    ${AEON_ENGINE_CONSOLE_SOURCE}
    ${AEON_ENGINE_GAME_SOURCE}
)

################################################################################

add_executable(aeon_engine ${AEON_ENGINE_SOURCE})

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

set_target_properties(aeon_engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
