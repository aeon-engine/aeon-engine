include(Utility)

set(CMAKE_PREFIX_PATH "$ENV{QTDIR}")

set(QT_USE_QTDESIGNER ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Designer)

add_subdirectory(editor_widgets)
add_subdirectory(application)

