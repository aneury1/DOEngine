#
# merge_static_libraries(
#     TARGET <target>
#     OUTPUT_NAME <output library name>
# )
#
# Example:
# merge_static_libraries(
#     TARGET DOEngine
#     OUTPUT_NAME DOEngine
# )
#
function(merge_static_libraries)

    set(options)
    set(oneValueArgs TARGET OUTPUT_NAME)
    cmake_parse_arguments(MSL "${options}" "${oneValueArgs}" "" ${ARGN})

    if(NOT MSL_TARGET)
        message(FATAL_ERROR "merge_static_libraries(): TARGET is required")
    endif()

    if(NOT MSL_OUTPUT_NAME)
        set(MSL_OUTPUT_NAME ${MSL_TARGET})
    endif()

    set(_monolith
        ${CMAKE_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${MSL_OUTPUT_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX})

    set(_merge_script
        ${CMAKE_BINARY_DIR}/merge_${MSL_OUTPUT_NAME}.cmake)

    file(WRITE ${_merge_script}
"file(GLOB_RECURSE _ARCHIVES \"${CMAKE_BINARY_DIR}/*${CMAKE_STATIC_LIBRARY_SUFFIX}\")\n"
"list(REMOVE_ITEM _ARCHIVES \"${_monolith}\")\n"
"set(_MERGE_DIR \"${CMAKE_BINARY_DIR}/_merge_${MSL_OUTPUT_NAME}\")\n"
"file(REMOVE_RECURSE \"\${_MERGE_DIR}\")\n"
"file(MAKE_DIRECTORY \"\${_MERGE_DIR}\")\n"
"set(_i 0)\n"
"foreach(_lib \${_ARCHIVES})\n"
"    message(STATUS \"Merging: \${_lib}\")\n"
"    set(_dir \"\${_MERGE_DIR}/lib\${_i}\")\n"
"    file(MAKE_DIRECTORY \"\${_dir}\")\n"
"    execute_process(\n"
"        COMMAND \"${CMAKE_AR}\" x \"\${_lib}\"\n"
"        WORKING_DIRECTORY \"\${_dir}\"\n"
"    )\n"
"    math(EXPR _i \"\${_i}+1\")\n"
"endforeach()\n"
"\n"
"file(GLOB_RECURSE _OBJS \"\${_MERGE_DIR}/*${CMAKE_C_OUTPUT_EXTENSION}\")\n"
"file(REMOVE \"${_monolith}\")\n"
"execute_process(\n"
"    COMMAND \"${CMAKE_AR}\" rcs \"${_monolith}\" \${_OBJS}\n"
")\n"
"execute_process(\n"
"    COMMAND \"${CMAKE_RANLIB}\" \"${_monolith}\"\n"
")\n"
"message(STATUS \"Created monolithic library: ${_monolith}\")\n"
    )

    add_custom_command(
        TARGET ${MSL_TARGET}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -P ${_merge_script}
        COMMENT "Creating monolithic static library ${MSL_OUTPUT_NAME}"
        VERBATIM
    )

endfunction()