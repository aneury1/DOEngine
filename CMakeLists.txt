cmake_minimum_required(VERSION 3.20)
project(DOEngine VERSION 1.0.0 LANGUAGES C CXX)


set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
        -g3
        -O0
        -fno-omit-frame-pointer
        -fsanitize=address
    )

    add_link_options(
        -fsanitize=address
    )
endif()


include(cmake-module/cmake_option_and_set.cmake)
include(cmake-module/doengine_resolve_target.cmake)
include(cmake-module/doengine_add_family.cmake)
include(cmake-module/merge_script.cmake)


# --- SDL2: use it if the system already has it, else build+install from external/ ---
find_package(SDL2 QUIET CONFIG)
if(NOT SDL2_FOUND)
    message(STATUS "DOEngine: building SDL2 from ${DOENGINE_SDL_EXTERNAL_DIR}/SDL")
    add_subdirectory(${DOENGINE_SDL_EXTERNAL_DIR} ${CMAKE_BINARY_DIR}/_sdl2_build)
else()
    message(STATUS "DOEngine: using system SDL2 (${SDL2_DIR})")
endif()

doengine_resolve_target(_sdl2_target SDL2::SDL2-static SDL2-static SDL2::SDL2 SDL2)

set(sdl2_SOURCE_DIR ${DOENGINE_SDL_EXTERNAL_DIR})
set(_family ${_sdl2_target})


doengine_add_family(SDL2_image DOENGINE_WITH_IMAGE SDL_image)
doengine_add_family(SDL2_ttf   DOENGINE_WITH_TTF   SDL_ttf)
doengine_add_family(SDL2_mixer DOENGINE_WITH_MIXER SDL_mixer)
doengine_add_family(SDL2_net   DOENGINE_WITH_NET   SDL_net)

# --- DOEngine itself ---
file(GLOB_RECURSE DOENGINE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

add_library(DOEngine STATIC ${DOENGINE_SOURCES})
add_library(DOEngine::DOEngine ALIAS DOEngine)

target_include_directories(DOEngine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
        $<BUILD_INTERFACE:${sdl2_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:includes>
)

add_subdirectory(sample)

target_link_libraries(DOEngine PRIVATE ${_family})

merge_static_libraries(
    TARGET DOEngine
    OUTPUT_NAME DOEngine
)

install(FILES ${_monolith}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RENAME ${CMAKE_STATIC_LIBRARY_PREFIX}DOEngine${CMAKE_STATIC_LIBRARY_SUFFIX}
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/includes/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)


