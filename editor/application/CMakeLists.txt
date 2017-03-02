include(Utility)

################################################################################

set(AEON_EDITOR_APPLICATION_SOURCES
    application/main.cpp
    application/application.cpp
    application/application.h
    application/frm_mainwindow_view.cpp
    application/frm_mainwindow_view.h
)

source_group(application FILES ${AEON_EDITOR_APPLICATION_SOURCES})

################################################################################

set(AEON_EDITOR_UI_SOURCES
    ui/frm_mainwindow.ui
)

source_group(ui FILES ${AEON_EDITOR_UI_SOURCES})

qt5_wrap_ui(AEON_EDITOR_UI_HEADERS
    ${AEON_EDITOR_UI_SOURCES}
)

source_group(generated FILES ${AEON_EDITOR_UI_HEADERS})

################################################################################

set(AEON_EDITOR_RESOURCES
    resources/resources.qrc
)

qt5_add_resources(AEON_EDITOR_RESOURCES_RCC ${AEON_EDITOR_RESOURCES})

source_group(generated FILES ${AEON_EDITOR_UI_HEADERS})

################################################################################

set (AEON_ADDITIONAL_RESOURCES "")
if (APPLE)
    set(AEON_EDITOR_OSX_ICON_NAME aeon.icns)
    set(AEON_EDITOR_OSX_ICON ${CMAKE_CURRENT_SOURCE_DIR}/resources/icon/${AEON_EDITOR_OSX_ICON_NAME})
    set(MACOSX_BUNDLE_ICON_FILE ${AEON_EDITOR_OSX_ICON_NAME})
    set_source_files_properties(${AEON_EDITOR_OSX_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    list(APPEND AEON_ADDITIONAL_RESOURCES ${AEON_EDITOR_OSX_ICON})
endif ()

add_executable(aeon_editor WIN32 MACOSX_BUNDLE
    ${AEON_EDITOR_APPLICATION_SOURCES}
    ${AEON_EDITOR_APPLICATION_MOC_FILES}

    ${AEON_EDITOR_UI_HEADERS}
    ${AEON_EDITOR_RESOURCES_RCC}
    ${AEON_ADDITIONAL_RESOURCES}
)

target_link_libraries(aeon_editor
    aeon
    aeon_engine
    aeon_engine_common
    aeon_engine_data
    aeon_engine_gfx_core
    aeon_engine_gfx_gl
    aeon_editor_widgets
    Qt5::Core
    Qt5::Widgets
)

target_include_directories(aeon_editor
    PRIVATE
        application
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)

set_target_properties(
    aeon_editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER editor
)

target_compile_definitions(aeon_editor PUBLIC -DQT_NO_KEYWORDS -DQT_NO_OPENGL_ES_2)

set_working_dir(aeon_editor "${CMAKE_SOURCE_DIR}/bin")

