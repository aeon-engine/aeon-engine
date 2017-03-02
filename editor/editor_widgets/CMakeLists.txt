include(Utility)
include(GenerateExportHeader)

# https://bugreports.qt.io/browse/QTBUG-55042
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4127 /wd4714")
endif ()

################################################################################

set(AEON_EDITOR_WIDGETS_SOURCES
    src/editor_widget.cpp
    include/aeon/editor_widgets/editor_widget.h

    src/resource_manager_toolbar.cpp
    include/aeon/editor_widgets/resource_manager_toolbar.h
    src/resource_manager_toolbar_plugin.cpp
    src/resource_manager_toolbar_plugin.h

    src/editor_widgets_collection.cpp
    src/editor_widgets_collection.h
)

source_group(widgets FILES ${AEON_EDITOR_WIDGETS_SOURCES})

################################################################################

set(AEON_EDITOR_WIDGETS_UI_SOURCES
    ui/resource_manager_toolbar.ui
)

source_group(ui FILES ${AEON_EDITOR_WIDGETS_UI_SOURCES})

qt5_wrap_ui(AEON_EDITOR_WIDGETS_UI_HEADERS
    ${AEON_EDITOR_WIDGETS_UI_SOURCES}
)

source_group(generated FILES ${AEON_EDITOR_WIDGETS_UI_HEADERS})

################################################################################

set(AEON_EDITOR_WIDGETS_RESOURCES
    res/resources.qrc
)

qt5_add_resources(AEON_EDITOR_WIDGETS_RESOURCES_RCC ${AEON_EDITOR_WIDGETS_RESOURCES})

source_group(generated FILES ${AEON_EDITOR_WIDGETS_RESOURCES_RCC})

################################################################################

add_library(aeon_editor_widgets SHARED
    ${AEON_EDITOR_WIDGETS_SOURCES}
    ${AEON_EDITOR_WIDGETS_MOC_HEADERS}
    ${AEON_EDITOR_WIDGETS_MOC_FILES}
    
    ${AEON_EDITOR_WIDGETS_UI_SOURCES}
    ${AEON_EDITOR_WIDGETS_UI_HEADERS}

    ${AEON_EDITOR_WIDGETS_RESOURCES_RCC}
)

generate_export_header(aeon_editor_widgets)

target_link_libraries(aeon_editor_widgets
    Qt5::Core
    Qt5::Widgets
    Qt5::Designer
)

target_include_directories(aeon_editor_widgets
    PUBLIC
        include
        ${CMAKE_CURRENT_BINARY_DIR}
    PRIVATE
        src
)

set_target_properties(
    aeon_editor_widgets PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/designer"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/designer"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/designer"
    FOLDER editor/widgets
)

target_compile_definitions(aeon_editor_widgets PUBLIC -DQT_NO_KEYWORDS)

