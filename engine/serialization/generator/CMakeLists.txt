file(GLOB AEON_ENGINE_SERIALIZATION_GENERATOR_DATA
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/objects 
    objects/*.json
)

file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/objects AEON_ENGINE_SERIALIZATION_GENERATOR_DATA_PATH)
file(TO_CMAKE_PATH ${CMAKE_BINARY_DIR} AEON_ENGINE_SERIALIZATION_GENERATOR_DESTINATION)

configure_file(generator_objects.h.in ${CMAKE_CURRENT_BINARY_DIR}/generator_objects.h @ONLY)

set(AEON_ENGINE_SERIALIZATION_GENERATOR_SOURCES
    src/application.cpp
    src/application.h
    src/generator.cpp
    src/generator.h
    src/main.cpp
    src/parser.cpp
    src/parser.h
    src/object.h
)

source_group(serialization FILES ${AEON_ENGINE_SERIALIZATION_GENERATOR_SOURCES})

add_executable(aeon_engine_serialization_generator
    ${AEON_ENGINE_SERIALIZATION_GENERATOR_SOURCES}
)

target_link_libraries(aeon_engine_serialization_generator
    aeon
    json11
)

target_include_directories(aeon_engine_serialization_generator
    PRIVATE
        src
        ${CMAKE_CURRENT_BINARY_DIR}
)

set_target_properties(
    aeon_engine_serialization_generator PROPERTIES
    FOLDER engine
)

add_custom_target(aeon_engine_serialization_generator_runner
    aeon_engine_serialization_generator
    COMMENT "Running Serialization Generator." VERBATIM
)

set_target_properties(
    aeon_engine_serialization_generator_runner PROPERTIES
    FOLDER engine
)

add_dependencies(aeon_engine_serialization_generator_runner aeon_engine_serialization_generator)
