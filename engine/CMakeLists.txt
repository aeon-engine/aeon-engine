include(Utility)
include(Buildinfo)

generate_build_info_header(${CMAKE_BINARY_DIR}/buildinfo.h)

add_subdirectory(common)

################################################################################

add_source_path(AEON_ENGINE_SOURCES data)
add_source_path(AEON_ENGINE_SOURCES application)
add_source_path(AEON_ENGINE_SOURCES resources)
add_source_path(AEON_ENGINE_SOURCES resources/codecs)
add_source_path(AEON_ENGINE_SOURCES resources/providers)
add_source_path(AEON_ENGINE_SOURCES resources/wrappers)
add_source_path(AEON_ENGINE_SOURCES assets)
add_source_path(AEON_ENGINE_SOURCES storage)

################################################################################

add_source_path(AEON_ENGINE_SOURCES gfx)

if (AEON_GFX_NULL)
    add_source_path(AEON_ENGINE_SOURCES gfx/null)
endif ()

if (AEON_GFX_GL)
    add_source_path(AEON_ENGINE_SOURCES gfx/gl_common)
    add_source_path(AEON_ENGINE_SOURCES gfx/gl)
endif ()

if (AEON_GFX_GLES2)
    add_source_path(AEON_ENGINE_SOURCES gfx/gl_common)
    add_source_path(AEON_ENGINE_SOURCES gfx/gles2)
endif ()

################################################################################

add_source_path(AEON_ENGINE_SOURCES platform)
add_source_path(AEON_ENGINE_SOURCES platform/generic)
add_source_path(AEON_ENGINE_SOURCES platform/null)

if (AEON_PLATFORM_GLFW)
    add_source_path(AEON_ENGINE_SOURCES platform/glfw)
endif ()

if (AEON_PLATFORM_RPI)
    add_source_path(AEON_ENGINE_SOURCES platform/rpi)
endif ()

if (AEON_PLATFORM_QT)
    find_package(Qt5Core REQUIRED)
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5OpenGL REQUIRED)

    add_source_path(AEON_ENGINE_SOURCES platform/qt)

    qt5_wrap_ui(AEON_PLATFORM_QT_UI_HEADERS
        platform/qt/mainwindow.ui
    )

    qt5_wrap_cpp(AEON_PLATFORM_QT_MOC_HEADERS
        platform/qt/platform_qt_window.h
        platform/qt/platform_qt_opengl_widget.h
    )
endif ()

################################################################################

add_source_path(AEON_ENGINE_SOURCES scene)
add_source_path(AEON_ENGINE_SOURCES scene/scene_managers/basic)
add_source_path(AEON_ENGINE_SOURCES scene/scene_managers/octree)

################################################################################

option(AEON_CONSOLE_OUTPUT_DEBUG_MSGS "Console outputs debug/trace messages." ON)
set(AEON_CONSOLE_BUFFER_SIZE 10240 CACHE STRING "The maximum length of a single console line")
set(AEON_DEFAULT_CONSOLE_LOG_LEVEL "console::log_level::info" CACHE STRING "The default minimum log level")
configure_file(build_config.h.in ${CMAKE_BINARY_DIR}/build_config.h @ONLY)

################################################################################



################################################################################

generate_source_groups("${AEON_ENGINE_SOURCES}")

if (AEON_PLATFORM_QT)
    source_group(platform\\qt\\ui FILES ${AEON_PLATFORM_QT_UI_FILES})
    list(APPEND AEON_ENGINE_SOURCES
        ${AEON_PLATFORM_QT_UI_HEADERS}
        ${AEON_PLATFORM_QT_MOC_HEADERS}
    )
endif ()

add_library(aeon_engine STATIC ${AEON_ENGINE_SOURCES})

target_include_directories(aeon_engine
    PUBLIC ${CMAKE_BINARY_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(aeon_engine
    aeon_engine_common
    aeon
    glm
    png_static
    openal
    ogg
    vorbis
    freetype
    assimp
    ${OPENGL_LIBRARIES}
)

if (APPLE)
    target_link_libraries(aeon_engine ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif ()

if (AEON_GFX_GL)
    target_link_libraries(aeon_engine glew_s)
endif ()

if (AEON_PLATFORM_GLFW)
    target_link_libraries(aeon_engine glfw)
endif ()

if (AEON_PLATFORM_RPI)
    target_link_libraries(aeon_engine RaspberryPiSdk)
endif ()

if (AEON_PLATFORM_QT)
    target_link_libraries(aeon_engine
        Qt5::Core
        Qt5::Widgets
        Qt5::OpenGL
    )

    # Do not use emit, signals, slots etc; but use Q_EMIT instead,
    # to avoid nameclashes.
    target_compile_definitions(aeon_engine PUBLIC -DQT_NO_KEYWORDS)
endif ()

set_target_properties(
    aeon_engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER engine
)
