find_package(Doxygen)

if (DOXYGEN_FOUND)
    message (STATUS "Enabling doxygen target for documentation.")

    include(GitDescribe)
    get_git_describe_tag(AEON_DOXYGEN_PROJECT_NUMBER)

    set(AEON_DOXYGEN_PROJECT_NAME "Aeon Engine" CACHE STRING
        "The project name as shown in Doxygen.")
    set(AEON_DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/doxygen CACHE PATH
        "The output path for doxygen.")
    set(AEON_DOXYGEN_INPUT_DIR ${CMAKE_SOURCE_DIR}/engine)
    set(AEON_DOXYGEN_DOXYFILE ${CMAKE_CURRENT_BINARY_DIR}/doxygen)

    configure_file(doxygen.in ${AEON_DOXYGEN_DOXYFILE} @ONLY)

    add_custom_target(doxygen
        COMMAND ${DOXYGEN_EXECUTABLE} ${AEON_DOXYGEN_DOXYFILE}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating doxygen documentation." VERBATIM
    )
endif ()
