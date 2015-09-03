macro(add_source_path target dir)
    set(source_files "")
    file(
        GLOB source_files
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
            ${dir}/*.cpp
            ${dir}/*.h
    )
    list(APPEND ${target} "${source_files}")
endmacro()

macro(generate_source_groups sources)
    foreach(f ${sources})
        string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" source_group_name ${f})
        string(REPLACE / \\ source_group_name ${source_group_name})
        source_group("${source_group_name}" FILES ${f})
    endforeach()
endmacro()
