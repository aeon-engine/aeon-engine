# Copyright (c) 2012-2017 Robin Degen
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

find_package(OpenGL REQUIRED)

if (APPLE)
    message(STATUS "Building on Apple. Finding Frameworks.")
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    mark_as_advanced(COCOA_LIBRARY IOKIT_LIBRARY COREVIDEO_LIBRARY)

    message(STATUS "Cocoa: ${COCOA_LIBRARY}")
    message(STATUS "IOKit: ${IOKIT_LIBRARY}")
    message(STATUS "CoreVideo: ${COREVIDEO_LIBRARY}")
    target_link_libraries(AeonEngineTemplate ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif ()

add_library(Aeon::Engine STATIC IMPORTED)
set_target_properties(Aeon::Engine PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${AEON_ENGINE_PATH}/include)

if (MSVC)
    set_target_properties(Aeon::Engine PROPERTIES IMPORTED_LOCATION_DEBUG "${AEON_ENGINE_PATH}/lib/aeon_engine_d.lib")
    set_target_properties(Aeon::Engine PROPERTIES IMPORTED_LOCATION_RELEASE "${AEON_ENGINE_PATH}/lib/aeon_engine.lib")

    set(AEON_LIBRARIES "")
    list(APPEND AEON_LIBRARIES opengl32.lib)

    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/aeon_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/aeon_engine_assets_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/aeon_engine_basic_scene_manager_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/aeon_engine_common_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/aeon_engine_data_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/aeon_engine_gfx_core_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/aeon_engine_gfx_gl_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/aeon_engine_gfx_gl_common_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/aeon_engine_input_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/aeon_engine_platform_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/aeon_engine_resources_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/aeon_engine_scene_core_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/aeon_engine_storage_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/assimp-vc140-mt_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/freetype_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/glfw3_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/libglew32_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/libpng_static_d.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:Debug>:${AEON_ENGINE_PATH}/lib/zlibstatic_d.lib>")

    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/aeon.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/aeon_engine_assets.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/aeon_engine_basic_scene_manager.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/aeon_engine_common.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/aeon_engine_data.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/aeon_engine_gfx_core.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/aeon_engine_gfx_gl.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/aeon_engine_gfx_gl_common.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/aeon_engine_input.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/aeon_engine_platform.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/aeon_engine_resources.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/aeon_engine_scene_core.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/aeon_engine_storage.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/assimp-vc140-mt.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/freetype.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/glfw3.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/libglew32.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/libpng_static.lib>")
    list(APPEND AEON_LIBRARIES "$<$<CONFIG:RELEASE>:${AEON_ENGINE_PATH}/lib/zlibstatic.lib>")

    set_target_properties(Aeon::Engine PROPERTIES INTERFACE_LINK_LIBRARIES "${AEON_LIBRARIES}")
endif ()
