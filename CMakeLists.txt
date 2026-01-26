cmake_minimum_required(VERSION 3.22.1)

project(DOENGINE)

option(DOENGINE_COVERAGE "Compile with coverage flags" OFF)
option(DOENGINE_TESTS "Compiles and runs tests" OFF)
option(DOENGINE_SAMPLES "Compiles samples" ON)

if(DOENGINE_COVERAGE)
    include(cmake-module/CodeCoverage.cmake)
endif()

# set(CMAKE_EXPORT_COMPILE_COMMANDS true)
 
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(FETCH_SDL_FROM_GIT true)
set(FETCH_GLM_FROM_GIT true)
set(BUILD_SAMPLE_ACTIVE false)
set(DOENGINE_PREFERED_LANGUAGE 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD ${DOENGINE_PREFERED_LANGUAGE})

set(SDL2IMAGE_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)
set(SDL2_DISABLE_INSTALL OFF)
set(SDL2TTF_VENDORED TRUE)

if(FETCH_SDL_FROM_GIT)
   include(cmake-module/fetchSDL3ProjectFromSource.cmake)
 else()
    message("WARNING: SDL Would the Machine Installed Version")
endif()

if(FETCH_GLM_FROM_GIT)
   include(cmake-module/fetchGLMProjectFromSource.cmake)
 else()
    message("WARNING: SDL Would the Machine Installed Version")
endif()


set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)

if(DOENGINE_TESTS)
    enable_testing()
    add_subdirectory(src/test)
endif()

if(DOENGINE_SAMPLES)
    add_subdirectory(sample)
endif()

include_directories(${CMAKE_SOURCE_DIR}/includes)

set(DOENGINE_SRC
    includes/DS.h
    includes/OpenglLoader.h
    includes/WindowManager.h
    includes/Renderer.h
    includes/Logger.h
    src/Application/OpenglLoader.cpp
    src/Application/Geometric.cpp
    src/Application/Logger.cpp
    src/Application/opengl_decls.cpp
    src/Application/opengl_decls.h
    src/Application/SDLOpenglWindow.cpp
    src/Application/SDLOpenglRenderer.cpp
    src/Application/SDLWindowManager.cpp
    src/Application/WindowManager.cpp
    src/Application/SDLWindowManager.h
    src/Application/SDLRenderer.cpp
    src/Application/SDLRenderer.h
    src/Application/SDLTTFText.h
    src/Application/SDLTTFText.cpp
    src/Application/Application.cpp
    src/Application/StringUtils.cpp
    src/Timer/FPSManager.cpp
    src/GameState/GameStateManager.cpp
    src/Timer/FPSManager.cpp
    src/Tilemap/Tilemap.cpp
    src/Tilemap/TileMapEditor.cpp
    src/Texture/Texture.cpp
    src/Event/SDLMouse.cpp
    src/Event/SDLKeyboard.cpp
    src/Music/SDLMusicHandler.cpp
    src/Music/SDLSoundHandler.cpp
    src/Event/SDLJoypad.cpp
    src/Music/SDLMusicHandler.cpp
    src/GameObject/GameObject.cpp
    src/Font/TTFText.cpp
    src/Font/FontCache.cpp
    src/Event/Event.cpp
    src/Event/EventHandler.cpp
    src/Drawable/Gui.cpp
    src/Drawable/UI.cpp
    src/Drawable/TextField.cpp
    src/Application/GameState.cpp
    src/Application/Camera.cpp
    src/Application/SDLTexture.cpp
    src/Application/SDLTexture.h
    src/Drawable/GameObject.cpp
    src/Drawable/Draggable.cpp
    src/Drawable/DraggableGameObject.cpp
    src/Drawable/SelectionRect.cpp
    src/Drawable/MessageBox.cpp
    includes/NativeStructs.h
    includes/Geometric.h
    includes/Color.h
    includes/defines.h
    includes/TTFText.h
    includes/FontCache.h
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
     includes/TileMapEditor.h
     includes/UDPPacket.h
     includes/Vector.h
     includes/Application.h
     includes/Mouse.h
     includes/Keyboard.h
     includes/Joypad.h
     includes/MusicHandler.h
     includes/SDLMusicHandler.h
     includes/SDLSoundHandler.h
     includes/UI.h
     includes/Draggable.h
     includes/DraggableGameObject.h
     includes/SelectionRect.h
     includes/SpriteOffset.h
     includes/TextField.h
     includes/MessageBox.h
)

add_library(${PROJECT_NAME}
  ${DOENGINE_SRC}
)

set(DOENGINE_LIBRARIES )
if(FETCH_SDL_FROM_GIT)
  set(DOENGINE_LIBRARIES ${DOENGINE_LIBRARIES} 
        SDL3::SDL3
        # SDL2::SDL2main
        SDL3_ttf::SDL3_ttf
        SDL3_image::SDL3_image
        SDL2_mixer
        GL
  )    
else()
    set(DOENGINE_LIBRARIES ${DOENGINE_LIBRARIES} 
        SDL2
        SDL2main
        SDL2_ttf
        SDL2_image
        SDL2_mixer
        GL
    )  
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${DOENGINE_LIBRARIES})

message("Copying asssets to buils dir.")
file(COPY ${ASSETS_DIR}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# install(TARGETS ${PROJECT_NAME} DESTINATION /home/afl/Desktop/doengine )


if(${BUILD_SAMPLE_ACTIVE})
#add_executable(${PROJECT_NAME}-sample
#   sample/ignored_main.cpp 
#)
add_executable(${PROJECT_NAME}-pong-sample
   sample/pong/SimplePong.cpp 
)

add_executable(${PROJECT_NAME}-SpaceInvader-sample
   sample/SpaceInvader/SpaceInvader.cpp
)

add_executable(${PROJECT_NAME}-Tetris-sample
   sample/tetris/Tetris.cpp
)

add_executable(${PROJECT_NAME}-MusicPlayer-sample
   sample/MusicPlayer/MusicPlayer.cpp
)
add_executable(BattleSpawn
   sample/BattleSpawn/BattleSpawn.cpp
)
add_executable(PacmanClone
   sample/Pacman/Pacman.cpp
)

add_executable(BattleCityRecreation
   sample/BattleCityRecreation/BattleCityRecreation.cpp
)

add_executable(Tetris
   sample/tetris/Tetris.cpp
)

add_executable(SideScroller
    sample/SideScroller/SideScroller.cpp
)

# to build sample needs 
# Zip support, ubuntu sudo apt-get install libzip-dev
#target_link_libraries(${PROJECT_NAME}-sample PRIVATE
#    ${PROJECT_NAME}
#    ${DOENGINE_LIBRARIES}
#)

target_link_libraries(${PROJECT_NAME}-pong-sample PRIVATE
    ${PROJECT_NAME}
    ${DOENGINE_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}-SpaceInvader-sample PRIVATE
    ${PROJECT_NAME}
    ${DOENGINE_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}-Tetris-sample PRIVATE
    ${PROJECT_NAME}
    ${DOENGINE_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}-MusicPlayer-sample PRIVATE
    ${PROJECT_NAME}
    ${DOENGINE_LIBRARIES}
)

target_link_libraries(BattleSpawn PRIVATE
    ${PROJECT_NAME}
    ${DOENGINE_LIBRARIES}
)

target_link_libraries(PacmanClone PRIVATE
    ${PROJECT_NAME}
    ${DOENGINE_LIBRARIES}
)


target_link_libraries(BattleCityRecreation PRIVATE
    ${PROJECT_NAME}
    ${DOENGINE_LIBRARIES}
)

target_link_libraries(Tetris PRIVATE
    ${PROJECT_NAME}
    ${DOENGINE_LIBRARIES}
)


target_link_libraries(SideScroller PRIVATE
    ${PROJECT_NAME}
    ${DOENGINE_LIBRARIES}
)
endif()