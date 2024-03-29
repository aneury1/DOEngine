cmake_minimum_required(VERSION 3.22.1)

project(DOENGINE)

option(DOENGINE_COVERAGE "Compile with coverage flags" FALSE)
option(DOENGINE_TESTS "Compiles and runs tests" FALSE)

if(DOENGINE_COVERAGE)
    include(cmake-module/CodeCoverage.cmake)
endif()

# set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)

set(SDL2IMAGE_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)
set(SDL2_DISABLE_INSTALL OFF)
set(SDL2TTF_VENDORED TRUE)

if(DOENGINE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

include(FetchContent)

# SDL2
# SET(SDL_SHARED FALSE)
FetchContent_Declare(
    sdl_lib
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.28.2
)

FetchContent_MakeAvailable(sdl_lib)

# SDL2_image
FetchContent_Declare(
    sdl_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_SUBMODULES external/
    GIT_TAG release-2.6.3
)

FetchContent_MakeAvailable(sdl_image)

# SDL2_ttf
FetchContent_Declare(
    sdl_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.20.2
)

FetchContent_MakeAvailable(sdl_ttf)

# SDL2_mixer
SET(SDL2MIXER_VENDORED TRUE)
FetchContent_Declare(
    sdl_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-2.6.3
)

FetchContent_MakeAvailable(sdl_mixer)

include_directories(${CMAKE_SOURCE_DIR}/includes)

add_library(${PROJECT_NAME}
    # Window/Window.cpp
    Timer/FPSManager.cpp
    Tilemap/Tilemap.cpp
    Texture/Texture.cpp
    GameState/GameStateManager.cpp
    GameObject/GameObject.cpp
    Font/TTFText.cpp
    Event/Event.cpp
    Drawable/Canvas.cpp
    Drawable/SDLRenderer.cpp

    includes/defines.h
    includes/abstract/Camera.h
    includes/Event.h
    includes/DOEngine.h
    includes/DOEngine_SDL_includes.h
    includes/abstract/EventHandler.h
    includes/FPSManager.h
    includes/GameObject.h
    includes/GameState.h
    includes/GameStateManager.h
    includes/Grids.h
    includes/LinkList.h
    includes/sort.h
    includes/Sprite.h
    includes/Utils.h
    includes/Texture.h
    includes/Tile.h
    includes/Tilemap.h
    includes/UDPPacket.h
    includes/Vector.h
)

target_link_options(${PROJECT_NAME} PRIVATE
    "LINKER:-static" -static-libgcc -static-libstdc++)
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf SDL2_image
    SDL2_mixer)

add_executable(${PROJECT_NAME}-sample
    # Sample APP
    sample/Window.h
    sample/Window.cpp
    sample/CanvasTestState.cpp
    sample/MatrixTestState.cpp
    sample/SortedState.cpp

    main.cpp
)

target_link_options(${PROJECT_NAME}-sample PRIVATE
    "LINKER:-static" -static-libgcc -static-libstdc++)
target_link_libraries(${PROJECT_NAME}-sample PRIVATE
    ${PROJECT_NAME}
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf SDL2_image
    SDL2_mixer)

# install(TARGETS ${PROJECT_NAME} DESTINATION /home/afl/Desktop/doengine )
