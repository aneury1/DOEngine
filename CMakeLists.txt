cmake_minimum_required(VERSION 3.20)

project(doengine VERSION 1.0 LANGUAGES C CXX)

# ------------------------------------------------------------
# Global options
# ------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

include(cmake-module/merge_script.cmake)

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


# Never search system packages
set(CMAKE_DISABLE_FIND_PACKAGE_SDL2 TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_SDL2_image TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_SDL2_ttf TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_SDL2_mixer TRUE)

# ------------------------------------------------------------
# SDL options
# ------------------------------------------------------------

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)

set(SDL2IMAGE_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_TESTS OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE)

set(SDL2TTF_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2TTF_TESTS OFF CACHE BOOL "" FORCE)
set(SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE)

set(SDL2MIXER_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_INSTALL OFF CACHE BOOL "" FORCE)

# ------------------------------------------------------------
# Add local SDL repositories
# ------------------------------------------------------------

add_subdirectory(
    external/doengine-shared/SDL2/SDL
    EXCLUDE_FROM_ALL
)

add_subdirectory(
    external/doengine-shared/SDL2/SDL_image
    EXCLUDE_FROM_ALL
)

add_subdirectory(
    external/doengine-shared/SDL2/SDL_ttf
    EXCLUDE_FROM_ALL
)

add_subdirectory(
    external/doengine-shared/SDL2/SDL_mixer
    EXCLUDE_FROM_ALL
)

# ------------------------------------------------------------
# doengine sources
# ------------------------------------------------------------

# --- doengine itself ---
file(GLOB_RECURSE DOENGINE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

add_library(doengine STATIC
    ${DOENGINE_SOURCES}
)

target_include_directories(doengine
PUBLIC
    includes
)

add_subdirectory(sample)

target_link_libraries(doengine
PUBLIC
    SDL2-static
    SDL2_image
    SDL2_ttf
    SDL2_mixer
)

target_compile_features(doengine PUBLIC cxx_std_17)

