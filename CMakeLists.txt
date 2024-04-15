cmake_minimum_required(VERSION 3.22.1)

project(DOENGINE)

option(DOENGINE_COVERAGE "Compile with coverage flags" FALSE)
option(DOENGINE_TESTS "Compiles and runs tests" FALSE)

if(DOENGINE_COVERAGE)
    include(cmake-module/CodeCoverage.cmake)
endif()

# set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)


if(DOENGINE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()



message("Fecthing SDL Source code")
# SDL2
# SET(SDL_SHARED FALSE)

include_directories(${CMAKE_SOURCE_DIR}/includes)

# message("END Fecthing SDL Source code")



add_library(${PROJECT_NAME}
    src/Application/Application.cpp
    src/Timer/FPSManager.cpp
    src/Tilemap/Tilemap.cpp
    src/Texture/Texture.cpp
    src/GameState/GameStateManager.cpp
    src/GameObject/GameObject.cpp
    src/Font/TTFText.cpp
    src/Event/Event.cpp
    src/Drawable/Canvas.cpp
    src/Application/SDLRenderer.cpp
    src/Application/SDLWindowManager.cpp
    src/Application/SDLTexture.cpp

    includes/defines.h
    includes/Camera.h
    includes/Event.h
    includes/DOEngine.h
    includes/DOEngine_SDL_includes.h
    includes/EventHandler.h
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
    includes/Application.h
)

# target_link_options(${PROJECT_NAME} PRIVATE
#     "LINKER:-static" -static-libgcc -static-libstdc++)
# target_link_libraries(${PROJECT_NAME} PRIVATE
#     SDL2::SDL2
#     SDL2::SDL2main
#     SDL2_ttf SDL2_image
#     SDL2_mixer)


target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2
    SDL2main
    SDL2_ttf 
    SDL2_image
    SDL2_mixer)