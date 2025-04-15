cmake_minimum_required(VERSION 3.22.1)

project(DOENGINE)

option(DOENGINE_COVERAGE "Compile with coverage flags" OFF)
option(DOENGINE_TESTS "Compiles and runs tests" ON)
option(DOENGINE_SAMPLES "Compiles samples" ON)

if(DOENGINE_COVERAGE)
    include(cmake-module/CodeCoverage.cmake)
endif()

# set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(FETCH_SDL_FROM_GIT true)
set(DOENGINE_PREFERED_LANGUAGE 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD ${DOENGINE_PREFERED_LANGUAGE})

set(SDL2IMAGE_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)
set(SDL2_DISABLE_INSTALL OFF)
set(SDL2TTF_VENDORED TRUE)

if(FETCH_SDL_FROM_GIT)
   include(cmake-module/fetchSDLProjectFromSource.cmake)
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


# message("END Fecthing SDL Source code")
set(DOENGINE_SRC
includes/DS.h
    includes/WindowManager.h
     includes/Renderer.h
     src/Application/Geometric.cpp
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
     src/Texture/Texture.cpp
     src/Event/SDLMouse.cpp
     src/Event/SDLKeyboard.cpp

    src/Music/SDLMusicHandler.cpp
     src/Music/SDLSoundHandler.cpp
     src/Event/SDLJoypad.cpp
     src/Music/SDLMusicHandler.cpp
     src/GameObject/GameObject.cpp
      src/Font/TTFText.cpp
     src/Event/Event.cpp
      src/Drawable/Gui.cpp
      src/Application/SDLTexture.cpp
     src/Application/SDLTexture.h
    includes/NativeStructs.h
    includes/Geometric.h
    includes/Color.h
       includes/defines.h
        includes/TTFText.h
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
      includes/Mouse.h
      includes/Keyboard.h
      includes/Joypad.h
      includes/MusicHandler.h
      includes/SDLMusicHandler.h
      includes/SDLSoundHandler.h
)

add_library(${PROJECT_NAME}
  ${DOENGINE_SRC}
)

set(DOENGINE_LIBRARIES )
if(FETCH_SDL_FROM_GIT)
  set(DOENGINE_LIBRARIES ${DOENGINE_LIBRARIES} 
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_ttf SDL2_image
        SDL2_mixer
  )    
else()
    set(DOENGINE_LIBRARIES ${DOENGINE_LIBRARIES} 
        SDL2
        SDL2main
        SDL2_ttf SDL2_image
        SDL2_mixer
    )  
endif()


target_link_libraries(${PROJECT_NAME} PRIVATE ${DOENGINE_LIBRARIES})

add_executable(${PROJECT_NAME}-sample
   sample/ignored_main.cpp 
)


# to build sample needs 
# Zip support, ubuntu sudo apt-get install libzip-dev
target_link_libraries(${PROJECT_NAME}-sample PRIVATE
    ${PROJECT_NAME}
    ${DOENGINE_LIBRARIES}
 
)

# install(TARGETS ${PROJECT_NAME} DESTINATION /home/afl/Desktop/doengine )
